#include <ansi.h>
#include <public.h>
#include <effect.h>
#include <skill.h>
#include <time.h>
#define _DEBUG(str) ;								  //if(objectp(find_char("1"))) {tell_user(find_char("1"),str);}
#define AUTO_REMOVE_ANGEL 0							  //	是否自动在关闭活动时自动清除“活动天使”
#define LOCK_PLAYER_DAMAGE 100000					  //	设置每次对玩家的固定伤害值
#define ACTIVE_ANGEL_NPC "npc/party/gtt_active_angel" //	活动天使存放位置
#define TIGER_KING_NPC "npc/party/gtt_tiger_king"	  //	真假虎王存放位置
#define TEMP_WORKER_NPC "npc/party/gtt_temp_worker"	  //	临时传送工存放位置
#define VIRTUAL_MAP "inh/std/normal"				  //	虚拟地图位置

private
static int active_is_open = 1; //	活动开启标志

private
static mapping active_bonus = ([ //	活动奖励内容结构
	1:({"A013", "Nhất Mã Bình Xuyên", "0"}),
	2:({"A013", "Nhất Mã Bình Xuyên", "10,000"}),
	3:({"A013", "Nhất Mã Bình Xuyên", "20,000"}),
	4:({"A013", "Nhất Mã Bình Xuyên", "50,000"}),
	5:({"A017", "Võ Tòng Đả Hổ", "100,000"}),
	6:({"A018", "Diệt Lục Hổ Tướng", "1,000,000", "Ngoại kháng +10, Nội kháng +10( Danh hiệu thuộc tính cần người chơi sau khi trang bị danh hiệu mới có tác dụng )"}),
]);
private
static int *left_tiger_position = ({35, 31});
private
static int pro_tiger_distance = 2;
/*------------------------------------------完毕----------------------------------------------*/

/*--------------------------------------公有函数接口------------------------------------------*/
int turn_on_activity();													  //	开启活动的功能函数 -- 成功返回1 失败 0
int turn_off_activity();												  //	关闭活动的功能函数 -- 成功返回1 失败 0							  //	设置活动时间需要两个整型参数 [0-6][00-23][00-59]
int active_main_logic(object who, int level);							  //	《真假虎王》活动的主逻辑?
int is_active_open();													  //	判断当前活动的开启状态
int is_in_active_area();												  //	判断当前时间是否在活动时间范围内
void delete_tigers_on_player(object who, int act);						  //	清除掉玩家身上所对应的虎王标记
void when_player_dead(object who);										  //	当玩家死亡时执行的函数
void when_enemy_be_hit(object me, object who, int hit_act, int distance); //	当玩家被攻击时所执行的函数										  //	获取当前已经设定好的活动时间
string *get_active_bonus(int level);									  //	获取过关等级所对应的奖励数组
/*------------------------------------------完毕----------------------------------------------*/

/*----------------------------------------初始函数--------------------------------------------*/
void create()
{

	if (active_is_open)
	{
		turn_on_activity();
	}
	else
	{
		turn_off_activity();
	}
}
/*------------------------------------------完毕----------------------------------------------*/

/*-----------------------------------------私有函数-------------------------------------------*/
//	返回一个范围不重复乱序的整数数组-- 这里假定乱序数字是一个连续整体且间隔为1
private
int *make_only_number(int from, int to)
{
	int *original_dict = ({});
	int *result_dict = ({});
	int tmp, i, size;
	if (from > to)
	{
		tmp = to;
		to = from;
		from = tmp;
	}
	for (i = 0, size = (to - from); i < size; i++)
	{
		original_dict += ({from + i});
	}
	for (i = 0; i < size; i++)
	{
		tmp = random(to - from - i);
		result_dict += ({original_dict[tmp]});
		original_dict -= ({original_dict[tmp]});
	}
	return result_dict;
}

//	生成虎王
private
object *invite_tiger_kings(int number, int strong, int week)
{
	object *tiger_kings = ({});
	object tmp_tiger_king;
	int i, *only_int_number, total;
	total = strong + week;
	only_int_number = make_only_number(0, total);
	for (i = 0; i < total; i++)
	{
		if (only_int_number[i] < strong)
		{
			//	设置较强虎王的属性
			tmp_tiger_king = new (TIGER_KING_NPC);
			tmp_tiger_king->set_walk_speed(1);
			tmp_tiger_king->set_walk_step(2);
			tmp_tiger_king->set_max_seek(8);
			tmp_tiger_king->set_attack_speed(10);
			tmp_tiger_king->set_dp(50000);
			tmp_tiger_king->set_pp(50000);
			tmp_tiger_king->set_max_hp(100000);
			tmp_tiger_king->set_max_mp(100000);
			tmp_tiger_king->set_ap(100000);
			tmp_tiger_king->set_cp(100000);
			tmp_tiger_king->set_when_enemy_dead((
				: when_player_dead:));
			tmp_tiger_king->set_when_enemy_be_hit((
				: when_enemy_be_hit:));
			tmp_tiger_king->set("enemy", number);
			tiger_kings += ({tmp_tiger_king});
		}
		else
		{
			//	设置较弱虎王的属性
			tmp_tiger_king = new (TIGER_KING_NPC);
			tmp_tiger_king->set_walk_speed(20);
			tmp_tiger_king->set_attack_speed(20);
			tmp_tiger_king->set_max_hp(10);
			tmp_tiger_king->set_max_mp(10);
			tmp_tiger_king->set_ap(10);
			tmp_tiger_king->set_dp(10);
			tmp_tiger_king->set_cp(10);
			tmp_tiger_king->set_pp(10);
			tmp_tiger_king->set("enemy", number);
			tmp_tiger_king->set_when_enemy_dead((
				: when_player_dead:));
			tiger_kings += ({tmp_tiger_king});
		}
	}
	return tiger_kings;
}
//	无条件清除NPCs
private
int byebye_npcs(object *npcs)
{
	int i, size;
	for (i = 0, size = sizeof(npcs); i < size; i++)
	{
		if (objectp(npcs[i]) && get_x(npcs[i]) > 0)
		{
			npcs[i]->remove_from_scene();
			destruct(npcs[i]);
		}
		else
		{
			_DEBUG(sprintf("DEBUG --  Không thể tẩy trừ %x#", getoid(npcs[i])));
		}
	}
	npcs = ({});
	return 1;
}
//	产生一个有效的地图位置
private
int get_valid_xy_point(int z)
{
	int p, i;
	for (i = 0, p = 0; i < 50; i++)
	{
		if (p = efun::get_xy_point(z, IS_CHAR_BLOCK))
		{
			return p;
		}
	}
}
/*-------------------------------------------完毕---------------------------------------------*/

/*-----------------------------------------公有函数-------------------------------------------*/
//	开启活动
int turn_on_activity()
{
	active_is_open = 1;
	_DEBUG("DEBUG -- Thành công mở ra hoạt động!");
	return 1;
}
//	关闭活动
int turn_off_activity()
{
	active_is_open = 0;
	_DEBUG("DEBUG -- Thành công đóng lại hoạt động!");
	return 1;
}
//	判断当前时间活动是否可以开启 可以返回1 否则返回0
int is_in_active_area()
{
	return active_is_open;
}
//	判断当前《真假虎王》是否处于开启状态
int is_active_open()
{
	return active_is_open;
}
string *get_active_bonus(int level)
{
	level = level > 6 ? 6 : level < 1 ? 1
									  : level;
	return active_bonus[level];
}
//	清除掉玩家身上所对应的虎王标记
void delete_tigers_on_player(object who, int act)
{
	mixed tigers_id;
	object item;
	int i, size;
	tigers_id = who->get("guess_true_tiger_tigers");
	for (i = 0, size = sizeof(tigers_id); i < size; i++)
	{
		if (item = find_char(tigers_id[i]))
		{
			if (item->is_npc())
			{
				item->remove_from_scene(act);
				item->before_destruct();
				destruct(item);
			}
			else
			{
				_DEBUG(sprintf("DEBUG -- Hổ Vương %s Không phải NPC", tigers_id[i]));
			}
		}
		else
		{
			_DEBUG(sprintf("DEBUG -- Không tìm được đối tượng tương ứng %s ", tigers_id[i]));
		}
	}
	who->delete ("guess_true_tiger_tigers");
	who->delete_save("guess_true_tiger_fight");
}
//	当玩家被打死时所执行的函数
void when_player_dead(object who)
{
	int old_z;
	object old_city;
	send_user(who, "%c%s", '!', "Thật đáng tiếc, ngươi vượt ải thất bại, không thu được bất kì phần thưởng nào.");
	if ((old_z = who->get("guess_true_tiger_map")) && (get_z(who) == old_z))
	{
		old_city = get_map_object(old_z);
		VIRTUAL_MAP->destruct_virtual_map(old_city, old_z);
	}
	who->add_to_scene(1, 152, 130, 3);
	who->delete_save("guess_true_tiger");
	who->delete ("guess_true_tiger_map");
	//who->set_save("userkill",1);
	//who->set_die(1);
	delete_tigers_on_player(who, 0);
}
//	当玩家受到攻击时所执行的函数
void when_enemy_be_hit(object me, object who, int hit_act, int distance)
{
	send_user(who, "%c%d%w%c%d%w%c", 0x48, getoid(who), LOCK_PLAYER_DAMAGE, get_d(who), getoid(me), hit_act, hit_act == HIT_NORMAL ? 2 : 1);
	CHAR_DIE_D->is_enemy_die(me, who, LOCK_PLAYER_DAMAGE);
}
//	开始游戏 -- 此次活动的主逻辑函数
int active_main_logic(object player, int level)
{
	object map, old_city, temp_worker;
	object *tiger_kings = ({});
	int x, y, z, d, size, i, p, old_z, *only_random_number, iTime, iDay;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];
	player->set("guess_true_tiger_nojump", 1);
	switch (level)
	{
	case 1:
		if ((z = find_map_flag(1000, 2999, 0)) <= 0)
		{
			return 1;
		}
		player->delete_save("guess_true_tiger");
		player->delete_save("guess_true_tiger_fight");
		player->set("guess_true_tiger_tigers", ({}));
		player->set("guess_true_tiger_map", z);
		d = 891;
		init_virtual_map(z, d);
		map = new (VIRTUAL_MAP);
		map->set_client_id(d);
		map->set_owner(player);
		map->set_name("Khu vực hoạt động Thật Giả Hổ Vương");
		set_map_object(map, map->set_id(z));
		tiger_kings = invite_tiger_kings(player->get_number(), 1, 6);
		size = sizeof(tiger_kings);
		only_random_number = make_only_number(0, size);
		for (i = 0; i < size; i++)
		{
			p = get_valid_xy_point(z);
			tiger_kings[only_random_number[i]]->add_to_scene(z, p / 1000, p % 1000, 3);
			//tiger_kings[only_random_number[i]]->add_to_scene(z,left_tiger_position[0]+i*pro_tiger_distance,left_tiger_position[1],3);
			player->add("guess_true_tiger_tigers", ({sprintf("%x#", getoid(tiger_kings[i]))}));
		}
		temp_worker = new (TEMP_WORKER_NPC);
		temp_worker->add_to_scene(z, 36, 40, 5);
		p = get_valid_xy_point(z);
		player->set_save("gtt.day", iDay);
		player->add_to_scene(z, p / 1000, p % 1000, 3);
		player->add_cash(-10000);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		tiger_kings = invite_tiger_kings(player->get_number(), level, 7 - level);
		size = sizeof(tiger_kings);
		only_random_number = make_only_number(0, size);
		player->set("guess_true_tiger_tigers", ({}));
		z = player->get("guess_true_tiger_map");
		for (i = 0; i < size; i++)
		{
			p = get_valid_xy_point(z);
			tiger_kings[only_random_number[i]]->add_to_scene(z, p / 1000, p % 1000, 3);
			//tiger_kings[only_random_number[i]]->add_to_scene(player->get("guess_true_tiger_map"),left_tiger_position[0]+i*pro_tiger_distance,left_tiger_position[1],3);
			player->add("guess_true_tiger_tigers", ({sprintf("%x#", getoid(tiger_kings[i]))}));
		}
		break;
	case 7:
		if ((old_z = player->get("guess_true_tiger_map")) && (get_z(player) == old_z))
		{
			old_city = get_map_object(old_z);
			player->add_to_scene(1, 152, 130, 3);
			VIRTUAL_MAP->destruct_virtual_map(old_city, old_z);
		}
		break;
	}
	return 1;
}
/*-------------------------------------------完毕---------------------------------------------*/
/*-------------------------------------------调试---------------------------------------------*/
/*-------------------------------------------完毕---------------------------------------------*/

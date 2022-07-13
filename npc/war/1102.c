#include <ansi.h>
#include <city.h>
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <cmd.h>

inherit BADMAN;

int weapon;

int is_caster;

int is_war_npc() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Yêu Ma Đại Tướng");
	set_level(60);
	set_max_hp(100);
	set_max_mp(0);
	set_ap(400);
	set_dp(300);
	set_cp(0);
	set_pp(300);
	set_sp(0);

	set_walk_speed(3);
	set_attack_speed(15);
	set_max_seek(4);
	set_char_picid(10);
	set_walk_step(1);
	set("no_correct_exp", 1);
	setup();

	set_char_type(FIGHTER_TYPE_2); // 重设类型
}

int is_caster()
{
	return is_caster;
}

int set_caster(int flag) { return is_caster = flag; }

// 函数：获取装备代码
int get_weapon_code() { return weapon; }

// 函数：获取装备代码
int set_weapon_code(int flag) { return weapon = flag; }

// 函数：特技攻击对手
int perform_action(object who)
{
	if (get_weapon_code() == UNARMED && is_caster() == 0)
		return 0;
	if (get_weapon_code() == THROWING)
		return PF_FILE_01611->perform_action_npc(this_object(), who);
	return PF_FILE_04232->perform_action_npc(this_object(), who);
}

// 函数：掉宝奖励
void win_bonus(object who) { __FILE__->win_bonus2(this_object(), who); }

// 函数：掉宝奖励(在线更新)
void win_bonus2(object me, object who)
{
	string name, result, id, owner, file;
	object orgnpc, map, item, leader, item2, item3, item4, item5, item6, item7, item8, item9, item10;
	int z, p, x, y, number, add, rand, rate;
	int drop = 1;
	"/sys/npc/npc"->win_bonus(me, who);
	if (who->is_npc())
	{
		who = who->get_owner();
	}
	if (!who)
		return;
	if (who->is_npc())
		return;
	id = who->get_leader();
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	if (!id)
		owner = who->get_id();
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
			owner = who->get_id();
	}
	rate = who->get_online_rate();
	if (random100() < 100 * rate / 100)
	{
		if (random(2))
			file = BOOK_FILE->get_book_file();
		else
			file = "/item/44/4489";
		item = new (file);
		if (item && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
		{
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	rand = random(10000);
	/*	if (rand<1500*rate/100)
	{
		if (random(2))
			file = ARMOR_FILE->get_armor_file_2(me->get_level());
		else
			file = WEAPON_FILE->get_weapon_file_2(me->get_level());
		item = new (file);
		"/sys/item/equip"->init_equip_prop_3(item);
	}
	else
	if (rand<2500*rate/100)
	{
		file = "/quest/product2"->get_random_level_blue_product(me->get_level(), me->get_level());
		item = new (file);
	}	
	else
	if (rand<3500*rate/100)
	{
		file = BOOK_FILE->get_book_file();
		item = new (file);
		file = BOOK_FILE->get_book_file();
		item2 = new (file);
		file = BOOK_FILE->get_book_file();
		item3 = new (file);		
		file = BOOK_FILE->get_book_file();
		item4 = new (file);
		file = BOOK_FILE->get_book_file();
		item5 = new (file);					
	}	
	else
	if (rand<4500*rate/100)
	{		
		item = new ("/item/44/4489");
		item2 = new ("/item/44/4489");
		item3 = new ("/item/44/4489");
		item4 = new ("/item/44/4489");
		item5 = new ("/item/44/4489");
		item6 = new ("/item/44/4489");		
	}
	else
	if (rand<5500*rate/100)
	{
		file = "/quest/product2"->get_random_card();
		item = new (file);
		file = "/quest/product2"->get_random_card();
		item2 = new (file);
		file = "/quest/product2"->get_random_card();
		item3 = new (file);		
		file = "/quest/product2"->get_random_card();
		item4 = new (file);	
		file = "/quest/product2"->get_random_card();
		item5 = new (file);							
	}	
	else
	if (rand<6500*rate/100)
	{
		item = new ("/item/sell/0042");
		item->set_amount(5);
	}
	else
	if (rand<7500*rate/100)
	{
		item = new ("/item/91/9178");
		item->set_amount(5);
	}	
	else
	if (rand<8500*rate/100)
	{
		item = new (sprintf("/item/93/%d", 9301+random(10)));
		item2 = new (sprintf("/item/93/%d", 9301+random(10)));
		item3 = new (sprintf("/item/93/%d", 9301+random(10)));
		item4 = new (sprintf("/item/93/%d", 9301+random(10)));
		item5 = new (sprintf("/item/93/%d", 9301+random(10)));
	}
	else
	if (rand<9500*rate/100)
	{
		item = new ("/item/sell/0033");		
		item2 = new ("/item/sell/0033");		
		item3 = new ("/item/sell/0033");		
	}
	else*/
	if (rand < 500 * rate / 100)
	{
		//	item = new ("/item/TuiLinhThach/NgauNhien/4");
		item2 = new ("/item/44/4489");
		item3 = new (BOOK_FILE->get_book_file_2());
		item4 = new ("/item/08/0854");
		item5 = new (BOOK_FILE->get_book_file_2());
		//	item6 = new ("/item/TuiLinhThach/NgauNhien/4");
		item7 = new (BOOK_FILE->get_book_file_2());
		item8 = new (BOOK_FILE->get_book_file_2());
		item9 = new (BOOK_FILE->get_book_file_2());
		item10 = new ("/item/08/0853");
	}

	// if (item && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
	// {
	// 	TEAM_D->drop_item(item,who);
	// 	item->set_user_id(owner);
	// 	item->add_to_scene(z, p / 1000, p % 1000);
	// 	item->set("winner", who);
	// 	item->set( "time", time() );
	// }
	if (item2 && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	{
		TEAM_D->drop_item(item2, who);
		item2->set_user_id(owner);
		item2->add_to_scene(z, p / 1000, p % 1000);
		item2->set("winner", who);
		item2->set("time", time());
	}
	if (item3 && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	{
		TEAM_D->drop_item(item3, who);
		item3->set_user_id(owner);
		item3->add_to_scene(z, p / 1000, p % 1000);
		item3->set("winner", who);
		item3->set("time", time());
	}
	if (item4 && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	{
		TEAM_D->drop_item(item4, who);
		item4->set_user_id(owner);
		item4->add_to_scene(z, p / 1000, p % 1000);
		item4->set("winner", who);
		item4->set("time", time());
	}
	if (item5 && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	{
		TEAM_D->drop_item(item5, who);
		item5->set_user_id(owner);
		item5->add_to_scene(z, p / 1000, p % 1000);
		item5->set("winner", who);
		item5->set("time", time());
	}
	// if (item6 && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	// {
	// 	TEAM_D->drop_item(item6, who);
	// 	item6->set_user_id(owner);
	// 	item6->add_to_scene(z, p / 1000, p % 1000);
	// 	item6->set("winner", who);
	// 	item6->set("time", time());
	// }
	if (item7 && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	{
		TEAM_D->drop_item(item7, who);
		item7->set_user_id(owner);
		item7->add_to_scene(z, p / 1000, p % 1000);
		item7->set("winner", who);
		item7->set("time", time());
	}
	if (item8 && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	{
		TEAM_D->drop_item(item8, who);
		item8->set_user_id(owner);
		item8->add_to_scene(z, p / 1000, p % 1000);
		item8->set("winner", who);
		item8->set("time", time());
	}
	if (item9 && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	{
		TEAM_D->drop_item(item9, who);
		item9->set_user_id(owner);
		item9->add_to_scene(z, p / 1000, p % 1000);
		item9->set("winner", who);
		item9->set("time", time());
	}
	if (item10 && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
	{
		TEAM_D->drop_item(item10, who);
		item10->set_user_id(owner);
		item10->add_to_scene(z, p / 1000, p % 1000);
		item10->set("winner", who);
		item10->set("time", time());
	}
}

void heart_beat_walk()
{
	object map, who, *see, *char, me, orgnpc;
	string cmd, name;
	int z, x, y, x1, y1, dx, p, p2;
	int walk, seek, flag, *dir, i, size;
	me = this_object();

	if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
		return;

	if (!me->get_action())
		return;

	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	// 判断是否进入跳转点5
	if (inside_jumpin(z, x, y, 5))
	{
		map = get_map_object(z);
		if (map)
		{
			char = map->get_player_dbase();
			map->set_damage(map->get_damage() + 1);
			if (sizeof(char))
			{
				if (map->get_damage() <= 100)
					send_user(char, "%c%c%d%s", 0x43, 6, 0, sprintf(CHAT + HIY + "Yêu ma đang xâm nhập thành, bản thành trước mắt tổn hại : %d/100.", map->get_damage()));
			}
			send_user(get_scene_object_2(me, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(me), get_y(me), 32411, 1, OVER_BODY, PF_ONCE);
			me->remove_from_scene();
			destruct(me);
			return;
		}
	}
	if (who = me->get_main_enemy()) // 搜索何人攻击(最重要的敌人)
		me->set_enemy(who);
	else
	{
		if (!me->get_enemy())
		{
			seek = me->get_max_seek();
			see = get_range_object(z, x, y, seek, USER_TYPE) + get_range_object(z, x, y, seek, CHAR_TYPE);
			char = filter_array(see, (
										 : $1->is_war_npc() == 0
										 :),
								me);
			see = filter_array(char, (
										 : $1->can_fight($2)
										 :),
							   me); //
			if (objectp(who = get_near_char(see, z, x, y)))
				me->auto_fight(who);
		}
	}

	if (gone_time(me->get_attack_time()) > 10)
		me->init_enemy_damage(0, 0); // 清除伤害状态

	z = get_z(me);
	x = get_x(me);
	y = get_y(me);

	if (objectp(who = me->get_enemy()))
	{
		if (who->is_die())
		{
			me->set_enemy(0);
			flag = 1;
		}
		else
			me->follow_user();
	}
	else
		flag = 1;

	if (flag && objectp(map = get_map_object(z))) // 跟随指定路线
	{
		p = 0;
		p2 = get_jumpin(z, 5);
		p = get_valid_path(z, x, y, p2 / 1000, p2 % 1000);
		if (p) // 找到可走路径
		{
			cmd = sprintf("%d", p);

			switch (me->get_walk_step())
			{
			default:
				if (strlen(cmd) > 1)
					cmd = cmd[0..0];
				break;
			case 2:
				if (strlen(cmd) > 2)
					cmd = cmd[0..1];
				break;
			}
			GO_CMD->main_npc(me, cmd);
		}
		else if (sizeof_range_object(z, x, y, 1, CHAR_TYPE) + sizeof_range_object(z, x, y, 1, USER_TYPE) < 9) // 随机乱走
		{
			dir = ({});
			if (!(get_block(z, x + 1, y) & IS_CHAR_BLOCK))
				dir += ({111});
			if (!(get_block(z, x + 1, y - 1) & IS_CHAR_BLOCK))
				dir += ({222});
			if (!(get_block(z, x, y - 1) & IS_CHAR_BLOCK))
				dir += ({333});
			if (!(get_block(z, x - 1, y - 1) & IS_CHAR_BLOCK))
				dir += ({444});
			if (!(get_block(z, x - 1, y) & IS_CHAR_BLOCK))
				dir += ({555});
			if (!(get_block(z, x - 1, y + 1) & IS_CHAR_BLOCK))
				dir += ({666});
			if (!(get_block(z, x, y + 1) & IS_CHAR_BLOCK))
				dir += ({777});
			if (!(get_block(z, x + 1, y + 1) & IS_CHAR_BLOCK))
				dir += ({888});

			if ((size = sizeof(dir)) && (p = dir[random(size)])) // 找到可走路径
			{
				cmd = sprintf("%d", p);

				switch (me->get_walk_step())
				{
				default:
					if (strlen(cmd) > 1)
						cmd = cmd[0..0];
					break;
				case 2:
					if (strlen(cmd) > 2)
						cmd = cmd[0..1];
					break;
				}
				GO_CMD->main_npc(me, cmd);
			}
		}
	}

	x = abs(x - get_x(me));
	y = abs(y - get_y(me));
	walk = (x > y) ? x : y;

	if (walk > 0)
	{
		set_heart_state(me, 0);
		set_heart_count_2(me, 3 * walk + 1); // walk * 10 / 4
	}
}
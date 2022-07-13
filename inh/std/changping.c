
#include <ansi.h>
#include <map.h>
#include <skill.h>
#include <action.h>
#include <equip.h>
#include <cmd.h>

inherit "/inh/std/virtual";

private
static object Owner;
void destruct_virtual_map(object map, int id);

// -------------------------------------------------------------
int is_changping() { return 1; }
// 函数：获取地型类别
int get_map_type() { return BATTLE_MAP; }

// 函数：构造处理
void create()
{
	object me = this_object();

	set_client_id(903);
	//    set_name("Chiến Trường");
	set_name("Trường Bình Chi Chiến");

	if (!clonep(me))
		return;

	set_heart_timer(me, set_heart_timer_2(me, getoid(me) % 10)); // 心跳随机
	set_heart_loop(me, 600);									 // 循环心跳：１分钟
	me->heart_beat();
	set_heart_beat(1);
}

// -------------------------------------------------------------

// 函数：获取用户标识
object get_owner() { return Owner; }

// 函数：设置用户标识
object set_owner(object who) { return Owner = who; }

// -------------------------------------------------------------

// 函数：心跳处理
void heart_beat() {}

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object map, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１分处理
{
	object qin, zhao;
	if (map->get("finish")) // 战斗结束
	{
		if (map->get("finish") == 2)
			destruct_virtual_map(map, map->get_id());
		return;
	}
	qin = map->get("qin1");
	zhao = map->get("zhao1");
	if (!qin || !zhao) //不存在，结束
		"npc/88/8800"->game_over(map, qin ? "Tần Quốc" : "Triệu Quốc");
}

// -------------------------------------------------------------

// 函数：清除所有物体
void cleanup_char_and_item(object map)
{
	object *item, who, npc;
	int z, x, y, p, max_x, max_y;
	int i, size;

	reset_eval_cost();

	z = map->get_id();
	max_x = get_map_max_x(z);
	max_y = get_map_max_y(z);

	for (x = 0; x < max_x; x += AREA_SIZE)
		for (y = 0; y < max_y; y += AREA_SIZE)
		{
			if (have_scene_object(z, x, y, ITEM_TYPE, 1))
			{
				item = get_scene_object(z, x, y, ITEM_TYPE, 1);

				for (i = 0, size = sizeof(item); i < size; i++)
					if (who = item[i])
					{
						who->remove_from_scene();
						destruct(who);
					}
			}
			if (have_scene_object(z, x, y, CHAR_TYPE, 1))
			{
				item = get_scene_object(z, x, y, CHAR_TYPE, 1);

				for (i = 0, size = sizeof(item); i < size; i++)
					if (who = item[i])
					{
						who->remove_from_scene();
						destruct(who);
					}
			}
			if (have_scene_object(z, x, y, USER_TYPE, 1))
			{
				item = get_scene_object(z, x, y, USER_TYPE, 1);

				for (i = 0, size = sizeof(item); i < size; i++)
					if (who = item[i])
						MAP_D->add_to_void(who); // 移入 VOID 场景
			}
		}
}

// 函数：删除虚拟场景
void destruct_virtual_map(object map, int id)
{
	if (!map->is_virtual_scene())
		return;
	cleanup_char_and_item(map);
	free_virtual_map(id);
	destruct(map);
}

// 函数：取地图内的所有玩家
object *get_all_user()
{
	object *item, who, *npc = ({}), *all = ({});
	int z, x, y, p, max_x, max_y;
	int i, size;

	reset_eval_cost();

	z = get_id();
	max_x = get_map_max_x(z);
	max_y = get_map_max_y(z);

	for (x = 0; x < max_x; x += AREA_SIZE)
		for (y = 0; y < max_y; y += AREA_SIZE)
		{
			if (have_scene_object(z, x, y, USER_TYPE, 1))
			{
				item = get_scene_object(z, x, y, USER_TYPE, 1);

				for (i = 0, size = sizeof(item); i < size; i++)
					if (who = item[i])
					{
						all += ({item[i]});
					}
			}
		}
	for (i = 0; i < sizeof(all); i++)
	{
		if (all[i] && all[i]->is_user())
			npc += ({all[i]});
	}
	return npc;
}

void kick_out_user(int count)
{
	object *item, who, npc;
	int z, x, y, p, max_x, max_y;
	int i, size;
	object map = this_object(), *nPlayer;

	remove_call_out("kick_out_user");
	if (!map)
		return;
	//        count--;
	//        if ( count > 0 )
	//        {
	//		call_out("kick_out_user",1,count);
	//		nPlayer = map->get_all_user();
	//		if ( nPlayer )
	//		{
	//			if ( map->get("win") == "Tần Quốc" )
	//				send_user( nPlayer, "%c%c%d%s", 0x43, 10, 0, sprintf(HIR"赵军主将廉颇已经被秦军击败！长平之战以秦军胜利结束，%d秒后大家将会返回周国。",count));
	//			else if ( map->get("win") == "Triệu Quốc" )
	//				send_user( nPlayer, "%c%c%d%s", 0x43, 10, 0, sprintf(HIR"秦军主将白起已经被赵军击败！长平之战以赵军胜利结束，%d秒后大家将会返回周国。",count));
	//		}
	//		return ;
	//	}
	map->set("finish", 2);
	reset_eval_cost();

	z = map->get_id();
	max_x = get_map_max_x(z);
	max_y = get_map_max_y(z);

	for (x = 0; x < max_x; x += AREA_SIZE)
		for (y = 0; y < max_y; y += AREA_SIZE)
		{
			if (have_scene_object(z, x, y, USER_TYPE, 1))
			{
				item = get_scene_object(z, x, y, USER_TYPE, 1);

				for (i = 0, size = sizeof(item); i < size; i++)
					if ((who = item[i]) && who->is_user())
					{
						who->delete_2("changping");
						//	who->set_save("nhandoict", 0);
						if (p = get_valid_xy(80, 243, 156, IS_CHAR_BLOCK))
						{
							CHAR_CHAR_D->init_loop_perform(who);
							who->add_to_scene(80, p / 1000, p % 1000);
						}
						else
						{
							CHAR_CHAR_D->init_loop_perform(who);
							MAP_D->add_to_void(who);
						}
					}
			}
		}
}

void game_over()
{
	object map = this_object();

	remove_call_out("kick_out_user");
	//	call_out("kick_out_user",1,10);
	call_out("kick_out_user", 60, 0);
}
//检查玩家是否进入战场
void check_fighter(int i)
{
	int wId, level, z, size;
	int *nFighter, *nFighter1, *nFighter2;
	object player;

	if (i)
	{
		call_out("check_fighter", i, 0);
		return;
	}
	//检查，不在场内的玩家做放弃处理
	wId = get("warid");
	level = get("warlevel");
	z = get_id();
	nFighter = "npc/88/8800"->get_2(sprintf("%d.%d.Tần Quốc", level, wId));
	nFighter += "npc/88/8800"->get_2(sprintf("%d.%d.Triệu Quốc", level, wId));
	for (i = 0, size = sizeof(nFighter); i < size; i++)
	{
		player = find_char(sprintf("%d", nFighter[i]));
		if (!objectp(player))
			continue;
		if (player->get_2("changping.start") == 0)
			continue;
		if (get_z(player) == z)
			continue;
		"npc/88/8800"->delete_sign_up(player);
	}
}

//比较大小
int sort_cmp(int id1, int id2)
{
	mapping mpTmp, mpTmp1, mpTmp2;

	mpTmp = get_2("player_info");
	if (!mapp(mpTmp))
		return 0;
	mpTmp1 = mpTmp[id1];
	mpTmp2 = mpTmp[id2];
	if (!mapp(mpTmp1) || !mapp(mpTmp1))
		return 0;
	if (mpTmp1["kill"] == mpTmp2["kill"])
		return mpTmp1["die"] - mpTmp2["die"];
	else
		return mpTmp2["kill"] - mpTmp1["kill"];
}
//测试使用
void test_it(int n)
{
	int *nTmp = ({}), i, j;
	mapping mpTmp = ([]);
	for (i = 0; i < 10; i++)
	{
		j = random100();
		if (i == 5 || i == 7)
			j = 10;
		mpTmp[i] = (["kill":j,
					  "die":random100(),
		]);
		nTmp += ({i});
	}
	set_2("player_info", mpTmp);
	nTmp = sort_array(nTmp, "sort_cmp", this_object());
	for (i = 0; i < 10; i++)
	{
		j = nTmp[i];
		tell_user(find_char(sprintf("%d", n)), "%d %d %d", j, mpTmp[j]["kill"], mpTmp[j]["die"]);
	}
}
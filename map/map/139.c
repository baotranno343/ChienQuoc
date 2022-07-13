
// 自动生成：/make/std/makemap

#include <map.h>
#include <time.h>
#include <chia_kenh.h>
inherit SCENE;
object wuzhang, liren, liwu;
object dajiangjun;
int djjTime, djjStart;
void clone_npc();

// 函数：获取标识
int get_id() { return 139; }

// 函数：获取标识(客户端)
int get_client_id() { return 139; }

// 函数：获取名字
string get_name() { return "Mục Trường"; }

// 函数：复位顺序
int get_reset_order() { return 107; }

// 函数：获取地型类别
int get_map_type() { return FIELD_MAP; }

// 函数：获取投掷类数
int get_caster_amount() { return 0; }

// 函数：构造处理
void create()
{
	object map = this_object();
	mixed *mxTmp;

	set_map_object(map, get_id());
	MAP_D->load_npc_file(map, "/map/npc/139.npc");

	set_fighter_file(({}));
	set_boss_file(({}));

	set_sizeof_xy(sizeof_xy_point(get_id()));

	set_heart_timer(map, set_heart_timer_2(map, (time() % RESET_TIME) * 10));
	set_heart_loop(map, 60); // 循环心跳：１分钟
	map->heart_beat();
	set_heart_beat(1);

	mxTmp = localtime(time());
	djjStart = mktime(mxTmp[TIME_YEAR], mxTmp[TIME_MON] + 1, mxTmp[TIME_MDAY], 20, 30, 0);
	call_out("reset", 1); // 地图复位
}

// 函数：心跳处理
void heart_beat() {}

// 函数：心跳处理(循环)
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１分处理
{
	call_out("reset", 1); // 地图复位
}

// 函数：复位处理
void reset()
{
	object map = this_object();
	int time = add_reset_time(1);
	int p, x, y, z;

	remove_call_out("reset");

	if (time % 100 == 0) // 10 分钟
	{
		MAP_D->reset_npc(get_id()); // 复位NPC 对象
		set_heart_timer(map, set_heart_timer_2(map, (time() % RESET_TIME) * 10));
	}
	if (time % 200 == 0) // 20 分钟
	{
		MAP_D->clone_boss(this_object()); // 载入小BOSS
	}
	if (time % get_clean_time() == 0) // 复位时间
	{
		call_out("reset_call_out", get_reset_order() % 6); // 载入小怪物
	}
	if (time % 30 == 0) //3分钟
	{
		if (!objectp(wuzhang))
		{
			wuzhang = new ("npc/task/0131");
			wuzhang->add_to_scene(139, 153, 68, 2);
		}
		else if (get_x(wuzhang) != 153 || get_y(wuzhang) != 68)
			wuzhang->add_to_scene(139, 153, 68, 2);
		if (!objectp(liren))
		{
			liren = new ("npc/task/0171");
			liren->add_to_scene(139, 135, 84, 2);
		}
		else if (get_x(liren) != 135 || get_y(liren) != 84)
			liren->add_to_scene(139, 135, 84, 2);
		if (!objectp(liwu))
		{
			liwu = new ("npc/task/0173");
			liwu->add_to_scene(139, 58, 85, 2);
		}
		else if (get_x(liwu) != 58 || get_y(liwu) != 85)
			liwu->add_to_scene(139, 58, 85, 2);
	}
	if (MAIN_D->get_kenh() != KENH_EVENT)
	{
		return;
	}
	//Uy Võ Đại Tướng Quân
	// if (time % 10 == 0 && MAIN_D->get_host_type() != 6012) //1分钟
	// {
	// 	if (djjTime == 0)
	// 	{
	// 		if (time() > djjStart) //第一次出现的时间
	// 		{
	// 			x = 132 + random(100) - 50;
	// 			y = 81 + random(100) - 50;
	// 			if (p = get_valid_xy(139, x, y, IS_CHAR_BLOCK))
	// 			{
	// 				x = (p % 1000000) / 1000;
	// 				y = p % 1000;
	// 				dajiangjun = new ("npc/boss/0003");
	// 				if (dajiangjun)
	// 				{
	// 					map->add_boss(dajiangjun);
	// 					dajiangjun->add_to_scene(139, x, y);
	// 					djjTime = -1;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (!objectp(dajiangjun) && djjTime == -1)
	// 		{
	// 			djjTime = time();
	// 		}
	// 		if (djjTime != -1 && (gone_time(djjTime) >= 3600 * 48))
	// 		{
	// 			x = 132 + random(100) - 50;
	// 			y = 81 + random(100) - 50;
	// 			if (p = get_valid_xy(139, x, y, IS_CHAR_BLOCK))
	// 			{
	// 				x = (p % 1000000) / 1000;
	// 				y = p % 1000;
	// 				dajiangjun = new ("npc/boss/0003");
	// 				if (dajiangjun)
	// 				{
	// 					map->add_boss(dajiangjun);
	// 					dajiangjun->add_to_scene(139, x, y);
	// 					djjTime = -1;
	// 				}
	// 			}
	// 		}
	// 	}
	// }
}

// 函数：复位处理
void reset_call_out()
{
	remove_call_out("reset_call_out");

	MAP_D->reset_item(get_id());

	if (sizeof_fighter_file() > 0)
	{
		set_add_amount(-1);
		clone_npc();
	}
}

// 函数：载入怪物
void clone_npc()
{
	remove_call_out("clone_npc");

	MAP_D->clone_npc(this_object());

	if (get_add_amount())
		call_out("clone_npc", 2);
}

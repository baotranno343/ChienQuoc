
// 自动生成：/make/std/makemap

#include <map.h>
#include <time.h>
#include <chia_kenh.h>
inherit SCENE;
object Big_boss;
int bigbossTime, bigbossStart;

void clone_npc();

// 函数：获取标识
int get_id() { return 335; }

// 函数：获取标识(客户端)
int get_client_id() { return 335; }

// 函数：获取名字
string get_name() { return "Hầm Vạn Nhân 5"; }

// 函数：复位顺序
int get_reset_order() { return 76; }

// 函数：获取地型类别
int get_map_type() { return CAVE_MAP; }

// 函数：获取投掷类数
int get_caster_amount() { return 0; }

// 函数：构造处理
void create()
{
	object map = this_object();
	mixed *mxTmp;

	set_map_object(map, get_id());
	MAP_D->load_npc_file(map, "/map/npc/335.npc");

	set_fighter_file(({
		"/npc/npc/0830",
		"/npc/npc/0831",
		"/npc/npc/0832",
		"/npc/npc/0840",
	}));
	set_boss_file(({
		"/npc/npc/0900",
		"/npc/npc/0913",
		"/npc/npc/0931",
	}));

	set_sizeof_xy(sizeof_xy_point(get_id()));

	set_heart_timer(map, set_heart_timer_2(map, (time() % RESET_TIME) * 10));
	set_heart_loop(map, 60); // 循环心跳：１分钟
	map->heart_beat();
	set_heart_beat(1);

	mxTmp = localtime(time());
	bigbossStart = mktime(mxTmp[TIME_YEAR], mxTmp[TIME_MON] + 1, mxTmp[TIME_MDAY], 20, 30, 0);
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
	if (MAIN_D->get_kenh() != KENH_EVENT)
	{
		return;
	}
	//Âm Gian Bạn Đồ
	// if (time % 10 == 0 && MAIN_D->get_host_type() != 6012) //1分钟
	// {
	// 	if (bigbossTime == 0)
	// 	{
	// 		if (time() > bigbossStart) //第一次出现的时间
	// 		{
	// 			if (p = efun::get_xy_point(335, IS_CHAR_BLOCK))
	// 			{
	// 				x = (p % 1000000) / 1000;
	// 				y = p % 1000;
	// 				Big_boss = new ("npc/boss/0016");
	// 				if (Big_boss)
	// 				{
	// 					map->add_boss(Big_boss);
	// 					Big_boss->add_to_scene(335, x, y);
	// 					bigbossTime = -1;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (!objectp(Big_boss) && bigbossTime == -1)
	// 		{
	// 			bigbossTime = time();
	// 		}
	// 		if (bigbossTime != -1 && (gone_time(bigbossTime) >= 3600 * 48))
	// 		{
	// 			if (p = efun::get_xy_point(335, IS_CHAR_BLOCK))
	// 			{
	// 				x = (p % 1000000) / 1000;
	// 				y = p % 1000;
	// 				Big_boss = new ("npc/boss/0016");
	// 				if (Big_boss)
	// 				{
	// 					map->add_boss(Big_boss);
	// 					Big_boss->add_to_scene(335, x, y);
	// 					bigbossTime = -1;
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

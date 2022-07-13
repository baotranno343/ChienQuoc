/********************************************************************************************************************************
		    -----------------------Bảo Hộp Phi Tặc --------------------

********************************************************************************************************************************/

#include <time.h>
#include <ansi.h>
#include <cmd.h>
#include <chia_kenh.h>
#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

#define BaoHop "npc/event/baohop"

void generate_scum();
void destroy_scum();
string *schoolname = ({
	"Đào Hoa Nguyên",
	"Thục Sơn",
	"Cấm Vệ Quân",
	"Đường Môn",
	"Mao Sơn",
	"Côn Luân",
	"Vân Mộng Cốc",
});
object *Scum;
mapping mpNianshou;

// 函数：生成二进制码
void SAVE_BINARY() {}

void create()
{
	if (MAIN_D->get_kenh() != KENH_EVENT)
	{
		return;
	}
	//	restore();
	Scum = ({});
	call_out("check_time", 1);
}

void check_time()
{
	int iTime, rate, level, z, p, x, y;
	int i, *nScene, size;
	mixed *mixTime;
	object robber;

	remove_call_out("check_time");
	iTime = time();
	mixTime = localtime(iTime);
	// Thứ 3, t5, t7 có bh

	i = 60 * (60 - mixTime[TIME_MIN]);
	if (mixTime[TIME_HOUR] % 2 == 1) // giờ lẻ
	{
		call_out("check_time", i);
	}
	else
	{
		// 10h , 12h, 20h, 22h
		if (mixTime[TIME_HOUR] == 0 || mixTime[TIME_HOUR] == 2 || mixTime[TIME_HOUR] == 4 || mixTime[TIME_HOUR] == 6 || mixTime[TIME_HOUR] == 8 //
			|| (mixTime[TIME_HOUR] == 10 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 12 && mixTime[TIME_MIN] > 30)						//
			|| mixTime[TIME_HOUR] == 14 || mixTime[TIME_HOUR] == 16																				//
			|| (mixTime[TIME_HOUR] == 18 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 20 && mixTime[TIME_MIN] > 30)						//
			|| (mixTime[TIME_HOUR] == 22))
			call_out("check_time", i + 3600);
		else
		{
			"cmd/base/time"->set_baohop(1);
			generate_scum();

			call_out("check_time", i + 3600);
			call_out("check_time2", 1800 - (60 * mixTime[TIME_MIN]));
			log_file("party_event.dat", sprintf("%d ：%d: Bảo HỘp mở ra\n", mixTime[TIME_HOUR], mixTime[TIME_MIN]));
		}
	}
}
//  放入武林败类NPC
void generate_scum()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(010, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(010, 155 + random(20), 75 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(010, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(010, 155 + random(20), 75 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(010, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(010, 155 + random(20), 75 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(010, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(010, 155 + random(20), 75 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(020, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(020, 89 + random(10), 146 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(020, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(020, 89 + random(10), 146 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(020, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(020, 89 + random(10), 146 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(020, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(020, 89 + random(10), 146 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(030, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(030, 318 + random(7), 125 + random(15));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(030, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(030, 318 + random(7), 125 + random(15));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(030, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(030, 305 + random(10), 155 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(030, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(030, 305 + random(10), 155 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(040, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(040, 177 + random(10), 60 - random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(040, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(040, 182 + random(8), 43 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(040, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(040, 212 + random(5), 70 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(040, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(040, 212 + random(6), 70 + random(5));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(050, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(050, 173 + random(20), 61 + random(10));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(050, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(050, 173 + random(20), 61 + random(10));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(050, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(050, 173 + random(20), 61 + random(10));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(050, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(050, 173 + random(20), 61 + random(10));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(060, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(060, 81 + random(10), 184 + random(3));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(060, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(060, 81 + random(10), 184 + random(3));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(060, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(060, 81 + random(10), 184 + random(3));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(060, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(060, 81 + random(10), 184 + random(3));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(070, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(070, 322 + random(10), 131 + random(15));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(070, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(070, 322 + random(10), 131 + random(15));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(070, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(070, 293 + random(10), 150 + random(20));
		Scum += ({npc});
	}
	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(070, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(070, 293 + random(10), 150 + random(20));
		Scum += ({npc});
	}
	for (i = 0; i < 4; i++)
	{
		if (!(p = efun::get_xy_point(080, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (BaoHop);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 2);
		npc->add_ap(npc->get_ap() * 2 / 5);
		npc->add_pp(npc->get_pp() / 2);
		npc->add_to_scene(080, 101 - random(20), 132 + random(10));
		Scum += ({npc});
	}

	// Xuất hiện 1 tiếng -> 55 phút sau sẽ biến mất => 3600 + 3300 <<== 55'

	CHAT_D->sys_channel(0, "Theo mật thám Chu Vương hồi báo: ở Doanh Trại 7 nước và Phong Thần Đài nước Chu  xuất hiện lũ Phi Tặc chuyên làm việc ác, cần phải tiêu diệt để trừ hại cho Bá Tánh. Nhiệm vụ bảo vệ thế giới và hòa binhNhiệm vụ.... ¥#%...¥,t");
	CHAT_D->sys_channel(0, "Theo mật thám Chu Vương hồi báo: ở Doanh Trại 7 nước và Phong Thần Đài nước Chu xuất hiện lũ Phi Tặc chuyên làm việc ác, cần phải tiêu diệt để trừ hại cho Bá Tánh. Nhiệm vụ bảo vệ thế giới và hòa binhNhiệm vụ.... ¥#%...¥,t");
	"cmd/func/allfunc"->thongbao_event(HIR "Kênh Event:" NOR "Theo mật thám Chu Vương hồi báo: ở Doanh Trại 7 nước và Phong Thần Đài nước Chu xuất hiện lũ Phi Tặc chuyên làm việc ác, cần phải tiêu diệt để trừ hại cho Bá Tánh. Nhiệm vụ bảo vệ thế giới và hòa binhNhiệm vụ.... ¥#%...¥,t");
}
//Sau 55 phút từ khi Bảo Hộp Phi Tặc xuất hiện, Bảo Hộp Phi Tặc sẽ tự động biến mất
void check_time2()
{
	int i, size;

	for (i = 0, size = sizeof(Scum); i < size; i++)
	{
		if (!objectp(Scum[i]))
			continue;

		Scum[i]->remove_from_scene();
		destruct(Scum[i]);
	}
	"cmd/base/time"->set_baohop(0);
	Scum -= ({0});
}

// 函数：掉宝奖励
void drop_items(object me, object who)
{
	int x, y, z, p, i, rate, rate1, level, level2;
	string *nTmp, id, owner, file;
	object item, leader;

	level = me->get_level();
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = who->get_leader();
	if (!id)
	{
		owner = who->get_id();
	}
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
		{
			owner = who->get_id();
		}
	}
	for (i = 0; i < 2 + random(3); i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/std/0001");
			item->set_value(1000 + random(2000));
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	for (i = 0; i < random(3) + 2; i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/01/0200");
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	for (i = 0; i < random(3) + 2; i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/01/0201");
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}

	p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
	if (!p)
	{
		return;
	}
	rate1 = me->correct_drop_rate(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
	if (rate1 < 40)
	{
		return;
	}
	rate = random(10000);
	item = 0;
	if (rate < 2500)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			//	item = new (STONE_FILE->get_diamond_file());
			item = new ("item/test2/TuiLinhThach");
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	else if (rate < 5000)
	{
		for (i = 0; i < 1 + random(2); i++)
		{
			item = new ("/item/01/0202");
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	return;
	//	if(!item) {
	//		return 0;
	//	}
}
void win_bonus_callout(object me, object who)
{
	object owner, *team;
	int level, level2, exp, exp2, pot, alllevel;
	int i, size, status, time, flag;

	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;
	if (who->get_group_id())
		return;

	CHAT_D->sys_channel(0, "Nghe nói Bảo Hộp Phi Tặc đã bị bằng hữu " + who->get_name() + " tiêu diệt");
	if (who->get_online_rate())
	{
		drop_items(me, who);
	}

	level = me->get_level();
	if (who->get_leader() && arrayp(team = who->get_team()) && sizeof(team) > 1)
	{
		team = me->correct_bonus_team(team);
		size = sizeof(team);
	}
	else
	{
		team = ({who});
		size = 1;
	}

	alllevel = 0;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			alllevel += team[i]->get_level();
		}
	if (alllevel == 0)
		alllevel = 1;
	exp = level * 100;
	pot = level * 5;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			level2 = level - team[i]->get_level();
			exp2 = exp * team[i]->get_level() / alllevel;
			exp2 = me->correct_exp_bonus(level, level2, exp2) * who->get_online_rate() / 100;

			if (exp2 < 5)
				exp2 = 5;
			exp2 = exp2 * team[i]->get_online_rate() / 100;
			pot = pot * team[i]->get_online_rate() / 100;
			team[i]->add_exp(exp2);
			team[i]->add_potential(pot);
			//	"sys/sys/test_db"->add_yuanbao(team[i],level/(4*size));
			//	write_user(team[i], sprintf(ECHO "Bạn tiêu diệt Phi Tặc cấp %d và nhận được %d Ngân Bảo !",level ));
		}
}
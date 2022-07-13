/********************************************************************************************************************************
		    -----------------------Chiến Quốc Tống Bảo Tiểu Yêu --------------------
10 : 061,062,063,281,282,283,284
15 : 081,082,251
20 : 041,042,043,021,141,142,211
25 : 089,181,131,271,272,241,242,132,182,243,155,231
30 : 163,164,261,262,263,264
35 : 265,266,111,112
40 : 011,012,013,014,015
45 : 151,152,153
50 : 171,172,173,174
55 : 071,072,073
60 : 031,032,033
********************************************************************************************************************************/

#include <ansi.h>
#include <time.h>
#include <cmd.h>
#include <chia_kenh.h>
#include <npc.h>
#include <city.h>
#include <action.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

#define TongBaoYeu "npc/event/tongbaoyeu"
// cấp 10
void mot();
void hai();
void ba();
void bon();
void nam();
void sau();
void bay();
// cấp 15
void mot_15();
void hai_15();
void ba_15();
// cấp 20
void mot_20();
void hai_20();
void ba_20();
void bon_20();
void nam_20();
void sau_20();
void bay_20();
// cấp 25
void mot_25();
void hai_25();
void ba_25();
void bon_25();
void nam_25();
void sau_25();
void bay_25();
void tam_25();
void chin_25();
void muoi_25();
void muoimot_25();
void muoihai_25();
// cấp 30
void mot_30();
void hai_30();
void ba_30();
void bon_30();
void nam_30();
void sau_30();
// cấp 35
void mot_35();
void hai_35();
void ba_35();
void bon_35();
// cấp 40
void mot_40();
void hai_40();
void ba_40();
void bon_40();
void nam_40();
// cấp 45
void mot_45();
void hai_45();
void ba_45();
// cấp 50
void mot_50();
void hai_50();
void ba_50();
void bon_50();
// cấp 55
void mot_55();
void hai_55();
void ba_55();
// cấp 60
void mot_60();
void hai_60();
void ba_60();

// 函数：生成二进制码
void SAVE_BINARY() {}

void create()
{
	if (MAIN_D->get_kenh() != KENH_EVENT)
	{
		return;
	}
	call_out("check_time", 30);
}

void check_time()
{
	int iHour;
	mixed *mixTime;

	remove_call_out("check_time");
	if (MAIN_D->get_host_type() == 2) //台湾除外
		return;
	// cấp 10
	mot();
	hai();
	ba();
	bon();
	nam();
	sau();
	bay();
	// cấp 15
	mot_15();
	hai_15();
	ba_15();
	// cấp 20
	mot_20();
	hai_20();
	ba_20();
	bon_20();
	nam_20();
	sau_20();
	bay_20();
	// cấp 25
	mot_25();
	hai_25();
	ba_25();
	bon_25();
	nam_25();
	sau_25();
	bay_25();
	tam_25();
	chin_25();
	muoi_25();
	muoimot_25();
	muoihai_25();
	// cấp 30
	mot_30();
	hai_30();
	ba_30();
	bon_30();
	nam_30();
	sau_30();
	// cấp 35
	mot_35();
	hai_35();
	ba_35();
	bon_35();
	// cấp 40
	mot_40();
	hai_40();
	ba_40();
	bon_40();
	nam_40();
	// cấp 45
	mot_45();
	hai_45();
	ba_45();
	// cấp 50
	mot_50();
	hai_50();
	ba_50();
	bon_50();
	// cấp 55
	mot_55();
	hai_55();
	ba_55();
	// cấp 60
	mot_60();
	hai_60();
	ba_60();
}
void check_mot()
{
	mot();
}
void mot()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(061, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(10);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 10);
		npc->add_max_hp(npc->get_max_hp() * 15);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(061, x, y);
	}
}
void check_hai()
{
	hai();
}
void hai()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(062, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(10);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 10);
		npc->add_max_hp(npc->get_max_hp() * 15);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(062, x, y);
	}
}
void check_ba()
{
	ba();
}
void ba()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(063, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(10);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 10);
		npc->add_max_hp(npc->get_max_hp() * 15);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(063, x, y);
	}
}
void check_bon()
{
	bon();
}
void bon()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(281, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(10);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 10);
		npc->add_max_hp(npc->get_max_hp() * 15);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(281, x, y);
	}
}
void check_nam()
{
	nam();
}
void nam()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(282, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(10);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 10);
		npc->add_max_hp(npc->get_max_hp() * 15);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(282, x, y);
	}
}
void check_sau()
{
	sau();
}
void sau()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(283, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(10);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 10);
		npc->add_max_hp(npc->get_max_hp() * 15);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(283, x, y);
	}
}
void check_bay()
{
	bay();
}
void bay()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(284, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(10);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 10);
		npc->add_max_hp(npc->get_max_hp() * 15);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(284, x, y);
	}
}
void check_mot_15()
{
	mot_15();
}
void mot_15()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(081, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(15);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 15);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(081, x, y);
	}
}
void check_hai_15()
{
	hai_15();
}
void hai_15()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(082, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(15);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 15);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(082, x, y);
	}
}
void check_ba_15()
{
	ba_15();
}
void ba_15()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(251, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(15);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 15);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(251, x, y);
	}
}
void check_mot_20()
{
	mot_20();
}
void mot_20()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(041, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(20);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 20);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(041, x, y);
	}
}
void check_hai_20()
{
	hai_20();
}
void hai_20()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(042, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(20);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 20);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(042, x, y);
	}
}
void check_ba_20()
{
	ba_20();
}
void ba_20()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(043, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(20);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 20);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(043, x, y);
	}
}
void check_bon_20()
{
	bon_20();
}
void bon_20()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(021, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(20);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 20);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(021, x, y);
	}
}
void check_nam_20()
{
	nam_20();
}
void nam_20()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(141, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(20);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 20);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(141, x, y);
	}
}
void check_sau_20()
{
	sau_20();
}
void sau_20()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(142, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(20);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 20);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(142, x, y);
	}
}
void check_bay_20()
{
	bay_20();
}
void bay_20()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(211, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(20);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 20);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(211, x, y);
	}
}
void check_mot_25()
{
	mot_25();
}
void mot_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(089, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(089, x, y);
	}
}
void check_hai_25()
{
	hai_25();
}
void hai_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(181, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(181, x, y);
	}
}
void check_ba_25()
{
	ba_25();
}
void ba_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(131, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(131, x, y);
	}
}
void check_bon_25()
{
	bon_25();
}
void bon_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(271, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(271, x, y);
	}
}
void check_nam_25()
{
	nam_25();
}
void nam_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(272, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(272, x, y);
	}
}
void check_sau_25()
{
	sau_25();
}
void sau_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(241, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(241, x, y);
	}
}
void check_bay_25()
{
	bay_25();
}
void bay_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(242, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(242, x, y);
	}
}
void check_tam_25()
{
	tam_25();
}
void tam_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(132, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(132, x, y);
	}
}
void check_chin_25()
{
	chin_25();
}
void chin_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(182, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(182, x, y);
	}
}
void check_muoi_25()
{
	muoi_25();
}
void muoi_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(243, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(243, x, y);
	}
}
void check_muoimot_25()
{
	muoimot_25();
}
void muoimot_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(155, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(155, x, y);
	}
}
void check_muoihai_25()
{
	muoihai_25();
}
void muoihai_25()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(231, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(25);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 25);
		npc->add_max_hp(npc->get_max_hp() * 20);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(231, x, y);
	}
}
void check_mot_30()
{
	mot_30();
}
void mot_30()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(163, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(30);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 30);
		npc->add_max_hp(npc->get_max_hp() * 25);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(163, x, y);
	}
}
void check_hai_30()
{
	hai_30();
}
void hai_30()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(164, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(30);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 30);
		npc->add_max_hp(npc->get_max_hp() * 25);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(164, x, y);
	}
}
void check_ba_30()
{
	ba_30();
}
void ba_30()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(261, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(30);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 30);
		npc->add_max_hp(npc->get_max_hp() * 25);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(261, x, y);
	}
}
void check_bon_30()
{
	bon_30();
}
void bon_30()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(262, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(30);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 30);
		npc->add_max_hp(npc->get_max_hp() * 25);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(262, x, y);
	}
}
void check_nam_30()
{
	nam_30();
}
void nam_30()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(263, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(30);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 30);
		npc->add_max_hp(npc->get_max_hp() * 25);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(263, x, y);
	}
}
void check_sau_30()
{
	sau_30();
}
void sau_30()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(264, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(30);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 30);
		npc->add_max_hp(npc->get_max_hp() * 25);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(264, x, y);
	}
}
void check_mot_35()
{
	mot_35();
}
void mot_35()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(265, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(35);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 35);
		npc->add_max_hp(npc->get_max_hp() * 30);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(265, x, y);
	}
}
void check_hai_35()
{
	hai_35();
}
void hai_35()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(266, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(35);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 35);
		npc->add_max_hp(npc->get_max_hp() * 30);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(266, x, y);
	}
}
void check_ba_35()
{
	ba_35();
}
void ba_35()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(111, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(35);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 35);
		npc->add_max_hp(npc->get_max_hp() * 30);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(111, x, y);
	}
}
void check_bon_35()
{
	bon_35();
}
void bon_35()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(112, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(35);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 35);
		npc->add_max_hp(npc->get_max_hp() * 30);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(112, x, y);
	}
}
void check_mot_40()
{
	mot_40();
}
void mot_40()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(011, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(40);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 40);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(011, x, y);
	}
}
void check_hai_40()
{
	hai_40();
}
void hai_40()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(012, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(40);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 40);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(012, x, y);
	}
}
void check_ba_40()
{
	ba_40();
}
void ba_40()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(013, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(40);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 40);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(013, x, y);
	}
}
void check_bon_40()
{
	bon_40();
}
void bon_40()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(014, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(40);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 40);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(014, x, y);
	}
}
void check_nam_40()
{
	nam_40();
}
void nam_40()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(015, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(40);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 40);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(015, x, y);
	}
}
void check_mot_45()
{
	mot_45();
}
void mot_45()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(151, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(45);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 45);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(151, x, y);
	}
}
void check_hai_45()
{
	hai_45();
}
void hai_45()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(152, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(45);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 45);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(152, x, y);
	}
}
void check_ba_45()
{
	ba_45();
}
void ba_45()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(153, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(45);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 45);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(153, x, y);
	}
}
void check_mot_50()
{
	mot_50();
}
void mot_50()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(171, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(50);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 50);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(171, x, y);
	}
}
void check_hai_50()
{
	hai_50();
}
void hai_50()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(172, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(50);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 50);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(172, x, y);
	}
}
void check_ba_50()
{
	ba_50();
}
void ba_50()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(173, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(50);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 50);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(173, x, y);
	}
}
void check_bon_50()
{
	bon_50();
}
void bon_50()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(174, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(50);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 50);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(174, x, y);
	}
}
void check_mot_55()
{
	mot_55();
}
void mot_55()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(071, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(55);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 55);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(071, x, y);
	}
}
void check_hai_55()
{
	hai_55();
}
void hai_55()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(072, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(55);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 55);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(072, x, y);
	}
}
void check_ba_55()
{
	ba_55();
}
void ba_55()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(073, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(55);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 55);
		npc->add_max_hp(npc->get_max_hp() * 40);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(073, x, y);
	}
}
void check_mot_60()
{
	mot_60();
}
void mot_60()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(031, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 50);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(031, x, y);
	}
}
void check_hai_60()
{
	hai_60();
}
void hai_60()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(032, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 50);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(032, x, y);
	}
}
void check_ba_60()
{
	ba_60();
}
void ba_60()
{
	int i, size, z, p, x, y, j;
	object npc;

	for (i = 0; i < 1; i++)
	{
		if (!(p = efun::get_xy_point(033, IS_CHAR_BLOCK)))
			continue;
		x = p / 1000;
		y = p % 1000;
		npc = new (TongBaoYeu);
		npc->set_level(60);
		npc->set_char_type(FIGHTER_TYPE_2);
		NPC_ENERGY_D->init_level(npc, 60);
		npc->add_max_hp(npc->get_max_hp() * 50);
		npc->add_dp(npc->get_dp() / 10);
		npc->add_ap(npc->get_ap() / 10);
		npc->add_pp(npc->get_pp() / 10);
		npc->add_to_scene(033, x, y);
	}
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
	for (i = 0; i < 5; i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/std/0001");
			item->set_value(level * 150);
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	/*    if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) {
                        item = new( "/item/04/0438" );
						item->set_amount(1+random(1));
						if ( !item )
							return;
                        TEAM_D->drop_item(item,who);
			item->set_user_id(owner);
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                } */

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
	if (rate < 3000)
	{
		item = new ("/item/91/9101"); // Hạt lạc hoàn
		item->set_amount(3);
	}
	else if (rate < 3500)
	{
		item = new (sprintf("/item/91/916%d", random(5))); // Vật phẩm gia tăng chỉ số trong 1 giờ
	}													   /*else if(rate < 5500 ) {	
        item = new( "/item/91/9167" ); // Tử Sâm Đơn
		item->set_amount(2); */
	else if (rate < 5500)
	{
		item = new ("/item/91/9102"); // Tạo hóa đơn
		item->set_amount(2);
	}
	else if (rate < 8300)
	{
		item = new ("/item/91/9120"); // Cấp cứu đan
		item->set_amount(3);
	}
	else if (rate < 9675)
	{
		item = new ("/item/91/9121"); // Hoạt tâm đan
		item->set_amount(3);
	}
	else if (rate < 10001)
	{
		item = new ("/item/91/9125"); // Tái tạo hoàn
		item->set_amount(2);
	}
	if (!item)
	{
		return 0;
	}
	TEAM_D->drop_item(item, who);
	item->set_user_id(owner);
	item->add_to_scene(z, p / 1000, p % 1000);
	item->set("winner", who);
	item->set("time", time());
}
void win_bonus_callout(object me, object who)
{
	object owner, *team;
	int level, level2, exp, exp3, exp2, pot, alllevel;
	int i, size, status, time, flag;

	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;
	if (who->get_group_id())
		return;

	if (get_z(me) == 061)
	{
		call_out("check_mot", 1800);
	}
	if (get_z(me) == 062)
	{
		call_out("check_hai", 1800);
	}
	if (get_z(me) == 063)
	{
		call_out("check_ba", 1800);
	}
	if (get_z(me) == 281)
	{
		call_out("check_bon", 1800);
	}
	if (get_z(me) == 282)
	{
		call_out("check_nam", 1800);
	}
	if (get_z(me) == 283)
	{
		call_out("check_sau", 1800);
	}
	if (get_z(me) == 284)
	{
		call_out("check_bay", 1800);
	}
	if (get_z(me) == 081)
	{
		call_out("check_mot_15", 1800);
	}
	if (get_z(me) == 082)
	{
		call_out("check_hai_15", 1800);
	}
	if (get_z(me) == 251)
	{
		call_out("check_ba_15", 1800);
	}
	if (get_z(me) == 041)
	{
		call_out("check_mot_20", 1800);
	}
	if (get_z(me) == 042)
	{
		call_out("check_hai_20", 1800);
	}
	if (get_z(me) == 043)
	{
		call_out("check_ba_20", 1800);
	}
	if (get_z(me) == 021)
	{
		call_out("check_bon_20", 1800);
	}
	if (get_z(me) == 141)
	{
		call_out("check_nam_20", 1800);
	}
	if (get_z(me) == 142)
	{
		call_out("check_sau_20", 1800);
	}
	if (get_z(me) == 211)
	{
		call_out("check_bay_20", 1800);
	}
	if (get_z(me) == 089)
	{
		call_out("check_mot_25", 1800);
	}
	if (get_z(me) == 181)
	{
		call_out("check_hai_25", 1800);
	}
	if (get_z(me) == 131)
	{
		call_out("check_ba_25", 1800);
	}
	if (get_z(me) == 271)
	{
		call_out("check_bon_25", 1800);
	}
	if (get_z(me) == 272)
	{
		call_out("check_nam_25", 1800);
	}
	if (get_z(me) == 241)
	{
		call_out("check_sau_25", 1800);
	}
	if (get_z(me) == 242)
	{
		call_out("check_bay_25", 1800);
	}
	if (get_z(me) == 132)
	{
		call_out("check_tam_25", 1800);
	}
	if (get_z(me) == 182)
	{
		call_out("check_chin_25", 1800);
	}
	if (get_z(me) == 243)
	{
		call_out("check_muoi_25", 1800);
	}
	if (get_z(me) == 155)
	{
		call_out("check_muoimot_25", 1800);
	}
	if (get_z(me) == 231)
	{
		call_out("check_muoihai_25", 1800);
	}
	if (get_z(me) == 163)
	{
		call_out("check_mot_30", 1800);
	}
	if (get_z(me) == 164)
	{
		call_out("check_hai_30", 1800);
	}
	if (get_z(me) == 261)
	{
		call_out("check_ba_30", 1800);
	}
	if (get_z(me) == 262)
	{
		call_out("check_bon_30", 1800);
	}
	if (get_z(me) == 263)
	{
		call_out("check_nam_30", 1800);
	}
	if (get_z(me) == 264)
	{
		call_out("check_sau_30", 1800);
	}
	if (get_z(me) == 265)
	{
		call_out("check_mot_35", 1800);
	}
	if (get_z(me) == 266)
	{
		call_out("check_hai_35", 1800);
	}
	if (get_z(me) == 111)
	{
		call_out("check_ba_35", 1800);
	}
	if (get_z(me) == 112)
	{
		call_out("check_bon_35", 1800);
	}
	if (get_z(me) == 011)
	{
		call_out("check_mot_40", 1800);
	}
	if (get_z(me) == 012)
	{
		call_out("check_hai_40", 1800);
	}
	if (get_z(me) == 013)
	{
		call_out("check_ba_40", 1800);
	}
	if (get_z(me) == 014)
	{
		call_out("check_bon_40", 1800);
	}
	if (get_z(me) == 015)
	{
		call_out("check_nam_40", 1800);
	}
	if (get_z(me) == 151)
	{
		call_out("check_mot_45", 1800);
	}
	if (get_z(me) == 152)
	{
		call_out("check_hai_45", 1800);
	}
	if (get_z(me) == 153)
	{
		call_out("check_ba_45", 1800);
	}
	if (get_z(me) == 171)
	{
		call_out("check_mot_50", 1800);
	}
	if (get_z(me) == 172)
	{
		call_out("check_hai_50", 1800);
	}
	if (get_z(me) == 173)
	{
		call_out("check_ba_50", 1800);
	}
	if (get_z(me) == 174)
	{
		call_out("check_bon_50", 1800);
	}
	if (get_z(me) == 071)
	{
		call_out("check_mot_55", 1800);
	}
	if (get_z(me) == 072)
	{
		call_out("check_hai_55", 1800);
	}
	if (get_z(me) == 073)
	{
		call_out("check_ba_55", 1800);
	}
	if (get_z(me) == 031)
	{
		call_out("check_mot_60", 1800);
	}
	if (get_z(me) == 032)
	{
		call_out("check_hai_60", 1800);
	}
	if (get_z(me) == 033)
	{
		call_out("check_ba_60", 1800);
	}
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
	//exp = level*500;
	pot = level * 5;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			exp2 = level * 500 + (size * 3000);
			level2 = level - team[i]->get_level();
			//    exp2 = exp * size * team[i]->get_level();///alllevel;
			if (size < 2)
				exp2 = me->correct_exp_bonus(level, level2, exp2) * who->get_online_rate() / 100;

			if (exp2 < 5)
				exp2 = 5;
			exp2 = exp2 * team[i]->get_online_rate() / 100;
			pot = pot * team[i]->get_online_rate() / 100;
			//exp3 = level*500;
			team[i]->add_exp(exp2);
			team[i]->add_potential(pot);
			//	"sys/sys/test_db"->add_yuanbao(team[i],level*10/size);
			//	team[i]->add_cash(level*1000/size);
			//	write_user(team[i], sprintf(ECHO "Bạn tiêu diệt Chiến Quốc Tống Bảo Yêu nhận được %d Kinh nghiệm và %d Kim bảo, Ngan Luong!",exp2, (level*10/size)/10 ),(level*10000/size));
		}
}
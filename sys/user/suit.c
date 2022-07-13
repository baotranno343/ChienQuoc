/***********
套装处理模块
*************/
#include <effect.h>
#include <skill.h>
#include <ansi.h>
#include <equip.h>

// 函数：生成二进制码
void SAVE_BINARY() {}
void remove_suit_effect(object who, string name, int amount);
void suit_effect(object who, string name, int amount);

// 函数：构造处理
void create()
{
}
//消除套装影响
void remove_suit_equip(object who)
{
	int i, size, j, count;
	string *nTmp;
	mapping mpTmp;

	mpTmp = who->get_2("suit_equip");
	if (!mapp(mpTmp))
		return;
	nTmp = keys(mpTmp);
	for (i = 0, size = sizeof(mpTmp); i < size; i++)
	{
		count = mpTmp[nTmp[i]]["count"];
		for (j = 2; j <= count; j++)
			remove_suit_effect(who, nTmp[i], j);
	}
}
//换装备时调用
void check_suit_equip(object who)
{
	int i, size, j, count, max;
	object *nEquip, oEquip, *inv;
	mapping mpTmp;
	string *nTmp, desc;

	remove_suit_equip(who);
	nEquip = who->get_all_equip();
	nEquip -= ({0});
	who->delete_2("suit_equip");
	for (i = 0, size = sizeof(nEquip); i < size; i++)
	{
		oEquip = nEquip[i];
		if (oEquip->is_suit())
		{
			who->add_2(sprintf("suit_equip.%s.count", oEquip->get_suit_name()), 1);
			//	who->set_2(sprintf("suit_equip.%s.equip.%s",oEquip->get_suit_name(),oEquip->get_name()),1);
		}
	}
	mpTmp = who->get_2("suit_equip");
	if (!mapp(mpTmp))
		return;
	nTmp = keys(mpTmp);
	for (i = 0, size = sizeof(mpTmp); i < size; i++)
	{
		count = mpTmp[nTmp[i]]["count"];
		for (j = 2; j <= count; j++)
			suit_effect(who, nTmp[i], j);
		if (count > max)
			max = count;
	}
	if (max >= 2)
		set_effect_2(who, EFFECT_USER_SUIT, 1, 5);

	for (i = 1; i <= HAND_TYPE - HEAD_TYPE + 1; i++) //已经装备的物品
	{
		"cmd/base/desc"->main(who, sprintf("%d", i));
	}
	inv = all_inventory(who, 0, 0);
	for (i = 0, size = sizeof(inv); i < size; i++)
	{
		if (!objectp(inv[i]) || inv[i]->is_suit() != 1)
			continue;
		send_user(who, "%c%d%c", 0x31, getoid(inv[i]), 0);
	}
}

//套装的影响
void suit_effect(object who, string name, int amount)
{
	int hp;
	object npc;

	switch (name)
	{
	case "Cự Tượng":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.hp.add", name), 5);
			who->set_2(sprintf("suit_sec.%s.hp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.hp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.ap.%s", name), 80);
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.pp.%s", name), 100);
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->set_2("suit_effect.double1", 30);
			who->set_2("suit_effect.double2", 50);
			break;
		}
		break;
	}
	case "Đằng Long":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.hp.add", name), 100);
			who->set_2(sprintf("suit_sec.%s.hp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.hp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.ap.%s", name), 160);
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.pp.%s", name), 200);
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->set_2("suit_effect.double1", 40);
			who->set_2("suit_effect.double2", 60);
			break;
		}
		break;
	}
	case "Chấn Thiên":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.hp.add", name), 250);
			who->set_2(sprintf("suit_sec.%s.hp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.hp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.ap.%s", name), 200);
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.pp.%s", name), 240);
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->set_2("suit_effect.double1", 50);
			who->set_2("suit_effect.double2", 60);
			break;
		}
		break;
	}
	case "Mãnh Hổ":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 5);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.maxhp.%s", name), 100);
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.ap.%s", name), 60);
			who->set_2(sprintf("suit_effect.cp.%s", name), 60);
			USER_ENERGY_D->count_ap(who);
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 200);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Thái Dương":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 100);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.maxhp.%s", name), 400);
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.ap.%s", name), 160);
			who->set_2(sprintf("suit_effect.cp.%s", name), 160);
			USER_ENERGY_D->count_ap(who);
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 600);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Thần Đạo":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 250);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.maxhp.%s", name), 600);
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.ap.%s", name), 200);
			who->set_2(sprintf("suit_effect.cp.%s", name), 200);
			USER_ENERGY_D->count_ap(who);
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 800);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Cuồng Sư":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2("suit_effect.no_drop", 1);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.ap.%s", name), 80);
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.pp.%s", name), 60);
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 200);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Lôi Quang":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2("suit_effect.no_drop", 1);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.ap.%s", name), 160);
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.pp.%s", name), 120);
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 600);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Cuồng Chiến":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2("suit_effect.no_drop", 1);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.ap.%s", name), 200);
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.pp.%s", name), 200);
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 800);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Săn Báo":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2("suit_effect.poison", 30);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.ap.%s", name), 40);
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->set_2("suit_effect.dodge", 5);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 200);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Toàn Phong":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2("suit_effect.poison", 60);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.ap.%s", name), 80);
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->set_2("suit_effect.dodge", 10);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 400);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Ám Toán":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2("suit_effect.poison", 80);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.ap.%s", name), 100);
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->set_2("suit_effect.dodge", 15);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 600);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Sói Trắng":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 5);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.dp.%s", name), 60);
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.cp.%s", name), 80);
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->set_2("suit_effect.summon", 1);
			npc = who->get("soldier");
			if (npc && !npc->get("suit_effect"))
			{
				npc->add_max_hp((hp = npc->get_max_hp() / 10));
				npc->set("suit_effect", hp);
				npc->add_dp(50);
			}
			break;
		}
		break;
	}
	case "Chiến Lang":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 100);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.dp.%s", name), 240);
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.cp.%s", name), 250);
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->set_2("suit_effect.summon", 1);
			npc = who->get("soldier");
			if (npc && !npc->get("suit_effect"))
			{
				npc->add_max_hp((hp = npc->get_max_hp() / 20));
				npc->set("suit_effect", hp);
				npc->add_dp(100);
			}
			break;
		}
		break;
	}
	case "Tu Sĩ":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 250);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.dp.%s", name), 300);
			who->set_2(sprintf("suit_effect.maxhp.%s", name), 500);
			USER_ENERGY_D->count_dp(who);
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.cp.%s", name), 320);
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->set_2("suit_effect.summon", 1);
			npc = who->get("soldier");
			if (npc && !npc->get("suit_effect"))
			{
				npc->add_max_hp((hp = npc->get_max_hp() / 40));
				npc->set("suit_effect", hp);
				npc->add_dp(200);
			}
			break;
		}
		break;
	}
	case "Tuyết Điêu":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 5);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2("suit_effect.damage2", 10);
			break;

		case 4:
			who->set_2(sprintf("suit_effect.maxmp.%s", name), 60);
			USER_ENERGY_D->count_max_mp(who);
			break;
		case 5:
			who->set_2("suit_effect.damage_rate1", 5);
			who->set_2("suit_effect.damage_rate3", 5);
			break;
		}
		break;
	}
	case "Liệp Ưng":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 100);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2("suit_effect.damage2", 40);
			break;

		case 4:
			who->set_2(sprintf("suit_effect.maxmp.%s", name), 240);
			USER_ENERGY_D->count_max_mp(who);
			break;
		case 5:
			who->set_2("suit_effect.damage_rate1", 10);
			who->set_2("suit_effect.damage_rate3", 10);
			break;
		}
		break;
	}
	case "Khai Sơn":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 300);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2("suit_effect.damage2", 60);
			break;

		case 4:
			who->set_2(sprintf("suit_effect.maxmp.%s", name), 600);
			USER_ENERGY_D->count_max_mp(who);
			break;
		case 5:
			who->set_2("suit_effect.damage_rate1", 20);
			who->set_2("suit_effect.damage_rate3", 20);
			break;
		}
		break;
	}
	case "Linh Hồ":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 10);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.dp.%s", name), 60);
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.maxhp.%s", name), 100);
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 5:
			who->set_2("suit_effect.damage_rand2", 33);
			break;
		}
		break;
	}
	case "Linh Lộc":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 100);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.dp.%s", name), 120);
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.maxhp.%s", name), 300);
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 5:
			who->set_2("suit_effect.damage_rand2", 66);
			break;
		}
		break;
	}
	case "Cứu Thế":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->set_2(sprintf("suit_sec.%s.mp.add", name), 400);
			who->set_2(sprintf("suit_sec.%s.mp.time", name), time());
			who->set_2(sprintf("suit_sec.%s.mp.interval", name), 5);
			break;
		case 3:
			who->set_2(sprintf("suit_effect.dp.%s", name), 200);
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->set_2(sprintf("suit_effect.maxhp.%s", name), 500);
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 5:
			who->set_2("suit_effect.double_rate", 800);
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	}
}

//消除特定套装的影响
void remove_suit_effect(object who, string name, int amount)
{
	int hp;
	object npc;

	switch (name)
	{
	case "Cự Tượng":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.pp.%s", name));
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double1", 30);
			who->delete_2("suit_effect.double2", 50);
			break;
		}
	}
	case "Đằng Long":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.pp.%s", name));
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double1", 40);
			who->delete_2("suit_effect.double2", 60);
			break;
		}
	}
	case "Chấn Thiên":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.pp.%s", name));
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double1", 50);
			who->delete_2("suit_effect.double2", 60);
			break;
		}
	}
	case "Mãnh Hổ":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.maxhp.%s", name));
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			who->delete_2(sprintf("suit_effect.cp.%s", name));
			USER_ENERGY_D->count_ap(who);
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Thái Dương":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.maxhp.%s", name));
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			who->delete_2(sprintf("suit_effect.cp.%s", name));
			USER_ENERGY_D->count_ap(who);
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Thần Đạo":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.maxhp.%s", name));
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			who->delete_2(sprintf("suit_effect.cp.%s", name));
			USER_ENERGY_D->count_ap(who);
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Cuồng Sư":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2("suit_effect.no_drop");
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.pp.%s", name));
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Lôi Quang":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2("suit_effect.no_drop");
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.pp.%s", name));
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Cuồng Chiến":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2("suit_effect.no_drop");
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.pp.%s", name));
			USER_ENERGY_D->count_pp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Săn Báo":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2("suit_effect.poison");
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->delete_2("suit_effect.dodge");
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Toàn Phong":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2("suit_effect.poison");
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->delete_2("suit_effect.dodge");
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Ám Toán":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2("suit_effect.poison");
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.ap.%s", name));
			USER_ENERGY_D->count_ap(who);
			break;
		case 4:
			who->delete_2("suit_effect.dodge");
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);
			break;
		}
		break;
	}
	case "Sói Trắng":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.dp.%s", name));
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.cp.%s", name));
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->delete_2("suit_effect.summon");
			npc = who->get("soldier");
			if (npc && (hp = npc->get("suit_effect")))
			{
				npc->delete ("suit_effect");
				npc->add_max_hp(-hp);
				npc->add_dp(-50);
			}
			break;
		}
		break;
	}
	case "Chiến Lang":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.dp.%s", name));
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.cp.%s", name));
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->delete_2("suit_effect.summon");
			npc = who->get("soldier");
			if (npc && (hp = npc->get("suit_effect")))
			{
				npc->delete ("suit_effect");
				npc->add_max_hp(-hp);
				npc->add_dp(-100);
			}
			break;
		}
		break;
	}
	case "Tu Sĩ":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.dp.%s", name));
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.cp.%s", name));
			USER_ENERGY_D->count_cp(who);
			break;
		case 5:
			who->delete_2("suit_effect.summon");
			npc = who->get("soldier");
			if (npc && (hp = npc->get("suit_effect")))
			{
				npc->delete ("suit_effect");
				npc->add_max_hp(-hp);
				npc->add_dp(-200);
			}
			break;
		}
		break;
	}
	case "Tuyết Điêu":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2("suit_effect.damage2");
			break;

		case 4:
			who->delete_2(sprintf("suit_effect.maxmp.%s", name));
			USER_ENERGY_D->count_max_mp(who);
			break;
		case 5:
			who->delete_2("suit_effect.damage_rate1");
			who->delete_2("suit_effect.damage_rate3");
			break;
		}
		break;
	}
	case "Liệp Ưng":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2("suit_effect.damage2");
			break;

		case 4:
			who->delete_2(sprintf("suit_effect.maxmp.%s", name));
			USER_ENERGY_D->count_max_mp(who);
			break;
		case 5:
			who->delete_2("suit_effect.damage_rate1");
			who->delete_2("suit_effect.damage_rate3");
			break;
		}
		break;
	}
	case "Khai Sơn":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2("suit_effect.damage2");
			break;

		case 4:
			who->delete_2(sprintf("suit_effect.maxmp.%s", name));
			USER_ENERGY_D->count_max_mp(who);
			break;
		case 5:
			who->delete_2("suit_effect.damage_rate1");
			who->delete_2("suit_effect.damage_rate3");
			break;
		}
		break;
	}
	case "Linh Hồ":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.dp.%s", name));
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.maxhp.%s", name));
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 5:
			who->delete_2("suit_effect.damage_rand2");
			break;
		}
		break;
	}
	case "Linh Lộc":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.dp.%s", name));
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.maxhp.%s", name));
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 5:
			who->delete_2("suit_effect.damage_rand2");
			break;
		}
		break;
	}
	case "Cứu Thế":
	{
		switch (amount)
		{
		default:
			break;
		case 2:
			who->delete_2(sprintf("suit_sec.%s", name));
			break;
		case 3:
			who->delete_2(sprintf("suit_effect.dp.%s", name));
			USER_ENERGY_D->count_dp(who);
			break;
		case 4:
			who->delete_2(sprintf("suit_effect.maxhp.%s", name));
			USER_ENERGY_D->count_max_hp(who);
			break;
		case 5:
			who->delete_2("suit_effect.double_rate");
			USER_ENERGY_D->count_hit_rate(who);

			break;
		}
		break;
	}
	}
}

void into_effect(object who)
{
	int i, size, iTime;
	string *nTmp;

	if (!mapp(who->get_2("suit_sec")))
		return;
	set_effect_2(who, EFFECT_USER_SUIT, 1, 5);
	nTmp = keys(who->get_2("suit_sec"));
	size = sizeof(nTmp);
	if (!size)
		who->delete_2("suit_sec");
	iTime = time();
	for (i = 0; i < size; i++)
	{
		if (mapp(who->get_2(sprintf("suit_sec.%s.hp", nTmp[i]))) && gone_time(who->get_2(sprintf("suit_sec.%s.hp.time", nTmp[i]))) >= who->get_2(sprintf("suit_sec.%s.hp.interval", nTmp[i])))
		{
			who->add_hp(who->get_2(sprintf("suit_sec.%s.hp.add", nTmp[i])));
			who->set_2(sprintf("suit_sec.%s.hp.time", nTmp[i]), iTime);
		}
		if (mapp(who->get_2(sprintf("suit_sec.%s.mp", nTmp[i]))) && gone_time(who->get_2(sprintf("suit_sec.%s.mp.time", nTmp[i]))) >= who->get_2(sprintf("suit_sec.%s.mp.interval", nTmp[i])))
		{
			who->add_mp(who->get_2(sprintf("suit_sec.%s.mp.add", nTmp[i])));
			who->set_2(sprintf("suit_sec.%s.mp.time", nTmp[i]), iTime);
		}
	}
}
//获取套装描述
string get_suit_desc(object who, object oEquip)
{
	string ret = "", name;
	int count;
	object owner;

	owner = oEquip->get_owner();
	if (owner && owner->is_user())
		who = owner;
	if (!who)
		return oEquip->get_suit_desc();
	name = oEquip->get_suit_name();
	count = who->get_2(sprintf("suit_equip.%s.count", name));
	switch (name)
	{
	default:
		break;
		// 55 DHN
	case "Cự Tượng":
		ret += sprintf("%s Cự Tượng (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf("%s Cự Tượng Đầu Khôi\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cự Tượng Đầu Khôi"))?PPM:WHT);
		//	ret += sprintf("%s Cự Tượng Khôi Giáp\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cự Tượng Khôi Giáp"))?PPM:WHT);
		//	ret += sprintf("%s Cự Tượng Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cự Tượng Hạng Liên"))?PPM:WHT);
		//	ret += sprintf("%s Cự Tượng Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cự Tượng Yêu Đới"))?PPM:WHT);
		//	ret += sprintf("%s Cự Tượng Chi Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cự Tượng Chi Ngoa"))?PPM:WHT);
		ret += sprintf("%s 2 món : 5 giây hồi 5 Khí Huyết\n", count >= 2 ? PPM : WHT);
		ret += sprintf("%s 3 món : tăng 80 Ngoại Công\n", count >= 3 ? PPM : WHT);
		ret += sprintf("%s 4 món : tăng 100 Nội Kháng\n", count >= 4 ? PPM : WHT);
		ret += sprintf("%s 5 món : giảm sát thương 30%%—50%% bạo kích\n", count >= 5 ? PPM : WHT);
		break;
		// 85 DHN
	case "Đằng Long":
		ret += sprintf("%s Đằng Long (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf("%s Đằng Long Đầu Khôi\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Đằng Long Đầu Khôi"))?PPM:WHT);
		//	ret += sprintf("%s Đằng Long Chiến Bào\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Đằng Long Chiến Bào"))?PPM:WHT);
		//	ret += sprintf("%s Đằng Long Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Đằng Long Hạng Liên"))?PPM:WHT);
		//	ret += sprintf("%s Đằng Long Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Đằng Long Yêu Đới"))?PPM:WHT);
		//	ret += sprintf("%s Đằng Long Chi Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Đằng Long Chi Ngoa"))?PPM:WHT);
		ret += sprintf("%s 2 món : 5 giây hồi 100 Khí Huyết\n", count >= 2 ? PPM : WHT);
		ret += sprintf("%s 3 món : tăng 160 Ngoại Công\n", count >= 3 ? PPM : WHT);
		ret += sprintf("%s 4 món : tăng 200 Nội Kháng\n", count >= 4 ? PPM : WHT);
		ret += sprintf("%s 5 món : giảm sát thương 40%%—60%% bạo kích\n", count >= 5 ? PPM : WHT);
		break;
		// 105 Huyết Long DHN
	case "Chấn Thiên":
		ret += sprintf("%s Chấn Thiên (%d/5)\n", count >= 2 ? HIR : WHT, count);
		ret += sprintf("%s 2 món : 5 giây hồi 250 Khí Huyết\n", count >= 2 ? HIR : WHT);
		ret += sprintf("%s 3 món : tăng 200 Ngoại Công\n", count >= 3 ? HIR : WHT);
		ret += sprintf("%s 4 món : tăng 240 Nội Kháng\n", count >= 4 ? HIR : WHT);
		ret += sprintf("%s 5 món : giảm sát thương 50%%—60%% bạo kích\n", count >= 5 ? HIR : WHT);
		break;

		// 55 TS
	case "Mãnh Hổ":
		ret += sprintf("%s Mãnh Hổ (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf("%s Mãnh Hổ Mão Quán\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Mãnh Hổ Mão Quán"))?PPM:WHT);
		//	ret += sprintf("%s Mãnh Hổ Bì Y\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Mãnh Hổ Bì Y"))?PPM:WHT);
		//	ret += sprintf("%s Mãnh Hổ Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Mãnh Hổ Hạng Liên"))?PPM:WHT);
		//	ret += sprintf("%s Mãnh Hổ Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Mãnh Hổ Yêu Đới"))?PPM:WHT);
		//	ret += sprintf("%s Mãnh Hổ Chi Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Mãnh Hổ Chi Ngoa"))?PPM:WHT);
		ret += sprintf("%s 2 món : 5 giây hồi 5 Ma Lực\n", count >= 2 ? PPM : WHT);
		ret += sprintf("%s 3 món : tăng 100 Khí Huyết\n", count >= 3 ? PPM : WHT);
		ret += sprintf("%s 4 món : tăng 60 Ngoại Công và 60 Nội Công\n", count >= 4 ? PPM : WHT);
		ret += sprintf("%s 5 món : tăng 2%% Bạo Kích\n", count >= 5 ? PPM : WHT);
		break;
		// 85 TS
	case "Thái Dương":
		ret += sprintf(" %s Thái Dương (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf(" %s Thái Dương Đầu Khôi\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Thái Dương Đầu Khôi"))?PPM:WHT);
		//	ret += sprintf(" %s Thái Dương Chiến Giáp\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Thái Dương Chiến Giáp"))?PPM:WHT);
		//	ret += sprintf(" %s Thái Dương Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Thái Dương Hạng Liên"))?PPM:WHT);
		//	ret += sprintf(" %s Thái Dương Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Thái Dương Yêu Đới"))?PPM:WHT);
		//	ret += sprintf(" %s Thái Dương Chi Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Thái Dương Chi Ngoa"))?PPM:WHT);
		ret += sprintf(" %s 2 món : 5 giây hồi 100 Ma Lực\n", count >= 2 ? PPM : WHT);
		ret += sprintf(" %s 3 món : tăng 400 Khí Huyết\n", count >= 3 ? PPM : WHT);
		ret += sprintf(" %s 4 món : tăng 160 Ngoại Công và 160 Nội Công\n", count >= 4 ? PPM : WHT);
		ret += sprintf(" %s 5 món : tăng 6%% Bạo Kích\n", count >= 5 ? PPM : WHT);
		break;
	// 105 Huyết Long TS
	case "Thần Đạo":
		ret += sprintf(" %s Thần Đạo (%d/5)\n", count >= 2 ? HIR : WHT, count);
		ret += sprintf(" %s 2 món : 5 giây hồi 250 Ma Lực\n", count >= 2 ? HIR : WHT);
		ret += sprintf(" %s 3 món : tăng 600 Khí Huyết\n", count >= 3 ? HIR : WHT);
		ret += sprintf(" %s 4 món : tăng 200 Ngoại Công và 200 Nội Công\n", count >= 4 ? HIR : WHT);
		ret += sprintf(" %s 5 món : tăng 8%% Bạo Kích\n", count >= 5 ? HIR : WHT);
		break;

		// 55 CVQ
	case "Cuồng Sư":
		ret += sprintf(" %s Cuồng Sư( %d /5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf(" %s Cuồng Sư Đầu Khôi\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cuồng Sư Đầu Khôi"))?PPM:WHT);
		//	ret += sprintf(" %s Cuồng Sư Chiến Giáp\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cuồng Sư Chiến Giáp"))?PPM:WHT);
		//	ret += sprintf(" %s Cuồng Sư Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cuồng Sư Hạng Liên"))?PPM:WHT);
		//	ret += sprintf(" %s Cuồng Sư Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cuồng Sư Yêu Đới"))?PPM:WHT);
		//	ret += sprintf(" %s Cuồng Sư Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Cuồng Sư Ngoa"))?PPM:WHT);
		ret += sprintf(" %s 2 món : vũ khí không bị rơi\n", count >= 2 ? PPM : WHT);
		ret += sprintf(" %s 3 món : tăng 80 Ngoại Công\n", count >= 3 ? PPM : WHT);
		ret += sprintf(" %s 4 món : tăng 60 Nội Kháng\n", count >= 4 ? PPM : WHT);
		ret += sprintf(" %s 5 món : tăng 2%% Bạo Kích\n", count >= 5 ? PPM : WHT);
		break;
		// 85 CVQ
	case "Lôi Quang":
		ret += sprintf(" %s Lôi Quang (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf(" %s Lôi Quang Đầu Khôi\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lôi Quang Đầu Khôi"))?PPM:WHT);
		//	ret += sprintf(" %s Lôi Quang Chiến Giáp\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lôi Quang Chiến Giáp"))?PPM:WHT);
		//	ret += sprintf(" %s Lôi Quang Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lôi Quang Hạng Liên"))?PPM:WHT);
		//	ret += sprintf(" %s Lôi Quang Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lôi Quang Yêu Đới"))?PPM:WHT);
		//	ret += sprintf(" %s Lôi Quang Hài\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lôi Quang Hài"))?PPM:WHT);
		ret += sprintf(" %s 2 món : không rớt vũ khí\n", count >= 2 ? PPM : WHT);
		ret += sprintf(" %s 3 món : tăng 160 Ngoại Công\n", count >= 3 ? PPM : WHT);
		ret += sprintf(" %s 4 món : tăng 120 Nội Kháng\n", count >= 4 ? PPM : WHT);
		ret += sprintf(" %s 5 món : tăng 6%% Bạo Kích\n", count >= 5 ? PPM : WHT);
		break;
		// 105 Huyết Long CVQ
	case "Cuồng Chiến":
		ret += sprintf(" %s Cuồng Chiến (%d/5)\n", count >= 2 ? HIR : WHT, count);
		ret += sprintf(" %s 2 món : không rớt vũ khí\n", count >= 2 ? HIR : WHT);
		ret += sprintf(" %s 3 món : tăng 200 Ngoại Công\n", count >= 3 ? HIR : WHT);
		ret += sprintf(" %s 4 món : tăng 200 nội kháng\n", count >= 4 ? HIR : WHT);
		ret += sprintf(" %s 5 món : tăng 8%% Bạo Kích\n", count >= 5 ? HIR : WHT);
		break;

		// 55 DM
	case "Săn Báo":
		ret += sprintf(" %s Săn Báo ( %d /5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf(" %s Lạp Báo Đầu Cân\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lạp Báo Đầu Cân"))?PPM:WHT);
		//	ret += sprintf(" %s Lạp Báo Phi Phong\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lạp Báo Phi Phong"))?PPM:WHT);
		//	ret += sprintf(" %s Lạp Báo Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lạp Báo Hạng Liên"))?PPM:WHT);
		//	ret += sprintf(" %s Lạp Báo Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lạp Báo Yêu Đới"))?PPM:WHT);
		//	ret += sprintf(" %s Lạp Báo Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Lạp Báo Ngoa"))?PPM:WHT);
		ret += sprintf(" %s 2 món : tăng 30 độc tính\n", count >= 2 ? PPM : WHT);
		ret += sprintf(" %s 3 món : tăng 40 Ngoại Công\n", count >= 3 ? PPM : WHT);
		ret += sprintf(" %s 4 món : tăng 5%% Thân Thủ\n", count >= 4 ? PPM : WHT);
		ret += sprintf(" %s 5 món : tăng 2%% Bạo Kích\n", count >= 5 ? PPM : WHT);
		break;
		// 85 DM
	case "Toàn Phong":
		ret += sprintf(" %s Toàn Phong (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf(" %s Toàn Phong Đầu Cân\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Toàn Phong Đầu Cân"))?PPM:WHT);
		//	ret += sprintf(" %s Toàn Phong Phi Phong\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Toàn Phong Phi Phong"))?PPM:WHT);
		//	ret += sprintf(" %s Toàn Phong Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Toàn Phong Hạng Liên"))?PPM:WHT);
		//	ret += sprintf(" %s Toàn Phong Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Toàn Phong Yêu Đới"))?PPM:WHT);
		//	ret += sprintf(" %s Toàn Phong Hài\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Toàn Phong Hài"))?PPM:WHT);
		ret += sprintf(" %s 2 món : tăng 60 độc tính\n", count >= 2 ? PPM : WHT);
		ret += sprintf(" %s 3 món : tăng 80 Ngoại Công\n", count >= 3 ? PPM : WHT);
		ret += sprintf(" %s 4 món : tăng 10%% Thân Thủ\n", count >= 4 ? PPM : WHT);
		ret += sprintf(" %s 5 món : tăng 4%% Bạo Kích\n", count >= 5 ? PPM : WHT);
		break;
	//105 Huyết Long DM
	case "Ám Toán":
		ret += sprintf(" %s Ám Toán (%d/5)\n", count >= 2 ? HIR : WHT, count);
		ret += sprintf(" %s 2 món : tăng 80 độc tính\n", count >= 2 ? HIR : WHT);
		ret += sprintf(" %s 3 món : tăng 100 Ngoại Công\n", count >= 3 ? HIR : WHT);
		ret += sprintf(" %s 4 món : tăng 15%% Né Tránh\n", count >= 4 ? HIR : WHT);
		ret += sprintf(" %s 5 món : tăng 6%% Bạo Kích\n", count >= 5 ? HIR : WHT);
		break;

		// 55 MS
	case "Sói Trắng":
		ret += sprintf(" %s Sói Trắng (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf(" %s Bạch Lang Bì Mão\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Bạch Lang Bì Mão"))?PPM:WHT);
		//	ret += sprintf(" %s Bạch Lang Bì Y\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Bạch Lang Bì Y"))?PPM:WHT);
		//	ret += sprintf(" %s Bạch Lang Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Bạch Lang Hạng Liên"))?PPM:WHT);
		//	ret += sprintf(" %s Bạch Lang Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Bạch Lang Yêu Đới"))?PPM:WHT);
		//	ret += sprintf(" %s Bạch Lang Chi Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Bạch Lang Chi Ngoa"))?PPM:WHT);
		ret += sprintf(" %s 2 món : 5 giây hồi 5 Ma Lực\n", count >= 2 ? PPM : WHT);
		ret += sprintf(" %s 3 món : tăng 60 Ngoại Kháng\n", count >= 3 ? PPM : WHT);
		ret += sprintf(" %s 4 món : tăng 80 Nội Công\n", count >= 4 ? PPM : WHT);
		ret += sprintf(" %s 5 món : tăng 10%% Khí Huyết và 50 Ngoại Kháng thú triệu hồi\n", count >= 5 ? PPM : WHT);
		break;
		// 85 MS
	case "Chiến Lang":
		ret += sprintf(" %s Chiến Lang ( %d /5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf(" %s Chiến Lang Bì Mão\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Chiến Lang Bì Mão"))?PPM:WHT);
		//	ret += sprintf(" %s Chiến Lang Bì Y\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Chiến Lang Bì Y"))?PPM:WHT);
		//	ret += sprintf(" %s Chiến Lang Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Chiến Lang Hạng Liên"))?PPM:WHT);
		//	ret += sprintf(" %s Chiến Lang Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Chiến Lang Yêu Đới"))?PPM:WHT);
		//	ret += sprintf(" %s Chiến Lang Chi Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Chiến Lang Chi Ngoa"))?PPM:WHT);
		ret += sprintf(" %s 2 món : 5 giây hồi 100 Ma Lực\n", count >= 2 ? PPM : WHT);
		ret += sprintf(" %s 3 món : tăng 240 Ngoại Kháng\n", count >= 3 ? PPM : WHT);
		ret += sprintf(" %s 4 món : tăng 250 Nội Công\n", count >= 4 ? PPM : WHT);
		ret += sprintf(" %s 5 món : tăng 20%% Khí Huyết và 100 Ngoại Kháng thú triệu hồi,\n", count >= 5 ? PPM : WHT);
		break;
	// 105 Huyết Long MS
	case "Tu Sĩ":
		ret += sprintf(" %s Tu Sĩ ( %d /5)\n", count >= 2 ? HIR : WHT, count);
		ret += sprintf(" %s 2 món : 5 giây hồi 250 Ma Lực\n", count >= 2 ? HIR : WHT);
		ret += sprintf(" %s 3 món : tăng 300 Ngoại Kháng và 500 Khí Huyết\n", count >= 3 ? HIR : WHT);
		ret += sprintf(" %s 4 món : tăng 320 Nội Công\n", count >= 4 ? HIR : WHT);
		ret += sprintf(" %s 5 món : tăng 40%% Khí Huyết và 200 Ngoại Kháng thú triệu hồi,\n", count >= 5 ? HIR : WHT);
		break;

		// 55 CL
	case "Tuyết Điêu":
		ret += sprintf("%s Tuyết Điêu (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf("%s Tuyết Điêu Vũ Mão\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Tuyết Điêu Vũ Mão"))?PPM:WHT);
		//	ret += sprintf("%s Tuyết Điêu Vũ Y\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Tuyết Điêu Vũ Y"))?PPM:WHT);
		//	ret += sprintf("%s Tuyết Điêu Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Tuyết Điêu Hạng Liên"))?PPM:WHT);
		//	ret += sprintf("%s Tuyết Điêu Vũ Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Tuyết Điêu Vũ Đới"))?PPM:WHT);
		//	ret += sprintf("%s Tuyết Điêu Vũ Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Tuyết Điêu Vũ Ngoa"))?PPM:WHT);
		ret += sprintf("%s 2 món : 5 giây hồi 5 Ma Lực\n", count >= 2 ? PPM : WHT);
		ret += sprintf("%s 3 món : tăng 10 thương tổn Nội Công\n", count >= 3 ? PPM : WHT);
		ret += sprintf("%s 4 món : tăng 60 Ma Lực\n", count >= 4 ? PPM : WHT);
		ret += sprintf("%s 5 món : giảm sát thương cận chiến nhận được 5%%\n", count >= 5 ? PPM : WHT);
		break;
		// 85 CL
	case "Liệp Ưng":
		ret += sprintf("%s Liệp Ưng (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf("%s Liệp Ưng Vũ Mão\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Liệp Ưng Vũ Mão"))?PPM:WHT);
		//	ret += sprintf("%s Liệp Ưng Vũ Y\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Liệp Ưng Vũ Y"))?PPM:WHT);
		//	ret += sprintf("%s Liệp Ưng Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Liệp Ưng Hạng Liên"))?PPM:WHT);
		//	ret += sprintf("%s Liệp Ưng Vũ Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Liệp Ưng Vũ Đới"))?PPM:WHT);
		//	ret += sprintf("%s Liệp Ưng Vũ Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Liệp Ưng Vũ Ngoa"))?PPM:WHT);
		ret += sprintf("%s 2 món : 5 giây hồi 100 Ma Lực\n", count >= 2 ? PPM : WHT);
		ret += sprintf("%s 3 món : tăng 40 thương tổn Nội Công\n", count >= 3 ? PPM : WHT);
		ret += sprintf("%s 4 món : tăng 240 Ma Lực\n", count >= 4 ? PPM : WHT);
		ret += sprintf("%s 5 món : Giảm sát thương cận chiến nhận được 10%%\n", count >= 5 ? PPM : WHT);
		break;
	// 105 Huyết Long CL
	case "Khai Sơn":
		ret += sprintf("%s Khai Sơn (%d/5)\n", count >= 2 ? HIR : WHT, count);
		ret += sprintf("%s 2 món : 5 giây hồi 300 Ma Lực\n", count >= 2 ? HIR : WHT);
		ret += sprintf("%s 3 món : tăng 60 thương tổn Nội Công\n", count >= 3 ? HIR : WHT);
		ret += sprintf("%s 4 món : tăng 600 Ma Lực\n", count >= 4 ? HIR : WHT);
		ret += sprintf("%s 5 món : Giảm sát thương cận chiến nhận được 20%%\n", count >= 5 ? HIR : WHT);
		break;

		// 55 VMC
	case "Linh Hồ":
		ret += sprintf("%s Linh Hồ (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf("%s Linh Hồ Nhung Mão\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Hồ Nhung Mão"))?PPM:WHT);
		//	ret += sprintf("%s Linh Hồ Bì Y\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Hồ Bì Y"))?PPM:WHT);
		//	ret += sprintf("%s Linh Hồ Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Hồ Hạng Liên"))?PPM:WHT);
		//	ret += sprintf("%s Linh Hồ Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Hồ Yêu Đới"))?PPM:WHT);
		//	ret += sprintf("%s Linh Hồ Chi Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Hồ Chi Ngoa"))?PPM:WHT);
		ret += sprintf("%s 2 món : 5 giây hồi 10 Ma Lực\n", count >= 2 ? PPM : WHT);
		ret += sprintf("%s 3 món : tăng 60 Ngoại Kháng\n", count >= 3 ? PPM : WHT);
		ret += sprintf("%s 4 món : tăng 100 Khí Huyết\n", count >= 4 ? PPM : WHT);
		ret += sprintf("%s 5 món : tăng 33 thương tổn Nội Công\n", count >= 5 ? PPM : WHT);
		break;
		// 85 VMC
	case "Linh Lộc":
		ret += sprintf("%s Linh Lộc (%d/5)\n", count >= 2 ? PPM : WHT, count);
		//	ret += sprintf("%s Linh Lộc Long Mão\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Lộc Long Mão"))?PPM:WHT);
		//	ret += sprintf("%s Linh Lộc Long Giáp\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Lộc Long Giáp"))?PPM:WHT);
		//	ret += sprintf("%s Linh Lộc Hạng Liên\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Lộc Hạng Liên"))?PPM:WHT);
		//	ret += sprintf("%s Linh Lộc Yêu Đới\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Lộc Yêu Đới"))?PPM:WHT);
		//	ret += sprintf("%s Linh Lộc Long Ngoa\n",who->get_2(sprintf("suit_equip.%s.equip.%s",name,"Linh Lộc Long Ngoa"))?PPM:WHT);
		ret += sprintf("%s 2 món : 5 giây hồi 100 Ma Lực\n", count >= 2 ? PPM : WHT);
		ret += sprintf("%s 3 món : tăng 120 Ngoại Kháng\n", count >= 3 ? PPM : WHT);
		ret += sprintf("%s 4 món : tăng 300 Khí Huyết\n", count >= 4 ? PPM : WHT);
		ret += sprintf("%s 5 món : tăng 66 thương tổn Nội Công\n", count >= 5 ? PPM : WHT);
		break;
	// 105 Huyết Long VMC
	case "Cứu Thế":
		ret += sprintf("%s Cứu Thế (%d/5)\n", count >= 2 ? HIR : WHT, count);
		ret += sprintf("%s 2 món : 5 giây hồi 400 Ma Lực\n", count >= 2 ? HIR : WHT);
		ret += sprintf("%s 3 món : tăng 200 Ngoại Kháng\n", count >= 3 ? HIR : WHT);
		ret += sprintf("%s 4 món : tăng 500 Khí Huyết\n", count >= 4 ? HIR : WHT);
		ret += sprintf("%s 5 món : tăng 8%% Bạo Kích\n", count >= 5 ? HIR : WHT);
		break;
	}
	return ret;
}
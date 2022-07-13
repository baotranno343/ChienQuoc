#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <public.h>
#include <time.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 8013; }
void do_bonus();
// 函数：构造处理
void create()
{
	set_name("Đoạt Bảo Mã Tặc");
	set_2("talk", (["bonus":(
								: do_bonus:),
	]));

	setup();
}
void do_look(object who)
{
	send_user(who, "%c%c%w%s", ':', 3, 8013, "Đoạt Bảo Mã Tặc:\n Ngươi muốn khiêu chiến với ta sao, suy nghĩ kĩ chưa ?\n" + sprintf(ESC "Khiêu chiến\ntalk %x# bonus\n", getoid(this_object())) + ESC "Rời khỏi");
}
void do_bonus()
{
	object who = this_player(), me = this_object();

	int x, y, z, level, p, d, family, ord, size, i;
	string cityname;
	object map, npc, *team;

	if (who->get_level() < 40)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Đoạt Bảo Mã Tặc: \nCấp bậc của ngươi chưa đạt 40 cấp, không có tư cách khiêu chiến với ta. \n" ESC "Xác nhận");
		return;
	}
	team = who->get_team();
	size = sizeof(team);
	if (size > 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Đoạt Bảo Mã Tặc: \nĐi một mình mới có thể khiêu chiến với ta, nếu cần sự trợ giúp của đồng đội thì đừng hòng ta chấp nhận lời khiêu chiến. \n" ESC "Xác nhận");
		return;
	}
	for (i = 0; i < size; i++)
	{
		if (!objectp(team[i]))
			continue;
		if (!inside_screen_2(me, team[i]))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Đoạt Bảo Mã Tặc: \nNếu đã không phải đi 1 mình thì hãy gọi đồng đội của ngươi đến đây cho ta xem mặt nào! Haha! \n" ESC "Xác nhận");
			return;
		}
	}
	if ((z = find_map_flag(1000, 2999, 0)) <= 0)
		return;
	x = (p % 1000000) / 1000;
	y = p % 1000;
	npc = new ("npc/event/doatbaomatac2");
	if (!npc)
		return;
	npc->set("level", who->get_level());
	d = 895;
	cityname = "Đấu Trường";
	init_virtual_map(z, d);
	map = new (NEWBIE);
	map->set_client_id(d);
	map->set_owner(who);
	set_map_object(map, map->set_id(z));
	map->set_name(cityname);
	p = get_jumpin(z, 1);
	npc->set_char_type(FIGHTER_TYPE_2);
	npc->set_level(who->get_level());
	NPC_ENERGY_D->init_level(npc, who->get_level());
	npc->add_max_hp(npc->get_max_hp() * 10);
	npc->add_dp(npc->get_dp() * 2);
	npc->add_ap(npc->get_ap() * 1 / 10);
	npc->add_pp(npc->get_pp() * 2);
	npc->set_walk_speed(2);
	npc->set_attack_speed(10);
	NPC_ENERGY_D->init_family1(npc);
	x = p / 1000, y = p % 1000;
	npc->set("doatbao_z", z);
	npc->set("doatbao_x", x);
	npc->set("doatbao_y", y);
	npc->set("user", who->get_number());
	npc->set("fight", who);
	who->set_2("doatbaomatac.x", get_x(who));
	who->set_2("doatbaomatac.y", get_y(who));
	who->set_2("doatbaomatac.z", get_z(who));
	if (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
	{
		x = p / 1000, y = p % 1000;
		who->add_to_scene(z, x, y, 3);
	}
	who->set_save_2("doatbaomatac.time", time());
	who->set_save_2("doatbaomatac.status", 1);
	npc->do_fight(1);
	me->remove_from_scene();
	destruct(me);
	return;
}

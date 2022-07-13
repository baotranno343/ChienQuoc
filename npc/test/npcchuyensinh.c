/*
Edit by Nguyễn Quang Hiếu
*/
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <time.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

inherit OFFICER;

// 函数:获取人物造型
int get_char_picid() { return 5101; }
int is_seller() { return 6006; }
int is_self_look() { return 1; }
void do_gift(string arg);

// 函数:构造处理
void create()
{
	set_name("Tiên Đế Thánh Thượng");
	set_real_name(HIR "Chuyển Sinh");

	set_2("talk", (["gift":(
							   : do_gift:),
	]));

	setup();
}

void do_look(object who)
{
	int id = getoid(this_object()), knb, cap;
	if (who->get_save_2("chuyensinh.score") == 0)
	{
		knb = 5000;
		cap = 120;
	}

	if (who->get_save_2("chuyensinh.score") < 1)
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf("%s :\nNgươi muốn Chuyển Sinh không ? \nSố lần Chuyển Sinh của ngươi là : " HIR "%d " NOR "Lần \nBây giờ Chuyển Sinh cần phải đạt tới cấp " HIB "%d " NOR " \nVà cần phải tiêu hao " HIB "%d " NOR "Kim Nguyên Bảo !\n" ESC HIY "Chuyển Sinh\ntalk %x# gift.2\n" ESC "Rời khỏi", get_name(), who->get_save_2("chuyensinh.score"), cap, knb, id, id, id, id, id, id));
	}
	else
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf("%s :\nNgươi đã Chuyển Sinh đến giới hạn, khi Sự kiện Chuyển Sinh Bá Vương bắt đầu mới có thể tiếp tục Chuyển Sinh !\n" ESC HIY "Nhận Thưởng Chuyển Sinh\ntalk %x# gift.7\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id));
	}
}

void do_gift(string arg)
{
	object me = this_object();
	__FILE__->do_gift2(me, arg);
}

void do_gift2(object me, string arg)
{
	int flag, id, i, p, size;
	object who, item, *inv, item2;
	string *nTmp, cFile, cTmp;
	string *thucuoi = ({"cao", "cavoi", "chim", "dadieu", "gau", "kien", "ngua", "rua", "tham", "tuanloc", "voi"});
	who = this_player();

	id = getoid(me);
	flag = to_int(arg);
	who->set_time("talk", 0);
	switch (flag)
	{
	case 1:
		break;
	case 2:
		if (who->get_save_2("chuyensinh.score") >= 1)
		{
			send_user(who, "%c%s", ':', me->get_name() + ":\n    Ngươi đã Chuyển Sinh tới giới hạn rồi !!!\n" ESC "Rời khỏi.");
			return;
		}

		inv = who->get_all_equip();
		for (i = 0, size = sizeof(inv); i < size; i++)
		{
			if (i == 7)
			{
				continue;
			}
			if (inv[i] != 0)
			{
				send_user(who, "%c%s", ':', me->get_name() + ":\n    Vui lòng gỡ hết trang bị ra\n" ESC "Rời khỏi.");
				return;
			}
		}
		// if (who->get_all_equip())
		// {
		// 	send_user(who, "%c%s", ':', me->get_name() + ":\n    Vui lòng gỡ hết trang bị ra\n" ESC "Rời khỏi.");
		// 	return;
		// }
		if (who->get_save_2("chuyensinh.score") < 1)
		{
			if (who->get_level() < 120)
			{
				send_user(who, "%c%s", ':', me->get_name() + ":\n    Cấp độ chưa đạt tới cấp 120, không thể Chuyển Sinh Lần 1 !!!\n" ESC "Rời khỏi.");
				return;
			}
			else if ("sys/sys/test_db"->get_yuanbao(who) < 50000)
			{
				send_user(who, "%c%s", ':', me->get_name() + ":\n    Không đủ 5000 Kim Nguyên Bảo, không thể Chuyển Sinh Lần 1 !!!\n" ESC "Rời khỏi.");
				return;
			}
			"sys/sys/test_db"->add_yuanbao(who, -50000);
			who->add_save_2("chuyensinh.score", 1);
			who->set_level(40);
			who->set_upgrade_exp(0);
			who->set_exp(USER_EXP_D->get_level_exp_low(who->get_reincarnation(), 40 - 1),
						 USER_EXP_D->get_level_exp_high(who->get_reincarnation(), 40 - 1));
			USER_ENERGY_D->count_all_prop(who);
			USER_ENERGY_D->count_max_yuan(who);
			who->set_max_level(who->get_level());
			who->set_hp(who->get_max_hp());
			who->set_mp(who->get_max_mp());

			who->count_gift();
			who->add_gift_point(250);
			who->add_title("Y001");
			who->show_title("Y001");

			USER_ENERGY_D->count_all_prop(who);

			send_user(who, "%c%s", ';', HIY "Bạn đã Chuyển Sinh lần 1 !!!");
			USER_D->user_channel(sprintf(HIG "Chúc mừng " HIC "%s" HIG " đã Chuyển Sinh lần thứ " HIC " %d  " HIG " . ", who->get_name(), who->get_save_2("chuyensinh.score")));
			return 0;
		}

		break;

	case 7:
		if (who->get_save_2("chuyensinh.score") < 1)
		{
			send_user(who, "%c%s", ':', me->get_name() + ":\n    Ngươi chưa Chuyển Sinh đã muốn nhận thưởng ???\n" ESC "Rời khỏi.");
			return;
		}
		if (who->get_save_2("chuyensinh.score") == 1)
		{
			if (who->get_save_2("chuyensinh.gift") >= 1)
			{
				send_user(who, "%c%s", ':', me->get_name() + ":\n    Ngươi đã nhận thưởng Chuyển Sinh lần 1 một lần rồi !\n" ESC "Rời khỏi.");
				return;
			}
			if (USER_INVENTORY_D->get_free_count(who) < 5)
			{
				notify("Hành trang không đủ 5 chỗ trống");
				return;
			}
			who->set_save_2("chuyensinh.gift", 1);
			who->add_cash(10000000);

			item = new ("ken/chuyensinh/hacthantuong");
			item->set_no_give(1);
			p = item->move2(who, -1);
			item->add_to_user(p);

			item = new ("item/01/0008");
			item->set_no_give(1);
			p = item->move2(who, -1);
			item->add_to_user(p);

			item = new ("item/ride/thucuoivip/" + thucuoi[random(10)]);
			item->set_no_give(1);
			p = item->move2(who, -1);
			item->add_to_user(p);

			send_user(who, "%c%s", ';', HIY "Bạn đã nhận thưởng Chuyển Sinh lần 1 !!!");
			return 0;
		}

		break;
	}
}
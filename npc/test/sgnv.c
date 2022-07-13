/* design by TjaGoChangLj
cải tiến bởi Nguyễn Quang Hiếu
*/
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>
#include <time.h>
#include <effect.h>

inherit OFFICER;

mapping Map = (["Sở Phương Thành 1":({061, 208, 133}),
					  "Mã Lăng Đạo":({141, 136, 67}),
				"Ranh Giới Đầm Lầy":({163, 81, 109}),
				"Đông Hải Ngư Thôn":({011, 51, 43}),
					   "Cự Thú Đảo":({549, 156, 128}),
		  "Địa Ngục Ma Quật Tầng 1":({533, 176, 157}),
		  "Địa Ngục Ma Quật Tầng 2":({534, 157, 143}),
		  "Địa Ngục Ma Quật Tầng 3":({535, 188, 125}),
		  "Địa Ngục Ma Quật Tầng 4":({536, 154, 148}),
		  "Địa Ngục Ma Quật Tầng 5":({537, 154, 125}),
		  "Địa Ngục Ma Quật Tầng 6":({538, 162, 149}),
		  "Địa Ngục Ma Quật Tầng 7":({539, 154, 123}),
		  "Địa Ngục Ma Quật Tầng 8":({540, 152, 128}),
]);

// 函数:获取人物造型
int get_char_picid() { return 5105; }
int is_seller() { return 7000; }
int is_self_look() { return 1; }
void do_welcome(string arg);
void do_bonus(string arg);

// 函数:构造处理
void create()
{
	set_name(HIB "Sứ Giả Nhiệm Vụ");
	//	set_real_name(HIR "Sứ Giả Nhiệm Vụ");
	set_2("good", ([
					  //    "01" : "/item/sell/4032",
					  //    "01" : "/item/ppvacanh/HoaPhu",
					  //    "02" : "/item/sell/0203",
					  //    "02" : "/item/test2/1008",
					  //    "03" : "/item/test2/1012",
					  //    "04" : "/item/test2/1013",
					  // "01":"/item/sell/0032",
	]));
	set_2("talk", ([

					  "welcome":(
									: do_welcome:),
						"bonus":(
									: do_bonus:),
	]));

	setup();
}

// 函数:对话处理
void do_look(object who, object me)
{
	int id = getoid(this_object());
	if (who->get_save_2("kiemtradanhanchua.score") == 1)
	{
		if (who->get_save_2("soquaicandiet.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Sở Quân Đao Binh,Sở Quân Kiếm Binh. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Sở Phương Thành <khu vực cấp 10-14>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Sở Phương Thành 1\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Sở Quân Đao Binh,Sở Quân Kiếm Binh. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ? " NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.1\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 2)
	{
		if (who->get_save_2("soquaicandiet1.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Phi Tặc,Ác Đồ.... " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Mã Lăng Đạo <khu vực cấp 20-24>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Mã Lăng Đạo\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Phi Tặc,Ác Đồ.... " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.2\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 3)
	{
		if (who->get_save_2("soquaicandiet2.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Hạt Vĩ Hạt,Chu Chu Quái,Độc Thứ Phong. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Ranh Giới Đầm Lầy <khu vực cấp 30-34>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Ranh Giới Đầm Lầy\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Hạt Vĩ Hạt,Chu Chu Quái,Độc Thứ Phong. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.3\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 4)
	{
		if (who->get_save_2("soquaicandiet3.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Binh Tôm,Tướng Cua. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Đông Hải Ngư Thôn <khu vực cấp 40-44>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Đông Hải Ngư Thôn\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Binh Tôm,Tướng Cua. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.4\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 5)
	{
		if (who->get_save_2("soquaicandiet4.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Tôm Hùng Đông Hải,Cua. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Cự Thú Đảo <khu vực cấp 55>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Cự Thú Đảo\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Tôm Hùng Đông Hải,Cua. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.5\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 6)
	{
		if (who->get_save_2("soquaicandiet5.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Địa Ngục Săn Báo. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Địa Ngục Ma Quật tầng 1 của Cự Thú Đảo <khu vực cấp 60>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Địa Ngục Ma Quật Tầng 1\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Địa Ngục Săn Báo. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.6\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 7)
	{
		if (who->get_save_2("soquaicandiet6.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Cự Hình Đường Lang Yêu. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Địa Ngục Ma Quật tầng 2 của Cự Thú Đảo <khu vực cấp 70>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Địa Ngục Ma Quật Tầng 2\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Cự Hình Đường Lang Yêu. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.7\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 8)
	{
		if (who->get_save_2("soquaicandiet7.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Địa Ngục Quán Yêu. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Địa Ngục Ma Quật tầng 3 của Cự Thú Đảo <khu vực cấp 80>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Địa Ngục Ma Quật Tầng 3\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Địa Ngục Quán Yêu. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.8\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 9)
	{
		if (who->get_save_2("soquaicandiet8.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Xích Kim Ma Hổ,Lục Huỳnh Quỷ. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Địa Ngục Ma Quật tầng 4 của Cự Thú Đảo <khu vực cấp 85-95>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Địa Ngục Ma Quật Tầng 4\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Xích Kim Ma Hổ,Lục Huỳnh Quỷ. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.9\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 10)
	{
		if (who->get_save_2("soquaicandiet9.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Địa Ngục Ma Binh,Địa Ngục Ma Tốt. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Địa Ngục Ma Quật tầng 5 của Cự Thú Đảo <khu vực cấp 100-105>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Địa Ngục Ma Quật Tầng 5\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Địa Ngục Ma Binh,Địa Ngục Ma Tốt. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.10\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 11)
	{
		if (who->get_save_2("soquaicandiet10.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Địa Ngục Chu Chu. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Địa Ngục Ma Quật tầng 6 của Cự Thú Đảo <khu vực cấp 110-115>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Địa Ngục Ma Quật Tầng 6\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Địa Ngục Chu Chu " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.11\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 12)
	{
		if (who->get_save_2("soquaicandiet11.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Địa Ngục Ma Bò Cạp,Địa Ngục Ác Tặc. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Địa Ngục Ma Quật tầng 7 của Cự Thú Đảo <khu vực cấp 120-125>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Địa Ngục Ma Quật Tầng 7\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Địa Ngục Ma Bò Cạp,Địa Ngục Ác Tặc. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.12\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}
	else if (who->get_save_2("kiemtradanhanchua.score") == 13)
	{
		if (who->get_save_2("soquaicandiet12.score") < 20)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi hãy giúp ta giết " HIR ": 20 con Địa Ngục Ác Lang,Địa Ngục Cương Thi. " HIB "(Lượt thứ %d).." NOR "(Nghe nói chúng có rất nhiều ở Địa Ngục Ma Quật tầng 8 của Cự Thú Đảo <khu vực cấp 130-145>)" NOR " \n" ESC HIY "Chuyển tới nơi làm nhiệm vụ\ntalk %x# welcome.100 Địa Ngục Ma Quật Tầng 8\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Thôi lát ta làm\n", who->get_save_2("solanlam.score"), id, id, id));
		}
		else
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi đã giết đủ " HIR ": 20 con Địa Ngục Ác Lang,Địa Ngục Cương Thi. " HIB "(Lượt thứ %d).." NOR "Ngươi muốn Hoàn thành Nhiệm vụ không ?" NOR " \n" ESC HIY "Hoàn thành nhiệm vụ\ntalk %x# bonus.13\n" ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n" ESC "Rời khỏi\n", who->get_save_2("solanlam.score"), id, id, id));
		}
	}

	else
		send_user(who, "%c%s", ':', sprintf(get_name() + ":\nCó phải ngươi muốn làm Nhiệm vụ của ta ?? \nNhiệm vụ cho phép mỗi ngày được làm 10 lượt !!! \nĐiểm tích luỹ Nhiệm vụ của ngươi là : %d điểm\n" ESC HIY "Nhận nhiệm vụ\ntalk %x# welcome.1\n"
												//	ESC HIG"Đổi Đoạn Thạch Đặc Biệt (500 điểm)\ntalk %x# bonus.100\n"
												//ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n"
												ESC "Thôi lát ta làm\n",
											who->get_save_2("diemnhiemvu.score"), id, id, id, id));
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int flag, id, p, i, iTime, iDay, solanlam, z, x, y, *zxy;
	object who, item;
	string *nTmp, cFile, cTmp, cFinal, result, mapname;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];

	who = this_player();
	id = getoid(me);
	flag = to_int(arg);
	who->set_time("talk", 0);
	solanlam = who->get_save_2("solanlam.score") + 1;
	switch (flag)
	{
	case 1:
		if (who->get_level() < 10)
		{
			send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi phải đạt cấp 10 trở lên thì mới có thể nhận nhiệm vụ"));
			return 0;
		}
		if (who->get_save_2("moingay.day") == iDay)
		{
			result = me->get_name() + ":\n    Hôm nay đã làm 10 lượt rồi ! Ngày mai hãy đến nhé !\n";
			send_user(who, "%c%c%w%s", ':', 3, 5105, result);
			return;
		}
		if (who->get_save_2("solanlam.score") > 9)
		{
			who->set_save_2("moingay.day", iDay);
			who->set_save_2("solanlam.score", 0);
			result = me->get_name() + ":\n    Hôm nay đã làm 10 lượt rồi ! Ngày mai hãy đến nhé !\n";
			send_user(who, "%c%c%w%s", ':', 3, 5105, result);
			return;
		}
		if (who->get_level() >= 130)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Địa Ngục Ác Lang hoặc Địa Ngục Cương Thi", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 13);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(540, 152, 128);
			return 0;
		}
		if (who->get_level() >= 120)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Địa Ngục Ma Bò Cạp hoặc Địa Ngục Ác Tặc", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 12);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(539, 154, 123);
			return 0;
		}
		if (who->get_level() >= 110)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Địa Ngục Chu Chu", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 11);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(538, 162, 149);
			return 0;
		}
		if (who->get_level() >= 100)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Địa Ngục Ma Binh hoặc Địa Ngục Ma Tốt", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 10);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(537, 154, 125);
			return 0;
		}
		if (who->get_level() >= 90)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Xích Kim Ma Hổ hoặc Lục Huỳnh Quỷ", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 9);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(536, 154, 148);
			return 0;
		}
		if (who->get_level() >= 80)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Địa Ngục Quán Yêu", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 8);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(535, 188, 125);
			return 0;
		}
		if (who->get_level() >= 70)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Cự Hình Đường Lang Yêu", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 7);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(534, 157, 143);
			return 0;
		}
		if (who->get_level() >= 60)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Địa Ngục Săn Báo", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 6);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(533, 176, 157);
			return 0;
		}
		if (who->get_level() >= 50)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Tôm Hùng Đông Hải hoặc Cua", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 5);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(549, 156, 128);
			return 0;
		}
		if (who->get_level() >= 40)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Binh Tôm hoặc Tướng Cua", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 4);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(011, 51, 43);
			return 0;
		}
		if (who->get_level() >= 30)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Hạt Vĩ Hạt hoặc Chu Chu Quái hoặc Độc Thứ Phong", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 3);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(163, 81, 109);
			return 0;
		}
		if (who->get_level() >= 20)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Phi Tặc hoặc Ác Đồ", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 2);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(141, 136, 67);
			return 0;
		}
		if (who->get_level() >= 10)
		{
			send_user(who, "%c%s", ';', sprintf("Bạn đã nhận nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Hãy tiêu diệt 20 con Sở Quân Đao Binh hoặc Sở Quân Kiếm Binh", solanlam));
			who->add_save_2("solanlam.score", 1);
			who->add_save_2("kiemtradanhanchua.score", 1);
			who->set_login_flag(2); // 跳转保护
			set_invisible(who, 1);
			set_effect(who, EFFECT_USER_LOGIN, 4);
			who->add_to_scene(061, 208, 133);
			return 0;
		}
		break;
	case 3:
		send_user(who, "%c%s", ':', sprintf(get_name() + ": \nĐiểm tích luỹ nhiệm vụ của ngươi là : %d điểm \n"
												//	ESC HIY"Đổi Đoạn Thạch Đặc Biệt (500 điểm)\ntalk %x# bonus.100\n"
												ESC HIG "Ta muốn đổi thưởng\nlist2 %x#\n"
												//	ESC HIY"Biến hình thành Vô Môn Phái Nam (5 điểm)\ntalk %x# bonus.101\n"
												//	ESC HIY"Biến hình thành Vô Môn Phái Nữ (5 điểm)\ntalk %x# bonus.102\n"
												//	ESC HIY"Biến hình thành Thục Sơn Nam (5 điểm)\ntalk %x# bonus.104\n"
												//	ESC HIY"Biến hình thành Thục Sơn Nữ (5 điểm)\ntalk %x# bonus.105\n"
												//	ESC HIY"Hủy bỏ Biến hình (Không mất điểm)\ntalk %x# bonus.103\n"
												ESC HIG "Thôi lát ta đổi\n",
											who->get_save_2("diemnhiemvu.score"), id, id, id, id, id, id, id, id));
		break;
	case 100:
		if (!sscanf(arg, "%d %s", flag, mapname) == 2)
			return;
		zxy = Map[mapname];
		if (!zxy)
			return;
		z = zxy[0];
		x = zxy[1];
		y = zxy[2];
		__FILE__->send_ok(who, z, x, y);
		break;
	}
}

//可以传送
void send_ok(object who, int z, int x, int y)
{
	int p;
	object me = this_object();
	p = x * 1000 + y;
	send_user(who, "%c%c%w%s", 0x5a, 0, 1, "Đang di chuyển……");
	who->set_2("travel.z", z);
	who->set_2("travel.p", p);
	set_effect(who, EFFECT_TRAVEL, 1);
	//	me->add_to_scene(z,x-2,y-2);
}

void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_object(), arg);
}

void do_bonus_2(object me, string arg)
{
	int flag, point, i, id, p, soluong, solanlam, cap, iTime, iDay, exp, knbkhoa, cashkhoa;
	object who, item;
	string cTmp, cFile, result;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];
	who = this_player();
	flag = to_int(arg);

	solanlam = who->get_save_2("solanlam.score");
	cap = who->get_level();
	switch (flag)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		if (who->get_save_2("moingay.day") == iDay)
		{
			result = me->get_name() + ":\n    Hôm nay đã làm 10 lượt rồi ! Ngày mai hãy đến nhé !\n";
			send_user(who, "%c%c%w%s", ':', 3, 5105, result);
			return;
		}
		if (flag == 1)
		{
			if (who->get_save_2("soquaicandiet.score") < 20)
			{
				send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi vẫn chưa giết đủ. Số lượng ngươi giết được là " HIR ":%d/20", who->get_save_2("soquaicandiet.score")));
				return 0;
			}
			who->set_save_2("soquaicandiet.score", 0);
		}
		else
		{
			if (who->get_save_2(sprintf("soquaicandiet%d.score", flag - 1)) < 20)
			{
				send_user(who, "%c%s", ':', sprintf(get_name() + ":\n    Ngươi vẫn chưa giết đủ. Số lượng ngươi giết được là " HIR ":%d/20", who->get_save_2("soquaicandiet1.score")));
				return 0;
			}
			who->set_save_2(sprintf("soquaicandiet%d.score", flag - 1), 0);
		}
		exp = (cap + solanlam) * 300;
		knbkhoa = 20;
		cashkhoa = 20000;
		who->set_save_2("kiemtradanhanchua.score", 0);
		who->add_save_2("diemnhiemvu.score", 1);
		who->add_exp(exp);
		who->add_knbkhoa(knbkhoa);
		who->add_cashkhoa(cashkhoa);
		if (who->get_save_2("solanlam.score") == 10)
		{
			who->add_cashkhoa(60000);
			who->add_knbkhoa(60);
		}
		send_user(who, "%c%s", ';', sprintf("Bạn đã hoàn thành nhiệm vụ lượt thứ " HIY "%d " NOR "!!!" HIC " Nhận được : %d Kim Nguyên Bảo khóa,   %d Ngân Lượng Khóa và %d kinh nghiệm", solanlam, knbkhoa, cashkhoa, exp));
		if (solanlam > 9)
		{
			who->set_save_2("moingay.day", iDay);
			who->set_save_2("solanlam.score", 0);
			result = me->get_name() + ":\n    Hôm nay đã làm 10 lượt rồi ! Ngày mai hãy đến nhé !\n";
			send_user(who, "%c%c%w%s", ':', 3, 5105, result);
			return;
		}
		break;
	}
}

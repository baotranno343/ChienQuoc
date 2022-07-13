
#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5417; }
void do_welcome(string arg);

void create()
{
	set_name("Thợ Làm Bánh");
	//	set_real_name("Phàm Chân");
	set_2("talk", (["welcome":(
								  : do_welcome:),

	]));
	setup();
}

void do_welcome(string arg)
{
	__FILE__->do_welcome2(this_object(), arg);
}
void do_welcome2(object npc, string arg)
{
	int flag, p, i, size, rate;
	object player = this_player(), item, who, me;
	string *nTmp, cFile, cTmp, cFinal, result, bennhat, bn;
	flag = to_int(arg);
	who = this_player();
	//	id = getoid(me);
	//      who->set_time( "talk",  0);
	rate = random(100);
	switch (flag)
	{

	case 1:
		return;
		//   if ( flag==11 ) bn="item/30/3020";
		//	else if ( flag==12 ) bn="item/30/3021";
		if (TASK_LEGEND_D->check_task_item_amount(who, "Ác Quỷ(vương)") < 70)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nVậy là ngươi không có 70 Ác Quỷ(vương)? Vậy đến đây làm gì vậy !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}

		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nHành trang của ngươi không đủ 1 ô trống !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Ác Quỷ(vương)", 70);
		if (random100() < 90)
			item = new ("item/sell/3032");
		else
			notify("Ghép thất bại, xin chia buồn cùng các hạ!");
		if (item)
		{
			p = item->move2(who, -1);
			item->add_to_user(p);
			send_user(who, "%c%s", ';', "Bạn đã thành công đổi được " + item->get_name() + ", xin chúc mừng !");
			CHAT_D->vip_channel(0, sprintf("Chúc mừng " HIR "" + who->get_name() + " " NOR "đã đổi thành công " HIY "%s" NOR "!", item->get_name()));
		}
		break;
	case 2:
		//   if ( flag==11 ) bn="item/30/3020";
		//	else if ( flag==12 ) bn="item/30/3021";
		return;
		if (TASK_LEGEND_D->check_task_item_amount(who, "Ác Quỷ(vương)") < 150)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nVậy là ngươi không có 150 Ác Quỷ(vương)? Vậy đến đây làm gì vậy !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}

		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nHành trang của ngươi không đủ 1 ô trống !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Ác Quỷ(vương)", 150);
		if (random100() < 80)
			item = new ("item/sell/5032");
		else
			notify("Ghép thất bại, xin chia buồn cùng các hạ!");
		if (item)
		{
			p = item->move2(who, -1);
			item->add_to_user(p);
			send_user(who, "%c%s", ';', "Bạn đã thành công đổi được " + item->get_name() + ", xin chúc mừng !");
			CHAT_D->vip_channel(0, sprintf("Chúc mừng " HIR "" + who->get_name() + " " NOR "đã đổi thành công " HIY "%s" NOR "!", item->get_name()));
		}
		break;
	case 3:
		return;
		//   if ( flag==11 ) bn="item/30/3020";
		//	else if ( flag==12 ) bn="item/30/3021";
		if (TASK_LEGEND_D->check_task_item_amount(who, "Ác Quỷ(vương)") < 200)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nVậy là ngươi không có 200 Ác Quỷ(vương)? Vậy đến đây làm gì vậy !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}

		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nHành trang của ngươi không đủ 1 ô trống !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Ác Quỷ(vương)", 200);
		if (random100() < 35)
			item = new ("item/sell/4032");
		else
			notify("Ghép thất bại, xin chia buồn cùng các hạ!");
		if (item)
		{
			p = item->move2(who, -1);
			item->add_to_user(p);
			send_user(who, "%c%s", ';', "Bạn đã thành công đổi được " + item->get_name() + ", xin chúc mừng !");
			CHAT_D->vip_channel(0, sprintf("Chúc mừng " HIR "" + who->get_name() + " " NOR "đã đổi thành công " HIY "%s" NOR "!", item->get_name()));
		}
		break;
	case 4:
		return;
		//   if ( flag==11 ) bn="item/30/3020";
		//	else if ( flag==12 ) bn="item/30/3021";
		if (TASK_LEGEND_D->check_task_item_amount(who, "Ác Quỷ(vương)") < 100)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nVậy là ngươi không có 100 Ác Quỷ(vương)? Vậy đến đây làm gì vậy !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}

		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nHành trang của ngươi không đủ 1 ô trống !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Ác Quỷ(vương)", 100);

		item = new ("item/91/9167_2");

		if (item)
		{
			item->set_amount(15);
			p = item->move2(who, -1);
			item->add_to_user(p);
			send_user(who, "%c%s", ';', "Bạn đã thành công đổi được " + item->get_name() + ", xin chúc mừng !");
			CHAT_D->vip_channel(0, sprintf("Chúc mừng " HIR "" + who->get_name() + " " NOR "đã đổi thành công " HIY "%s" NOR "!", item->get_name()));
		}
		break;
	case 5:
		return;
		//   if ( flag==11 ) bn="item/30/3020";
		//	else if ( flag==12 ) bn="item/30/3021";
		if (TASK_LEGEND_D->check_task_item_amount(who, "Ác Quỷ(vương)") < 100)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nVậy là ngươi không có 100 Ác Quỷ(vương)? Vậy đến đây làm gì vậy !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}

		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Phàm Chân:\nHành trang của ngươi không đủ 1 ô trống !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Ác Quỷ(vương)", 100);

		item = new ("item/test/pyktanthu");

		if (item)
		{
			item->set_amount(40);
			p = item->move2(who, -1);
			item->add_to_user(p);
			send_user(who, "%c%s", ';', "Bạn đã thành công đổi được " + item->get_name() + ", xin chúc mừng !");
			CHAT_D->vip_channel(0, sprintf("Chúc mừng " HIR "" + who->get_name() + " " NOR "đã đổi thành công " HIY "%s" NOR "!", item->get_name()));
		}
		break;
	}
}

void do_look(object player)
{
	object npc = this_object();

	send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "Cao Cấp Đoạn Thạch Kết Dính được đùng để đập trang bị nếu thất bại chỉ bị rớt 1 sao\n Siêu Cấp Đoạn Thạch để đập trang bị lên 7 sao với tỷ lệ 100%% \nCao Cấp Đoạn Thạch Đặc Biệt để đập trang bị lên 8 sao với tỷ lệ 100%%\n Tử Sâm Đơn để tăng tiềm năng \n PYK Tàn Thư Dùng để đổi Pháp Bảo Chân Tử Ấn và Bàn Đơn cho Huyễn Thú \n" ESC HIY "Dùng 70 điểm Ghép Cao Cấp Đoạn Thạch Bị Kết Dính(Tỷ lệ 90%%)\ntalk %x# welcome.1\n" ESC HIY "Dùng 150 điểm Ghép Siêu Cấp Đoạn Thạch(Tỷ lệ 80%%) \ntalk %x# welcome.2\n" ESC HIY "Dùng 200 điểm Ghép Cao Cấp Đoạn Thạch Đặc Biệt (Tỷ Lệ 35%%) \ntalk %x# welcome.3\n" ESC HIY "Dùng 100 điểm Ghép 15 Tử Sâm Đơn\ntalk %x# welcome.4\n" ESC HIY "Dùng 100 điểm Ghép 40 PYK Tàn Thư\ntalk %x# welcome.5\n" ESC HIY "Dùng 1300 Điểm Đổi Thú Cưỡi Vip\ntalk %x# welcome.10\n"

																			 ESC "Rời khỏi\nCLOSE\n",
																		 npc->get_name(), getoid(npc), getoid(npc), getoid(npc), getoid(npc), getoid(npc), getoid(npc), getoid(npc)));
}

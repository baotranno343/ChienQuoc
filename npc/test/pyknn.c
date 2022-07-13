
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数:获取人物造型
int get_char_picid() { return 8299; }
void do_welcome(string arg);
void do_bonus(string arg);

// 函数:构造处理
void create()
{
	set_name("Phòng Yêu Kính Nương Nương");
	set_2("talk", (["welcome":(
								  : do_welcome:),
					  "bonus":(
								  : do_bonus:),
	]));

	setup();
}

// 函数:对话处理
void do_look(object who)
{
	int id = getoid(this_object());
	send_user(who, "%c%s", ':', sprintf(get_name() + ":\n Long Ấn của thiên tử xem như chỉ có trong truyền thuyết, nhưng ngươi biết không? Nó có thật đấy, nếu mang cho ta đủ Phong yêu kính Tàn thư, ta có thể giúp người. Haha!\n"
											// ESC "Đổi tín vật Long Ấn ngoại công\ntalk %x# bonus.2\n"
											//	 ESC "Đổi tín vật Long Ấn nội công\ntalk %x# bonus.3\n"
											ESC "Đổi túi trang bị Huyết sắc\ntalk %x# bonus.4\n"
											// ESC "Đổi Thiên hỏa Thạch bàn đơn\ntalk %x# bonus.5\n"
											ESC "Rời khỏi\ntalk %x# welcome.2\n",
										id, id, id, id, id, id, id, id, id));
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int flag, id, p;
	object who, item;

	who = this_player();
	id = getoid(me);
	flag = to_int(arg);
	who->set_time("talk", 0);
	switch (flag)
	{
	case 1:
		break;
		/*	case 2:
			send_user(who,"%c%s",':',sprintf( get_name() + ":\n    Hoan nghênh! Vô Song Thành là thiên hạ đệ nhất đại thành với những bảo vật quý hiếm trên nhân gian, chỉ cần ngươi giao cho ta Vô Song Điểm Phiếu thì sẽ được tưởng thưởng hậu hĩ!\n"
				ESC"150 Sử dụng Vô Song Điểm Phiếu đổi Trang Phục Mùa Hè (Nữ)\ntalk %x# bonus.8\n"
				ESC"150 Sử dụng Vô Song Điểm Phiếu đổi Trang Phục Dạo Phố (Nam)\ntalk %x# bonus.9\n"
				ESC"Thoát\n",id,id));
			break;*/
	}
}

void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_object(), arg);
}

void do_bonus_2(object me, string arg)
{
	int flag, point, i, id, p;
	object who, item, item2;
	string cTmp, cFile;
	who = this_player();
	flag = to_int(arg);
	switch (flag)
	{
	case 1:
		break;
	// case 2:
	// 	send_user(who, "%c%s", ':', sprintf("Bạn có muốn dùng 999 Phong yêu kính Tàn thư đổi Long Ấn sát thương Ngoại không ??\n" ESC "Đồng ý\ntalk %x# bonus.12\n" ESC "Hủy bỏ", getoid(me)));
	// 	break;
	// case 3:
	// 	send_user(who, "%c%s", ':', sprintf("Bạn có muốn dùng 999 Phong yêu kính Tàn thư đổi Long Ấn sát thương Nội không ??\n" ESC "Đồng ý\ntalk %x# bonus.13\n" ESC "Hủy bỏ", getoid(me)));
	// 	break;
	case 4:
		send_user(who, "%c%s", ':', sprintf("Bạn có muốn dùng 500 Phong yêu kính Tàn thư đổi lấy Túi Huyết Sắc không ?\n" ESC "Đồng ý\ntalk %x# bonus.14\n" ESC "Hủy bỏ", getoid(me)));
		break;
		// case 5:
		// 	send_user(who, "%c%s", ':', sprintf("Bạn có muốn dùng 5 Phong yêu kính Tàn thư đổi lấy 1 viên Thiên hỏa Thạch bàn đơn không ?\n" ESC "Đồng ý\ntalk %x# bonus.15\n" ESC "Hủy bỏ", getoid(me)));
		// 	break;
		/*	case 6:
			send_user(who,"%c%s",':',sprintf( "Bạn muốn dùng 1200 Vô Song Điểm Phiếu đổi "HIR "Dùng cho Nam"NOR " Thánh Linh Chi Dực·Vàng Nhạt không?\n"
				ESC"xác định\ntalk %x# bonus.16\n"
				ESC"bỏ",getoid(me)));
			break;
		case 7:
			send_user(who,"%c%s",':',sprintf( "Bạn muốn dùng 1200 Vô Song Điểm Phiếu đổi "HIR "Dùng cho Nữ"NOR " Thánh Linh Chi Dực·Trắng Thuần không?\n"
				ESC"xác định\ntalk %x# bonus.17\n"
				ESC"bỏ",getoid(me)));
			break;
       	case 8:
			send_user(who,"%c%s",':',sprintf( "Bạn muốn dùng 150 Vô Song Điểm Phiếu đổi Trang Phục Mùa Hè (Nữ) không?\n"
				ESC"xác định\ntalk %x# bonus.18\n"
				ESC"bỏ",getoid(me)));
			break;
       	case 9:
			send_user(who,"%c%s",':',sprintf( "Bạn muốn dùng 150 Vô Song Điểm Phiếu đổi Trang Phục Dạo Phố (Nam) không?\n"
				ESC"xác định\ntalk %x# bonus.19\n"
				ESC"bỏ",getoid(me)));
			break;*/
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		// if (flag == 12)
		// {
		// 	point = 999;
		// 	cFile = "item/phapbaovip/ngoai";
		// }
		// else if (flag == 13)
		// {
		// 	point = 999;
		// 	cFile = "item/phapbaovip/noi";
		// }
		if (flag == 14)
		{
			point = 500;
			cFile = "item/test/tuihuyetsac";
		}
		// else if (flag == 15)
		// {
		// 	point = 5;
		// 	cFile = "item/huyenthu/exp";
		// }
		/*	else if ( flag == 16 )
			{
				point = 1200;
				cFile = "item/30/3031";
			}
			else if ( flag == 17 )
			{
				point = 1200;
				cFile = "item/30/3028";
			}
			else if ( flag == 18 )
			{
				point = 150;
				cFile = "item/100/11051";
			}
			else if ( flag == 19 )
			{
				point = 150;
				cFile = "item/100/10051";
			}*/
		if (TASK_LEGEND_D->check_task_item_amount(who, "Phong Yêu Kính Tàn Thư") < point)
		{
			write_user(who, sprintf(ECHO "Ngươi không có đủ %d Phong Yêu Kính Tàn Thư !", point));
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Phong Yêu Kính Tàn Thư", point);
		item = new (cFile);
		i = item->move2(who, -1);
		if (!i)
		{
			destruct(item);
			return;
		}
		item->add_to_user(i);
		send_user(who, "%c%s", ';', "Bạn nhận được " HIY + item->get_name());
		break;
	}
}
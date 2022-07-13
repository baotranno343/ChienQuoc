#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;
// private
// static object *chiSoArr;
// 函数：获取人物造型
int get_char_picid() { return 9956; }
void do_welcome(string arg);
void check_duc_lo(string arg);
void duc_lo(string arg);
object *check_chiso(object item, string arg);
void create()
{
	set_name("Chiết Xuất Trang Bị");
	set_real_name("Bồ Nguyên");
	set_2("talk", (["welcome":(
								  : do_welcome:),
					  "check_duc_lo":(
										 : check_duc_lo:),
							"duc_lo":(
										 : duc_lo:),

	]));
	setup();
}

void do_welcome(string arg)
{
	__FILE__->do_welcome2(this_object(), arg);
}
void do_welcome2(object npc, string arg)
{
	int flag;
	object player = this_player();
	flag = to_int(arg);
	switch (flag)
	{
	case 1:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf(npc->get_name() + ":\n" + "Chiết Xuất là việc cần thiết để nâng cao thuộc tính trang bị, gia tăng sức mạnh nhân vật.  ?\n" ESC "Alt + G để giao trang bị\ntalk %x# welcome.2\n" ESC "Thoát ra\nCLOSE\n", getoid(npc)));
		break;
	case 2:
		send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), npc->get_name() + ":\n" + "Sử dụng Alt + G để đưa trang bị cho ta !\n" ESC "Ta hiểu rồi\nCLOSE\n" ESC "Thoát ra\nCLOSE\n");
		break;
	}
}
void do_look(object player)
{
	object npc = this_object();

	send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), sprintf("%s :\n" + "Ta chính là thợ Chiết Xuất cho trang bị trong Chiến Quốc. Tuy nhiên Chiết Xuất trang bị tốn rất nhiều chi phí, thế nào, nhà ngươi có trang bị nào tốt cần Chiết Xuất khảm nạm không? Hãy đưa ta xem !\n" ESC "Tìm hiểu Chiết Xuất trang bị\ntalk %x# welcome.1\n" ESC "Rời khỏi\nCLOSE\n", npc->get_name(), getoid(npc), getoid(npc)));
}

int accept_object(object who, object item) { return __FILE__->accept_object_callout(this_object(), who, item); }

// 函数:接受物品(在线更新)
int accept_object_callout(object me, object who, object item)
{
	me->to_front_eachother(who);
	me->set("id_item", sprintf("%x#", getoid(item)));
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
			  sprintf("Bồ Nguyên:\n Ngươi muốn Chiết Xuất ?\n" ESC "Chiết Xuất Thanh Đồng\ntalk %x# check_duc_lo.chietxuat1\n" ESC "Chiết Xuất Bạch Kim\ntalk %x# check_duc_lo.chietxuat2\n" ESC "Chiết Xuất Hoàng Kim\ntalk %x# check_duc_lo.chietxuat3\n" ESC "Huỷ bỏ", getoid(me), getoid(me), getoid(me)));
	return -99;
}
// 函数:接受物品
void check_duc_lo(string arg) { return __FILE__->check_duc_lo_callout(this_object(), this_player(), arg); }
// 函数:接受物品(在线更新)
void check_duc_lo_callout(object me, object who, string arg)
{
	object item;

	if (!objectp(item = present(me->get("id_item"), who, 1, MAX_CARRY * 4)))
		return 0;
	if (arg == "chietxuat1")
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Bạn có muốn gỡ và hủy bảo thạch ở lỗ 1 không ?\n" ESC "Xác nhận\ntalk %x# duc_lo.chietxuat1\n" ESC "Huỷ bỏ", getoid(me), getoid(item)));
	}
	if (arg == "chietxuat2")
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Bạn có muốn gỡ và hủy bảo thạch ở lỗ 2 không ?\n" ESC "Xác nhận\ntalk %x# duc_lo.chietxuat2\n" ESC "Huỷ bỏ", getoid(me), getoid(item)));
	}
	if (arg == "chietxuat3")
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Bạn có muốn gỡ và hủy bảo thạch ở lỗ 3 không ?\n" ESC "Xác nhận\ntalk %x# duc_lo.chietxuat3\n" ESC "Huỷ bỏ", getoid(me), getoid(item)));
	}

	return 0;
}
// Bla bla
void duc_lo(string arg) { return __FILE__->duc_lo_callout(this_object(), this_player(), arg); }
// Bla bla
void duc_lo_callout(object me, object who, string arg)
{
	int level, i, knb, nl, dct, p;
	object item, item2, *chiSoArr;
	string x, *y;
	if (!objectp(item = present(me->get("id_item"), who, 1, MAX_CARRY * 4)))
		return 0;
	if (!item->is_equip())
		return 0;
	if (item->is_equip())
	{
		level = item->get_level();
		i = item->get_equip_type();
		if (i != WEAPON_TYPE && i != ARMOR_TYPE && i != HEAD_TYPE && i != BOOTS_TYPE && i != WAIST_TYPE && i != NECK_TYPE)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bồ Nguyên:\n Thứ ngươi giao cho ta không phải là trang bị hoặc vũ khí !\n" ESC "Xác nhận");
			return 0;
		}
		if (item->get("make"))
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bồ Nguyên:\n Trang bị đã khảm linh thạch không thể chiết xuất !\n" ESC "Xác nhận");
			return 0;
		}
		if (item->get_item_color() == 3)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bồ Nguyên:\n Không được chiết xuất trang bị tử kim !\n" ESC "Xác nhận");
			return 0;
		}
	}
	if (who->get_cash() < 100000)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Không đủ %d ngân lượng để chiết xuất trang bị!\n" ESC "Xác nhận", 100000));
		return 0;
	}
	if ("/sys/sys/test_db"->get_yuanbao(who) < 1000)
	{
		send_user(who, "%c%s", '!', "KNB của bạn không đủ 100");
		return 0;
	}
	if (item->get("chietxuat"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), "Bồ Nguyên:\n Trang bị này đã sử dụng chiết xuất !\n" ESC "Xác nhận");
		return 0;
	}

	if (arg == "chietxuat1")
	{

		if (TASK_LEGEND_D->check_task_item_amount(who, "Búa Thanh Đồng") < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Ngươi không có Búa Thanh Đồng !\n" ESC "Xác nhận"));
			return 0;
		}

		chiSoArr = check_chiso(item, arg);
	}
	if (arg == "chietxuat2")
	{

		if (TASK_LEGEND_D->check_task_item_amount(who, "Búa Bạch Kim") < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Ngươi không có Búa Bạch Kim !\n" ESC "Xác nhận"));
			return 0;
		}

		chiSoArr = check_chiso(item, arg);
	}
	if (arg == "chietxuat3")
	{

		if (TASK_LEGEND_D->check_task_item_amount(who, "Búa Hoàng Kim") < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("Ngươi không có Búa Hoàng Kim !\n" ESC "Xác nhận"));
			return 0;
		}

		chiSoArr = check_chiso(item, arg);
	}
	if (sizeof(chiSoArr) != 0)
	{
		switch (arg)
		{
		case "chietxuat1":
			TASK_LEGEND_D->check_task_item1(who, "Búa Thanh Đồng", 1);
			break;
		case "chietxuat2":
			TASK_LEGEND_D->check_task_item1(who, "Búa Bạch Kim", 1);
			break;
		case "chietxuat3":
			TASK_LEGEND_D->check_task_item1(who, "Búa Hoàng Kim", 1);
			break;

		default:
			return 0;
			break;
		}
		x = sprintf("%s", chiSoArr[random(sizeof(chiSoArr))]);
		if (x)
		{
			y = explode(x, ":");
			item2 = new ("tran/chietxuat/dachietxuat");
			item2->set(y[0], to_int(y[1]));
			p = item2->move2(who, -1);
			item2->add_to_user(p);
			item->remove_from_user();
			destruct(item);
			"/sys/sys/test_db"->add_yuanbao(who, -1000);
			who->add_cash(-100000);
			tell_user(who, "Bạn Đã Chiết Xuất Trang Bị Thành Công!");
		}
	}
	else
	{
		tell_user(who, "Không tìm thấy chỉ số cần chiết xuất");
	}
	return 0;
}

object *check_chiso(object item, string arg)
{
	int x;
	string y;
	object *chiso;
	string *list;
	string *list1 = ({"ap", "cp", "dp", "pp", "hp"});
	string *list2 = ({"sp", "!%", "double", "-*", "-c*"});
	string *list3 = ({"?%",
					  "double",
					  "hp*",
					  "mp*",
					  "-*%",
					  "-c*%",
					  "t!%", "c!%"});
	chiso = ({});
	if (item)
	{
		switch (arg)
		{
		case "chietxuat1":
			list = list1;
			break;
		case "chietxuat2":
			list = list2;
			break;
		case "chietxuat3":
			list = list3;
			break;
		default:
			return 0;
			break;
		}
		foreach (y in list)
		{
			if (x = item->get(y))
			{
				chiso += ({y + ":" + x});
			}
		}
	}
	if (sizeof(chiso) != 0)
	{
		// chiSoArr = chiso;
		return chiso;
	}
	return 0;
}
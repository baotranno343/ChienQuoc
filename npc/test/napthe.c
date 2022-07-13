#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
#include <time.h>
inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 5302; }
void do_accept(string arg);
void capnhat();
void codetanthu();
void create()
{
	set_name("Nạp Kim Nguyên Bảo");
	set_2("talk", (["capnhat":(
								  : capnhat:),
					  "codetanthu":(
									   : codetanthu:),

	]));

	setup();
}

void capnhat()
{
	object npc = this_object();
	object me = this_player();
	string tong = "\n", arg1, arg2, arg3, *line;
	int x, i, j, n, l = 0, check = 0;
	if (!file_exist("napthe.txt"))
	{
		printf("Không tìm thấy file");
		return;
	}
	line = explode(read_file("napthe.txt"), "\n");
	if (sizeof(line) == 0)
	{
		printf("Chưa có dữ liệu");
		return;
	}
	for (i = 0; i < sizeof(line); i++)
	{
		if (sscanf(line[i], "%s:%s:%s", arg1, arg2, arg3) == 3)
		{
			if (to_int(arg2) == me->get_number())
			{
				line[i] = "";
				check = 2;
				//((to_int(arg3) / 10) + (20 * to_int(arg3) / 1000)) KM 20 %
				"sys/sys/test_db"->add_yuanbao(me, ((to_int(arg3) / 10) + (20 * to_int(arg3) / 1000)));
				if (to_int(arg3) >= 100000)
					me->add_cash(to_int(arg3) * 20);
				tell_user(me, sprintf("Nạp thành công số tiền %d, vui lòng kiểm tra số dư tại Trân Bảo Khố.", to_int(arg3)));
				log_file("napthe.txt", sprintf("%s , ID: %d đã nạp thành công số tiền %d \n", short_time(time()), me->get_number(), to_int(arg3)));
				break;
			}
		}
	}
	if (check == 2)
	{
		for (i = 0; i < sizeof(line); i++)
		{
			if (line[i] == "")
				continue;
			tong = tong + line[i] + "\n";
		}
		rm("napthe.txt");
		ghi_file("napthe.txt", tong);
	}

	else
	{
		printf("Bạn chưa nạp thẻ");
	}

	return;
}
void codetanthu()
{
	object me = this_object();
	object who = this_player();
	string *line;
	int i;
	if (file_exist("log/tanthu.txt"))
	{

		line = explode(read_file("log/tanthu.txt"), "\n");
		for (i = 0; i < sizeof(line); i++)
		{
			if (to_int(line[i]) == who->get_number())
			{
				printf("Bạn đã nhận code Tân Thủ rồi");
				return;
			}
		}
	}
	if (who->get_fam_name() == "")
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(),
				  sprintf(" %s :\n Ngươi chưa gia nhập Môn phái, không thể nhập Code Tân Thủ !\n" ESC HIY "Ta hiểu rồi\ntalk %x# gift.1002\n" ESC "Huỷ bỏ\nCLOSE\n", me->get_name(), getoid(me)));
		return;
	}
	if (who->get_level() > 105)
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(),
				  sprintf(" %s :\n Trên cấp 105 không thể nhập Code Tân Thủ !\n" ESC HIY "Ta hiểu rồi\ntalk %x# gift.1002\n" ESC "Huỷ bỏ\nCLOSE\n", me->get_name(), getoid(me)));
		return;
	}
	if (USER_INVENTORY_D->get_free_count(who) < 10)
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(),
				  sprintf(" %s :\n Hành trang không đủ 10 chỗ trống !\n" ESC HIY "Ta hiểu rồi\ntalk %x# gift.1002\n" ESC "Huỷ bỏ\nCLOSE\n", me->get_name(), getoid(me)));
		return;
	}
	send_user(who, "%c%c%d%s", '?', 16, 15, "Xin nhập mã Code Tân Thủ    (Tối đa 15 ký tự):\n" ESC "codetanthu + %s\n");
	return;
}
void do_look(object player)
{
	object npc = this_object();
	string lo, de, result = "";
	int size, i;
	result += "Nhấn vào cập nhật để xác nhận nạp Nguyên bảo!";
	result += "\n";
	result += sprintf(ESC "Cập nhật\ntalk %x# capnhat\n", getoid(npc));
	result += sprintf(ESC "Nhập Code Tân Thủ\ntalk %x# codetanthu\n", getoid(npc));

	send_user(player, "%c%c%w%s", ':', 3, npc->get_char_picid(), result);
}
// 函数:接受物品
int accept_object(object who, object item) { return __FILE__->accept_object_callout(this_object(), who, item); }

// 函数:接受物品(在线更新)
int accept_object_callout(object me, object who, object item)
{
	int ngay, de, lo, i, n, tien, xi1, xi2, xi3, xi;
	string file, x1, x2, x3, *x;
	me->to_front_eachother(who);

	return -99;
}
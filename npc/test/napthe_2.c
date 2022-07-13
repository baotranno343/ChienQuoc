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
void capnhat2()
{
	object npc = this_object(), item;
	object me = this_player();
	string tong = "\n", arg1, arg2, arg3, *line;
	int x, p, i, j, n, l = 0, check = 0;
	if (!file_exist("quayso.txt"))
	{
		printf("Không tìm thấy file");
		return;
	}
	line = explode(read_file("quayso.txt"), "\n");
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
				if (USER_INVENTORY_D->get_free_count(me) < 2)
				{
					send_user(me, "%c%s", '!', "Hành trang không đủ 2 chỗ.");
					return 0;
				}
				switch (arg3)
				{
				case "item/hoahongchithach":
					item = new ("item/04/0438");
					if (item)
						return;
					item->set_amount(1);
					p = item->move2(me, -1);
					item->add_to_user(p);
					break;

				default:
					return;
					break;
				}
				tell_user(me, sprintf("Bạn đã nhận được %s từ Vòng Quay May Mắn, vui lòng kiểm tra lại túi", item->get_name()));
				log_file("quayso.txt", sprintf("%s , ID: %d đã nhận quà quay số thành công quà: %s \n", short_time(time()), me->get_number(), item->get_name()));
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
		rm("quayso.txt");
		ghi_file("quayso.txt", tong);
	}
	else
	{
		printf("Bạn chưa có quà quay số");
	}

	return;
}
void do_look(object player)
{
	object npc = this_object();
	string lo, de, result = "";
	int size, i;
	result += "Nhấn vào cập nhật để xác nhận nạp Nguyên bảo!";
	result += "\n";
	result += sprintf(ESC "Nhận KNB\ntalk %x# capnhat\n", getoid(npc));
	result += sprintf(ESC "Nhận Quà Quay Số\ntalk %x# capnhat2\n", getoid(npc));

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
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{

	int p, cap, cap1, exist = 1, i, size, q;
	string tong = "\n", result, arg2, arg3, *line, *data, file;
	object item, item1, who;

	if (!arg)
		return 1;
	if (arg == 0)
		return 1;
	if (me->get_save("codetanthu"))
	{
		send_user(me, "%c%s", ';', "Bạn đã nhận code tân thủ rồi");
		write_user(me, ECHO "Bạn đã nhận code tân thủ rồi");
		return 1;
	}
	if (me->get_level() < 10)
	{
		send_user(me, "%c%s", ';', sprintf("Cấp bậc %d nhỏ hơn 10, không thể nhập Code Tân Thủ.", me->get_level()));
		write_user(me, sprintf(ECHO "Cấp bậc %d nhỏ hơn 10, không thể nhập Code Tân Thủ.", me->get_level()));
		return 1;
	}
	if (me->get_fam_name() == "")
	{
		send_user(me, "%c%s", ';', "Vô Môn Phái không thể nhập Code Tân Thủ.");
		write_user(me, ECHO "Vô Môn Phái không thể nhập Code Tân Thủ.");
		return 1;
	}
	if (USER_INVENTORY_D->get_free_count(me) < 5)
	{
		send_user(me, "%c%s", ';', "Hành trang không đủ 10 chỗ trống !.");
		write_user(me, ECHO "Hành trang không đủ 10 chỗ trống !");

		return 1;
	}
	// 20 code
	if (sscanf(arg, "+ %s", arg2) != 1)
		return 1;

	if (!file_exist("giftcode.txt"))
	{
		printf("Không tìm thấy file");
		return 1;
	}
	file = read_file("giftcode.txt");
	line = explode(file, "\n");
	if (sizeof(line) == 0)
	{
		printf("Chưa có dữ liệu");
		return 1;
	}
	for (i = 0, size = sizeof(line); i < size; i++)
	{
		if (line[i] == arg2)
		{
			line[i] = "";
			exist = 0;
			break;
		}
	}
	if (exist >= 1)
	{
		send_user(me, "%c%s", ';', "Bạn đã nhập sai Code Tân Thủ.");
		write_user(me, ECHO "Bạn đã nhập sai Code Tân Thủ.");
		return 1;
	}
	else
	{
		for (i = 0, size = sizeof(line); i < size; i++)
		{
			if (line[i] == "")
				continue;
			tong = tong + line[i] + "\n";
		}
		rm("giftcode.txt");
		ghi_file("giftcode.txt", tong);
		//	log_file("giftcode.txt", sprintf("%s , ID: %d đã nhận code Tân Thủ Thành Công\n", short_time(time()), me->get_number()));
		me->set_save("codetanthu", 1);
		item = new ("ken/hotrotanthu/tuiquatanthu");
		q = item->move2(me, -1);
		item->add_to_user(q);
		send_user(me, "%c%s", ';', HIY "Bạn đã nhận phần thưởng từ Code Tân Thủ thành công !");
		return 1;
	}

	return 1;
}
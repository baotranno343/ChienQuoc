#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{

	int p, cap, exist, exist2, i, size, knb;
	string result, arg2, arg3, arg4, *line, *data;
	object item, item1, who, *objs, target;

	return 1;
	if (!arg)
		return 1;
	if (arg == 0)
		return 1;
	if (sscanf(arg, "- %s", arg2) == 1)
	{
		if (arg2 && !(who = find_any_char(arg2)))
		{
			write_user(me, ECHO "Không tìm thấy người này !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nKhông thể tìm thấy người này, hãy chắc chắn rằng người đó đang trực tuyến ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		if (who == me)
		{
			write_user(me, ECHO "Không thể tự chuyển cho chính mình !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nKhông thể tự chuyển Kim Bảo cho chính mình ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		send_user(me, "%c%c%d%s", '?', 16, 10, "Bạn muốn chuyển bao nhiêu Ngân Bảo tới người chơi có số ID " + arg2 + " : \n" ESC "chuyenknb ? " + arg2 + " %s\n");
	}
	else if (sscanf(arg, "? %s %d", arg2, knb) == 2)
	{
		if (arg2 && !(who = find_any_char(arg2)))
		{
			write_user(me, ECHO "Không tìm thấy người này !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nKhông thể tìm thấy người này, hãy chắc chắn rằng người đó đang trực tuyến ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		if (who == me)
		{
			write_user(me, ECHO "Không thể tự chuyển cho chính mình !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nKhông thể tự chuyển Kim Bảo cho chính mình ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		if ("sys/sys/test_db"->get_yuanbao(me) < knb)
		{
			write_user(me, ECHO "Số lượng Ngân Bảo cần chuyển nhiều hơn số Ngân Bảo hiện có của bạn !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nMgân Bảo của bạn không đủ để chuyển ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		if (knb < 10)
		{
			write_user(me, ECHO "Số lượng Ngân Bảo cần chuyển phải nhiều hơn 10 !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nMgân Bảo muốn chuyển phải là số lớn hơn 10 ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		if (knb > 10000)
		{
			write_user(me, ECHO "Số lượng Ngân Bảo cần chuyển không được lớn hơn 10.000 !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nMgân Bảo muốn chuyển không được lớn hơn 10.000 ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		result = sprintf("Nhân viên chuyển Kim Bảo : \nBạn muốn chuyển " HIR "%d Ngân Bảo (%d KNB)" NOR " cho người chơi " HIR "%s (%d)" NOR " phải không? \n Phí chuyển là:" HIR " %d Ngân Bảo (%d KNB) !\n", knb, knb / 10, who->get_name(), who->get_number(), knb * 5 / 100, (knb * 5 / 100) / 10);
		result += sprintf(ESC "Xác nhận\nchuyenknb + %s %d\n", arg2, knb);
		result += ESC "Hủy bỏ\n";
		send_user(me, "%c%c%w%s", ':', 3, 5302, result);
	}
	else if (sscanf(arg, "+ %s %d", arg2, knb) == 2)
	{
		if (arg2 && !(who = find_any_char(arg2)))
		{
			write_user(me, ECHO "Không tìm thấy người này !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nKhông thể tìm thấy người này, hãy chắc chắn rằng người đó đang trực tuyến ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		if (who == me)
		{
			write_user(me, ECHO "Không thể tự chuyển cho chính mình !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nKhông thể tự chuyển Kim Bảo cho chính mình ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		if ("sys/sys/test_db"->get_yuanbao(me) < knb + (knb * 5 / 100))
		{
			write_user(me, ECHO "Số lượng Ngân Bảo cần chuyển nhiều hơn số Ngân Bảo hiện có của bạn sau khi tính phí 5%% !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nMgân Bảo của bạn không đủ để chuyển sau khi tính phí 5%% ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		if (knb < 10)
		{
			write_user(me, ECHO "Số lượng Ngân Bảo cần chuyển phải nhiều hơn 10 !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nMgân Bảo muốn chuyển phải là số lớn hơn 10 ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		if (knb > 10000)
		{
			write_user(me, ECHO "Số lượng Ngân Bảo cần chuyển không được lớn hơn 10.000 !");
			send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nMgân Bảo muốn chuyển không được lớn hơn 10.000 ! \n" ESC "Xác nhận\nCLOSE");
			return 1;
		}
		"sys/sys/test_db"->add_yuanbao(who, knb);
		"sys/sys/test_db"->add_yuanbao(me, -(knb + (knb * 5 / 100)));
		log_file("chuyenknb.txt", sprintf("%s : %s (%d) đã chuyển %d Ngân Bảo (%d KNB) cho người chơi %s có số id %d\n", short_time(time()), me->get_name(), me->get_number(), knb, knb / 10, who->get_name(), who->get_number()));
		send_user(me, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nBạn đã chuyển " + knb + " Ngân Bảo (" + knb / 10 + " KNB) cho người chơi " + who->get_name() + " (" + who->get_number() + "), xin kiểm tra tài khoản của mình ! \n" ESC "Xác nhận\nCLOSE");
		send_user(who, "%c%c%w%s", ':', 3, 5302, "Nhân viên chuyển Kim Bảo : \nBạn đã nhận được " + knb + " Ngân Bảo (" + knb / 10 + " KNB) do người chơi " + me->get_name() + " (" + me->get_number() + ") chuyển vào, xin kiểm tra tài khoản của mình ! \n" ESC "Xác nhận\nCLOSE");
		write_user(me, sprintf(ECHO "Bạn đã chuyển %d Ngân Bảo (%d KNB) cho người chơi %s (%d).", knb, knb / 10, who->get_name(), who->get_number()));
		write_user(who, sprintf(ECHO "Bạn đã nhận được %d Ngân Bảo (%d KNB) do người chơi %s (%d) chuyển vào.", knb, knb / 10, me->get_name(), me->get_number()));
	}
	return 1;
}
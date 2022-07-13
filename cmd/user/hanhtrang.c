#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
#define HANHTRANG "hanhtrang.txt"
string *ListPass = ({});
private
void load_pass();
private
void load_pass()
{
	string *line, result;
	int i, size;

	line = explode(read_file(HANHTRANG), "\n");

	for (i = 0, size = sizeof(line); i < size; i++)
	{
		ListPass += ({line[i]});
	}
}
int set_pass(string old_data, string new_data)
{
	string id, list;
	int i, size;
	ListPass = ({});
	load_pass();
	if (old_data != "")
		ListPass -= ({old_data});
	if (new_data != "")
		ListPass += ({new_data});

	list = "";
	size = sizeof(ListPass);
	for (i = 0; i < size; i++)
		list += ListPass[i] + "\n";
	rm(HANHTRANG);
	write_file(HANHTRANG, list);

	return 1;
}
int main(object me, string arg)
{

	int p, cap, exist, exist2, i, size, tontai;
	string result, arg2, arg3, arg4, *line, *data, ten, num, pass, doc, doc2;
	object item, item1, who, *objs, target;

	if (!arg)
		return 1;
	if (arg == 0)
		return 1;
	line = explode(read_file(HANHTRANG), "\n");
	if (sscanf(arg, "+ %s", arg2) == 1)
	{
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		for (i = 0, size = sizeof(line); i < size; i++)
		{
			data = explode(line[i], " ");
			if (data[0] == me->get_name())
			{
				tontai = 1;
				ten = data[0];
				num = data[1];
				pass = data[2];
			}
		}
		if (!me->get_save("passhanhtrang"))
		{
			if (strlen(arg2) < 6 || strlen(arg2) > 12)
			{
				send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Mật khẩu bảo vệ Hành trang phải từ 6-12 ký tự");
				return 1;
			}
			for (i = 0; i < strlen(arg2); i++)
			{
				if ((arg2[i] < 'a' || arg2[i] > 'z') && (arg2[i] < 'A' || arg2[i] > 'Z') && arg2[i] != '-' && arg2[i] != '_' && (arg2[i] < '0' || arg2[i] > '9'))
				{
					send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Mật khẩu bảo vệ Hành trang không được chứa ký tự  đặc biệt , khoảng trống , tiếng việt có dấu.");
					return 1;
				}
			}
			result = sprintf("Bạn muốn thiết lập " HIR "%s " NOR "làm Mật khẩu bảo vệ Hành trang không? \n", arg2);
			result += sprintf(ESC "Xác nhận\nhanhtrang ? %s\n", arg2);
			result += ESC "Hủy bỏ\n";
			send_user(me, "%c%s", ':', result);
		}
		else
		{
			if (me->get_save("ndmkhtk") >= 1)
			{
				if (strlen(arg2) < 6 || strlen(arg2) > 12)
				{
					send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Mật khẩu bảo vệ Hành trang phải từ 6-12 ký tự");
					return 1;
				}
				for (i = 0; i < strlen(arg2); i++)
				{
					if ((arg2[i] < 'a' || arg2[i] > 'z') && (arg2[i] < 'A' || arg2[i] > 'Z') && arg2[i] != '-' && arg2[i] != '_' && (arg2[i] < '0' || arg2[i] > '9'))
					{
						send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Mật khẩu bảo vệ Hành trang không được chứa ký tự  đặc biệt , khoảng trống , tiếng việt có dấu.");
						return 1;
					}
				}
				result = sprintf("Bạn muốn thiết lập " HIR "%s " NOR "làm Mật khẩu bảo vệ Hành trang mới không? \n", arg2);
				result += sprintf(ESC "Xác nhận\nhanhtrang ? %s\n", arg2);
				result += ESC "Hủy bỏ\n";
				send_user(me, "%c%s", ':', result);
			}
			else
			{
				send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa nhập Mật khẩu bảo vệ cũ.");
			}
		}
		return 1;
	}
	else if (sscanf(arg, "? %s", arg2) == 1)
	{
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		for (i = 0, size = sizeof(line); i < size; i++)
		{
			data = explode(line[i], " ");
			if (data[0] == me->get_name())
			{
				tontai = 1;
				ten = data[0];
				num = data[1];
				pass = data[2];
			}
		}
		if (!me->get_save("passhanhtrang"))
		{
			if (strlen(arg2) < 6 || strlen(arg2) > 12)
			{
				send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Mật khẩu bảo vệ Hành trang phải từ 6-12 ký tự");
				return 1;
			}
			for (i = 0; i < strlen(arg2); i++)
			{
				if ((arg2[i] < 'a' || arg2[i] > 'z') && (arg2[i] < 'A' || arg2[i] > 'Z') && arg2[i] != '-' && arg2[i] != '_' && (arg2[i] < '0' || arg2[i] > '9'))
				{
					send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Mật khẩu bảo vệ Hành trang không được chứa ký tự  đặc biệt , khoảng trống , tiếng việt có dấu.");
					return 1;
				}
			}
			me->set_save("passhanhtrang", arg2);
			doc2 = me->get_name() + " " + me->get_number() + " " + arg2;
			__FILE__->set_pass("", doc2);
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn đã đặt Mật khẩu bảo vệ Hành trang !");
			send_user(me, "%c%c%d%s", 0x43, 10, 0, sprintf(HIR "Mật khẩu Hành trang của bạn : %s", arg2));
		}
		else
		{
			if (me->get_save("ndmkhtk") >= 1)
			{
				if (strlen(arg2) < 6 || strlen(arg2) > 12)
				{
					send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Mật khẩu bảo vệ Hành trang phải từ 6-12 ký tự");
					return 1;
				}
				for (i = 0; i < strlen(arg2); i++)
				{
					if ((arg2[i] < 'a' || arg2[i] > 'z') && (arg2[i] < 'A' || arg2[i] > 'Z') && arg2[i] != '-' && arg2[i] != '_' && (arg2[i] < '0' || arg2[i] > '9'))
					{
						send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Mật khẩu bảo vệ Hành trang không được chứa ký tự  đặc biệt , khoảng trống , tiếng việt có dấu.");
						return 1;
					}
				}
				if (tontai < 1)
				{
					send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa có Mật khẩu bảo vệ Hành trang.");
					return 1;
				}
				me->set_save("passhanhtrang", arg2);
				doc = ten + " " + num + " " + pass;
				doc2 = ten + " " + num + " " + arg2;
				__FILE__->set_pass(doc, doc2);
				me->set_save("ndmkhtk", 0);
				send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn đã đổi Mật khẩu bảo vệ Hành trang !");
				send_user(me, "%c%c%d%s", 0x43, 10, 0, sprintf(HIR "Mật khẩu Hành trang của bạn : %s", arg2));
			}
			else
			{
				send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa nhập Mật khẩu bảo vệ cũ.");
			}
		}
		return 1;
	}
	else if (sscanf(arg, "@ %s", arg2) == 1)
	{
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		for (i = 0, size = sizeof(line); i < size; i++)
		{
			data = explode(line[i], " ");
			if (data[0] == me->get_name())
			{
				tontai = 1;
				ten = data[0];
				num = data[1];
				pass = data[2];
			}
		}
		if (tontai < 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa có Mật khẩu bảo vệ Hành trang.");
			return 1;
		}
		if (me->get_name() == ten)
		{
			if (arg2 == me->get_save("passhanhtrang"))
			{
				if (arg2 == pass)
				{
					me->set_save("ndmkhtk", 1);
					send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn đã nhập đúng Mật khẩu bảo vệ Hành trang, bây giờ bạn có thể sử dụng Hành trang mà không cần phải nhập lại Mật khẩu cho đến khi bạn thoát khỏi trò chơi.");
					return 1;
				}
				else
				{
					send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn đã nhập sai Mật khẩu bảo vệ Hành trang.");
					return 1;
				}
			}
			else
			{
				send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn đã nhập sai Mật khẩu bảo vệ Hành trang.");
				return 1;
			}
		}
		return 1;
	}
	else if (sscanf(arg, "x %s", arg2) == 1)
	{
		for (i = 0, size = sizeof(line); i < size; i++)
		{
			data = explode(line[i], " ");
			if (data[0] == arg2)
			{
				tontai = 1;
				ten = data[0];
				num = data[1];
				pass = data[2];
			}
		}
		if (tontai < 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa có Mật khẩu bảo vệ Hành trang.");
			return 1;
		}
		if (!me->get_save("passhanhtrang"))
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa đặt Mật khẩu bảo vệ Hành trang.");
			return 1;
		}

		if (me->get_save("ndmkhtk") < 1)
		{
			if (me->get_save("quenmkht") > time())
			{
				send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Xin nhập vào Mật khẩu bảo vệ Hành trang.");
				return 1;
			}
		}
		if (arg2 == me->get_name())
		{
			me->delete_save("passhanhtrang");
			doc = ten + " " + num + " " + pass;
			__FILE__->set_pass(doc, "");
			me->delete_save("ndmkhtk");
			me->delete_save("quenmkht");
			send_user(me, "%c%s", ';', "Bạn đã xoá Mật khẩu bảo vệ Hành trang thành công !");
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn đã xoá Mật khẩu bảo vệ Hành trang.");
		}
		return 1;
	}
	else if (sscanf(arg, "kt %s", arg2) == 1)
	{
		if (!is_god(me))
			return 1;
		for (i = 0, size = sizeof(line); i < size; i++)
		{
			data = explode(line[i], " ");
			if (data[1] == arg2)
			{
				tontai = 1;
				ten = data[0];
				num = data[1];
				pass = data[2];
			}
		}
		if (tontai < 1)
		{
			if (!ten)
				ten = "Người chơi này";
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR + ten + " chưa có Mật khẩu bảo vệ Hành trang.");
			return 1;
		}
		write_user(me, HIG "Mật khẩu bảo vệ Hành trang của " + ten + " (" + num + ") là:\n" + HIC + pass);
		return 1;
	}
	return 1;
}

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <equip.h>

#define THIS_PERFORM 00099
#define PF_START "00099"
#define PF_NAME "Mệnh lệnh Bảo Mật"

// 函数：获取描述
string get_desc(object me)
{
	return "[ " PF_NAME " ]\n Chức năng đặc biệt để thao tác về Bảo mật Hành trang.\n ";
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
	int gender, gender1, p, i, z;
	object item, map;
	string result, cmd1;
	map = get_map_object(get_z(me));
	// Start hạn chế
	if (!map)
		notify("Bạn đang đứng ở đâu?");
	else
	{
		if (map->get_client_id() == 888 || map->get_client_id() == 889)
		{
			notify("Bạn đang ở trong VST, không thể sử dụng chức năng này.");
			return 1;
		}
		if (map->get_client_id() == 885)
		{
			notify("Bạn đang ở trong Tỉ võ trường, không thể sử dụng chức năng này.");
			return 1;
		}
	}
	if (me->get_attack_mode() == 0 || me->get_attack_mode() == 2 || me->get_attack_mode() == 3)
	{
		notify("Bạn đang trong trạng thái PK, không thể sử dụng chức năng này.");
		return 1;
	}
	// End hạn chế
	if (arg == "")
	{
		result = sprintf("Chức năng bảo mật Hành trang : \n");
		if (me->get_save("quenmkht") > 0)
		{
			result += ESC "Kiểm tra tình hình gỡ bỏ mã bảo vệ\npf2 00099.ktquen\n";
			result += ESC "Đóng\n";
		}
		else if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
		{
			result += ESC "Mở khoá Hành trang\npf2 00099.mokhoa\n";
			result += ESC "Tôi quên mật khẩu bảo vệ rồi\npf2 00099.quen\n";
			result += ESC "Hủy bỏ\n";
		}
		else if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") >= 1)
		{
			result += ESC "Tiếp tục bảo vệ Hành Trang\npf2 00099.tieptuc\n";
			result += ESC "Đổi mật khẩu bảo vệ Hành trang\npf2 00099.doi\n";
			result += ESC "Xoá mật khẩu bảo vệ Hành trang\npf2 00099.xoa\n";
			result += ESC "Hủy bỏ\n";
		}
		else if (!me->get_save("passhanhtrang"))
		{
			result += ESC "Đặt mật khẩu bảo vệ Hành trang\npf2 00099.dat\n";
			result += ESC "Hủy bỏ\n";
		}
		send_user(me, "%c%s", ':', result);
		return 1; // me->get_save("ndmkhtk")
	}
	if (arg == "quen")
	{
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		if (!me->get_save("passhanhtrang") || me->get_save("ndmkhtk") >= 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa có mã hành trang hoặc bạn đã nhập mã hành trang .");
			return 1;
		}
		result = "Để hủy mã bảo vệ, bạn cần phải đợi ít nhất 72 giờ.Trong thời gian hủy mã bảo vệ bạn không thể tắt mệnh lệnh bảo vệ, bạn chắc chắn muốn hủy chứ\n";
		result += ESC "Tôi muốn hủy mã bảo vệ\npf2 00099.xnquen\n";
		result += ESC "Tôi muốn suy nghĩ lại\n";
		send_user(me, "%c%s", ':', result);
		//	"cmd/user/hanhtrang"->main(me,"x "+me->get_name());
		return 1;
	}
	if (arg == "xnquen")
	{
		if (!me->get_save("passhanhtrang") || me->get_save("ndmkhtk") >= 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa có mã hành trang hoặc bạn đã nhập mã hành trang .");
			return 1;
		}
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		result = "Bạn đã hủy mật khẩu bảo vệ, sau 72 giờ bạn vui lòng gửi lại yêu cầu gỡ bỏ mã bảo vệ một lần nữa để thực hiện xóa mã bảo vệ\n";
		result += ESC "Rời khỏi\n";
		send_user(me, "%c%s", ':', result);
		me->set_save("quenmkht", time() + (3600 * 72));
		//	send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR);
		// if (me->get_save("ndmkhtk") < 1)
		// {
		// 	send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn phải nhập Mật khẩu bảo vệ Hành trang vào mới có thể Xoá mật khẩu bảo vệ Hành trang.");
		// 	return 1;
		// }
		return 1;
	}
	if (arg == "ktquen")
	{
		if (!me->get_save("passhanhtrang") || me->get_save("ndmkhtk") >= 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa có mã hành trang hoặc bạn đã nhập mã hành trang .");
			return 1;
		}
		if (me->get_save("quenmkht") > time())
		{
			result = sprintf("Bạn còn %d giờ nữa mới có thể tiến hành hủy mã bảo vệ\n", (me->get_save("quenmkht") - time()) / 3600);
			result += ESC "Tôi không muốn hủy mã bảo vệ nữa\npf2 00099.huyquen\n";
			result += ESC "Tôi chỉ xem qua vậy thôi\n";
			send_user(me, "%c%s", ':', result);
		}
		//	send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR sprintf("Bạn còn %d giờ nữa mới có thể tiến hành hủy mã bảo vệ", me->get_save("quenmkht")));
		else
		{
			result = "Bạn đã đợi đủ 72 giờ, mã bảo vệ của bạn đã được hủy thành công\n";
			result += ESC "Đồng ý\n";
			send_user(me, "%c%s", ':', result);
			"cmd/user/hanhtrang"->main(me, "x " + me->get_name());
		}
		return 1;
	}
	if (arg == "huyquen")
	{
		if (!me->get_save("passhanhtrang") || me->get_save("ndmkhtk") >= 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa có mã hành trang hoặc bạn đã nhập mã hành trang .");
			return 1;
		}
		send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn đã hủy yêu cầu xóa mật mã bảo vệ.");
		me->delete_save("quenmkht");
		return 1;
	}

	if (arg == "tieptuc")
	{
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		if (!me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa thiết lập Mật khẩu bảo vệ Hành trang, không thể sử dụng chức năng này.");
			return 1;
		}
		me->set_save("ndmkhtk", 0);
		return 1;
	}
	if (arg == "mokhoa")
	{
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		if (!me->get_save("passhanhtrang"))
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn chưa thiết lập Mật khẩu bảo vệ Hành trang, không thể sử dụng chức năng này.");
			return 1;
		}
		send_user(me, "%c%c%d%s", '?', 16, 12, "Xin nhập Mật khẩu bảo vệ     Hành trang :\n" ESC "hanhtrang @ %s\n");
		return 1;
	}
	if (arg == "dat")
	{

		if (me->get_save("passhanhtrang"))
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn đã thiết lập Mật khẩu bảo vệ Hành trang rồi, hãy nhập đúng Mật khẩu bảo vệ và chọn Đổi mật khẩu.");
			return 1;
		}
		send_user(me, "%c%c%d%s", '?', 16, 12, "Xin nhập Mật khẩu bảo vệ     Hành trang \n(giới hạn 12 ký tự) : \n" ESC "hanhtrang + %s\n");
		return 1;
	}
	if (arg == "doi")
	{
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		if (me->get_save("ndmkhtk") < 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn phải nhập Mật khẩu bảo vệ cũ vào mới được đặt Mật khẩu bảo vệ Hành trang mới.");
			return 1;
		}
		send_user(me, "%c%c%d%s", '?', 16, 12, "Xin nhập Mật khẩu bảo vệ     Hành trang \n(giới hạn 12 ký tự) : \n" ESC "hanhtrang + %s\n");
		return 1;
	}
	if (arg == "xoa")
	{
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		if (me->get_save("ndmkhtk") < 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn phải nhập Mật khẩu bảo vệ Hành trang vào mới có thể Xoá mật khẩu bảo vệ Hành trang.");
			return 1;
		}
		result = "Bạn xác nhận phải Xoá Mật khẩu bảo vệ Hành trang không?\n";
		result += ESC "Chấp nhận\npf2 00099.xnxoa\n";
		result += ESC "Hủy bỏ\n";
		send_user(me, "%c%s", ':', result);
		//	"cmd/user/hanhtrang"->main(me,"x "+me->get_name());
		return 1;
	}
	if (arg == "xnxoa")
	{
		if (me->get_save("quenmkht") > 0)
		{
			return 1;
		}
		if (me->get_save("ndmkhtk") < 1)
		{
			send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Bạn phải nhập Mật khẩu bảo vệ Hành trang vào mới có thể Xoá mật khẩu bảo vệ Hành trang.");
			return 1;
		}
		"cmd/user/hanhtrang"->main(me, "x " + me->get_name());
		return 1;
	}

	return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数：能否使用指令
void can_perform(object me)
{
	send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME);
}

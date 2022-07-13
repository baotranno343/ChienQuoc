#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{

	int p, cap;
	string result, arg2, arg3;
	object item, item1, who;
	if (is_player(me))
	{
		write_user(me, ECHO "Bạn không đủ quyền hạn !");
		return 1;
	}

	if (!arg)
		return 1;
	if (arg == 0)
		return 1;
	if (sscanf(arg, "%s %s %d", arg2, arg3, cap) != 3)
		return 1;
	if (arg2 && !(who = find_any_char(arg2)))
	{
		write_user(me, ECHO "Không tìm thấy người này !");
		return 1;
	}
	switch (arg3)
	{
	case "thanthuvoanh":
		who->set_skill(0104, cap);
		write_user(me, sprintf(ECHO "Nhập Môn Thân Thủ Vô Ảnh của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Nhập Môn Thân Thủ Vô Ảnh bây giờ là cấp %d", cap));
		return 1;
		break;
	case "kienthan":
		who->set_skill(0404, cap);
		write_user(me, sprintf(ECHO "Kiện Thân của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Kiện Thân bây giờ là cấp %d", cap));
		return 1;
		break;
	case "tutam":
		who->set_skill(0405, cap);
		write_user(me, sprintf(ECHO "Tu Tâm của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Tu Tâm bây giờ là cấp %d", cap));
		return 1;
		break;
	case "kinhlachocthuyet":
		who->set_skill(0109, cap);
		write_user(me, sprintf(ECHO "Kinh Lạc Học Thuyết của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Kinh Lạc Học Thuyết bây giờ là cấp %d", cap));
		return 1;
		break;
	case "daogiahocthuyet":
		who->set_skill(0401, cap);
		write_user(me, sprintf(ECHO "Học Thuyết Đạo Gia của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Học Thuyết Đạo Gia bây giờ là cấp %d", cap));
		return 1;
		break;
	case "tungkinh":
		who->set_skill(0402, cap);
		write_user(me, sprintf(ECHO "Tụng Kinh của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Tụng Kinh bây giờ là cấp %d", cap));
		return 1;
		break;
	case "thiendinh":
		who->set_skill(0403, cap);
		write_user(me, sprintf(ECHO "Thiền Định của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Thiền Định bây giờ là cấp %d", cap));
		return 1;
		break;
	case "chieugiachithuat":
		who->set_skill(0202, cap);
		write_user(me, sprintf(ECHO "Chiêu Giá Chi Thuật của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Chiêu Giá Chi Thuật bây giờ là cấp %d", cap));
		return 1;
		break;
	case "cobanquyencuoc":
		who->set_skill(0111, cap);
		write_user(me, sprintf(ECHO "Cơ Bản Quyền Cước của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cơ Bản Quyền Cước bây giờ là cấp %d", cap));
		return 1;
		break;
	case "cobandaophap":
		who->set_skill(0121, cap);
		write_user(me, sprintf(ECHO "Cơ Bản Đao Pháp của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cơ Bản Đao Pháp bây giờ là cấp %d", cap));
		return 1;
		break;
	case "cobankiemphap":
		who->set_skill(0131, cap);
		write_user(me, sprintf(ECHO "Cơ Bản Kiếm Pháp của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cơ Bản Kiếm Pháp bây giờ là cấp %d", cap));
		return 1;
		break;
	case "cobanthuongphap":
		who->set_skill(0141, cap);
		write_user(me, sprintf(ECHO "Cơ Bản Thương Pháp của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cơ Bản Thương Pháp bây giờ là cấp %d", cap));
		return 1;
		break;
	case "cobanbongphap":
		who->set_skill(0151, cap);
		write_user(me, sprintf(ECHO "Cơ Bản Bổng Pháp của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cơ Bản Bổng Pháp bây giờ là cấp %d", cap));
		return 1;
		break;
	case "amkhidauxa":
		who->set_skill(0161, cap);
		write_user(me, sprintf(ECHO "Ám Khí Đầu Xạ của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Ám Khí Đầu Xạ bây giờ là cấp %d", cap));
		return 1;
		break;
	case "ngoaicong":
		who->set_skill(0430, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Ngoại Công của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Ngoại Công bây giờ là cấp %d", cap));
		return 1;
		break;
	case "noicong":
		who->set_skill(0432, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Nội Công của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Nội Công bây giờ là cấp %d", cap));
		return 1;
		break;
	case "ngoaikhang":
		who->set_skill(0431, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Ngoại Kháng của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Ngoại Kháng bây giờ là cấp %d", cap));
		return 1;
		break;
	case "noikhang":
		who->set_skill(0433, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Nội Kháng của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Nội Kháng bây giờ là cấp %d", cap));
		return 1;
		break;
	case "thanthu":
		who->set_skill(0434, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Thân Thủ của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Thân Thủ bây giờ là cấp %d", cap));
		return 1;
		break;
	case "baokich":
		who->set_skill(0435, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Bạo Kích của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Bạo Kích bây giờ là cấp %d", cap));
		return 1;
		break;
	case "chinhxac":
		who->set_skill(0437, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Chính Xác của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Chính Xác bây giờ là cấp %d", cap));
		return 1;
		break;
	case "thechat":
		who->set_skill(0438, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Thể Chất của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Thể Chất bây giờ là cấp %d", cap));
		return 1;
		break;
	case "baoho":
		who->set_skill(0439, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Bảo Hộ của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Bảo Hộ bây giờ là cấp %d", cap));
		return 1;
		break;
	case "vatlieu":
		who->set_skill(0436, cap);
		write_user(me, sprintf(ECHO "Cường Hoá Vật Liệu của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cường Hoá Vật Liệu bây giờ là cấp %d", cap));
		return 1;
		break;
	case "daubep":
		who->set_skill(0610, cap);
		write_user(me, sprintf(ECHO "Đầu Bếp của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Đầu Bếp bây giờ là cấp %d", cap));
		return 1;
		break;
	case "renduc":
		who->set_skill(0620, cap);
		write_user(me, sprintf(ECHO "Rèn Đúc của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Rèn Đúc bây giờ là cấp %d", cap));
		return 1;
		break;
	case "luyendon":
		who->set_skill(0630, cap);
		write_user(me, sprintf(ECHO "Luyện Đơn của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Luyện Đơn bây giờ là cấp %d", cap));
		return 1;
		break;
	case "maymac":
		who->set_skill(0640, cap);
		write_user(me, sprintf(ECHO "May Mặc của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("May Mặc bây giờ là cấp %d", cap));
		return 1;
		break;
	case "dieukhac":
		who->set_skill(0650, cap);
		write_user(me, sprintf(ECHO "Điêu Khắc của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Điêu Khắc bây giờ là cấp %d", cap));
		return 1;
		break;
	case "coquan":
		who->set_skill(0660, cap);
		write_user(me, sprintf(ECHO "Cơ Quan của %s(%d) bây giờ là cấp %d", who->get_name(), who->get_number(), cap));
		send_user(who, "%c%s", ';', sprintf("Cơ Quan bây giờ là cấp %d", cap));
		return 1;
		break;
	}

	return 1;
}
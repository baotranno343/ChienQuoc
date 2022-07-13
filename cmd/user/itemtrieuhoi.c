#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

#define tiLeChiSoNangCapQuan 30
#define tongSoQuanCoTheTrieuhoi 1
#define soQuanMoiLanTrieuHoi 1
int main(object me, string arg2)
{

	object item, npc;
	int p, z, x, y, arg, capQuanDoan, slQuanDoanHienTai, i, tongSoQuanDoanChoPhep, tinhTime, hp, mp, ap, cp, dp, pp;
	string result;
	tongSoQuanDoanChoPhep = tongSoQuanCoTheTrieuhoi;
	slQuanDoanHienTai = "/map/city/08"->get_2(sprintf("quanDoan.%d.sl", me->get_number()));
	if (!objectp(item = present("Bùa Triệu Hồi Hình Nhân", me, 1, MAX_CARRY * 4)))
	{
		write_user(me, ECHO "Bạn không có Bùa Triệu Hồi Hình Nhân !");
		return 1;
	}

	arg = to_int(arg2);
	switch (arg)
	{
	case 0:
		// result = sprintf("Bạn đang sử dụng Triệu Hồi Quân Đoàn:\n Thời Gian Thiết Lập: %d\n Số Quân Đoàn Đang Xuất Hiện: %d\n Cấp Quân Đoàn Hiện Tại: %d \n Xin hãy lựa chọn :\n", item->get("timeTrieuHoi"), slQuanDoanHienTai, me->get_save("capQuanDoan"));
		result = sprintf("Bạn đang sử dụng Triệu Hồi Hình Nhân:\n");
		result += ESC "Triệu Hồi Hình Nhân\nitemtrieuhoi 11\n";
		result += ESC "Thiết Lập Thời Gian\nitemtrieuhoi 2\n";
		// result += ESC "Nâng Cấp Quân Đoàn\nitemtrieuhoi 3\n";

		result += ESC "Hủy bỏ\n";
		send_user(me, "%c%s", ':', result);
		break;
	case 1:
		result = sprintf("Bạn đang sử dụng Triệu Hồi Quân Đoàn:\n Thời Gian Thiết Lập: %d\n Số Quân Đoàn Đang Xuất Hiện: %d\n xin hãy lựa chọn :\n", item->get("timeTrieuHoi"), slQuanDoanHienTai);
		result += ESC "Binh 1\nitemtrieuhoi 11\n";
		// result += ESC "Binh 2\nitemtrieuhoi 12\n";
		// result += ESC "Binh 3\nitemtrieuhoi 13\n";
		result += ESC "Hủy bỏ\n";
		send_user(me, "%c%s", ':', result);
		break;
	case 2:
		result = sprintf("Bạn đang sử dụng Triệu Hồi Quân Đoàn:\n Thời Gian Thiết Lập: %d\n Số Quân Đoàn Đang Xuất Hiện: %d\n xin hãy lựa chọn :\n", item->get("timeTrieuHoi"), slQuanDoanHienTai);
		result += ESC "4 Giờ\nitemtrieuhoi 21\n";
		result += ESC "8 Giờ\nitemtrieuhoi 22\n";
		result += ESC "12 Giờ\nitemtrieuhoi 23\n";
		result += ESC "Hủy bỏ\n";
		send_user(me, "%c%s", ':', result);
		break;
	case 3:
		result = sprintf("Bạn đang sử dụng Triệu Hồi Quân Đoàn:\n Thời Gian Thiết Lập: %d\n Số Quân Đoàn Đang Xuất Hiện: %d\n xin hãy lựa chọn :\n", item->get("timeTrieuHoi"), slQuanDoanHienTai);
		result += ESC "Dùng 100 Nguyên Liệu 1, 100 Nguyên Liệu 2, 100 Nguyên Liệu 3 để nâng cấp 1?\nitemtrieuhoi 31\n";
		result += ESC "Dùng 150 Nguyên Liệu 1, 150 Nguyên Liệu 2, 150 Nguyên Liệu 3 để nâng cấp 2?\nitemtrieuhoi 32\n";

		result += ESC "Hủy bỏ\n";
		send_user(me, "%c%s", ':', result);
		break;
	case 11:
	case 12:
	case 13:
		capQuanDoan = me->get_save("capQuanDoan") * tiLeChiSoNangCapQuan;
		if (arg == 11)
		{
			npc = new ("tran/quandoan/bobinh");
		}
		if (arg == 12)
		{
			npc = new ("tran/quandoan/cungtien");
		}
		if (arg == 13)
		{
			npc = new ("tran/quandoan/thapdichuyen");
		}
		if (!npc)
		{
			send_user(me, "%c%s", ';', "Không tìm thấy npc");
			return 1;
		}

		hp = npc->get_hp() + (npc->get_hp() * capQuanDoan / 100);
		mp = npc->get_mp() + (npc->get_mp() * capQuanDoan / 100);
		ap = npc->get_ap() + (npc->get_ap() * capQuanDoan / 100);
		cp = npc->get_cp() + (npc->get_cp() * capQuanDoan / 100);
		dp = npc->get_dp() + (npc->get_dp() * capQuanDoan / 100);
		pp = npc->get_pp() + (npc->get_pp() * capQuanDoan / 100);

		result = sprintf("Chỉ Số Hiện Tại Của Binh 1:\nHP: %d\nMP: %d\nAP: %d\nCP: %d\nDP: %d\nPP: %d\n", hp, mp, ap, cp, dp, pp);
		result += ESC "Xuất Binh\nitemtrieuhoi 111\n";
		result += ESC "Hủy bỏ\n";
		send_user(me, "%c%s", ':', result);
		break;
	case 111:
	case 122:
	case 133:
		if (!item->get("timeTrieuHoi"))
		{
			send_user(me, "%c%s", ';', "Vui lòng thiết lập thời gian triệu hồi");
			return 1;
		}

		if (slQuanDoanHienTai == tongSoQuanDoanChoPhep)
		{
			send_user(me, "%c%s", ';', "Bạn đã triệu hồi đủ số lượng quân đoàn rồi");
			return 1;
		}

		z = get_z(me);
		x = get_x(me);
		y = get_y(me);

		tongSoQuanDoanChoPhep -= slQuanDoanHienTai;
		if (tongSoQuanDoanChoPhep - slQuanDoanHienTai > soQuanMoiLanTrieuHoi)
			tongSoQuanDoanChoPhep = soQuanMoiLanTrieuHoi;

		for (i = 0; i < tongSoQuanDoanChoPhep; i++)
		{
			if (arg == 111)
			{
				npc = new ("tran/quandoan/bobinh");
			}
			if (arg == 122)
			{
				npc = new ("tran/quandoan/cungtien");
			}
			if (arg == 133)
			{
				npc = new ("tran/quandoan/thapdichuyen");
			}
			if (!npc)
			{
				send_user(me, "%c%s", ';', "Không tìm thấy npc");
				return 1;
			}
			npc->set_name(me->get_name() + "> Hình Nhân");
			npc->set_idChuQuanDoan(me->get_number());
			npc->destroy_time(item->get("timeTrieuHoi") * 3600);
			if (capQuanDoan = me->get_save("capQuanDoan"))
			{
				capQuanDoan *= tiLeChiSoNangCapQuan;
				npc->add_hp(npc->get_hp() * capQuanDoan / 100);
				npc->add_ap(npc->get_ap() * capQuanDoan / 100);
				npc->add_cp(npc->get_cp() * capQuanDoan / 100);
				npc->add_dp(npc->get_dp() * capQuanDoan / 100);
				npc->add_pp(npc->get_pp() * capQuanDoan / 100);
			}
			if (!(p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)))
			{
				send_user(me, "%c%s", ';', "Không tìm được vị trí thả npc");
				return 1;
			}
			x = p / 1000;
			y = p % 1000;
			npc->add_to_scene(z, x, y);

			send_user(me, "%c%s", ';', "Bạn triệu hồi " HIY "Hình Nhân Thành Công");
			item->remove_from_user();
			destruct(item);
		}
		"/map/city/08"->add_2(sprintf("quanDoan.%d.sl", me->get_number()), tongSoQuanDoanChoPhep);
		break;

	case 21:
		item->set("timeTrieuHoi", 4);
		send_user(me, "%c%s", ';', "Thiết Lập Thời Gian Triệu Hồi Thành Công");
		break;
	case 22:
		item->set("timeTrieuHoi", 8);
		send_user(me, "%c%s", ';', "Thiết Lập Thời Gian Triệu Hồi Thành Công");
		break;
	case 23:
		item->set("timeTrieuHoi", 12);
		send_user(me, "%c%s", ';', "Thiết Lập Thời Gian Triệu Hồi Thành Công");
		break;
	case 31:
		if (slQuanDoanHienTai > 0)
		{
			write_user(me, ECHO "Đang triệu hồi quân đoàn không thể nâng cấp! ");
			return;
		}
		if (me->get_save("capQuanDoan"))
		{
			write_user(me, ECHO "Quân Đoàn chưa nâng cấp mới có thể nâng cấp 1! ");
			return;
		}
		if (TASK_LEGEND_D->check_task_item_amount(me, "Nguyên Liệu Một") < 100)
		{
			write_user(me, ECHO "Ngươi không có đủ 100 Nguyên Liệu 1 !");
			return;
		}
		if (TASK_LEGEND_D->check_task_item_amount(me, "Nguyên Liệu Hai") < 100)
		{
			write_user(me, ECHO "Ngươi không có đủ 100 Nguyên Liệu 2 !");
			return;
		}
		if (TASK_LEGEND_D->check_task_item_amount(me, "Nguyên Liệu Ba") < 100)
		{
			write_user(me, ECHO "Ngươi không có đủ 100 Nguyên Liệu 3 !");
			return;
		}

		TASK_LEGEND_D->check_task_item1(me, "Nguyên Liệu Một", 100);
		TASK_LEGEND_D->check_task_item1(me, "Nguyên Liệu Hai", 100);
		TASK_LEGEND_D->check_task_item1(me, "Nguyên Liệu Ba", 100);
		me->set_save("capQuanDoan", 1);
		send_user(me, "%c%d%c", 0x31, getoid(item), 0);
		send_user(me, "%c%s", ';', HIY "Chúc mừng bạn nâng cấp Quân Đoàn thành công!");

		break;
	case 32:
		if (slQuanDoanHienTai > 0)
		{
			write_user(me, ECHO "Đang triệu hồi quân đoàn không thể nâng cấp! ");
			return;
		}
		if (me->get_save("capQuanDoan") != 1)
		{
			write_user(me, ECHO "Quân Đoàn cấp 1 mới có thể nâng cấp 2 ! ");
			return;
		}
		if (TASK_LEGEND_D->check_task_item_amount(me, "Nguyên Liệu Một") < 150)
		{
			write_user(me, ECHO "Ngươi không có đủ 100 Nguyên Liệu Một !");
			return;
		}
		if (TASK_LEGEND_D->check_task_item_amount(me, "Nguyên Liệu Hai") < 150)
		{
			write_user(me, ECHO "Ngươi không có đủ 100 Nguyên Liệu Hai !");
			return;
		}
		if (TASK_LEGEND_D->check_task_item_amount(me, "Nguyên Liệu Ba") < 150)
		{
			write_user(me, ECHO "Ngươi không có đủ 100 Nguyên Liệu Ba !");
			return;
		}

		TASK_LEGEND_D->check_task_item1(me, "Nguyên Liệu Một", 150);
		TASK_LEGEND_D->check_task_item1(me, "Nguyên Liệu Hai", 150);
		TASK_LEGEND_D->check_task_item1(me, "Nguyên Liệu Ba", 150);
		me->set_save("capQuanDoan", 2);
		send_user(me, "%c%d%c", 0x31, getoid(item), 0);
		send_user(me, "%c%s", ';', HIY "Chúc mừng bạn nâng cấp Quân Đoàn thành công!");

		break;
	default:
		break;
	}
	return 1;
}
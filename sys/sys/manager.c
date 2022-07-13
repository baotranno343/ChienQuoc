
#include <ansi.h>
#include <equip.h>
#include <city.h>
#include <map.h>
#include <task.h>
#include <chia_kenh.h>
//	任务列表  1~6 天枢院任务	10 Dự Trữ	20 Thương Nhân

string *task1 = ({
	"Phá Tổn Đầu Khôi",
	"Phá Tổn Khôi Giáp",
	"Đồng Bổng",
	"Đồng Sáo",
	"Đồng Hoàn",
	"Đồng Ti",
	"Đồng Phiến",
	"Ma Bố",
	"Tiểu Đồng Phiến",
	"Đồng Quản",
	"Ma Tuyến",
	"烤地瓜",
	"地瓜解暑汤",
	"橙玉石",
	"橙宝石",
	"Xà Chi Quán",
	"Cánh Bọ Cánh Cứng",
	"Ngòi Ong",
	"Xương Cá",
	"Đuôi Khỉ",
	"Càng Bọ Ngựa",
	"Yên Bạch Ngọc Thạch",
	"Yên Bạch Bảo Thạch",
	"Cánh Bọ Ngựa",
	"Đuôi Chó",
	"Hỏa Chủng",
	"Châu Xuyến",
	"Núm Vú",
	"灰玉石",
	"Phi Hành Phiến",
	"Yêu Bài",
	"Búi Tóc",
	"Tích Bổng",
	"Tích Sáo",
	"Tích Hoàn",
	"Tích Ti",
	"Tích Phiến",
	"Ti Trù",
	"Ti Tuyến",
	"油炸地瓜片",
	"小米粥",
	"小青铜片",
	"Thanh Đồng Quản",
	"灰宝石",
	"Cẩu Bì Dược Cao",
	"Phá Cựu Đầu Khôi",
	"Phá Cựu Khôi Giáp",
	"Chu Hồng Ngọc Thạch",
	"Hài Cốt Toái Phiến",
	"Đuôi Bò Cạp",
	"Tơ Nhện",
	"Kịch Độc Châm",
	"Chu Hồng Bảo Thạch",
	"银杏子",
	"黑玉断续膏",
	"玉米棒",
	"Thanh Đồng Quản",
	"Gân Bò",
	"Khoen Mũi",
	"Thủy Tặc Đầu Cân",
	"Chân Ếch",
	"Thiểm Quang Thạch Đầu",
	"Đuôi Thằn Lằn",
	"Lục Sắc Tiểu Thạch",
	"Bạch Ngọc Thạch",
	"Bạch Bảo Thạch",
	"Ngân Bổng",
	"Ngân Sáo",
	"Ngân Hoàn",
	"Ngân Ti",
	"银片",
	"铁棒",
	"铁套",
	"铁环",
	"铁丝",
	"板蓝根粉",
	"金银花露",
	"御米壳",
	"田七粉",
	"野菊花粉",
	"黄芪粉",
	"Thiết Phiến",
	"Lăng",
	"Lăng Tuyến",
	"舍利子",
	"仙山灵芝",
	"小铁片",
	"Thiết Quản",
	"Càng Lớn",
	"Phá Bố Y",
	"玉白玉石",
	"玉白宝石",
	"Mạng Nhện",
	"Hồng Sắc Tiểu Thạch",
	"Bích Lục Ngọc Thạch",
	"Bích Lục Bảo Thạch",
	"Tứ Giả Di Vật",
	"Tua Mũ",
	"Phá Cựu Đầu Khôi",
	"Phá Cựu Khôi Giáp",
	"Chuôi Đao",
	"Vỏ Kiếm",
	"Bao Đựng Tên",
	"Mặc Ngọc Ngọc Thạch",
	"Mặc Ngọc Bảo Thạch",
	"Kim Bổng",
	"Kim Sáo",
	"Kim Hoàn",
	"Kim Ti",
	"Kim Phiến",
	"皮带",
	"Sa",
	"Sa Tuyến",
	"紫箐丹",
	"Khí Mạch Đan",
	"鸡蛋汤",
	"水煮大南瓜",
	"小银片",
	"Ngân Quản",
	"Đầu Thương",
	"Thục Địa",
	"干红枣",
	"干陈皮",
	"洋金花丝",
	"黄连粉",
	"穿心莲粉",
	"Ngư Xoa",
	"Đồng Quán",
	"Hoàng Sắc Tiểu Thạch",
	"Hủ Cốt",
	"Đồng Hài",
	"Thanh Ngọc Thạch",
	"Tinh Thiết Bổng",
	"Tinh Thiết Sáo",
	"Tinh Thiết Hoàn",
	"Tinh Thiết Ti",
	"Tinh Thiết Phiến",
	"Huyền Thiết Bổng",
	"Huyền Thiết Sáo",
	"Huyền Thiết Hoàn",
	"Tiêu Diêu Tán",
	"清心丹",
	"水煮大南瓜",
	"南瓜饼",
	"Huyền Thiết Ti",
	"Huyền Thiết Phiến",
	"Thanh Bảo Thạch",
	"Thất Sắc Xuyến Châu",
	"Thiết Hài",
	"Cốt Thuẫn",
	"Khô Đầu Lâu",
	"Đào Mộc Đinh",
	"Cương Thi Quán",
	"Lục Ngọc Thạch",
	"Lục Bảo Thạch",
	"Toái Ngọc",
	"Đào Dũng Chi Thử",
	"Đào Dũng Tí",
	"Toả Ma Liên",
	"Giáp Trụ",
	"Tiểu Thái Cực",
	"Ngọc Cái",
	"Mai Rùa",
	"Trường Thọ Thạch",
	"Ngọc Thúc Kế",
	"Hỏa Phượng Dực",
	"Phất Trần",
	"Thiên Thanh Ngọc Thạch",
	"Thiên Thanh Bảo Thạch",
	"Hồng Ngọc Thạch",
	"Hồng Bảo Thạch",
	"Hắc Ngọc Thạch",
	"Cam Thảo Phiến",
	"Bạch Kỳ Phấn",
	"Đương Quy Phiến",
	"Xuyên Bối Phấn",
	"Trùng Thảo",
	"Tàng Hồng Hoa",
});
int *count1 = ({
	3,
	3,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	3,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	1,
	3,
	3,
	3,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	3,
	3,
	3,
	1,
	3,
	3,
	3,
	3,
	1,
	1,
	1,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	3,
	3,
	1,
	1,
	3,
	3,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	3,
	1,
	1,
	1,
	1,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	3,
	1,
	1,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
});
string *unit1 = ({
	"颗",
	"颗",
	"颗",
	"个",
	"个",
	"个",
	"朵",
	"条",
	"片",
	"扎",
	"块",
	"块",
	"块",
	"个",
	"个",
	"颗",
	"条",
	"把",
	"个",
	"个",
	"个",
	"个",
	"颗",
	"个",
	"个",
	"个",
	"个",
	"个",
	"个",
	"个",
	"根",
	"根",
	"扎",
	"个",
	"个",
	"根",
	"朵",
	"块",
	"块",
	"块",
	"块",
	"个",
	"块",
	"件",
	"件",
	"块",
	"包",
	"个",
	"个",
	"个",
	"个",
	"块",
	"块",
	"条",
	"条",
	"条",
	"块",
	"个",
	"个",
	"根",
	"个",
	"块",
	"块",
	"个",
	"块",
	"张",
	"张",
	"个",
	"块",
	"条",
	"朵",
	"颗",
	"朵",
	"只",
	"个",
	"把",
	"把",
	"个",
	"个",
	"个",
	"个",
	"个",
	"块",
	"根",
	"根",
	"条",
	"块",
	"个",
	"块",
	"个",
	"朵",
	"块",
	"个",
	"朵",
	"颗",
	"根",
	"块",
	"块",
	"顶",
	"条",
	"个",
	"个",
	"个",
	"个",
	"根",
	"块",
	"个",
	"粒",
	"颗",
	"个",
	"个",
	"个",
	"个",
	"个",
	"块",
	"条",
	"个",
	"块",
	"个",
	"个",
	"个",
	"个",
});
string *task2 = ({
	"Trình Lâm Khai",
	"Chu Đồng",
	"Lý Tam Thẩm",
	"Hứa Thị",
	"Lưu Đức",
	"Mạnh Cầu",
	"Chu Cuồng",
	"Ngụy Quản Gia",
	"Lý Đồ",
	"Lý Lăng",
	"Vương Khải",
	"Khổng Tiểu Phi",
	"Thôi Ngọc",
	"Tề Quản Gia",
	"Lão Vương Thẩm",
	"Mã Đại Hán",
	"Triệu Mộc",
	"Lâm Vi",
	"Du Tử",
	"Tiền Lão Bát",
	"Hàn Quản Gia",
	"Lưu Đầu",
	"Tiền Lão Cửu",
	"Tôn Lục",
	"Vương Mãn",
	"Sở Quản Gia",
	"Vương Thiết Tượng",
	"Cước Phu",
	"Lý Phòng",
	"Bạch Dịch",
	"Triệu Quản Gia",
	"Bành Tiêm Hào",
	"Mã Hiển",
	"Hạ Hầu Đảng",
	"Tần Quản Gia",
	"Tào Thanh",
	"Đinh Hạc Niên",
	"Trình Phong",
	"Yên Quản Gia",
});
//string * food = ({ "水稻", "麦子", "玉米", "小米", "高粱", "冬瓜", "南瓜", "黄瓜", "萝卜", "白菜", "青菜", "地瓜", "山药", });
string *food = ({
	"烤地瓜",
	"地瓜解暑汤",
	"油炸地瓜片",
	"小米粥",
	"玉米棒",
	"玉米羹",
});
// 内测期间生活技能封闭时暂时用的物品
string *task3 = ({
	"Phá Tổn Đầu Khôi",
	"Phá Tổn Khôi Giáp",
	"Xà Chi Quán",
	"Cánh Bọ Cánh Cứng",
	"Ngòi Ong",
	"Xương Cá",
	"Đuôi Khỉ",
	"Càng Bọ Ngựa",
	"Cánh Bọ Ngựa",
	"Đuôi Chó",
	"Hỏa Chủng",
	"Châu Xuyến",
	"Núm Vú",
	"Phi Hành Phiến",
	"Yêu Bài",
	"Búi Tóc",
	"Cẩu Bì Dược Cao",
	"Phá Cựu Đầu Khôi",
	"Phá Cựu Khôi Giáp",
	"Hài Cốt Toái Phiến",
	"Đuôi Bò Cạp",
	"Tơ Nhện",
	"Kịch Độc Châm",
	"Gân Bò",
	"Khoen Mũi",
	"Thủy Tặc Đầu Cân",
	"Chân Ếch",
	"Thiểm Quang Thạch Đầu",
	"Đuôi Thằn Lằn",
	"Lục Sắc Tiểu Thạch",
	"Càng Lớn",
	"Phá Bố Y",
	"Mạng Nhện",
	"Hồng Sắc Tiểu Thạch",
	"Tứ Giả Di Vật",
	"Tua Mũ",
	"Phá Cựu Đầu Khôi",
	"Phá Cựu Khôi Giáp",
	"Chuôi Đao",
	"Vỏ Kiếm",
	"Bao Đựng Tên",
	"Đầu Thương",
	"Ngư Xoa",
	"Đồng Quán",
	"Hoàng Sắc Tiểu Thạch",
	"Hủ Cốt",
	"Đồng Hài",
	"Thất Sắc Xuyến Châu",
	"Thiết Hài",
	"Cốt Thuẫn",
	"Khô Đầu Lâu",
	"Đào Mộc Đinh",
	"Cương Thi Quán",
	"Toái Ngọc",
	"Đào Dũng Chi Thử",
	"Đào Dũng Tí",
	"Toả Ma Liên",
	"Giáp Trụ",
	"Tiểu Thái Cực",
	"Ngọc Cái",
	"Mai Rùa",
	"Trường Thọ Thạch",
	"Ngọc Thúc Kế",
	"Hỏa Phượng Dực",
	"Phất Trần",
});

// 函数:生成二进制码
void SAVE_BINARY() {}

void init_org_place(int z, string name, object orgnpc);

// 国家的帮派总管
void do_look_1(object me, object who)
{
	string result;
	int position;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	"/quest/help"->send_help_tips(me, 26);
	result = sprintf(" %s :\n Ta là Tổng Quản phụ trách nhiệm vụ của Bang phái %s , ngươi có chuyện gì cần ta giúp đỡ không?\n", who->get_name(), who->get_city_name());
	position = me->get_org_position();
	if (position > 0 && me->get_city_name() == who->get_city_name() && me->get_org_name() != "")
		result += sprintf(ESC "Quay về Bang phái\ntalk %x# back\n", getoid(who));
	else if (position == 0 && me->get_city_name() == who->get_city_name() && me->get_org_name() != "")
		result += sprintf(ESC "Xin buông tha\ntalk %x# info.10\n", getoid(who));
	else
	{
		if (me->get_org_name() == "")
		{
			result += sprintf(ESC "Ta muốn gia nhập bang\ntalk %x# info.20\n", getoid(who));
			result += sprintf(ESC "Ta muốn lập bang\ntalk %x# info.30\n", getoid(who));
		}
	}
	result += sprintf(ESC "Tham quan Bang phái khác\ntalk %x# travel\n", getoid(who));
	result += sprintf(ESC "Rời khỏi\nCLOSE\n");
	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
}

// 回帮派
void do_back(object me, object who, string arg)
{
	string result, name;
	int position;
	object map, orgnpc, npc;
	int i, size, z, p, x, y, x0, y0;
	position = me->get_org_position();
	name = me->get_org_name();
	if (name == "")
		return;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (position > 0 && me->get_city_name() == who->get_city_name())
	{
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
		if (!objectp(orgnpc))
			return;
		map = orgnpc->get("map");
		if (map == 0)
		{
			if ((z = find_map_flag(NEWBIE_MAP_BEGIN, NEWBIE_MAP_END, 0)) > 0)
			{
				p = 886;
				init_virtual_map(z, p); // 生成虚拟地图
				map = new ("/inh/std/org");
				map->set_client_id(p);
				set_map_object(map, map->set_id(z));
				orgnpc->set("map", map);
				orgnpc->set("z", z);
				map->set_name(name);
				init_org_place(z, name, orgnpc);
			}
			else
				return;
		}
		else
		{
			z = orgnpc->get("z");
		}
		me->set_2("jiguan.z", get_z(me));
		me->set_2("jiguan.x", get_x(me));
		me->set_2("jiguan.y", get_y(me));
		if (random(2))
			p = get_jumpin(z, 11);
		else
			p = get_jumpin(z, 12);
		if (p)
		{
			me->add_to_scene(z, p / 1000, p % 1000, 3);
		}
	}
}

// 国家总管的相关函数
void do_info(object me, object who, string arg)
{
	int position, flag, number, i, size;
	string result, name;
	object orgnpc, city, *char, item;
	position = me->get_org_position();
	flag = to_int(arg);
	name = me->get_org_name();
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (flag >= 10 && flag < 20)
	{
		if (name == "")
			return;
		if (position > 0)
		{
			result = sprintf("%s:\n    Ngươi đã ở trong Bang Phái\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (flag == 10)
		{
			result = sprintf("%s:\n    Ngươi thật sự không muốn %s gia nhập Bang phải không ?\n", who->get_name(), name);
			result += sprintf(ESC "Xác nhận\ntalk %x# info.11\n", getoid(who));
			result += ESC "Huỷ bỏ\nCLOSE\n";
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
		number = me->get_number();
		if (objectp(orgnpc))
		{
			if (orgnpc->get_join_id(number))
			{
				orgnpc->delete_join_info(number);
				orgnpc->save();
			}
		}
		me->set_org_name("");
		result = sprintf("%s:\n    Ta đã không muốn cho %s gia nhập, có chuyện gì cứ đến tìm ta.\n", who->get_name(), name);
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (name != "")
		return;
	if (flag >= 20 && flag < 30)
	{
		switch (flag)
		{
		case 20:
			result = sprintf("%s:\n    Ngươi muốn gia nhập Bang Phái? trước hết là phải gia nhập quốc tịch vào quốc gia.Còn nếu muốn sáng lập Bang Phái mới? Phải có 1 tín vật gọi là Tù Và Đế Vương\n", who->get_name());
			result += sprintf(ESC "Xác nhận\ntalk %x# info.21\n", getoid(who));
			result += sprintf(ESC "Phản hồi\ntalk %x# info.29\n", getoid(who));
			break;
		case 21:
			if (me->get_city_name() != who->get_city_name() && me->get_city_name() != "" && me->get_city_name() != 0)
			{
				result = sprintf("%s:\n    Ngươi đã gia nhập nước khác, ta không thể nhận ngươi được.\n", who->get_name());
			}
			else
			{
				if (!(city = CITY_D->get_city_object(who)))
					return;
				char = city->get("manager");
				send_user(me, "%c%c%c%d", 0x95, 53, 1, getoid(who));
				size = sizeof(char);
				for (i = 0; i < size; i++)
					if (objectp(char[i]))
					{
						if (char[i]->get_city_name() == "Tề Quốc")
						{
							result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
						}
						else if (char[i]->get_city_name() == "Hàn Quốc")
						{
							result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
						}
						else if (char[i]->get_city_name() == "Triệu Quốc")
						{
							result = sprintf("%12s%1s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
						}
						else if (char[i]->get_city_name() == "Ngụy Quốc")
						{
							result = sprintf("%12s%2s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
						}
						else if (char[i]->get_city_name() == "Tần Quốc")
						{
							result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
						}
						else if (char[i]->get_city_name() == "Sở Quốc")
						{
							result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
						}
						else if (char[i]->get_city_name() == "Yên Quốc")
						{
							result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
						}
						send_user(me, "%c%c%c%d%c%w%w%s", 0x95, 53, 2, char[i]->get_power(), char[i]->get_grade(), char[i]->sizeof_member_dbase(), char[i]->get_max_number(), result);
					}
				return;
			}
			break;
		case 29:
			do_look_1(me, who);
			return;
		}
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (me->get_city_name() != who->get_city_name())
	{
		result = sprintf("%s:\n    Bạn không phải là quốc dân này\n", who->get_name());
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (me->get_level() < 40)
	{
		result = sprintf("%s:\n    Cấp bậc chưa đến 40, còn không thể gánh vác trách nhiệm nữa !!\n", who->get_name());
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	switch (flag)
	{
	case 30:
		result = sprintf("%s:\n    Tuổi trẻ bây giờ thật là vô hậu, ngươi muốn sáng lập Bang Phái thì phải đưa cho ta 1 tín vật gọi là \"Tù Và Đế Vương\"  !\n", who->get_name());
		result += sprintf(ESC "Giao nộp \"Tù Và Đế Vương\"\ntalk %x# info.31\n", getoid(who));
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	case 31:
		if (objectp(item = present("Tù Và Đế Vương", me, 1, MAX_CARRY * 4)))
		{
			result = sprintf("%s:\n    Qủa đúng là \"Tù Và Đế Vương\" , thôy được lão đây cho đáp ứng nguyện vọng của ngươi !\n", who->get_name());
			result += sprintf(ESC "Sáng lập Bang phái\ntalk %x# info.32\n", getoid(who));
			result += ESC "Ta vẫn còn lo lắng……\nCLOSE\n";
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		result = sprintf("%s:\n    \"Tù Và Đế Vương\" còn chưa tìm được sao ? ngươi hãy đi hỏi Thần Tiên Gia Gia thử xem, ta tin hắn sẽ giúp ngươi được chuyện này !\n", who->get_name());
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	case 32:
		if (objectp(item = present("Tù Và Đế Vương", me, 1, MAX_CARRY * 4)))
		{
			name = me->get("org");
			if (!stringp(name) || name == "")
				send_user(me, "%c%c%d%s", '?', 16, 11, "Ngươi muốn sáng lập Bang Phái, hãy nhập tên Bang Phái vào (1-5 từ):\n" ESC "org @ %s\n");
			else
				"cmd/user/org"->main(me, "@ " + name);
			return;
		}
		break;
	}
}

// Tham quan其他帮派
void do_travel(object me, object who, string arg)
{
	string name, result;
	object map, orgnpc, city, *char;
	int i, size, z, p, x, y, x0, y0;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (arg == "" || arg == 0)
	{
		if (!(city = CITY_D->get_city_object(who)))
			return;
		char = city->get("manager");
		send_user(me, "%c%c%c%d", 0x95, 54, 1, getoid(who));
		size = sizeof(char);
		for (i = 0; i < size; i++)
			if (objectp(char[i]))
			{
				if (char[i]->get_city_name() == "Tề Quốc")
				{
					result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
				}
				else if (char[i]->get_city_name() == "Hàn Quốc")
				{
					result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
				}
				else if (char[i]->get_city_name() == "Triệu Quốc")
				{
					result = sprintf("%12s%1s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
				}
				else if (char[i]->get_city_name() == "Ngụy Quốc")
				{
					result = sprintf("%12s%2s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
				}
				else if (char[i]->get_city_name() == "Tần Quốc")
				{
					result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
				}
				else if (char[i]->get_city_name() == "Sở Quốc")
				{
					result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
				}
				else if (char[i]->get_city_name() == "Yên Quốc")
				{
					result = sprintf("%12s%3s%-10s%" + 14 + "s%-12s", char[i]->get_city_name(), " ", char[i]->get_org_name(), " ", char[i]->get_master_name());
				}
				send_user(me, "%c%c%c%d%c%w%w%s", 0x95, 54, 2, char[i]->get_power(), char[i]->get_grade(), char[i]->sizeof_member_dbase(), char[i]->get_max_number(), result);
			}
		return;
	}
	name = arg;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	result = sprintf("%s:\n    Bạn muốn đi tham quan %s không ? thật dễ dàng, bạn chỉ cần đưa tôi 2000 lượng là mọi thứ Okê\n", who->get_name(), name);
	result += sprintf(ESC "Xác nhận\ntalk %x# travel2.%s\n", getoid(who), name);
	result += ESC "Rời khỏi\nCLOSE\n";
	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
	send_user(me, "%c%c", 0x95, 255);
}

// 进入其他帮派
void do_travel2(object me, object who, string arg)
{
	string name, result;
	object map, orgnpc, npc;
	int i, size, z, p, x, y, x0, y0;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (arg == "")
		return;
	name = arg;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	if (me->get_cash() < 2000)
	{
		result = sprintf("%s:\n    Không có tiền ? thật là nói đùa ! Chờ có đủ 2000 lượng rồi lại đến đi !\n", who->get_name());
		result += ESC "Rời khỏi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	me->add_cash(-2000);
	"/sys/sys/count"->add_use("visit", 2000);
	me->log_money("Tham quan", -2000);
	orgnpc->add_gold(1000);
	map = orgnpc->get("map");
	if (map == 0)
	{
		if ((z = find_map_flag(NEWBIE_MAP_BEGIN, NEWBIE_MAP_END, 0)) > 0)
		{
			p = 886;
			init_virtual_map(z, p); // 生成虚拟地图
			map = new ("/inh/std/org");
			map->set_client_id(p);
			set_map_object(map, map->set_id(z));
			orgnpc->set("map", map);
			orgnpc->set("z", z);
			map->set_name(name);
			init_org_place(z, name, orgnpc);
		}
		else
			return;
	}
	else
	{
		z = orgnpc->get("z");
	}
	me->set_2("jiguan.z", get_z(me));
	me->set_2("jiguan.x", get_x(me));
	me->set_2("jiguan.y", get_y(me));
	if (p = get_jumpin(z, 10))
	{
		me->add_to_scene(z, p / 1000, p % 1000, 3);
	}
}

// 申请加入帮派
void do_join(object me, object who, string arg)
{
	string name, result;
	object map, orgnpc;
	int i, size, z, p, x, y, x0, y0;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (me->get_city_name() != "" && me->get_city_name() != who->get_city_name())
		return;
	if (me->get_org_name() != "")
		return;
	name = arg;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	if ("/sys/city/manager2"->do_join(me, orgnpc, "") == 1)
	{
		//		me->set_org_name(name);
		result = sprintf("%s:\n    Ngài đích xin thư ta vừa rồi đã muốn ủy thác bộ hạ chuyển giao cấp %s đích %s đại nhân, ngài liền tĩnh hậu giáo lý Phúc Âm đi.\n", who->get_name(), name, orgnpc->get_master_name());
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		send_user(me, "%c%c", 0x95, 255);
	}
}

// 帮派里的总管
void do_look_2(object me, object who)
{
	string result, name;
	object orgnpc;
	int position, id;
	name = who->get_org_name();
	name = who->get_org_name();
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (name == "")
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	result = sprintf(" %s :\n Ta chính là Tổng Quản của %s , phụ trách tất cả nhiệm vụ thường ngày quản lý Bang phái %s . ngươi tìm ta có việc gì không?\n", who->get_name(), name, name);
	position = me->get_org_position();
	if ((me->get_org_name() == name) && (position > 0))
	{
		id = getoid(who);
		result += sprintf(ESC "Tra danh sách thành viên Bang phái\ntalk %x# info\n", id);
		result += sprintf(ESC "Công báo và ký sự của Bang phái\ntalk %x# note\n", id);
		result += sprintf(ESC "Chiến tranh Bang phái\ntalk %x# war\n", id);
		result += sprintf(ESC "Tình hình Bang phái\ntalk %x# org\n", id);
		if (position == 9 && orgnpc->get_demisstime() > time())
			result += sprintf(ESC "Huỷ bỏ nhường chức vị\ntalk %x# quest.30\n", id);
		if (me->get_save_2("orgtask2.type") == 0)
			result += sprintf(ESC "Lãnh nhiệm vụ Thiên Xu Viện\ntalk %x# quest.10\n", id);
		else
			result += sprintf(ESC "Hoàn thành nhiệm vụ Thiên Xu Viện\ntalk %x# quest.20\n", id);
	}
	result += sprintf(ESC "Rời khỏi\nCLOSE\n");
	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
}

// 帮派的武教头
void do_look_3(object me, object who)
{
	string result, name;
	int position, count, i;
	object orgnpc;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	result = sprintf(" %s :\n Người này chuyên phụ trách huấn luyện Bang phái và chiêu mộ nhân tài chiến đấu.\n", who->get_name());
	position = me->get_org_position();
	name = who->get_org_name();
	if (name == "")
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	if (position > 0 && me->get_org_name() == who->get_org_name())
	{
		count = 0;
		for (i = 0; i <= 9; i++)
			if (orgnpc->get_strong(i))
				count++;
		result += sprintf("Hiện nay độ huấn luyện của Bang phái này là %d , khởi động %d huấn luyện cường hóa, cần phải làm những gì?\n", orgnpc->get_train(), count);
		if (position >= 8)
			result += sprintf(ESC "Mở ra Cường Hoá kĩ năng\ntalk %x# info.10\n", getoid(who));
		if (count > 0)
			result += sprintf(ESC "Học kỹ năng cường hóa\ntalk %x# info.20\n", getoid(who));
		if (position >= 8)
		{
			result += sprintf(ESC "Tăng độ huấn luyện\ntalk %x# info.50\n", getoid(who));
			//???			result += sprintf(ESC"聘请帮派守护者\ntalk %x# info.40\n", getoid(who));
		}
	}
	result += sprintf(ESC "Rời khỏi\nCLOSE\n");
	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
}

// 武教头的相关函数
void do_info_3(object me, object who, string arg)
{
	int position, flag, number, i, size, level, time, cash, level1;
	string result, name, list, desc;
	object orgnpc, city, *char, item, file;
	position = me->get_org_position();
	flag = to_int(arg);
	name = me->get_org_name();
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (position == 0 || name == "" || name != who->get_org_name())
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	switch (flag)
	{
	case 10:
		if (position < 8)
			return;
		list = "";
		size = orgnpc->get_strongcount();
		if (size > 0)
		{
			for (i = 0; i <= 9; i++)
				if (orgnpc->get_strong(i))
				{
					file = load_object(sprintf("/skill/04/%04d", 430 + i));
					if (file)
					{
						if (list == "")
							list = file->get_name();
						else
							list = list + "、" + file->get_name();
					}
				}
			if (size >= orgnpc->get_grade() * 2)
			{
				result = sprintf("%s:\n    Trước mắt bang phái đã mở ra %d hạng cường hoá (%s) đã tới mức hạn cao nhất.Hãy thăng cấp quy mô Bang Phái rồi xem xét \n", who->get_name(), size, list);
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				return;
			}
			result = sprintf("%s:\n    Trước mắt bang phái đã mở ra %d hạng cường hoá (%s) chưa tới hạn mức cao nhất, hãy mở ra thêm Cường hoá, mỗi lần mở ra tiêu hao Bang phái Tài chính 500 vạn, Dự trữ 200 \n", who->get_name(), size, list);
		}
		else
			result = sprintf("%s:\n    Hãy lựa chọn mở ra Cường Hoá, mở ra tiêu hao Tài chính 500 vạn, Dự trữ 200 \n", who->get_name());
		for (i = 0; i <= 9; i++)
			if (orgnpc->get_strong(i) == 0)
			{
				file = load_object(sprintf("/skill/04/%04d", 430 + i));
				if (file)
				{
					result += sprintf(ESC "%s\ntalk %x# info.%d\n", file->get_name(), getoid(who), 101 + i);
				}
			}
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 101:
	case 102:
	case 103:
	case 104:
	case 105:
	case 106:
	case 107:
	case 108:
	case 109:
	case 110:
	case 151:
	case 152:
	case 153:
	case 154:
	case 155:
	case 156:
	case 157:
	case 158:
	case 159:
	case 160:
		if (position < 8)
			return;
		i = (flag - 1) % 10;
		if (orgnpc->get_strong(i))
			return;
		file = load_object(sprintf("/skill/04/%04d", 430 + i));
		if (!file)
			return;
		size = orgnpc->get_strongcount();
		if (size >= orgnpc->get_grade() * 2)
		{
			result = sprintf("%s:\n    Trước mắt Bang Phái đã mở ra %d hạng cường hoá, đã đạt hạn mức cao nhất, hãy thăng cấp quy mô rồi lại đến\n", who->get_name(), size);
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		//		if (orgnpc->get_train()<(size+1)*10+5)
		if (orgnpc->get_train() < (size + 1) * 10 + 5)
		{
			result = sprintf("%s:\n    Trước mắt Bang Phái độ Huấn luyện không đủ %d, hãy tăng độ huấn luyện rồi hãy Cường hoá kĩ năng\n", who->get_name(), (size + 1) * 10 + 5);
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (orgnpc->get_gold() < 5000000)
		{
			result = sprintf("%s:\n    Trước mắt Tài chính không đủ 500 vạn, hãy gia tăng cho đủ rồi lại đến\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (orgnpc->get_store() < 200)
		{
			result = sprintf("%s:\n    Trước mắt Bang Phái dự trữ không đủ 200, hãy gia tăng Dự trữ rồi lại đến\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (flag < 129)
		{
			desc = file->get_desc();
			result = sprintf("%s:\n    %s %s xác nhận phải mở ra Kĩ năng Cường Hoá phải không ? \n", who->get_name(), file->get_name(), desc[25.. < 2], );
			result += sprintf(ESC "Xác nhận\ntalk %x# info.%d\n", getoid(who), 151 + i);
			result += sprintf(ESC "Huỷ bỏ\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		orgnpc->add_gold(-5000000);
		orgnpc->set_store(orgnpc->get_store() - 200);
		orgnpc->set_strong(i);
		orgnpc->save();
		result = sprintf("%s:\n    Bạn mở ra %s, tiêu hao Tài chính 500 vạn, Dự trữ 200\n", who->get_name(), file->get_name());
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		FAMILY_D->org_channel(name, 0, sprintf(HIR "Kĩ năng Cường Hoá của bổn bang mở ra thêm \"%s\".", file->get_name()));
		break;
	case 20:
		result = sprintf("%s:\n    Thành viên trong Bang có thể tới chỗ ta để học Kĩ năng Cường Hoá, mỗi lần học tiêu hao 20.000 lượng, Cống hiến 5 điểm, một số điểm Tiềm năng nhất định, mặt khác điểm cống hiến Bang Phái phải đạt trên 3000 điểm mới có thể học ! :\n", who->get_name());
		for (i = 0; i <= 9; i++)
			if (orgnpc->get_strong(i))
			{
				file = load_object(sprintf("/skill/04/%04d", 430 + i));
				if (file)
				{
					result += sprintf(ESC "%s\ntalk %x# info.%d\n", file->get_name(), getoid(who), 111 + i);
				}
			}
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 111:
	case 112:
	case 113:
	case 114:
	case 115:
	case 116:
	case 117:
	case 118:
	case 119:
	case 120:
		i = (flag - 1) % 10;
		if (orgnpc->get_strong(i) == 0)
			return;
		file = load_object(sprintf("/skill/04/%04d", 430 + i));
		if (!file)
			return;
		cash = file->get_learn_money();
		if (cash == 0)
			cash = 30000;
		result = sprintf("%s:\n    Cường hoá %s một lần, chỉ có thể tăng 5 điểm thuần thục, mỗi lần tiêu hao %d lượng, cống hiến Bang phái 5 điểm, Tiềm năng %d điểm, ngươi xác nhận học không ?\n", who->get_name(), file->get_name(), cash, 1000 * me->get_skill(430 + i));
		result += sprintf(ESC "Xác nhận\ntalk %x# info.%d\n", getoid(who), 141 + i);
		result += sprintf(ESC "Huỷ bỏ\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 141:
	case 142:
	case 143:
	case 144:
	case 145:
	case 146:
	case 147:
	case 148:
	case 149:
	case 150:
		i = (flag - 1) % 10;
		if (orgnpc->get_strong(i) == 0)
			return;
		file = load_object(sprintf("/skill/04/%04d", 430 + i));
		if (!file)
			return;
		//		if ( (i==6)&&me->get_skill(430+i)>=5)
		//		{
		//			result = sprintf("%s:\n    Kĩ năng %s của bạn đã đạt hạn mước cao nhất\n", who->get_name(), file->get_name());
		//			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		//			return;
		//		}
		if (i == 6)
			level1 = 5;
		else if (i == 0 || i == 1 || i == 2 || i == 3 || i == 7 || i == 8)
			level1 = 20;
		else
			level1 = 10;
		if (me->get_skill(430 + i) >= level1)
		{
			result = sprintf("%s:\n    Kĩ năng %s của bạn đã đạt hạn mước cao nhất\n", who->get_name(), file->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		//		if(me->get_skill(430+i)>=me->get_level()/10-2)
		//		{
		//			result = sprintf("%s:\n    您只有升至%d级才能继续提升%s.\n", who->get_name(), (me->get_level()/10+1)*10, file->get_name());
		//			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		//			return;
		//		}
		cash = file->get_learn_money();
		if (cash == 0)
			cash = 30000;
		if (me->get_cash() < cash)
		{
			result = sprintf("%s:\n    Ngân lượng không đủ %d, không thể luyện Cường hoá\n", who->get_name(), cash);
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		number = me->get_number();
		if (orgnpc->get_member_all_contribute(number) < 3000)
		{
			result = sprintf("%s:\n    Cống hiến Bang phái không đủ 3000 điểm, không thể học Cường hoá\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (orgnpc->get_member_contribute(number) < 5)
		{
			result = sprintf("%s:\n    Không đủ điểm Cống hiến để học Cường Hoá\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (me->get_potential() < 1000 * me->get_skill(430 + i))
		{
			result = sprintf("%s:\n    Không đủ điểm Tiềm năng để học Cường Hoá\n", who->get_name(), 1000 * me->get_skill(430 + i));
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		me->add_cash(-cash);
		"/sys/sys/count"->add_use("org-strong", cash);
		me->log_money("Kĩ Năng Cường Hoá", -cash);
		orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number) - 5);
		me->set_potential(me->get_potential() - (1000 * me->get_skill(430 + i)));
		me->improve_skill(430 + i, 5);
		level = me->get_skill(430 + i);
		result = sprintf("%s:\n    Bạn cường hoá %s tăng thuần thục lên 5 điểm, trước mắt cấp bậc %d cấp, độ thuần thục %d / %d .\n", who->get_name(), file->get_name(), level, me->get_skill_degree(430 + i), (level + 1) * (level + 1) * 5);
		result += sprintf(ESC "Tiếp tục học\ntalk %x# info.%d\n", getoid(who), 141 + i);
		result += sprintf(ESC "Huỷ bỏ\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 50:
	case 51:
		time = orgnpc->get_traintime();
		if (time > 0)
		{
			if (time() > time)
			{
				orgnpc->set_traintime(0);
				orgnpc->set_train(orgnpc->get_train() + 1);
			}
			else
			{
				result = sprintf("%s:\n    Bang Phái tăng độ Huấn luyện còn thừa %d phút\n", who->get_name(), (time - time()) / 60);
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				return;
			}
		}
		if (orgnpc->get_train() >= 25 * orgnpc->get_grade())
		{
			result = sprintf("%s:\n    Bang Phái độ Huấn luyện đã đạt hạn mức cao nhất\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (orgnpc->get_gold() < 2000000)
		{
			result = sprintf("%s:\n    Tài chính không đủ 200 vạn, không thể tăng độ huấn luyện\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (orgnpc->get_store() < 60)
		{
			result = sprintf("%s:\n    Dự trữ không đủ 60, không thể tăng độ huấn luyện\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (flag == 30)
		{
			result = sprintf("%s:\n    Trước mắt Bang phái độ huấn luyện là %d, tăng lên 1 điểm cần tiêu hao Tài chính 200 vạn cùng với Dự trữ 60, 6h sau sẽ có hiệu lực , ngươi xác nhận tăng độ huấn luyện không ? \n", who->get_name(), orgnpc->get_train());
			result += sprintf(ESC "Xác nhận\ntalk %x# info.51\n", getoid(who));
			result += sprintf(ESC "Huỷ bỏ\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		orgnpc->add_gold(-2000000);
		orgnpc->set_store(orgnpc->get_store() - 60);
		orgnpc->set_traintime(time() + 6 * 3600);
		orgnpc->save();
		FAMILY_D->org_channel(name, 0, sprintf(HIR "Bổn bang đã bắt đầu tăng độ huấn luyện, hiệu quả sau 6h nữa", orgnpc->get_sciencetime()));
		break;
	}
}

// 帮派的帐房先生
void do_look_4(object me, object who)
{
	string result, name, *trader;
	int position, store;
	object orgnpc;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	result = sprintf(" %s :\n Làm quản kho của Bang phái này, cần phải tận tâm tận lực, tính toán kỹ lưỡng.\n", who->get_name());
	position = me->get_org_position();
	name = who->get_org_name();
	if (name == "")
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	if (position > 0 && me->get_org_name() == name)
	{
		store = orgnpc->get_store();
		result += sprintf("Hiện tại bang này có nguồn vốn là %d lượng, trù bị là %d . Bạn đến tìm ta có chuyện gì không?\n", orgnpc->get_gold(), store);
		if (store < orgnpc->get_grade() * 500 && (me->get_save_2("orgtask.type") != 1))
			result += sprintf(ESC "Lãnh nhiệm vụ trù bị\ntalk %x# info.10\n", getoid(who));
		if (me->get_save_2("orgtask.type") == 1)
			result += sprintf(ESC "Hoàn thành nhiệm vụ trù bị\ntalk %x# info.20\n", getoid(who));
		trader = orgnpc->get_trader();
		if (arrayp(trader) && member_array(me->get_id(), trader) != -1 || me->get_number() == orgnpc->get_master())
		{
			if (me->get_save_2("orgtask3.type") == 0)
				result += sprintf(ESC "Lĩnh nhiệm vụ Thương nhân\ntalk %x# info.30\n", getoid(who));
		}
		if (me->get_save_2("orgtask3.type") == 1)
			result += sprintf(ESC "Hoàn thành nhiệm vụ Thương nhân\ntalk %x# info.40\n", getoid(who));
		result += sprintf(ESC "Quyên Tiền\ntalk %x# savings\n", getoid(who));
	}
	result += sprintf(ESC "Rời khỏi\nCLOSE\n");
	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
}

// 帐房先生的相关函数
void do_info_4(object me, object who, string arg)
{
	int position, flag, number, i, size, level, count, gold, p, exp, contrib, base, rand, order, store;
	string result, name, list;
	object orgnpc, city, *char, item, file;
	object *inv;
	position = me->get_org_position();
	flag = to_int(arg);
	name = me->get_org_name();
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (position == 0 || name == "" || name != who->get_org_name())
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	store = orgnpc->get_store();
	switch (flag)
	{
	case 10: // Dự Trữ

		if (store >= orgnpc->get_grade() * 500)
		{
			return;
		}
		if (me->get_save_2("orgtask.type") != 0)
		{
			result = sprintf("%s:\n    Nhiệm vụ Bang phái của ngươi chưa hoàn thành, không thể lĩnh nhiệm vụ mới\n", who->get_name());
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (time() - me->get_save_2("orgtask.time") < 0)
			me->set_save_2("orgtask.time", 0);
		if (time() - me->get_save_2("orgtask.time") < 1)
		{
			result = sprintf("%s:\n    Lĩnh nhiệm vụ mới cần 3 phút\n", who->get_name());
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		level = orgnpc->get_grade();
		//		if (MAIN_D->get_host_type()!=4 && MAIN_D->get_host_type()!=0)
		if (1)
		{
			switch (level)
			{
			case 1:
				size = 64;
				rand = 100 - 64;
				break;
			case 2:
				size = 100;
				rand = 130 - 100;
				break;
			case 3:
				size = 130;
				rand = 161 - 130;
				break;
			case 4:
				size = 161;
				rand = sizeof(task1);
				break;
			default:
				size = sizeof(task1);
				rand = 1;
				break;
			}
			base = size;
			i = random(size);
			me->set_save_2("orgtask.double", 0);
			if (level < 5)
			{
				if (random(100) < 5)
				{
					i = base + random(rand);
					if (i >= sizeof(task1))
						i = base;
					me->set_save_2("orgtask.double", 1);
				}
			}
			me->set_save_2("orgtask.status", 1);
			me->set_save_2("orgtask.name", task1[i]);
			me->set_save_2("orgtask.count", count1[i]);
			me->set_save_2("orgtask.unit", "个");
			me->set_save_2("orgtask.time", time());
		}
		else
		{
			switch (level)
			{
			case 1:
				size = 30;
				rand = 38 - 30;
				break;
			case 2:
				size = 38;
				rand = 46 - 38;
				break;
			case 3:
				size = 46;
				rand = 59 - 46;
				break;
			case 4:
				size = 59;
				rand = sizeof(task3);
				break;
			default:
				size = sizeof(task3);
				rand = 1;
				break;
			}
			base = size;
			i = random(size);
			me->set_save_2("orgtask.double", 0);
			if (level < 5)
			{
				if (random(100) < 5)
				{
					i = base + random(rand);
					if (i >= sizeof(task3))
						i = base;
					me->set_save_2("orgtask.double", 1);
				}
			}
			me->set_save_2("orgtask.status", 1);
			me->set_save_2("orgtask.name", task3[i]);
			me->set_save_2("orgtask.count", 10);
			me->set_save_2("orgtask.unit", "个");
			me->set_save_2("orgtask.time", time());
		}
		result = sprintf("%s:\n    Sắp tới Bang phái bởi vì phát triển quan hệ, cần dự trữ rất nhiều. Trước mắt Bang phái còn thiếu rất nhiều vật, ngươi đi tìm về đi\n", who->get_name());
		result += sprintf(ESC "Nhận nhiệm vụ\ntalk %x# info.11\n", getoid(who));
		result += sprintf(ESC "Rời khỏi\ntalk %x# info.12\n", getoid(who));
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 11:
		if (store >= orgnpc->get_grade() * 500)
		{
			return;
		}
		if (me->get_save_2("orgtask.status") == 1)
			me->set_save_2("orgtask.type", 1);
		if (me->get("tasklist") != 0)
		{
			send_user(me, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "Nhiệm Vụ Bang Phái");
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 10, "Dự Trữ");
		}
		break;
	case 12:
		me->set_save_2("orgtask.status", 0);
		break;
	case 20:
	case 21:
		if (me->get_save_2("orgtask.type") != 1)
		{
			result = sprintf("%s:\n    Bạn không có lĩnh nhiệm vụ Dự Trữ.\n", who->get_name());
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		name = me->get_save_2("orgtask.name");
		number = me->get_save_2("orgtask.count");
		list = me->get_save_2("orgtask.unit");
		inv = all_inventory(me, 1, MAX_CARRY * 4);
		inv -= ({0});
		count = 0;
		for (i = 0, size = sizeof(inv); i < size; i++)
		{
			if ((inv[i]->get_name() == name) && (inv[i]->is_legend_item() == 0))
			{
				if (inv[i]->get_max_combined() <= 1)
					count++;
				else
					count += inv[i]->get_amount();
			}
		}
		if (count < number)
		{
			if (!objectp(item = present("Rương Dự Trữ", me, 1, MAX_CARRY * 4)))
			{
				result = sprintf("%s:\n    Cần ngươi mua %d%s%s ? Làm việc phải có thuỷ chung, không thể bỏ nữa chừng, nếu có vấn đề gì thì hãy tới gặp Công Đức Lão Nhân.\n", who->get_name(), number, list, name);
				result += sprintf(ESC "Rời khỏi\nCLOSE\n");
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				return;
			}
		}

		if (flag == 20)
		{
			if (item)
			{
				result = sprintf("%s:\n    Bạn muốn tiêu hao 1 cái Rương Dự Trữ để hoàn thành nhiệm vụ phải không ?\n", who->get_name());
				result += sprintf(ESC "Xác nhận\ntalk %x# info.21\n", getoid(who));
				result += sprintf(ESC "Huỷ bỏ\nCLOSE\n");
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				break;
			}
			result = sprintf("%s:\n    Biểu hiện của ngươi thiệt không tồi, nhanh như vậy đã thu thập toàn bộ, bổn bang nếu ai cũng như ngươi thì chuyện hùng bá sẽ không còn là vấn đề, ta sẽ bẩm báo công lao của ngươi với Bang Chủ !\n", who->get_name());
			result += sprintf(ESC "Hoàn thành nhiệm vụ\ntalk %x# info.21\n", getoid(who));
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			break;
		}
		if (item)
		{
			//	send_user( me, "%c%d", 0x2d, getoid(item) );
			//                destruct(item);
			item->add_amount(-1);
		}
		else
			for (i = 0, size = sizeof(inv); i < size; i++)
			{
				if ((inv[i]->get_name() == name) && (inv[i]->is_legend_item() == 0))
				{
					if (inv[i]->get_max_combined() <= 1)
					{
						number--;
						send_user(me, "%c%d", 0x2d, getoid(inv[i]));
						destruct(inv[i]);
					}
					else
					{
						if (number > inv[i]->get_amount())
						{
							number -= inv[i]->get_amount();
							send_user(me, "%c%d", 0x2d, getoid(inv[i]));
							destruct(inv[i]);
						}
						else
						{
							inv[i]->add_amount(-number);
							number = 0;
						}
					}
					if (number <= 0)
						break;
				}
			}
		me->add_exp(2000 * me->get_online_rate() / 100);
		number = me->get_number();
		order = me->get_save_2("orgtask.order");
		order++;
		order = order * me->get_online_rate() / 100;
		orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number) + order);
		orgnpc->add_store(1);
		result = sprintf("Bạn hoàn thành nhiệm vụ Dự Trữ, kinh nghiệm tăng %d, điểm cống hiến Bang tăng %d \n", 2000 * me->get_online_rate() / 100, order * me->get_online_rate() / 100);
		if (me->get_save_2("orgtask.double"))
		{
			me->add_cash(2000 * me->get_online_rate() / 100);
			me->log_money("Nhiệm Vụ Bang Phái", 2000 * me->get_online_rate() / 100);
			"/sys/sys/count"->add_income("org", 2000 * me->get_online_rate() / 100);
			orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number) + 3 * me->get_online_rate() / 100);
			result += sprintf("Được thưởng %d điểm cống hiến Bang phái cùng %d lượng \n", 3 * me->get_online_rate() / 100, 2000 * me->get_online_rate() / 100);
		}
		if (order == 10 && random100() < me->get_online_rate())
		{
			if (me->get_level() >= 40 && random100() == 0)
			{
				item = new ("/item/01/0007");
			}
			else
				item = new ("sys/item/product"->get_random_mid_product());
			if (item)
			{
				if (USER_INVENTORY_D->can_carry(me, item) >= 1)
				{
					p = item->move(me, -1);
					item->add_to_user(p);
					send_user(me, "%c%s", '!', "Bạn nhận được " + item->get_name());
				}
				else
					destruct(item);
			}
			if (random100() < 5 * me->get_online_rate() / 100)
				"/quest/box"->give_box(me);
		}
		me->delete_save_2("orgtask");
		if (order >= 10)
			order = 0;
		me->set_save_2("orgtask.order", order);
		send_user(me, "%c%s", ';', result);
		send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 10, "");
		send_user(me, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "");
		break;
	case 30:
	case 31:
		char = orgnpc->get_trader();
		if ((!arrayp(char) || member_array(me->get_id(), char) == -1) && me->get_number() != orgnpc->get_master())
		{
			result = sprintf("%s:\n    Bạn không phải Thương Nhân, không thể nhận Tiền Giấy\n", who->get_name());
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (present("Ngân Phiếu", me, 1, MAX_CARRY * 4))
		{
			send_user(me, "%c%s", '!', "Ngươi đã lĩnh Ngân Phiếu");
			return;
		}
		//if( sizeof_inventory(me, 1, MAX_CARRY) >= MAX_CARRY )
		if (USER_INVENTORY_D->get_free_count(me) < 1)
		{
			send_user(me, "%c%s", '!', "Hành trang không đủ 1 chỗ trống");
			return;
		}
		level = me->get_level();
		gold = 50000;
		if (orgnpc->get_gold() < gold)
		{
			send_user(me, "%c%s", '!', "Bang Phái tài chính không đủ, không thể làm Thương Nhân");
			return;
		}
		if (flag == 30)
		{
			result = sprintf("%s:\n    Trong Bang không thể thiếu đi Thương Nhân được, đây cầm lấy đi, là %d lượng Ngân Phiếu, hãy thay bổn bang kiếm %d lượng rồi trở về\n", who->get_name(), gold, gold / 2);
			result += sprintf(ESC "Nhận nhiệm vụ\ntalk %x# info.31\n", getoid(who));
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			break;
		}
		orgnpc->add_gold(-gold);
		item = new ("/item/std/0002");
		item->set_orgin_money(gold);
		item->set_money(gold);
		if (p = item->move2(me, -1))
			item->add_to_user(p);
		else
			destruct(item);
		me->set_save_2("orgtask3.type", 1);
		me->set_save_2("orgtask3.money", gold);
		if (me->get("tasklist") != 0)
		{
			send_user(me, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "Nhiệm Vụ Bang Phái");
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 20, "Thương Nhân");
		}
		break;
	case 40:
	case 41:
		item = present("Ngân Phiếu", me, 1, MAX_CARRY * 4);
		if (!objectp(item) || item->get_money() < item->get_orgin_money() * 3 / 2)
		{
			result = sprintf("%s:\n    Như thế nào rồi Thương Nhân ? Mỗi quốc gia đều có 1 thằng cha Thương Nhân buôn bán, ngươi phải suy nghĩ động não, giá thấp thì mua, giá cao thì bán, OK chưa hả \n", who->get_name());
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (flag == 40)
		{
			result = sprintf("%s:\n    Ha Ha ta quả nhiên không nhìn lầm người, ngươi quả nhiên là một Thương Nhân thiên tài,có ngươi thì Bang của chúng ta sẽ càng ngày càng mạnh.\n", who->get_name());
			result += sprintf(ESC "Hoàn thành nhiệm vụ\ntalk %x# info.41\n", getoid(who));
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			break;
		}
		orgnpc->add_gold(item->get_money());
		FAMILY_D->org_channel(name, 0, sprintf(HIR "Thương Nhân %s vì bổn bang kiếm được %d lượng", me->get_name(), item->get_money() - item->get_orgin_money()));
		gold = me->get_level() * 100;
		gold = gold * me->get_online_rate() / 100;
		contrib = me->get_level() / 4;
		contrib = contrib * me->get_online_rate() / 100;
		exp = NPC_ENERGY_D->get_exp_bonus(me->get_level()) * 32;
		exp = exp * me->get_online_rate() / 100;
		result = "Bạn hoàn thành nhiệm vụ Thương Nhân";
		if (random(100) < 10 * me->get_online_rate() / 100)
		{
			switch (random(3))
			{
			case 0:
				gold *= 2;
				result += HIR "Nhận được ngoài ý muốn, ngân lượng gấp bội" BLK;
				break;
			case 1:
				contrib *= 2;
				result += HIR "Nhận được ngoài ý muốn, Cống hiến gấp bội" BLK;
				break;
			case 2:
				exp *= 2;
				result += HIR "Nhận được ngoài ý muốn, kinh nghiệm gấp bội" BLK;
				break;
			}
		}
		me->add_exp(exp);
		me->add_cash(gold);
		me->log_money("Thương Nhân", gold);
		"/sys/sys/count"->add_income("orgtrader", gold);
		number = me->get_number();
		orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number) + contrib);
		result += sprintf("Kinh nghiệm tăng %d, Cống hiến Bang tăng %d, Ngân lượng tăng %d \n", exp, contrib, gold);
		send_user(me, "%c%s", ';', result);
		send_user(me, "%c%d", 0x2d, getoid(item));
		destruct(item);
		me->delete_save_2("orgtask3");
		send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 20, "");
		send_user(me, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "");

		break;
	}
}

// 帮派的天机院主
void do_look_5(object me, object who)
{
	string result, name;
	int position, store;
	object orgnpc;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	result = sprintf(" %s :\n Ta là viện chủ Thiên Cơ Viện chịu trách nhiệm khai thác kỹ năng Bang phái của bổn bang, không biết các hạ tìm ta có việc gì?\n", who->get_name());
	position = me->get_org_position();
	name = who->get_org_name();
	if (name == "")
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	if (position > 0 && me->get_org_name() == name)
	{
		result += sprintf(ESC "Học kỹ năng\ntalk %x# skill\n", getoid(who));
		if (position >= 8)
		{
			result += sprintf(ESC "Nghiên cứu kĩ năng\ntalk %x# info.10\n", getoid(who));
		}
		result += sprintf(ESC "Tìm hiểu tình hình kỹ năng Bang phái trước kia\ntalk %x# info.20\n", getoid(who));
	}
	result += sprintf(ESC "Rời khỏi\nCLOSE\n");
	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
}

// 天机院主的相关函数
void do_info_5(object me, object who, string arg)
{
	int position, flag, number, i, size, level, time, degree, speed, len, *search;
	string result, name, list, *key;
	object orgnpc, city, *char, item, file;
	mapping skls;
	position = me->get_org_position();
	flag = to_int(arg);
	name = me->get_org_name();
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (position == 0 || name == "" || name != who->get_org_name())
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	skls = orgnpc->get_skill_dbase();
	size = 0;
	number = sizeof(skls);
	key = keys(skls);
	for (i = 0; i < number; i++)
	{
		if (orgnpc->get_skill(to_int(key[i])) > 1)
			size++;
	}
	switch (flag)
	{
	case 10:
	case 11:
		if (position < 8)
			return;
		if (orgnpc->get_science() >= orgnpc->get_grade() * 4)
		{
			result = sprintf("%s:\n    Hiện tại bổn bang nghiên cứu đã đạt tới mức hạn cao nhất %d điểm, \n", who->get_name(), orgnpc->get_grade() * 4);
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		time = orgnpc->get_sciencetime();
		if (time > 0)
		{
			if (time() > time)
			{
				orgnpc->add_science(1);
				orgnpc->set_sciencetime(0);
				char = orgnpc->get("comrade");
				if (char && sizeof(char) > 0)
				{
					for (i = 0; i < sizeof(char); i++)
						char[i]->set_level(orgnpc->get_science());
				}
				orgnpc->save();
				FAMILY_D->org_channel(name, 0, sprintf(HIR "Bang phái đã tăng lên 1 điểm nghiên cứu, hiện bây giờ Bang Phái đã có %d điểm nghiên cứu", orgnpc->get_science()));
			}
			else
			{
				result = sprintf("%s:\n    Hiện tại Bang phái đã khai phá nghiên cứu, chỉ cần đợi %d phút nữa là có thể tháy được thành quả\n", who->get_name(), (time - time()) / 60);
				result += sprintf(ESC "Rời khỏi\nCLOSE\n");
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				return;
			}
		}
		if (flag == 10)
		{
			result = sprintf("%s:\n    Tăng lên 1 điểm nghiên cứu cần tiêu hao 300 vạn tài chính, 100 điểm dự trữ, tiêu hao 48 giờ, muốn tăng không ?\n", who->get_name());
			result += sprintf(ESC "Xác nhận\ntalk %x# info.11\n", getoid(who));
			result += sprintf(ESC "Huỷ bỏ\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		}
		else
		{
			if (orgnpc->get_gold() < 3000000 || orgnpc->get_store() < 100)
			{
				result = sprintf("%s:\n    Hiện tại trong Bang tài chính và điểm dự trữ không đủ\n", who->get_name());
				result += sprintf(ESC "Rời khỏi\nCLOSE\n");
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			}
			else
			{
				orgnpc->add_gold(-3000000);
				orgnpc->set_store(orgnpc->get_store() - 100);
				orgnpc->set_sciencetime(time() + 48 * 3600);
				orgnpc->save();
				result = sprintf("%s:\n    Hiện tại Bang phái đã khai phá nghiên cứu, chỉ cần đợi 48 giờ nữa sẽ thấy được thành quả\n", who->get_name());
				result += sprintf(ESC "Rời khỏi\nCLOSE\n");
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			}
		}
		break;
	case 20:
		result = sprintf(" %s :\n Hiện tại sức nghiên cứu của Bang phái là %d , kỹ năng đã nghiên cứu là %d , số lượng kỹ năng nghiên cứu đồng thời lớn nhất là %d .\n", who->get_name(), orgnpc->get_science(), size, 1 + orgnpc->get_science() / 5);
		len = strlen(result);
		i = orgnpc->get_research();
		if (i > 0 && objectp(file = load_object(sprintf("/skill/%02d/%04d", i / 100, i))))
		{
			result += sprintf("Trước mắt Nghiên cứu Kĩ năng là %s，", file->get_name());
			switch (orgnpc->get_research_level())
			{
			case 1:
				list = "Bình thường";
				break;
			case 2:
				list = "Nhanh hơn";
				break;
			default:
				list = "Cấp tốc";
				break;
			}
			speed = 400 + orgnpc->get_research_level() * 400;
			result += "Đang lấy " + list + " tốc độ nghiên cứu trung";
			level = orgnpc->get_skill(i);
			degree = orgnpc->get_skill_degree(i);
			level++;
			result += sprintf("Tin tưởng %d giờ sau có thể tăng lên 1 bậc\n", (level * level * 5 - degree) / speed + 1);
		}
		skls = orgnpc->get_researchs();
		search = keys(skls);
		size = sizeof(search);
		if (size > 0)
		{
			for (i = 0; i < size; i++)
			{
				if (search[i] > 0 && objectp(file = load_object(sprintf("/skill/%02d/%04d", search[i] / 100, search[i]))))
				{
					result += sprintf("    Trước mắt nghiên cứu " HIR "%s" NOR "，", file->get_name());
					switch (skls[search[i]])
					{
					case 1:
						list = "Bình thường";
						break;
					case 2:
						list = "Nhanh hơn";
						break;
					default:
						list = "Cấp tốc";
						break;
					}
					speed = 400 + skls[search[i]] * 400;
					result += "Đang lấy " + list + " tốc độ nghiên cứu trung";
					level = orgnpc->get_skill(search[i]);
					degree = orgnpc->get_skill_degree(search[i]);
					level++;
					result += sprintf("Tinh tưởng %d giờ sau có thể tăng lên 1 bậc\n", (level * level * 5 - degree) / speed + 1);
				}
			}
		}
		if (len == strlen(result))
			result += "Hiện không có kỹ năng nghiên cứu.\n";
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	}
}

// 帮派的神机院主
void do_look_6(object me, object who)
{
	string result, name, *list;
	int position, store, p, i, size, count;
	object orgnpc, item;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	result = sprintf(" %s :\n Ta là viện chủ Thần Cơ Viện, mỗi ngày vào 12 giờ và 24 giờ chỗ ta sản xuất được 1 số vật phẩm. Chỉ cần quy mô của bổn bang càng lớn mạnh, phẩm chất vật phẩm mà ta có thể làm ra sẽ càng cao. Sao? Muốn mua gì phải không?\n", who->get_name());
	position = me->get_org_position();
	name = who->get_org_name();
	if (name == "")
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	// 检查是否过了制作的时间
	who->check_item();
	list = orgnpc->get_productfile2();
	if (position >= ORG_TANGZHU && me->get_org_name() == name)
	{
		size = sizeof(list);
		if (size == 0)
		{
			if (orgnpc->get_stable() < 1000)
			{
				result += ESC "Bang Phái độ Yên ổn không đủ, không thể chế tác\nCLOSE\n";
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				return;
			}
			result += ESC "Sản phẩm bán ra\nCLOSE\n";
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		count = 0;
		for (i = 0; i < size; i++)
		{
			if (list[i] != "")
			{
				result += sprintf(ESC "Tiêu hao %d lượng để mua %s\ntalk %x# info.%d\n", 20000 * orgnpc->get_grade(), list[i]->get_name(), getoid(who), i + 1);
				count++;
			}
		}
		if (count == 0)
		{
			count = orgnpc->get_buytime();
			if (count)
				result += sprintf(ESC "Sản phẩm đã %s bán ra\nCLOSE\n", short_time(count));
			else
				result += ESC "Sản phẩm bán ra\nCLOSE\n";
		}
		else
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}

	result += sprintf(ESC "Rời khỏi\nCLOSE\n");
	send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
}

// 帮派的神机院主
void do_info_6(object me, object who, string arg)
{
	string result, name, *list;
	int position, store, p, i, size;
	object orgnpc, item;
	position = me->get_org_position();
	name = who->get_org_name();
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (name == "")
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	position = me->get_org_position();
	if (position < 1 || name != me->get_org_name())
	{
		return;
	}
	if (position < ORG_TANGZHU)
	{
		return;
	}
	list = orgnpc->get_productfile2();
	size = sizeof(list);
	if (size == 0)
	{
		return;
	}
	i = to_int(arg);
	if (i < 1 || i > size)
		return;
	i--;
	if (list[i] == "")
		return;
	if (me->get_cash() < orgnpc->get_grade() * 20000)
	{
		notify("Tiền mặt không đủ");
		return;
	}
	me->add_cash(-orgnpc->get_grade() * 20000);
	me->log_money("Bang Phái mua sản phẩm", -orgnpc->get_grade() * 20000);
	"/sys/sys/count"->add_use("orgbuy", orgnpc->get_grade() * 20000);
	item = new (list[i]);
	if (!item)
		return;
	if (USER_INVENTORY_D->can_carry(me, item) < 1)
	{
		notify("Hành trang không đủ chỗ trống");
		destruct(item);
		return;
	}
	notify(sprintf("Bạn mua %s", item->get_name()));
	if (p = item->move(me, -1))
	{
		item->add_to_user(p);
	}
	else
		destruct(item);
	list[i] = "";
	orgnpc->set_productfile2(list);
	orgnpc->set_buytime(time());
	orgnpc->save();
}

// 提升帮派规模
void do_upgrade(object me, object who, string arg)
{
	string result, name;
	int position, grade, stable, favour, store, gold, time;
	object orgnpc, war;
	position = me->get_org_position();
	name = who->get_org_name();
	if (name == "")
		return;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		result = sprintf("%s:\n    Vui lòng nâng quy mô ở kênh Bang Phái\n", who->get_name());
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	if (name != me->get_org_name())
		return;
	if (position < 9)
		return;
	grade = orgnpc->get_grade();
	if (grade >= 5)
		return;
	switch (grade)
	{
	case 1:
		stable = 2000;
		break;
	case 2:
		stable = 3000;
		break;
	case 3:
		stable = 5000;
		break;
	case 4:
		stable = 8000;
		break;
	}
	favour = stable;
	store = grade * 300;
	gold = 2000000 * grade;
	time = orgnpc->get_gradetime();
	if (time > 0)
	{
		if (time < time())
		{
			orgnpc->set_gradetime(0);
			orgnpc->set_grade(grade + 1);
			FAMILY_D->org_channel(name, 0, sprintf(HIR "Bang Phái quy mô tăng lên 1, hiện quy mô của Bang là %d.", grade + 1));
		}
		else
		{
			result = sprintf("%s:\n    Quy mô tăng lên còn thừa %d phút\n", who->get_name(), (time - time()) / 60);
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
	}
	if (arg == "" || arg == 0)
	{
		result = sprintf("%s:\n    Trước mắt quy mô Bang phái ngươi là %d, Tăng lên cấp tiếp theo đều cần độ Yên ổn và Nhân Khí là %d, hơn nữa còn tiêu hao %d dự trữ, %d tài chính, sau khi xác nhận thăng cấp 10 phút sau quái vật sẽ xâm chiếm bổn bang, nếu có thể giết hết quái vậy thì 24h sau quy mô sẽ tăng lên, nếu thất bại thì tất cả sẽ trở về con số 0, ngươi xác nhận không ?\n", who->get_name(), grade, favour, store, gold);
		result += sprintf(ESC "Xác nhận\ntalk %x# upgrade.1\n", getoid(who));
		result += sprintf(ESC "Huỷ bỏ\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (orgnpc->get_gradewartime())
	{
		stable = (orgnpc->get_gradewartime() - time()) / 60;
		result = sprintf("%s:\n    Bổn bang %d phút sau bị quái vật xâm chiếm, nếu có thể đánh lui thì 24 tiếng sau có thể thuận lợi tăng lên quy mô\n", who->get_name(), stable);
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (orgnpc->get_stable() < stable)
	{
		result = sprintf("%s:\n    Bang Phái độ Yên ổn không đủ %d\n", who->get_name(), stable);
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (orgnpc->get_favour() < favour)
	{
		result = sprintf("%s:\n    Bang Phái Nhân Khí không đủ %d\n", who->get_name(), favour);
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (orgnpc->get_store() < store)
	{
		result = sprintf("%s:\n    Bang Phái Dự trữ không đủ %d\n", who->get_name(), store);
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (orgnpc->get_gold() < gold)
	{
		result = sprintf("%s:\n    Bang Phái Tài chính không đủ %d\n", who->get_name(), gold);
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		return;
	}
	if (MAIN_D->get_host_type() == 2)
	{
		orgnpc->set_store(orgnpc->get_store() - store);
		orgnpc->set_gold(orgnpc->get_gold() - gold);
		orgnpc->set_gradetime(time() + 24 * 3600);
		orgnpc->save();
		FAMILY_D->org_channel(name, 0, HIR "Bổn bang đã thăng cấp quy mô, hiệu quả trong 24h sau");
		return;
	}
	war = new ("/inh/std/upgrade");
	if (war)
	{
		orgnpc->set_store(orgnpc->get_store() - store);
		orgnpc->set_gold(orgnpc->get_gold() - gold);
		orgnpc->set_gradewartime(time() + 600);
		orgnpc->set_wardamage(0);
		orgnpc->save();
		war->set_org_name(name);
		war->set_z(orgnpc->get("z"));
		war->set_grade(orgnpc->get_grade());
		//		war->add_heart_sec(500);
		FAMILY_D->org_channel(name, 0, HIR "Bổn Bang đã muốn thăng cấp quy mô, 10 phút sau quái vật sẽ xâm nhập, toàn thể thành viên hãy quay về Bang phái");
	}
}

// 帮派总管的天枢院任务
void do_quest(object me, object who, string arg)
{
	int position, flag, number, i, size, level, count, gold, p, type, x, y, z, order, exp, pot, cash;
	string result, name, list;
	object orgnpc, city, *char, item, file, npc;
	object *inv;
	position = me->get_org_position();
	flag = to_int(arg);
	name = me->get_org_name();
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Để sử dụng tính năng Bang Phái hãy về Kênh Bang Phái");
		return;
	}
	if (position == 0 || name == "" || name != who->get_org_name())
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	number = me->get_number();
	switch (flag)
	{
	case 10:
		if (me->get_save_2("orgtask2.type") != 0)
		{
			result = sprintf("%s:\n    Nhiệm vụ Xu Thiện của ngươi chưa hoàn thành, không thể nhận nhiệm vụ mới\n", who->get_name());
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (time() - me->get_save_2("orgtask2.time") < 1)
		{
			result = sprintf("%s:\n    Làm việc phải cẩn thận, không cần nóng vội !!\n", who->get_name());
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		result = sprintf("%s:\n    Bổn bang công việc bề bộn, hiện tại ta có một chuyện nhờ ngươi đi làm, ngươi nhất định phải hoàn thành !!\n", who->get_name());
		result += sprintf(ESC "Nhận\ntalk %x# quest.11\n", getoid(who));
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 11:
		if (me->get_save_2("orgtask2.type") != 0)
		{
			result = sprintf("%s:\n    Nhiệm vụ Xu Thiện của ngươi chưa hoàn thành, không thể nhận nhiệm vụ mới\n", who->get_name());
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (time() - me->get_save_2("orgtask2.time") < 1)
		{
			result = sprintf("%s:\n    Lĩnh nhiệm vụ Xu Thiện phải đợi 3 phút\n", who->get_name());
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		type = 1 + random(6);
		if (is_god(me))
		{
			if (me->get("lb"))
				type = me->get("lb");
		}
		send_user(me, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "Nhiệm Vụ Bang Phái");
		if (type == 2)
			type = 1;
		switch (type)
		{
		case 1:
			npc = new ("/npc/org/0100");
			npc->set("user", me->get_number());
			npc->set_name(name + "Người Đưa Tin");
			z = 10 * (1 + random(8));
			p = get_xy_point(z, IS_CHAR_BLOCK);
			if (!p)
				return;
			npc->add_to_scene(z, p / 1000, p % 1000, 3);
			file = load_object(sprintf("/map/map/%03d", z));
			result = sprintf("%s:\n    %s Người Đưa Tin ở （%s %d, %d） bất hạnh bị ám toán, mà hắn đang giữ trong người cơ mật tình báo,  ngươi hãy đem thuốc chữa thương này tới tay %s Người Đưa Tin, để đảm bảo hắn có thể an toàn quay về\n", who->get_name(), name, file->get_name(), get_x(npc), get_y(npc), name);
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			me->set_save_2("orgtask2.place", file->get_name());
			me->set_save_2("orgtask2.x", get_x(npc));
			me->set_save_2("orgtask2.y", get_y(npc));
			me->set_2("orgtask2.npc", npc);
			item = new ("/item/01/0003");
			if (p = item->move(me, -1))
			{
				item->add_to_user(p);
			}
			else
				destruct(item);
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 1, "Phù Nguy Cứu Cấp");
			break;
		case 2:
			npc = new ("/npc/org/0101");
			npc->set("user", me->get_number());
			npc->set_owner(me);
			size = sizeof(task2);
			i = random(size);
			npc->set_name(sprintf("%s Hài Tử(%d)", task2[i], me->get_number()));
			me->set_save_2("orgtask2.name", task2[i]);
			me->set_save_2("orgtask2.id", sprintf("%x#", getoid(npc)));
			me->set_2("orgtask2.npc", npc);
			z = get_z(who);
			x = get_x(who);
			y = get_y(who);
			if (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
			{
				x = p / 1000;
				y = p % 1000;
				npc->add_to_scene(z, x, y, 3);
			}
			result = sprintf("%s:\n    Một thành viên bổn bang đưa 1 em nhỏ trở về, biết được là %s Hài Tử, để làm tốt quan hệ ngươi phải đưa %s Hài Tử trở về\n", who->get_name(), task2[i], task2[i]);
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 2, "Mê Lộ Hài Đồng");
			break;
		case 3:
			npc = new ("/npc/org/0102");
			npc->set("user", me->get_number());
			npc->set_name(name + " Bảo Rương");
			z = 10 * (1 + random(8));
			p = get_xy_point(z, IS_CHAR_BLOCK);
			if (!p)
				return;
			npc->add_to_scene(z, p / 1000, p % 1000, 3);
			file = load_object(sprintf("/map/map/%03d", z));
			result = sprintf("%s:\n    Bảo vật bổn bang đánh rơi ở %s (%d,%d) , bảo vật này quen hệ đến tồn vong bổn bang, ngươi hãy mau đi tìm về\n", who->get_name(), file->get_name(), get_x(npc), get_y(npc));
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			me->set_save_2("orgtask2.place", file->get_name());
			me->set_save_2("orgtask2.x", get_x(npc));
			me->set_save_2("orgtask2.y", get_y(npc));
			me->set_save_2("orgtask2.id", sprintf("%x#", getoid(npc)));
			me->set_2("orgtask2.npc", npc);
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 3, "Bảo Vật Di Thất");
			break;
		case 4:
			size = sizeof(task2);
			i = random(size);
			me->set_save_2("orgtask2.name", task2[i]);
			result = sprintf("%s:\n    Một vị đệ tử bổn bang tưởng niệm thân nhân %s, vì ổn định bang chúng ngươi hãy đem lá thư này đến tay thân nhân của hắn\n", who->get_name(), task2[i]);
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			item = new ("/item/01/0005");
			if (p = item->move(me, -1))
			{
				item->add_to_user(p);
			}
			else
				destruct(item);
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 4, "Thiên Lí Tống Thư Nhà");
			break;
		case 5:
			size = sizeof(food);
			i = random(size);
			me->set_save_2("orgtask2.name", food[i]);
			result = sprintf("%s:\n    Hiện tại thiên hạ thái bình, không rung chuyển, thừa lúc này ngươi hãy đi thu thập 1 cái %s \n", who->get_name(), food[i]);
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 5, "Cơm No Áo Ấm");
			break;
		case 6:
			npc = new ("/npc/org/0103");
			npc->set("user", me->get_number());
			npc->set("target", me->get_name());
			npc->init_level(me->get_level());
			z = 10 * (1 + random(8));
			p = get_xy_point(z, IS_CHAR_BLOCK);
			if (!p)
				return;
			npc->add_to_scene(z, p / 1000, p % 1000, 3);
			file = load_object(sprintf("/map/map/%03d", z));
			result = sprintf("%s:\n    Nghe nói có %s xuất hiện ở %s (%d,%d) làm hại dân chúng, ngươi hãy đến diệt trừ hắn\n", who->get_name(), npc->get_name(), file->get_name(), get_x(npc), get_y(npc));
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			me->set_save_2("orgtask2.place", file->get_name());
			me->set_save_2("orgtask2.name", npc->get_name());
			me->set_save_2("orgtask2.x", get_x(npc));
			me->set_save_2("orgtask2.y", get_y(npc));
			me->set_2("orgtask2.npc", npc);
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 6, "Trừ Ác Phù Nhược");
			break;
		}
		me->set_save_2("orgtask2.type", type);
		me->set_save_2("orgtask2.status", 1);
		me->set_save_2("orgtask2.time", time());
		break;
	case 20:
	case 21:
		switch (me->get_save_2("orgtask2.type"))
		{
		case 3:
			item = present("Di Thất Bảo Vật", me, 1, MAX_CARRY * 4);
			if (!objectp(item))
			{
				result = sprintf("%s:\n    Ngươi không hoàn thành chuyện của ngươi ư, làm vinh dự cho bổn bang là trách nhiệm mỗi thành viên, nếu Bang Chủ biết được sẽ trách phạt ngươi đấy\n", who->get_name());
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				return;
			}
			break;
		case 5:
			list = me->get_save_2("orgtask2.name");
			inv = all_inventory(me, 1, MAX_CARRY * 4);
			inv -= ({0});
			count = 0;
			for (i = 0, size = sizeof(inv); i < size; i++)
			{
				if (inv[i]->get_name() == list)
				{
					if (inv[i]->get_max_combined() <= 1)
						count++;
					else
						count += inv[i]->get_amount();
				}
			}
			if (count < 1)
			{
				result = sprintf("%s:\n    Ngươi không hoàn thành chuyện của ngươi ư, làm vinh dự cho bổn bang là trách nhiệm mỗi thành viên, nếu Bang Chủ biết được sẽ trách phạt ngươi đấy\n", who->get_name());
				send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
				return;
			}
			break;
		default:
			result = sprintf("%s:\n    Ngươi không hoàn thành chuyện của ngươi ư, làm vinh dự cho bổn bang là trách nhiệm mỗi thành viên, nếu Bang Chủ biết được sẽ trách phạt ngươi đấy\n", who->get_name());
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		if (flag == 20)
		{
			result = sprintf("%s:\n    Ngươi làm rất tốt ! %s có ngươi trợ thủ sau này hùng bá sẽ không là vấn đề, ta sẽ báo cáo công lao của ngươi với Bang Chủ\n", who->get_name(), name);
			result += sprintf(ESC "Hoàn thành nhiệm vụ\ntalk %x# quest.21\n", getoid(who));
			result += sprintf(ESC "Rời khỏi\nCLOSE\n");
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
			return;
		}
		order = me->get_save_2("orgtask2.order");
		order++;
		level = me->get_level();
		exp = (level * 8 + order * order * level * 4) * 3 / 5;
		exp = exp * me->get_online_rate() / 100;
		pot = order * 10 + level;
		pot = pot * me->get_online_rate() / 100;
		cash = (500 + level * 6 * (order - 1)) * 3 / 6;
		cash = cash * me->get_online_rate() / 100;
		switch (me->get_save_2("orgtask2.type"))
		{
		case 3:
			send_user(me, "%c%d", 0x2d, getoid(item));
			destruct(item);
			orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number) + 1 + order * 2 / 9);
			orgnpc->add_stable(1);
			orgnpc->add_favour(1);
			me->add_potential(pot);
			me->add_cash(cash);
			me->add_exp(exp);
			me->log_money("Nhiệm Vụ Bang Phái", cash);
			"/sys/sys/count"->add_income("org", cash);
			send_user(me, "%c%s", ';', sprintf("Bạn nhận được %d kinh nghiệm, tiềm năng %d, ngân lượng %d, cống hiến %d, Nhân khí tăng 1 điểm, Yên ổn tăng 1 điểm ", exp, pot, cash, 1 + order * 2 / 9));
			me->delete_save_2("orgtask2");
			me->delete_2("orgtask2");
			if (order >= 10)
			{
				order = 0;
				if (random100() < 5 * me->get_online_rate() / 100)
					"/quest/box"->give_box(me);
			}
			me->set_save_2("orgtask2.order", order);
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 3, "");
			send_user(me, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "");
			break;
		case 5:
			count = 1;
			for (i = 0, size = sizeof(inv); i < size; i++)
			{
				if (inv[i]->get_name() == list)
				{
					if (inv[i]->get_max_combined() <= 1)
					{
						count--;
						send_user(me, "%c%d", 0x2d, getoid(inv[i]));
						destruct(inv[i]);
					}
					else
					{
						if (count > inv[i]->get_amount())
						{
							count -= inv[i]->get_amount();
							send_user(me, "%c%d", 0x2d, getoid(inv[i]));
							destruct(inv[i]);
						}
						else
						{
							inv[i]->add_amount(-count);
							count = 0;
						}
					}
					if (count <= 0)
						break;
				}
			}
			orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number) + 1 + order * 2 / 9);
			orgnpc->add_stable(2);
			orgnpc->add_favour(2);
			me->add_potential(pot);
			me->add_cash(cash);
			me->add_exp(exp);
			me->log_money("Nhiệm Vụ Bang Phái", cash);
			"/sys/sys/count"->add_income("org", cash);
			send_user(me, "%c%s", ';', sprintf("Bạn nhận được %d kinh nghiệm, tiềm năng %d, ngân lượng %d, cống hiến %d, Nhân khí tăng 2 điểm, Yên ổn tăng 2 điểm ", exp, pot, cash, 1 + order * 2 / 9));
			me->delete_save_2("orgtask2");
			me->delete_2("orgtask2");
			if (order >= 10)
			{
				if (random100() < 5 * me->get_online_rate() / 100)
					"/quest/box"->give_box(me);
				order = 0;
			}
			me->set_save_2("orgtask2.order", order);
			send_user(me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 5, "");
			send_user(me, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "");
			break;
		}
		break;
	case 30:
		if (position != 9)
			return;
		if (time() > orgnpc->get_demisstime())
			return;
		result = sprintf("%s:\n    Huỷ bỏ việc nhường chức vị, xác nhận không ?\n", who->get_name());
		result += sprintf(ESC "Xác nhận\ntalk %x# quest.31\n", getoid(who));
		result += sprintf(ESC "Rời khỏi\nCLOSE\n");
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result);
		break;
	case 31:
		if (position != 9)
			return;
		if (time() > orgnpc->get_demisstime())
			return;
		orgnpc->set_demissnumber(0);
		orgnpc->set_demisstime(0);
		orgnpc->save();
		FAMILY_D->org_channel(name, 0, sprintf(HIR "Bang Chủ %s trải qua lo lắng, quyết định không nhường chức vị nữa", who->get_name()));
		break;
	}
}

void init_org_place(int z, string name, object orgnpc)
{
	object npc, *all;
	int i;
	int *locate = ({
		87,
		123,
		95,
		129,
		95,
		117,
		107,
		126,
		121,
		111,
		110,
		102,
		86,
		140,
		77,
		134,
	});

	npc = new ("/npc/org/0010");
	npc->set_org_name(name);
	npc->set_name(sprintf(" %s Tổng Quản", name));
	npc->set("orgnpc", orgnpc);
	npc->add_to_scene(z, 79, 141, 2);
	set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
	npc = new ("/npc/org/0011");
	npc->set_org_name(name);
	npc->set("orgnpc", orgnpc);
	npc->add_to_scene(z, 67, 134, 2);
	set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
	npc = new ("/npc/org/0012");
	npc->set_org_name(name);
	npc->set("orgnpc", orgnpc);
	npc->add_to_scene(z, 114, 152, 2);
	set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
	npc = new ("/npc/org/0013");
	npc->set_org_name(name);
	npc->set("orgnpc", orgnpc);
	npc->add_to_scene(z, 58, 110, 2);
	set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
	npc = new ("/npc/org/0014");
	npc->set_org_name(name);
	npc->set("orgnpc", orgnpc);
	npc->add_to_scene(z, 67, 104, 6);
	set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
	npc = new ("/npc/org/0015");
	npc->set_org_name(name);
	npc->set("orgnpc", orgnpc);
	npc->add_to_scene(z, 110, 88, 2);
	set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
	npc = new ("/npc/org/0016");
	npc->set_org_name(name);
	npc->set("orgnpc", orgnpc);
	npc->add_to_scene(z, 139, 110, 2);
	set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
	//	npc = new ("/npc/org/qgl_amass");
	//	npc->set_org_name(name);
	//	npc->set("orgnpc", orgnpc);
	//	npc->add_to_scene(z, 82, 139, 3);
	//	set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
	all = ({});
	// Tiễn Tháp
	for (i = 0; i < 8; i++)
	{
		npc = new ("/npc/org/0017");
		npc->set_org_name(name);
		npc->set("orgnpc", orgnpc);
		npc->set_level(orgnpc->get_science());
		npc->add_to_scene(z, locate[2 * i], locate[2 * i + 1], 2);
		set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
		all += ({npc});
	}
	orgnpc->set("comrade", all);
}

void task_giveup(object player, int type)
{
	int time;
	object npc;
	if (type == 20)
		return; // 经商不能放弃
	send_user(player, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, type, "");
	send_user(player, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "");
	if (type < 10)
	{
		switch (type)
		{
		case 1:
		case 2:
		case 3:
		case 6:
			npc = player->get_2("orgtask2.npc");
			if (objectp(npc))
			{
				npc->remove_from_scene();
				destruct(npc);
			}
			break;
		}
		time = player->get_save_2("orgtask2.time");
		player->delete_save_2("orgtask2");
		player->set_save_2("orgtask2.time", time);
	}
	else if (type == 10)
	{
		time = player->get_save_2("orgtask.time");
		player->delete_save_2("orgtask");
		player->set_save_2("orgtask.time", time);
	}
}

void send_task_list(object who)
{
	int type;
	if (who->get_save_2("orgtask.type") == 0 && who->get_save_2("orgtask2.type") == 0 && who->get_save_2("orgtask3.type") == 0)
		return;
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "Nhiệm Vụ Bang Phái");
	type = who->get_save_2("orgtask.type");
	if (type > 0)
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 10, "Dự Trữ");
	type = who->get_save_2("orgtask2.type");
	switch (type)
	{
	case 1:
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 1, "Phù Nguy Cứu Cấp");
		break;
	case 2:
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 2, "Mê Lộ Hài Đồng");
		break;
	case 3:
		if (who->get_save_2("orgtask2.status") == 1)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 3, "Bảo Vật Di Thất");
		else
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 3, "Tống Hồi Bảo Vật Di Thất");
		break;
	case 4:
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 4, "Thiên Lí Tống Thư Nhà");
		break;
	case 5:
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 5, "Cơm No Áo Ấm");
		break;
	case 6:
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 6, "Trừ Ác Phù Nhược");
		break;
	}
	type = who->get_save_2("orgtask3.type");
	if (type > 0)
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 20, "Thương Nhân");
}

string get_task_str(object who, int iKind)
{
	string result, name, unit;
	int count, order, level;
	name = who->get_org_name();
	result = "";
	if (name == "")
		return result;
	order = who->get_save_2("orgtask2.order");
	level = who->get_level();
	switch (iKind)
	{
	case 1:
		result = sprintf(BLK "Phù Nguy Cứu Cấp\n" BLK "Trước mắt hoàn sổ: %d/10\n" BLK "Mục đích nhiệm vụ:\n" BLK "    Đem linh dược trị thương tới %s Người Đưa Tin\n" BLK "Nhiệm vụ miêu tả:\n" BLK "    %s Người Đưa Tin ở %s （%d,%d） bất hạnh bị ám toán, mà hắn đang giữ trong người cơ mật tình báo,  ngươi hãy đem thuốc chữa thương này tới tay %s Người Đưa Tin, để đảm bảo hắn có thể an toàn quay về\n" BLK "Phần thưởng nhiệm vụ: Cống hiến %d điểm\n" BLK "          Kinh nghiệm %d\n" BLK "          Tiềm năng %d\n" BLK "          Ngân lượng %d\n", order + 1, name, name, who->get_save_2("orgtask2.place"), who->get_save_2("orgtask2.x"), who->get_save_2("orgtask2.y"), name, 1 + (order + 1) * 2 / 9, (level * 8 + (order + 1) * (order + 1) * level * 4) * 3 / 5, (order + 1) * 10 + level, (500 + level * 6 * order) * 3 / 6);
		break;
	case 2:
		name = who->get_save_2("orgtask2.name");
		result = sprintf(BLK "Mê Lộ Hài Đồng\n" BLK "Trước mắt hoàn sổ: %d/10\n" BLK "Mục đích nhiệm vụ:\n" BLK "    Đem %s Hài Tử trở về %s\n" BLK "Nhiệm vụ miêu tả:\n" BLK "    Một thành viên bổn bang dẫn về một Hài Đồng, hắn là %s Hài Tử, để quan hệ dân chúng tốt hơn, ngươi phải đem hắn trở về, hắn sẽ ngụ ở %s %s\n" BLK "Phần thưởng nhiệm vụ: Cống hiến %d điểm\n" BLK "          Kinh nghiệm %d\n" BLK "          Tiềm năng %d\n" BLK "          Ngân lượng %d\n", order + 1, name, name, name, name, "/quest/escort"->get_country_name(name), "/quest/escort"->get_place_name(name), 1 + (order + 1) * 2 / 9, (level * 8 + (order + 1) * (order + 1) * level * 4) * 3 / 5, (order + 1) * 10 + level, (500 + level * 6 * order) * 3 / 6);
		break;
	case 3:
		result = sprintf(BLK "Di Thất Bảo Vật\n" BLK "Trước mắt hoàn sổ: %d/10\n" BLK "Mục đích nhiệm vụ:\n" BLK "    Tìm Di Thất Bảo Vật về\n" BLK "Nhiệm vụ miêu tả:\n" BLK "    Bảo vật bổn bang đánh rơi ở %s (%d,%d) , bảo vật này quen hệ đến tồn vong bổn bang, ngươi hãy mau đi tìm về\n" BLK "Phần thưởng nhiệm vụ: Cống hiến %d điểm\n" BLK "          Kinh nghiệm %d\n" BLK "          Tiềm năng %d\n" BLK "          Ngân lượng %d\n", order + 1, who->get_save_2("orgtask2.place"), who->get_save_2("orgtask2.x"), who->get_save_2("orgtask2.y"), 1 + (order + 1) * 2 / 9, (level * 8 + (order + 1) * (order + 1) * level * 4) * 3 / 5, (order + 1) * 10 + level, (500 + level * 6 * order) * 3 / 6);
		break;
	case 4:
		name = who->get_save_2("orgtask2.name");
		result = sprintf(BLK "Thiên Lí Tống Thư Nhà\n" BLK "Trước mắt hoàn sổ: %d/10\n" BLK "Mục đích nhiệm vụ:\n" BLK "    Đem Thư Nhà đưa cho %s\n" BLK "Nhiệm vụ miêu tả:\n" BLK "    Một đệ tử bổn bang tưởng niệm thân nhân %s, hắn ngụ ở %s %s, vì ổn định bang chúng, ngươi hãy đem thư đưa tới thân nhân của hắn\n" BLK "Phần thưởng nhiệm vụ: Cống hiến %d điểm\n" BLK "          Kinh nghiệm %d\n" BLK "          Tiềm năng %d\n" BLK "          Ngân lượng %d\n", order + 1, name, name, "/quest/escort"->get_country_name(name), "/quest/escort"->get_place_name(name), 1 + (order + 1) * 2 / 9, (level * 8 + (order + 1) * (order + 1) * level * 4) * 3 / 5, (order + 1) * 10 + level, (500 + level * 6 * order) * 3 / 6);
		break;
	case 5:
		name = who->get_save_2("orgtask2.name");
		result = sprintf(BLK "Cơm No Áo Ấm\n" BLK "Trước mắt hoàn sổ: %d/10\n" BLK "Mục đích nhiệm vụ:\n" BLK "    Thu thập 1 cái %s\n" BLK "Nhiệm vụ miêu tả:\n" BLK "    Hiện tại thiên hạ thái bình, không rung chuyển, thừa lúc này ngươi hãy đi thu thập 1 cái %s \n" BLK "Phần thưởng nhiệm vụ: Cống hiến %d điểm\n" BLK "          Kinh nghiệm %d\n" BLK "          Tiềm năng %d\n" BLK "          Ngân lượng %d\n", order + 1, name, name, 1 + (order + 1) * 2 / 9, (level * 8 + (order + 1) * (order + 1) * level * 4) * 3 / 5, (order + 1) * 10 + level, (500 + level * 6 * order) * 3 / 6);
		break;
	case 6:
		name = who->get_save_2("orgtask2.name");
		result = sprintf(BLK "Trừ Ác Phù Nhược\n" BLK "Trước mắt hoàn sổ: %d/10\n" BLK "Mục đích nhiệm vụ:\n" BLK "    Diệt trừ %s\n" BLK "Nhiệm vụ miêu tả:\n" BLK "    Gần đây nghe nói có %s xuất hiện ở %s (%d,%d) , ngươi hãy đến giệt trừ\n" BLK "Phần thưởng nhiệm vụ: Cống hiến %d điểm\n" BLK "          Kinh nghiệm %d\n" BLK "          Tiềm năng %d\n" BLK "          Ngân lượng %d\n", order + 1, name, name, who->get_save_2("orgtask2.place"), who->get_save_2("orgtask2.x"), who->get_save_2("orgtask2.y"), 1 + (order + 1) * 2 / 9, (level * 8 + (order + 1) * (order + 1) * level * 4) * 3 / 5, (order + 1) * 10 + level, (500 + level * 6 * order) * 3 / 6);
		break;
	case 10:
		name = who->get_save_2("orgtask.name");
		count = who->get_save_2("orgtask.count");
		unit = who->get_save_2("orgtask.unit");
		order = who->get_save_2("orgtask.order");
		result = sprintf(BLK "Gia tăng dự trữ\n" BLK "Trước mắt hoàn sổ: %d/10\n" BLK "Mục đích nhiệm vụ:\n" BLK "    Thu mua " HIR "%d%s%s" BLK "， giao cho Trưởng Phòng Tiên Sinh\n" BLK "Nhiệm vụ miêu tả:\n" BLK "    Sắp tới bổn bang vì nghiên cứu phát triển, hiện đang thiếu " HIR " %s " BLK ", bởi vậy Trưởng Phòng Tiên Sinh  uỷ thác ta đi tìm" HIR "%d%s%s" BLK "trở về\n" BLK "Phần thưởng nhiệm vụ: Cống hiến %d điểm\n" BLK "          Kinh nghiệm 2000\n", order + 1, count, unit, name, name, count, unit, name, order + 1);
		break;
	case 20:
		count = who->get_save_2("orgtask3.money");
		result = sprintf(BLK "Bang Phái Thương Nhân\n" BLK "Mục đích nhiệm vụ:\n" BLK "    Kiếm %d lượng, mang về cho Trưởng Phòng Tiên Sinh\n" BLK "Nhiệm vụ miêu tả:\n" BLK "    Thương Nhân là không thể thiếu trong Bang, Trưởng Phòng Tiên Sinh giao ta %d lượng Ngân Phiếu, muốn ta kiếm đủ %d lượng rồi mới được trở về \n" BLK "Phần thưởng nhiệm vụ: Cống hiến %d điểm\n", count / 2, count, count / 2, who->get_level() / 4);
		break;
	}
	return result;
}

void upgrade(object me)
{
	string name, *all, *names, file, name2;
	object orgnpc;
	mapping skls;
	int level, contrib, store, i, size, skill, level2, id;
	string *list = MAIN_D->getlist();
	int kenh = MAIN_D->get_kenh();
	name = me->get_org_name();
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", name));
	if (!objectp(orgnpc))
		return;
	if (kenh != KENH_BANG)
	{
		me->save();
		ghi_file(sprintf("bang/check%d.txt", KENH_BANG), sprintf("\nupgrade %s %d %s", name, me->get_number(), me->get_id()));
		return;
	}
	level = me->get_level();
	contrib = level * 12 / 10;
	if (level == 10)
		store = 200;
	else if (level == 20)
		store = 400;
	else if (level == 25)
		store = 800;
	else if (level == 30)
		store = 1200;
	else if (level > 30)
	{
		switch ((level - 31) / 5)
		{
		default:
			store = 1200 + ((level - 31) / 5) * 400;
			break;
		}
	}
	if (store > 0)
	{
		skls = orgnpc->get_skill_dbase();
		size = sizeof(skls);
		all = ({});
		names = sort_array(keys(skls), 1);
		for (i = 0; i < size; i++)
		{
			skill = to_int(to_int(names[i]));
			if (skill == 408 || skill == 409)
				continue;
			if (skill >= 430 && skill <= 438)
				continue;
			if (orgnpc->get_skill(skill) > 1)
			{
				all += ({names[i]});
			}
		}
		if (sizeof(all) == 0)
			all = ({"0109"});
		i = random(sizeof(all));
		skill = to_int(to_int(all[i]));
		level2 = orgnpc->get_skill(to_int(all[i]));

		orgnpc->improve_skill(to_int(all[i]), store);
		orgnpc->set_member_contribute(me->get_number(), orgnpc->get_member_contribute(me->get_number()) + contrib);
		orgnpc->save();
		if (load_object(file = SKILL->get_skill_file(skill)) && (file->is_basic_skill() || file->is_vita_skill()))
			name2 = file->get_name();
		else
			name2 = all[i];
		if (level2 < orgnpc->get_skill(to_int(all[i])))
			FAMILY_D->org_channel(name, 0, sprintf("Chúc  %s ( %d )đẳng cấp đạt đến cấp %d , Bang phái của" HIR " %s " NOR "Độ thuần thục tăng %d điểm. " HIR " %s " NOR "nâng lên cấp %d .", me->get_name(), me->get_number(), level, name2, store, name2, orgnpc->get_skill(to_int(all[i]))));
		else
			FAMILY_D->org_channel(name, 0, sprintf(" mừng %s ( %d )đẳng cấp đạt đến cấp %d , Bang phái của" HIR " %s " NOR "Độ thuần thục tăng %d điểm.", me->get_name(), me->get_number(), level, name2, store));
	}
}
//帮派群发信件
void org_mail(int id, string cName, string info)
{
	int i, size, number;
	object orgnpc;
	string cTmp, *nName, account;
	if (!stringp(info) || sizeof(info) == 0)
		return;
	orgnpc = CITY_ZHOU->get_2(sprintf("org.%s", cName));
	if (!objectp(orgnpc))
		return;
	size = orgnpc->sizeof_member_dbase();
	nName = orgnpc->get_all_member();
	for (i = 0; i < size; i++)
	{
		number = to_int(nName[i]);
		account = orgnpc->get_member_id(number);
		"/inh/user/mail"->sys_mail(account, number, info);
	}
}
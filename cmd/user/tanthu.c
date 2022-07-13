
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{
	string result, arg2;
	int type, i, size, gender, p;
	object *inv, item, item1;
	gender = me->get_gender();
	return 1;
	if (!objectp(item1 = present("Túi Quà Tân Thủ", me, 1, MAX_CARRY * 4)))
	{
		write_user(me, ECHO "Bạn không có Túi Quà Tân Thủ !");
		return 1;
	}
	if (me->get_save("tuiquatanthu") >= 1)
	{
		write_user(me, ECHO "Bạn đã sử dụng Túi quà Tân Thủ 1 lần rồi!");
		return 1;
	}
	if (USER_INVENTORY_D->get_free_count(me) < 6)
	{
		write_user(me, ECHO "Hành trang của bạn không đủ 6 chỗ trống!");
		return 1;
	}
	if (arg == 0)
	{
		if (me->get_level() < 10)
		{
			result = sprintf("Bạn đang sử dụng Túi quà Tân Thủ, xin hãy lựa chọn Môn Phái :\n");
			result += ESC "Đào Hoa Nguyên\ntanthu daohoanguyenhieu\n";
			result += ESC "Thục Sơn\ntanthu thucsonhieu\n";
			result += ESC "Cấm Vệ Quân\ntanthu camvequanhieu\n";
			result += ESC "Đường Môn\ntanthu duongmonhieu\n";
			result += ESC "Mao Sơn\ntanthu maosonhieu\n";
			result += ESC "Côn Luân\ntanthu conluanhieu\n";
			result += ESC "Vân Mộng Cốc\ntanthu vanmongcochieu\n";
			//	result += ESC "Hủy bỏ\n";
			send_user(me, "%c%s", ':', result);
			return 1;
		}
		else
		{
			item = new (sprintf("item/test/tuihoangkimtanthucap20"));
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new (sprintf("item/ngoai_trang/ngoaitrang%d", gender));
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
			return 1;
		}
		return 1;
	}
	if (arg == "daohoanguyenhieu")
	{
		if (me->get_save("tuiquatanthu") >= 1)
		{
			write_user(me, ECHO "Bạn đã sử dụng Túi quà Tân Thủ 1 lần rồi!");
			return 1;
		}
		if (me->get_level() >= 10)
		{
			write_user(me, ECHO "Bạn không thể sử dụng được nữa !");
			return 1;
		}
		if (gender == 1)
		{
			me->set_fam_name("Đào Hoa Nguyên");
			me->set_fam_master("Vô Ức");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Đào Hoa Nguyên", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0211, 30);
			me->set_skill(0212, 30);
			me->set_skill(0316, 30);
			me->set_skill(0317, 30);
			me->set_skill(0319, 30);
			item = new ("item/60/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/65/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/70/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang1");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(80);
			p = item->move2(me, -1);
			item->add_to_user(p);
			//	item = new("item/tuiquatanthuhieu/0010");
			//	item->set_amount(60);
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/09/0901");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		else
		{
			me->set_fam_name("Đào Hoa Nguyên");
			me->set_fam_master("Vô Ức");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Đào Hoa Nguyên", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0211, 30);
			me->set_skill(0212, 30);
			me->set_skill(0316, 30);
			me->set_skill(0317, 30);
			me->set_skill(0319, 30);
			item = new ("item/61/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/66/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/70/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang2");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(80);
			p = item->move2(me, -1);
			item->add_to_user(p);
			//	item = new("item/tuiquatanthuhieu/0010");
			//	item->set_amount(60);
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/09/0901");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		return 1;
	}
	if (arg == "thucsonhieu")
	{
		if (me->get_save("tuiquatanthu") >= 1)
		{
			write_user(me, ECHO "Bạn đã sử dụng Túi quà Tân Thủ 1 lần rồi!");
			return 1;
		}
		if (me->get_level() >= 10)
		{
			write_user(me, ECHO "Bạn không thể sử dụng được nữa !");
			return 1;
		}
		if (gender == 1)
		{
			me->set_fam_name("Thục Sơn");
			me->set_fam_master("Tử Hằng Đạo Nhân");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Thục Sơn", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0221, 30);
			me->set_skill(0231, 30);
			me->set_skill(0222, 30);
			me->set_skill(0325, 30);
			me->set_skill(0329, 30);
			item = new ("item/60/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/65/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/76/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang1");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0902");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		else
		{
			me->set_fam_name("Thục Sơn");
			me->set_fam_master("Tử Hằng Đạo Nhân");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Thục Sơn", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0221, 30);
			me->set_skill(0231, 30);
			me->set_skill(0222, 30);
			me->set_skill(0325, 30);
			me->set_skill(0329, 30);
			item = new ("item/61/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/66/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/2020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/76/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang2");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0902");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		return 1;
	}
	if (arg == "camvequanhieu")
	{
		if (me->get_save("tuiquatanthu") >= 1)
		{
			write_user(me, ECHO "Bạn đã sử dụng Túi quà Tân Thủ 1 lần rồi!");
			return 1;
		}
		if (me->get_level() >= 10)
		{
			write_user(me, ECHO "Bạn không thể sử dụng được nữa !");
			return 1;
		}
		if (gender == 1)
		{
			me->set_fam_name("Cấm Vệ Quân");
			me->set_fam_master("Quân Giáo Đầu");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Cấm Vệ Quân", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0241, 30);
			me->set_skill(0251, 30);
			me->set_skill(0242, 30);
			me->set_skill(0348, 30);
			me->set_skill(0349, 30);
			item = new ("item/60/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/65/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/74/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang1");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(80);
			p = item->move2(me, -1);
			item->add_to_user(p);
			//	item = new("item/tuiquatanthuhieu/0010");
			//	item->set_amount(60);
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/09/0903");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		else
		{
			me->set_fam_name("Cấm Vệ Quân");
			me->set_fam_master("Quân Giáo Đầu");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Cấm Vệ Quân", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0241, 30);
			me->set_skill(0251, 30);
			me->set_skill(0242, 30);
			me->set_skill(0348, 30);
			me->set_skill(0349, 30);
			item = new ("item/61/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/66/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/3020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/74/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang2");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(80);
			p = item->move2(me, -1);
			item->add_to_user(p);
			//	item = new("item/tuiquatanthuhieu/0010");
			//	item->set_amount(60);
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/09/0903");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		return 1;
	}
	if (arg == "duongmonhieu")
	{
		if (me->get_save("tuiquatanthu") >= 1)
		{
			write_user(me, ECHO "Bạn đã sử dụng Túi quà Tân Thủ 1 lần rồi!");
			return 1;
		}
		if (me->get_level() >= 10)
		{
			write_user(me, ECHO "Bạn không thể sử dụng được nữa !");
			return 1;
		}
		if (gender == 1)
		{
			me->set_fam_name("Đường Môn");
			me->set_fam_master("Đường Bưu");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Đường Môn", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0261, 30);
			me->set_skill(0363, 30);
			me->set_skill(0364, 30);
			me->set_skill(0365, 30);
			me->set_skill(0368, 30);
			item = new ("item/60/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/65/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/71/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang1");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0904");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		else
		{
			me->set_fam_name("Đường Môn");
			me->set_fam_master("Đường Bưu");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Đường Môn", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0261, 30);
			me->set_skill(0363, 30);
			me->set_skill(0364, 30);
			me->set_skill(0365, 30);
			me->set_skill(0368, 30);
			item = new ("item/61/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/66/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/4020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/71/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang2");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0904");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		return 1;
	}
	if (arg == "maosonhieu")
	{
		if (me->get_save("tuiquatanthu") >= 1)
		{
			write_user(me, ECHO "Bạn đã sử dụng Túi quà Tân Thủ 1 lần rồi!");
			return 1;
		}
		if (me->get_level() >= 10)
		{
			write_user(me, ECHO "Bạn không thể sử dụng được nữa !");
			return 1;
		}
		if (gender == 1)
		{
			me->set_fam_name("Mao Sơn");
			me->set_fam_master("Linh Toán Tử");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Mao Sơn", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0271, 30);
			me->set_skill(0413, 30);
			me->set_skill(0414, 30);
			me->set_skill(0417, 30);
			me->set_skill(0418, 30);
			item = new ("item/60/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/65/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/77/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang1");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0905");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		else
		{
			me->set_fam_name("Mao Sơn");
			me->set_fam_master("Linh Toán Tử");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Mao Sơn", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0271, 30);
			me->set_skill(0413, 30);
			me->set_skill(0414, 30);
			me->set_skill(0417, 30);
			me->set_skill(0418, 30);
			item = new ("item/61/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/66/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/5020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/77/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang2");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0905");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		return 1;
	}
	if (arg == "conluanhieu")
	{
		if (me->get_save("tuiquatanthu") >= 1)
		{
			write_user(me, ECHO "Bạn đã sử dụng Túi quà Tân Thủ 1 lần rồi!");
			return 1;
		}
		if (me->get_level() >= 10)
		{
			write_user(me, ECHO "Bạn không thể sử dụng được nữa !");
			return 1;
		}
		if (gender == 1)
		{
			me->set_fam_name("Côn Luân");
			me->set_fam_master("Văn Xương Chân Quân");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Côn Luân", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0421, 30);
			me->set_skill(0422, 30);
			me->set_skill(0423, 30);
			me->set_skill(0424, 30);
			me->set_skill(0425, 30);
			item = new ("item/60/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/65/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/78/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang1");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0906");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		else
		{
			me->set_fam_name("Côn Luân");
			me->set_fam_master("Văn Xương Chân Quân");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Côn Luân", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0421, 30);
			me->set_skill(0422, 30);
			me->set_skill(0423, 30);
			me->set_skill(0424, 30);
			me->set_skill(0425, 30);
			item = new ("item/61/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/66/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/6020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/78/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang2");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0906");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		return 1;
	}
	if (arg == "vanmongcochieu")
	{
		if (me->get_save("tuiquatanthu") >= 1)
		{
			write_user(me, ECHO "Bạn đã sử dụng Túi quà Tân Thủ 1 lần rồi!");
			return 1;
		}
		if (me->get_level() >= 10)
		{
			write_user(me, ECHO "Bạn không thể sử dụng được nữa !");
			return 1;
		}
		if (gender == 1)
		{
			me->set_fam_name("Vân Mộng Cốc");
			me->set_fam_master("Tô Tần");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Vân Mộng Cốc", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0281, 30);
			me->set_skill(0501, 30);
			me->set_skill(0511, 30);
			me->set_skill(0531, 30);
			me->set_skill(0591, 30);
			item = new ("item/60/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/65/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/79/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang1");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0907");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		else
		{
			me->set_fam_name("Vân Mộng Cốc");
			me->set_fam_master("Tô Tần");
			me->set_fam_order(4);
			me->set_save("famrec", 1);
			"/sys/sys/count"->add_family("Vân Mộng Cốc", 1);
			me->set_fam_time(time());
			//me->set_level(20);
			me->add_exp(55211);
			me->count_gift();
			me->add_cash(10000);
			me->add_save("tuiquatanthu", 1);
			me->set_skill(0281, 30);
			me->set_skill(0501, 30);
			me->set_skill(0511, 30);
			me->set_skill(0531, 30);
			me->set_skill(0591, 30);
			item = new ("item/61/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/66/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/86/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/87/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/88/7020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/79/1020");
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new ("item/ngoai_trang/ngoaitrang2");
			p = item->move2(me, -1);
			item->add_to_user(p);
			me->use_equip(item);
			//	item = new("item/tuiquatanthuhieu/6002");
			//	p = item->move2(me,-1);
			//	item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0008");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/tuiquatanthuhieu/0010");
			item->set_amount(60);
			p = item->move2(me, -1);
			item->add_to_user(p);
			item = new ("item/09/0907");
			item->set_item_level(1);
			me->restore_equip(item);
			"/sys/user/energy"->count_all_prop(me);
			//	USER_ENERGY_D->count_max_yuan(me);
			send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
					  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->remove_from_user();
			destruct(item1);
			send_user(me, "%c%s", ';', "Bạn đã sử dụng \"Túi Quà Tân Thủ\"");
		}
		return 1;
	}

	return 1;
}
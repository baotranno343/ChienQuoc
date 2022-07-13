#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{
	mapping skls;
	int skill = to_int(arg), p, check_give, q, size, i, level;
	string result, *name;
	object *inv, item, item1;

	if (!objectp(item1 = present("Túi Quà Tân Thủ CQ3", me, 1, MAX_CARRY * 4)))
	{
		write_user(me, ECHO "Bạn không có Túi Quà Tân Thủ Chiến Quốc!");
		return 1;
	}
	if (me->get_level() >= 120)
	{
		write_user(me, ECHO "Đẳng Cấp Của Bạn Quá Cao Để Nhận Quà!");
		return 1;
	}
	if (me->get_fam_type() == 0)
	{
		write_user(me, ECHO "Vui Lòng Gia Nhập Môn Phái!");
		return 1;
	}
	if (USER_INVENTORY_D->get_free_count(me) < 10)
	{
		write_user(me, ECHO "Hành trang của bạn không đủ 10 chỗ trống!");
		return 1;
	}

	check_give = item1->get_no_give();
	if (arg == 0)
	{
		result = sprintf("Bạn Muốn Chơi Từ Level Nào :\n");
		result += ESC "Level 60\ntuiquatanthu 60\n";
		result += ESC "Level 120\ntuiquatanthu 115\n";
		result += ESC "Hủy bỏ\n";
		send_user(me, "%c%s", ':', result);
		return 1;
	}
	if (arg == "60")
	{
		level = 60;
		if (me->get_level() > 60)
		{
			write_user(me, ECHO "Đẳng cấp của bạn đã vượt quá mốc hỗ trợ vui lòng chọn mốc cao hơn");
			return 1;
		}
	}
	if (arg == "115")
	{
		level = 115;
		if (me->get_level() > 115)
		{
			write_user(me, ECHO "Đẳng cấp của bạn đã vượt quá mốc hỗ trợ vui lòng chọn mốc cao hơn");
			return 1;
		}
	}
	if (arg != "60" && arg != "115")
	{
		return 1;
	}
	if (mapp(skls = me->get_skill_dbase()) && sizeof(skls))
	{
		name = keys(skls);
		for (i = 0, size = sizeof(name); i < size; i++)
		{
			skill = to_int(name[i]);
			if (skill < 610)
				me->delete_skill(skill);
		}
	}
	// inv = me->get_all_equip();
	// for (i = 0, size = sizeof(inv); i < size; i++)
	// 	if (inv[i])
	// 	{
	// 		inv[i]->remove_from_user(); // 删除所有装备
	// 		destruct(inv[i]);
	// 	}
	me->set_upgrade_exp(0);
	me->set_exp(USER_EXP_D->get_level_exp_low(me->get_reincarnation(), level - 1),
				USER_EXP_D->get_level_exp_high(me->get_reincarnation(), level - 1));
	NPC_ENERGY_2_D->init_family2(me, me->get_fam_type(), level, -1);
	USER_ENERGY_D->count_all_prop(me);
	USER_ENERGY_D->count_max_yuan(me);
	me->set_max_level(me->get_level());
	me->set_hp(me->get_max_hp());
	me->set_mp(me->get_max_mp());

	// if (me->get_fam_name() == "")
	// {
	// 	item = new ("item/09/0908");
	// 	me->restore_equip(item);
	// }
	// else if (me->get_fam_name() == "Đào Hoa Nguyên")
	// {
	// 	item = new ("item/09/0901");
	// 	item->set_item_level(1);
	// 	me->restore_equip(item);
	// 	"/sys/user/energy"->count_all_prop(me);
	// 	//

	// 	q = item->move2(me, -1);
	// 	item->add_to_user(q);
	// }
	// else if (me->get_fam_name() == "Thục Sơn")
	// {
	// 	item = new ("item/09/0902");
	// 	item->set_item_level(1);
	// 	me->restore_equip(item);
	// 	"/sys/user/energy"->count_all_prop(me);

	// 	q = item->move2(me, -1);
	// 	item->add_to_user(q);
	// }
	// else if (me->get_fam_name() == "Cấm Vệ Quân")
	// {
	// 	item = new ("item/09/0903");
	// 	item->set_item_level(1);
	// 	me->restore_equip(item);
	// 	"/sys/user/energy"->count_all_prop(me);

	// 	q = item->move2(me, -1);
	// 	item->add_to_user(q);
	// }
	// else if (me->get_fam_name() == "Đường Môn")
	// {
	// 	item = new ("item/09/0904");
	// 	item->set_item_level(1);
	// 	me->restore_equip(item);
	// 	"/sys/user/energy"->count_all_prop(me);
	// 	//

	// 	q = item->move2(me, -1);
	// 	item->add_to_user(q);
	// }
	// else if (me->get_fam_name() == "Mao Sơn")
	// {
	// 	item = new ("item/09/0905");
	// 	item->set_item_level(1);
	// 	me->restore_equip(item);
	// 	"/sys/user/energy"->count_all_prop(me);
	// 	//

	// 	q = item->move2(me, -1);
	// 	item->add_to_user(q);
	// }
	// else if (me->get_fam_name() == "Côn Luân")
	// {
	// 	item = new ("item/09/0906");
	// 	item->set_item_level(1);
	// 	me->restore_equip(item);
	// 	"/sys/user/energy"->count_all_prop(me);
	// 	//

	// 	q = item->move2(me, -1);
	// 	item->add_to_user(q);
	// }
	// else if (me->get_fam_name() == "Vân Mộng Cốc")
	// {
	// 	item = new ("item/09/0907");
	// 	item->set_item_level(1);
	// 	me->restore_equip(item);
	// 	"/sys/user/energy"->count_all_prop(me);
	// 	//

	// 	q = item->move2(me, -1);
	// 	item->add_to_user(q);
	// }
	// else
	// {
	// 	return 1;
	// }
	//me->add_knbkhoa(10000);
	item = new ("item/ride/042");
	q = item->move2(me, -1);
	item->set_no_give(1);
	item->add_to_user(q);
	//send_user(who, "%c%s", ';', "Bạn nhận được " HIR "Kiến Chiến Binh.");

	//send_user(who, "%c%s", ';', "Bạn nhận được " HIR "3 Chén Bạc Vip.");
	if (level == 60)
	{
		item = new ("ken/hotrotanthu/tuihoangkimtanthucap60");
		q = item->move2(me, -1);
		item->add_to_user(q);
	}
	if (level == 115)
	{
		item = new ("ken/hotrotanthu/tuihoangkimtanthucap100");
		q = item->move2(me, -1);
		item->add_to_user(q);
	}

	item1->remove_from_user();
	destruct(item1);
	send_user(me, "%c%s", ';', "Bạn nhận quà thành công từ " HIY "Chiến Quốc");

	return 1;
}
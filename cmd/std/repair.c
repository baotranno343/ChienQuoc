
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>
#include <item.h>

// 函数：命令处理
int main(object me, string arg)
{
	object city, who, item, *inv;
	string id, legend;
	int level, tax, value, size, flag, i, allvalue, last, itemid;
	string result;

	if (gone_time(me->get_time("repair")) < 1) // 时间限制
	{
		me->set_time("repair", time());
		return 1;
	}
	me->set_time("repair", time());

	if (!arg)
		return 1;
	else if (sscanf(arg, "<< %s %s", id, arg) == 2)
		flag = 8;
	else if (sscanf(arg, "< %s %s", id, arg) == 2)
		flag = 7;
	else if (sscanf(arg, "!! %s %s", id, arg) == 2)
		flag = 5;
	else if (sscanf(arg, "! %s %s", id, arg) == 2)
		flag = 4;
	else if (sscanf(arg, ">> %s %s", id, arg) == 2)
		flag = 3;
	else if (sscanf(arg, "> %s %s", id, arg) == 2)
		flag = 2;
	else if (sscanf(arg, "* %s", id) == 1)
		flag = 6;
	else if (sscanf(arg, "%s %s", id, arg) == 2)
		flag = 1;
	else
		id = arg;

	if (!objectp(who = find_char(id)))
		return 1;

	if (!who->is_repairer())
		return 1;
	if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
	{
		send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
		return 1;
	}
	if (!inside_screen_2(me, who))
	{
		notify("Bạn cách %s quá xa rồi.", who->get_name());
		return 1;
	}

	if (flag == 0)
	{
		if (me->get_skill(650))
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf(" %s :\n %s \n Xin hỏi bạn cần phục vụ gì?\n" ESC "Tôi cần đánh giá trang bị\nrepair %x# identify\n" ESC "Ta cần phân giải trang bị\nrepair * %x#\n" ESC "Tôi cần sửa chữa thông thường\nrepair %x# 2\n" ESC "Tôi chỉ tham quan, dạo qua mà thôi\nCLOSE\n", who->get_name(), "/quest/word"->get_normal_word(who), getoid(who), getoid(who), getoid(who)));
		else
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf(" %s :\n %s \n Xin hỏi bạn cần phục vụ gì?\n"
							  //                                ESC "我需要完美的特殊修理\nrepair %x# 1\n"
							  ESC "Tôi cần đánh giá trang bị\nrepair %x# identify\n" ESC "Tôi cần sửa chữa thông thường\nrepair %x# 2\n" ESC "Tôi chỉ tham quan, dạo qua mà thôi\nCLOSE\n",
							  who->get_name(), "/quest/word"->get_normal_word(who), getoid(who), getoid(who)));
		return 1;
	}
	if (flag == 1)
	{
		if (arg == "identify")
		{
			send_user(me, "%c%c%d", 0x61, 1, getoid(who));
			return 1;
		}
		if (arg == "1")
			send_user(me, "%c%c%d", 0x52, 2, getoid(who));
		else
			send_user(me, "%c%c%d", 0x52, 1, getoid(who));
		return 1;
	}
	if (flag == 6)
	{
		send_user(me, "%c%c%d", 0x60, 10, getoid(who));
		return 1;
	}
	if (flag == 7 || flag == 8)
	{
		item = present(arg, me, 0, 0);
		if (!item)
			return 1;
		if (!item->is_equip())
		{
			return 1;
		}
		if (item->get_equip_type() == HAND_TYPE)
		{
			return 1;
		}
		if (item->get_equip_type() == 0)
		{
			return 1;
		}
		if (!item->get_hide() || item->get_level() < 30)
		{
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf("%s：\n    %s đã giám định rồi", who->get_name(), item->get_name()));
			return 1;
		}
		level = item->get_level();
		level *= 30;
		if (level == 0)
			level = 30;
		if (flag == 7)
		{
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf(" %s :\n Giám định trang bị này cần tốn Số Ngân lượng %d , có thực là muốn giám định không?\n" ESC "Vâng, tôi cần giám định\nrepair << %x# %x#\n" ESC "Đắt quá, tôi không giám định\nCLOSE\n", who->get_name(), level, getoid(who), getoid(item)));
			return 1;
		}
		if (me->get_cash() < level)
		{
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf("%s：\n    Ngân lượng của bạn không đủ %d, không thể giám định %s。", who->get_name(), level, item->get_name()));
			return;
		}
		me->add_cash2(-level);
		legend = sprintf("Giám định %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), level, get_z(me), get_x(me), get_y(me));
		//"/sys/user/cmd"->log_item(legend);
		"/sys/sys/count"->add_use("Giám định", level);
		if (item->get_item_color() == 0 || item->get_item_color() == 4)
		{
			i = random(10000);
			if (i == 0)
				"/sys/item/equip"->init_equip_prop_3(item);
			else if (i < 301)
				"/sys/item/equip"->init_equip_prop_1(item);
			if (item->get_item_color() != 0 && item->get_item_color() != 4)
			{
				itemid = "/sys/sys/id"->add_max_itemid(1);
				item->set_user_id(sprintf("#%d#", itemid));
				//log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item) ));
				legend = sprintf("鉴定升级 @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", who->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
				//"/sys/user/cmd"->log_item(legend);
			}
		}
		item->set_hide(0);
		level = get_d(item);
		item->add_to_user(level);
		level = item->get_item_color();
		switch (level)
		{
		case 0:
		case 4:
			result = "Trang bị của ngươi bình thường ! không có gì đặc biệt !";
			break;
		case 1:
			result = "Sự chuẩn bị của bạn thật tốt! Trang bị xuất sắc.";
			break;
		case 2:
			result = "Đây là trang bị quý hiếm, chúc mừng ngươi !";
			break;
		default:
			result = "Thật vinh hạnh cho ta có thể nhìn thấy được trang bị này !";
			break;
		}
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
				  sprintf(" %s :\n %s \n" ESC "Tiếp tục kiểm định\nrepair %x# identify\n" ESC "Rời khỏi\nCLOSE\n", who->get_name(), result, getoid(who)));
		return 1;
	}
	me->to_front_eachother(who);
	if (city = CITY_D->get_city_object(who))
	{
		if (me->get_city_name() == who->get_city_name())
			tax = city->get_buy_tax();
		else
			tax = city->get_buy_tax_2();
	}
	else
		tax = 0;
	if (arg == "all")
	{
		allvalue = 0;
		inv = me->get_all_equip();
		for (i = 0, size = sizeof(inv); i < size; i++)
		{
			if (objectp(inv[i]))
			{
				item = inv[i];
				if (!item->is_equip())
					continue;
				//        			if( item->get_equip_type() == HAND_TYPE ) continue;
				if (item->get_weapon_code() == THROWING)
					continue;
				if (item->get_equip_type() == HAND_TYPE)
					continue;
				if (item->get_equip_type() == FAMILY_TYPE)
					continue;
				if (item->get_max_lasting() < 10)
					continue;
				if (item->get_lasting() >= item->get_max_lasting())
					continue;
				if ((value = item->get_value()) <= 0)
					continue;
				if (item->is_combined())
					value *= item->get_amount();
				value = value - value * item->get_lasting() / item->get_max_lasting();
				if (item->get_equip_type() == HAND_TYPE && item->get_lasting() != item->get_max_lasting())
					value = 100000;
				if (flag == 3 || flag == 5)
					value *= 8; // 特殊修理
				value += value * tax / 100;
				if (value < 10)
					value = 10;
				allvalue += value;
			}
		}
		if (me->get_cash() < allvalue)
		{
			notify("Sửa chữa tất cả trang bị tốn Số Ngân lượng %d , Ngân lượng của bạn hiện không đủ.", allvalue);
			return 1;
		}
		if (allvalue <= 0)
		{
			notify("Tất cả những trang bị của bạn trước mắt rất tốt, chưa cần sửa chữa");
			return 1;
		}
		if (flag == 2)
		{
			send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					  sprintf("%s：\n    Sửa chửa tất cả trang bị tiêu hao %d lượng, ngươi xác nhận không ?\n" ESC "Đồng ý\nrepair ! %x# all\n" ESC "Ta không sửa chửa\nCLOSE\n", who->get_name(), allvalue, getoid(who)));
			return 1;
		}
		if (flag == 3)
		{
			//		        send_user( me, "%c%c%w%s", ':', 1, who->get_char_picid(),
			//		                sprintf("%s：\n    特殊修理所有装备需要花费%d金,你是否同意？\n"
			//		                        ESC "我同意\nrepair !! %x# all\n"
			//		                        ESC "太贵了,我不修理了\nCLOSE\n", who->get_name(), allvalue, getoid(who) ) );
			return 1;
		}

		me->add_cash2(-allvalue);
		me->add_gold_log("repair", allvalue);
		legend = sprintf("Sửa chữa %s,%d,%s,%s @%s lượng 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), allvalue, get_z(me), get_x(me), get_y(me));
		//"/sys/user/cmd"->log_item(legend);
		"/sys/sys/count"->add_use("repair", allvalue);
		for (i = 0, size = sizeof(inv); i < size; i++)
		{
			if (objectp(inv[i]))
			{
				item = inv[i];
				if (!item->is_equip())
					continue;
				//        			if( item->get_equip_type() == HAND_TYPE ) continue;
				if (item->get_weapon_code() == THROWING)
					continue;
				if (item->get_equip_type() == HAND_TYPE)
					continue;
				if (item->get_equip_type() == FAMILY_TYPE)
					continue;
				if (item->get_max_lasting() < 10)
					continue;
				if (item->get_lasting() >= item->get_max_lasting())
					continue;
				if ((value = item->get_value()) <= 0)
					continue;
				last = item->get_max_lasting();
				if (flag == 4)
				{
					last = last - (last - item->get_lasting()) / 20;
					if (item->get_max_lasting() - last < 10)
						last = item->get_max_lasting() - 10;
				}
				item->set_max_lasting(last);
				item->set_lasting(last);
			}
		}
		"/sys/user/energy"->count_all_prop(me);
		if (city = CITY_D->get_city_object(who))
		{
			city->add_tax(value * tax / (100 + tax));
			city->add_cash(value * (100 - tax) / (100 + tax));
		}

		write_user(me, ECHO "Bạn xuất ra tất cả trang bị cấp %s sửa chửa ,tiêu hao %d lượng",
				   who->get_name(), allvalue);

		return 1;
	}

	if (!(item = present(arg, me, 1, FAMILY_TYPE)))
	{
		inv = me->get_all_equip();
		for (i = 0, size = sizeof(inv); i < size; i++)
		{
			if (objectp(inv[i]) && arg == sprintf("%x#", getoid(inv[i])))
			{
				item = inv[i];
				break;
			}
		}
		if (!objectp(item))
			return 1; // 您找不到这样东西。
	}

	if (!item->is_equip())
	{
		notify(item->get_name() + "Không phải trang bị, không thể sửa chửa");
		return 1;
	}

	if (item->get_equip_type() == HAND_TYPE)
	{
		notify("Không thể sửa %s !", item->get_name());
		return 1;
	}

	if (item->get_weapon_code() == THROWING)
	{
		notify(item->get_name() + "Là ám khí, không có biện pháp sửa chửa");
		return 1;
	}
	if (item->get_equip_type() == FAMILY_TYPE)
	{
		notify("Không thể sửa %s !", item->get_name());
		return 1;
	}
	if (item->get_equip_type() == HAND_TYPE)
	{
		notify("Không thể sửa %s !", item->get_name());
		return 1;
	}
	if (item->get_max_lasting() < 10)
	{
		notify(" %s đã hư cũ, không thể sửa lại được.", item->get_name());
		return 1;
	}
	if (item->get_lasting() >= item->get_max_lasting())
	{
		notify(" %s hiện nay rất tốt, không có gì cần phải sửa lại.", item->get_name());
		return 1;
	}

	if ((value = item->get_value()) < 0)
	{
		notify(item->get_name() + "Là vật bấu vô giá, không có biện pháp sửa chửa");
		return 1;
	}
	else if (value == 0)
	{
		notify(item->get_name() + "Là không đáng 1 xu, không tất yếu sửa chửa");
		return 1;
	}

	if (item->is_combined())
		value *= item->get_amount();
	value = value - value * item->get_lasting() / item->get_max_lasting();
	//	if( item->get_equip_type() == HAND_TYPE ) value = 100000;
	//        if( flag == 3 || flag== 5 ) value *= 8;    // 特殊修理
	if (flag == 3 || flag == 5)
		return 1;

	value += value * tax / 100;
	if (value < 10)
		value = 10;

	if (me->get_cash() < value)
	{
		notify("Sửa %s cần phải tốn %d lượng, Ngân lượng bạn đem theo không đủ.", item->get_name(), value);
		return 1;
	}
	if (flag == 2)
	{
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(),
				  sprintf("%s：\n    Bình thường sửa chửa %s cần tiêu hao %d lượng, ngươi đồng ý không ?\n" ESC "Đồng Ý\nrepair ! %x# %x#\n" ESC "Tta không sửa chửa\nCLOSE\n", who->get_name(), item->get_name(), value, getoid(who), getoid(item)));
		return 1;
	}
	if (flag == 3)
	{
		//                send_user( me, "%c%c%w%s", ':', 1, who->get_char_picid(),
		//                        sprintf("%s：\n    特殊修理%s需要花费%d金,你是否同意？\n"
		//                                ESC "我同意\nrepair !! %x# %x#\n"
		//                                ESC "太贵了,我不修理了\nCLOSE\n", who->get_name(), item->get_name(), value, getoid(who), getoid(item) ) );
		return 1;
	}

	me->add_cash2(-value);
	me->add_gold_log("repair", value);
	legend = sprintf("修理 %s,%d,%s,%s @%s 金 0 %d 0 %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), who->get_name(), value, get_z(me), get_x(me), get_y(me));
	//"/sys/user/cmd"->log_item(legend);
	"/sys/sys/count"->add_use("repair", value);
	size = item->get_max_lasting();
	if (flag == 4)
	{
		size = size - (size - item->get_lasting()) / 20;
		if (item->get_max_lasting() - size < 10)
			size = item->get_max_lasting() - 10;
	}
	item->set_max_lasting(size);
	item->set_lasting(size);

	if (city = CITY_D->get_city_object(who))
	{
		city->add_tax(value * tax / (100 + tax));
		city->add_cash(value * (100 - tax) / (100 + tax));
	}

	write_user(me, ECHO "Bạn xuất ra %s cấp %s sửa chửa ,tieu hao %d lượng",
			   item->get_name(), who->get_name(), value);

	return 1;
}

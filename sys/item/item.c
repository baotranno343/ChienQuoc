
#include <ansi.h>
#include <item.h>
#include <equip.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：获取道具描述(基本)
string get_desc_string(object who, object item)
{
	switch (item->get_equip_type())
	{
	case HEAD_TYPE:
		return sprintf("[Nón] %s \n", item->get_desc());
	case NECK_TYPE:
		return sprintf("[Trang Sức] %s \n", item->get_desc());
	case WEAPON_TYPE:
		if (item->get_desc() == "Trang bị “Quyền Pháp”" && file_exist(UNARMED_TYPE))
			return sprintf("[Vũ Khí] %s \n", read_file("/" UNARMED_TYPE));
		if (item->get_desc() == "Trang bị “Ám Khí”" && file_exist(THROWING_TYPE))
			return sprintf("[Vũ Khí] %s \n", read_file("/" THROWING_TYPE));
		if (item->get_desc() == "Trang bị “Đao Pháp”" && file_exist(BLADE_TYPE))
			return sprintf("[Vũ Khí] %s \n", read_file("/" BLADE_TYPE));
		if (item->get_desc() == "Trang bị “Kiếm Pháp”" && file_exist(SWORD_TYPE))
			return sprintf("[Vũ Khí] %s \n", read_file("/" SWORD_TYPE));
		if (item->get_desc() == "Trang bị “Thương Pháp”" && file_exist(SPEAR_TYPE))
			return sprintf("[Vũ Khí] %s \n", read_file("/" SPEAR_TYPE));
		if (item->get_desc() == "Trang bị “Côn Pháp”" && file_exist(STICK_TYPE))
			return sprintf("[Vũ Khí] %s \n", read_file("/" STICK_TYPE));
		else
			return sprintf("[Vũ Khí] %s \n", item->get_desc());
	case ARMOR_TYPE:
		if (item->get_gender() == 1)
			return sprintf("[Y Phục] %s \n", item->get_desc()); // "[Phòng Cụ]"
		else
			return sprintf("[Y Phục] %s \n", item->get_desc()); // "[Phòng Cụ]"
	case WAIST_TYPE:
		return sprintf("[Yêu Đới] %s \n", item->get_desc());
	case BOOTS_TYPE:
		return sprintf("[Giày] %s \n", item->get_desc());
	case HAND_TYPE:
		return sprintf("[Pháp Bảo] %s \n", item->get_desc()); // "[Pháp Bảo]"
	default:
		if (item->is_usable())
			return sprintf("[Có thể sử dụng] %s \n", item->get_desc());
		else
			return sprintf(" %s \n", item->get_desc());
	}
}

string get_pawn_string(object me, string prop)
{
	string name, result = "", name2, *key, id, color, special;
	int level, point, i, size, use, maxuse, locktime, lockutil, z, x, y, no_give;
	object map;
	if (!sscanf(prop, "%s;%*s", name) || !load_object(name))
		return "";

	result = "";
	switch (name->get_item_type())
	{
	case ITEM_TYPE_EQUIP:

		if (sscanf(prop, "%s;%d;%d;%d;%d;%s;[%s]%d,%d", name, size, no_give, use, maxuse, prop, id, locktime, lockutil) != 9)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		if (!sscanf(prop, "%s-1-:%d,%*s", name2, point))
			point = 0; // 免装备等cấp
		level = name->get_level() - me->get_equip_less_level() - point;
		if (level < 0)
			level = 0;

		switch (name->get_item_color())
		{
		default:
			color = "";
			break;
		case 1:
			color = HIC;
			break;
		case 2:
			color = HIY;
			break;
		case 3:
			color = HIG;
			break;
		case 4:
			color = HIC;
			break;
		case 5:
			color = HIR;
			break;
		}

		if (prop != "")
		{
			key = explode(prop, ",");
			size = sizeof(key);
			for (i = 0; i < size; i++)
			{
				if (!sscanf(key[i], "%s:%s", name2, special))
					continue;
				if (name2 == "forge" && (z = strlen(special)))
				{
					result += color;
					for (x = 0; x < z; x++)
						result += "★";
					result += "\n";
					break;
				}
			}
		}

		if (name->get_stuff_type() == 0 && name->get_max_lasting() > 0)
			result += sprintf("Độ bền: %d / %d \n", use / 100, maxuse / 100);
		else if (name->get_max_lasting() > 0)
			result += sprintf("Số lần sử dụng: %d / %d\n", use / 100, maxuse / 100);
		if (name->is_thanbinh())
		{
			if (name->is_thanbinh1())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Ngọc La Quyền Thủ\n");
			else if (name->is_thanbinh2())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Thần Tiên Hạc Kim\n");
			else if (name->is_thanbinh3())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Đao Tử Vân\n");
			else if (name->is_thanbinh4())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Lục Thần Thương\n");
			else if (name->is_thanbinh5())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Phàn Thiên Côn\n");
			else if (name->is_thanbinh6())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Lục Tiên Kiếm\n");
		}
		if (name->is_nangcap() && name->get("aohoa") && name->get_lock_time() > time())
		{
			switch (name->get("aohoa"))
			{
			case 1:
				result += sprintf(HIG "Ảo hóa: Thánh Linh Chi Dực - Đơn Sắc\n");
			case 2:
				result += sprintf(HIG "Ảo hóa: Thánh Linh Chi Dực - Vạn Sắc\n");
			case 3:
				result += sprintf(HIG "Ảo hóa: Vạn Ác Chi Dực - Đơn Sắc\n");
			case 4:
				result += sprintf(HIG "Ảo hóa: Vạn Ác Chi Dực - Vạn Sắc\n");
			default:
				break;
			}
		}
		if (name->get_stuff_type() == 0)
		{
			if (level > 0)
				result += sprintf("Trang bị yêu cầu: %s %d cấp\n", level > me->get_level() ? HIR : NOR, name->get_level());
		}
		else
		{
			if (level > 0)
				result += sprintf("Kĩ năng yêu cầu: %s%d	cấp\n", NOR, name->get_level());
		}

		name2 = me->get_fam_name();

		switch (name->get_equip_type())
		{
		case HEAD_TYPE:
		case ARMOR_TYPE:
		case BACK_TYPE:
			if (name->get_gender() == 1)
				result += sprintf("Thích hợp dùng cho: %s nam\n", me->get_gender() == 1 ? NOR : HIR);
			else if (name->get_gender() == 2)
				result += sprintf("Thích hợp dùng cho: %s nữ\n", me->get_gender() == 2 ? NOR : HIR);
			// break;    //	同下面共用，不能有 break;

		default:
			switch (name->get_family())
			{
				//						default	: result += "Môn phái thích hợp dùng: －－\n";	 break;
			case 1:
				result += sprintf("Môn phái thích hợp dùng: %s Đào Hoa Nguyên\n",
								  name2 != "Đào Hoa Nguyên" ? HIR : NOR);
				break;
			case 2:
				result += sprintf("Môn phái thích hợp dùng: %s Thục Sơn\n",
								  name2 != "Thục Sơn" ? HIR : NOR);
				break;
			case 3:
				result += sprintf("Môn phái thích hợp dùng: %s Cấm Vệ Quân\n",
								  name2 != "Cấm Vệ Quân" ? HIR : NOR);
				break;
			case 4:
				result += sprintf("Môn phái thích hợp dùng: %s Đường Môn\n",
								  name2 != "Đường Môn" ? HIR : NOR);
				break;
			case 5:
				result += sprintf("Môn phái thích hợp dùng: %s Mao Sơn\n",
								  name2 != "Mao Sơn" ? HIR : NOR);
				break;
			case 6:
				result += sprintf("Môn phái thích hợp dùng: %s Côn Luân\n",
								  name2 != "Côn Luân" ? HIR : NOR);
				break;
			case 7:
				result += sprintf("Môn phái thích hợp dùng: %s Vân Mộng Cốc\n",
								  name2 != "Vân Mộng Cốc" ? HIR : NOR);
				break;
			}
			break;
		case WEAPON_TYPE:
			switch (name->get_family())
			{
				//						default	: result += "Môn phái thích hợp dùng: －－\n";	 break;
			case 1:
				result += sprintf("Môn phái thích hợp dùng: %s Đào Hoa Nguyên\n",
								  name2 != "Đào Hoa Nguyên" ? HIR : NOR);
				break;
			case 2:
				result += sprintf("Môn phái thích hợp dùng: %s Thục Sơn\n",
								  name2 != "Thục Sơn" ? HIR : NOR);
				break;
			case 3:
				result += sprintf("Môn phái thích hợp dùng: %s Cấm Vệ Quân\n",
								  name2 != "Cấm Vệ Quân" ? HIR : NOR);
				break;
			case 4:
				result += sprintf("Môn phái thích hợp dùng: %s Đường Môn\n",
								  name2 != "Đường Môn" ? HIR : NOR);
				break;
			case 5:
				result += sprintf("Môn phái thích hợp dùng: %s Mao Sơn\n",
								  name2 != "Mao Sơn" ? HIR : NOR);
				break;
			case 6:
				result += sprintf("Môn phái thích hợp dùng: %s Côn Luân\n",
								  name2 != "Côn Luân" ? HIR : NOR);
				break;
			case 7:
				result += sprintf("Môn phái thích hợp dùng: %s Vân Mộng Cốc\n",
								  name2 != "Vân Mộng Cốc" ? HIR : NOR);
				break;
			case 9:
				result += sprintf("Môn phái thích hợp dùng: %s Vân Mộng Cốc, Thục Sơn, Mao Sơn, Côn Luân\n",
								  (name2 != "Vân Mộng Cốc" && name2 != "Mao Sơn" && name2 != "Thục Sơn" && name2 != "Côn Luân") ? HIR : NOR);
				break;
			}
			break;
		}

		if (prop != "")
		{
			key = explode(prop, ",");
			size = sizeof(key);
			for (i = 0; i < size; i++)
			{
				if (!sscanf(key[i], "%s:%d", name2, point))
					continue;
				if (name2 == "hide" && point > 0)
				{
					size = -1;
					id = "";
					result += HIR "Chưa giám định";
					break;
				}
			}
			if (size == -1)
				break;
			for (i = 0; i < size; i++)
			{
				if (!sscanf(key[i], "|%s:%d", name2, point))
					continue;
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(name, name2, point, color);
			}
			if (!sscanf(prop, "%s+:%d,%*s", name2, point))
				point = 0;
		}

		id = "";
		if (point)
			id = sprintf("%+d", point);

		break;

	case ITEM_TYPE_TALISMAN:

		if (sscanf(prop, "%s;%d;%d;%d;%d;%d;[%s]%d,%d", name, size, no_give, use, maxuse, point, id, locktime, lockutil) != 9)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}

		result += sprintf("Độ bền: %d / %d \n", use / 100, maxuse / 100);
		if (name->get_stuff_type() == 0)
			result += sprintf(" %d cấp Pháp Bảo\n", name->get_level());
		else
			result += sprintf("Trang bị yêu cầu %d cấp\n", name->get_level());

		switch (name->get_talisman_type())
		{
		default:
			break;

		case 2: // Cửu Long Thần Hỏa Trảo
			result += sprintf("Khí huyết: %d / %d \n", point, name->get_max_hp());
			break;
		case 9: // 招魂幡
			if (point < name->get_time_interval())
				result += sprintf(HIR "%d％ 准备中\n", point * 100 / name->get_time_interval());
			else
				result += HIG "100％ 准备好\n";
			break;
		}

		switch (name->get_level())
		{
		default:
			color = "";
			break;
		case 2:
			color = HIC;
			break;
		case 3:
			color = HIY;
			break;
		case 4:
			color = HIG;
			break;
		case 5:
			color = HIR;
			break;
		}
		id = "";

		break;

	case ITEM_TYPE_FLAG:
		if (sscanf(prop, "%s;%d;[%s]%d,%d", name, size, id, locktime, lockutil) != 5)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}

		name2 = me->get_fam_name();
		result += sprintf("Môn phái thích hợp dùng: %s Vân Mộng Cốc\n", name2 != "Vân Mộng Cốc" ? HIR : NOR);

		color = "";
		id = "";

		break;

	case ITEM_TYPE_POISON:
		if (sscanf(prop, "%s;%d;[%s]%d,%d", name, size, id, locktime, lockutil) != 5)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}

		name2 = me->get_fam_name();
		//				result += sprintf( "Môn phái thích hợp dùng: %s Đường Môn\n", name2 != "Đường Môn" ? HIR : NOR );

		if (point = name->get_poison())
			result += ITEM_EQUIP_D->get_chinese_prop_string(name, "@", point);

		color = "";
		id = "";

		break;

	case ITEM_TYPE_POISON_2:
		if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", name, size, point, id, locktime, lockutil) != 6)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		result += sprintf("Độc tính: %d\n", point);

		color = "";
		id = "";

		break;

	case ITEM_TYPE_BOOK:
	case ITEM_TYPE_BOOK_2:
		if (sscanf(prop, "%s;%d;[%s]%d,%d", name, size, id, locktime, lockutil) != 5)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		name2 = name->get_family_name();
		if (name2 != " －" && name2 != "" && name2 != 0)
			result += sprintf("Môn phái thích hợp dùng: %s %s \n", name2[1.. < 1] != me->get_fam_name() ? HIR : NOR, name2[1.. < 1]);

		color = "";
		id = "";

		break;

	case ITEM_TYPE_TREASURE:
		if (sscanf(prop, "%s;%d;%d;%d;%d;[%s]%d,%d", name, size, z, x, y, id, locktime, lockutil) != 8)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		if (map = get_map_object(z))
			result += sprintf("Vị trí: %s ( %d , %d )\n", map->get_name(), x, y);

		color = "";
		id = "";

		break;

	case ITEM_TYPE_DIAMOND_2:
		if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", name, size, point, id, locktime, lockutil) != 6)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		color = "";
		id = "";
		if (point)
			id = sprintf("%+d", point);

		break;

	case ITEM_TYPE_POTENTIAL:
		if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", name, size, point, id, locktime, lockutil) != 6)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		if (point)
			result += sprintf("Tiềm năng: %+d\n", point);

		color = "";
		id = "";

		break;
	case ITEM_TYPE_SPECIAL:
		if (sscanf(prop, "%s;%d;%s;[%s]%d,%d", name, size, special, id, locktime, lockutil) != 6)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		color = "";
		id = "";
		//				result = name->get_special_desc(special);
		return sprintf("%s%s%s\n%s%s", color, name->get_name(), id, name->get_special_desc(special), result);
	default:
		if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", name, size, no_give, id, locktime, lockutil) != 6)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		color = "";
		id = "";

		break;
	case ITEM_TYPE_KIMNGUYENBAO:
		if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", name, size, point, id, locktime, lockutil) != 6)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		if (point)
			result += sprintf(HIY "Kim Nguyên Bảo: %+d\n", point / 10);

		color = "";
		id = "";

		break;
	case ITEM_TYPE_CHIENTICH:
		if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", name, size, point, id, locktime, lockutil) != 6)
		{
			return "数据出了问题的物品，赎回会导致物品消失。有问题请通知ＧＭ。";
		}
		if (point)
			result += sprintf(HIY "Điểm Chiến Tích: %+d\n", point);

		color = "";
		id = "";

		break;
	}
	if (name->is_suit())
		result += name->get_suit_desc();
	result = sprintf("%s%s%s\n%s%s", color, name->get_name(), id, ITEM_ITEM_D->get_desc_string(me, name), result);
	return result;
}

// 函数：获取道具描述(所有)
// 说明：flag == 1 不显示卖出价
varargs string get_look_string(object who, object item, int flag)
{
	object map, fileobj, whosee;
	string name, file, color, result, product, bind, forge, hole, *tach_hole, check_duc_lo, fileobject;
	int level, point, lockutil;
	int i, j, size;
	string cHole, *nTmp, *nTmp1;
	bind = "";
	switch (item->get_bind())
	{
	case 1:
		if (item->get_equip_type())
			bind = HIC "(Sau khi trang bị sẽ bị Phong Ấn)" NOR;
		else
			bind = HIC "(Sau khi sử dụng sẽ bị Phong Ấn)" NOR;
		break;
	case 2:
		if (item->get_equip_type())
			bind = HIC "(Vật phẩm đã Phong Ấn)" NOR;
		else
			bind = HIC "(Vật phẩm đã Phong Ấn)" NOR;
		break;
	case 3:
		bind = HIC "(Nhặt vật phẩm sẽ Phong Ấn)" NOR;
		break;

	case 4:
		bind = HIC "(Nhặt vật phẩm đã Phong Ấn)" NOR;
		break;
	case 5:
		bind = HIC "(Khoá Sử Dụng)" NOR;
		break;
	}
	if (item->get("duc_lo.3"))
	{
		check_duc_lo = HIW "(3 Lỗ)" NOR;
	}
	else if (item->get("duc_lo.2"))
	{
		check_duc_lo = HIW "(2 Lỗ)" NOR;
	}
	else if (item->get("duc_lo.1"))
	{
		check_duc_lo = HIW "(1 Lỗ)" NOR;
	}
	else
	{
		check_duc_lo = "";
	}

	if (!is_player(who))
		result = sprintf("%s%s %s[%s]%s%x#%s%s\n%s", item->get_name(), item->get_item_make_desc(), check_duc_lo, item->get_user_id(), item->is_locked() > 0 ? "[Khóa]" : "", getoid(item), bind, item->get_no_give() == 1 ? "(Khóa)" : "", get_desc_string(who, item));
	else
		result = sprintf("%s%s %s%s%s\n%s", item->get_name(), item->get_item_make_desc(), check_duc_lo, bind, item->get_no_give() == 1 ? "(Khóa)" : "", get_desc_string(who, item));

	if (item->get("chietxuat"))
	{
		result += HIG "Đã Chiết Xuất" NOR;
	}
	if (item->get_product_id() != "" && item->get_product_id() != 0)
	{
		switch (item->get_item_color())
		{
		default:
			color = HIG;
			break;
		case 1:
			color = HIC;
			break;
		case 2:
			color = HIY;
			break;
		case 3:
			color = PPM;
			break;
		case 4:
			color = HIG;
			break;
		case 5:
			color = HIR;
			break;
		}
		result += sprintf(" %s Người chế tác: %s \n", color, item->get_product_id());
	}
	color = "";
	switch (item->get_item_color())
	{
	default:
		color = "";
		break;
	case 1:
		color = HIC;
		break;
	case 2:
		color = HIY;
		break;
	case 3:
		color = PPM;
		break;
	case 4:
		color = HIG;
		break;
	case 5:
		color = HIR;
		break;
	}
	forge = item->get("forge");
	if (size = strlen(forge))
	{
		result += color;
		for (i = 0; i < size; i++)
			result += "★";
		result += NOR "\n";
	}
	// hole = item->get("hole");
	// if (stringp(hole))
	// {
	// 	result += HIG "Pháp bảo đã được tạo ấn \n" NOR;
	// 	tach_hole = explode(hole, "|");
	// 	if ((sizeof(tach_hole)) < 2)
	// 	{
	// 		result += HIG;
	// 		for (i = 0; i < to_int(hole); i++)
	// 			result += "⚪";
	// 		result += NOR "\n";
	// 	}
	// 	else
	// 	{
	// 		result += HIG;
	// 		for (i = 0; i < to_int(tach_hole[0]); i++)
	// 		{
	// 			if (i < sizeof(explode(tach_hole[1], ":")))
	// 			{
	// 				result += "⚫";
	// 			}
	// 			else
	// 			{
	// 				result += "⚪";
	// 			}
	// 			// for (j = 0; j < sizeof(implode(tach_hole[1], ":")); i++)
	// 			// {
	// 			// 	if (i > j)
	// 			// 	{
	// 			// 		result += "⚪";
	// 			// 	}
	// 			// 	else
	// 			// 	{
	// 			// 		result += "⚫";
	// 			// 	}
	// 			// }
	// 		}
	// 		result += NOR "\n";
	// 	}
	// }
	switch (item->get_item_type())
	{
	default:
		break;

	case ITEM_TYPE_EQUIP:
		level = item->get_level() - who->get_equip_less_level() - item->get("-1-"); // 免装备等cấp
		if (level < 0)
			level = 0;
		if (item->is_thanbinh())
		{
			if (item->is_thanbinh1())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Ngọc La Quyền Thủ\n");
			else if (item->is_thanbinh2())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Thần Tiên Hạc Kim\n");
			else if (item->is_thanbinh3())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Đao Tử Vân\n");
			else if (item->is_thanbinh4())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Lục Thần Thương\n");
			else if (item->is_thanbinh5())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Phàn Thiên Côn\n");
			else if (item->is_thanbinh6())
				result += sprintf(HIG "Huyết binh được luyện thành từ: " PPM "Lục Tiên Kiếm\n");
		}
		if (item->is_nangcap() && item->get("aohoa") && item->get_lock_time() > time())
		{
			switch (item->get("aohoa"))
			{
			case 1:
				result += sprintf(HIG "Ảo hóa: Thánh Linh Chi Dực - Đơn Sắc\n");
				break;
			case 2:
				result += sprintf(HIG "Ảo hóa: Thánh Linh Chi Dực - Vạn Sắc\n");
				break;
			case 3:
				result += sprintf(HIG "Ảo hóa: Vạn Ác Chi Dực - Đơn Sắc\n");
				break;
			case 3:
				result += sprintf(HIG "Ảo hóa: Vạn Ác Chi Dực - Vạn Sắc\n");
				break;
			default:
				break;
			}
		}
		if (item->get_stuff_type() == 0)
		{
			if (level > 0)
				result += sprintf("Trang bị yêu cầu: %s %d cấp\n", level > who->get_level() ? HIR : NOR, item->get_level());
		}
		else
		{
			if (level > 0)
				result += sprintf("Kĩ năng yêu cầu: %s%d cấp\n", NOR, item->get_level());
		}

		name = who->get_fam_name();
		switch (item->get_equip_type())
		{
		case HEAD_TYPE:
		case ARMOR_TYPE:
		case BACK_TYPE:
			if (item->get_gender() == 1)
				result += sprintf("Thích hợp dùng cho: %s nam\n", who->get_gender() == 1 ? NOR : HIR);
			else if (item->get_gender() == 2)
				result += sprintf("Thích hợp dùng cho: %s nữ\n", who->get_gender() == 2 ? NOR : HIR);

			// break;    // 同下面共用，不能有 break;

		default:
			switch (item->get_family())
			{
				//                                              default : result += "Môn phái thích hợp dùng: －－\n";  break;
			case 1:
				result += sprintf("Môn phái thích hợp dùng: %s Đào Hoa Nguyên\n",
								  name != "Đào Hoa Nguyên" ? HIR : NOR);
				break;
			case 2:
				result += sprintf("Môn phái thích hợp dùng: %s Thục Sơn\n",
								  name != "Thục Sơn" ? HIR : NOR);
				break;
			case 3:
				result += sprintf("Môn phái thích hợp dùng: %s Cấm Vệ Quân\n",
								  name != "Cấm Vệ Quân" ? HIR : NOR);
				break;
			case 4:
				result += sprintf("Môn phái thích hợp dùng: %s Đường Môn\n",
								  name != "Đường Môn" ? HIR : NOR);
				break;
			case 5:
				result += sprintf("Môn phái thích hợp dùng: %s Mao Sơn\n",
								  name != "Mao Sơn" ? HIR : NOR);
				break;
			case 6:
				result += sprintf("Môn phái thích hợp dùng: %s Côn Luân\n",
								  name != "Côn Luân" ? HIR : NOR);
				break;
			case 7:
				result += sprintf("Môn phái thích hợp dùng: %s Vân Mộng Cốc\n",
								  name != "Vân Mộng Cốc" ? HIR : NOR);
				break;
			}
			break;

		case WEAPON_TYPE:
			switch (item->get_family())
			{
				//                                              default : result += "Môn phái thích hợp dùng: －－\n";  break;
			case 1:
				result += sprintf("Môn phái thích hợp dùng: %s Đào Hoa Nguyên\n",
								  name != "Đào Hoa Nguyên" ? HIR : NOR);
				break;
			case 2:
				result += sprintf("Môn phái thích hợp dùng: %s Thục Sơn\n",
								  name != "Thục Sơn" ? HIR : NOR);
				break;
			case 3:
				result += sprintf("Môn phái thích hợp dùng: %s Cấm Vệ Quân\n",
								  name != "Cấm Vệ Quân" ? HIR : NOR);
				break;
			case 4:
				result += sprintf("Môn phái thích hợp dùng: %s Đường Môn\n",
								  name != "Đường Môn" ? HIR : NOR);
				break;
			case 5:
				result += sprintf("Môn phái thích hợp dùng: %s Mao Sơn\n",
								  name != "Mao Sơn" ? HIR : NOR);
				break;
			case 6:
				result += sprintf("Môn phái thích hợp dùng: %s Côn Luân\n",
								  name != "Côn Luân" ? HIR : NOR);
				break;
			case 7:
				result += sprintf("Môn phái thích hợp dùng: %s Vân Mộng Cốc\n",
								  name != "Vân Mộng Cốc" ? HIR : NOR);
				break;
			case 9:
				result += sprintf("Môn phái thích hợp dùng: %s Vân Mộng Cốc, Thục Sơn, Mao Sơn, Côn Luân\n",
								  (name != "Vân Mộng Cốc" && name != "Mao Sơn" && name != "Thục Sơn" && name != "Côn Luân") ? HIR : NOR);
				break;
			}
			if (item->get_poison() && time() > item->get("poison_time"))
				result += sprintf("Độc tính：%d\n", item->get_poison());
			break;
		}
		if (item->get_level() >= 30 && item->get_hide() && clonep(item))
		{
			result += HIR "Chưa giám định\n";
			break;
		}
		if (item->get_stuff_type() == 0 && item->get_max_lasting() > 0)
			result += sprintf("Độ bền: %d / %d \n", item->get_lasting() / 100, item->get_max_lasting() / 100);
		else if (item->get_max_lasting() > 0)
			result += sprintf("Số lần sử dụng: %d / %d\n", item->get_lasting() / 100, item->get_max_lasting() / 100);
		file = get_file_name(item);

		if (point = item->get("ap") + item->get("ap+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "ap", point, color);

		if (point = item->get("app"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "app", point, color);
		if (point = item->get("ap2"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "ap2", point, color);

		if (point = item->get("double"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "double", point, color);
		}
		if (point = item->get("double2"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "double2", point, color);
		if (point = item->get("ap%") + item->get("ap%+"))
		{
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "ap%", point, color);
		}
		if (point = item->get("!%") + item->get("!%+"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "!%", point, color);
		}
		if (point = item->get("cp") + item->get("cp+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "cp", point, color);
		if (point = item->get("cpp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "cpp", point, color);
		if (point = item->get("cp2"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "cp2", point, color);

		if (point = item->get("cp%") + item->get("cp%+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "cp%", point, color);
		if (point = item->get("c!%") + item->get("c!%+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "c!%", point, color);
		if (point = item->get("t!%") + item->get("t!%+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "t!%", point, color);
		if (point = item->get("dp") + item->get("dp+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "dp", point, color);
		if (point = item->get("dpp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "dpp", point, color);
		if (point = item->get("dp2"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "dp2", point, color);

		if (point = item->get("pp") + item->get("pp+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "pp", point, color);
		if (point = item->get("ppp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "ppp", point, color);
		if (point = item->get("pp2"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "pp2", point, color);

		if (point = item->get("hp") + item->get("hp+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "hp", point, color);
		if (point = item->get("hpp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "hpp", point, color);
		if (point = item->get("hp2"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "hp2", point, color);

		if (point = item->get("hp%") + item->get("hp%+"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "hp%", point, color);
		}
		if (point = item->get("mp") + item->get("mp+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "mp", point, color);
		if (point = item->get("mpp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "mpp", point, color);
		if (point = item->get("mp2"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "mp2", point, color);
		if (point = item->get("mp%") + item->get("mp%+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "mp%", point, color);
		if (point = item->get("hp*") + item->get("hp*+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "hp*", point, color);
		if (point = item->get("mp*") + item->get("mp*+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "mp*", point, color);
		if (point = item->get("sp") + item->get("sp+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "sp", point, color);
		if (point = item->get("sp2"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "sp2", point, color);
		if (point = item->get("?%") + item->get("?%+"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "?%", point, color);
		}
		if (point = item->get("c?%") + item->get("c?%+"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "c?%", point, color);
		}
		if (point = item->get("-*") + item->get("-*+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "-*", point, color);
		if (point = item->get("-*%") + item->get("-*%+"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "-*%", point, color);
		}
		if (point = item->get("-c*") + item->get("-c*+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "-c*", point, color);
		if (point = item->get("-c*%") + item->get("-c*%+"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "-c*%", point, color);
		}
		if (point = item->get_poison())
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "@", point, color);
		if (point = item->get("@%") + item->get("@%+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "@%", point, color);
		if (point = item->get("X@%") + item->get("X@%+"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "X@%", point, color);
		}
		if (point = item->get("-@%") + item->get("-@%+"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "-@%", point, color);
		}
		if (point = item->get("/%") + item->get("/%+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "/%", point, color);
		if (point = item->get("??%") + item->get("??%+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "??%", point, color);
		if (point = item->get("#%") + item->get("#%+"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "#%", point, color);
		if (point = item->get("hp+@"))
			result += sprintf("Mỗi 1 giây hồi phục %d Khí Huyết\n", point);
		if (point = item->get("mp+@"))
			result += sprintf("Mỗi 1 giây hồi phục %d Pháp Lực\n", point);
		//	if( point = item->get(  "mau+@" )) result += sprintf("Mỗi 1 giây hồi phục %d Khí Huyết\n",point);
		//	if( point = item->get(  "mana+@" )) result += sprintf("Mỗi 1 giây hồi phục %d Pháp Lực\n",point);
		if (point = item->get("yuan+@"))
			result += sprintf("Mỗi 1 giây hồi phục %d điểm Nguyên Khí\n", point);
		if (point = item->get("cp+@"))
			result += sprintf("Gia tăng hiệu quả pháp thuật thương tổn %d điểm\n", point);
		if (point = item->get("heal+@"))
			result += sprintf("Gia tăng hiệu quả pháp thuật trị liệu %d điểm\n", point);
		if (point = item->get("trilieu"))
			result += sprintf("C Hiệu quả trị liệu + %d%%\n", point);
		break;

	case ITEM_TYPE_TALISMAN:
		level = item->get_level();
		if (item->get_stuff_type() == 0)
		{
			switch (level)
			{
			case 1:
				color = HIC;
				break;
			case 2:
				color = HIY;
				break;
			default:
				color = PPM;
				break;
			}
		}
		else
		{
			switch (item->get_item_color())
			{
			case 0:
				color = "";
				break;
			case 1:
				color = HIC;
				break;
			case 3:
				color = PPM;
				break;
			case 4:
				color = HIG;
				break;
			case 5:
				color = HIR;
				break;
			default:
				color = HIY;
				break;
			}
		}
		if (!item->is_limit_time_item())
			result += sprintf("Độ bền: %d / %d \n", item->get_lasting() / 100, item->get_max_lasting() / 100);
		if (item->get_stuff_type() == 0)
			result += sprintf(" %d cấp Pháp Bảo\n", level);
		else
			result += sprintf("Kĩ năng yêu cầu %d cấp\n", level);

		switch (item->get_talisman_type())
		{
		default:
			break;

		case 2: // Cửu Long Thần Hỏa Trảo
			result += sprintf("Khí huyết: %d / %d \n", item->get_hp(), item->get_max_hp());
			break;
		case 9: // 招魂幡
			if ((point = item->get_heart_sec()) < item->get_time_interval())
				result += sprintf(HIR "%d％ 准备中\n", point * 100 / item->get_time_interval());
			else
				result += HIG "100％ 准备好\n";
			break;
		}

		if (point = item->get("ap"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "ap", point);
		if (point = item->get("ap%"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "ap%", point);
		if (point = item->get("!%"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "!%", point);
		}
		if (point = item->get("cp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "cp", point);
		if (point = item->get("cp%"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "cp%", point);
		if (point = item->get("c!%"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "c!%", point);
		if (point = item->get("t!%"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "t!%", point);
		if (point = item->get("dp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "dp", point);
		if (point = item->get("pp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "pp", point);
		if (point = item->get("hp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "hp", point);
		if (point = item->get("hp%"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "hp%", point);
		}
		if (point = item->get("mp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "mp", point);
		if (point = item->get("mp%"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "mp%", point);
		if (point = item->get("hp*"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "hp*", point);
		if (point = item->get("mp*"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "mp*", point);
		if (point = item->get("sp"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "sp", point);
		if (point = item->get("?%"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "?%", point);
		}
		if (point = item->get("c?%"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "c?%", point);
		}
		if (point = item->get("-*"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "-*", point);
		if (point = item->get("-*%"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "-*%", point);
		}
		if (point = item->get("-c*"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "-c*", point);
		if (point = item->get("-c*%"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "-c*%", point);
		}
		//                              if( point = item->get_poison() ) result += ITEM_EQUIP_D->get_chinese_prop_string_2(color,   "@" , point);
		if (point = item->get("@%"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "@%", point);
		if (point = item->get("X@%"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "X@%", point);
		}
		if (point = item->get("-@%"))
		{

			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "-@%", point);
		}
		if (point = item->get("/%"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "/%", point);
		if (point = item->get("??%"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "??%", point);
		if (point = item->get("#%"))
			result += ITEM_EQUIP_D->get_chinese_prop_string_2(color, "#%", point);

		break;

	case ITEM_TYPE_FLAG:
		name = who->get_fam_name();
		result += sprintf("Môn phái thích hợp dùng: %s Vân Mộng Cốc\n", name != "Vân Mộng Cốc" ? HIR : NOR);

		color = "";
		break;

	case ITEM_TYPE_POISON:
		name = who->get_fam_name();
		//                                result += sprintf( "Môn phái thích hợp dùng: %s Đường Môn\n", name != "Đường Môn" ? HIR : NOR );

		file = get_file_name(item);
		if (point = item->get_poison())
			result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "@", point);

		color = "";
		break;

	case ITEM_TYPE_POISON_2:
		if (point = item->get_poison())
			result += sprintf("Độc tính: %d\n", point);

		color = "";
		break;

	case ITEM_TYPE_BOOK:
	case ITEM_TYPE_BOOK_2:
		name = item->get_family_name();
		if (name != " －" && name != "" && name != 0)
			result += sprintf("Môn phái thích hợp dùng: %s %s \n", name[1.. < 1] != who->get_fam_name() ? HIR : NOR, name[1.. < 1]);

		break;

	case ITEM_TYPE_FLY_SEAL:
		switch (who->get_latest_city() / 100)
		{
		case 10:
			result += "Trở về: Tề Quốc\n";
			break;
		case 20:
			result += "Trở về: Hàn Quốc\n";
			break;
		case 30:
			result += "Trở về: Triệu Quốc\n";
			break;
		case 40:
			result += "Trở về: Ngụy Quốc\n";
			break;
		case 50:
			result += "Trở về: Tần Quốc\n";
			break;
		case 60:
			result += "Trở về: Sở Quốc\n";
			break;
		case 70:
			result += "Trở về: Yên Quốc\n";
			break;
		case 80:
			result += "Trở về: Chu Quốc\n";
			break;
		default:
			result += "Trở về: Tân Thủ thôn\n";
			break;
		}

		color = "";
		break;

	case ITEM_TYPE_GOOD:
		if (point = item->get_buyin())
			result += sprintf("买入价: %d\n", point);

		color = "";
		break;

	case ITEM_TYPE_CHEQUE2:
		if (point = item->get_orgin_money())
			result += sprintf("Tiền vốn: %d\Vốn lưu động: %d\n当流动资金达到一定数目时，交还商票给门派的司库即可完成筹集资金任务。", point, item->get_money());
		color = "";
		break;
	case ITEM_TYPE_CHEQUE:
		if (point = item->get_orgin_money())
			result += sprintf("Tiền vốn: %d\nVốn lưu động: %d\nVốn lưu động đạt tới %d thì giao cho \nTrưởng Phòng Tiên Sinh \nđể hoàn thành nhiệm vụ", point, item->get_money(), point * 3 / 2);
		color = "";
		break;

	case ITEM_TYPE_TREASURE:
		if (objectp(map = get_map_object(item->get_map_z())))
		{
			if (item->get_name() == "挖宝小锄头")

				result += sprintf("在" HIR "%s国的（%d，%d）" NOR "似乎隐藏着什么宝物。\n", map->get_name(), item->get_map_x(), item->get_map_y());
			else
				result += sprintf("Vị trí: %s ( %d , %d )\n", map->get_name(), item->get_map_x(), item->get_map_y());
		}
		break;

	case ITEM_TYPE_POTENTIAL:
		if (point = item->get_potential())
			result += sprintf("Tiềm năng: %+d\n", point);

		color = "";
		break;
	case ITEM_TYPE_SPECIAL:
		break;
	case ITEM_TYPE_KIMNGUYENBAO:
		if (point = "sys/sys/test_db"->get_yuanbao(item))
			result += sprintf(HIY "Kim Nguyên Bảo: %+d\n", point / 10);

		color = "";
		break;
	case ITEM_TYPE_CHIENTICH:
		if (point = item->get_save_2("changping.score"))
			result += sprintf(HIY "Điểm Chiến Tích: %+d\n", point);

		color = "";
		break;
	}
	/// Khảm Nạm

	if (item->get("duc_lo.1") || item->get("duc_lo.2") || item->get("duc_lo.3"))
	{
		result += "\n";
		result += HIG "【Bảo thạch khảm nạm】\n";
		if (item->get("duc_lo.1") == 1)
		{
			result += "Trống\n";
		}

		if (item->get("duc_lo.1") && item->get("duc_lo.1") != 1)
		{
			if (item->get("ap3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "ap3", item->get("duc_lo.1"), PPM);
			}
			if (item->get("cp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "cp3", item->get("duc_lo.1"), PPM);
			}
			if (item->get("dp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "dp3", item->get("duc_lo.1"), PPM);
			}
			if (item->get("pp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "pp3", item->get("duc_lo.1"), PPM);
			}
			if (item->get("hp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "hp3", item->get("duc_lo.1"), PPM);
			}
		}
		if (item->get("duc_lo.2") == 1)
		{
			result += "Trống\n";
		}
		if (item->get("duc_lo.2") && item->get("duc_lo.2") != 1)
		{
			if (item->get("ap3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "ap3", item->get("duc_lo.2"), PPM);
			}
			if (item->get("cp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "cp3", item->get("duc_lo.2"), PPM);
			}
			if (item->get("dp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "dp3", item->get("duc_lo.2"), PPM);
			}
			if (item->get("pp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "pp3", item->get("duc_lo.2"), PPM);
			}
			if (item->get("hp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "hp3", item->get("duc_lo.2"), PPM);
			}
		}
		if (item->get("duc_lo.3") == 1)
		{
			result += "Trống\n";
		}
		if (item->get("duc_lo.3") && item->get("duc_lo.3") != 1)
		{
			if (item->get("ap3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "ap3", item->get("duc_lo.3"), PPM);
			}
			if (item->get("cp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "cp3", item->get("duc_lo.3"), PPM);
			}
			if (item->get("dp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "dp3", item->get("duc_lo.3"), PPM);
			}
			if (item->get("pp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "pp3", item->get("duc_lo.3"), PPM);
			}
			if (item->get("hp3"))
			{
				result += ITEM_EQUIP_D->get_chinese_prop_string_3(file, "hp3", item->get("duc_lo.3"), PPM);
			}
		}
	}

	if (!flag && (point = item->get_value()) > 0)
	{
		if (!(level = item->get_max_lasting()))
			point = point / 2;
		else
			point = point / 2 * (item->get_lasting() * 100 / level) / 100; // 小心越界
		result += sprintf("Giá bán ra: %d \n", point);
	}
	if (item->get_item_type_2() == ITEM_TYPE_2_PRODUCT)
	{
		fileobj = load_object(sprintf("/skill/06/%04d", item->get_product_skill()));
		if (fileobj)
		{
			if (who->get_skill(item->get_product_skill()))
				result += sprintf("Võ công yêu cầu : %s \n", fileobj->get_name());
			else
				result += sprintf(HIR "Võ công yêu cầu : %s \n", fileobj->get_name());
		}
		if (who->get_skill(item->get_product_skill()) < item->get_product_level())
			result += sprintf(HIR "Đẳng cấp Võ công yêu cầu: %d \n", item->get_product_level());
		else
			result += sprintf("Đẳng cấp Võ công yêu cầu: %d \n", item->get_product_level());
		if ("/sys/item/product"->check_vita_skill(who, item->get_product_type() + item->get_product_skill() * 100) == 1)
			result += HIC "Đã học";
		product = item->get_product();
		if (strlen(product) < 6)
			fileobj = load_object(sprintf("/item/stuff/%04d", to_int(product)));
		else
			fileobj = load_object(item->get_product());
		if (fileobj)
		{
			if (item->get_item_color() == 2)
				result += sprintf("\n " HIY "Thành phẩm: %s \n", fileobj->get_name());
			else if (item->get_item_color() == 1)
				result += sprintf("\n " HIC "Thành phẩm: %s \n", fileobj->get_name());
			else
				result += sprintf("\n Thành phẩm: %s \n", fileobj->get_name());
			result += sprintf(" %s \n", "/sys/item/item"->get_look_string(who, fileobj, 0));
		}
	}
	// nếu cái này mà lag thì làm cái set("suit_hide");
	if (item->is_suit())
	{
		// whosee = item->get_owner();
		// if (!whosee)
		// 	result += "sys/user/suit"->get_suit_desc(who, item) + "\n";
		// else
		// {
		// 	if (whosee->get_number() == who->get_number())
		// 	{
		// 		result += "sys/user/suit"->get_suit_desc(who, item) + "\n";
		// 	}
		// }
		//	tell_user(who, "%d", getoid(item));
		if (find_user_item(sprintf("%x#", getoid(item)), who))
		{
			result += "sys/user/suit"->get_suit_desc(who, item) + "\n";
		}
	}
	if (item->get_equip_type() == FAMILY_TYPE)
	{

		result += item->get_tinvat_desc();
		result += item->get_family_desc();
	}
	switch (item->get_item_color())
	{
	default:
		color = "";
		break;
	case 1:
		color = HIC;
		break;
	case 2:
		color = HIY;
		break;
	case 3:
		color = PPM;
		break;
	case 4:
		color = HIG;
		break;
	case 5:
		color = HIR;
		break;
	}
	if (stringp(file = item->get_tail_desc()))
		result += file + "\n";
	if ((lockutil = item->get_lock_until()) && (lockutil -= gone_time(item->get_lock_time())) > 0)
	{
		if (result[strlen(result) - 1] != '\n')
			result += "\n";
		result += "[Bị khóa đến]";
		result += sprintf(" %s \n", short_time(item->get_lock_time() + item->get_lock_until()));
	}
	else if ((item->get_lock_until() == 0) && (lockutil = item->get_lock_time()) > 0)
	{
		if (result[strlen(result) - 1] != '\n')
			result += "\n";
		if (item->get_lock_time() < time())
		{
			if (!item->is_nangcap())
				result += HIR "[Hết hạn sử dụng]";
		}
		else
		{
			if (!item->is_nangcap())
				result += "[Sử dụng đến]";
			else
				result += "[Ảo hóa ngoại hình đến]";
			result += sprintf(" %s \n", short_time(item->get_lock_time()));
		}
	}

	return color + result;
}

string get_prop_string(object item)
{
	string id, file, prop;
	int amount, index, point, locktime, lockutil, no_give;
	int i, size;
	file = get_file_name(item);
	amount = item->get_amount();
	index = get_d(item);
	no_give = item->get_no_give();
	if (!stringp(id = item->get_user_id()))
		id = "-";
	locktime = item->get_lock_time();
	lockutil = item->get_lock_until();

	switch (item->get_item_type())
	{
	case ITEM_TYPE_EQUIP:
		prop = sprintf("%s;%d;%d;%d;%d;%d;%s;[%s]%d,%d",
					   file, amount, no_give, index, item->get_lasting(), item->get_max_lasting(), ITEM_EQUIP_D->get_save_prop_string(item), id, locktime, lockutil);
		break;

	case ITEM_TYPE_TALISMAN:
		switch (item->get_talisman_type())
		{
		default:
			point = 0;
			break;
		case 2:
			point = item->get_hp();
			break; // Cửu Long Thần Hỏa Trảo
		case 9:
			point = item->get_heart_sec();
			break; // 招魂幡
		}
		prop = sprintf("%s;%d;%d;%d;%d;%d;%d;[%s]%d,%d",
					   file, amount, no_give, index, item->get_lasting(), item->get_max_lasting(), point, id, locktime, lockutil);
		break;

	case ITEM_TYPE_POISON_2:
		prop = sprintf("%s;%d;%d;%d;[%s]%d,%d",
					   file, amount, index, item->get_poison(), id, locktime, lockutil);
		break;

	case ITEM_TYPE_GOOD:
		prop = sprintf("%s;%d;%d;%d;[%s]%d,%d",
					   file, amount, index, item->get_buyin(), id, locktime, lockutil);
		break;
	case ITEM_TYPE_CHEQUE2:
	case ITEM_TYPE_CHEQUE:
		prop = sprintf("%s;%d;%d;%d;%d;[%s]%d,%d",
					   file, amount, index, item->get_orgin_money(), item->get_money(), id, locktime, lockutil);
		break;

	case ITEM_TYPE_TREASURE:
		prop = sprintf("%s;%d;%d;%d;%d;%d;[%s]%d,%d",
					   file, amount, index, item->get_map_z(), item->get_map_x(), item->get_map_y(), id, locktime, lockutil);
		break;

	case ITEM_TYPE_DIAMOND_2:
		prop = sprintf("%s;%d;%d;%d;[%s]%d,%d",
					   file, amount, index, item->get_item_level(), id, locktime, lockutil);
		break;

	case ITEM_TYPE_POTENTIAL:
		prop = sprintf("%s;%d;%d;%d;[%s]%d,%d",
					   file, amount, index, item->get_potential(), id, locktime, lockutil);
		break;
	case ITEM_TYPE_SPECIAL:
		prop = sprintf("%s;%d;%d;%s;[%s]%d,%d", file, amount, index, item->get("special"), id, locktime, lockutil);
		break;
	case ITEM_TYPE_KIMNGUYENBAO:
		prop = sprintf("%s;%d;%d;%d;[%s]%d,%d",
					   file, amount, index, "sys/sys/test_db"->get_yuanbao(item), id, locktime, lockutil);
		break;
	case ITEM_TYPE_CHIENTICH:
		prop = sprintf("%s;%d;%d;%d;[%s]%d,%d",
					   file, amount, index, item->get_save_2("changping.score"), id, locktime, lockutil);
		break;
	case ITEM_TYPE_DIAMOND_3:
		prop = sprintf("%s;%d;%d;%d;%s;[%s]%d,%d", file, item->get_level(), no_give, index, item->get("special"), id, locktime, lockutil);
		break;
	default:
		prop = sprintf("%s;%d;%d;%d;[%s]%d,%d", file, amount, no_give, index, id, locktime, lockutil);
		break;
	}
	return prop;
}

string get_pawn_save_string(object item)
{
	string file, total, prop, id;
	int amount, locktime, lockutil, point, no_give;
	file = get_file_name(item);
	amount = item->get_amount();
	no_give = item->get_no_give();
	if (!load_object(file))
	{
		return "";
	}
	if (!stringp(id = item->get_user_id()))
		id = "-";
	locktime = item->get_lock_time();
	lockutil = item->get_lock_until();

	switch (item->get_item_type())
	{
	case ITEM_TYPE_EQUIP:
		prop = sprintf("%s;%d;%d;%d;%d;%s;[%s]%d,%d",
					   file, amount, no_give, item->get_lasting(), item->get_max_lasting(), ITEM_EQUIP_D->get_save_prop_string_2(item), id, locktime, lockutil);
		break;

	case ITEM_TYPE_TALISMAN:
		switch (item->get_talisman_type())
		{
		default:
			point = 0;
			break;
		case 2:
			point = item->get_hp();
			break; // Cửu Long Thần Hỏa Trảo
		case 9:
			point = item->get_heart_sec();
			break; // 招魂幡
		}
		prop = sprintf("%s;%d;%d;%d;%d;%d;[%s]%d,%d",
					   file, amount, no_give, item->get_lasting(), item->get_max_lasting(), point, id, locktime, lockutil);
		break;

	case ITEM_TYPE_POISON_2:
		prop = sprintf("%s;%d;%d;[%s]%d,%d",
					   file, amount, item->get_poison(), id, locktime, lockutil);
		break;

	case ITEM_TYPE_TREASURE:
		prop = sprintf("%s;%d;%d;%d;%d;[%s]%d,%d",
					   file, amount, item->get_map_z(), item->get_map_x(), item->get_map_y(), id, locktime, lockutil);
		break;

	case ITEM_TYPE_DIAMOND_2:
		prop = sprintf("%s;%d;%d;[%s]%d,%d",
					   file, amount, item->get_item_level(), id, locktime, lockutil);
		break;

	case ITEM_TYPE_POTENTIAL:
		prop = sprintf("%s;%d;%d;[%s]%d,%d",
					   file, amount, item->get_potential(), id, locktime, lockutil);
		break;
	case ITEM_TYPE_SPECIAL:
		prop = sprintf("%s;%d;%s;[%s]%d,%d", file, amount, item->get("special"), id, locktime, lockutil);
		break;
	case ITEM_TYPE_KIMNGUYENBAO:
		prop = sprintf("%s;%d;%d;[%s]%d,%d",
					   file, amount, "sys/sys/test_db"->get_yuanbao(item), id, locktime, lockutil);
		break;
	case ITEM_TYPE_CHIENTICH:
		prop = sprintf("%s;%d;%d;[%s]%d,%d",
					   file, amount, item->get_save_2("changping.score"), id, locktime, lockutil);
		break;
	case ITEM_TYPE_DIAMOND_3:
		prop = sprintf("%s;%d;%d;[%s]%d,%d", file, item->get_level(), no_give, id, locktime, lockutil);
		break;
	default:
		prop = sprintf("%s;%d;%d;[%s]%d,%d", file, amount, no_give, id, locktime, lockutil);
		break;
	}
	return prop;
}
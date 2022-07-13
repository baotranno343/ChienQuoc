#include <item.h>
#include <ansi.h>
#include <equip.h>

int check_match(object equip, object diamond);
int mix1(object me, object *item);

// 函数：命令处理
int main(object me, string arg)
{
	object *item, who;
	string name, make, result, forge, index;
	int *id;
	int i, flag, level, rate;

	if (!arg)
		return 1;

	item = ({
		0,
		0,
	});
	id = ({
		0,
		0,
	});

	if (sscanf(arg, "? %s %x# %x#", name, id[0], id[1]) == 3)
		flag = 1;
	else if (sscanf(arg, "%s %x# %x#", name,
					id[0], id[1]) == 3)
		flag = 2;
	else
	{
		notify("Bạn muốn tinh luyện đồ vật gì?");
		return 1;
	}
	/*
        if( !objectp( who = find_char(name) ) ) return 1;

        if( !who->is_maker() ) return 1;

        if( !inside_screen_2(me, who) )
        {
                notify( "Bạn cách %s quá xa rồi.", who->get_name() );
                return 1;
        }

        me->to_front_eachother(who);
*/
	if (flag == 1) //精炼成功率
	{
		for (i = 0; i < 2; i++)
		{
			if (!objectp(item[i] = present(sprintf("%x#", id[i]), me, 1, MAX_CARRY * 4))) // 物品是否存在？
			{
				send_user(me, "%c%c%c%d", 0x25, 0, 0, 0);
				return 1;
			}
		}
		if (item[1]->get_item_type() != ITEM_TYPE_DIAMOND_3)
		{
			send_user(me, "%c%c%c%d", 0x25, 0, 0, 0);
			return 1;
		}
		if (item[1]->get_diamond_type() != "forge") //Đánh giá đá rèn có phù hợp hay không
		{
			make = item[0]->get("make");
			level = item[1]->get_level();
			if (make == 0)
				make = "";
			if (strlen(make) != level - 1)
			{
				send_user(me, "%c%c%c%d", 0x25, 0, 0, 0);
				return 1;
			}
			if (check_match(item[0], item[1]) == 0)
			{
				send_user(me, "%c%c%c%d", 0x25, 0, 0, 0);
				return 1;
			}
		}
		else //Bản án đá giả mạo kết quả phù hợp với thiết bị.
		{
			forge = item[0]->get("forge"); //Đây là ngôi sao của trang bị
			if (forge == 0)
				forge = "";
			level = strlen(forge);
			index = item[1]->get_forge_index();
			if ((level == 1 || level == 0) && index != "1")
			{
				notify("Loại đá rèn không phù hợp, không thể tinh luyện");
				return 1;
			}
			if ((level == 2 || level == 3) && index != "2")
			{
				notify("Loại đá rèn không phù hợp, không thể tinh luyện");
				return 1;
			}
			if (level >= 4)
			{
				if ((index != "3" && index != "4"))
				{
					notify("Loại đá rèn không phù hợp, không thể tinh luyện");
					return 1;
				}
			}
		}
		if (item[1]->get_diamond_type() == "forge") //Ở đây là để tính toán tỷ lệ thành công của các thiết bị tập thể dục rèn đá
		{
			rate = 10000;
			for (i = 4; i <= level; i++)
			{
				rate = rate * 3 / 5;
			}
			//			rate = rate / 100;
			rate = 10;
		}
		else //Dưới đây là tỷ lệ thành công thiết bị tính toán spar giả mạo.
		{
			switch (level)
			{
			case 1:
				rate = 100;
				break;
			case 2:
				rate = 90;
				break;
			case 3:
				rate = 80;
				break;
			case 4:
				rate = 70;
				break;
			case 5:
				rate = 60;
				break;
			case 6:
				rate = 50;
				break;
			case 7:
				rate = 40;
				break;
			case 8:
				rate = 30;
				break;
			case 9:
				rate = 20;
				break;
			default:
				rate = 10;
				break;
			}
		}
		if (level != 1 && me->get_vip() && !me->get_save_2("vip_package.trial"))
			rate += 0;
		send_user(me, "%c%c%c%d", 0x25, 0, rate, 0);
		return 1;
	}
	else //精炼装备
	{
		for (i = 0; i < 2; i++)
		{
			if (!objectp(item[i] = present(sprintf("%x#", id[i]), me, 1, MAX_CARRY * 4))) // 物品是否存在？
			{
				return 1;
			}
		}
		if (item[1]->get_item_type() != ITEM_TYPE_DIAMOND_3)
		{
			notify("Tinh chỉnh đá");
			return 1;
		}
		if (item[1]->get_diamond_type() == "forge")
		{
			return mix1(me, ({item[0], item[1]})); //Giả mạo thiết bị đá giả mạo
		}
		if (item[1]->get_mix_level() && item[0]->get_level() > item[1]->get_mix_level())
		{
			notify(sprintf("Xin lỗi, bạn không thể sử dụng các thiết bị hơn spar %d mức ", item[1]->get_mix_level()));
			return 1;
		}
		make = item[0]->get("make");
		level = item[1]->get_level();
		if (make == 0)
			make = "";
		if (strlen(make) != level - 1)
		{
			notify("Tinh chỉnh bằng đá quý và mức độ thiết bị không phù hợp.");
			return 1;
		}
		if (check_match(item[0], item[1]) == 0)
		{
			notify("Các loại đá quý không phù hợp không thể được tinh chế");
			return 1;
		}
		switch (level)
		{
		case 1:
			rate = 100;
			break;
		case 2:
			rate = 90;
			break;
		case 3:
			rate = 80;
			break;
		case 4:
			rate = 70;
			break;
		case 5:
			rate = 60;
			break;
		case 6:
			rate = 50;
			break;
		case 7:
			rate = 40;
			break;
		case 8:
			rate = 30;
			break;
		case 9:
			rate = 20;
			break;
		default:
			rate = 10;
			break;
		}
		if (level != 1 && me->get_vip() && !me->get_save_2("vip_package.trial"))
			rate += 0;
		if (random100() < rate)
		{
			item[0]->add(item[1]->get_diamond_type(), item[1]->get_diamond_add());
			make += item[1]->get_diamond_index();
			item[0]->set("make", make);
			if (item[1]->is_record())
			{
				result = sprintf("Tinh chế thành công biến mất %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item[1]->get_name(), "/sys/item/item"->get_pawn_save_string(item[1]), 1, item[1]->get_user_id(), get_z(me), get_x(me), get_y(me));
				//"/sys/user/cmd"->log_item(result);
			}
			item[1]->remove_from_user();
			destruct(item[1]);
			send_user(me, "%c%d%c", 0x31, getoid(item[0]), 0);
			write_user(me, ECHO " %s tinh luyện thành công! Bạn đạt được %s ＋ %d .", item[0]->get_name(), item[0]->get_name(), level);
			if (level >= 9)
			{
				result = HIY + sprintf("Chúc mừng %s ( %d ) thành công sẽ luyện được %s ＋ %d ", me->get_name(), me->get_number(), item[0]->get_name(), level);
				CHAT_D->sys_channel(0, result);
			}
		}
		else
		{
			if (item[1]->is_record())
			{
				result = sprintf("Tinh chỉnh không biến mất %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item[1]->get_name(), "/sys/item/item"->get_pawn_save_string(item[1]), 1, item[1]->get_user_id(), get_z(me), get_x(me), get_y(me));
				//"/sys/user/cmd"->log_item(result);
			}
			item[1]->remove_from_user();
			destruct(item[1]);
			write_user(me, ECHO "%s tinh luyện không thành công！", item[0]->get_name());
		}
		return 1;
	}

	return 1;
}

int check_match(object equip, object diamond)
{
	string type = diamond->get_diamond_type();
	switch (equip->get_equip_type())
	{
	case HEAD_TYPE:
	case ARMOR_TYPE:
		if (type == "hp")
			return 1;
		if (type == "mp")
			return 1;
		if (type == "dp")
			return 1;
		if (type == "pp")
			return 1;
		break;
	case NECK_TYPE:
		if (type != "double" && type != "double2")
			return 1;
		break;
	case WEAPON_TYPE:
		if (type == "ap")
			return 1;
		if (type == "cp")
			return 1;
		if (type == "!%")
			return 1;
		if (type == "double")
			return 1;
		if (type == "double2")
			return 1;
		break;
	case WAIST_TYPE:
		if (type != "ap" && type != "cp" && type != "double" && type != "double2")
			return 1;
		break;
	case BOOTS_TYPE:
		if (type != "ap" && type != "cp" && type != "!%" && type != "double" && type != "double2")
			return 1;
		break;
	}
}
//锻造石精炼装备
int mix1(object me, object *item)
{
	int level, rate, rate1, i, color, bind;
	string forge, result, index;
	if (!(i = item[0]->get_equip_type()) || (i != WEAPON_TYPE && i != ARMOR_TYPE && i != HEAD_TYPE && i != BOOTS_TYPE && i != WAIST_TYPE && i != NECK_TYPE))
		return 0;
	forge = item[0]->get("forge");
	index = item[1]->get_forge_index();
	if (index < "5")
		return 0;
	if (forge == 0)
		forge = "";
	level = strlen(forge);
	if (item[1]->get_level() != 1)
	{
		notify("Đá rèn cho các lớp học đầu vào công cộng trên một phân hủy.");
		return 1;
	}
	if (index != "5" && index != "6" && index != "7")
	{
		notify("Không thể sử dụng.");
		return 1;
	}
	if (index == "5")
	{
		if (level >= 7 || level < 6)
		{
			notify("Rèn đá chính chỉ rèn thiết bị từ 6 sao và ít hơn 7 sao.");
			return 1;
		}
	}
	if (index == "6")
	{
		if (level >= 8 || level < 7)
		{
			notify("Trung cấp rèn đá chỉ rèn thiết bị từ 7 sao và ít hơn 8 sao.");
			return 1;
		}
	}
	if (index == "7")
	{
		if (level >= 9 || level < 8)
		{
			notify("Trung cấp rèn đá chỉ rèn thiết bị từ 8 sao và ít hơn 9 sao.");
			return 1;
		}
	}

	bind = item[0]->get_bind();
	if (me->get_level() / 10 < level + 1)
	{
		notify("Số sao trang bị chỉ rèn được × 10 cấp.");
		return 0;
	}
	color = item[0]->get_item_color();
	rate = 10000;
	for (i = 4; i <= level; i++)
		rate = rate * 3 / 5;
	rate = 100;

	if (me->get_vip() && !me->get_save_2("vip_package.trial"))
		rate += 0;
	rate1 = random100();
	if (is_god(me))
	{
		if (me->get("lb"))
			rate1 = me->get("lb");
		tell_user(me, "Bây giờ xác xuất thành công %d là %d", rate, rate1);
	}
	if (rate1 < rate)
	{
		forge += item[1]->get_forge_index();
		if (item[1]->is_record())
		{
			result = sprintf("Tinh chế thành công biến mất %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item[1]->get_name(), "/sys/item/item"->get_pawn_save_string(item[1]), 1, item[1]->get_user_id(), get_z(me), get_x(me), get_y(me));
			//"/sys/user/cmd"->log_item(result);
		}

		ITEM_EQUIP_D->init_equip_prop_5(item[0]);
		if (color != 0)
			"/sys/sys/count"->add_equip("blue", -1);
		item[0]->set("forge", forge);
		item[1]->remove_from_user();
		destruct(item[1]);
		//item[1]->add_amount(-1); //Mới
		send_user(me, "%c%d%c", 0x31, getoid(item[0]), 0);
		level = strlen(forge);
		write_user(me, ECHO "Chúc mừng bạn thành công rèn ra một %d tinh cấp trang bị!", level);
		if (level >= 7)
		{
			result = HIY + sprintf("Chúc mừng %s thành công rèn ra %d tinh cấp trang bị!", me->get_name(), level);
			CHAT_D->sys_channel(0, result);
		}
	}
	else
	{
		if (item[1]->is_record())
		{
			result = sprintf("Giả mạo không thành công biến mất %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item[1]->get_name(), "/sys/item/item"->get_pawn_save_string(item[1]), 1, item[1]->get_user_id(), get_z(me), get_x(me), get_y(me));
			//"/sys/user/cmd"->log_item(result);
		}
		if (item[1]->get_forge_index() == "4")
		{
			//		 	ITEM_EQUIP_D->reduce_equip_prop(item[0]);
			ITEM_EQUIP_D->reduce_equip_prop_123(item[0]);
			write_user(me, ECHO "Thật không may, rèn thất bại. %s của bạn vẫn còn y nguyên !", item[0]->get_name());
		}
		else
		{
			item[0]->delete ("forge");
			ITEM_EQUIP_D->reset_equip_prop(item[0]);
			write_user(me, ECHO "Thật không may, rèn thất bại. %s của bạn mất hết ngôi sao", item[0]->get_name());
		}
		send_user(me, "%c%d%c", 0x31, getoid(item[0]), 0);
		item[1]->remove_from_user();
		destruct(item[1]);
		//item[1]->add_amount(-1); //Mới
	}
	return 1;
}

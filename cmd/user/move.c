#include <ansi.h>
#include <item.h>
#include <equip.h>

// 函数：命令处理
int main(object me, string arg)
{
	object item, item2;
	int num, num2, amount, amount2, total;
	int i, size, begin, end, flag, count, bag, b, c, d, itemid, rate, level, count_hole;
	string fileobject, result, legend, make, check_hole, *tach_hole;
	string *chi_so;

	if (!arg)
		return 1;
	else if (sscanf(arg, "%s to %d", arg, num) == 2)
		flag = 2;
	else if (sscanf(arg, "! %s %d", arg, num) == 2)
		flag = 3;
	else if (sscanf(arg, "%s %d", arg, num) == 2)
		flag = 1;
	else
		return 1;

	if (!objectp(item = present(arg, me, 0, 0)))
	{
		return 1;
	}
	if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
	{
		send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
		return 1;
	}
	if (me->get_store(sprintf("%02d", get_d(item))))
	{
		notify(item->get_name() + "Muốn ngừng, không thể di chuyển.");
		send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
		return 1;
	}
	bag = me->have_bag();
	b = bag % 100;
	c = (bag / 100) % 100;
	d = bag / 10000;
	if (b > 0 && me->get_bag1_time() > 0 && time() > me->get_bag1_time())
		b = 0;
	if (c > 0 && me->get_bag2_time() > 0 && time() > me->get_bag2_time())
		c = 0;
	if (d > 0 && me->get_bag3_time() > 0 && time() > me->get_bag3_time())
		d = 0;
	if (me->get_reincarnation())
		b = MAX_CARRY;
	//        if (d>18) d = 18;
	if (flag == 1)
	{
		num2 = (get_d(item) - 1) / MAX_CARRY * MAX_CARRY;
		if (num < num2 + 1 || num > num2 + MAX_CARRY) // 同栏之中
		{
			send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
			return 1;
		}
		else if (num2 == MAX_CARRY) // 包裹之内
		{
			if (num > MAX_CARRY + b)
			{
				send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
				return 1;
			}
		}
		else if (num2 == MAX_CARRY * 2) // 乾坤袋之内
		{
			if (num > MAX_CARRY * 2 + c)
			{
				send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
				return 1;
			}
		}
		else if (num2 == MAX_CARRY * 3) // 乾坤袋之内
		{
			if (num > MAX_CARRY * 3 + d)
			{
				send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
				return 1;
			}
		}

		if ((num2 = get_d(item)) != num)
		{
			if (objectp(item2 = number_present(me, num, 0, 0)))
			{
				if (me->get_store(sprintf("%02d", get_d(item2))))
				{
					notify(item2->get_name() + "Muốn ngừng, không thể di chuyển.");
					send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
					return 1;
				}
				if (item->is_specal_move())
				{
					if (item->move_item(me, item, item2))
						return 1;
				}
				//限时物品叠加时间.
				if (item->is_limit_time_item() && item2->is_limit_time_item() && get_file_name(item) == get_file_name(item2))
				{
					result = sprintf("Muốn hợp thành vật phẩm không ?\n" ESC "%c\n" ESC "\nmix2 time_limit %x# %x#\n", 1, getoid(item), getoid(item2));
					send_user(me, "%c%s", ';', "Hai cái hợp thành vật phẩm sau thời hạn hiệu lực đem chồng lên nhau \nđã qua kì hạn vật phẩm sẽ không giảm bớt hiệu lực thời hạn vật phẩm, nhưng sẽ tự động bị thanh trừ.\n");
					send_user(me, "%c%c%s", 0x59, 1, result);
					return 1;
				}
				if (item->get_item_type() == ITEM_TYPE_DIAMOND_3)
				{
					// if (item2->get_item_type() == ITEM_TYPE_DIAMOND_3 && item2->get_diamond_type() != "forge")
					// {
					// 	result = sprintf("Muốn hợp thành bảo thạch không ?\n" ESC "%c\n" ESC "\nmix2 0# %x# %x#\n", 1, getoid(item), getoid(item2));
					// 	send_user(me, "%c%c%s", 0x59, 1, result);
					// 	return 1;
					// }

					if (item2->is_equip() && item2->get_equip_type() != HAND_TYPE)
					{
						make = item2->get("make");
						level = item->get_level();
						if (level > 10)
						{
							notify("Tối đa 10 cấp linh thạch");
							return 1;
						}
						if (make == 0)
							make = "";
						if (strlen(make) != level - 1)
						{
							notify("Bảo thạch loại hình không hợp, không thể tinh luyện");
							send_user(me, "%c%c%c%d", 0x25, 0, 0, 0);
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
							rate += 5;
						if (rate > 100)
							rate = 100;
						result = sprintf("Tỉ lệ thành công tinh luyện cho trang bị hiện nay là " HIR " %d " NOR ",\n Bạn muốn tinh luyện %s không ?\n" ESC "Chấp nhận\nmix3 0# %x# %x#\n" ESC "Hủy bỏ\n", rate, item2->get_name(), getoid(item2), getoid(item));
						send_user(me, "%c%c%w%s", ':', 3, 0, result);
						return 1;
					}
				}

				if (item->get_item_type() == ITEM_TYPE_SHIKE)
				{
					if (item2->is_equip() && item2->get_equip_type() != HAND_TYPE)
					{
						if (item->get("mpp") > 0 && item2->get_equip_type() != BOOTS_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("hpp") > 0 && item2->get_equip_type() != WAIST_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("app") > 0 && item2->get_equip_type() != WEAPON_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("dpp") > 0 && item2->get_equip_type() != ARMOR_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("cpp") > 0 && item2->get_equip_type() != WEAPON_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("double2") > 0 && item2->get_equip_type() != WEAPON_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("ppp") > 0 && item2->get_equip_type() != HEAD_TYPE && item2->get_equip_type() != WAIST_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						count = item2->get("app") + item2->get("dpp") + item2->get("cpp") + item2->get("ppp") + item2->get("hpp") + item2->get("mpp") + item2->get("double2");
						if (count > 0)
						{
							result = sprintf("%s đã được khảm nạm, có muốn thay thế không ?\n" ESC "%c\n" ESC "move ! %x# %d\n", item2->get_name(), 1, getoid(item), num);
						}
						else
						{
							result = sprintf("Muốn khảm nạm %s hay không ?\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", item2->get_name(), 1, getoid(item), num);
						}
						send_user(me, "%c%c%s", 0x59, 1, result);
						return 1;
					}
				}
				if (item->get_item_type() == ITEM_TYPE_DAKHAM)
				{
					if (item2->is_equip() && item2->get_equip_type() != HAND_TYPE)
					{
						if (item->get("hp3") > 0 && item2->get_equip_type() != WAIST_TYPE && item2->get_equip_type() != ARMOR_TYPE && item2->get_equip_type() != BOOTS_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("ap3") > 0 && item2->get_equip_type() != WEAPON_TYPE && item2->get_equip_type() != NECK_TYPE && item2->get_equip_type() != HEAD_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("dp3") > 0 && item2->get_equip_type() != ARMOR_TYPE && item2->get_equip_type() != WAIST_TYPE && item2->get_equip_type() != BOOTS_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("cp3") > 0 && item2->get_equip_type() != WEAPON_TYPE && item2->get_equip_type() != NECK_TYPE && item2->get_equip_type() != HEAD_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("pp3") > 0 && item2->get_equip_type() != BOOTS_TYPE && item2->get_equip_type() != WAIST_TYPE && item2->get_equip_type() != ARMOR_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						count = item2->get("ap3") + item2->get("dp3") + item2->get("cp3") + item2->get("pp3") + item2->get("hp3");
						if (count > 0)
						{
							result = sprintf("%s đã được khảm nạm, có muốn thay thế không ?\n" ESC "%c\n" ESC "move ! %x# %d\n", item2->get_name(), 1, getoid(item), num);
						}
						else
						{
							result = sprintf("Muốn khảm nạm %s hay không ?\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", item2->get_name(), 1, getoid(item), num);
						}
						send_user(me, "%c%c%s", 0x59, 1, result);
						return 1;
					}
				}
				if (item->is_dachietxuat())
				{
					if (item2->is_equip() && item2->get_equip_type())
					{

						result = sprintf("Muốn khảm nạm %s hay không ?\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", item2->get_name(), 1, getoid(item), num);
						send_user(me, "%c%c%s", 0x59, 1, result);
						return 1;
					}
				}
				if (item->get_name() == "Thiên Ấn Toàn Năng")
				{
					if (item2->get_item_type() == ITEM_TYPE_TALISMAN)
					{
						send_user(me, "%c%c%w%s", ':', 3, 1, sprintf("Bạn Muốn Gì? \n" ESC "Tạo Ấn\nmixhole 0 %x# %x#\n" ESC "Khắc Ấn\nmixhole 1 %x# %x#\n" ESC "Huỷ bỏ", getoid(item2), getoid(item), getoid(item2), getoid(item)));
						return 1;
					}
				}

				if (item->is_food_huyenthu())
				{
					if (item2->is_huyenthu())
					{
						result = sprintf("Bạn muốn dùng cho %s hay không ?\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", item2->get_name(), 1, getoid(item), num);

						send_user(me, "%c%c%s", 0x59, 1, result);
						return 1;
					}
				}
				if (item->is_aohoa())
				{
					if (item2->is_nangcap() && item2->get_equip_type() == BACK_TYPE)
					{
						send_user(me, "%c%c%w%s", ':', 3, 1, sprintf("Bạn muốn ảo hóa cho %s hay không \n" ESC "Đồng Ý\nmixaohoa %x# %x#\n" ESC "Huỷ bỏ", item2->get_name(), getoid(item2), getoid(item)));
						return 1;
					}
				}
				if (item->is_aohoa_rm())
				{
					if (item2->is_nangcap() && item2->get_equip_type() == BACK_TYPE)
					{
						result = sprintf("Bạn muốn hủy ảo hóa của %s hay không ?\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", item2->get_name(), 1, getoid(item), num);

						send_user(me, "%c%c%s", 0x59, 1, result);
						return 1;
					}
				}

				if (item->is_mirror())
				{
					if (item2->is_equip() && item2->get_hide() && item2->get_equip_type() != HAND_TYPE)
					{
						result = sprintf("Muốn giám định %s không ?\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", item2->get_name(), 1, getoid(item), num);
						send_user(me, "%c%c%s", 0x59, 1, result);
						return 1;
					}
				}
				if (item->is_repair() && item2->is_equip())
				{
					if (item->move_item(me, item, item2))
						return 1;
				}
				/*	宝石合成尚末开放

								if( num2 <= MAX_CARRY && item->is_diamond_3() && item2->is_diamond_2() )
								{
										ITEM_DIAMOND_D->make_diamond(me, item, item2);
										if( item ) send_user( me, "%c%d%c", 0x4e, getoid(item), item->get_amount() );    // 补发消息
										return 1;
								}
*/
				if (item2->is_combined() && get_file_name(item) == get_file_name(item2) && (item->get("special") == item2->get("special")) && item->get_no_give() == item2->get_no_give())
				{

					if ((amount2 = item2->get_amount()) < item2->get_max_combined())
					{
						amount = item->get_amount();
						if (amount + amount2 <= item2->get_max_combined())
						{
							item->set_amount(0);
							item2->set_amount(amount + amount2);
							return 1;
						}
						else
						{
							item->set_amount(amount + amount2 - item2->get_max_combined());
							item2->set_amount(item2->get_max_combined());
							return 1;
						}
					}
				}

				set_d(item2, num2);
			}
			set_d(item, num);
			send_user(me, "%c%c%c", 0x5c, num2, num);
		}
	}
	else if (flag == 3)
	{
		if ((num2 = get_d(item)) != num)
		{
			if (objectp(item2 = number_present(me, num, 0, 0)))
			{
				if (me->get_store(sprintf("%02d", get_d(item2))))
				{
					notify(item2->get_name() + "Muốn ngừng, không thể di chuyển.");
					send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
					return 1;
				}
				if (item->is_specal_move())
				{
					if (item->move_item2(me, item, item2))
						return 1;
				}
				if (item->get_item_type() == ITEM_TYPE_SHIKE)
				{
					if (item2->is_equip() && item2->get_equip_type() != HAND_TYPE)
					{
						if (item->get("mpp") > 0 && item2->get_equip_type() != BOOTS_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("hpp") > 0 && item2->get_equip_type() != WAIST_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("app") > 0 && item2->get_equip_type() != WEAPON_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("dpp") > 0 && item2->get_equip_type() != ARMOR_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("cpp") > 0 && item2->get_equip_type() != WEAPON_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("double2") > 0 && item2->get_equip_type() != WEAPON_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("ppp") > 0 && item2->get_equip_type() != HEAD_TYPE && item2->get_equip_type() != WAIST_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						item2->set("app", item->get("app"));
						item2->set("dpp", item->get("dpp"));
						item2->set("cpp", item->get("cpp"));
						item2->set("ppp", item->get("ppp"));
						item2->set("hpp", item->get("hpp"));
						item2->set("mpp", item->get("mpp"));
						item2->set("double2", item->get("double2"));
						send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
						item->remove_from_user();
						destruct(item);
						return 1;
					}
				}
				if (item->get_item_type() == ITEM_TYPE_DAKHAM)
				{
					if (item2->is_equip() && item2->get_equip_type() != HAND_TYPE)
					{

						if (item->get("hp3") > 0 && item2->get_equip_type() != WAIST_TYPE && item2->get_equip_type() != ARMOR_TYPE && item2->get_equip_type() != BOOTS_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("ap3") > 0 && item2->get_equip_type() != WEAPON_TYPE && item2->get_equip_type() != NECK_TYPE && item2->get_equip_type() != HEAD_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("dp3") > 0 && item2->get_equip_type() != ARMOR_TYPE && item2->get_equip_type() != WAIST_TYPE && item2->get_equip_type() != BOOTS_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("cp3") > 0 && item2->get_equip_type() != WEAPON_TYPE && item2->get_equip_type() != NECK_TYPE && item2->get_equip_type() != HEAD_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						if (item->get("pp3") > 0 && item2->get_equip_type() != BOOTS_TYPE && item2->get_equip_type() != WAIST_TYPE && item2->get_equip_type() != ARMOR_TYPE)
						{
							notify("Vật phẩm không phù hợp, không thể khảm nạm");
							return 1;
						}
						chi_so = ({"hp3", "ap3", "cp3", "dp3", "pp3"});
						for (i = 0; i < 5; i++)
							if (item2->get(chi_so[i]))
							{
								if (item->get_unit() != chi_so[i])
								{
									notify("Bạn chỉ có thể khảm cùng 1 loại!");
									return 1;
								}
							}
						if (!item2->get("duc_lo.1") && !item2->get("duc_lo.2") & !item2->get("duc_lo.3"))
						{
							notify("Bạn chưa đục lỗ cho trang bị này!");
						}
						else if (item2->get("duc_lo.1") && item2->get("duc_lo.1") == 1)
						{
							notify(sprintf("Bạn đã khảm %s vào %s ", item->get_name(), item2->get_name()));
							item2->add(item->get_unit(), item->get(item->get_unit()));
							item2->set("duc_lo.1", item->get(item->get_unit()));
							send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
							item->remove_from_user();
							destruct(item);
							return 1;
						}
						else if (item2->get("duc_lo.2") && item2->get("duc_lo.2") == 1)
						{
							notify(sprintf("Bạn đã khảm %s vào %s ", item->get_name(), item2->get_name()));
							item2->add(item->get_unit(), item->get(item->get_unit()));
							item2->set("duc_lo.2", item->get(item->get_unit()));
							send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
							item->remove_from_user();
							destruct(item);
							return 1;
						}
						else if (item2->get("duc_lo.3") && item2->get("duc_lo.3") == 1)
						{
							notify(sprintf("Bạn đã khảm %s vào %s ", item->get_name(), item2->get_name()));
							item2->add(item->get_unit(), item->get(item->get_unit()));
							item2->set("duc_lo.3", item->get(item->get_unit()));
							send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
							item->remove_from_user();
							destruct(item);
							return 1;
						}
						else
						{
							notify("Bạn đã khảm tối đa rồi!");
						}
					}
				}
				if (item->is_dachietxuat())
				{
					if (item2->is_dachietxuat())
					{
						amount = 0;
						amount2 = 0;

						chi_so = ({"ap", "cp", "dp", "pp", "hp", "sp", "!%", "double", "-*", "-c*", "?%",
								   "double",
								   "hp*",
								   "mp*",
								   "-*%",
								   "-c*%",
								   "t!%", "c!%"});
						for (i = 0; i < sizeof(chi_so); i++)
						{
							if (item->get(chi_so[i]) && item2->get(chi_so[i]))
							{
								notify("Không thể hợp thành chiết xuất cùng loại chỉ số");
								return 1;
							}
							if (item->get(chi_so[i]))
							{

								amount += 1;
							}
							if (item2->get(chi_so[i]))
							{

								amount2 += 1;
							}
						}
						if (amount > 1 || amount2 > 1)
						{
							notify("Mỗi chiết xuất chỉ được hợp thành 1 lần");
							return 1;
						}
						for (i = 0; i < sizeof(chi_so); i++)
						{
							if (item->get(chi_so[i]))
							{
								item2->set(chi_so[i], item->get(chi_so[i]));
								break;
							}
						}
						send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
						notify(sprintf("Bạn đã hợp thành %s vào %s ", item->get_name(), item2->get_name()));
						item->remove_from_user();
						destruct(item);

						return 1;
					}
					if (item2->is_equip() && item2->get_equip_type())
					{
						if (item2->get("chietxuat"))
						{
							notify("Mỗi trang bi chi duoc su dung chiet xuat 1 lan");
							return 1;
						}
						chi_so = ({"ap", "cp", "dp", "pp", "hp", "sp", "!%", "double", "-*", "-c*", "?%",
								   "double",
								   "hp*",
								   "mp*",
								   "-*%",
								   "-c*%",
								   "t!%", "c!%"});
						for (i = 0; i < sizeof(chi_so); i++)
						{
							if (item->get(chi_so[i]))
							{
								item2->add(chi_so[i], item->get(chi_so[i]));
							}
						}
						item2->set("chietxuat", 1);
						send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
						notify(sprintf("Bạn đã khảm %s vào %s ", item->get_name(), item2->get_name()));
						item->remove_from_user();
						destruct(item);

						return 1;
					}
				}

				if (item->is_food_huyenthu())
				{
					if (item2->is_huyenthu())
					{
						if (me->get("zombie2"))
						{
							notify("Vui lòng thu hồi Huyễn thú lại");
							return 1;
						}
						if (item2->get("lv") < 5)
						{
							if (item2->get_exp() >= item2->get_max_exp() || (item2->get_exp() + item->get("exp") >= item2->get_max_exp()))
							{
								item2->add_exp(item->get("exp"));
								item2->set("lv", (item2->get("lv") + 1));
								send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
								item->add_amount(-1);
								// destruct(item);
								//	USER_ENERGY_D->count_all_prop(item2);
								return 1;
							}
							else
							{
								item2->add_exp(item->get("exp"));
								//	item->remove_from_user();

								send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
								item->add_amount(-1);
								// destruct(item);
								//	USER_ENERGY_D->count_all_prop(item2);
								return 1;
							}
						}
						else
						{
							notify("Huyễn Thú đã đạt cấp độ tối đa");

							return 1;
						}
					}
				}

				if (item->is_aohoa_rm())
				{
					if (item2->is_nangcap() && item2->get_equip_type() == BACK_TYPE)
					{
						"cmd/std/mixaohoa"->xoa_aohoa(item2, me);
						item->remove_from_user();
						destruct(item);
						return 1;
					}
				}
				if (item->is_mirror())
				{
					if (item2->is_equip() && item2->get_hide() && item2->get_equip_type() != HAND_TYPE)
					{
						if (item2->get_level() > item->get("level2"))
						{
							notify("Giám định kính của ngươi không đủ cấp để giám định trang bị này");
							return 1;
						}
						d = get_d(item2);
						if (item2->get_item_color() == 0 || item2->get_item_color() == 4)
						{
							i = random(10000);
							if (i < 3)
								"/sys/item/equip"->init_equip_prop_3(item2);
							else if (i < 603)
								"/sys/item/equip"->init_equip_prop_1(item2);
							if (item2->get_item_color() != 0 && item2->get_item_color() != 4)
							{
								itemid = "/sys/sys/id"->add_max_itemid(1);
								item2->set_user_id(sprintf("#%d#", itemid));
								// log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item2->get_name(), "/sys/item/item"->get_pawn_save_string(item2)));
								legend = sprintf("鉴定升级 @%s %s,%d,%s,%s %s %s %d %s %d_%d_%d", item->get_name(), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item2->get_name(), "/sys/item/item"->get_pawn_save_string(item2), 1, item2->get_user_id(), get_z(me), get_x(me), get_y(me));
								//"/sys/user/cmd"->log_item(legend);
							}
						}
						item2->set_hide(0);
						item2->add_to_user(d);
						item->add_amount(-1);
						notify("Giám định hoàn tất.");
						return 1;
					}
				}
				if (item->is_repair() && item2->is_equip())
				{
					if (item->move_item2(me, item, item2))
						return 1;
				}
			}
		}
	}
	else
	{
		if (item->get_name() == "钱票")
		{
			notify("不能收起钱票.");
			send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
			return 1;
		}
		if (item->get_name() == "贵重物品")
		{
			notify("不能收起贵重物品.");
			send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
			return 1;
		}
		if (!(num == 1) && !(num == 2 && b > 0) && !(num == 3 && c > 0) && !(num == 4 && d > 0))
		{
			send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
			return 1;
		}

		if (num == (get_d(item) - 1) / MAX_CARRY + 1) // 同栏之中
		{
			send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
			return 1;
		}
		if (num == 2) // 包裹之内
		{
			begin = MAX_CARRY + 1;
			end = MAX_CARRY + b;
		}
		else if (num == 3) //
		{
			begin = MAX_CARRY * 2 + 1;
			end = MAX_CARRY * 2 + c;
		}
		else if (num == 4) // 乾坤袋之内
		{
			begin = MAX_CARRY * 3 + 1;
			end = MAX_CARRY * 3 + d;
		}
		else
		{
			begin = 1;
			end = MAX_CARRY;
		}
		if ((total = USER_INVENTORY_D->can_carry_2(me, item, begin, end)) < 1)
		{
			notify("对应物品栏已满.");
			send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
			return 1;
		}
		if (item->is_combined())
		{
			if (total > item->get_amount())
				total = item->get_amount();

			amount = USER_INVENTORY_D->carry_combined_item_2(me, item, total, begin, end);

			if (amount > 0 && item->set_amount(amount))
			{
				if (sizeof_inventory(me, begin, end) >= end - begin + 1)
				{
					notify("目标物品栏已满.");
					send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
					return 1;
				}

				for (i = 0, size = end - begin + 1; i < size; i++)
					if (!number_present(me, i + begin, begin, end))
						break; // 寻找空位

				if (i < size)
				{
					send_user(me, "%c%c%c", 0x5c, get_d(item), i + begin);
					set_d(item, i + begin);
				}
			}
			else
				item->add_amount(-total);
		}
		else
		{
			if (sizeof_inventory(me, begin, end) >= end - begin + 1)
			{
				notify("目标物品栏已满.");
				send_user(me, "%c%d%c", 0x4e, getoid(item), item->get_amount()); // 补发消息
				return 1;
			}

			for (i = 0, size = end - begin + 1; i < size; i++)
				if (!number_present(me, i + begin, begin, end))
					break; // 寻找空位

			if (i < size)
			{
				send_user(me, "%c%c%c", 0x5c, get_d(item), i + begin);
				set_d(item, i + begin);
			}
		}
	}

	return 1;
}

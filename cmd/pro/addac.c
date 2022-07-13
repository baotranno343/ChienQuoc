#include <item.h>
#include <equip.h>

// 函数：命令处理
int main(object me, string arg2)
{
	object *inv, item, who = me, char, pawn, item2;
	int i, size, type, total, index, count, value;
	string *ids = ({}), *key, name, file, id, prop, arg, prop2;
	string special;
	int amount, use, maxuse, locktime, lockutil;
	int point, point2, point3;
	mapping list;
	if (is_player(me))
	{
		notify("您没有足够的权限。");
		return 1;
	}
	if (!arg2)
		return 1;
	if (sscanf(arg2, "%s %d %d %s %d %s", arg, type, index, file, count, prop) != 6)
	{
		if (sscanf(arg2, "%s %d %d %s %d", arg, type, index, file, count) == 5)
		{
			prop = "";
		}
		else
			// 根据存档格式生成文件
			if (sscanf(arg2, "%s %d %d %s", arg, type, index, prop) == 4)
		{
			// 先要判断是当铺的存档还是身上的存档格式
			sscanf(prop, "%s;%*s", file);
			if (!sizeof(file) || !load_object(file))
			{
				send_user(me, "%c%s", '!', "存档文件格式不对。");
				return 1;
			}
			key = explode(prop, ";");
			switch (file->get_item_type())
			{
			case ITEM_TYPE_EQUIP:
				if (sizeof(key) == 7)
				{
					if (sscanf(prop, "%s;%d;%d;%d;%d;%s;[%s]%d,%d", file, amount, i, use, maxuse, prop2, id, locktime, lockutil) != 9)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;%d;%s;[%s]%d,%d", file, amount, use, maxuse, prop2, id, locktime, lockutil) != 8)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				item->set_max_lasting(maxuse);
				item->set_lasting(use);
				ITEM_EQUIP_D->set_prop_baseon_string(item, prop2);
				break;

			case ITEM_TYPE_TALISMAN:
				if (sizeof(key) == 7)
				{
					if (sscanf(prop, "%s;%d;%d;%d;%d;%d;[%s]%d,%d", file, amount, i, use, maxuse, point, id, locktime, lockutil) != 9)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;%d;%d;[%s]%d,%d", file, amount, use, maxuse, point, id, locktime, lockutil) != 8)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				item->set_max_lasting(maxuse);
				item->set_lasting(use);

				switch (item->get_talisman_type())
				{
				default:
					break;
				case 2:
					item->set_hp(point);
					break; // 九龙神火罩
				case 9:
					item->set_heart_sec(point);
					break; // 招魂幡
				}

				break;

			case ITEM_TYPE_POISON_2:
				if (sizeof(key) == 5)
				{
					if (sscanf(prop, "%s;%d;%d;%d;[%s]%d,%d", file, amount, i, point, id, locktime, lockutil) != 7)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", file, amount, point, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				item->set_poison(point);

				break;

			case ITEM_TYPE_GOOD:
				if (sizeof(key) == 5)
				{
					if (sscanf(prop, "%s;%d;%d;%d;[%s]%d,%d", file, amount, i, point, id, locktime, lockutil) != 7)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", file, amount, point, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				item->set_buyin(point);

				break;

			case ITEM_TYPE_CHEQUE2:
			case ITEM_TYPE_CHEQUE:
				if (sizeof(key) == 6)
				{
					if (sscanf(prop, "%s;%d;%d;%d;%d;[%s]%d,%d", file, amount, i, point, point2, id, locktime, lockutil) != 8)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;%d;[%s]%d,%d", file, amount, point, point2, id, locktime, lockutil) != 7)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				item->set_orgin_money(point);
				item->set_money(point2);

				break;

			case ITEM_TYPE_TREASURE:
				if (sizeof(key) == 7)
				{
					if (sscanf(prop, "%s;%d;%d;%d;%d;%d;[%s]%d,%d", file, amount, i, point, point2, point3, id, locktime, lockutil) != 9)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;%d;%d;[%s]%d,%d", file, amount, point, point2, point3, id, locktime, lockutil) != 8)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}

				item = new (file);
				if (amount)
					item->set_amount(amount);
				item->set_map_z(point);
				item->set_map_x(point2);
				item->set_map_y(point3);

				break;

			case ITEM_TYPE_DIAMOND_2:
				if (sizeof(key) == 5)
				{
					if (sscanf(prop, "%s;%d;%d;%d;[%s]%d,%d", file, amount, i, point, id, locktime, lockutil) != 7)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", file, amount, point, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				item->set_item_level(point);

				break;

			case ITEM_TYPE_POTENTIAL:
				if (sizeof(key) == 5)
				{
					if (sscanf(prop, "%s;%d;%d;%d;[%s]%d,%d", file, amount, i, point, id, locktime, lockutil) != 7)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", file, amount, point, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				item->set_potential(point);

				break;
			case ITEM_TYPE_SPECIAL:
				if (sizeof(key) == 5)
				{
					if (sscanf(prop, "%s;%d;%d;%s;[%s]%d,%d", file, amount, i, special, id, locktime, lockutil) != 7)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%s;[%s]%d,%d", file, amount, special, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				item->set("special", special);
				break;
			case ITEM_TYPE_KIMNGUYENBAO:
				if (sizeof(key) == 5)
				{
					if (sscanf(prop, "%s;%d;%d;%d;[%s]%d,%d", file, amount, i, point, id, locktime, lockutil) != 7)
					{
						send_user(me, "%c%s", '!', "Lưu trứ cách thức không đúng");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", file, amount, point, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "Lưu trứ cách thức không đúng");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				//  item->set_potential(point);
				"sys/sys/test_db"->set_yuanbao(item, point);

				break;
			case ITEM_TYPE_CHIENTICH:
				if (sizeof(key) == 5)
				{
					if (sscanf(prop, "%s;%d;%d;%d;[%s]%d,%d", file, amount, i, point, id, locktime, lockutil) != 7)
					{
						send_user(me, "%c%s", '!', "Lưu trứ cách thức không đúng");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", file, amount, point, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "Lưu trứ cách thức không đúng");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);
				//  item->set_potential(point);
				//	"sys/sys/test_db"->set_yuanbao(item,point);
				item->set_save_2("changping.score", point);

				break;
			case ITEM_TYPE_DIAMOND_3:
				if (sizeof(key) == 4)
				{
					if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", file, amount, i, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;%d;[%s]%d,%d", file, amount, i, i, id, locktime, lockutil) != 7)
					{
						if (sscanf(prop, "%s;%d;[%s]%d,%d", file, amount, id, locktime, lockutil) != 5)
						{
							send_user(me, "%c%s", '!', "存档文件格式不对。");
							return 1;
						}
					}
				}
				item = new (file);
				if (amount)
					item->set_level(amount);

				break;
			default:
				if (sizeof(key) == 4)
				{
					if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", file, amount, i, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;[%s]%d,%d", file, amount, id, locktime, lockutil) != 5)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				item = new (file);
				if (amount)
					item->set_amount(amount);

				break;
			case ITEM_TYPE_DIAMOND_100:
				if (sizeof(key) == 4)
				{
					if (sscanf(prop, "%s;%d;%d;[%s]%d,%d", file, amount, i, id, locktime, lockutil) != 6)
					{
						send_user(me, "%c%s", '!', "存档文件格式不对。");
						return 1;
					}
				}
				else
				{
					if (sscanf(prop, "%s;%d;%d;%d;[%s]%d,%d", file, amount, i, i, id, locktime, lockutil) != 7)
					{
						if (sscanf(prop, "%s;%d;[%s]%d,%d", file, amount, id, locktime, lockutil) != 5)
						{
							send_user(me, "%c%s", '!', "存档文件格式不对。");
							return 1;
						}
					}
				}
				item = new (file);
				if (amount)
					item->set_level(amount);

				break;
			}
			if (item)
				prop = "/sys/item/item"->get_prop_string(item);
		}
		else
		{
			send_user(me, "%c%s", '!', "格式不对");
			tell_user(me, "格式不对");
			return 1;
		}
	}
	if (!item)
	{
		ids = explode(prop, ";");
		if (type < 0)
			return 1;
		if (index < 0)
			return 1;
		// 生成道具
		item = new (file);
		if (!item)
		{
			tell_user(me, "无法生成这种道具");
			send_user(me, "%c%s", '!', "无法生成这种道具");
			return 1;
		}
		if (item->get_max_combined() && count > 0)
			item->set_amount(count);
		size = sizeof(ids);
		for (i = 0; i < size; i++)
		{
			sscanf(ids[i], "%s %d", name, value);
			item->set(name, value);
		}
	}
	if (!(who = find_player(arg)))
	{
		id = strlwr(arg);
		if (!user_exist(id))
		{
			send_user(me, "%c%s", '!', "这个用户并不存在！");
			notify("这个用户并不存在！");
			return 1;
		}

		who = new (USER);
		who->set_id(id);
		if (!who->restore())
		{
			send_user(me, "%c%s", '!', "这个用户并不存在！");
			destruct(who);
			destruct(item);
			return 1;
		}

		if (char = find_player(sprintf("%d", who->get_number())))
		{
			destruct(who);
			destruct(item);
			send_user(me, "%c%s", '!', "该用户处于在线状态！");
			return 1;
		}
	}
	else
	{
		destruct(item);
		send_user(me, "%c%s", '!', "该用户处于在线状态！");
		return 1;
	}
	if (type == 0) // 查询道具
	{
		who->restore_inventory();
		if (index >= HEAD_TYPE)
		{
			destruct(item);
			destruct(who);
			send_user(me, "%c%s", '!', "不能直接往装备栏添加道具。");
			tell_user(me, "不能直接往装备栏添加道具。");
			return 1;
		}
		else
		{
			item2 = number_present(who, index, 0, 0);
			if (item2)
			{
				destruct(item);
				destruct(who);
				send_user(me, "%c%s", '!', "这个位置已经有道具了。");
				tell_user(me, "这个位置已经有道具了。");
				return 1;
			}
			else
			{
				item->move(who, index);
				send_user(me, "%c%c%d%c%w%s", 0xac, 0, who->get_number(), index, item->get_amount(), item->get_name());
				log_file("gm/op.dat", sprintf("%s %s(%d) 增加 %s(%d) 装备 %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), "/sys/item/item"->get_prop_string(item)));
			}
		}
		who->save_inventory();
		who->save();
		who->before_destruct();
		destruct(who);
		return 1;
	}
	type--;
	pawn = new (PAWN);
	pawn->set_id(type);
	pawn->set_owner(who->get_id());
	list = pawn->get_pawn();
	if (!mapp(list))
		list = ([]);
	if (list[sprintf("%02d", index)])
	{
		destruct(pawn);
		destruct(who);
		destruct(item);
		send_user(me, "%c%s", '!', "当铺的这个位置已经有道具了。");
		tell_user(me, "当铺的这个位置已经有道具了。");
		return 1;
	}
	prop = "/sys/item/item"->get_pawn_save_string(item);
	send_user(me, "%c%c%d%c%c%w%s", 0xac, 5, who->get_number(), type + 1, index, item->get_amount(), item->get_name());
	pawn->set_pawn(sprintf("%02d", index), prop);
	log_file("gm/op.dat", sprintf("%s %s(%d) 增加 %s(%d) 当铺 %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), prop));
	pawn->save();
	destruct(pawn);
	destruct(who);
	return 1;
}

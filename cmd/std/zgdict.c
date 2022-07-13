/*-----------------------------------------------------------------------------------*\
	摇奖查询等命令：目前主要用于配合《Chiến Quốc Bảo Điển》设定
	由 cjxx 于2007-09-04 创建
\*-----------------------------------------------------------------------------------*/
#include <ansi.h>

#define ZG_DICTIONARY "/quest/zg_dict"
#define _DEBUG(str) ; //if(objectp(find_char("1"))) {tell_user(find_char("1"),str);}

void zgdict_rock_item(object player);

int main(object me, string arg)
{
	int cmd_size, id, i, type, locate, level, color, total;
	string *cmds, result;
	object item, *allitem;
	if (!arg || arg == "")
	{
		return 0;
	}
	cmds = explode(arg, " ");
	cmd_size = sizeof(cmds);
	switch (cmds[0])
	{
	case "open":
		if (!objectp(item = present("Chiến Quốc Bảo Điển", me, 1, MAX_CARRY * 4)))
		{
			return 0;
		}
		ZG_DICTIONARY->search_in_user(me);
		break;
	case "lv":
		if (!objectp(item = present("Chiến Quốc Bảo Điển", me, 1, MAX_CARRY * 4)))
		{
			return 0;
		}
		if (cmd_size == 2)
		{
			ZG_DICTIONARY->search_in_level(me, to_int(cmds[1]));
		}
		break;
	case "rock":
		if (!objectp(item = present("Chiến Quốc Bảo Điển", me, 1, MAX_CARRY * 4)))
		{
			_DEBUG("没有战国宝典");
			return 0;
		}
		if (cmd_size >= 2 && ZG_DICTIONARY->if_allow_prize(me))
		{
			allitem = me->get_2("zgdict.item");
			switch (cmds[1])
			{
			case "open":
				if (me->get_2("zgdict.status") == 1)
				{
					return 0;
				}
				if (me->get_level() > 10)
				{
					send_user(me, "%c%s", '!', "Đẳng cấp của bạn quá cao không thể nhận được nữa.");
					return 0;
				}
				if (allitem)
				{
					_DEBUG("残留物品存在，重新发送");
					if (sizeof(allitem) == 8)
					{
						send_user(me, "%c%c", 0xa6, 7);
						for (i = 0; i < 8; i++)
						{
							if (item = allitem[i])
							{
								_DEBUG(sprintf("%s", item->get_name()));
								type = item->get_item_type_2();
								locate = item->get_equip_type();
								if (locate > 100)
								{
									locate -= 100;
								}
								if (item->get_level() > 0)
								{
									level = item->get_level();
								}
								else
								{
									level = item->get("level");
								}
								color = item->get_item_color();
								send_user(me, "%c%c%c%d%w%w%c%c%c%c%s", 0xa6, 2, i + 1, getoid(item),
										  item->get_picid_2(), item->get_amount(), type,
										  color, level, locate, item->get_name());
								result = ITEM_ITEM_D->get_look_string(me, item);
								send_user(me, "%c%c%d%s", 0xa6, 3, getoid(item), result);
							}
						}
						send_user(me, "%c%c", 0xa6, 0);
					}
					return 0;
				}
				_DEBUG("生成新物品");
				if (me->get_online_rate() < 100)
				{
					send_user(me, "%c%s", ';', "非健康时间不能进行摇奖！");
					return 0;
				}
				if (USER_INVENTORY_D->count_empty_carry(me) < 3)
				{
					send_user(me, "%c%s", '!', "空间不够，请确认有至少3格空间来放置奖品。");
					return 0;
				}
				allitem = ZG_DICTIONARY->get_rock_item(me);
				if (!allitem || sizeof(allitem) != 8)
				{
					_DEBUG("没有生成物品");
					return 0;
				}
				me->set_2("zgdict.item", allitem);
				send_user(me, "%c%c", 0xa6, 7);
				for (i = 0; i < 8; i++)
				{
					if (item = allitem[i])
					{
						type = item->get_item_type_2();
						locate = item->get_equip_type();
						if (locate > 100)
						{
							locate -= 100;
						}
						if (item->get_level() > 0)
						{
							level = item->get_level();
						}
						else
						{
							level = item->get("level");
						}
						color = item->get_item_color();
						send_user(me, "%c%c%c%d%w%w%c%c%c%c%s", 0xa6, 2, i + 1, getoid(item),
								  item->get_picid_2(), item->get_amount(), type,
								  color, level, locate, item->get_name());
						result = ITEM_ITEM_D->get_look_string(me, item);
						send_user(me, "%c%c%d%s", 0xa6, 3, getoid(item), result);
					}
				}
				me->set_2("zgdict.status", 0);
				break;
			case "start":
				if (!allitem || sizeof(allitem) != 8 || me->get_2("zgdict.status") != 0)
				{
					return 0;
				}
				if (USER_INVENTORY_D->count_empty_carry(me) < 3)
				{
					send_user(me, "%c%s", '!', "空间不够，请确认有至少3格空间来放置奖品。");
					return 0;
				}
				if (me->get_level() > 10)
				{
					send_user(me, "%c%s", '!', "Đẳng cấp của bạn quá cao không thể nhận được nữa.");
					return 0;
				}
				me->set_2("zgdict.status", 1);
				call_out("zgdict_rock_item", 7, me);
				send_user(me, "%c%c", 0xa6, 4);
				break;
			case "?":
				if (!allitem || sizeof(allitem) != 8 || cmd_size < 3)
				{
					return 0;
				}
				item = 0;
				sscanf(cmds[2], "%x#", id);
				for (i = 0; i < 8; i++)
				{
					if (getoid(allitem[i]) == id)
					{
						item = allitem[i];
						break;
					}
				}
				if (!item)
					return 1;
				result = ITEM_ITEM_D->get_look_string(me, item);
				send_user(me, "%c%c%d%s", 0xa6, 3, getoid(item), result);
				break;
			}
		}
		break;
	}
	return 1;
}
//	提示玩家恭喜得到相关物品的信息，可以通过延迟函数调用
void send_gala_message(object player, string item_name)
{
	if (objectp(player) && item_name)
	{
		send_user(player, "%c%s", ';', sprintf("Chúc mừng bạn nhận được" HIR " %s " NOR "!", item_name));
	}
}

//	玩家得到奖品的相关操作
void zgdict_rock_item(object player)
{
	int rand, i, total, amount, count, p, size;
	string item_info, user_get_item = "";
	object item, *items, *allitem;
	if (!objectp(player))
	{
		return;
	}
	_DEBUG("开奖");
	allitem = player->get_2("zgdict.item");
	if (!allitem || sizeof(allitem) != 8)
	{
		return;
	}
	item_info = ZG_DICTIONARY->get_sell_item(player);
	items = ZG_DICTIONARY->deal_with_item_info(item_info);
	size = sizeof(items);
	for (i = 0; i < size; i++)
	{
		if (objectp(items[i]))
		{
			if (items[i]->is_cash())
			{
				player->add_cash(items[i]->get_value());
				destruct(items[i]);
			}
			else
			{
				items[i]->set("winner", player);
				items[i]->set("time", time());
				items[i]->set_no_give(1);
				items[i]->set_no_sell(1);
				if ((total = USER_INVENTORY_D->can_carry(player, items[i])) < 1)
				{
					send_user(player, "%c%s", '!', "您身上没有空位！");
					user_get_item += sprintf(HIR "%s" NOR " ", items[i]->get_name());
					p = get_valid_xy(get_z(player), get_x(player), get_y(player), IS_ITEM_BLOCK);
					item->set_user_id(player->get_id());
					item->add_to_scene(get_z(player), p / 1000, p % 1000);
				}
				else
				{
					user_get_item += sprintf(HIR "%s" NOR " ", items[i]->get_name());
					p = items[i]->move(player, -1);
					items[i]->add_to_user(p);
				}
			}
		}
	}
	rand = random(100000);
	if (rand < 10)
	{
		rand = 0; //	A级物品
	}
	else if (rand < 7010)
	{
		rand = random(2) + 1; //	B级物品
	}
	else
	{
		rand = random(5) + 3; //	C级物品
	}
	item = allitem[rand];
	send_user(player, "%c%c%c", 0xa6, 5, rand + 1);
	if (item->is_cash())
	{
		i = item->get_value();
		player->add_cash(i);
		user_get_item += sprintf(HIR " %d " NOR "lượng ", i);
		call_out("send_gala_message", 1, player, user_get_item);
		for (i = 0; i < sizeof(allitem); i++)
		{
			destruct(allitem[i]);
		}
		player->delete_2("zgdict");
		ZG_DICTIONARY->player_can_get_prize(player, 0);
		send_user(player, "%c%c", 0xa6, 0);
		return;
	}
	if ((total = USER_INVENTORY_D->can_carry(player, item)) < 1)
	{
		send_user(player, "%c%s", '!', "您身上没有空位！");
		user_get_item += sprintf(HIR "%s" NOR, item->get_name());
		call_out("send_gala_message", 1, player, user_get_item);
		p = get_valid_xy(get_z(player), get_x(player), get_y(player), IS_ITEM_BLOCK);
		item->set_user_id(player->get_id());
		item->add_to_scene(get_z(player), p / 1000, p % 1000);
		item->set("winner", player);
		item->set("time", time());
		allitem -= ({item});
		for (i = 0; i < sizeof(allitem); i++)
		{
			destruct(allitem[i]);
		}
		player->delete_2("zgdict");
		ZG_DICTIONARY->player_can_get_prize(player, 0);
		send_user(player, "%c%c", 0xa6, 0);
		return;
	}
	allitem -= ({item});
	count = item->get_amount();
	user_get_item += sprintf(HIR "%s" NOR, item->get_name());
	if (item->get_max_combined() > 1)
	{
		total = count;
		amount = USER_INVENTORY_D->carry_combined_item(player, item, total);
		if (amount > 0 && item->set_amount(amount))
		{
			if (p = item->move(player, -1))
			{
				item->add_to_user(p);
			}
		}
		else
		{
			item->add_amount(-total);
		}
	}
	else
	{
		if (p = item->move(player, -1))
		{
			item->add_to_user(p);
		}
	}
	if (user_get_item && user_get_item != "")
	{
		call_out("send_gala_message", 1, player, user_get_item);
	}
	for (i = 0; i < sizeof(allitem); i++)
	{
		destruct(allitem[i]);
	}
	player->delete_2("zgdict");
	ZG_DICTIONARY->player_can_get_prize(player, 0);
	send_user(player, "%c%c", 0xa6, 0);
}
//	退出前执行函数
void before_quit(object me)
{
	object *allitem;
	int i;
	allitem = me->get_2("zgdict.item");
	if (!allitem)
		return;
	for (i = 0; i < sizeof(allitem); i++)
	{
		if (objectp(allitem[i]))
		{
			destruct(allitem[i]);
		}
	}
	me->delete_2("zgdict");
}
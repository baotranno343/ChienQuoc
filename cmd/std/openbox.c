
#include <ansi.h>
#include <equip.h>

#define PLUNDER_PROTECT_TIME 120 // 战利品保护时间

int open_box(object me);

// 函数：命令处理
int main(object me, string arg)
{
	object *allitem, item, item2, item3;
	string *args, result;
	int rand, id, i, p;
	int type, locate, level, color;
	allitem = me->get_2("openbox.item");
	if (!arg)
	{
		if (!allitem)
			return 1;
		if (sizeof(allitem) != 8)
			return 1;
		if (me->get_2("openbox.status") != 0)
			return 1;
		me->set_2("openbox.status", 1);
		call_out("open_box", 7, me);
		send_user(me, "%c%c", 0x91, 4);
		return 1;
	}
	args = explode(arg, " ");
	if (sizeof(args) != 2)
		return 1;
	if (args[0] == "?")
	{
		if (!allitem)
			return 1;
		if (sizeof(allitem) != 8)
			return 1;
		sscanf(args[1], "%x#", id);
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
		send_user(me, "%c%c%d%s", 0x91, 3, getoid(item), result);
		return 1;
	}
	if (!objectp(item = present(args[0], me, 1, MAX_CARRY * 4)))
		return 1;
	if (!objectp(item2 = present(args[1], me, 1, MAX_CARRY * 4)))
		return 1;
	if (!item->is_key())
		return 1;
	if (!item2->is_box())
		return 1;
	if (me->get_online_rate() < 100)
	{
		send_user(me, "%c%s", ';', "非健康时间不能打开宝箱！");
		return 0;
	}
	if (item->get_level() != item2->get_level())
	{
		send_user(me, "%c%s", '!', "Bảo Hộp và Chìa Khoá không hợp nhau");
		return 1;
	}
	allitem = "/quest/box"->get_item(item2->get_level());
	if (!allitem)
		return 1;
	if (sizeof(allitem) != 8)
		return 1;
	me->set_2("openbox.item", allitem);
	if (item->is_record())
	{
		result = sprintf("打开宝箱 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
		//"/sys/user/cmd"->log_item(result);
	}
	if (item->get_level() == 4 || item->get_level() == 5)
	{
		item->add_amount(-1);
	}
	else
	{
		item->remove_from_user();
		destruct(item);
	}
	if (item2->is_record())
	{
		result = sprintf("打开宝箱 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item2->get_name(), "/sys/item/item"->get_pawn_save_string(item2), 1, item2->get_user_id(), get_z(me), get_x(me), get_y(me));
		//"/sys/user/cmd"->log_item(result);
	}

	if (item2->get_level() == 4 || item2->get_level() == 5)
	{
		//	item3 = new("/item/01/0203");
		//	p = item3->move2(me,-1);
		//	item3->add_to_user(p);

		//	item2->remove_from_user();
		//	destruct(item2);
	}
	else
	{
		item2->remove_from_user();
		destruct(item2);
	}
	for (i = 0; i < 8; i++)
		if (item = allitem[i])
		{
			type = item->get_item_type_2();
			locate = item->get_equip_type();
			if (locate > 100)
				locate -= 100;
			if (item->get_level() > 0)
				level = item->get_level();
			else
				level = item->get("level");
			color = item->get_item_color();
			send_user(me, "%c%c%c%d%w%w%c%c%c%c%s", 0x91, 2, i + 1, getoid(item),
					  item->get_picid_2(), item->get_amount(), type,
					  color, level, locate, item->get_name());
			result = ITEM_ITEM_D->get_look_string(me, item);
			send_user(me, "%c%c%d%s", 0x91, 3, getoid(item), result);
		}
	return 1;
}

int open_box(object me)
{
	object *allitem, item;
	int rand, total, amount, i, count, p;
	allitem = me->get_2("openbox.item");
	if (!allitem)
		return 1;
	if (sizeof(allitem) != 8)
		return 1;
	rand = random(100);
	if (rand < 5)
		rand = 0;
	else if (rand < 10)
		rand = 1;
	else if (rand < 15)
		rand = 2;
	else
		rand = rand % 5 + 3;
	if (is_god(me))
	{
		if (me->get("lb") > 0)
			rand = me->get("lb") - 1;
		if (rand > 8)
			rand = 7;
	}
	item = allitem[rand];
	send_user(me, "%c%c%c", 0x91, 5, rand + 1);
	if (item->is_cash())
	{
		i = item->get_value();
		me->add_cash(i);
		call_out("message_box", 1, me, 1, sprintf(" %d lượng", i));
		for (i = 0; i < sizeof(allitem); i++)
			destruct(allitem[i]);
		me->delete_2("openbox");
		return;
	}
	if ((total = USER_INVENTORY_D->can_carry_3(me, item)) < 1)
	{
		send_user(me, "%c%s", '!', "Hành trang không đủ 1 chỗ trống");
		p = get_valid_xy(get_z(me), get_x(me), get_y(me), IS_ITEM_BLOCK);
		item->set_user_id(me->get_id());
		item->add_to_scene(get_z(me), p / 1000, p % 1000);
		item->set("winner", me);
		item->set("time", time());
		allitem -= ({item});
		for (i = 0; i < sizeof(allitem); i++)
			destruct(allitem[i]);
		me->delete_2("openbox");
		return;
	}
	//	send_user(me, "%c%s", ';', sprintf("恭喜您获得了%s.", item->get_name()));
	if (rand <= 2)
		call_out("message_box", 1, me, 2, item->get_name());
	else
		call_out("message_box", 1, me, 1, item->get_name());
	//	if (rand<=2) USER_D->user_channel( sprintf("恭喜%s玩家开启宝箱获得了%s的奖励，让我们对其表示祝贺！", me->get_name(), item->get_name()));
	allitem -= ({item});
	count = item->get_amount();
	if (item->get_max_combined() > 1)
	{
		total = count;
		amount = USER_INVENTORY_D->carry_combined_item(me, item, total);
		if (amount > 0 && item->set_amount(amount))
		{
			if (p = item->move2(me))
			{
				item->add_to_user(p);
			}
		}
		else
			item->add_amount(-total);
	}
	else
	{
		if (p = item->move2(me))
		{
			item->add_to_user(p);
		}
	}
	for (i = 0; i < sizeof(allitem); i++)
		destruct(allitem[i]);
	me->delete_2("openbox");
}

int message_box(object me, int type, string name)
{
	send_user(me, "%c%s", ';', sprintf("Bạn nhận được" HIY " %s " NOR ".", name));
	if (type == 2)
		USER_D->user_channel(sprintf("Chúc mừng người chơi %s mở Bảo Hộp nhận được" HIR " %s " NOR ", thật là may mắn !", me->get_name(), name));
}

void before_quit(object me)
{
	object *allitem, item;
	int i;
	allitem = me->get_2("openbox.item");
	if (!allitem)
		return;
	for (i = 0; i < sizeof(allitem); i++)
		destruct(allitem[i]);
	me->delete_2("openbox");
}
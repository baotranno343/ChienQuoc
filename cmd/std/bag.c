#include <ansi.h>
#include <equip.h>
#include <effect.h>
#include <skill.h>

int use_bag(object me, object item, int type);

// 函数：命令处理
int main(object me, string arg)
{
	object item;
	int num;
	if (!arg)
		return 1;
	if (sscanf(arg, "%s %d", arg, num) != 2)
		return 1;
	if (!objectp(item = present(arg, me, 0, 0)))
		return 1;
	return use_bag(me, item, num);
}

int use_bag(object me, object item, int type)
{
	int bag, b, c, d, level, date, lasting;
	string cmd1, cmd2, cmd3, result;
	if (!item->if_in_user(me))
		return 1;
	bag = me->have_bag();
	b = bag % 100;
	c = (bag / 100) % 100;
	d = bag / 10000;
	level = item->get("bag");
	lasting = item->get("lasting");
	if (level == 0)
		return 1;
	if (item->get_fin_type() > 1700)
		date = 10;
	else
		date = 30;
	if (type == 1)
	{
		if (b == 0)
		{
			b = level;
			if (lasting == 0)
				me->set_bag1_time(time() + date * 24 * 3600);
			else
				me->set_bag1_time(-1);
			USER_INVENTORY_D->send_carry_desc(me, 0);
		}
		else if (c == 0)
		{
			send_user(me, "%c%c%w%s", ':', 3, 0, "Không thể mở balo thứ 3");
			return 1;
			c = level;
			if (lasting == 0)
				me->set_bag2_time(time() + date * 24 * 3600);
			else
				me->set_bag2_time(-1);
			USER_INVENTORY_D->send_carry_desc(me, 1);
		}
		else if (d == 0)
		{
			d = level;
			if (lasting == 0)
				me->set_bag3_time(time() + date * 24 * 3600);
			else
				me->set_bag3_time(-1);
			USER_INVENTORY_D->send_carry_desc(me, 2);
		}
		else
		{
			send_user(me, "%c%c%w%s", ':', 3, 0, "Ngươi không thể thêm ba lô mới");
			return 1;
		}
		bag = d * 10000 + c * 100 + b;
		me->set_have_bag(bag);
		USER_INVENTORY_D->send_max_carry_flag(me);
		item->remove_from_user();
		destruct(item);
		return 1;
	}
	if (type == 2)
	{
		result = "Bạn muốn đổi Ba lô phải không ?\n";
		if ((b == level) && me->get_bag1_time() > 0 && ((me->get_bag1_time() - time()) / (24 * 3600) < 330))
			result += sprintf(ESC "Đổi ba lô thứ 2\nbag %x# 21\n", getoid(item));
		if ((c == level) && me->get_bag2_time() > 0 && ((me->get_bag2_time() - time()) / (24 * 3600) < 330))
			result += sprintf(ESC "Đổi ba lô thứ 3\nbag %x# 22\n", getoid(item));
		if ((d == level) && me->get_bag3_time() > 0 && ((me->get_bag3_time() - time()) / (24 * 3600) < 330))
			result += sprintf(ESC "Đổi ba lô thứ 4\nbag %x# 23\n", getoid(item));
		result += ESC "Phản hồi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		return 1;
	}
	if (type == 3)
	{
		result = sprintf("Ngươi muốn sử dụng %s để tăng thêm ba lô mới không?\n", item->get_name());
		if (b > 0 && b != level)
			result += sprintf(ESC "Mở thêm ba lô thứ 2\nbag %x# 31\n", getoid(item));
		if (c > 0 && c != level)
			result += sprintf(ESC "Mở thêm ba lô thứ 3\nbag %x# 32\n", getoid(item));
		if (d > 0 && d != level)
			result += sprintf(ESC "Mở thêm ba lô thứ 4\nbag %x# 33\n", getoid(item));
		result += ESC "Phản hồi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		return 1;
	}
	if (type >= 21 && type <= 23)
	{
		switch (type)
		{
		case 21:
			if (b == level && me->get_bag1_time() > 0 && (me->get_bag1_time() - time()) / (24 * 3600) < 330)
			{
				if (time() > me->get_bag1_time())
					me->set_bag1_time(time() + date * 24 * 3600);
				else
					me->set_bag1_time(me->get_bag1_time() + date * 24 * 3600);
				USER_INVENTORY_D->send_carry_desc(me, 0);
			}
			break;
		case 22:
			if (c == level && me->get_bag2_time() > 0 && (me->get_bag2_time() - time()) / (24 * 3600) < 330)
			{
				if (time() > me->get_bag2_time())
					me->set_bag2_time(time() + date * 24 * 3600);
				else
					me->set_bag2_time(me->get_bag2_time() + date * 24 * 3600);
				USER_INVENTORY_D->send_carry_desc(me, 1);
			}
			break;
		case 23:
			if (d == level && me->get_bag3_time() > 0 && (me->get_bag3_time() - time()) / (24 * 3600) < 330)
			{
				if (time() > me->get_bag3_time())
					me->set_bag3_time(time() + date * 24 * 3600);
				else
					me->set_bag3_time(me->get_bag3_time() + date * 24 * 3600);
				USER_INVENTORY_D->send_carry_desc(me, 2);
			}
			break;
		}
		USER_INVENTORY_D->send_max_carry_flag(me);
		item->remove_from_user();
		destruct(item);
		return 1;
	}
	if (type >= 31 && type <= 33)
	{
		switch (type)
		{
		case 31:
			if (b > 0)
			{
				b = level;
				if (lasting == 0)
					me->set_bag1_time(time() + date * 24 * 3600);
				else
					me->set_bag1_time(-1);
				USER_INVENTORY_D->send_carry_desc(me, 0);
			}
			break;
		case 32:
			if (c > 0)
			{
				c = level;
				if (lasting == 0)
					me->set_bag2_time(time() + date * 24 * 3600);
				else
					me->set_bag2_time(-1);
				USER_INVENTORY_D->send_carry_desc(me, 1);
			}
			break;
		case 33:
			if (d > 0)
			{
				d = level;
				if (lasting == 0)
					me->set_bag3_time(time() + date * 24 * 3600);
				else
					me->set_bag3_time(-1);
				USER_INVENTORY_D->send_carry_desc(me, 2);
			}
			break;
		}
		bag = d * 10000 + c * 100 + b;
		me->set_have_bag(bag);
		USER_INVENTORY_D->send_max_carry_flag(me);
		item->remove_from_user();
		destruct(item);
		return 1;
	}
	return 1;
}

int get_use_effect(object me, object item)
{
	string cmd1, cmd2, cmd3, result;
	int b, c, d, bag, i, time;
	result = "";
	if (item->get("lasting") > 0)
	{
		bag = me->have_bag();
		b = bag % 100;
		c = (bag / 100) % 100;
		d = bag / 10000;
		if (b == 0 || c == 0 || d == 0)
		{
			cmd1 = sprintf("bag %x# 1\n", getoid(item));
			result = sprintf("Ngươi muốn sử dụng %s để mở thêm ba lô vĩnh viễn không?\n", item->get_name());
			cmd1 = sprintf("bag %x# 1\n", getoid(item));
			result += ESC "Mở ba lô mới\n" + cmd1;
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				switch (i)
				{
				case 0:
					time = me->get_bag1_time();
					cmd1 = "Hai";
					break;
				case 1:
					time = me->get_bag2_time();
					cmd1 = "Ba";
					break;
				default:
					time = me->get_bag3_time();
					cmd1 = "Bốn";
					break;
				}
				if (time < 0)
					continue;
				if (time() > time)
					cmd2 = "Hết hạn sử dụng";
				else if (time - time() > 24 * 3600)
					cmd2 = sprintf("Kì hạn sử dụng còn %d ngày", (time - time()) / (24 * 3600));
				else
					cmd2 = sprintf("Kì hạn sử dụng còn %d giờ", (time - time()) / 3600);
				result += sprintf(ESC "Thay thế %s ba lô %s\nbag %x# %d\n", cmd1, cmd2, getoid(item), 31 + i);
			}
			if (result == "")
				result = "Ba lô của bạn không thể mở rộng nữa\n";
			else
				result = sprintf("Bạn phải sử dụng %s thay vào ba lô nào ?\n%s", item->get_name(), result);
		}
		result += ESC "Phản hồi\nCLOSE\n";
		send_user(me, "%c%c%w%s", ':', 3, 0, result);
		return 0;
	}
	cmd1 = sprintf("bag %x# 1\n", getoid(item));
	cmd2 = sprintf("bag %x# 2\n", getoid(item));
	cmd3 = sprintf("bag %x# 3\n", getoid(item));
	result = sprintf("Bạn muốn sử dụng %s ở đâu?\n", item->get_name());
	result += ESC "Mở ra không gian ba lô mới \n" + cmd1 +
			  ESC "Đổi ba lô cũ\n" + cmd2 +
			  ESC "Thay ba lô vốn có\n" + cmd3 +
			  ESC "Phản hồi\nCLOSE\n";
	send_user(me, "%c%c%w%s", ':', 3, 0, result);
	return 0;
}
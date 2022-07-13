
#include <equip.h>

#define CLONE_LOG "gm/clone.txt" // Phục chế物品日志

// 函数：命令处理
int main(object me, string arg)
{
	object obj, obj1;
	string file, err, *nTmp;
	int z, x0, y0, x1, y1, p, count, i, size;
	int amount, total;
	if (is_player(me))
	{
		notify("Ngươi không đủ quyền hạn");
		return 1;
	}

	if (!arg)
		arg = me->get_cwf();
	nTmp = explode(arg, " ");
	arg = nTmp[0];
	if (sizeof(nTmp) > 1)
		count = to_int(nTmp[1]);
	else
		count = 1;
	file = absolute_path(me, arg);
	if (sscanf(file, "%*s.c") != 1)
		file += ".c";

	if (!file_exist(file))
	{
		notify("Không thể tìm thấy cái này");
		return 1;
	}

	me->set_cwf(file); // 设置当前文件

	if (!(obj = find_any_object(file)) && (err = catch (call_other(file, "???")))) // 载入指定文件
	{
		tell_user(me, "Tái nhập thất bại: " + err);
		return 1;
	}
	if (err = catch (obj = new (get_file_name(obj)))) // Phục chế指定物体
	{
		tell_user(me, "Phục chế thất bại: " + err);
		return 1;
	}

	log_file(CLONE_LOG, sprintf("%s %s(%s) Phục chế %s %s\n",
								short_time(), me->get_name(), me->get_id(), obj->get_name(), file)); // 记录日志文件

	// 只见$N伸手凌空一指，变出了$n。

	z = get_z(me);
	x0 = get_x(me);
	y0 = get_y(me);

	if (obj->is_char() && !obj->is_user())
	{
		for (i = 0; i < count; i++)
			if (p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK))
			{
				obj1 = new (get_file_name(obj));
				x1 = p / 1000;
				y1 = p % 1000;
				obj1->add_to_scene(z, x1, y1);
			}
		tell_user(me, obj->get_name() + " đã phục chế bên nhân vật");
		destruct(obj);
		return 1;
	}
	else if (obj->is_item())
	{
		if (USER_INVENTORY_D->can_carry(me, obj) < 1)
		{
			if (p = get_valid_xy(z, x0, y0, IS_ITEM_BLOCK))
			{
				x1 = p / 1000;
				y1 = p % 1000;
				obj->add_to_scene(z, x1, y1);
				if (count > 0 && obj->is_combined())
					obj->set_amount(count);
				me->to_front_xy(x1, y1);
				tell_user(me, obj->get_name() + " đã phục chế bên nhân vật");
				return 1;
			}
		}
		else
		{
			tell_user(me, obj->get_name() + " đã phục chế vào người");
			if (obj->get_max_combined() > 1)
			{
				if (count > 0)
					total = count;
				else
					total = 1;
				amount = USER_INVENTORY_D->carry_combined_item(me, obj, total);
				if (amount > 0 && obj->set_amount(amount))
				{
					if (p = obj->move(me, -1))
					{
						obj->add_to_user(p);
					}
				}
				else
					obj->add_amount(-total);
			}
			else
			{
				if (p = obj->move(me, -1))
				{
					obj->add_to_user(p);
				}
			}
			return 1;
		}
	}

	destruct(obj);
	notify("Không thể Phục chế vật thể này.");

	return 1;
}


#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main(object me, string arg)
{
	object who, obj, obj1;
	string file, err, *nTmp, arg2, arg3;
	int z, x0, y0, x1, y1, p, count, i, size;
	int amount, total;
	if (is_player(me))
	{
		notify("Ngươi không đủ quyền hạn");
		return 1;
	}
	if (arg == 0)
		return 1;
	if (!arg)
		return 1;
	if (sscanf(arg, "%s %s", arg2, arg3) == 2)
	{
		if (arg2 && !(who = find_any_char(arg2)))
		{
			notify("Không tìm thấy người này");
			return 1;
		}
		if (!arg3)
			arg3 = me->get_cwf();
		nTmp = explode(arg3, " ");
		arg3 = nTmp[0];
		if (sizeof(nTmp) > 1)
			count = to_int(nTmp[1]);
		else
			count = 1;
		file = absolute_path(me, arg3);
		if (sscanf(file, "%*s.c") != 1)
			file += ".c";

		if (!file_exist(file))
		{
			notify("Không thể tìm thấy cái này");
			return 1;
		}

		me->set_cwf(file);

		if (!(obj = find_any_object(file)) && (err = catch (call_other(file, "???"))))
		{
			tell_user(me, "Tái nhập thất bại: " + err);
			return 1;
		}
		if (err = catch (obj = new (get_file_name(obj))))
		{
			tell_user(me, "Phục chế thất bại: " + err);
			return 1;
		}

		log_file("cloneben.txt", sprintf("%s : %s (%d) đã clone %s ( %s ) cho người chơi %s có số id %d\n",
										 short_time(time()), me->get_name(), me->get_number(), obj->get_name(), file, who->get_name(), who->get_number()));

		z = get_z(who);
		x0 = get_x(who);
		y0 = get_y(who);

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
			tell_user(me, obj->get_name() + " đã phục chế bên nhân vật của " + who->get_name() + " (" + who->get_number() + ")");
			tell_user(who, obj->get_name() + " đã phục chế bên nhân vật");
			destruct(obj);
			return 1;
		}
		else if (obj->is_item())
		{
			if (USER_INVENTORY_D->can_carry(who, obj) < 1)
			{
				if (p = get_valid_xy(z, x0, y0, IS_ITEM_BLOCK))
				{
					x1 = p / 1000;
					y1 = p % 1000;
					obj->add_to_scene(z, x1, y1);
					if (count > 0 && obj->is_combined())
						obj->set_amount(count);
					who->to_front_xy(x1, y1);
					tell_user(me, obj->get_name() + " đã phục chế bên nhân vật của " + who->get_name() + " (" + who->get_number() + ")");
					tell_user(who, obj->get_name() + " đã phục chế bên nhân vật");
					return 1;
				}
			}
			else
			{
				tell_user(me, obj->get_name() + " đã phục chế vào người của " + who->get_name() + " (" + who->get_number() + ")");
				tell_user(who, obj->get_name() + " đã phục chế vào người");
				if (obj->get_max_combined() > 1)
				{
					if (count > 0)
						total = count;
					else
						total = 1;
					amount = USER_INVENTORY_D->carry_combined_item(who, obj, total);
					if (amount > 0 && obj->set_amount(amount))
					{
						if (p = obj->move(who, -1))
						{
							obj->add_to_user(p);
						}
					}
					else
						obj->add_amount(-total);
				}
				else
				{
					if (p = obj->move(who, -1))
					{
						obj->add_to_user(p);
					}
				}
				return 1;
			}
		}

		destruct(obj);
		notify("Không thể Phục chế vật thể này.");
	}
	return 1;
}
int clone_web(string arg)
{
	object who, obj, obj1;
	string file, err, *nTmp, arg2, arg3;
	int z, x0, y0, x1, y1, p, count, i, size;
	int amount, total;
	if (arg == 0)
		return 1;
	if (!arg)
		return 1;
	if (sscanf(arg, "%s %s", arg2, arg3) == 2)
	{
		if (arg2 && !(who = find_any_char(arg2)))
		{
			notify("Không tìm thấy người này");
			return 1;
		}
		if (!arg3)
			return 1;
		nTmp = explode(arg3, " ");
		arg3 = nTmp[0];
		if (sizeof(nTmp) > 1)
			count = to_int(nTmp[1]);
		else
			count = 1;
		file = absolute_path(who, arg3);
		if (sscanf(file, "%*s.c") != 1)
			file += ".c";
		// CHAT_D->sys_channel(0, sprintf(" %s ", file));
		if (!file_exist(file))
		{
			notify("Không thể tìm thấy cái này");
			return 1;
		}

		if (!(obj = load_object(file)) && (err = catch (call_other(file, "???"))))
		{
			return 1;
		}
		if (err = catch (obj = new (get_file_name(obj))))
		{
			return 1;
		}

		z = get_z(who);
		x0 = get_x(who);
		y0 = get_y(who);

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
			tell_user(who, obj->get_name() + " đã phục chế bên nhân vật");
			destruct(obj);
			return 1;
		}
		else if (obj->is_item())
		{
			if (USER_INVENTORY_D->can_carry(who, obj) < 1)
			{
				if (p = get_valid_xy(z, x0, y0, IS_ITEM_BLOCK))
				{
					x1 = p / 1000;
					y1 = p % 1000;
					obj->add_to_scene(z, x1, y1);
					if (count > 0 && obj->is_combined())
						obj->set_amount(count);
					who->to_front_xy(x1, y1);

					tell_user(who, obj->get_name() + " đã phục chế bên nhân vật");
					return 1;
				}
			}
			else
			{

				tell_user(who, obj->get_name() + " đã phục chế vào người");
				if (obj->get_max_combined() > 1)
				{
					if (count > 0)
						total = count;
					else
						total = 1;
					amount = USER_INVENTORY_D->carry_combined_item(who, obj, total);
					if (amount > 0 && obj->set_amount(amount))
					{
						if (p = obj->move(who, -1))
						{
							obj->add_to_user(p);
						}
					}
					else
						obj->add_amount(-total);
				}
				else
				{
					if (p = obj->move(who, -1))
					{
						obj->add_to_user(p);
					}
				}
				return 1;
			}
		}

		destruct(obj);
		notify("Không thể Phục chế vật thể này.");
	}
	return 1;
}

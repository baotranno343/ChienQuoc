#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
#include <time.h>

int main(object me, string arg)
{

	int p, cap, exist, exist2, i, size, iTime;
	string result, arg2, arg3, arg4, *line, *data, id, order;
	object item, item1, who, *objs, target, obj, obj2;
	mixed *mixTime;
	iTime = time();
	mixTime = localtime(iTime);
	if (is_player(me))
		return 1;
	if (!arg)
		return 1;
	if (arg == 0)
		return 1;
	if (sscanf(arg, "%s %s", arg3, arg2) == 2)
	{
		if (arg3 && !(who = find_any_char(arg3)))
		{
			write_user(me, ECHO "Không tìm thấy người này !");
			return 1;
		}
		who->set_name(arg2);
		who->save();
		obj = new ("/inh/user/list");
		id = who->get_id();
		obj->set_owner(who->get_real_id());
		if (who->get_real_id() == id)
			order = "1";
		else
			order = id[ < 1.. < 1];
		obj->set_save_2(order + ".name", arg2);
		obj->save();
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
		//	"sys/party/bxh_cap"->update_bxh_cap(me);
		write_user(me, ECHO "Đối phương đã đổi tên thành công !");
	}
	return 1;
}
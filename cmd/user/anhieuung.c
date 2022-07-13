#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me)
{

	int p, diem;
	string result, arg2;
	object item, item1, who;

	if (me->get("anhieuung") == 1)
	{
		me->set("anhieuung", 2);
		tell_user(me, "Bạn đã hiện hiệu ứng.");
	}
	else
	{
		me->set("anhieuung", 1);
		tell_user(me, "Bạn đã ẩn hiệu ứng.");
	}

	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));

	return 1;
}
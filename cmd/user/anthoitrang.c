#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me)
{

	int p, diem;
	string result, arg2;
	object item, item1, who;

	if (me->get("anthoitrang") == 1)
	{
		me->set("anthoitrang", 2);
		tell_user(me, "Bạn đã hiện thời trang cho nhân vật.");
	}
	else
	{
		me->set("anthoitrang", 1);
		tell_user(me, "Bạn đã ẩn thời trang cho nhân vật.");
	}

	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));

	return 1;
}
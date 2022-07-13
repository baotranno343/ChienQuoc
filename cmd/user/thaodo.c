
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{
	if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
	{
		send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
		return 1;
	}
	if (USER_INVENTORY_D->get_free_count(me) < 6)
	{
		notify("Hành trang không đủ 6 chỗ trống");
		return;
	}
	if (objectp(me->get_equip(WEAPON_TYPE)))
		me->remove_equip(WEAPON_TYPE);
	if (objectp(me->get_equip(ARMOR_TYPE)))
		me->remove_equip(ARMOR_TYPE);
	if (objectp(me->get_equip(HEAD_TYPE)))
		me->remove_equip(HEAD_TYPE);
	if (objectp(me->get_equip(NECK_TYPE)))
		me->remove_equip(NECK_TYPE);
	if (objectp(me->get_equip(WAIST_TYPE)))
		me->remove_equip(WAIST_TYPE);
	if (objectp(me->get_equip(BOOTS_TYPE)))
		me->remove_equip(BOOTS_TYPE);
	return 1;
}
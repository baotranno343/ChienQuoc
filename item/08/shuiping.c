#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

inherit "/inh/equip/equip";

#define PICID 3019
int get_item_value()
{
	return 500;
}
int get_item_value_2() { return 500; }
int is_limit_time_item() { return 1; }
int get_item_number() { return 10001102; }
int get_item_color() { return 2; }
void create()
{
	set_name("Bảo Bình");
	set_picid_1(4258);
	set_picid_2(4258);
	set_bind(1);
	set_value(50);
	set_no_sell(1);
	setup();
}
string get_desc()
{
	return "Bảo Bình là 1 trong 12 cung Hoàng Đạo. Khi được triệu hồi sẽ giúp chủ nhân nhận thêm 20% điểm kinh nghiệm.";
}

string get_short()
{
	return "Bảo Bình là 1 trong 12 cung Hoàng Đạo. Khi được triệu hồi sẽ giúp chủ nhân nhận thêm 20% điểm kinh nghiệm. Thời gian giới hạn 14 ngày. nhận được sẽ tự phong ấn.";
}

// 函数：使用效果
int get_use_effect(object me) { return __FILE__->get_use_effect_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout(object me, object item)
{
	object *obj, zombie, npc;
	int size, index, p, z, x, y;

	if (item->get_lock_time() == 0)
	{
		item->set_lock_time(time() + 14 * 24 * 60 * 60); //处理时间控制上面的。
		send_user(me, "%c%d%c", 0x31, getoid(item), 0);
	}
	if (item->get_lock_time() < time())
	{
		send_user(me, "%c%s", '!', "Vật phẩm đã hết hạn sử dụng");
		return;
	}
	obj = me->get("zombie"); //处理不能重叠使用机械宠物和水瓶的情况。
	size = sizeof(obj);
	if (size)
	{
		for (index = 0; index < size; index++)
		{
			zombie = obj[index];
			if (!objectp(zombie))
				continue;
			send_user(get_scene_object_2(zombie, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(zombie), get_y(zombie), 9414, 1, OVER_BODY, PF_ONCE);
			send_user(me, "%c%c%d", 0x2c, 0, getoid(zombie));
			zombie->remove_from_scene();
			destruct(zombie);
		}
		item->set_no_drop(0);
		item->set_no_get(0);
		me->delete ("zombie"); //将机械宠物给删除掉。
		me->delete_2("jiguan");
		USER_ENERGY_D->count_all_prop(me);
		return 0;
	}
	item->set_no_drop(1);
	item->set_no_give(1);
	item->set_no_sell(1);
	item->set_no_get(1);
	npc = new ("/npc/std/jiguan");
	npc->set_name(get_name());
	npc->set_char_picid(PICID);
	npc->upgrade_level(1);
	npc->set_owner(me);
	npc->set_action_mode(2);
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK);
	x = p / 1000;
	y = p % 1000;
	npc->add_to_scene(z, x, y, 3);
	me->add("zombie", ({npc}));
	//处理经验加成的情况。
	me->set("shuiping", npc);
	npc->set("shuiping.time", item->get_lock_time());
	return 0;
}
//
string get_tail_desc()
{
	object item = this_object();
	string desc;

	if (item->get_lock_time() == 0)
	{
		desc = HIG "(Chưa kích hoạt)" NOR "[Thời gian sử dụng 14 ngày]\n ";
	}

	return desc;
}

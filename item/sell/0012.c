#include <item.h>
#include <ansi.h>
#include <effect.h>
#include <map.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

int get_item_value() { return 10; }
int get_item_value_2() { return 10; }
int get_item_number() { return 10001017; }
int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Thiên Lý Hữu Tình");
	set_picid_1(3857);
	set_picid_2(3857);
	set_record(1);
	set_value(666);
	//	set_save("knb2",3);
	set_amount(1);
}

// 函数：获取描述
string get_desc()
{
	return "Phía trên có dòng chữ \"Thiên Trường Địa Cửu, Hữu Nghĩa Vĩnh Tồn\". \nDùng để triệu hồi một thành viên trong nhóm đến vị trí của mình. \nCó thể tái sử dụng sau 2 giây.";
}

// 函数：使用效果
int get_use_effect(object me) { return __FILE__->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout(object me)
{
	object map, *team, npc, item;
	string str1, str2;
	if (!objectp(map = get_map_object(get_z(me))))
		return 0;
	if (map->is_copy_scene())
	{
		send_user(me, "%c%s", '!', "Trong phó bản không thể sử dụng.");
		return 0;
	}
	if (map->is_changping())
	{
		send_user(me, "%c%s", '!', "Ở trong này không thể sử dụng.");
		return 0;
	}
	if (get_z(me) == 704)
	{
		notify("Trong Nhà Ngục không thể sử dụng.");
		return 0;
	}
	if (me->is_die())
	{
		notify("Chết rồi không thể sử dụng.");
		return 0;
	}
	if (me->get_save("cambayquest"))
	{
		notify("Ngươi không thể sử dụng khi đang mang trong mình nhiệm vụ.");
		//	send_user(me, "%c%s", '!', "Ngươi không thể sử dụng khi đang mang trong mình nhiệm vụ.");
		return 0;
	}
	/*	if ( map->get_map_type()==CAVE_MAP )
		{
				notify("Ở Hang động không thể sử dụng.");
                return 0;	
		} */
	if (map->is_ken_map())
	{
		notify("Trong phó bản không thể sử dụng.");
		//	send_user(me, "%c%s", '!', "Trong phó bản không thể sử dụng.");
		return 0;
	}
	if (get_z(me) == 910)
	{
		notify("Trong Bãi Luyện Tập không thể sử dụng");
		return 0;
	}
	if (get_z(me) == 920)
	{
		notify("Trong Bãi Luyện Tập không thể sử dụng");
		return 0;
	}
	if (get_z(me) == 889)
	{
		notify("Ở trong Vô Song Cung không thể sử dụng.");
		return 0;
	}
	if (get_z(me) == 888)
	{
		notify("Ở trong Vô Song Thành không thể sử dụng.");
		return 0;
	}
	if (objectp(item = present("Cờ Hiệu Vô Song Thành", me, 1, MAX_CARRY * 4)))
	{
		notify("Mang theo Cờ Hiệu không thể sử dụng.");
		return 0;
	}
	send_user(me, "%c%c%d%d%s", '?', 3, 0, me->get_save("fly"), "Ngươi muốn gọi bằng hữu ? Hãy điền số ID người ngươi muốn gọi về !\n" ESC "conlau ?.%s\n");
	return 0;
}
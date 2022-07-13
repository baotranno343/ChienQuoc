
// 自动生成：/make/equip/60b

#include <equip.h>
#include <level.h>
#include <item.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;

int get_family() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Bá Vương Chiến Bào");
        set_picid_1(6042);        set_picid_2(6042);

        set_level(150);        set_value(78500);
        set_max_lasting(50099);
        set("dp+", 350);
        set("pp+", 350);
		set("hp+", 700);
		set("hp%+", 10);
		set("mp%+", 10);
		set("mp+", 700);
		set("-*%", 10);
		set("sp+", 300);
		//set_item_color(2);

        setup();

        set_gender(1);
        set_armor_code(M_CHANGPAO);
}

// 函数：获取描述
string get_desc()
{
        return "Bá Vương Chiến Bào";
}
string get_tail_desc()
{
	return "【Hiệu ứng】 Hào quang Bá Vương.";		
}
void start_loop_perform( object me )
{
	CHAR_CHAR_D->init_loop_perform(me);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 40812, 1,UNDER_FOOT, PF_LOOP );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 59111, 1,UNDER_FOOT, PF_LOOP );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 95619, 1,UNDER_FOOT, PF_LOOP );
	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
void stop_loop_perform( object me )
{
	CHAR_CHAR_D->init_loop_perform(me);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 40812, 1, UNDER_FOOT, PF_STOP );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 59111, 1, UNDER_FOOT, PF_STOP );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 95619, 1, UNDER_FOOT, PF_STOP );
	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
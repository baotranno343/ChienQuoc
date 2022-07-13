
#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("Thô Ma Y");
        set_picid_1(6020);
        set_picid_2(6020);
        set_unit("件");

        set_level(10);
        set_value(1200);
        set_max_lasting(4599);
        set("dp", 20);
        set("pp", 20);
        set("hp", 15);
        set("mp", 15);

        setup();

        set_gender(1);
        set_armor_code(M_BUYI);
        set_armor_color_1(0x310228c0);
        set_armor_color_2(0x00001060);
}

// 函数：获取描述
string get_desc()
{
        return "Thô Ma Y";
}
void start_loop_perform( object me )
{
	CHAR_CHAR_D->init_loop_perform(me);
	//send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 2416, 1,UNDER_FOOT, PF_LOOP );
	//send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 24155, 1,UNDER_FOOT, PF_LOOP );
	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
void stop_loop_perform( object me )
{
	CHAR_CHAR_D->init_loop_perform(me);
	//send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 2416, 1, UNDER_FOOT, PF_STOP );
	//send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 24155, 1, UNDER_FOOT, PF_STOP );
	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
}
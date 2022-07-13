
#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("Tế Miên Y");
        set_picid_1(6120);
        set_picid_2(6120);
        set_unit("件");

        set_level(20);
        set_value(1350);
        set_max_lasting(6699);
        set("dp", 30);
        set("pp", 30);
        set("hp", 25);
        set("mp", 25);

        setup();

        set_gender(2);
        set_armor_code(F_BUYI);
        set_armor_color_1(0x20c23901);
        set_armor_color_2(0x000020e2);
}

// 函数：获取描述
string get_desc()
{
        return "Tế Miên Y";
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
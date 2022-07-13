
#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("Vũ Sinh Phục");
        set_picid_1(6013);
        set_picid_2(6013);
        set_unit("件");

        set_level(30);
        set_value(2500);
        set_max_lasting(8499);
        set("dp", 40);
        set("pp", 40);
        set("hp", 35);
        set("mp", 35);

        setup();

        set_gender(1);
        set_armor_code(M_JINZHUANG);
        set_armor_color_1(0x416282e2);
        set_armor_color_2(0x000018a0);
}

// 函数：获取描述
string get_desc()
{
        return "Vũ Sinh Phục";
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
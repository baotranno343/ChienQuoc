
#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("Phu Tử Phục");
        set_picid_1(6025);
        set_picid_2(6025);
        set_unit("件");

        set_level(50);
        set_value(5000);
        set_max_lasting(10599);
        set("dp", 60);
        set("pp", 60);
        set("hp", 55);
        set("mp", 55);

        setup();

        set_gender(1);
        set_armor_code(M_CHANGPAO);
        set_armor_color_1(0x20e33121);
        set_armor_color_2(0x00004208);
}

// 函数：获取描述
string get_desc()
{
        return "Phu Tử Phục";
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
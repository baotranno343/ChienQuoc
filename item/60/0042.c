
#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("Hiệp Sĩ Trang");
        set_picid_1(6023);
        set_picid_2(6023);
        set_unit("件");

        set_level(40);
        set_value(3000);
        set_max_lasting(9099);
        set("dp", 50);
        set("pp", 50);
        set("hp", 45);
        set("mp", 45);

        setup();

        set_gender(1);
        set_armor_code(M_JINZHUANG);
        set_armor_color_1(0x294518e3);
        set_armor_color_2(0x00002945);
}

// 函数：获取描述
string get_desc()
{
        return "Hiệp Sĩ Trang";
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
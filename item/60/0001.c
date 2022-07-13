
// 自动生成：/make/equip/60b

#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;
//int get_item_color() { return 1; }
// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Nam Trang Bố Y");
        set_picid_1(6003);
        set_picid_2(6003);

        set_level(0);
        set_value(80);
        set_max_lasting(2599);
        set("dp", 10);
        set("pp", 0);

        setup();

        set_gender(1);
        set_armor_code(0);
}

// 函数：获取描述
string get_desc()
{
        return "Nam Trang Bố Y";
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
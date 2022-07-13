#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

inherit "/inh/equip/equip";

#define RIDE_ID	20
int get_item_value() {return 500 ;}
int get_item_value_2() {return 500 ;}
int get_item_color() { return 2; }
// 函数：nh9h构造处理
void create()
{
        set_name( "Xe Trung Thu" );
        set_picid_1(10);
        set_picid_2(10);
        set_value(500);
        set_hide(0);
        set_bind(1);
}

// 函数：nh9h获取描述
string get_desc() 
{ 
        return "Cùng chị Hằng đi dạo chơi chốn Thiên đình nào.\n";
}

// 函数：nh9h使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me, this_object()); }

// 函数：nh9h使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
	int type;
	object who, npc;
	int i, size, x, y, z, p;	
	if (me->get_ride())
	{
		me->set_ride(0);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));		
		return 0;
	}
	me->set_ride(RIDE_ID);
	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
	if (item->get_bind()==1)
	{
		item->set_bind(2);
		send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
	}
        return 0;
}

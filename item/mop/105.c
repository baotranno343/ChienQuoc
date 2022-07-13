#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

inherit "/inh/equip/equip";

#define RIDE_ID	5

// 函数：构造处理
void create()
{
        set_name( "Trứng Bàn Bàn" );
        set_picid_1(14);
        set_picid_2(14);
        set_value(500);
        set_hide(0);
        set_bind(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Bàn Bàn là Kỵ Thú đặc biệt của Sự Kiện.\n Vật phẩm sau khi sử dụng sẽ Phong Ấn vào nhân vật.\n";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
	int type;
	object who, npc;
	int i, size, x, y, z, p;
	if (item->get_lock_time()==0) item->set_lock_time(time()+31*24*3600);
	if (item->get_lock_time()<time())
	{
		send_user(me, "%c%s", '!', "道具已过期");
		return 0;		
	}	
	if (me->get_fam_name()==""||!me->get_fam_name())
	{
		send_user(me, "%c%s", '!', "需要加入门派后才能使用这个道具。");
		return 0;
	}	
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

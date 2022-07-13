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
        return "Bàn Bàn vốn là Kỵ Thú của nước Tần\n Điều kiện sử dụng: Người sử dụng phải trở thành dân của nước Tần hoặc đạt đủ Giao Hảo với nước Tần.\n Vật phẩm sau khi sử dụng sẽ Phong Ấn vào nhân vật.\n";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
	int type;
	object who, npc;
	int i, size, x, y, z, p;	
	if (me->get_ride())
	{
	//me->set_2("thucuoi.hp", 0);
	//me->set_2("thucuoi.mp", 0);
	me->set_2("thucuoi.ap", 0);
	me->set_2("thucuoi.cp", 0);
	me->set_2("thucuoi.dp", 0);
	me->set_2("thucuoi.pp", 0);
	me->set_2("thucuoi.sp", 0);
	//USER_ENERGY_D->count_max_hp(me);
	//USER_ENERGY_D->count_max_mp(me);
	USER_ENERGY_D->count_ap(me);
	USER_ENERGY_D->count_cp(me);
	USER_ENERGY_D->count_dp(me);
	USER_ENERGY_D->count_pp(me);
	USER_ENERGY_D->count_sp(me);
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

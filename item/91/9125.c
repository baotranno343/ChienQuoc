#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

#define ITEM_USE_TIME	90 - me->get_skill(0436)

int get_item_color() { return 1; }
// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_ADD_HP; }

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Tái Tạo Hoàn" );
        set_picid_1(9125);
        set_picid_2(9125);
        set_unit( "粒" );
        set_value(7600);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Hồi phục toàn bộ Khí huyết và Ma lực, thời gian tái sử dụng 90 giây";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
	int type;
	if (get_item_type_2()== ITEM_TYPE_2_ADD_HP) type = EFFECT_USE_ITEM_1;
	else type = EFFECT_USE_ITEM_2 ;
        if (get_effect(me, type))
      	{
      		send_user( me, "%c%s", '!', sprintf("Thời gian đóng băng của vật phẩm còn %d giây", get_effect(me, type)) );
              	return 0;
      	}        
      	set_effect(me, type, ITEM_USE_TIME);
      	send_user( me, "%c%c%c%w", 0x30, get_item_type_2(), 0, ITEM_USE_TIME );	
        me->add_hp( me->get_max_hp() );
        me->add_mp( me->get_max_mp() );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );      
        return 1;
}

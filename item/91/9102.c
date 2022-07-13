#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

#define ITEM_USE_TYPE 	"add_hp"
#define ITEM_USE_TIME	15 - me->get_skill(0436) - (me->get_vip()?5:0)

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_ADD_HP; }

// 函数：构造处理
void create()
{
        set_name( "Tạo Hoá Đơn" );
        set_picid_1(9102);
        set_picid_2(9102);
        set_unit( "颗" );
        set_value(2100);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Lập tức hồi phụ 800 Khí Huyết, thời gian tái sử dụng 15 giây";
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
	send_user( me, "%c%c%c%w", 0x30, get_item_type_2(), 0, ITEM_USE_TIME );    // 更新使用间隔  

        me->add_hp( 800 * ( 100 + me->get_healing_rate() ) / 100 );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );      
        return 1;
}

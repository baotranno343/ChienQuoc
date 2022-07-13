#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

#define ITEM_USE_TYPE 	"add_mp"
#define ITEM_USE_TIME	2

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_ADD_MP; }

int get_item_value() {return 50 ;}
int get_item_value_2() {return 40 ;}
int get_item_number() {return 10001009 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name( "速效小恢复药水" );
        set_picid_1(4256);
        set_picid_2(4256);
        set_value(100);
        set_amount(1);
        set_record(1);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //        
}

// 函数：获取描述
string get_desc() 
{ 
        return "小瓶的法力药水，可马上恢复自身800点法术力。冷却时间2秒。";
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
      		send_user( me, "%c%s", '!', sprintf("道具冷冻时间还剩%d秒", get_effect(me, type)) );
              	return 0;
      	}        
      	set_effect(me, type, ITEM_USE_TIME);
	send_user( me, "%c%c%c%w", 0x30, get_item_type_2(), 0, ITEM_USE_TIME );    // 更新使用间隔  

        me->add_mp( 800 * ( 100 + me->get_healing_rate() ) / 100 );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );      
        return 1;
}

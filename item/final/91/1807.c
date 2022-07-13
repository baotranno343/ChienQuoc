#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

#define ITEM_USE_TIME	15 - me->get_skill(0436) - (me->get_vip()?5:0)

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_ADD_HP; }

// 函数：成品编号
int get_fin_type() { return 1807; }

// 函数：构造处理
void create()
{
        set_name( "Thí Luyện Quả" );
        set_picid_1(9102);
        set_picid_2(9102);
        set_value(800);
        set("level", 60);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Lập tức hồi phục 1850 điểm Khí Huyết, tái sử dụng 15 giây";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
	int type;
	object obj = this_object();
	if (get_item_type_2()== ITEM_TYPE_2_ADD_HP) type = EFFECT_USE_ITEM_1;
	else type = EFFECT_USE_ITEM_2 ;
        if (get_effect(me, type))
      	{
      		send_user( me, "%c%s", '!', sprintf("道具冷冻时间还剩%d秒", get_effect(me, type)) );
              	return 0;
      	}       
      	if (me->get_level()< obj->get("level"))
      	{
      		send_user( me, "%c%s", '!', sprintf("你的等级不够%d", obj->get("level")) );
              	return 0;
      	}       	
      	set_effect(me, type, ITEM_USE_TIME);
	send_user( me, "%c%c%c%w", 0x30, get_item_type_2(), 0, ITEM_USE_TIME );    // 更新使用间隔
        me->add_hp( 1850 * ( 100 + me->get_healing_rate() ) / 100 );        
        me->add_mp( 0 * ( 100 + me->get_healing_rate() ) / 100 );        
        if(type == EFFECT_USE_ITEM_1) send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE );      
        else send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9156, 1, OVER_BODY, PF_ONCE );      
        return 1;
}

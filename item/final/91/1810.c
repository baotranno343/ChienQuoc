#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

#define ITEM_USE_TIME	30 - me->get_skill(0436)

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_CON_MP; }

// 函数：成品编号
int get_fin_type() { return 1810; }

// 函数：构造处理
void create()
{
        set_name( "Tử Thiến Đơn" );
        set_picid_1(9121);
        set_picid_2(9121);
        set_value(1100);
        set("level", 20);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Nâng cao 10% Thân Thủ, hiệu quả 10 phút, tái sử dụng 2 giây";
}

// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me )
{
	int type;
	object obj = this_object();     
      	if (me->get_level()< obj->get("level"))
      	{
      		send_user( me, "%c%s", '!', sprintf("你的等级不够%d", obj->get("level")) );
              	return 0;
      	}       
      	if (get_effect(me, EFFECT_1810))
      	{
      		send_user( me, "%c%s", '!', sprintf("您已经使用了%s", obj->get_name()) );
              	return 0;
      	}       		
      	set_effect(me, EFFECT_1810, 600);
	send_user( me, "%c%w%w%c", 0x81, 1810, 600, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 1810, 1, EFFECT_GOOD );
        CHAR_CHAR_D->init_loop_perform(me);
        USER_ENERGY_D->count_max_hp(me);
        return 1;
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        return "增加10％的敏捷。\n";
}

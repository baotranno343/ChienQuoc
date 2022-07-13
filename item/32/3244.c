
// 自动生成：/make/item/make31c
#include <item.h>
#include <ansi.h>
inherit ITEM;
    inherit COMBINED;
inherit USABLE;   

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_CON_ALL; }

// 函数：原料类型
int get_stuff_type() { return 169; }

// 函数：构造处理
void create()
{
        set_name("蜂蜜");
        set_picid_1(3244);
        set_picid_2(3244);
        set_unit("罐");
        set_value(100);
        set_amount(1);
        set("add_hp", 150);	        
	set("add_mp", 150);	        
}

// 函数：获取描述
string get_desc() 
{
	return "品尝起来相当美味的蜂蜜，\n20秒内恢复玩家150点法术力150点气血值，\n2秒/15点,冷却时间2秒";    	
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }
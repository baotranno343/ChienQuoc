#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_CON_MP; }

// 函数：成品编号
int get_fin_type() { return 1755; }

// 函数：构造处理
void create()
{
        set_name("好喝的水");
        set_picid_1(9083);
        set_picid_2(9083);
        set_value(200);
        set_amount(1);
	set("level", 45);
	set("add_hp", 0);	
	set("add_mp", 805);	
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	desc = "战国2里才有的水，14秒内恢复玩家805点法力值。";
	if (this_player()->get_level()<this_object()->get("level"))
        	return sprintf(HIR+desc+"\n"HIR"使用要求 %d 级", get("level") ); 
	else
		return sprintf(desc+"\n使用要求 %d 级", get("level") ); 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }
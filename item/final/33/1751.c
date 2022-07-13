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
int get_fin_type() { return 1751; }

// 函数：构造处理
void create()
{
        set_name("玉米汤");
        set_picid_1(9083);
        set_picid_2(9083);
        set_value(100);
        set_amount(1);
	set("level", 20);
	set("add_hp", 0);	
	set("add_mp", 455);	
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	desc = "滋补养颜的汤,很好喝14秒内恢复玩家455点法力值。";
	if (this_player()->get_level()<this_object()->get("level"))
        	return sprintf(HIR+desc+"\n"HIR"使用要求 %d 级", get("level") ); 
	else
		return sprintf(desc+"\n使用要求 %d 级", get("level") ); 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }
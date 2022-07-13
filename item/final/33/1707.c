#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_CON_ALL; }

// 函数：成品编号
int get_fin_type() { return 1707; }

// 函数：构造处理
void create()
{
        set_name("水果拼盘");
        set_picid_1(9922);
        set_picid_2(9922);
        set_value(200);
        set_amount(1);
	set("level", 40);
	set("add_hp", 665);	
	set("add_mp", 665);	
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	desc = "好多好吃的水果拼在一起，14秒内恢复玩家665点气血值和法力值。";
	if (this_player()->get_level()<this_object()->get("level"))
        	return sprintf(HIR+desc+"\n"HIR"使用要求 %d 级", get("level") ); 
	else
		return sprintf(desc+"\n使用要求 %d 级", get("level") ); 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }
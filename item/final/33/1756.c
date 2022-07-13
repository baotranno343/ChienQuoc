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
int get_fin_type() { return 1756; }

// 函数：构造处理
void create()
{
        set_name("Rượu Cao Lương");
        set_picid_1(3154);
        set_picid_2(3154);
        set_value(400);
        set_amount(1);
	set("level", 50);
	set("add_hp", 0);	
	set("add_mp", 980);	
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	desc = "Loại rượu dân gian thường uống, Trong 14 giây hồi phục 980 điểm Pháp Lực";
	if (this_player()->get_level()<this_object()->get("level"))
        	return sprintf(HIR+desc+"\n"HIR"Sử dụng yêu cầu %d cấp", get("level") ); 
	else
		return sprintf(desc+"\nSử dụng yêu cầu %d cấp", get("level") ); 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }
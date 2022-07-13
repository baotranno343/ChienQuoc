#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_CON_HP; }

// 函数：成品编号
int get_fin_type() { return 1703; }

// 函数：构造处理
void create()
{
        set_name("Đậu Hủ Khô");
        set_picid_1(3304);
        set_picid_2(3304);
        set_value(100);
        set_amount(1);
	set("level", 20);
	set("add_hp", 385);	
	set("add_mp", 0);	
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	desc = "Đậu phụ khô, khôi phục 385 điểm giá trị khí huyết của người chơi trong vòng 14 giây.";
	if (this_player()->get_level()<this_object()->get("level"))
        	return sprintf(HIR+" %s \n "HIR"Yêu cầu sử dụng %d cấp", desc, get("level") ); 
	else
		return sprintf(" %s \n Yêu cầu sử dụng %d cấp", desc, get("level") ); 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }
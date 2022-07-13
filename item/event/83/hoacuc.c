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
int get_fin_type() { return 1710; }
int get_item_color() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Hoa Cúc");
        set_picid_1(3004);
        set_picid_2(3004);
        set_value(10000);
        set_amount(1);
	set("level", 10);
	set("add_hp", 500);	
	set("add_mp", 500);	
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	desc = "Một trong những loại hoa thường thấy trong các dịp Lễ 8/3.\nTrong 14 giây hồi phục 500 điểm Pháp Lực và 500 điểm Khí Huyết.";
	if (this_player()->get_level()<this_object()->get("level"))
        	return sprintf(HIR+desc+"\n"HIR "Yêu cầu sử dụng %d cấp", get("level") ); 
	else
		return sprintf(desc+"\nYêu cầu sử dụng %d cấp", get("level") ); 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }
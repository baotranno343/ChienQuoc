
// 自动生成：/make/item/make31c
#include <item.h>
#include <ansi.h>
inherit ITEM;
    inherit COMBINED;
inherit USABLE;   

// 函数：叠加上限
//  int get_max_combined() { return 30; }

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_CON_HP; }

// 函数：原料类型
int get_stuff_type() { return 225; }

// 函数：构造处理
void create()
{
        set_name("Dưa hấu");
        set_picid_1(3280);
        set_picid_2(3280);
        set_unit("块");
        set_value(1100);
        set_amount(1);
	set("level", 60);
	set("add_hp", 1100);	
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	desc = "Một loại trái cây với lượng nước cao và thanh ngọt, trong 20 giây người chơi hồi phục 1100 điểm Khí Huyết.";
	if (this_player()->get_level()<this_object()->get("level"))
        	return sprintf(HIR+" %s \n "HIR"Yêu cầu sử dụng %d cấp", desc, get("level") ); 
	else
		return sprintf(" %s \n Yêu cầu sử dụng %d cấp", desc, get("level") ); 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }
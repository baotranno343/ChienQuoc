
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

// 函数：构造处理
void create()
{
        set_name("Khoai Lang Nướng");
        set_picid_1(3320);
        set_picid_2(3320);
        set_unit("个");
        set_value(1150);
        set_amount(1);
	set("level", 70);
	set("add_hp", 1200);	
}

// 函数：获取描述
string get_desc() 
{
	string desc;
	desc = "Một loại khoai lang thơm ngon, 20 giây hồi phục cho người chơi 1200 điểm khí huyết.";
	if (this_player()->get_level()<this_object()->get("level"))
        	return sprintf(HIR+desc+"\n"HIR"Yêu cầu sử dụng %d cấp", get("level") ); 
	else
		return sprintf(desc+"\nYêu cầu sử dụng %d cấp", get("level") ); 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/sys/item/food" ->get_use_effect(me, this_object()); }
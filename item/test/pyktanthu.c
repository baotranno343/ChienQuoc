#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 999; }
int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Phong Yêu Kính Tàn Thư");
        set_picid_1(3858);
        set_picid_2(3858);
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	return "Vật phẩm chỉ có ở trong Phong yêu kính. Nghe nói Can Tương biết cách sử dụng vật phẩm này.";    	
}
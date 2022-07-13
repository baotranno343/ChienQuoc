#include <ansi.h>
#include <item.h>
#include <skill.h>

inherit COMBINED;
inherit ITEM;

int get_item_type() { return ITEM_TYPE_SPECIAL; }

int is_mirror() {return 1;}

// 函数：构造处理
void create()
{
        set_name("Hoàng Kim Giám Định Kính");
        set_picid_1(3564);
        set_picid_2(3564);
        set_value(5000);
        set("level2", 1000);
        set_amount(1);
}

int is_usable() {return 1;}

// 函数：获取描述
string get_desc() 
{		
	return "Cái gương có Pháp Lực, mang gương đặt ở vị trí cần giám định của trang bị .\n Có thể giám định được tất cả các trang bị .";
}

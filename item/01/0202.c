#include <ansi.h>
#include <equip.h>
inherit USABLE;
inherit ITEM;

int is_box() {return 1;}
int get_item_value() {return 300 ;}
int get_item_value_2() {return 300 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("Tử Kim Bảo Hộp");
        set_picid_1(6706);
        set_picid_2(6706);
        set_level(3);
        set_value(50);
}

// 函数：获取描述
string get_desc()
{
        return "Kho tàng của Chu Vương cất giấu, được làm từ những vật liệu tốt nhất ( có thể dùng "HIR "Chìa Khoá Tử Kim "NOR " mở ra).";
}

int get_use_effect( object me ) 
{
	return "/item/01/0200"->get_use_effect_callout(me,this_object());	
}

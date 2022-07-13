#include <ansi.h>
#include <equip.h>
inherit USABLE;
inherit ITEM;

int is_box() {return 1;}
int get_item_value() {return 300 ;}
int get_item_value_2() {return 300 ;}

// 函数：构造处理
void create()
{
        set_name("Thanh Đồng Bảo Hộp");
        set_picid_1(6704);
        set_picid_2(6704);
        set_level(2);
        set_value(50);
}

// 函数：获取描述
string get_desc()
{
        return "Kho tàng của Chu Vương cất giấu, được làm từ những vật liệu tốt nhất ( có thể dùng "HIR "Chìa Khoá Thanh Đồng "NOR " mở ra).";
}

int get_use_effect( object me ) 
{
	return "/item/01/0200"->get_use_effect_callout(me,this_object());	
}

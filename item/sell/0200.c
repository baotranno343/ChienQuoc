#include <equip.h>
#include <ansi.h>
inherit USABLE;
inherit ITEM;

int is_key() {return 1;}

int get_item_value() {return 5 ;}
int get_item_value_2() {return 5 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("Chìa Khóa Hồng Mộc");
        set_picid_1(6701);
        set_picid_2(6701);
        set_level(1);
        set_value(50);
		set_save("knb",20);
}

// 函数：获取描述
string get_desc()
{
        return "Nghe nói có thể mở được Hồng Mộc Bảo Rương trong kho tàng của Chu Vương. \n Khi tra chìa khóa vào, có thể làm "HIR"Hồng Mộc Bảo Rương "NOR"mở ra.";
}

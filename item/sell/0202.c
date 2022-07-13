#include <equip.h>
#include <ansi.h>
inherit USABLE;
inherit ITEM;

int is_key() { return 1; }

int get_item_value() { return 30; }
int get_item_value_2() { return 30; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Chìa Khóa Tử Kim");
        set_picid_1(6705);
        set_picid_2(6705);
        set_level(3);
        set_value(50);
        set_save("knb", 40);
}

// 函数：获取描述
string get_desc()
{
        return "Nghe nói có thể mở được Tử Kim Bảo Rương trong kho tàng của Chu Vương. \n Khi tra chìa khóa vào, có thể làm " HIR "Tử Kim Bảo Rương" NOR " mở ra.";
}

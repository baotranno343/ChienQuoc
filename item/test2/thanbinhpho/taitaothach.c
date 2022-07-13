#include <item.h>
#include <ansi.h>
#include <equip.h>
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_item_color() { return 2; }
// 函数：构造处理
void create()
{
    set_name("Tái Tạo Thạch");
    set_picid_1(8900);
    set_picid_2(8900);
    set_value(10);
    set_amount(1);
}

// 函数：获取描述
string get_desc()
{
    return "Viên thạch màu tím được phân giải từ viên Đoạn Thạch.";
}

#include <effect.h>
inherit ITEM;
inherit COMBINED;

int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Bánh Trứng");
        set_picid_1(9941);
        set_picid_2(9941);
        set_value(2);
        set_amount(1);
}

// 函数：获取描述
string get_desc()
{
        return "Trông thì dường như to hơn trứng gà thường một chút, là một trong những nguyên liệu làm Bánh Trứng Tầng, Bánh Kem.";
}

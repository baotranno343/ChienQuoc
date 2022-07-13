
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Tương Thiết Hài");
        set_picid_1(8806);
        set_picid_2(8806);

        set_level(25);
        set_value(2300);
        set_max_lasting(4999);
        set("dp", 7);
        set("sp", 9);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tương Thiết Hài";
}

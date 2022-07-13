
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Lam Mã Não Hạng Liên");
        set_picid_1(8613);
        set_picid_2(8613);

        set_level(55);
        set_value(31000);
        set_max_lasting(7699);
        set("cp", 0);
        set("pp", 55);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lam Mã Não Hạng Liên";
}

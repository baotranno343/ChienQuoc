
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Linh Lung Hài");
        set_picid_1(8812);
        set_picid_2(8812);

        set_level(35);
        set_value(4400);
        set_max_lasting(7099);
        set("dp", 18);
        set("sp", 19);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Linh Lung Hài";
}

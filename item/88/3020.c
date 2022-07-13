
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Sa Trường Hài");
        set_picid_1(8804);
        set_picid_2(8804);

        set_level(20);
        set_value(2000);
        set_max_lasting(5899);
        set("dp", 11);
        set("sp", 4);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Sa Trường Hài";
}


// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Toàn Phong Chi Ngoa");
        set_picid_1(8806);
        set_picid_2(8806);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("dp", 28);
        set("sp", 142);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Toàn Phong Chi Ngoa";
}

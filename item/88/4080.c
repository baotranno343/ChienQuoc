
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Hàn Tinh Hài");
        set_picid_1(8808);
        set_picid_2(8808);

        set_level(80);
        set_value(16000);
        set_max_lasting(10599);
        set("dp", 18);
        set("sp", 82);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hàn Tinh Hài";
}

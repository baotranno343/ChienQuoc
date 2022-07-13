
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Cuồng Chiến Hài");
        set_picid_1(8808);
        set_picid_2(8808);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("dp", 60);
        set("sp", 70);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cuồng Chiến Hài";
}

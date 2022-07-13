
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Cuồng Chiến Lý");
        set_picid_1(8804);
        set_picid_2(8804);

        set_level(30);
        set_value(2900);
        set_max_lasting(6699);
        set("dp", 16);
        set("sp", 10);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cuồng Chiến Lý";
}

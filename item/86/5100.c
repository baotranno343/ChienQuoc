
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Phụng Hoàng Minh Châu");
        set_picid_1(8600);
        set_picid_2(8600);

        set_level(100);
        set_value(80000);
        set_max_lasting(6099);
        set("cp", 188);
        set("pp", 106);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phụng Hoàng Minh Châu";
}

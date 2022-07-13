
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Phượng Vũ Yêu Đới");
        set_picid_1(8712);
        set_picid_2(8712);

        set_level(90);
        set_value(19500);
        set_max_lasting(10299);
        set("dp", 80);
        set("pp", 80);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phượng Vũ Yêu Đới";
}

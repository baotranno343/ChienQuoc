
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Lý Ngư Yêu Đới");
        set_picid_1(8705);
        set_picid_2(8705);

        set_level(40);
        set_value(8000);
        set_max_lasting(7299);
        set("dp", 30);
        set("pp", 30);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lý Ngư Yêu Đới";
}

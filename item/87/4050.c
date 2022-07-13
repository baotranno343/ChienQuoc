
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Cản Nhật Yêu Đới");
        set_picid_1(8707);
        set_picid_2(8707);

        set_level(50);
        set_value(10300);
        set_max_lasting(7899);
        set("dp", 40);
        set("pp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cản Nhật Yêu Đới";
}


// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Nhiếp Hồn Quán");
        set_picid_1(6580);
        set_picid_2(6580);

        set_level(100);
        set_value(27000);
        set_max_lasting(10299);
        set("dp", 85);
        set("pp", 63);

        setup();

        set_gender(1);
        set_head_code(47);
}

// 函数：获取描述
string get_desc()
{
        return "Nhiếp Hồn Quán";
}

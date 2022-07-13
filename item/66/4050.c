
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Cản Nhật Cân Mão");
        set_picid_1(6615);
        set_picid_2(6615);

        set_level(50);
        set_value(12000);
        set_max_lasting(7299);
        set("dp", 45);
        set("pp", 33);

        setup();

        set_gender(2);
        set_head_code(53);
}

// 函数：获取描述
string get_desc()
{
        return "Cản Nhật Cân Mão";
}

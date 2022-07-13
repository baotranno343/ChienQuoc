
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Hiên Duyên Hà Quán");
        set_picid_1(6680);
        set_picid_2(6680);

        set_level(110);
        set_value(30000);
        set_max_lasting(10899);
        set("dp", 93);
        set("pp", 69);

        setup();

        set_gender(2);
        set_head_code(58);
}

// 函数：获取描述
string get_desc()
{
        return "Hiên Duyên Hà Quán";
}

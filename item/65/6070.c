
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Hỗn Thiên Quán");
        set_picid_1(6562);
        set_picid_2(6562);

        set_level(70);
        set_value(29000);
        set_max_lasting(7899);
        set("dp", 47);
        set("pp", 80);

        setup();

        set_gender(1);
        set_head_code(45);
}

// 函数：获取描述
string get_desc()
{
        return "Hỗn Thiên Quán";
}


// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Cuồng Chiến Quán");
        set_picid_1(6574);
        set_picid_2(6574);

        set_level(30);
        set_value(5000);
        set_max_lasting(6699);
        set("dp", 44);
        set("pp", 16);

        setup();

        set_gender(1);
        set_head_code(42);
}

// 函数：获取描述
string get_desc()
{
        return "Cuồng Chiến Quán";
}

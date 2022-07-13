
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Bố Mạo");
        set_picid_1(6523);
        set_picid_2(6523);

        set_level(0);
        set_value(400);
        set_max_lasting(2499);
        set("dp", 5);
        set("pp", 0);

        setup();

        set_gender(1);
        set_head_code(40);
}

// 函数：获取描述
string get_desc()
{
        return "Bố Mạo";
}


// 自动生成：/make/equip/66b

#include <equip.h>

inherit HEAD;

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set_unit("%s");

        set_level(%d);
        set_value(%d);
        set_max_lasting(%d);
        set("dp", %d);
        set("pp", %d);
        set("hp", %d);
        set("mp", %d);

        setup();

        set_gender(2);
        set_head_code(%s);
        set_head_color(0x%04x%04x);
}

// 函数：获取描述
string get_desc()
{
        return "%s";
}

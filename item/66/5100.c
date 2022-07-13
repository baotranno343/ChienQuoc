
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Hỗn Lôi Hà Quán");
        set_picid_1(6678);
        set_picid_2(6678);

        set_level(100);
        set_value(45500);
        set_max_lasting(9699);
        set("dp", 68);
        set("pp", 113);

        setup();

        set_gender(2);
        set_head_code(57);
}

// 函数：获取描述
string get_desc()
{
        return "Hỗn Lôi Hà Quán";
}

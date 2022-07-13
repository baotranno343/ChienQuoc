
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Phong Lôi Đầu Cân");
        set_picid_1(6603);
        set_picid_2(6603);

        set_level(35);
        set_value(6700);
        set_max_lasting(7299);
        set("dp", 50);
        set("pp", 19);

        setup();

        set_gender(2);
        set_head_code(52);
}

// 函数：获取描述
string get_desc()
{
        return "Phong Lôi Đầu Cân";
}

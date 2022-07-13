
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Linh Lung Đầu Cân");
        set_picid_1(6603);
        set_picid_2(6603);

        set_level(35);
        set_value(6700);
        set_max_lasting(7299);
        set("dp", 44);
        set("pp", 27);

        setup();

        set_gender(2);
        set_head_code(52);
}

// 函数：获取描述
string get_desc()
{
        return "Linh Lung Đầu Cân";
}

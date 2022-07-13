
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Thẩm Diệu Chi Liên");
        set_picid_1(8605);
        set_picid_2(8605);

        set_level(50);
        set_value(30500);
        set_max_lasting(6399);
        set("cp", 0);
        set("pp", 52);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thẩm Diệu Chi Liên";
}

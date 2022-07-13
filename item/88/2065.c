
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Tiêu Dao Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(65);
        set_value(13800);
        set_max_lasting(9299);
        set("dp", 31);
        set("sp", 37);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tiêu Dao Lý";
}

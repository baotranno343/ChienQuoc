
#include <equip.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("勇敢者上衣");
        set_picid_1(6003);
        set_picid_2(6003);
        set_unit("件");

        set_level(0);
        set_value(1);
        set_max_lasting(10099);
        set("dp", 20);
        set_no_give(1);

        setup();

        set_gender(1);
        set_armor_code(M_BUYI);
}

// 函数：获取描述
string get_desc()
{
        return "供勇敢者使用，无等级限制、无门派限制。";
}

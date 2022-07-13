
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 1457; }

// 函数：构造处理
void create()
{
        set_name("Lôi Thần Hạng Liên");
        set_picid_1(8655);
        set_picid_2(8655);

        set_level(86);
        set_value(999);
        set_max_lasting(12099);
        set("ap", 107);
        set("dp", 0);
        set("cp", 167);
        set("pp", 108);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lôi Thần Hạng Liên";
}


// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：成品编号
int get_fin_type() { return 1305; }

// 函数：构造处理
void create()
{
        set_name("Kim Hạng Liên");
        set_picid_1(8608);
        set_picid_2(8608);

        set_level(20);
        set_value(2500);
        set_max_lasting(5099);
        set("ap", 0);
        set("dp", 0);
        set("cp", 48);
        set("pp", 38);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kim Hạng Liên";
}

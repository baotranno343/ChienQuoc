
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 1454; }

// 函数：构造处理
void create()
{
        set_name("Truy Phong Hạng Liên");
        set_picid_1(8655);
        set_picid_2(8655);

        set_level(46);
        set_value(999);
        set_max_lasting(7599);
        set("ap", 62);
        set("dp", 0);
        set("cp", 98);
        set("pp", 63);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Truy Phong Hạng Liên";
}

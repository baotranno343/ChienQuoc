
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1307; }

// 函数：构造处理
void create()
{
        set_name("Hộ Mệnh Hạng Liên");
        set_picid_1(8612);
        set_picid_2(8612);

        set_level(25);
        set_value(5000);
        set_max_lasting(5599);
        set("ap", 35);
        set("dp", 0);
        set("cp", 0);
        set("pp", 29);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hộ Mệnh Hạng Liên";
}

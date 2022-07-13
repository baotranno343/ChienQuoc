
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：成品编号
int get_fin_type() { return 1375; }

// 函数：构造处理
void create()
{
        set_name("U Hồn Hạng Liên");
        set_picid_1(8612);
        set_picid_2(8612);

        set_level(70);
        set_value(20000);
        set_max_lasting(10099);
        set("ap", 0);
        set("dp", 0);
        set("cp", 148);
        set("pp", 88);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "U Hồn Hạng Liên";
}

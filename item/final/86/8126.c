
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 1461; }

// 函数：构造处理
void create()
{
        set_name("Thiên Tôn Hạng Liên");
        set_picid_1(8612);
        set_picid_2(8612);

        set_level(126);
        set_value(999);
        set_max_lasting(32099);
        set("ap", 167);
        set("dp", 0);
        set("cp", 259);
        set("pp", 168);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Tôn Hạng Liên";
}

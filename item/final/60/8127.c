
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2380; }

// 函数：构造处理
void create()
{
        set_name("Thiên Tôn Thần Khải");
        set_picid_1(6182);
        set_picid_2(6182);

        set_level(127);
        set_value(1000);
        set_max_lasting(27899);
        set("ap", 0);
        set("dp", 490);
        set("cp", 0);
        set("pp", 480);
		set("hp", 325);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Tôn Thần Khải";
}

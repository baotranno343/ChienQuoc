
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 7; }

// 函数：成品编号
int get_fin_type() { return 2143; }

// 函数：构造处理
void create()
{
        set_name("Nguyệt Nha Trường Bào");
        set_picid_1(6025);
        set_picid_2(6025);

        set_level(55);
        set_value(8500);
        set_max_lasting(21899);
        set("ap", 0);
        set("dp", 96);
        set("cp", 0);
        set("pp", 152);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Nguyệt Nha Trường Bào";
}

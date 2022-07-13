
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 5; }

// 函数：成品编号
int get_fin_type() { return 2205; }

// 函数：构造处理
void create()
{
        set_name("Diệu Nhật Trường Bào");
        set_picid_1(6034);
        set_picid_2(6034);

        set_level(85);
        set_value(10000);
        set_max_lasting(24899);
        set("ap", 0);
        set("dp", 130);
        set("cp", 0);
        set("pp", 224);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Diệu Nhật Trường Bào";
}

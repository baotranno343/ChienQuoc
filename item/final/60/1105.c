
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 1; }

// 函数：成品编号
int get_fin_type() { return 2243; }

// 函数：构造处理
void create()
{
        set_name("Vong Hồn Chi Khải");
        set_picid_1(6058);
        set_picid_2(6058);

        set_level(105);
        set_value(10500);
        set_max_lasting(25899);
        set("ap", 0);
        set("dp", 240);
        set("cp", 0);
        set("pp", 155);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vong Hồn Chi Khải";
}

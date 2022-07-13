
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 1; }

// 函数：成品编号
int get_fin_type() { return 2180; }

// 函数：构造处理
void create()
{
        set_name("Thiết Bàn Thật Chiến Khải");
        set_picid_1(6080);
        set_picid_2(6080);

        set_level(75);
        set_value(9000);
        set_max_lasting(22899);
        set("ap", 0);
        set("dp", 180);
        set("cp", 0);
        set("pp", 110);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiết Bàn Thật Chiến Khải";
}

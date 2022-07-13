
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2383; }

// 函数：构造处理
void create()
{
        set_name("Thiên Tôn Chiến Ngoa");
        set_picid_1(8812);
        set_picid_2(8812);

        set_level(127);
        set_value(1000);
        set_max_lasting(27899);
        set("ap", 0);
        set("dp", 59);
        set("cp", 0);
        set("pp", 0);
        set("sp", 65);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Tôn Chiến Ngoa";
}

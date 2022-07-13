
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit %s;

// 函数：适用门派
int get_family() { return %d; }

// 函数：成品编号
int get_fin_type() { return %d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%04d);
        set_picid_2(%04d);

        set_level(%d);
        set_value(%d);
        set_max_lasting(%d);
        set("ap", %d);
        set("dp", %d);
        set("cp", %d);
        set("pp", %d);
        set("sp", %d);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "%s";
}

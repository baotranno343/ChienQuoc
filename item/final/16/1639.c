#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：成品编号
int get_fin_type() { return 1639; }

// 函数：构造处理
void create()
{
        set_name( "寒铁机关构件" );
        set_picid_1(4211);
        set_picid_2(4211);
        set_value(400);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "机关所需的零件";
}


#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：叠加上限
int get_max_combined() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1623; }

// 函数：构造处理
void create()
{
        set_name( "楚国织布机" );
        set_picid_1(4170);
        set_picid_2(4170);
        set_value(2400);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "操作复杂的织布机";
}


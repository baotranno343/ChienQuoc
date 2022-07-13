#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：叠加上限
int get_max_combined() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1627; }

// 函数：构造处理
void create()
{
        set_name( "玄铁锄头" );
        set_picid_1(3402);
        set_picid_2(3402);
        set_value(2800);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "传说中的工具";
}


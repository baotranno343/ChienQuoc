#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：叠加上限
int get_max_combined() { return %d; }

// 函数：成品编号
int get_fin_type() { return %d; }

// 函数：构造处理
void create()
{
        set_name( "%s" );
        set_picid_1(%d);
        set_picid_2(%d);
        set_value(%d);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "%s";
}


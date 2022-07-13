#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：成品编号
int get_fin_type() { return 1610; }

// 函数：构造处理
void create()
{
        set_name( "Cơ Cấu Chuyển Động" );
        set_picid_1(4212);
        set_picid_2(4212);
        set_value(1100);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Một ít bộ kiện cơ bản của cơ quan";
}


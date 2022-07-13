#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit USABLE;   

// 函数：成品编号
int get_fin_type() { return 1636; }

// 函数：构造处理
void create()
{
        set_name( "包裹" );
        set_picid_1(7104);
        set_picid_2(7104);
        set_value(1000);
        set("bag", 6);
}

// 函数：获取描述
string get_desc() 
{ 
        return "居家旅行时所用的小背包，\n可增加使用者6格的背包空间。\n包裹30天后会自动损坏。"; 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/cmd/std/bag" ->get_use_effect(me, this_object()); }

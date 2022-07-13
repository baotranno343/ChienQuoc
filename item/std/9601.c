#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit USABLE;   

// 函数：构造处理
void create()
{
        set_name( "乾坤袋" );
        set_picid_1(9601);
        set_picid_2(9601);
        set_value(5000);
        set("bag", 24);
}

// 函数：获取描述
string get_desc() 
{ 
        return "奇异的小口袋，里面似乎存在着无限的空间，\n可增加使用者24格的背包空间。\n乾坤袋30天后会自动损坏。"; 
}

// 函数：使用效果
int get_use_effect( object me ) { return "/cmd/std/bag" ->get_use_effect(me, this_object()); }

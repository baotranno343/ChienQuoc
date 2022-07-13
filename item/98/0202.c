#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit COMBINED;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "百合花" );
        set_picid_1(3015);
        set_picid_2(3015);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.卫队长最喜欢的一种花卉。"; 
}
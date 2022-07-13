#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "老酒" );
        set_picid_1(3152);
        set_picid_2(3152);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.采用糯米酿制，并掩埋于土下的米酒，有增强体力之功效。"; 
}
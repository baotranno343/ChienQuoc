#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;


// 函数：构造处理
void create()
{
        set_name( "黄金" );
        set_picid_1(9963);
        set_picid_2(9963);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.韩国使节想用来锻造鱼钩的一种贵重金属。"; 
}
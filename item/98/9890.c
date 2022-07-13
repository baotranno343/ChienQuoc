#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit COMBINED;
inherit LEGEND_ITEM;
int is_xiaomai() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "小麦" );
        set_picid_1(3202);
        set_picid_2(3202);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.一种酿酒的上等材料。"; 
}
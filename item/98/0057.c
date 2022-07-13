#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit COMBINED;
inherit LEGEND_ITEM;


// 函数：构造处理
void create()
{
        set_name( "Hồng bảo thạch" );
        set_picid_1(8962);
        set_picid_2(8962);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.Bảo thạch thương muốn dự trữ đích thương phẩm."; 
}
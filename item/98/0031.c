#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit COMBINED;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "Vũ mao" );
        set_picid_1(4001);
        set_picid_2(4001);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.Dùng để tỉnh lại thôi đại quan nhân đích trọng yếu vật phẩm。"; 
}
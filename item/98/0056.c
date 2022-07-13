#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit COMBINED;
inherit LEGEND_ITEM;


// 函数：构造处理
void create()
{
        set_name( "Quân Cờ" );
        set_picid_1(3766);
        set_picid_2(3766);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.Yến quốc thủ vệ muốn bắt được một loại kì loại."; 
}
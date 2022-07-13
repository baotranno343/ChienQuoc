#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;
int is_sacred_clothes() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "Hoàng Kim Thánh Y" );
        set_picid_1(6062);
        set_picid_2(6062);
        set_value(1);
        set_no_give(1);
//        set_no_drop(1);
        set_no_sell(1);  
//        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "Chiến Y mặc vào có thể biến thành Hoàng Kim Thánh Đấu Sĩ."; 
}


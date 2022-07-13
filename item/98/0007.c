#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit COMBINED;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "兽角" );
        set_picid_1(9072);
        set_picid_2(9072);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
        set_amount(1);
       
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.守卫的母亲治病需要的药材。"; 
}
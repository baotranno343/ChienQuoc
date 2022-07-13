#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "给牛郎的仙丹" );
        set_picid_1(9166);
        set_picid_2(9166);
        set_value(10);
        set_no_give(1);
//        set_no_drop(1);
        set_no_sell(1);  
//        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "王母娘娘赐予牛郎的仙丹。\n只要将仙丹"HIR"给予(Alt+G)"NOR"牛郎，他们就可以自由了。"; 
}


#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit COMBINED;
inherit LEGEND_ITEM;
int is_mitang() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "蜜糖" );
        set_picid_1(3244);
        set_picid_2(3244);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.相当美味的蜜糖。"; 
}
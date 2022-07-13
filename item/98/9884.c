#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;
int is_jiuqian() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "酒钱" );
        set_picid_1(0001);
        set_picid_2(0001);
        set_unit( "个" );
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.送给卫队长的酒钱。"; 
}
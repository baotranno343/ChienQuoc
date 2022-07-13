#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;
int is_tiecui() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "铁锤" );
        set_picid_1(3410);
        set_picid_2(3410);
        set_unit( "个" );
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.修理店老板需要的修理工具之一。"; 
}
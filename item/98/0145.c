#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "摄魂铃铛" );
        set_picid_1(9521);
        set_picid_2(9521);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.用来制服妖魔鬼怪所需要的法术用品。"; 
}
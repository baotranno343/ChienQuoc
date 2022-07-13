#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;
int is_qipu() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "棋谱" );
        set_picid_1(9808);
        set_picid_2(9808);
        set_unit( "副" );
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.送给门派向导的棋谱。"; 
}
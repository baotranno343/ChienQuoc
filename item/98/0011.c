#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;

int iOwner;
int who_can_get() { return iOwner; }
int set_owner(int i) { return iOwner=i; }

// 函数：构造处理
void create()
{
        set_name( "玉龙睛" );
        set_picid_1(8907);
        set_picid_2(8907);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.类似龙睛的一种宝石。"; 
}
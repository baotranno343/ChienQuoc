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
        set_name( "户籍信件" );
        set_picid_1(3857);
        set_picid_2(3857);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.查阅户名用的一种信函。"; 
}
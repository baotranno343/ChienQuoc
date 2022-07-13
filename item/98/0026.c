#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "盘缠" );
        set_picid_1(0003 );
        set_picid_2(0003 );
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.孟求去燕需要的路费。"; 
}

// 函数：使用效果
int get_use_effect( object me )
{
	if ( !me->get_legend(7,9) )
		return 0;
	return 1;	
}
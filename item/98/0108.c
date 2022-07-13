#include <ansi.h>
#include <item.h>
#include <task.h>

inherit ITEM;
inherit LEGEND_ITEM;


// 函数：构造处理
void create()
{
        set_name( "镜子" );
        set_picid_1(3563);
        set_picid_2(3563);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.被施法的能吸人灵魂的铜镜。"; 
}

// 函数：使用效果
int get_use_effect( object me ) 
{
	if ( ( me->get_legend(TASK_23,8) && !me->get_legend(TASK_23,10) )
		|| ( me->get_legend(TASK_23,20) && !me->get_legend(TASK_23,21) ) )
		return 0;
	return 1;
}
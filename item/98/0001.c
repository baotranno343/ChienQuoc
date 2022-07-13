#include <ansi.h>
#include <item.h>
#include <task.h>

inherit ITEM;
inherit USABLE;
inherit LEGEND_ITEM;

int is_huowu() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "Tiền Lão Cửu Hàng Hóa" );
        set_picid_1(4);
        set_picid_2(4);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ. Tiền lão cửu bị sở phương thành thủ vệ giam hàng hóa."; 
}
// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
	if ( me->get_legend(TASK_NEWBIE_03, 2)	|| ( !me->get_legend(TASK_NEWBIE_03, 1) && !me->get_legend(TASK_NEWBIE_03, 2)) )
		return 1;
}
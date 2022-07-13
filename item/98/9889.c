#include <ansi.h>
#include <item.h>
#include <task.h>

inherit ITEM;
inherit LEGEND_ITEM;
int is_baibuxian() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "百步仙" );
        set_picid_1(3154);
        set_picid_2(3154);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.陈老头梦寐以求的天下名酒。"; 
}

// 函数：使用效果
int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_call(me,this_object());	
}

int get_use_effect_call(object who, object item)
{
	if ( who->get_legend(TASK_NEWBIE_02,21) || !who->get_legend(TASK_NEWBIE_02,17) )
		return 1;	
}
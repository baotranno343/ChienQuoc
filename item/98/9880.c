#include <ansi.h>
#include <item.h>
#include <task.h>
inherit ITEM;
inherit LEGEND_ITEM;
int is_xunbao() { return 1;}

// 函数：构造处理
void create()
{
        set_name( "Gia Tộc Ngọc Bội" );
        set_picid_1(4953);
        set_picid_2(4953);
        set_unit( "块" );
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.Là Ngọc Bội có khắc dấu hiệu gia tộc của Chủ Tiệm Y Dược."; 
}
// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
	if (me->get_legend(TASK_48, 6) && me->get_legend(TASK_48, 7) && me->get_legend(TASK_48, 8) && me->get_legend(TASK_48, 9) && me->get_legend(TASK_48, 10))	return 1;
	return 0;
}
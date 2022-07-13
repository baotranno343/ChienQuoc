#include <ansi.h>
#include <task.h>

int is_legend_item() { return 1;}
//不执行ITEM的RESET
void reset() {}
//
int is_usable() { return 1; }
// 函数：使用效果
int get_use_effect( object me ) 
{
	return TASK_LEGEND_D->use_legend_item(me,this_object());	
}
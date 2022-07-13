#include <ansi.h>
#include <item.h>

inherit ITEM;

//int get_item_type() { return ITEM_TYPE_SPECIAL; }
int is_brand() { return 1; }
// 函数：构造处理
void create()
{
        set_name( "七夕蓝玫瑰" );
        set_picid_1(0050);
        set_picid_2(0050);
        set_value(0);
        set_no_give(1);
//        set_no_drop(1);
        set_no_sell(1);  
//        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "缘分信物，据说找到持有相同信物的异性，然后组队找到月老，\n按照月老的指引完成任务就有意想不到的惊喜。"; 
}
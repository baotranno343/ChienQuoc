#include <ansi.h>
#include <item.h>
#include <task.h>

inherit ITEM;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "灵芝草" );
        set_picid_1(9032);
        set_picid_2(9032);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.据说可以治疗头疼的一种中药材。\n右击使用可触发任务。"; 
}
// 函数：使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object item )
{
	if ( me->get_legend(TASK_49, 4) )
	{
		send_user( me, "%c%s",';',"将灵芝草交给新手村当铺老板，相信能治好他的头疼，他会给你高额报酬的。");
		send_user( me, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
		send_user( me, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,115,"头疼的毛病（3）" );
	}
}
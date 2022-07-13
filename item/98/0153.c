#include <ansi.h>
#include <item.h>
#include <task.h>

inherit ITEM;
inherit LEGEND_ITEM;

// 函数：构造处理
void create()
{
        set_name( "虎皮遗书" );
        set_picid_1(4201);
        set_picid_2(4201);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm nhiệm vụ.祖父留给丁鹤年的遗书，可右击查看。"; 
}

int get_use_effect( object me ) 
{
	if ( !me->get_legend(TASK_32,27) || me->get_legend(TASK_32,30) )
		return ::get_use_effect( me );
	if ( !me->get_legend(TASK_32,28) )
		send_user(me,"%c%s",'!',"请找丁鹤年交任务");
	else if ( !me->get_legend(TASK_32,29) )
	{
		if ( me->get("dhnopen") )
		{
			if ( TASK_LEGEND_D->can_task_add(me) != 1 ) return;
			me->delete("dhnopen");
			me->set_legend(TASK_32,29);
			send_user( me, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"楚国" );
			send_user( me, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,32,"祖父的遗产（2）" );
			send_user( me, "%c%s", '!', "得到任务 "HIY"祖父的遗产（2）");
		}
		else
		{
			me->set("dhnopen",1);
			send_user(me, "%c%c%w%s", ':', 3,0, sprintf("延之（丁鹤年父亲的字），为父欣慰，你看到这张虎皮书时，证明你已经有能力去到了困魔阵三层了，为父当初一直骂你愚驽，一心只迷恋建功立业，而不走我丁家炼气修身的本道，然则如此看来也许你的选择没有错，军道也是道，为父没有什么好教导你的了，你经历了战火的磨练，必定变得更加坚强，更加像我们丁家的男子汉，为父为你留下了一点有用的财产，可以让你们生活的舒适一些，你的母亲苦了她了，你去楚国找到刘头，他会告诉你财产的详细信息。\n"ESC"接受任务\nuse %x#\n", getoid(this_object())));
		}
	}
	return 0;
}
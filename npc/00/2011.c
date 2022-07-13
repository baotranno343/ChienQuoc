#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 2001; }

// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：构造处理
void create()
{
        set_name("陵墓宝箱");

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int z,y,x,p,*nLegend,i,size;
	mapping mpTmp;
	if( who->get_legend(TASK_2_01, 4) && !who->get_legend(TASK_2_01, 5) 
		&& !who->get_save("fb_gsb_jgtzb") )
	{
		if (get_effect(who, EFFECT_OPEN_BOX)) return;
		who->set("openbox",this_object());
		send_user(who, "%c%c%w%s", 0x5a, 0, 10, "查看中……");
		set_effect_2(who, EFFECT_OPEN_BOX, 1,10);				
		return;
	}
}

void into_effect( object who,object npc )
{
	object item;
	int p,z,x,y;
	int i,size,*nLegend;
	mapping mpTmp;
	string tmp;
	
	if( who->get_legend(TASK_2_01, 4) && !who->get_legend(TASK_2_01, 5) 
		&& !who->get_save("fb_gsb_jgtzb") )
	{
		if ( USER_INVENTORY_D->count_empty_carry(who) <1 )
		{
			send_user( who, "%c%s", '!', "您身上没有空位！");
			return;
		}
		TASK_LEGEND_D->give_item(who,"item/98/0242",1);
		send_user(who,"%c%s",'!',HIY"机关密图中部 1/1");
		if ( who->set_save("fb_gsb_jgtzb",1) && who->get_save("fb_gsb_jgtsb") 
			&& who->get_save("fb_gsb_jgtxb") )
		{
			who->set_legend(TASK_2_01,5);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,103,"机关密图(完成)" );
		}
		USER_TASK_D->send_task_intro(who,2,TID_ZHOUGUO,103);
	}
}

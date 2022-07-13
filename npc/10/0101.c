#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5415; }

// 函数：构造处理
void create()
{
        set_name("Quản Trọng");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*10+2,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        if ( who->get_legend(TASK_10,1) && !who->get_legend(TASK_10,2) ) 
		tmp += sprintf(ESC HIY "大王的口信\ntalk %x# welcome.1\n",getoid(this_object())); 
        send_user( who, "%c%s", ':', sprintf( "%s：\n    不知这山戎国何时才能停止对燕国的侵犯，可怜了那些燕国的子民啊～\n", get_name())
        + tmp +
        ESC"离开"
         );
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}
void do_welcome2( object me, string arg )
{
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_10,1) && !who->get_legend(TASK_10,2) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    %s，我早听说过你了，你就是那位消灭山戎族奸细和孤竹族使节的%s！\n    我军本被困在这崇山峻岭中，虽派出多批探子探路，但仍然找不着出路，后找了匹识途的老马带路，才使我军走出了山谷，现在战事已停，我得带领大军速速回国。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),who->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	break;

        case 2:
        	if ( who->get_legend(TASK_10,1) && !who->get_legend(TASK_10,2) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64031",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_10,2);
			who->add_exp(4000);
			who->add_potential(130);
			who->add_cash(4000);
			send_user(who,"%c%s",';',"带信给管仲（3） 经验 4000 潜能 130 金钱 4000 传风袍图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,8,"" );
        	}
        	break;   

        }
}
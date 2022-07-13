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
        set_name("Chu Tử");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*9+22,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        if ( who->get_legend(TASK_09,21) && !who->get_legend(TASK_09,22) ) 
		tmp += sprintf(ESC HIY "财政官的询问\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_09,22) && !who->get_legend(TASK_09,23) ) 
		tmp += sprintf(ESC HIY "周子的信物\ntalk %x# welcome.1\n",getoid(this_object())); 
        send_user( who, "%c%s", ':', sprintf( "%s：\n    鄱阳湖如此美景，真是令人心旷神怡啊！\n", get_name())
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
        	if ( who->get_legend(TASK_09,21) && !who->get_legend(TASK_09,22) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    赵国对于燕、齐两国来说，是西方的一道屏障，就像牙齿有嘴唇这道屏障一样，嘴唇没有了，牙齿就会感到寒冷。如果赵国今天灭亡了，明天就会轮到齐、燕两国，所以要救赵国，而且一定要迅速。\n    稻子为信，你去给我找9束稻子，然后交给财政官，他就明白我的意思了！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,22) && !who->get_legend(TASK_09,23) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    赵国对于燕、齐两国来说，是西方的一道屏障，就像牙齿有嘴唇这道屏障一样，嘴唇没有了，牙齿就会感到寒冷。如果赵国今天灭亡了，明天就会轮到齐、燕两国，所以要救赵国，而且一定要迅速。\n    稻子为信，你去给我找9束稻子，然后交给财政官，他就明白我的意思了！消灭大别山的狼妖就可以拿到稻子。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_09,23) && !who->get_legend(TASK_09,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    还没给财政官传达我的意思吗?\n"ESC"离开", me->get_name()));
        	break;

        case 2:
        	if ( who->get_legend(TASK_09,21) && !who->get_legend(TASK_09,22) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_09,22);
			who->add_exp(2500);
			who->add_potential(60);
			who->add_cash(1800);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,2,"" );
			send_user(who,"%c%s",';',"唇亡齿寒（2） 经验 2500 潜能 60 金钱 1800");
			me->do_welcome(1);
        	}
        	break;   
 	case 3:
        	if ( who->get_legend(TASK_09,22) && !who->get_legend(TASK_09,23) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,23);
        		who->delete_save_2("zouzidaozi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,3,"唇亡齿寒（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"唇亡齿寒（3）");
        	}
        	break;  
        }
}
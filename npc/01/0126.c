
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5802; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name( "Mạnh Đại Bá" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
        setup();
	set("mpLegend2",([5:({32*40+23,}),]));
}

// 变量：随机对话
string *TalkTable = ({ 
        "时间不早了，该回家吃饭了，我家老太婆肯定急着呢，呵呵，早点回去吧！",
});

int sizeof_talk = sizeof(TalkTable);

// 函数：对话处理
void do_look( object who )
{
        string tmp = "";

	if ( who->get_legend(TASK_NEWBIE_02, 22) && !who->get_legend(TASK_NEWBIE_02, 23) )  
			tmp = sprintf(ESC"孟氏的劝慰\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( who->get_legend(TASK_40, 22) && !who->get_legend(TASK_40, 23) )  
			tmp += sprintf(ESC HIY "食物的来源\ntalk %x# welcome.3\n",getoid(this_object()));
		      
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        send_user( who, "%c%s", ':', sprintf( "%s：\n%s\n", get_name(), TalkTable[ random(sizeof_talk) ] )
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
	int flag,i,j,k,size,*tmp=({}),*res=({}),p;
	object who,item,item1,*inv;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
		if( who->get_legend(TASK_NEWBIE_02, 22) && !who->get_legend(TASK_NEWBIE_02, 23) )
			send_user(who,"%c%s",':',sprintf("%s:\n    啊？你看我钓鱼都忘了时间，夫人还在家等着我吃饭呢！昨天晚上态度过激了点，今天想着钓点鱼改善下生活，安慰安慰她，没想到就忘记时间了，看我这脑子，好好好，谢谢你了，%s，我这就回家！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
			
		break;
	case 2:
		if( who->get_legend(TASK_NEWBIE_02, 22) && !who->get_legend(TASK_NEWBIE_02, 23) )
		{
			who->add_exp(150);
			who->add_potential(20);
			send_user(who,"%c%s",';',"夫妻间的争吵 经验 150 潜能 20");
			who->set_legend(TASK_NEWBIE_02, 23);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HUANJIAO,"" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HUANJIAO,1,"" );
		}
		break;
	case 3:
		if( who->get_legend(TASK_40, 22) && !who->get_legend(TASK_40, 23) )
			send_user(who,"%c%s",':',sprintf("%s:\n    我当然愿意呀！捕鱼是我的爱好，我每天既能做我喜欢的事，又能赚钱，那何乐而不为呢。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),getoid(me)));
			
		break;
	case 4:
		if( who->get_legend(TASK_40, 22) && !who->get_legend(TASK_40, 23) )
		{
			TASK_LEGEND_D->task_finish(who);
			who->add_exp(350);
			who->add_potential(20);
			send_user(who,"%c%s",';',"食物的来源 经验 350 潜能 20");
			who->set_legend(TASK_40, 23);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,35,"" );
		}
		break;
	}
}
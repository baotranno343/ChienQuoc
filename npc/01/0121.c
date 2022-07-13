
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5801; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name( "Lý Đại Bá" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//        set("level",4);
//        set("legend",({32*2+10}));
//	set("mpLegend",([0:({32*2+10,}),]));
        setup();
}

// 变量：随机对话
string *TalkTable = ({ 
        "Thời buổi quá loạn lạc, ra ngoài phải cẩn thận",
});

int sizeof_talk = sizeof(TalkTable);

// 函数：对话处理
void do_look( object who )
{
        string cmd,tmp="";
        int level, gold, exp;
        
//	if (!who->get_legend(TASK_NEWBIE_02, 10))
//		tmp = sprintf("\n"ESC"找智慧老人谈谈\ntalk %x# welcome.1\n",getoid(this_object()));
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        send_user( who, "%c%s", ':', sprintf( "%s:\n    %s\n", get_name(), TalkTable[ random(sizeof_talk) ] )
        			+ tmp +
        			ESC"Rời khỏi"
        			 );
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,p;
	object who,item;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        	case 1:
        		if (!who->get_legend(TASK_NEWBIE_02, 10))
        			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s\n    你好，年轻人，刚来这儿，肯定有很多不懂的吧？当然，我不是在说耕田种地之类的东西。现在，你去和智慧老人谈谈吧，他会解答你很多，你一直在疑惑的问题。智慧老人就在新手村的东北方。\n"ESC"接受\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
        		break;
        	case 2:
        		if (!who->get_legend(TASK_NEWBIE_02, 10))
        		{
        			who->set_legend(TASK_NEWBIE_02, 10);
				send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,17,"找智慧老人谈谈" );
				send_user( who, "%c%s", '!', "你接受了"HIY"找智慧老人谈谈"NOR"任务");
        		}
        		break;
	}
}
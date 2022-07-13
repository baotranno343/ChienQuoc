
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;
void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 7805; }

// 函数：构造处理
void create()
{
        set_name( "Mạnh Thị" );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//        set("level", 6);
//        set("legend", ({ 32*2+22 }));
//	set("mpLegend",([5:({32*2+22}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
        string tmp="";

/*	if( who->get_level() >= 5 )
        {
                if( !who->get_legend(TASK_NEWBIE_02, 23) )
                {
			tmp = sprintf(ESC"劝孟大伯回家\ntalk %x# welcome.1\n",getoid(this_object()));
                }
        }      */
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        send_user( who, "%c%s", ':', sprintf( " %s :\n Ông nhà ta ra ngoài vẫn chưa về, sắp ăn cơm đến nơi rồi! Thiệt đúng là chỉ biết làm người ta lo lắng, chẳng biết có xảy ra chuyện gì không nữa.\n", get_name() )
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
	int flag,i,j,k,size,*tmp=({}),*res=({}),p;
	object who,item,item1,*inv;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 22))
			send_user(who,"%c%s",':',sprintf("%s:\n    昨天晚上为搬家的问题和他吵了一架，唉，他早上出门了到现在还没回来，也该要吃饭了，可能还生我气，但又懒得和我计较，一个人在外面抽闷烟吧，夫妻哪能没有一点矛盾呢，拜托你帮我找到孟大伯，替我劝劝他。\n    他一般也不会去别处，就呆在这幽谷，可能就在我附近吧。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_NEWBIE_02, 22) && !who->get_legend(TASK_NEWBIE_02, 23))	
			send_user(who,"%c%s",':',sprintf("%s:\n    是他不愿意回来，还是你没找到他呢？不会真的出什么问题了吧？都出去一整天了，你可得尽快给我找到他呀，我都快担心死了！\n"ESC"离开",me->get_name()));
			
		break;
	case 2:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 22) )
		{
			who->set_legend(TASK_NEWBIE_02, 22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HUANJIAO,"幽谷" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HUANJIAO,1,"夫妻间的争吵" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"夫妻间的争吵");	
		}
		break;
	}
}
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 7309; }

// 函数：构造处理
void create()
{
        set_name("Tiếu Phu Nhân");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",103);
//        set("legend",({32*37+4}));
 	set("mpLegend",([100:({32*37+4})]));
	set("mpLegend2",([100:({32*37+6,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        if ( (who->get_level() >= 100 && !who->get_legend(TASK_37,4)) || (who->get_legend(TASK_37,4) && !who->get_legend(TASK_37,6)) ) 
		tmp += sprintf(ESC HIY "蜘蛛精\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_37,6) && !who->get_legend(TASK_36,29) ) 
		tmp += sprintf(ESC HIY "询问马铜\ntalk %x# welcome.1\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    听说长白山天池有神兽狻猊出现，国王允诺重赏要得此神兽，我家相公肖独贵为了我们刚刚出世的孩儿能有机会出山富贵，同着一伙熟识的猎人进山碰运气，但是一轮月圆月缺过去，时至今日也没有任何消息，我日日倚望独望，秋水望穿也不见相公归来，哎，帘卷北风，人比黄花瘦，怎么一个愁字了得，如果他有什么不测…我…我…呜……\n", get_name())
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
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_37,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我听其他猎人说，长白天池的黑风口是常年异兽的聚集之地，也是此次狩猎的必经之途，诸如蜘蛛精、树精雪怪都有出没，还听说成年的蜘蛛精善于变化媚人，常常抓壮年男子进补，哎要是我家相公……无论如何，壮士都要救救我们母子，救救我家相公啊，无论情形如何绑也要把相公绑回来啊，什么神兽猎不到就算了，那些天物，可不是我们这些普通人家能够消受的，能够一家子平平安安过一辈子就安心了。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_37,4) && !who->get_legend(TASK_37,5) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呜，相公，你怎可丢下我一人……\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_37,5) && !who->get_legend(TASK_37,6) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你碰到的蜘蛛精容貌丑陋远远不能同我相比，呀哟，你讲笑了，咦，我家相公那，没有一起回来吗？难道还有另外一个蜘蛛精？天哪，这可如何是好啊……\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_37,6) && !who->get_legend(TASK_36,29) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    当初我家相公是同着我的妹夫马铜一起出门的，他们哥俩儿应该一直在一起的，你帮我去东海渔村问问马铜回家没有，有没有我家相公的消息。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
	case 2:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_37,4) )
        	{
          		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
          		who->set_legend(TASK_37,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,60,"肖独贵（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"肖独贵（1）");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_37,5) && !who->get_legend(TASK_37,6) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_37,6);
			who->add_exp(44500);
			who->add_potential(650);
			who->add_cash(43500);
			send_user(who,"%c%s",';',"肖独贵（1） 经验 44500 潜能 650 金钱 43500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,60,"" );
			me->do_welcome(1);
        	}
        	break;   
	case 4:
        	if ( who->get_legend(TASK_37,6) && !who->get_legend(TASK_36,29) ) 
        	{
          		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
          		who->set_legend(TASK_36,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,61,"肖独贵（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"肖独贵（2）");
        	}
        	break;
        }
}
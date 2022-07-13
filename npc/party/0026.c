#include <npc.h>
#include <ansi.h>
#include <public.h>

inherit OFFICER;
object npc;
int iStart,iFinish;
// 函数：获取人物造型
int get_char_picid() { return 6009; }
void do_welcome(string arg);
// 函数：构造处理
void create()
{
        set_name("战国活动使者");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
	iStart = mktime(2007,3,21,10,0,0);
	iFinish = mktime(2007,3,21,22,0,0);
        setup();
}

void do_look(object who)
{
	int id = getoid(this_object()),iTime=time();
	if ( iTime > iFinish )
	{
		this_object()->remove_from_scene();
		destruct(this_object());
		return ;	
	}
	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("战国活动使者：\n    亲爱的%s你好，我是天帝派来的战国活动使者。今天是321世界网游日，所以，在今天的10点～22点期间进入大话战国的玩家都可以从我这里领取一共4小时的"HIR"321世界网游日双倍经验时间"NOR"。但是过了今天22点就没有机会领取了！赶快领取吧！\n"ESC"领取“321世界网游日双倍经验时间”\ntalk %x# welcome.0\n"ESC"详细规则\ntalk %x# welcome.5\n"ESC"离开",who->get_name(),id,id));
}


void do_welcome( string arg )
{
        object me = this_object();
        if ( time() > iFinish )
	{
		me->remove_from_scene();
		destruct(me);
		return ;	
	}
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,id;
       	object who;   
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 0:
        	i = 4-who->get_save("double321");
//        	if ( i > 3 )
//			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("战国活动使者：\n    321世界网游日双倍经验时间一共可以领取4个小时，但是领取时间仅限于今天的10点～22点。你还有%d小时双倍经验时间可以领取。你要领取多长时间的321世界网游日双倍经验时间？\n"ESC"一小时\ntalk %x# welcome.1\n"ESC"两小时\ntalk %x# welcome.2\n"ESC"三小时\ntalk %x# welcome.3\n"ESC"四小时\ntalk %x# welcome.4\n"ESC"离开",i,id,id,id,id));
//		else if ( i > 2 )
//			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("战国活动使者：\n    321世界网游日双倍经验时间一共可以领取4个小时，但是领取时间仅限于今天的10点～22点。你还有%d小时双倍经验时间可以领取。你要领取多长时间的321世界网游日双倍经验时间？\n"ESC"一小时\ntalk %x# welcome.1\n"ESC"两小时\ntalk %x# welcome.2\n"ESC"三小时\ntalk %x# welcome.3\n"ESC"离开",i,id,id,id));
		if ( i > 1 )
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("战国活动使者：\n    321世界网游日双倍经验时间一共可以领取4个小时，但是领取时间仅限于今天的10点～22点。你还有%d小时双倍经验时间可以领取。你要领取多长时间的321世界网游日双倍经验时间？\n"ESC"一小时\ntalk %x# welcome.1\n"ESC"两小时\ntalk %x# welcome.2\n"ESC"离开",i,id,id,));
		else if ( i == 1 )
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("战国活动使者：\n    321世界网游日双倍经验时间一共可以领取4个小时，但是领取时间仅限于今天的10点～22点。你还有%d小时双倍经验时间可以领取。你要领取多长时间的321世界网游日双倍经验时间？\n"ESC"一小时\ntalk %x# welcome.1\n"ESC"离开",i,id,));
		else
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"战国活动使者：\n    您已经没有双倍经验时间可以领取了！");
		break;
	case 1..2:
        	if ( who->get_save("double321") >= 4 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"战国活动使者：\n    您已经没有双倍经验时间了！");
        		return ;	
        	}
        	if ( who->get_save("double321") + flag > 4 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"战国活动使者：\n    您不能领取这么多双倍经验时间！");
        		return ;	
        	}
        	i = gone_time( who->get_login_time() );
		if ( i+ who->get_game_time()<who->get_double_time())
		{
		        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n     您的双倍经验时间还剩 %d 秒，不能领取\n"
		                ESC "关闭\nCLOSE\n", me->get_name(), who->get_double_time() - i - who->get_game_time() ) );			
			return;		               
		}
		
        	who->add_save("double321",flag);
		who->set_double_time(i+ who->get_game_time()+3600*flag);
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "" ); 
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,0001,"游戏辅助" ); 
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "双倍时间" ); 

		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("战国活动使者：\n    您领取了%d个小时双倍经验时间，祝您游戏愉快！",flag));
        	break;
        case 5:
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("战国活动使者：\n    "HIR"321世界网游日双倍经验时间"NOR"是在今天"HIR"10时～22时"NOR"内特别开放的活动，在活动期间，你可以领取到额外于你原来双倍经验时间的特别双倍经验时间。但是321世界网游日双倍经验时间"HIR"不可以跟其他双倍经验时间叠加"NOR"，如果你身上已经有双倍经验时间，你必须把你已有的双倍经验时间消耗完才可以再领取该双倍经验时间。\n"ESC"离开",));
		break; 
        }
        
}

void set_open(object who)
{
	if ( time() >= iFinish )
	{
		send_user(who,"%c%s",'!',"活动时间已过，不能开启");
		return ;
	}
	if ( objectp(npc) )
		return ;
	npc = new("npc/party/0026");
	npc->add_to_scene(80,285,177,4);
	call_out("gonggao",5);
	send_user(who,"%c%s",'!',"活动开启");
}

void set_close(object who)
{
	remove_call_out("gonggao");
	if ( objectp(npc) )
	{
		npc->remove_from_scene();
		destruct(npc);	
	}
	send_user(who,"%c%s",'!',"活动关闭");
}

void gonggao()
{
	remove_call_out("gonggao");
	if ( time() > iFinish )
	{
		if ( objectp(npc) )
		{
			npc->remove_from_scene();
			destruct(npc);	
		}
		return ;
	}
	call_out("gonggao",900);
	CHAT_D->sys_channel(0,HIR"321世界网游日双倍经验时间"NOR"活动现正火热进行中，各大玩家在今天的10时～22时期间可以到周国找战国活动使者领取"HIR"321世界网游日双倍经验时间"NOR"。还等什么？赶快行动吧！");
}
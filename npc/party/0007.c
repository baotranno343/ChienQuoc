#include <npc.h>
#include <ansi.h>
#include <public.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 6010; }
void do_welcome(string arg);
// 函数：构造处理
void create()
{
        set_name("补偿使者");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );

        setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("补偿使者：\n    对于本次开服延迟，我们深感抱歉。因此特在本服进行补偿。每位玩家可以在此领取额外10个小时的双倍时间。祝您游戏愉快！\n"ESC"领取补偿\ntalk %x# welcome.1\n"ESC"离开",id));
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i;
       	object who;   
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_save("bucang920") )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"补偿使者：\n    您已经领取过补偿了！");
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
        	who->set_save("bucang920",1);
		who->set_double_time(i+ who->get_game_time()+36000);

		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"补偿使者：\n    您领取了10个小时双倍时间的补偿，祝您游戏愉快！");
        	break;
 
        }
        
}
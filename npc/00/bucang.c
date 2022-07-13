
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#define CUR_BUCANG 	2

inherit OFFICER;

void do_look( object who );
void do_welcome( string arg );


// 函数：获取人物造型
int get_char_picid() { return 6009; }

// 函数：构造处理
void create()
{
        set_name( "补偿使者" );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int x;
	string cmd1, result;
	object me= this_object();
	cmd1 = sprintf("talk %x# welcome.1\n", getoid(me));
	result =  get_name() + "：\n    因为这次官方的修改所对贵用户造成的不便，我们特别为您提供了一次补偿机会。记住，补偿的机会只有一次，当你把所有的补偿都领取完毕之后，我不会再给予你任何的补偿，一定要好好把握应用。您想领取补偿吗？\n"
		ESC "领取\n" + cmd1 +
		ESC "取消\nCLOSE\n";
	send_user( who, "%c%c%w%s", ':', 3, 6009, result );
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	string result;
	object who;
	int level, exp, flag, pot, money; 
	who = this_player();
	flag = to_int(arg);
        switch(flag)
        {
        case 1:
        	if (who->get_save("buchang")>=CUR_BUCANG)
        	{
	                result =  get_name() + "：\n    您不是已经领过补偿了吗？\n"
	                		ESC "离开\nCLOSE\n";
			send_user( who, "%c%c%w%s", ':', 3, 6009, result );
			return ;
        	}
        	if (who->get_birthday()>1156417200)
        	{
	                result =  get_name() + "：\n    这次补偿只针对2006年8月24日19:00之前注册的玩家\n"
	                		ESC "离开\nCLOSE\n";
			send_user( who, "%c%c%w%s", ':', 3, 6009, result );
			return ;
        	}
        	who->set_save("buchang", CUR_BUCANG);
        	level = who->get_level();
        	exp = level*5000*3;
        	pot = level*200*3;
        	money = level*2000*3;
        	who->add_exp(exp);
        	who->add_potential(pot);
        	who->add_cash(money);
	        result =  get_name() + sprintf("：\n    您补偿了经验%d，潜能%d，金钱%d。\n"
	        		ESC "离开\nCLOSE\n", exp, pot, money);
			        	
		send_user( who, "%c%c%w%s", ':', 3, 6009, result );        	
                break;
        }
}


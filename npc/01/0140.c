
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5601; }

// 函数：构造处理
void create()
{
        set_name( "Đinh Đại Thúc" );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
        string cmd,tmp="";
        int gold, exp, pot;
        
	if (who->get_legend(TASK_NEWBIE_00, 17) && !who->get_legend(TASK_NEWBIE_00, 18))
		tmp = sprintf(ESC+HIY"稻草人的委托\ntalk %x# welcome.1\n",getoid(this_object()));              
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        send_user( who, "%c%s", ':', get_name() + "：\n    有空过来尝尝我做的小菜，吃过的人没有说不好的，这可是我生平最得意的一件事情！\n" +
        	tmp +
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
        int flag, date , status, p, z, x, y, i;
        object who, item;     
	string cmd;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);

        switch(flag)
        {
        case 1:
        	if (who->get_legend(TASK_NEWBIE_00, 17) && !who->get_legend(TASK_NEWBIE_00, 18))
        	{
                	cmd = sprintf( "talk %x# welcome.2\n", getoid( me ) );
                	send_user( who, "%c%s", ':', get_name() + "：\n    真是稀奇，竟然有人会帮奇怪的稻草人的忙？可见少侠真是个善心之人。请稍候片刻，我给你弄一个。\n    这块灵石是我以前从长白山的峰顶长白天池深处采集回来的，汇集了天地间的灵气，或许能派上用场，你就把它给稻草人装上吧。\n" 
                        	ESC "索取灵石\n" + cmd + ESC"离开" );        		
        	}
        	break;
        case 2:
        	if (who->get_legend(TASK_NEWBIE_00, 17) && !who->get_legend(TASK_NEWBIE_00, 18))
        	{
	                item = new ("/item/01/0002");
	                if( item )
	                {
	                        if (p = item->move(who, -1) )
	                        {
	                                item->add_to_user(p);
					who->set_legend(TASK_NEWBIE_00, 18);
	                                send_user( who, "%c%s", '>', "您得到" HIY "灵石" NOR " 1 块！");    
	                                send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,19,"" );
	                                send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,19,"稻草人的委托(已经完成)" );
	                        }                            
	                        else
	                        {
	                                destruct(item); 
	                                send_user(who,"%c%s",'!',"你携带的任务物品太多了");   
	                        }
	                }        		
        	}
        	break;	
        }
}
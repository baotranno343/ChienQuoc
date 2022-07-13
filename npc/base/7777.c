
#include <npc.h>
#include <ansi.h>
#include <map.h>
#include <task.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 6010; } 

// 函数：构造处理
void create()
{
        set_name( "PK赛报名人" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();     
}

void do_look( object who )
{
        int status;
        object me = this_object();
        if( is_player(who) ) 
	        send_user( who, "%c%c%w%s", ':', 3, 6010,
        		sprintf("%s：\n    想要在众玩家中一展雄风吗？想扬名天下吗？想要拿到官方送出的丰厚大奖吗？报名参加周六的玩家活动吧！只要花上10000游戏币的报名费，只要你能在周六的个人PK赛中一举夺魁，一切将不再是梦想！\n"
                	ESC "我想报名\ntalk %x# welcome.1\n"
                	ESC "我只是来看看\nCLOSE\n", me->get_name(), getoid(me) ) );
	else        
	if (me->get("start")==0)
	        send_user( who, "%c%c%w%s", ':', 3, 6010,
        		sprintf("%s：\n    你想做什么呢？你可以用showdat指令来查看所有玩家的报名。\n"
                	ESC "我想开启报名功能\ntalk %x# welcome.2\n"
                	ESC "我只是来看看\nCLOSE\n", me->get_name(), getoid(me) ) );
	else
	        send_user( who, "%c%c%w%s", ':', 3, 6010,
        		sprintf("%s：\n    你想做什么呢？你可以用showdat指令来查看所有玩家的报名。\n"
                	ESC "我想关闭报名功能\ntalk %x# welcome.3\n"
                	ESC "我想报名\ntalk %x# welcome.1\n"
                	ESC "我只是来看看\nCLOSE\n", me->get_name(), getoid(me), getoid(me) ) );
	                	
                	
}

void do_welcome( string arg )
{
        object npc, who, me, *inv;
        int i, flag, size;
        me = this_object();
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if (me->get("start")==0)
                {
                	send_user( who, "%c%c%w%s", ':', 3, 6010, sprintf("%s：\n    报名尚未开始呢。\n" , me->get_name() ) );
                	return;
                }        	
                if (who->get_save("pk_game")==1)
                {
                	send_user( who, "%c%c%w%s", ':', 3, 6010, sprintf("%s：\n    对不起，你已报名参加活动，请勿重复报名！\n" , me->get_name() ) );
                	return;
                }
                if (who->get_cash()<10000)
                {
                	send_user( who, "%c%c%w%s", ':', 3, 6010, sprintf("%s：\n    对不起，你的报名费不够，暂时不能报名！\n" , me->get_name() ) );
                	return;
                }              
                who->add_cash(-10000);  
                who->set_save("pk_game", 1);
                log_file("pkgame.dat", sprintf("%s %s %s(%d)\n", short_time(), who->get_id(), who->get_name(), who->get_number()));
                send_user( who, "%c%c%w%s", ':', 3, 6010, sprintf("%s：\n    你成功地报名参加活动，请静候相关活动通知。\n" , me->get_name() ) );
                break;
	case 2:
		me->set("start", 1);          
		send_user( who, "%c%c%w%s", ':', 3, 6010, sprintf("%s：\n    报名功能开启。\n" , me->get_name() ) );     
		break;
	case 3:
		me->set("start", 0);          
		send_user( who, "%c%c%w%s", ':', 3, 6010, sprintf("%s：\n    报名功能关闭。\n" , me->get_name() ) );     
		break;		
        }
}
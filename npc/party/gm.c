
#include <npc.h>
#include <ansi.h>
#include <map.h>
#include <task.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5201; } 

// 函数：构造处理
void create()
{
        set_name( "GM" );  
        setup();     
}

void do_look( object who )
{
        int status;
        int time;
        string result;
        object me = this_object();
        time = "/cmd/gm/findgm"->get_save("gm_time");
        if (who->get_save("findgm")==time)
        {
	        send_user( who, "%c%c%w%s", ':', 3, 5201,
	        	sprintf("%s：\n    我今天很感谢你，不过这次机会还是让给别人吧。\n"
	                , me->get_name() ) );        	
		return;	               
        }
        send_user( who, "%c%c%w%s", ':', 3, 5201,
        	sprintf("%s：\n    终于来救我了，好勇敢呀！我要谢谢你的救命之恩，好好的重谢你！\n"
                , me->get_name() ) );
	who->add_cash(30000);           	
	who->set_save("findgm", time);
	result = sprintf( HIY "%s援救ＧＭ成功，获得了30000金钱奖励。", who->get_name() );
	USER_D->user_channel(result);
	me->remove_from_scene();
	destruct(me);
}

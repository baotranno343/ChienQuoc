/**************
    任务链
***************/
#include <ansi.h>
#include <item.h>
#include <city.h>

// 函数：命令处理
int main( object me, string arg )
{
	int i;
	object who;
	string *nTmp,id;
        if( me->is_store_open() )
        {
                notify( "您在摆摊, 不能闲聊." );
                return 1;
        }
        if( !arg ) return 1;
        sscanf(arg, "%s %s", id, arg);
	if( !objectp( who = find_char(id) ) ) return 1;
        if( !inside_screen_2(me, who)  )
        {
                notify( "Bạn cách %s quá xa rồi.", who->get_name() );
                return 1;
        }
        i = to_int(arg);
        if ( i == 31 )
        	CHAIN_D->kill_boss(me,who);
        else if ( i == 11 && me->get_save_2("chain.status") != 99 )
        {
        	send_user(me,"%c%c%c%d%s",0x90,1,0,getoid(who),who->get_name());	//打开给予窗口
        }
        else
		CHAIN_D->finish_task(me,who,arg);
}
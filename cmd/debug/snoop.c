
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
        object who;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg ) return 1;

        if( arg=="none" )
        {
                who->set_snooper(0);
                tell_user( me, "您停止监听" );
                return 1;
        }

	if( !arg ) 
	{
                notify( "您要监听哪位玩家？" );
                return 1;
	}

        if( !( who = find_player(arg) ) )
        {
                notify( "您无法找到这个人。" );
                return 1;
        }
        who->set_snooper(me);
        tell_user( me, "您开始监听%s(%d)。", who->get_name(), who->get_number() );


        return 1;
}

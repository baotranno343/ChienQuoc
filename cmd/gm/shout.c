
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
        string result;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

	if( !arg || arg == "" ) 
	{
                notify( "您想告诉大家什么？" );
                return 1;
	}

        result = sprintf( HIY "%s ầm ĩ thét lớn: %s", me->get_name(), arg );
        USER_D->user_channel(result);

        return 1;
}

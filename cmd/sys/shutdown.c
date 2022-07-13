
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
        if( me != this_player(1) || is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        USER_D->user_channel( HIR "游戏重新启动，请稍候一分钟再重新登录。" );

        USER_D->save_all_data();    // 保存所有数据
        "/sys/sys/count"->hour_callout();

        shutdown(0);

        return 1;
}


#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
	int time;
        if( me != this_player(1) || is_player(me) ) 
        {
                notify( "Bạn không có đủ quyền hạn" );
		return 1;
        }
	if (!arg) time = 30;
	else time = to_int(arg);
	if (time==0) time = 30;
        USER_D->user_channel( sprintf(HIR "Trò chơi sẽ tắt sau %d phút.", time) );

        call_out( "do_reboot", 60, time );

        return 1;
}

// 函数：重启处理
private void do_reboot( int min )
{
        remove_call_out( "do_reboot" );

	if( -- min ) 
	{
                USER_D->user_channel( sprintf( HIR "Trò chơi sẽ tắt sau %d phút.", min ) );
		call_out( "do_reboot", 60, min );
	} 
	else 
	{
                USER_D->user_channel( HIR "Khởi động lại trò chơi, xin hãy đợi một phút và sau đó đăng nhập lại." );

                USER_D->save_all_data();    // 保存所有数据

                shutdown(0);
	}
}

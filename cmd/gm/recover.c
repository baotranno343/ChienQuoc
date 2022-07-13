
#include <ansi.h>

#define RECOVER_LOG     "gm/recover.txt"        // 恢复日志文件

// 函数：命令处理
int main( object me, string arg )
{
	object who = me;

        if( is_player(me) ) 
        {
                notify( "Ngươi không đủ quyền hạn" );
		return 1;
        }
	if( arg && !( who = find_any_char(arg) ) ) 
	{
	        notify( "Không thể tìm thấy người này" );
		return 1;
	}   
        who->set_hp( who->get_max_hp() );
        who->set_mp( who->get_max_mp() );
        who->set_yuan( who->get_max_yuan() );

        if( who != me && userp(who) ) 
        {
        	tell_user( me, HIY "%s đã khôi phục tất cả sinh lực。", who->get_name() );
                write_user( who, HIY "%s đã hoàn toàn khôi phục。",  me->get_name() );
                log_file( RECOVER_LOG, sprintf( "%s %s  %s(%s) đã hoàn toàn khôi phục。\n", 
                        short_time(), me->get_id(), who->get_name(), who->get_id() ) );
        }
        else        
        	tell_user( me, HIY " đã khôi phục hoàn toàn Sinh lực" );
        return 1;
}

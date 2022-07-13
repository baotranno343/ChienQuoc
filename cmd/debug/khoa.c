
#include <ansi.h>
#include <cmd.h>

// 函数：命令处理
int main( object me, string arg )
{
        object who;

        if( is_player(me) ) 
        {
                notify( "Bạn không đủ quyền hạn." );
		return 1;
        }

	if( !arg ) 
        {
                return 1;
        }

	if( !( who = find_player(arg) ) )
        {
                notify( "Không tìm thấy người này." );
		return 1;
        }
        if( who == me )
        {
                notify( "Không thể khoá chính mình." );
		return 1;
        }
        if( me->get_security_class() < who->get_security_class() )
        {
                notify( "Quyền lực của bạn không đủ." );
		return 1;
        }
		who->set_save("khoanhanvat",1);

	tell_user( me, "Bạn đã khoá nhân vật " + who->get_name() + " và kich ra khỏi trò chơi." );

        QUIT_CMD->main( who, "" );

        return 1;
}

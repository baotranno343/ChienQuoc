
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
        object who;

        if( is_player(me) ) 
        {
                notify( "Bạn không đủ quyền hạn" );
		return 1;
        }

	if( !arg ) 
	{
                notify( "Bạn muốn giết người nào ?" );
                return 1;
	}

        if( !( who = find_any_char(arg) ) )
        {
                notify( "Không tìm thấy người này" );
                return 1;
        }
        if( who == me )
        {
                notify( "Bạn không thể tự giết chính mình" );
		return 1;
        }
        if( !inside_screen_2(me, who) )
        {
                notify( "Bạn với người này khoảng cách quá xa" );
                return 1;
        }

        tell_user( who, HIR "GM đột nhiên xuất hiện trước mặt ngươi\n"
                        HIR "ＧＭ nói: “Mọi người sẽ nhớ tới ngươi, chết một hồi đi！”" );
        tell_user( me, HIR "Bạn hét lớn:“Chết đi!”， biến " + who->get_name() + " trở thành đống tro tàn" );

        CHAR_DIE_D->is_enemy_die( me, who, who->get_hp() );

        return 1;
}

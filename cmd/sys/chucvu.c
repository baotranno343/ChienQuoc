
#include <ansi.h>

// 函数:命令处理
int main( object me, string arg )
{
        object who;
        string cmd1, cmd2, cmd3, cmd4;
        string id, class0, class1;

        if( me != this_player(1) || !is_god(me) ) 
        {
                notify( "Bạn không đủ quyền hạn." );
		return 1;
        }

        if( !arg || sscanf( arg, "%s %s", id, class1 ) != 2 )
        {
                id = "?";  class1 = "?";
        }

        if( id == "?" )
        {
                send_user( me, "%c%c%d%s", '?', 1, 0, sprintf( "Cánh báo ! Bạn đang quản lý quyền hạn.\n\nHãy nhập vào só ID : \n"
                        ESC "chucvu %%s %s\n", class1 ) );
                return 1;
        }
        if( !( who = find_player(id) ) ) 
        {
                notify( "Không tìm thấy người này." );
                return 1;
        }
        if( !inside_screen_2(me, who) )
        {
                notify( "Khoảng cách quá xa." );
		return 1;
        }

        if( class1 == "?" )
        {
                cmd1 = sprintf( "chucvu %s (gm2)\n", id );
                cmd2 = sprintf( "chucvu %s (gm)\n", id );
                cmd3 = sprintf( "chucvu %s (player)\n", id );
                cmd4 = sprintf( "chucvu %s (god)\n", id );
                send_user( me, "%c%s", ':', sprintf( "Cánh báo ! Bạn đang quản lý quyền hạn.\n\nBạn muốn thiết lập %s(%d) chức vụ gì ?\n", who->get_name(), who->get_number() ) +
                        ESC "Chức vụ GM2.(gm2)\n" + cmd1 +
                        ESC "Chức vụ GM.(gm)\n" + cmd2 +
                        ESC "Người chơi.(player)\n" + cmd3 +
                        ESC "Chức vụ cao nhất.(god)\n" + cmd4 +
                        ESC "Ta phải suy nghĩ...\nCLOSE\n" );
                return 1;
        }

        if( class1 != PLAYER_CLASS && class1 != GM_CLASS && class1 != GOD_CLASS && class1 != GM2_CLASS ) 
        {
                notify( "Hệ thống ko có chức vụ này." );
		return 1;
        }

        class0 = get_class(who);

        if( !CLASS_D->set_class(me, who, class1) ) 
        {
                notify( "Thiết lập chức vụ thất bại !" );
		return 1;
        }

    	tell_user( me, HIY "Bạn đã thiết lập %s(%s) từ chức vụ %s thành chức vụ %s.", who->get_name(), who->get_id(), class0, class1 );
    	tell_user( who, HIY "%s(%d) đã thiết lập Bạn từ chức vụ %s thành chức vụ %s.", me->get_name(), me->get_number(), class0, class1 );
        who->setup();

        return 1;
}

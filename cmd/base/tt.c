
#include <ansi.h>

// 函数:命令处理
int main( object me, string arg )
{
        object *team, who;
        string name, id;

        if( !is_god(me) && gone_time( me->get_time("tt") ) < 3 )
        {
                notify( "Không nên sử dụng kênh Đội Nhóm thường xuyên" );
                return 1;
        }
		if ( get_z(me)==704 )
		{
				notify( "Trong Nhà Ngục không thể sử dụng Kênh này" );
                return 1;	
		}
        me->set_time( "tt", time() );

        if( !arrayp( team = me->get_team() ) )
        {
                notify( "Bạn chưa có gia nhập nhóm" );
                return 1;
        }

	if( !arg ) 
	{
                notify( "Bạn muốn nói gì ?" );
                return 1;
	}
	"/quest/help"->send_help_tips(me, 44);
	"/quest/help"->send_help_tips(me, 45);
        //name = sprintf( NAME_LEFT "%s" NAME_RIGHT, me->get_name() );
        name = sprintf("%c+%d,%s=%d%c-", '\t', 0xffff00, me->get_name(), me->get_number(), '\t');
        name = replace_string(name, "#", "＃");

	if( arg[0] == '#' && ( arg[1] < '0' || arg[1] > '9' ) )
	{
	        arg = arg[1..<1];

                send_user( team, "%c%c%d%s", 0x43, 7, me->get_number(), sprintf( CHAT "%s%s", name, arg ) );		
	}
	else if( arg[0] == '*' )
	{
	        arg = arg[1..<1];

                if( sscanf( arg, "%s %s", arg, id ) == 2 )
                {
                        if( id == "i" || id == "me" )
                        {
                                who = me;
                        }
                        else if( !( who = find_char(id) ) )
                        {
                                notify( "Không thể tìm thấy người này" );
	        	        return 1;
                        }
                        arg = EMOTE_D->do_emote(me, name, arg, who);
                }
                else    arg = EMOTE_D->do_emote(me, name, arg, 0);

                if( !arg ) return 1;

                send_user( team, "%c%c%d%s", 0x43, 7, me->get_number(), CHAT + arg );				
	}
	else    send_user( team, "%c%c%d%s", 0x43, 7, me->get_number(), sprintf( CHAT "%s : %s", name, arg ) );

        return 1;
}
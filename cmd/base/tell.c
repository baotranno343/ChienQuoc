#include <ansi.h>

// 函数:命令处理
int main( object me, string arg )
{
	string result, name;
        object who;
        string id;
        

        if( gone_time( me->get_time("mail") ) < 1 )
        {
                me->set_time( "mail", time() );
                notify( "Không nên nói thầm thường xuyên" );
                return 1;
        }
		if ( get_z(me)==704 )
		{
				notify( "Trong Nhà Ngục không thể sử dụng Kênh này" );
                return 1;	
		}
        me->set_time( "mail", time() );
        
        name = sprintf("%c+%d,%s=%d%c-", '\t', 0xff0000+246, me->get_name(), me->get_number(), '\t');
        name = replace_string(name, "#", "＃");
        
        if (arg=="" || arg==0) return 1;
	"/quest/help"->send_help_tips(me, 44);
	"/quest/help"->send_help_tips(me, 45);
        if( sscanf( arg, "%s %s", id, arg )==2 ) 
        {
		if (who = find_player(id) )
		{
			result = sprintf (HIY"Bạn nói thầm với %s : %s ", who->get_name(), arg);
			send_user( me, "%c%c%d%s", 0x43, 11, 0, result );
			result = sprintf (HIY" %s nói thầm với bạn : %s ", name, arg);
			send_user( who, "%c%c%d%s", 0x43, 11, me->get_number(), result );
		}
		else
		{
			result = "Bạn không thể tìm được người chơi này";
			send_user( me, "%c%c%d%s", 0x43, 11, 0, result );
		}
                return 1;
        }

        return 1;
}

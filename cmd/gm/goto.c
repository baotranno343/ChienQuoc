
#include <effect.h>

// 潞炉脢媒拢潞脙眉脕卯麓娄脌铆
int main( object me, string arg )
{
        object who;
        int z, x, y, x0, y0, p;

        if( is_player(me) ) 
        {
                notify( "脛煤脙禄脫脨脳茫鹿禄碌脛脠篓脧脼隆拢" );
		return 1;
        }

        if( !arg )
        {
                tell_user( me, "脛煤脧脰脭脷脭脷拢潞%d (%d, %d)", get_z(me), get_x(me), get_y(me) );
		return 1;
        }

        if( sscanf( arg, "%d,%d", x0, y0 ) == 2 )
        {
                z = get_z(me);
        }
        else if( !(who = find_any_char(arg) ) )
        {
                notify( "脛煤脦脼路篓脮脪碌陆脮芒赂枚脠脣隆拢" );
		return 1;
        }
        else if( who == me )
        {
                notify( "脛煤虏禄脛脺脠楼脳脭录潞脛脟脌茂隆拢" );
		return 1;
        }
        else
        {
                z = get_z(who);  x0 = get_x(who);  y0 = get_y(who);
        }

        if( p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK) )
        {
                x = p / 1000;  y = p % 1000;

                me->set_login_flag(2);    // 脤酶脳陋卤拢禄陇
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 4);

                me->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0) );

                tell_user( me, "Bạn đã bay tới: %d (%d, %d)", z, x, y );
		return 1;
        }
        else 
        {
        	if (who)
                	notify( "脛煤脠楼虏禄脕脣%s脛脟脌茂隆拢", who->get_name() );
                else
                	notify( "Không thể bay tới nơi này" );
		return 1;
        }
}

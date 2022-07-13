#include <ansi.h>
#include <effect.h>

// 潞炉脢媒拢潞脙眉脕卯麓娄脌铆
int main( object me, string arg )
{
        object who;
        int z, x, y, x0, y0, p;
		string arg2;

        if( is_player(me) ) 
        {
                notify( "Không đủ quyền hạn" );
		return 1;
        }

        if( !arg )
        {
                tell_user( me, "Can not fly %d (%d, %d)", get_z(me), get_x(me), get_y(me) );
		return 1;
        }
		if( sscanf( arg, "%d %d %d", z, x0, y0 ) == 3 )
        {
				p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK);
        }
		else if( sscanf( arg, "%d %d", x0, y0 ) == 2 )
        {
                z = get_z(me);
				p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK);
        }
		else if( z = to_int(arg) ) p = get_jumpin(z, -1);
		else if ( sscanf( arg, "id%s", arg2 ) == 1 )
		{
			if ( arg2 && !(who = find_any_char(arg2) ) )
			{
				notify( "Không tìm thấy người này" );
				return 1;
			}
			z = get_z(who);  x0 = get_x(who);  y0 = get_y(who);
			p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK);
		}

        if( p )
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
		return 1;
        }
}

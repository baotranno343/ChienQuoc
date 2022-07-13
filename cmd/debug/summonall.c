
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
	object * user, who;
        int z, x, y, x0, y0, p, i, size, number;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arrayp( user = USER_D->get_user() ) ) return 1;
        user -= ({ me });
        size = sizeof(user);
        if (size==0) 
        {
        	tell_user( me, HIY "游戏中没有其他人。" );
        	return 1;
        }
	number = 0;
        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);
	for (i=0;i<size;i++)
	{
		who = user[i];
		if (!who) continue;
	        if( p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK) )
	        {
	                x = p / 1000;  y = p % 1000;
	                who->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0), 40971, 0, 40971, 0 );
			number ++;
	        }
	        else
	        {
	        	x = get_x(me), y = get_y(me);
	        	who->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0), 40971, 0, 40971, 0 );
	        	number ++;
	        }
	        reset_eval_cost();
	}	       
	tell_user( me, sprintf(HIY "你召集了%d个玩家。", number) );
        return 1;
}

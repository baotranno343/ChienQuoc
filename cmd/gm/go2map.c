#include <ansi.h>
#include <effect.h>

// 函数：命令处理
int main( object me, string arg )
{
        int z, x, y, p, i;
	string *cmd = ({ "", "", "", "", "", "", "", "" });
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg )
        {
        	for (i=0;i<8;i++)
        		cmd[i] = sprintf("go2map %d 1\n", 10+i*10);
        	send_user( me, "%c%s", ':', "您想飞去哪个地图？\n"
        		ESC "齐国\n" + cmd[0] +
        		ESC "韩国\n" + cmd[1] +
        		ESC "赵国\n" + cmd[2] +
        		ESC "魏国\n" + cmd[3] +
        		ESC "秦国\n" + cmd[4] +
        		ESC "楚国\n" + cmd[5] +
        		ESC "燕国\n" + cmd[6] +
        		ESC "周国\n" + cmd[7] +
        		ESC "取消\nCLOSE\n");        		        		
		return 1;
        }
        else if( sscanf( arg, "%d %d,%d", z, x, y ) == 3 )
		p = get_valid_xy(z, x, y, IS_CHAR_BLOCK);
        else if( sscanf( arg, "%d %d", z, p ) == 2 )
                p = get_jumpin(z, p);
        else
        {
                z = to_int(arg);
                p = get_jumpin(z, -1);
        }

        if( p )
        {
                x = p / 1000;  y = p % 1000;

                me->set_login_flag(2);    // 跳转保护
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 4);

                me->add_to_scene(z, x, y, 3);

                tell_user( me, "您去到: %d (%d, %d)。", z, x, y );
		return 1;
        }
        else 
        {
                notify( "您去不了那张地图。" );
		return 1;
        }
}

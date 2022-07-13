#include <ansi.h>
object npc;

// 函数：命令处理
int main( object me, string arg )
{
	int p,x,y,z;
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
	if ( !objectp(npc) )
		npc = new("/npc/party/0001");
	
	if( p = get_valid_xy(z=get_z(me), get_x(me), get_y(me), IS_CHAR_BLOCK) )
        {
                x = p / 1000;  y = p % 1000;
                npc->add_to_scene( z, x, y, 3);
        }
	return 1; 
}
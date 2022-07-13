
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

int *place = ({ 010, 020, 030, 040, 050, 060, 070, 080 });

// 函数：命令处理
int main( object me, string arg )
{
        object what = me, item;
        int type, time, i, z, x, y, p;
        string name;
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
/*        
	for (i=0;i<100;i++)
	{
		z = place[random(sizeof(place))];
		p = get_jumpin(z, -1);
	        if( p )
	        {
	                x = p / 1000;  y = p % 1000;
	        }		
	        item = new( "/item/std/0591" );
	
	        item->set( SEAL_AREA, 1 );
	        item->set( SEAL_START, time() );
	        item->set( SEAL_INTERVAL, 10+i*5 );    // 小心准备 me
	        item->set( SEAL_CP, 200 );    // 小心准备 me, ap
	        item->set_owner(me);
	
	        set_z(item, z);  set_x(item, x);  set_y(item, y);  set_d(item, 1);
	//      set_map_seal(z, x, y, d);
	        set_block(z, x, y, SEAL_BLOCK);
	        move_object(item, z, x, y, SEAL_TYPE);	
	        item->do_start(me);		
	}
*/	
        "/npc/clone_100"->clone(me);
        return 1;
}

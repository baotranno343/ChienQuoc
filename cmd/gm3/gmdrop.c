
#include <ansi.h>
#include <equip.h>

// 函数：命令处理
int main( object me, string arg )
{
        object item;
        string *weapon, file;
        string cmd1, cmd2, cmd3, cmd4;
        int family, z, x, y, p, i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        z = get_z(me), x = get_x(me), y = get_y(me);
        for (i = 0; i< 10; i++)
        {        	
        	if ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
        	{
        		item = new ("/item/std/0001");
        		item->set_value(10000000);
        		item->add_to_scene(z, p / 1000, p % 1000);
        	}
        }
    /*    for (i = 0; i< 1; i++)
        {        	
        	if ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
        	{
        		item = new ("/item/04/0438");
        		item->set_amount(5);
        		item->add_to_scene(z, p / 1000, p % 1000);
        	}
        }  */      
        log_file("gm/gm3.dat", sprintf(" %s %s ( %d ) phần thưởng hoạt động %d ( %d %d )\n", short_time(), me->get_id(), me->get_number(), get_z(me), get_x(me), get_y(me) ));
        return 1;
}

#include <ansi.h>
#include <map.h>
#include <city.h>

// 函数：命令处理
int main( object me, string arg )
{
        string result;
        object map;
        object *item, who, npc;
        string name;
        int z, x, y, p, max_x, max_y;
        int i, size;        

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        who = me;
        if( arg && !( who = find_any_char(arg) ) )
        {
                notify( "您无法找到这个人。" );
		return 1;
        }        
	z = get_z(who);
	map = get_map_object(z);
	if (!map)
        {
                notify( "场景对象已删除" );
		return 1;
        }
        z = map->get_id();  max_x = get_map_max_x(z);  max_y = get_map_max_y(z);
        send_user( me, "%c%s", '>', sprintf("地图%s的大小为%d, %d", map->get_name(), max_x, max_y));
        for( x = 0; x < max_x; x += AREA_SIZE ) for( y = 0; y < max_y; y += AREA_SIZE )
        {
                if( have_scene_object(z, x, y, USER_TYPE, 1) )
                {
                        item = get_scene_object(z, x, y, USER_TYPE, 1);

                        for( i = 0, size = sizeof(item); i < size; i ++ ) if( who = item[i] )
                        {
                                send_user( me, "%c%s", '>', sprintf("%s的坐标是%d,%d", who->get_name(), get_x(who), get_y(who)));
                        }
                }                
        }
        return 1;
}

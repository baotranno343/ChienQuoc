#include <map.h>

object *nCopy = ({});
// 函数：生成二进制码
void SAVE_BINARY() { }

int new_scene(int d,string mapname,string name)
{
	int x,y,z,p;
	object map;
	
	if( ( z = find_map_flag(COPY_MAP_BEGIN, COPY_MAP_END, 0) ) <= 0 ) return 0;
        map = new(mapname);
        if ( !d )
        	d = map->get_client_id();
	init_virtual_map(z, d);		
        map->set_client_id(d);
        set_map_object( map, map->set_id(z) );       
        if ( sizeof(name) )
	        map->set_name(name);    
//        p = get_jumpin(z, 1);
        nCopy += ({ map });
	return z;
}

object *get_copy()
{
	return copy(nCopy);
}
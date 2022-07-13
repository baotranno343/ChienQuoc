#define FILE_GUMU "sys/party/PhoBanSatThanVuong"

inherit COPY_MAP;

// 函数：构造处理
void create() 
{ 
        object me = this_object();

        set_client_id(703);
        set_name("Phó Bản Bá Vương");

        if( !clonep(me) ) return;

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 600);    // 循环心跳：１分钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object map, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１分处理
{
	object *nMember;
	nMember = __FILE__->get_all_user( map );
	if ( nMember )
		nMember -= ({0});
	if ( sizeof(nMember) )
		return ;
	//副本内无玩家，删除此副本
	FILE_GUMU->delete_map(map);
	COPY_MAP->destruct_virtual_map( map, map->get_id() );
}
object *get_all_user( object map )
{
        object *item, who, *npc=({}),*all=({});
        int z, x, y, p, max_x, max_y;
        int i, size;

        reset_eval_cost();

        z = map->get_id();  max_x = get_map_max_x(z);  max_y = get_map_max_y(z);

        for( x = 0; x < max_x; x += AREA_SIZE ) for( y = 0; y < max_y; y += AREA_SIZE )
        {
                if( have_scene_object(z, x, y, USER_TYPE, 1) )
                {
                        item = get_scene_object(z, x, y, USER_TYPE, 1);

                        for( i = 0, size = sizeof(item); i < size; i ++ ) if( who = item[i] )
                        {
                                all += ({ item[i] });
                        }
                }
        }
	for (i=0;i<sizeof(all);i++)
	{
		if (all[i]->is_user())
			npc += ({all[i]});
	}
	return npc;
}
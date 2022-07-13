
// 自动生成：/make/std/makemap

#include <map.h>

inherit SCENE;

object lidashan,jianxi,wenshen,dudu;
void clone_npc();

// 函数：获取标识
int get_id() { return 142; }

// 函数：获取标识(客户端)
int get_client_id() { return 142; }

// 函数：获取名字
string get_name() { return "Bạch Mã Trang"; }

// 函数：复位顺序
int get_reset_order() { return 22; }

// 函数：获取地型类别
int get_map_type() { return FIELD_MAP; }

// 函数：获取投掷类数
int get_caster_amount() { return 1; }

// 函数：构造处理
void create() 
{
        object map = this_object();

        set_map_object( map, get_id() );
        MAP_D->load_npc_file( map, "/map/npc/142.npc" );

        set_fighter_file( ({ "/npc/npc/0220", "/npc/npc/0212",  }) );
        set_boss_file( ({ "/npc/npc/0275",  }) );

        set_sizeof_xy( sizeof_xy_point( get_id() ) );

        set_heart_timer( map, set_heart_timer_2( map, ( time() % RESET_TIME ) * 10 ) );
        set_heart_loop(map, 60);    // 循环心跳：１分钟
        map->heart_beat();
        set_heart_beat(1);

        call_out("reset", 1);    // 地图复位
}

// 函数：心跳处理
void heart_beat() { }

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１分处理
{
        call_out("reset", 1);    // 地图复位
}

// 函数：复位处理
void reset() 
{
        object map = this_object();
        int time = add_reset_time(1);

        remove_call_out( "reset" );

        if( time % 100 == 0 )    // 10 分钟
        {
                MAP_D->reset_npc( get_id() );    // 复位NPC 对象
                set_heart_timer( map, set_heart_timer_2( map, ( time() % RESET_TIME ) * 10 ) );
        }
        if( time % 200 == 0 )    // 20 分钟
        {
                MAP_D->clone_boss( this_object() );    // 载入小BOSS
        }
        if( time % get_clean_time() == 0 )    // 复位时间
        {
                call_out( "reset_call_out", get_reset_order()%6 );    // 载入小怪物
        }
        if ( time % 30 == 0 )		//3分钟
        {
        	if ( !objectp(lidashan) )
        	{
        		lidashan = new("npc/task/0115");	
        		lidashan->add_to_scene(142,204,129,2);
        	}
        	else if ( get_x(lidashan) != 204 || get_y(lidashan) != 129 )
        		lidashan->add_to_scene(142,204,129,2);
        	if ( !objectp(jianxi) )
        	{
        		jianxi = new("npc/task/0141");	
        		jianxi->add_to_scene(142,164,139,2);
        	}
        	else if ( get_x(jianxi) != 164 || get_y(jianxi) != 139 )
        		jianxi->add_to_scene(142,164,139,2);     		
        	if ( !objectp(wenshen) )
        	{
        		wenshen = new("npc/task/0185");	
        		wenshen->add_to_scene(142,132,122,2);
        	}
        	else if ( get_x(wenshen) != 132 || get_y(wenshen) != 122 )
        		wenshen->add_to_scene(142,132,122,2);
        	if ( !objectp(dudu) )
        	{
        		dudu = new("npc/task/0193");	
        		dudu->add_to_scene(142,80,122,2);
        	}
        	else if ( get_x(dudu) != 80 || get_y(dudu) != 122 )
        		dudu->add_to_scene(142,80,122,2);
        }
}

// 函数：复位处理
void reset_call_out()
{
        remove_call_out( "reset_call_out" );

        MAP_D->reset_item( get_id() );

        if( sizeof_fighter_file() > 0 ) 
        { 
                set_add_amount(-1);  clone_npc(); 
        }
}

// 函数：载入怪物
void clone_npc()
{
        remove_call_out( "clone_npc" );

        MAP_D->clone_npc( this_object() );

        if( get_add_amount() ) call_out( "clone_npc", 2 );
}

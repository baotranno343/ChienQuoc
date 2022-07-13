
// 自动生成：/make/std/makemap

#include <map.h>

inherit SCENE;
object suihuguai,zhangdashen,zhaoxiaosan,huangsulang;
void clone_npc();

// 函数：获取标识
int get_id() { return 264; }

// 函数：获取标识(客户端)
int get_client_id() { return 264; }

// 函数：获取名字
string get_name() { return "Bà Dương Hồ"; }

// 函数：复位顺序
int get_reset_order() { return 40; }

// 函数：获取地型类别
int get_map_type() { return FIELD_MAP; }

// 函数：获取投掷类数
int get_caster_amount() { return 0; }

// 函数：构造处理
void create() 
{
        object map = this_object();

        set_map_object( map, get_id() );
        MAP_D->load_npc_file( map, "/map/npc/264.npc" );

        set_fighter_file( ({ "/npc/npc/0322", "/npc/npc/0323",  }) );
        set_boss_file( ({ "/npc/npc/0357",  }) );

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
        	if ( !objectp(suihuguai) )
        	{
        		suihuguai = new("npc/task/0123");	
        		suihuguai->add_to_scene(264,117,45,2);
        	}
        	else if ( get_x(suihuguai) != 117 || get_y(suihuguai) != 45 )
        		suihuguai->add_to_scene(264,117,45,2);
        	if ( !objectp(zhangdashen) )
        	{
        		zhangdashen = new("npc/task/0126");	
        		zhangdashen->add_to_scene(264,150,158,2);
        	}
        	else if ( get_x(zhangdashen) != 150 || get_y(zhangdashen) != 158 )
        		zhangdashen->add_to_scene(264,150,158,2);
        	if ( !objectp(zhaoxiaosan) )
        	{
        		zhaoxiaosan = new("npc/task/0127");	
        		zhaoxiaosan->add_to_scene(264,75,72,2);
        	}
        	else if ( get_x(zhaoxiaosan) != 75 || get_y(zhaoxiaosan) != 72 )
        		zhaoxiaosan->add_to_scene(264,75,72,2);
        	if ( !objectp(huangsulang) )
        	{
        		huangsulang = new("npc/task/0128");	
        		huangsulang->add_to_scene(264,92,91,2);
        	}
        	else if ( get_x(huangsulang) != 92 || get_y(huangsulang) != 91 )
        		huangsulang->add_to_scene(264,92,91,2);
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

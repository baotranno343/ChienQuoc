
// 自动生成：/make/std/makemap

#include <map.h>

inherit SCENE;
object zhangjiu,xuzigao,wusan;
void clone_npc();

// 函数：获取标识
int get_id() { return 051; }

// 函数：获取标识(客户端)
int get_client_id() { return 051; }

// 函数：获取名字
string get_name() { return "Tần Trường Thành 1"; }

// 函数：复位顺序
int get_reset_order() { return 63; }

// 函数：获取地型类别
int get_map_type() { return FIELD_MAP; }

// 函数：获取投掷类数
int get_caster_amount() { return 1; }

// 函数：构造处理
void create() 
{
        object map = this_object();

        set_map_object( map, get_id() );
        MAP_D->load_npc_file( map, "/map/npc/051.npc" );

        set_fighter_file( ({ "/npc/npc/0660", "/npc/npc/0661", "/npc/npc/0662",  }) );
        set_boss_file( ({ "/npc/npc/0710",  }) );

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
        	if ( !objectp(zhangjiu) )
        	{
        		zhangjiu = new("npc/task/0159");	
        		zhangjiu->add_to_scene(51,96,138,2);
        	}
        	else if ( get_x(zhangjiu) != 96 || get_y(zhangjiu) != 138 )
        		zhangjiu->add_to_scene(51,96,138,2);
        	if ( !objectp(xuzigao) )
        	{
        		xuzigao = new("npc/task/0162");	
        		xuzigao->add_to_scene(51,97,133,2);
        	}
        	else if ( get_x(xuzigao) != 97 || get_y(xuzigao) != 133 )
        		xuzigao->add_to_scene(51,97,133,2);
        	if ( !objectp(wusan) )
        	{
        		wusan = new("npc/task/0164");	
        		wusan->add_to_scene(51,153,187,2);
        	}
        	else if ( get_x(wusan) != 153 || get_y(wusan) != 187 )
        		wusan->add_to_scene(51,153,187,2);
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

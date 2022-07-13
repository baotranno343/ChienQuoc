
// 自动生成：/make/std/makemap

#include <map.h>

inherit SCENE;

void clone_npc();

int is_pvp() {return 1;}

// 函数：获取标识
int get_id() { return 518; }

// 函数：获取标识(客户端)
int get_client_id() { return 518; }

// 函数：获取名字
string get_name() { return "Đồng Quan"; }

// 函数：复位顺序
int get_reset_order() { return 143; }

// 函数：获取地型类别
int get_map_type() { return FIELD_MAP; }

// 函数：获取投掷类数
int get_caster_amount() { return 0; }

// 函数：构造处理
void create() 
{
        object map = this_object();

        set_map_object( map, get_id() );
        MAP_D->load_npc_file( map, "/map/npc/518.npc" );

        set_fighter_file( ({ "/npc/npc/1100", "/npc/npc/1101",  }) );
        set_boss_file( ({ "/npc/npc/1151", "/npc/npc/1152",  }) );

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
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4 )    // 每１分处理
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

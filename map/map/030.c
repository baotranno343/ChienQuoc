
// 自动生成：/make/std/makemap

#include <map.h>
#include <city.h>

inherit SCENE_2;

// 禁止PK
int get_no_fight() {return 1;}

// 函数：获取标识
int get_id() { return 030; }

// 函数：获取标识(客户端)
int get_client_id() { return 030; }

// 函数：获取名字
string get_name() { return "Triệu"; }

// 函数：复位顺序
int get_reset_order() { return 120; }

// 函数：获取地型类别
int get_map_type() { return CITY_MAP; }

// 函数：构造处理
void create() 
{
        object map = this_object();

        set_map_object( map, get_id() );
        MAP_D->load_npc_file( map, "/map/npc/030.npc" );

        set_heart_timer( map, set_heart_timer_2( map, ( time() % RESET_TIME ) * 10 ) );
        set_heart_loop(map, 60);    // 循环心跳：１分钟
        map->heart_beat();
        set_heart_beat(1);

        call_out("reset", 1);    // 地图复位
        set_clean_time(10);
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
                map->init_herb_dbase();    // 清除草药数组
                set_heart_timer( map, set_heart_timer_2( map, ( time() % RESET_TIME ) * 10 ) );
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

        MAP_D->clone_fish( this_object(), CITY_ZHAO );
}

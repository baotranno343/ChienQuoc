
// 自动生成：/make/std/makemap

#include <map.h>

inherit SCENE;
object zhaoliu,xinmo,hunshimo,mingzhiyao,yeqing,lixiaoliu;
void clone_npc();

// 函数：获取标识
int get_id() { return 072; }

// 函数：获取标识(客户端)
int get_client_id() { return 072; }

// 函数：获取名字
string get_name() { return "Yên Trường Thành 2"; }

// 函数：复位顺序
int get_reset_order() { return 58; }

// 函数：获取地型类别
int get_map_type() { return FIELD_MAP; }

// 函数：获取投掷类数
int get_caster_amount() { return 0; }

// 函数：构造处理
void create() 
{
        object map = this_object();

        set_map_object( map, get_id() );
        MAP_D->load_npc_file( map, "/map/npc/072.npc" );

        set_fighter_file( ({ "/npc/npc/0560", "/npc/npc/0561", "/npc/npc/0562",  }) );
        set_boss_file( ({ "/npc/npc/0610",  }) );

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
        	if ( !objectp(zhaoliu) )
        	{
        		zhaoliu = new("npc/task/0145");	
        		zhaoliu->add_to_scene(072,53,73,2);
        	}
        	else if ( get_x(zhaoliu) != 53 || get_y(zhaoliu) != 73 )
        		zhaoliu->add_to_scene(072,53,73,2);
        	if ( !objectp(xinmo) )
        	{
        		xinmo = new("npc/task/0147");	
        		xinmo->add_to_scene(072,36,61,2);
        	}
        	else if ( get_x(xinmo) != 36 || get_y(xinmo) != 61 )
        		xinmo->add_to_scene(072,36,61,2);
        	if ( !objectp(hunshimo) )
        	{
        		hunshimo = new("npc/task/0149");	
        		hunshimo->add_to_scene(072,91,94,2);
        	}
        	else if ( get_x(hunshimo) != 91 || get_y(hunshimo) != 94 )
        		hunshimo->add_to_scene(072,91,94,2);
        	if ( !objectp(mingzhiyao) )
        	{
        		mingzhiyao = new("npc/task/0150");	
        		mingzhiyao->add_to_scene(072,165,146,2);
        	}
        	else if ( get_x(mingzhiyao) != 165 || get_y(mingzhiyao) != 146 )
        		mingzhiyao->add_to_scene(072,165,146,2);

        	if ( !objectp(yeqing) )
        	{
        		yeqing = new("npc/task/0155");	
        		yeqing->add_to_scene(072,112,110,2);
        	}
        	else if ( get_x(yeqing) != 112 || get_y(yeqing) != 110 )
        		yeqing->add_to_scene(072,112,110,2);
        	if ( !objectp(lixiaoliu) )
        	{
        		lixiaoliu = new("npc/task/0156");	
        		lixiaoliu->add_to_scene(072,156,157,2);
        	}
        	else if ( get_x(lixiaoliu) != 156 || get_y(lixiaoliu) != 157 )
        		lixiaoliu->add_to_scene(072,156,157,2);
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

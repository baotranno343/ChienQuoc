
// 自动生成：/make/std/makemap

#include <map.h>

inherit SCENE;

// 禁止PK
int get_no_fight() {return 1;}

void clone_npc();

// 函数：获取标识
int get_id() { return 007; }

// 函数：获取标识(客户端)
int get_client_id() { return 001; }

// 函数：获取名字
string get_name() { return "Tân Thủ Thôn(3)"; }

// 函数：复位顺序
int get_reset_order() { return 1; }

// 函数：获取地型类别
int get_map_type() { return FIELD_MAP; }

// 函数：获取投掷类数
int get_caster_amount() { return 0; }

// 函数：构造处理
void create()
{
        object map = this_object();
        object npc;

        set_map_object( map, get_id() );
        MAP_D->load_npc_file( map, "/map/npc/007.npc" );

        set_fighter_file( ({ "/npc/npc/0010", "/npc/npc/0011", "/npc/npc/0012",  }) );
//        set_boss_file( ({ "/npc/npc/0063",  }) );

        set_sizeof_xy( sizeof_xy_point( get_id() ) );

        set_heart_timer( map, set_heart_timer_2( map, ( time() % RESET_TIME ) * 10 ) );
        set_heart_loop(map, 60);    // 循环心跳：１分钟
        map->heart_beat();
        set_heart_beat(1);

	set_clean_time(1);
        call_out("reset", 1);    // 地图复位
        call_out("check_npc", 60);
        "/sys/sys/login"->create();
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

void check_npc()
{
	object npc;
        if (MAIN_D->get_host_type()!=4)
        {
/*        	
	        npc = new ("/npc/00/0200");
	        npc->add_to_scene(1, 150, 146, 3);
	        npc = new ("/npc/00/0200");
	        npc->add_to_scene(80, 321, 132, 4);
*/	        
}
/*
	npc = new ("/npc/01/0004");
	npc->add_to_scene(1, 155, 146, 3);
	npc = new ("/npc/01/0004");
	npc->add_to_scene(80, 324, 127, 4);
*/	
	if (MAIN_D->get_host_type()==2 )
	{
		npc = new ("/npc/ride/001");
		npc->add_to_scene(1, 53, 144, 3);
		npc = new ("/npc/ride/001");
		npc->add_to_scene(10, 85, 148, 2);
		npc = new ("/npc/ride/001");
		npc->add_to_scene(80, 292, 183, 4);

		npc = new ("/npc/ride/002");
		npc->add_to_scene(1, 146, 153, 5);
		npc = new ("/npc/ride/002");
		npc->add_to_scene(20, 205, 67, 4);
		npc = new ("/npc/ride/002");
		npc->add_to_scene(80, 323, 134, 4);

		npc = new ("/npc/ride/003");
		npc->add_to_scene(1, 182, 153, 3);
		npc = new ("/npc/ride/003");
		npc->add_to_scene(30, 200, 75, 3);
		npc = new ("/npc/ride/003");
		npc->add_to_scene(80, 340, 169, 4);

		npc = new ("/npc/ride/004");
		npc->add_to_scene(1, 193, 148, 3);
		npc = new ("/npc/ride/004");
		npc->add_to_scene(40, 321, 150, 3);
		npc = new ("/npc/ride/004");
		npc->add_to_scene(80, 250, 218, 2);

		npc = new ("/npc/ride/005");
		npc->add_to_scene(1, 154, 147, 3);
		npc = new ("/npc/ride/005");
		npc->add_to_scene(50, 66, 123, 2);
		npc = new ("/npc/ride/005");
		npc->add_to_scene(80, 310, 140, 3);

		npc = new ("/npc/ride/006");
		npc->add_to_scene(1, 152, 147, 3);
		npc = new ("/npc/ride/006");
		npc->add_to_scene(60, 212, 248, 2);
		npc = new ("/npc/ride/006");
		npc->add_to_scene(80, 290, 149, 3);

		npc = new ("/npc/ride/007");
		npc->add_to_scene(1, 143, 154, 3);
		npc = new ("/npc/ride/007");
		npc->add_to_scene(70, 218, 250, 4);
		npc = new ("/npc/ride/007");
		npc->add_to_scene(80, 322, 135, 3);

		npc = new ("/npc/ride/010");
		npc->add_to_scene(80, 318, 132, 3);

		npc = new ("/npc/ride/020");
		npc->add_to_scene(10, 86, 149, 2);
		npc = new ("/npc/ride/020");
		npc->add_to_scene(20, 203, 68, 4);
		npc = new ("/npc/ride/020");
		npc->add_to_scene(30, 202, 78, 2);
		npc = new ("/npc/ride/020");
		npc->add_to_scene(40, 323, 153, 3);
		npc = new ("/npc/ride/020");
		npc->add_to_scene(50, 68, 125, 2);
		npc = new ("/npc/ride/020");
		npc->add_to_scene(60, 214, 250, 2);
		npc = new ("/npc/ride/020");
		npc->add_to_scene(70, 220, 248, 4);
		
		npc = new ("/npc/party/0020");
		npc->add_to_scene(1, 143, 147, 3);
		npc = new ("/npc/party/0021");
		npc->add_to_scene(1, 141, 147, 3);
		
		npc = new ("/npc/party/0020");
		npc->add_to_scene(80, 327, 127, 3);
		npc = new ("/npc/party/0021");
		npc->add_to_scene(80, 325, 127, 3);		
	}
	
}

// 函数：载入怪物
void clone_npc()
{
        remove_call_out( "clone_npc" );

        MAP_D->clone_npc( this_object() );

        if( get_add_amount() ) call_out( "clone_npc", 2 );
}

#include <map.h>
inherit SCENE;

mapping mpPlace = ([
20 : ({ ({69, 46}), ({77, 52}), ({85, 56}),  }),
40 : ({ ({92, 61}), ({100, 67}), ({107, 71}),  }),
50 : ({ ({64, 51}), ({72, 56}), ({81, 61}), ({87, 65}), ({96, 71}), ({102, 75}),  }),
60 : ({ ({59, 55}), ({67, 60}), ({75, 66}), ({82, 70}), ({91, 76}), ({97, 79}),  }),
70 : ({ ({54, 59}), ({63, 66}), ({71, 71}), ({77, 75}), ({84, 80}), ({89, 85}),  }),
80 : ({ ({48, 66}), ({55, 71}), ({62, 76}), ({68, 81}), ({74, 86}), ({80, 91}), }),
100 : ({ ({80, 34}), ({87, 40}), ({94, 46}), ({101, 51}),  }),
130 : ({ ({74, 40}), ({81, 46}), ({89, 51}), ({97, 56}),  }),
150 : ({ ({109, 57}), ({116, 63}), ({105, 62}), ({111, 67}),  }),
]);
mapping mpColor = ([
40 : 0x3426,
50 : 0x71c6,
60 : 0x4210,
70 : 0x4307,
80 : 0x6a07,
100 : 0xffffff,
130 : 0x1abce7,
150 : 0xa7cb42,
]);
// 函数：获取标识
int get_id() { return 887; }

// 函数：获取标识(客户端)
int get_client_id() { return 887; }

// 函数：获取名字
string get_name() { return "Võ Công Tu Luyện Trường"; }

// 函数：获取地型类别
int get_map_type() { return CAVE_MAP; }

void init_trainer()
{
	int i,size,*nTmp,level,m,n;
	object npc;
	mixed *mxTmp;
	nTmp = keys(mpPlace);
	for(i=0,size=sizeof(nTmp);i<size;i++)
	{
		level = nTmp[i];
		mxTmp = mpPlace[level];
		for(m=0,n=sizeof(mxTmp);m<n;m++)
		{
			npc = new("npc/std/0008");
			if ( !npc )
				return ;
			npc->set_level(level);
			if ( mpColor[level] )
				npc->set_head_color(mpColor[level]);
			npc->add_to_scene(887,mxTmp[m][0],mxTmp[m][1]);
		}
		
	}
	
}

// 函数：构造处理
void create() 
{
        object map = this_object();

        set_map_object( map, get_id() );
        MAP_D->load_npc_file( map, "/map/npc/887.npc" );
		
        set_heart_timer( map, set_heart_timer_2( map, ( RESET_TIME - time() % RESET_TIME ) * 10 ) );
        set_heart_loop(map, 60);    // 循环心跳：１分钟
        map->heart_beat();
        set_heart_beat(1);

        call_out("reset", 1);    // 地图复位
        
       	init_trainer();
}

// 函数：复位处理
void reset() 
{
        int time = add_reset_time(1);

        remove_call_out( "reset" );

        if( !( time % 10 ) ) MAP_D->reset_npc( get_id() );
        if( time % get_clean_time() ) return;
        MAP_D->reset_item_callout( get_id() );
}

// 函数：跳离之前处理
void before_jumpout( object me )
{
        object soldier, *zombie;
        int i, size;

        if( objectp( soldier = me->get("soldier") ) )    // 停止召唤兽攻击
        {
                soldier->set_enemy(0);
        }
        if( arrayp( zombie = me->get("zombie") ) )
        {
                for( i = 0, size = sizeof(zombie); i < size; i ++ ) 
                        if( objectp( zombie[i] ) ) zombie[i]->set_enemy(0);
        }
        me->set_enemy(0);
}


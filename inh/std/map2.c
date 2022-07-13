
inherit "/inh/std/scene";

private static mapping mpHerb = ([ ]);          // 草药数组

// -------------------------------------------------------------

// 函数：获取草药数组
mapping get_herb_dbase() { return copy(mpHerb); }

// 函数：获取草药数据尺寸
int sizeof_herb_dbase() { return sizeof(mpHerb); }

// 函数：清除草药数组(刷新时)
void init_herb_dbase() { mpHerb = ([ ]); }

// 函数：获取草药数据
int get_herb( int x, int y ) { return mpHerb[ sprintf("%d,%d", x, y) ]; }

// 函数：设置草药数据
int set_herb( int x, int y, int value ) { return mpHerb[ sprintf("%d,%d", x, y) ] = value; }

// 函数：添加草药数据
int add_herb( int x, int y, int value )
{
        int old;

        if( !( old = get_herb(x, y) ) ) 
                return set_herb(x, y, value);
        else    return set_herb(x, y, old + value);
}

// -------------------------------------------------------------

// 函数：消除之前处理
void before_destruct()
{
        mapping officer;
        object map, *char, npc;
        string *key;
        int i, size;

        map = this_object();

        if( mapp( officer = map->get_npc_dbase() ) )
        {
                size = sizeof( key = keys(officer) );
                for( i = 0; i < size; i ++ ) if( objectp( npc = officer[ key[i] ] ) )
                {
                        npc->remove_from_scene();
                        destruct(npc);
                }
        }

        if( arrayp( char = map->get_2("fish") ) )
        {
                for( i = 0, size = sizeof(char); i < size; i ++ ) if( objectp( npc = char[i] ) )
                {
                        npc->remove_from_scene();
                        destruct(npc);
                }
        }

        if( arrayp( char = map->get_reset_dbase() ) )
        {
                for( i = 0, size = sizeof(char); i < size; i ++ ) if( objectp( npc = char[i] ) )
                {
                        npc->remove_from_scene();
                        destruct(npc);
                }
        }
}

//进入场景处理
void enter_scene(object who)
{
	QUEST_TIPS->enter_scene_tip(who,this_object());
}
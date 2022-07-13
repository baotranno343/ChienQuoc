
private static int StoreOpen;
private static string StoreName = "Tiệm tạp hóa";
private static mapping Store = ([ ]);           // 商品资料
private static mapping Beast = ([ ]);           // 召唤兽对应表

// -------------------------------------------------------------

// 函数：获取商品数据
mapping get_store_dbase() { return copy(Store); }

// 函数：初始化商品数据
void init_store_dbase() { Store = ([ ]); Beast = ([ ]); };

// -------------------------------------------------------------

// 函数：获取商品数据
int get_store( string key ) { return Store[key]; }

// 函数：设置商品数据
int set_store( string key, int value ) 
{ 
        send_user( this_object(), "%c%c%d", 0x7b, to_int(key), value );
        return Store[key] = value; 
}

// 函数：删除商品数据
void delete_store( string key ) 
{ 
        send_user( this_object(), "%c%c%d", 0x7b, to_int(key), -1 );
        map_delete(Store, key); 
}

// 函数：获取商铺名字
string get_store_name() { return StoreName; }

// 函数：设置商铺名字
string set_store_name( string name ) 
{ 
        object me = this_object();

        if( sizeof(name) > 20 ) name = name[0..19];
        if( !CHECK_D->is_legal_store(me, name) ) return StoreName;
//      if( !is_chinese(name) ) return StoreName;

        if( StoreOpen && name != StoreName )    // 摆摊时才群发
        {
                if( me->get_login_flag() > 1 ) send_user(me, "%c%c%s", 0x3d, 80, name);
                send_user( get_scene_object_2(me, USER_TYPE), "%c%c%d%s", 0x3d, 81, getoid(me), name );
        }
        return StoreName = name;
}

// 函数：商铺是否打开
int is_store_open() { return StoreOpen; }

// 函数：打开商铺
int open_store( int flag ) { return StoreOpen = flag; }

//获取上架宠物位置
string get_store_beast_pos()
{
	int i;
	for(i=0;i<3;i++)
	{
		if ( Store[sprintf("%2d",100+i)] ) continue;
		return sprintf("%2d",100+i);
	}	
	return 0;
}

//获取上架宠物ID
string get_store_beast_id(string key) { return Beast[key]; }

//设定上架宠物ID
string set_store_beast_id(string key, string id) { return Beast[key] = id; }

//删除上架宠物ID
void delete_store_beast_id(string key) { map_delete(Beast,key); }


inherit DBASE_F;

private static int MapId;               // 数字标识
private static int MapId2;              // 数字标识(客户端)
private static string MapName;          // 地图名称

// 函数：场景识别函数
int is_scene() { return 1; }

// 函数：虚拟场景识别
int is_virtual_scene() { return 1; }

// 函数：获取标识
int get_id() { return MapId; }

// 函数：设置标识
int set_id( int id ) { return MapId = id; }

// 函数：获取标识(客户端)
int get_client_id() { return MapId2; }

// 函数：设置标识(客户端)
int set_client_id( int id ) { return MapId2 = id; }

// 函数：获取名字
string get_name() { return MapName; }

// 函数：设置名字
string set_name( string name ) { return MapName = name; }

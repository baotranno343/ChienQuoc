
#define SAVE_FILE       "data/city/08" SAVE_EXTENSION

inherit "/inh/std/city";

// 函数：获取地图标识
int get_map_id() { return 80; }

// 函数：获取城市名称
string get_name() { return "Chu Quốc"; }

// 函数：构造处理
void create() { }

// 函数：获取合法坐标
int get_xy_point( int flag ) { return 080 * 1000000 + efun::get_xy_point(080, flag); }

// 函数：取存盘文件名
string get_save_file() { return SAVE_FILE; }

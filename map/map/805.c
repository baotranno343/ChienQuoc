
// 自动生成：/make/std/makemap

#include <map.h>

inherit SCENE;

// 禁止PK
int get_no_fight() {return 1;}

// 函数：获取标识
int get_id() { return 805; }

// 函数：获取标识(客户端)
int get_client_id() { return 805; }

// 函数：获取名字
string get_name() { return "Trạm Dịch Duyên Phận"; }

// 函数：获取地型类别
int get_map_type() { return FIELD_MAP; }

// 函数：构造处理
void create()
{
        object map = this_object();
        object npc;

        set_map_object( map, get_id() );

 
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

}


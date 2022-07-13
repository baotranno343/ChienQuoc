
#include <npc.h>
#include <ansi.h>
#include <map.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

void do_welcome( string arg );

void do_look(object me) {};

// 函数：获取人物造型
int get_armor_code() { return 10000; } 

int get_ride() {return 6;}

// 函数：构造处理
void create()
{
        set_name( "紫毛" );
        setup();     
}

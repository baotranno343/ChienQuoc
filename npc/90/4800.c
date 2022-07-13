
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <cmd.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取门派名称
string get_fam_name() { return "Đường Môn"; }

// 函数：获取人物造型
int get_char_picid() { return 7102; }

// 函数：获取门派顺序
int get_fam_order() { return 7; }

void do_info();
void do_init(string arg);

// 函数：构造处理
void create()
{
        set_name( "Đường Lão Bà Bà" );    
        set_2( "talk", ([
                "init"                : (: do_init :),                  
        ])); 
        setup();
}

// 函数：点击出现界面
void do_look( object who ) { TASK_MASTER_D->do_look( who, this_object() ); }
//洗点
void do_init(string arg) {TASK_MASTER_D->do_init_gift( this_player(), this_object(),arg );}
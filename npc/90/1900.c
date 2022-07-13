
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <cmd.h>
#include <ansi.h>

inherit OFFICER;
string accept_quest(string arg);
// 函数：获取门派名称
string get_fam_name() { return "Đào Hoa Nguyên"; }

// 函数：获取人物造型
int get_char_picid() { return 5805; }

// 函数：获取门派顺序
int get_fam_order() { return 8; }

// 函数：构造处理
void create()
{
        set_name( "Thôn Trang Hộ Vệ" );
        set_2( "talk", ([
                "accept_quest"            : (: accept_quest :),  
        ]));
        setup();
}

// 函数：点击出现界面
void do_look( object who ) { TASK_MASTER_D->do_look_quest8( who, this_object() ); }
void accept_quest(string arg) { TASK_MASTER_D->accept_quest8( this_player(), this_object(),arg); }


#include <npc.h>
#include <equip.h>
#include <cmd.h>

inherit OFFICER;

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 9306; }

// 函数：构造处理
void create()
{
        set_name( "Võ Giáo Đầu" );

        set_skill(0111, 40);
        set_skill(0121, 40);
        set_skill(0131, 40);
        set_skill(0141, 40);
        set_skill(0151, 40);
        set_skill(0161, 40);

        setup();
}

// 函数：技能学习界面
void do_look( object who )
{
        LEARN_CMD->learn_menu( who, this_object() );
}

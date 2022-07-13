
#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 2100; }

// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Tinh Quặng Sắt Thạch");

        setup();
}

// 函数：对话处理
void do_look( object who )
{

	if( who->get_legend(TASK_05,10) && !who->get_legend(TASK_05,11) )
	{
		if (get_effect(who, EFFECT_MINE)) return;
		send_user(who, "%c%c%w%s", 0x5a, 0, 10, "Khai thác.....");
		set_effect(who, EFFECT_MINE, 10);
		who->set_save_2("mine",sprintf("%x#",getoid(this_object())));
	}

}

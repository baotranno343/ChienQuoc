
#include <npc.h>
#include <cmd.h>
#include <ansi.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5420; }

// 函数：构造处理
void create()
{
        set_name("云游商人");
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	send_user( who, "%c%c%w%s", ':', 3, 5420,"云游商人:\n    哈哈，我是假的啦！\n"ESC"离开" );
}

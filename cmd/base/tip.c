
#include <ansi.h>

// 函数:命令处理
int main( object me, string arg )
{   
	if (arg=="reset")
	{
		me->delete_save("tipstatus");
		return 1;
	}
	if (arg=="?")
	{
		"/quest/help"->send_level_tips2(me, me->get_level());
		return 1;
	}     
	else   
		"/quest/help"->send_help_tips(me, to_int(arg));
        return 1;
}

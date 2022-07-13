#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
	string com,arg1;
	
	if ( sscanf(arg,"%s %s",com,arg1) != 2 )
		com = arg;
	if ( com == "hide" )
		me->hide_title();
	else if ( com == "show" )
		me->show_title(arg1);
        
        return 1;
}
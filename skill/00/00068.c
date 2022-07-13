
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM    00068
#define PF_START       "00068"
#define PF_NAME        "Hoạt động Thi đấu"

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\n Chức năng đặc biệt dành cho Game Master.\n "; 
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
	if ( !is_god(me) )
	{
		notify("Game Master mới có thể sử dụng!");
		return 1;
	}
		"cmd/gm/gmmap"->main(me,0);
        return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数：能否使用指令
void can_perform( object me )
{
		send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}

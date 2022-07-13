
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM    00075
#define PF_START       "00075"
#define PF_NAME        "Tỷ Thý"

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\n Chức năng giúp người chơi có thể tỷ thý với nhau.\n "; 
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
	int gender,gender1,p,i,z;
	object item;
	string result,cmd1;
	gender = me->get_gender();
	gender1 = me->get_gender() == 1 ? 0 : 1000;
		if ( me->is_user() ) return 1;
		if ( arg=="" )
		{
		if (  me->get("tythyben")>0 ) return 1;
        send_user( me, "%c%c%d%s", '?', 16, 6, "Xin nhập ID muốn tỷ thý : \n" ESC "tythy ?.%s\n" );
		}
 
        return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_ME_7; }

// 函数：能否使用指令
void can_perform( object me )
{
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}


#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM    00071
#define PF_START       "00071"
#define PF_NAME        "Shop Linh Thạch"

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\n Shop Linh Thạch (Nên để vào thanh phím tắt 2).\n "; 
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
 
	int type;
	object * objs, target;
	int i, size;
				  	
	if ( arg=="" )
		{	
	objs = children("/npc/test/BaoKho_HoTro2");	
	
	size = sizeof(objs);
	if (size==0) return 0;
	for (i=0;i<size;i++)
	{
		if (objectp(objs[i]) )
		{
			target = objs[i];
			break;
		}
	}
	if (!target) return 0;	
//	me->set("pawn_time", time());
	"/cmd/std/list3"->main(me, sprintf("%x#", getoid(target)));
            return 1; 
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

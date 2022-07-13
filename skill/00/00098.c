
#include <ansi.h>
#include <skill.h>

#define THIS_PERFORM    00098
#define PF_START       "00098"
#define PF_NAME        "Sử dụng Quản Khố"

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "[ " PF_NAME " ]\n Chức năng đặc biệt để mở ra Kho chứa đồ của Quản Khố.\n "; 
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
	int type;
	object * objs, target;
	int i, size;
		
		if ( arg=="" )
		{	
        	
	if (get_z(me)==001)
	objs = children("/npc/base/0001");
	else if (get_z(me)==010)
	objs = children("/npc/base/1001");
	else if (get_z(me)==020)
	objs = children("/npc/base/2001");
	else if (get_z(me)==030)
	objs = children("/npc/base/3001");
	else if (get_z(me)==040)
	objs = children("/npc/base/4001");
	else if (get_z(me)==050)
	objs = children("/npc/base/5001");
	else if (get_z(me)==060)
	objs = children("/npc/base/6001");
	else if (get_z(me)==070)
	objs = children("/npc/base/7001");
	else if (get_z(me)==080)
	objs = children("/npc/base/8001");
	else if (get_z(me)==549)
	objs = children("/npc/base/0911");
	else
	objs = children("/npc/base/1001");
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
	me->set("pawn_time", time());
	"/cmd/std/pawn"->do_list(me, sprintf("%x#", getoid(target)), 1);
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

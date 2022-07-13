#include <item.h>
#include <effect.h>
#include <skill.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

inherit "/inh/equip/equip";

#define SKILL_LEVEL     1

// 函数:叠加上限
int get_max_combined() { return 1; }

// 函数:成品编号
int get_fin_type() { return 1633; }

// 函数:构造处理
void create()
{
        set_name( "Đương Phô Liên Tiếp Khí" );
        set_picid_1(4203);
        set_picid_2(4203);
        set_value(3300);
        set_amount(1);
}

// 函数:获取描述
string get_desc() 
{ 
	string color;
	object me = this_player();
	if (me->get_skill(660)<SKILL_LEVEL) color = HIR + sprintf("Yêu cầu Cơ quan cấp bậc: %d\n", SKILL_LEVEL);
	else color = sprintf("Yêu cầu Cơ quan cấp bậc: %d\n", SKILL_LEVEL);	
        return color + "Có thể vĩnh viễn mở ra 1 kho đồ trong Quản Khố để cất giữ vật phẩm";
}

// 函数:使用效果
int get_use_effect( object me ) { return __FILE__ ->get_use_effect_callout(me); }

// 函数:使用效果(在线更新)
int get_use_effect_callout( object me )
{
	int type;
	object * objs, target;
	int i, size;	
	
        if (me->get_skill(660)<SKILL_LEVEL)
        {
                send_user( me, "%c%s", '!', sprintf("Ngươi cơ quan cấp bậc không đủ %d, vô pháp sử dụng %s", SKILL_LEVEL, get_name()) );
                return 0;
        }	
        if(time()-me->get("pawn_time")<300)
        	return 0;
        	
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
        set_effect(me, EFFECT_PROGRESS2, 300);
        me->set_progress_file(__FILE__);   
	send_user(me, "%c%c%w%s", 0x5a, 0, 300, "Đang sử dụng Bảo...");	
        return 1;
}

// 函数:法术处理
int into_effect( object me , string arg)
{
	me->set("pawn_time", 0);
	send_user(me, "%c%c%c", 0x5a, 1, 1);
	return 1;
}

void effect_break(object me, string arg)
{
	me->set("pawn_time", 0);
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	set_effect(me, EFFECT_PROGRESS2, 0 );	
}
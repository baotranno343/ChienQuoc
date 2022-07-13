#include <effect.h>
// 函数：获取人物造型
int get_char_picid() { return 2108; }

// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：对话处理
void do_look( object who )
{
	if( get_effect(who, EFFECT_CHAR_INVISIBLE) ) set_effect_2(who, EFFECT_CHAR_INVISIBLE, 1, 1 );
	if( get_effect_3(who, EFFECT_CHAR_LAZY) ) return;
	if( get_effect_3(who, EFFECT_CHAR_SLOW) ) return;
	if( get_effect_3(who, EFFECT_CHAR_DREAM_1) ) return;
	if( get_effect_3(who, EFFECT_CHAR_CHAOS) ) return;
	if( get_effect_3(who, EFFECT_CHAR_SHUT) ) return;
	if( get_effect_3(who, EFFECT_CHAR_FAINT) ) return;
	if( get_effect_3(who, EFFECT_CHAR_FAINT_2) ) return;
	if( get_effect_3(who, EFFECT_SLEEP) ) return;
	if( get_effect_3(who, EFFECT_MAGIC_4243) ) 
	{
		send_user( who, "%c%s", '!', "Đang biến thân không thể mở Bảo Rương");               
		return;
	}
	if (who->get_online_rate()<100)
	{
		send_user(who, "%c%s", ';', "非健康时间不能开宝箱.");
		return 0;
	}	
	"/sys/item/box"->do_look(who, this_object());
}

// 函数：对话处理
void into_effect( object who, string arg )
{
	if( get_effect_3(who, EFFECT_CHAR_LAZY) ) 
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}
	if( get_effect_3(who, EFFECT_CHAR_SLOW) )
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}	
	if( get_effect_3(who, EFFECT_CHAR_DREAM_1) )
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}	
	if( get_effect_3(who, EFFECT_CHAR_CHAOS) )
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}	
	if( get_effect_3(who, EFFECT_CHAR_SHUT) )
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}	
	if( get_effect_3(who, EFFECT_CHAR_FAINT) )
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}	
	if( get_effect_3(who, EFFECT_CHAR_FAINT_2) )
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}	
	if( get_effect_3(who, EFFECT_SLEEP) )
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}	
	if( get_effect_3(who, EFFECT_MAGIC_4243) )	
	{
		send_user(who, "%c%c%c", 0x5a, 1, 0);
		return;
	}	
	"/sys/item/box"->into_effect(who, arg);
}

void effect_break(object who, string arg)
{
	set_effect(who, EFFECT_PROGRESS2, 0);
	send_user(who, "%c%c%c", 0x5a, 1, 0);
}

void wait_for_reset(object me)
{
	me->remove_from_scene();
	call_out( "reset_stuff", me->get("reset_time"), me );
}

void reset_stuff(object me)
{
	int z, x, y, p;
	z = me->get("z");
	if (z==0) 
	{
		z = 265;
		me->set("z", 265);
	}
	p = "/sys/item/box"->get_xy(z);
	me->add_to_scene(z, p / 1000, p % 1000, 3);
	me->set("time", 1);
}
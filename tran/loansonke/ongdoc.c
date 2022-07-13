#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <public.h>

inherit BADMAN;
int get_char_picid() { return 0150; }
int is_loansonke() { return 1; }
void create()
{
	object me = this_object();
	set_name("Ong Độc");
	set_level(1);
	set_max_hp(1);
	set_ap(1);
	set_dp(1);
	set_cp(1);
	set_pp(1);
	set_sp(1);
	set_walk_speed(9);
	set_attack_speed(1);

	setup();
	set_heart_timer(me, set_heart_timer_2(me, getoid(me) % 10)); // 心跳随机
	set_heart_loop(me, 10);										 // 循环心跳：１秒钟
	me->heart_beat();
	set_heart_beat(1);
}
int can_fight(object player)
{
	return 0;
}

int can_be_fighted(object player)
{
	return 0;
}

void heart_beat() {}
void heart_beat_loop(int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) { __FILE__->heart_beat_loop_callout(this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout(object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8) // 每１秒处理
{
	GO_CMD->main_npc(me, sprintf("%d", random(8) + 1));
}

#include <npc.h>
#include <ansi.h>
#include <public.h>

inherit BADMAN;
int get_char_picid() { return 0011; }
int is_yutu() { return 1; }
void create()
{
	set_name("月兔");
        set_level(1);
	set_max_hp(1);
	set_ap(1);
	set_dp(1);
	set_cp(1);
	set_pp(1);
	set_sp(1);
	set_walk_speed(1);
	set_attack_speed(1);

        setup();	
}
int can_fight(object player)
{
	return 0;
}

int can_be_fighted(object player)
{
	return 0;
}
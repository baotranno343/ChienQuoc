#include <ansi.h>
#include <city.h>
#include <npc.h>
#include <equip.h>
#include <skill.h>

inherit BADMAN;

// 函数：传递坐标
//int is_send_position() { return 1; }

// 函数：获取人物造型
// int get_char_picid()
// {
// 	int rate;
// 	rate = random(2);
// 	if (rate == 0)
// 		return 0052;
// 	else
// 		return 0201;
// }
int set_fight_status(int level)
{

	add_dp(level);
	add_pp(level);
}
// 函数：构造处理
void create()
{
	set_name("Cổ Mộ Tay Sai");

	set_max_hp(10);
	set_max_mp(0);
	set_ap(1);
	set_dp(1);
	set_cp(1);
	set_pp(1);
	set_sp(1);
	set_level(30);
	set_attack_speed(15);
	set_walk_speed(6);
	set_max_seek(4);

	setup();
	set_char_type(FIGHTER_TYPE); // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

//死亡奖励
void win_bonus(object who)
{
	int exp, level1, level2;
	level1 = get_level();
	level2 = who->get_level();
	exp = correct_exp_bonus(level1, level1 - level2, 50);
	who->add_exp(exp);
	who->add_potential(1);
	//tell_user( who, "您击毙%s，经验 %+d, 潜能 %+d。", get_name(), exp, 1 );
}
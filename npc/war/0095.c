
#include <npc.h>
#include <equip.h>
#include <skill.h>

inherit COMRADE;

// 函数：是否允许移动
int is_moveable() { return 0; }    // 禁止使用 go 命令

int is_anti_effect() {return 1;}   // 禁止effect

// 函数：跟随对手(心跳之中调用)
void follow_user() { }    // 禁止跟随敌人

int get_comrade_type() {return 95;}

// 函数：获取人物造型
int get_char_picid() { return 9955; }

// 函数：构造处理
void create()
{
        set_name( "总管" );

        set_max_hp(100000);  set_max_mp(0);
        set_ap(1000);  set_dp(1400);  
        set_cp(  0);  set_pp(1100);  
        set_sp(0);

        set_walk_speed(10);  set_attack_speed(10);
        set_max_seek(10);    // 全屏搜索

        setup();

        set_char_type(FIGHTER_TYPE_2);
}

// 函数：获取装备代码
int get_weapon_code() { return THROWING; }

// 函数：特技攻击对手
int perform_action( object who ) { return __DIR__ "0080" ->perform_action_npc( this_object(), who ); }

// 函数：死亡奖励
void win_bonus( object who ) { NPC_BATTLE_D->manager_win_bonus( this_object(), who ); }

void upgrade(int level)
{
	int hp;
	object me = this_object();
	hp = me->get_max_hp();
        me->set_max_hp(me->get_max_hp()*14/10);
        me->add_hp(me->get_max_hp()-hp);
        me->set_level(level);
}


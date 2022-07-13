
#include <npc.h>
#include <equip.h>
#include <skill.h>

inherit BADMAN;

// 函数：获取人物造型
int get_char_picid() { return 0053; }

// 函数：构造处理
void create()
{
        set_name("Lưu manh");

        set_max_hp(400);  set_max_mp(0);
        set_ap(300);  set_dp(160);  
        set_cp(  0);  set_pp(700);  
        set_sp(500);

        set_walk_speed(5);  set_attack_speed(10);
        set_max_seek(6);

        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return THROWING; }

// 函数：特技攻击对手
int perform_action( object who ) { return PF_FILE_01611->perform_action_npc( this_object(), who ); }

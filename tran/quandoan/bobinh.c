
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>

inherit BADMAN;
int idChu;
// 函数：远程攻击的怪
// int is_caster() { return 1; }

int is_quanDoan()
{
        return 1;
}
int set_idChuQuanDoan(int id) { return idChu = id; }
int get_idChuQuanDoan() { return idChu; }
// 函数：是否允许移动
// int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：跟随对手(心跳之中调用)
// void follow_user() { }    // 禁止跟随敌人

// 函数：获取人物造型
int get_char_picid() { return 0652; }

// 函数：构造处理
void create()
{
        set_name("Sở Quân Kiếm Binh");

        set_char_type(FIGHTER_TYPE); // init_level 要用到

        set_head_color(0x0);
        set_level(100);
        set_max_hp(2000);
        set_max_mp(500);
        set_ap(500);
        set_dp(400);
        set_cp(300);
        set_pp(200);
        set_sp(200);

        set_walk_speed(3);
        set_attack_speed(10);
        set_max_seek(12);
        setup();

        set_char_type(132); // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action(object who) { return 0; } // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
// void auto_fight( object who ) { }

// 函数：任务处理(有任务时调用)
void check_legend_task(object who)
{
}
// 函数：掉宝奖励
void drop_items(object who) { __FILE__->drop_items_callout(this_object(), who); }

// 函数：掉宝奖励(在线更新)
void drop_items_callout(object me, object who)
{
}
void destroy_time(int time)
{

        call_out("destroy", time);
}

void destroy()
{

        if ("/map/city/08"->get_2(sprintf("quanDoan.%d.sl", get_idChuQuanDoan())) > 0)
        {
                "/map/city/08"->add_2(sprintf("quanDoan.%d.sl", get_idChuQuanDoan()), -1);
        }
        this_object()->remove_from_scene();
        destruct(this_object());
}
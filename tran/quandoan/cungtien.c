
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
int idChu;
// 函数：远程攻击的怪
int is_caster() { return 0; }

int is_quanDoan()
{
        return 1;
}
int set_idChuQuanDoan(int id) { return idChu = id; }
int get_idChuQuanDoan() { return idChu; }

// 函数：获取人物造型
int get_char_picid() { return 9969; }

// 函数：构造处理
void create()
{
        set_name("Cung Binh");

        set_char_type(FIGHTER_TYPE); // init_level 要用到

        set_head_color(0x0);

        NPC_ENERGY_D->init_level(this_object(), 62 + random(2)); //
        set_max_seek(12);

        setup();

        set_char_type(132); // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
// int perform_action( object who ) { return PF_FILE_04232->perform_action_npc( this_object(), who ); }
int perform_action(object who) { return 0; }

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
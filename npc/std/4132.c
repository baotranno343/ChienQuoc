
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <action.h>

inherit SLAVE;

int get_max_level0() { return 3; }

// 函数：获取召唤兽类型
int get_zombie_type() { return SOLDIER_TYPE_2; } // 判断种类

// 函数：构造处理
void create()
{
        set_name("天兵");
        set_char_picid(4132);

        setup();
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// --------------------------------------------------------------- 远程调用 ----

// 函数：升级处理
void upgrade_level(int level) { __FILE__->upgrade_level_callout(this_object(), level); }

// 函数：升级处理(在线更新)
void upgrade_level_callout(object me, int level)
{
        switch (level)
        {
        default:
                me->set_char_type(SLAVE_TYPE_1);
                break;
        case 2:
                me->set_char_type(SLAVE_TYPE_2);
                break;
        case 3:
                me->set_char_type(SLAVE_TYPE_3);
                break;
        case 4:
                me->set_char_type(SLAVE_TYPE_4);
                break;
        case 5:
                me->set_char_type(SLAVE_TYPE_5);
                break;
        }
        me->set_attack_speed(20);
        me->set_walk_step(2);
        me->set_walk_speed(3);
}

// 函数：升级处理
void upgrade_level_2(int level) { __FILE__->upgrade_level_2_callout(this_object(), level); }

// 函数：升级处理(在线更新)
void upgrade_level_2_callout(object me, int level)
{
        object owner;
        int hp, cp, pp, dp, level0;

        if (level > 1)
                if (objectp(owner = me->get_owner()) && owner->is_user())
                {
                        level0 = me->get_level_0();
                        cp = me->get_ap() * 10 / 100;
                        pp = me->get_pp() * 10 / 100;
                        dp = me->get_dp() * 10 / 100;
                        me->add_max_hp(60);
                        me->set_hp(me->get_max_hp());
                        me->set_mp(me->get_max_mp());
                        me->add_ap(10 + cp);
                        me->add_dp(60 + dp);
                        me->add_pp(10 + pp);
                }
}

void do_after_attack(object who)
{
        object me = this_object();
        object *user;
        int level, level0, rate;
        level = me->get_level_2();
        level0 = me->get_level_0();
        rate = level0 / 20 + 5 * level;
        if (random(100) < rate && !get_effect(who, EFFECT_CHAR_WOUND_0))
        {
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_WOUND, 10);
                send_user(who, "%c%w%w%c", 0x81, 9020, get_effect_3(who, EFFECT_CHAR_WOUND), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9020, 1, EFFECT_BAD);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9020, 1, OVER_BODY, PF_LOOP);
                if (who->is_user())
                {
                        USER_ENERGY_D->count_ap(who);
                        USER_ENERGY_D->count_dp(who);
                }
        }
        if (time() - me->get("pf") > 15)
        {
                me->set("pf", time());
                who->set_enemy(me);
                who->set("2122", time());
                who->init_enemy_damage(me, 1);
        }
}
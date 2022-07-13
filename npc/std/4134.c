#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <action.h>

inherit SLAVE;

int get_max_level0() { return 3; }

// 函数：获取召唤兽类型
int get_zombie_type() { return ZOMBIE_TYPE_1; } // 判断种类

// 函数：构造处理
void create()
{
        set_name("僵尸");
        set_char_picid(4134);

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
        }
        me->set_attack_speed(10);
        me->set_walk_speed(2);
        me->set_walk_step(2);
}

// 函数：升级处理
void upgrade_level_2(int level) { __FILE__->upgrade_level_2_callout(this_object(), level); }

// 函数：升级处理(在线更新)
void upgrade_level_2_callout(object me, int level)
{
        object owner;
        int hp, cp, pp, dp;

        if (level > 1)
                if (objectp(owner = me->get_owner()) && owner->is_user())
                {
                        cp = me->get_ap() * 10 / 100;
                        pp = me->get_pp() * 10 / 100;
                        dp = me->get_dp() * 10 / 100;
                        me->add_max_hp(80);
                        me->set_hp(me->get_max_hp());
                        me->set_mp(me->get_max_mp());
                        me->add_ap(25 + cp);
                        me->add_dp(8 + dp);
                        me->add_pp(20 + pp);
                        me->add_sp(10);
                }
}

void do_after_attack(object who)
{
        object me = this_object();
        object *user;
        int level, level0, rate;
        level = me->get_level_2();
        level0 = me->get_level_0();
        rate = level0 / 10 + 3 * level;
        if (random(100) < rate)
        {
                who->set_poison(30);
                set_effect_2(who, EFFECT_CHAR_POISON, 10, 2);
                send_user(who, "%c%w%w%c", 0x81, 9096, get_effect_3(who, EFFECT_CHAR_POISON), EFFECT_BAD);
                send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9096, 1, EFFECT_BAD);
        }
}
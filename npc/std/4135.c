
#include <npc.h>
#include <equip.h>

inherit SLAVE;

int get_max_level0() { return 3; }

// 函数：获取召唤兽类型
int get_zombie_type() { return ZOMBIE_TYPE_2; } // 判断种类

// 函数：构造处理
void create()
{
        set_name("豆兵");
        set_char_picid(4135);

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
        me->set_walk_step(2);
        me->set_walk_speed(3);
        me->set_attack_speed(15);
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
                        me->add_max_hp(150);
                        me->set_hp(me->get_max_hp());
                        me->set_mp(me->get_max_mp());
                        me->add_ap(5 + cp);
                        me->add_dp(40 + dp);
                        me->add_pp(40 + pp);
                }
}

void do_after_attack(object who)
{
        object me = this_object();
        object *user;
        int level, level0, rate;
        if (time() - me->get("pf") > 15)
        {
                me->set("pf", time());
                who->set_enemy(me);
                who->set("2122", time() + 4);
                who->init_enemy_damage(me, 1);
        }
}

// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <item.h>

#define THIS_SKILL 0221
#define THIS_PERFORM 02210
#define PF_START "01211"
#define PF_NAME "Đơn Đao Trực Nhập"

#define SKILL_LEVEL 1
#define TIME_INTERVAL 1
#define SUB_MP 6 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 3
#define ADD_AP 10 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 10
#define SUB_EFFECT (10 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 8 * 2)

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数：获取法力
int get_sub_mp(object me) { return SUB_MP; }

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n    Chiêu thức đao pháp cơ bản, gia tăng sát thương khi tấn công một mục tiêu. Sử dụng đối với quái vật sẽ giảm 10 điểm Ngoại Kháng.";
        cur_level = (level - SKILL_LEVEL) / 10 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Chiêu thức đao pháp cơ bản, gia tăng %d sát thương khi tấn công một mục tiêu. Sử dụng đối với quái vật sẽ giảm %d điểm Ngoại Kháng.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d sát thương. Sử dụng đối với quái vật sẽ giảm %d điểm Ngoại Kháng.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP, SUB_EFFECT, cur_level * 10 + SKILL_LEVEL, ADD_AP + 10, SUB_EFFECT + 2);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        int z, d, x0, y0;
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1; // 小心准备 level

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 level
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

        if (me->get_weapon_code() != BLADE)
                if (me->get_weapon_code() != SWORD)
                {
                        printf(ECHO "Sử dụng \"" PF_NAME "\" phải trang bị đao hoặc kiếm");
                        return 1;
                }
        //}
        z = get_z(me);
        if (who)
        {
                if (!inside_screen_2(me, who))
                        return 1;

                x = get_x(who);
                y = get_y(who);
        }
        else if (objectp(who = me->get_enemy_2()) && inside_screen_2(me, who))
        {
                x = get_x(who);
                y = get_y(who);
        }
        else
                return 1;
        if (get_z(who) != z)
                return 1;
        if (!who->can_be_fighted(me) || !me->can_fight(who))
                return 1;
        x0 = get_x(me);
        y0 = get_y(me);

        me->set_enemy_2(who); // 远程目标锁定

        me->add_mp(-mp);

        //      set_heart_state(me, MAGIC_STAT);
        //      set_heart_count_2(me, 9);

        if (me->get_gender() != 1 && !CHAR_FIGHT_D->attack_action(me, who, 2010))
                return 1;
        else if (me->get_gender() == 1 && !CHAR_FIGHT_D->attack_action(me, who, 1010))
                return 1;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                  get_x(me), get_y(me), getoid(who), 21175, 1, OVER_BODY);

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21171, 1, OVER_BODY, PF_ONCE);

        CHAR_FIGHT_D->attack_done(me, who, HIT_BLADE, ADD_AP); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 40);

        me->set_enemy_3(who);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);
        me->add_2("go_count.count2", 7);
        // zz
        if (!CHAR_FIGHT_D->attack_action(me, who, 1060))
                return 1;
        me->set_cast_file(__FILE__);
        me->set_cast_arg(sprintf("%s", who->get_char_id()));
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());
        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_LOOP);

        return 1;
}

int perform_action(object me, object who)
{
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1; // 小心准备 me

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

        /*    if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        } */

        if (me->get_weapon_code() == UNARMED)
        {
                printf(ECHO "Sử dụng \" %s \" phải trang bị binh khí.", PF_NAME);
                return 1;
        }

        if (!CHAR_FIGHT_D->attack_action(me, who, 1060))
                return 1;

        me->add_mp(-mp);
        //     me->add_yuan( -SUB_YUAN );
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());
        return 2; // 执行成功
}

// 函数：特殊技处理
int perform_done(object me, object who)
{
        object *inv;
        int level, mp, ret, i, time;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        //      if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        /*      if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }       */

        /*      if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }       */

        if (me->get_weapon_code() == UNARMED)
        {
                printf(ECHO "Sử dụng \" %s \" phải trang bị binh khí.", PF_NAME);
                return 1;
        }

        me->set_perform_file(0);
        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who),
                  25163, 1, OVER_BODY, 25164, 1, OVER_BODY, PF_ONCE);
        me->set("add_damage", ADD_AP);
        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_NONE); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 80);
        me->set("add_damage", 0);
        if (!who)
                return 2; // 执行成功

        if (ret > 0) // rate - who->get_immunity()
        {
                if (get_effect_3(who, EFFECT_NO_CLOTH_0))
                        return 2;
                send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21142, 1, OVER_BODY, PF_ONCE); // 技能成功
                time = 0;
                set_effect(who, EFFECT_NO_CLOTH, time);
                set_effect(who, EFFECT_NO_CLOTH_0, time + 0);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user(who, "%c%w%w%c", 0x81, 2516, time, EFFECT_BAD);
                send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 2516, 1, EFFECT_BAD);
                if (who->is_user())
                {
                        USER_ENERGY_D->count_all_prop(who);
                }
                else
                {
                        who->set("02210", SUB_EFFECT);
                        who->add_dp(-SUB_EFFECT);
                }
        }

        return 2; // 执行成功
}

// 函数：特殊技处理
int cast_done(object me)
{
        object *inv;
        int level, mp, ret, i, time;
        string arg;
        object who;

        if (!stringp(arg = me->get_cast_arg()))
                return 1;
        if (!objectp(who = find_char(arg)))
                return 1;
        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who),
                  25163, 1, OVER_BODY, 25164, 1, OVER_BODY, PF_ONCE);
        me->set("add_damage", ADD_AP);
        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_NONE); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 80);
        me->set("add_damage", 0);
        if (!who)
                return 2; // 执行成功

        if (ret > 0) // rate - who->get_immunity()
        {
                if (get_effect_3(who, EFFECT_NO_CLOTH_0))
                        return 2;
                send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21142, 1, OVER_BODY, PF_ONCE); // 技能成功
                time = 0;
                set_effect(who, EFFECT_NO_CLOTH, time);
                set_effect(who, EFFECT_NO_CLOTH_0, time + 0);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user(who, "%c%w%w%c", 0x81, 2516, time, EFFECT_BAD);
                send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 2516, 1, EFFECT_BAD);
                if (who->is_user())
                {
                        USER_ENERGY_D->count_all_prop(who);
                }
                else
                {
                        who->set("02210", SUB_EFFECT);
                        who->add_dp(-SUB_EFFECT);
                }
        }

        return 2; // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform(object me)
{
        int interval;
        string name;

        if (me->get_skill(THIS_SKILL) < SKILL_LEVEL)
        {
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME);
                return;
        }
        name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 + 1);
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        if (me->get_gender() == 1)
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 1, 10, 7, 0);
        else
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 2, 10, 7, 0);
}

void into_effect(object me)
{
        if (me->is_user())
        {
                CHAR_CHAR_D->init_loop_perform(me);
                USER_ENERGY_D->count_all_prop(me);
                send_user(me, "%c%w%w%c", 0x81, 2516, 0, EFFECT_BAD);
        }
        else
        {
                me->add_dp(me->get("02210"));
                me->set("02210", 0);
        }
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 2516, 0, EFFECT_BAD);
}
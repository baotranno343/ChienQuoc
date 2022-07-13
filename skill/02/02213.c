
// 法术＋出招  TIPS:[PF_CAST_HIT]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL 0221
#define THIS_PERFORM 02213
#define PF_START "02213"
#define PF_NAME "Phá Ma Trảm"

#define SKILL_LEVEL 13
#define TIME_INTERVAL 2
#define SUB_MP 20 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 5
#define ADD_AP2 (20 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 10)

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        int cur_level;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 13 cấp\n    Dùng Đao khí phá vỡ tâm ma của đối thủ, tăng thêm 20 điểm sát thương khi tấn công đồng thời phá bỏ 1 bùa chú hộ thể của mục tiêu.";
        cur_level = (level - SKILL_LEVEL) / 10 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Dùng Đao khí phá vỡ tâm ma của đối thủ, tăng thêm %d điểm sát thương khi tấn công đồng thời phá bỏ 1 bùa chú hộ thể của mục tiêu.\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d điểm Ngoại Công.\n",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP2, cur_level * 10 + SKILL_LEVEL, ADD_AP2 + 10);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        int z, d, x0, y0;
        int level, mp, ret;
        object *user;
        int i, size, time, pos;
        int *all = ({
            EFFECT_CHAR_ADD_DP,
            EFFECT_EXCITE,
            EFFECT_REBOUND,
            EFFECT_USER_DP,
            EFFECT_USER_SP,
            EFFECT_DODGE,
            EFFECT_03484,
            EFFECT_CHAR_MOVE,
            EFFECT_CHAR_HALFGOD2,
            EFFECT_CHAR_POWERUP,
            EFFECT_CHAR_POWERUP2,
            EFFECT_CHAR_POWERUP3,
        });
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

        if (me->get_gender() != 1 && !CHAR_FIGHT_D->attack_action(me, who, 1070))
                return 1;
        else if (me->get_gender() == 1 && !CHAR_FIGHT_D->attack_action(me, who, 2070))
                return 1;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                  get_x(me), get_y(me), getoid(who), 21175, 1, OVER_BODY);

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 22131, 1, OVER_BODY, PF_ONCE);

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_BLADE, ADD_AP2); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 30);
        me->set_enemy_3(who);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);
        me->add_2("go_count.count2", 7);
        if (!who)
                return 1;
        if (ret > 0)
        {

                size = sizeof(all);
                time = 0;
                pos = -1;
                for (i = 0; i < size; i++)
                        if (time < get_effect_3(who, all[i]))
                        {
                                time = get_effect_3(who, all[i]);
                                pos = i;
                        }
                if (who->get_perform(PF_FLAG_03172))
                {
                        if (time() - who->get_perform(PF_FLAG_03172) > time)
                        {
                                who->delete_perform(PF_FLAG_03172);
                                pos = -1;
                                CHAR_CHAR_D->init_loop_perform(who);
                                send_user(who, "%c%w%w%c", 0x81, 3172, 0, EFFECT_GOOD);
                                send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 3172, 0, EFFECT_GOOD);
                        }
                }
                if (pos != -1)
                {
                        if (all[pos] < 96)
                                set_effect(who, all[pos], 1);
                        else
                                set_effect_2(who, all[pos], 1, 1);
                }
        }
        return 1;
}

// 函数：特殊技处理
int cast_done(object me)
{
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
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 2, 70, 7, 0);
        else
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 1, 70, 7, 0);
}

int perform_action_npc(object me, object who)
{
        int z, d, x0, y0, x, y;
        int level, mp, ret;
        object *user;
        int i, size, time, pos;
        int *all = ({
            EFFECT_CHAR_ADD_DP,
            EFFECT_EXCITE,
            EFFECT_REBOUND,
            EFFECT_USER_DP,
            EFFECT_USER_SP,
            EFFECT_DODGE,
            EFFECT_03484,
            EFFECT_CHAR_MOVE,
            EFFECT_CHAR_HALFGOD2,
            EFFECT_CHAR_POWERUP,
            EFFECT_CHAR_POWERUP2,
            EFFECT_CHAR_POWERUP3,
        });
        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1; // 小心准备 level

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

        if (me->get_gender() != 1 && !CHAR_FIGHT_D->attack_action(me, who, 1070))
                return 1;
        else if (me->get_gender() == 1 && !CHAR_FIGHT_D->attack_action(me, who, 2070))
                return 1;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                  get_x(me), get_y(me), getoid(who), 21175, 1, OVER_BODY);

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 22131, 1, OVER_BODY, PF_ONCE);

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_BLADE, ADD_AP2); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 30);
        me->set_enemy_3(who);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);
        if (!who)
                return 1;
        if (ret > 0)
        {

                size = sizeof(all);
                time = 0;
                pos = -1;
                for (i = 0; i < size; i++)
                        if (time < get_effect_3(who, all[i]))
                        {
                                time = get_effect_3(who, all[i]);
                                pos = i;
                        }
                if (who->get_perform(PF_FLAG_03172))
                {
                        if (time() - who->get_perform(PF_FLAG_03172) > time)
                        {
                                who->delete_perform(PF_FLAG_03172);
                                pos = -1;
                                CHAR_CHAR_D->init_loop_perform(who);
                                send_user(who, "%c%w%w%c", 0x81, 3172, 0, EFFECT_GOOD);
                                send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 3172, 0, EFFECT_GOOD);
                        }
                }
                if (pos != -1)
                {
                        if (all[pos] < 96)
                                set_effect(who, all[pos], 1);
                        else
                                set_effect_2(who, all[pos], 1, 1);
                }
        }
        return 1;
}
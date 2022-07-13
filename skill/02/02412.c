
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL 0241
#define THIS_PERFORM 02412
#define PF_START "02412"
#define PF_NAME "Trường Giang Nộ Thủy"

#define SKILL_LEVEL 12
#define TIME_INTERVAL 2
#define SUB_YUAN 2
#define SUB_MP 0
#define ADD_AP (12 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 5 / 2)

// 函数：获取法力
int get_sub_mp(object me)
{
        int level = me->get_skill(THIS_SKILL);
        return SUB_MP;
}

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 12\n Chiêu thức mãnh liệt cuồn cuộn như nước chảy, làm cho đối thủ trong 8 giây mất đi tổng cộng 96 điểm Khí Huyết.", PF_NAME);
        cur_level = (level - SKILL_LEVEL) / 10 + 1;
        if (cur_level % 2 == 0)
                result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Chiêu thức mãnh liệt cuồn cuộn như nước chảy, làm cho đối thủ trong 8 giây mất đi tổng cộng %d điểm Khí Huyết.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n Làm đối thủ 8 giây mất đi tổng cộng %d điểm Khí huyết.",
                                 PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP * 8, cur_level * 10 + SKILL_LEVEL, (ADD_AP + 3) * 8);
        else
                result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Chiêu thức mãnh liệt cuồn cuộn như nước chảy, làm cho đối thủ trong 8 giây mất đi tổng cộng %d điểm Khí Huyết.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n Làm đối thủ 8 giây mất đi tổng cộng %d điểm Khí huyết.",
                                 PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP * 8, cur_level * 10 + SKILL_LEVEL, (ADD_AP + 2) * 8);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        int z, d, x0, y0;
        int level, mp, ret;
        object *user;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1; // 小心准备 level

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 level
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }
        if (me->get_yuan() < SUB_YUAN)
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN);
                return 1;
        }
        if (me->get_weapon_code() == UNARMED)
        {
                printf(ECHO "Sử dụng \" %s \" phải trang bị binh khí.", PF_NAME);
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
                return;
        x0 = get_x(me);
        y0 = get_y(me);

        me->set_enemy_2(who); // 远程目标锁定

        me->add_mp(-mp);
        me->add_yuan(-SUB_YUAN);

        //      set_heart_state(me, MAGIC_STAT);
        //      set_heart_count_2(me, 9);

        if (!CHAR_FIGHT_D->attack_action(me, who, 1020, 1))
                return 1;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                  get_x(me), get_y(me), getoid(who), 21175, 1, OVER_BODY);

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 24121, 1, OVER_BODY, PF_ONCE);

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, 0); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 80);

        me->set_enemy_3(who);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);
        me->add_2("go_count.count2", 7);
        if (!who)
                return 1;
        if (who->is_anti_effect())
                return 2;
        if (ret > 0)
        {
                if (get_effect(who, EFFECT_CHAR_BLOOD))
                {
                        if (who->is_user() && who->get_save("char_blood") > ADD_AP)
                                return 1;
                        if (who->is_npc() && who->get("char_blood") > ADD_AP)
                                return 1;
                }
                user = get_scene_object_2(who, USER_TYPE);
                set_effect_2(who, EFFECT_CHAR_BLOOD, 8, 2);
                send_user(who, "%c%w%w%c", 0x81, 9022, get_effect_3(who, EFFECT_CHAR_BLOOD), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9022, 1, EFFECT_BAD);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9022, 1, OVER_BODY, PF_LOOP);
                if (who->is_user())
                        who->set_save("char_blood", ADD_AP);
                else
                        who->set("char_blood", ADD_AP);
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
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 1, 20, 7, 0);
}

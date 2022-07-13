
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL 0221
#define THIS_PERFORM 02211
#define PF_START "02211"
#define PF_NAME "Nghênh Phong Trảm"

#define SKILL_LEVEL 4
#define TIME_INTERVAL 2
#define SUB_MP 8 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 11 * 4
#define ADD_AP (100 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 11 * 20)
#define ADD_AP2 (15 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 11 * 10)

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

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
                return HIR + PF_NAME + "\n Võ công yêu cầu: 4 cấp\n    Đao thức như cuồng phong, tăng thêm 15 điểm sát thương và làm đối thủ Xuất Huyết trong một thời gian.";
        cur_level = (level - SKILL_LEVEL) / 11 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Đao thức như cuồng phong, tăng thêm %d điểm sát thương và làm đối thủ Xuất Huyết %d trong 20 giây.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d điểm sát thương và làm đối thủ Xuất Huyết %d trong 20 giây.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP2, ADD_AP, cur_level * 11 + SKILL_LEVEL, ADD_AP2 + 10, ADD_AP + 20);
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

        if (me->get_gender() != 1 && !CHAR_FIGHT_D->attack_action(me, who, 1020))
                return 1;
        else if (me->get_gender() == 1 && !CHAR_FIGHT_D->attack_action(me, who, 2020))
                return 1;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                  get_x(me), get_y(me), getoid(who), 21175, 1, OVER_BODY);

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21171, 1, OVER_BODY, PF_ONCE);

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_BLADE, ADD_AP2); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 70);
        me->set_enemy_3(who);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);
        me->add_2("go_count.count2", 7);
        me->set_cast_file(__FILE__);
        if (!who)
                return 1;
        if (who->is_anti_effect())
                return 2;
        if (ret > 0)
        {
                if (get_effect(who, EFFECT_CHAR_BLOOD))
                {
                        if (who->is_user() && who->get_save("char_blood") > ADD_AP / 10)
                                return 1;
                        if (who->is_npc() && who->get("char_blood") > ADD_AP / 10)
                                return 1;
                }
                user = get_scene_object_2(who, USER_TYPE);
                set_effect_2(who, EFFECT_CHAR_BLOOD, 20, 0);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user(who, "%c%w%w%c", 0x81, 9022, get_effect_3(who, EFFECT_CHAR_BLOOD), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9022, 1, EFFECT_BAD);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9022, 1, OVER_BODY, PF_LOOP);
                if (who->is_user())
                        who->set_save("char_blood", ADD_AP / 10);
                else
                        who->set("char_blood", ADD_AP / 10);
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
        name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 11 + 1);
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        if (me->get_gender() == 1)
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 2, 20, 7, 0);
        else
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 1, 20, 7, 0);
}

int perform_action_npc(object me, object who)
{
        int z, d, x0, y0, x, y;
        int level, mp, ret;
        object *user;

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

        if (me->get_gender() != 1 && !CHAR_FIGHT_D->attack_action(me, who, 1020))
                return 1;
        else if (me->get_gender() == 1 && !CHAR_FIGHT_D->attack_action(me, who, 2020))
                return 1;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                  get_x(me), get_y(me), getoid(who), 21175, 1, OVER_BODY);

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21171, 1, OVER_BODY, PF_ONCE);

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_BLADE, ADD_AP2); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 70);
        me->set_enemy_3(who);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);
        me->set_cast_file(__FILE__);
        if (!who)
                return 1;
        if (who->is_anti_effect())
                return 2;
        if (ret > 0)
        {
                if (get_effect(who, EFFECT_CHAR_BLOOD))
                {
                        if (who->is_user() && who->get_save("char_blood") > ADD_AP / 10)
                                return 1;
                        if (who->is_npc() && who->get("char_blood") > ADD_AP / 10)
                                return 1;
                }
                user = get_scene_object_2(who, USER_TYPE);
                set_effect_2(who, EFFECT_CHAR_BLOOD, 10, 2);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user(who, "%c%w%w%c", 0x81, 9022, get_effect_3(who, EFFECT_CHAR_BLOOD), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9022, 1, EFFECT_BAD);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9022, 1, OVER_BODY, PF_LOOP);
                if (who->is_user())
                        who->set_save("char_blood", ADD_AP / 10);
                else
                        who->set("char_blood", ADD_AP / 10);
        }
        return 1;
}

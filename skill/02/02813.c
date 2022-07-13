
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <action.h>

#define THIS_SKILL 0281
#define THIS_PERFORM 02813
#define PF_START "02813"
#define PF_NAME "Phong Vũ Kinh Thiên"

#define SKILL_LEVEL 30
#define TIME_INTERVAL 8
#define MY_CP (me->get_cp() * 30 / 100)
#define WHO_HP_DOWN (me->get_skill(THIS_SKILL) / 15)
#define SUB_MP (30 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 15)
#define ADD_CP (MY_CP + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 200)
#define ADD_INTERVAL 10

// 函数：获取符法效果
int get_cast_seal() { return 9101; } // 符纸顺旋

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 30 cấp\n    Chú thuật thượng thừa hô gọi cuồng phong tấn công từ xa, Gây sát thương đối thủ liên tục trong 10 giây";
        cur_level = (level - SKILL_LEVEL) / 10 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Chú thuật thượng thừa hô gọi cuồng phong tấn công từ xa, Gây %d  sát thương + 30%% nội công của bản thân + %d %% máu của đối thủ liên tục trong 10 giây.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Gây thêm %d điểm Nội Công.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, (ADD_CP - MY_CP), WHO_HP_DOWN, cur_level * 10 + SKILL_LEVEL, ADD_CP + 200);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        object *user;
        int z;
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1;

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

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
        {
                z = get_z(me);

                if (!inside_screen(get_x(me), get_y(me), x, y))
                        return 1;
                if (!objectp(who = get_xy_object(z, x, y, CHAR_TYPE)) && !objectp(who = get_xy_object(z, x, y, USER_TYPE)))
                {
                        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
                        me->set_time("pf", time());

                        me->to_front_xy(x, y);
                        user = get_scene_object_2(me, USER_TYPE);
                        send_user(user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END);
                        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP);

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 5);
                        me->add_2("go_count_count2", 5);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg(sprintf("%d,%d,%d", z, x, y));

                        return 1;
                }
        }

        me->set_enemy_2(who); // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user(user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END);
        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP);

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count_count2", 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg(sprintf("%s,%d", who->get_char_id(), level));
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());
        return 1;
}

// 函数：法术处理
int cast_done(object me)
{
        object *user, who;
        string arg;
        int damage, z, x, y, level;

        if (!stringp(arg = me->get_cast_arg()))
                return 1;

        if (sscanf(arg, "%d,%d,%d", z, x, y) == 3)
        {
                send_user(get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y,
                          42321, 1, OVER_BODY, 42322, 1, UNDER_FOOT, PF_ONCE);

                return 1; // 打到空地
        }
        if (sscanf(arg, "%s,%d", arg, level) != 2)
                return 1;
        if (!objectp(who = find_char(arg)))
                return 1;

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who),
                  2813, 1, OVER_BODY, PF_ONCE);

        if (!who->can_be_fighted(me) || !me->can_fight(who))
                return 2; // 执行成功
        //damage = "/sys/char/fight"->get_cast_damage(me, who, ADD_CP + me->get_cp(), me->get_cp() + ADD_CP - 35);
        damage = ADD_CP;
        if (who->is_user())
        { //50000 * 13/100
                damage += who->get_max_hp() * WHO_HP_DOWN / 100;
        }
        if (damage < 4)
                damage = 4;
        if (get_effect(who, EFFECT_CHAR_BLOOD))
        {
                if (who->is_user() && who->get_save("char_blood") > damage / (ADD_INTERVAL / 2))
                        return 1;
                if (who->is_npc() && who->get("char_blood") > damage / (ADD_INTERVAL / 2))
                        return 1;
        }
        user = get_scene_object_2(who, USER_TYPE);
        set_effect_2(who, EFFECT_CHAR_BLOOD, (ADD_INTERVAL / 2), 2);
        send_user(who, "%c%w%w%c", 0x81, 9022, get_effect_3(who, EFFECT_CHAR_BLOOD), EFFECT_BAD);
        send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9022, 1, EFFECT_BAD);
        CHAR_CHAR_D->init_loop_perform(who);
        send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9022, 1, OVER_BODY, PF_LOOP);
        if (who->is_user())
                who->set_save("char_blood", damage / (ADD_INTERVAL / 2));
        else
                who->set("char_blood", damage / (ADD_INTERVAL / 2));
        if (who->get_enemy() == 0)
                who->init_enemy_damage(me, 0);
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 100);
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
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 10, MAGIC_ACT_BEGIN, 0, 5, 0);
}

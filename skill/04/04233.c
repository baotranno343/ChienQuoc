
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL 0423
#define THIS_PERFORM 04233
#define PF_START "04233"
#define PF_NAME "Hoả Long Quyết"

#define SKILL_LEVEL 18
#define TIME_INTERVAL 2
#define SUB_MP (40 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 20)
#define ADD_AP (50 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 25)
#define ADD_CP (100 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 15)
#define ADD_DAMAGE (100 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 5)
#define ADD_INTERVAL 12

// 函数：获取符法效果
int get_cast_seal() { return 9102; } // 符纸顺旋

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 18 cấp\Vật phẩm tiêu hao: 3 lá Bùa Giấy\nn    Triệu hồi Hoả Long Liệt Diễm vô tình thiêu đốt kẻ địch, tăng thêm 200 điểm Nội Công khi sát thương và làm mục tiêu bị Thiêu Đốt trong 4 giây, mỗi 1 giây mất 80 điểm Khí Huyết";
        cur_level = (level - SKILL_LEVEL) / 10 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Vật phẩm tiêu hao: 3 lá Bùa Giấy\n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Triệu hồi Hoả Long Liệt Diễm vô tình thiêu đốt kẻ địch, tăng thêm %d điểm Nội Công khi sát thương và làm mục tiêu bị Thiêu Đốt trong 4 giây, mỗi 1 giây mất %d điểm Khí Huyết.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d điểm Nội Công khi sát thương và làm mục tiêu bị Thiêu Đốt trong 10 giây, mỗi 1 giây mất %d điểm Khí Huyết.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_CP, ADD_DAMAGE, cur_level * 10 + SKILL_LEVEL, ADD_CP + 15, ADD_DAMAGE + 20);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        object *user, item;
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
        if (me->get_weapon_code() == BLADE)
        {
                printf(ECHO "Không thể sử dụng \"" PF_NAME "\" khi trang bị Đao pháp.");
                return 1;
        }
        if (!objectp(item = present("Bùa Giấy", me, 1, MAX_CARRY * 4))) // || item->get_amount() < 2
        {
                printf(ECHO "Phải có Bùa Giấy mới có thể sử dụng \"" PF_NAME "\"."); // "使用\"" PF_NAME "\"得准备两张符纸."
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
                        me->to_front_xy(x, y);
                        user = get_scene_object_2(me, USER_TYPE);
                        send_user(user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
                        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP);

                        me->add_mp(-mp);
                        item->add_amount(-3);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 5);
                        me->add_2("go_count.count2", 5);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg(sprintf("%d,%d,%d", z, x, y));
                        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
                        me->set_perform(PF_START, time());
                        return 1;
                }
        }

        me->set_enemy_2(who); // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user(user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP);

        me->add_mp(-mp);
        item->add_amount(-3);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2", 5);
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
        int z, x, y;
        int level, ret, damage;

        if (!stringp(arg = me->get_cast_arg()))
                return 1;

        if (sscanf(arg, "%d,%d,%d", z, x, y) == 3)
        {
                send_user(get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y,
                          42331, 2, OVER_BODY, 42332, 2, OVER_BODY, PF_ONCE);

                return 1; // 打到空地
        }
        if (sscanf(arg, "%s,%d", arg, level) != 2)
                return 1;
        if (!objectp(who = find_char(arg)))
                return 1;

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who),
                  42331, 2, OVER_BODY, 42332, 2, OVER_BODY, PF_ONCE);

        if (!who->can_be_fighted(me) || !me->can_fight(who))
                return 2; // 执行成功

        ret = CHAR_FIGHT_D->cast_done(me, who, ADD_CP); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 90);
        if (!who)
                return 1; // 执行成功
        if (who->is_anti_effect())
                return 2;

        if (get_effect(who, EFFECT_CHAR_9145))
                return 2; // 执行成功

        if (ret > 0)
        {
                damage = ADD_DAMAGE;
                if (get_effect(me, EFFECT_USER_BURN))
                {
                        if ((who->get_save("pf.burn") > damage))
                                return 2;
                }
                who->set_save("pf.burn", damage); // 小心准备 me
                user = get_scene_object_2(who, USER_TYPE);
                set_effect_2(who, EFFECT_USER_BURN, (ADD_INTERVAL) / 3, 0); // 小心准备 me
                CHAR_CHAR_D->init_loop_perform(who);
                send_user(who, "%c%w%w%c", 0x81, 9026, get_effect_3(who, EFFECT_USER_BURN), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9026, 1, EFFECT_BAD);
                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9026, 1, OVER_BODY, PF_LOOP);
        }

        return 2; // 执行成功
}

// 函数：命令处理
int perform_action_npc(object me, object who)
{
        object *user;

        if (!inside_screen_2(me, who))
                return 0;

        me->to_front_xy(get_x(who), get_y(who));
        user = get_scene_object_2(me, USER_TYPE);
        send_user(user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
        send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg(sprintf("%s,%d", who->get_char_id(), me->get_skill(THIS_SKILL)));

        return 1;
}

// 函数：法术处理
int cast_done_npc(object me)
{
        object *user, who;
        string arg;
        int z, x, y;
        int level, rate;

        if (!stringp(arg = me->get_cast_arg()))
                return 1;

        if (sscanf(arg, "%s,%d", arg, level) != 2)
                return 1;
        if (!objectp(who = find_char(arg)))
                return 1;

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who),
                  42331, 2, OVER_BODY, 42332, 2, OVER_BODY, PF_ONCE);

        if (!who->can_be_fighted(me) || !me->can_fight(who))
                return 2; // 执行成功

        CHAR_FIGHT_D->cast_done(me, who, ADD_AP); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 90);
        if (!who)
                return 2; // 执行成功
        if (!me)
                return 2;

        /*      if(     get_effect(who, EFFECT_CHAR_FAINT)
        ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) return 2;    // 执行成功
*/
        if (get_effect(who, EFFECT_CHAR_9145))
                return 2; // 执行成功

        rate = 25 * level / range_value(who->get_level(), 1, MAX_NUMBER) + me->get_lucky() - who->get_lucky();
        if (get_effect(me, EFFECT_CHAR_BLIND))
                rate /= 2; // 失明(命中减半)

        if (random(100) < range_value(rate - who->get_immunity(), 5, 100))
        {
                who->set_save("pf.burn", ADD_AP); // 小心准备 me
                user = get_scene_object_2(who, USER_TYPE);
                set_effect_2(who, EFFECT_USER_BURN, (ADD_INTERVAL) / 2, 0); // 小心准备 me
                send_user(who, "%c%w%w%c", 0x81, 9026, get_effect_3(who, EFFECT_USER_BURN), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9026, 1, EFFECT_BAD);
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
        send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 0, 10, MAGIC_ACT_BEGIN, 0, 5, "Bùa Giấy");
}

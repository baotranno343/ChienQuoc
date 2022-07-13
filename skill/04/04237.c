
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL 0423
#define THIS_PERFORM 04237
#define PF_START "04237"
#define PF_NAME "Huyền Long Chân Khí"

#define SKILL_LEVEL 44
#define TIME_INTERVAL 5
#define SUB_MP (30 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 19 * 15)
#define ADD_RATE (800 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) * 500 / 19)
#define ADD_AP (350 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 19 * 60)

// 函数：获取符法效果
int get_cast_seal() { return 9102; } // 符纸顺旋

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 44 cấp\n Vật phẩm tiêu hao: 4 lá Bùa Giấy\n    Triệu hồi Hắc Ám Thần Long tấn công đối thủ, tăng thêm 250 điểm Nội Công và tăng 8%% khả năng ra đòn Bạo Kích.";
        cur_level = (level - SKILL_LEVEL) / 19 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Vật phẩm tiêu hao: 4 lá Bùa Giấy\n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Triệu hồi Hắc Ám Thần Long tấn công đối thủ, tăng thêm %d điểm Nội Công và tăng %d%% khả năng ra đòn Bạo Kích.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d điểm Nội Công，và tăng thêm %d%% khả năng Bạo kích.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP, (ADD_RATE) / 100, cur_level * 19 + SKILL_LEVEL, ADD_AP + 60, (ADD_RATE) / 100 + 5);
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
                        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
                        me->set_time("pf", time());

                        me->to_front_xy(x, y);
                        user = get_scene_object_2(me, USER_TYPE);
                        send_user(user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
                        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP);

                        me->add_mp(-mp);
                        item->add_amount(-2);

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

        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
        me->set_time("pf", time());

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
        int level, rate;

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
                  42351, 2, OVER_BODY, 42352, 2, OVER_BODY, PF_ONCE);

        if (!who->can_be_fighted(me) || !me->can_fight(who))
                return 2; // 执行成功

        rate = me->get_double_rate_2();
        me->set_double_rate_2(rate + ADD_RATE);
        CHAR_FIGHT_D->cast_done(me, who, ADD_AP); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 90);
        me->set_double_rate_2(rate);
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
        name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 19 + 1);
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 0, 10, MAGIC_ACT_BEGIN, 0, 5, "Bùa Giấy");
}
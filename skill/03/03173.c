#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <action.h>

#define THIS_SKILL 0317
#define THIS_PERFORM 03173
#define PF_FLAG "03173"
#define PF_TIME "03173#"
#define PF_NAME "Hộ Thể Kim Cang"

#define SKILL_LEVEL 20
#define TIME_INTERVAL 60 - (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 15 * 3
#define SUB_MP 0
#define SUB_YUAN 1
#define ADD_AP (1 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 10 / 10 + 5) // phản damage
#define ADD_INTERVAL 20 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 15 * 1

// 函数:获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 20 cấp\n    Dùng kim cang bảo hộ bản thân, tự động phản hồi 3%% sát thương cận chiến và tầm xa."; // Mặc định 10%
        cur_level = (level - SKILL_LEVEL) / 15 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Dùng kim cang bảo hộ bản thân, trong %d giây tự động phản hồi %d%% sát thương cận chiến và tầm xa.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Trong %d giây tự động phản hồi %d%% sát thương cận chiến và tầm xa. Giảm thời gian tái sử dụng xuống %d giây",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_INTERVAL, ADD_AP, cur_level * 15 + SKILL_LEVEL, ADD_INTERVAL + 1, ADD_AP + 3, TIME_INTERVAL - 3); // Mặc định add_ap +5
        return result;
}

// 函数:获取描述(持续)
string get_loop_desc(object me)
{
        if (me->get_save(PF_TIME))
                return sprintf(PF_NAME ":\nPhản đòn %d%% sát thương cận chiến và tầm xa.\n",
                               ADD_AP);
        else
                return sprintf(PF_NAME "\n");
}

// 函数:命令处理
int main(object me, object who, int x, int y, string arg)
{
        int level, interval, mp, i, size, z;
        object *user, *team, *all, owner;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        interval = TIME_INTERVAL;

        if (gone_time(me->get_perform(PF_FLAG)) < interval)
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
        if (me->is_anti_effect())
                return 1;
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END);

        me->add_mp(-mp);
        me->add_yuan(-SUB_YUAN);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2", 9);
        interval = ADD_INTERVAL;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_FLAG, time());
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 31731, 1, OVER_BODY, PF_ONCE);
        user = get_scene_object_2(me, USER_TYPE);
        set_effect(me, EFFECT_REBOUND, interval);
        send_user(me, "%c%w%w%c", 0x81, 3173, get_effect_3(me, EFFECT_REBOUND), EFFECT_GOOD);
        send_user(user - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3173, 1, EFFECT_GOOD);
        send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(me), 32511, 1, OVER_BODY, PF_ONCE);
        if (me->is_user())
                me->set_save(PF_TIME, ADD_AP);
        else
                me->set(PF_TIME, ADD_AP);
        CHAR_FIGHT_D->set_enmity2(me, me, 330 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 50); // Mặc định *70
        return 1;
}

// 函数:法术处理
int cast_done(object me)
{
        return 2; // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; } //ON_CHAR

// 函数:能否使用特技
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
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_FLAG));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}

void effect_done(object me)
{
        send_user(me, "%c%w%w%c", 0x81, 3173, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3173, 0, EFFECT_GOOD);
        if (me->is_user())
                me->delete_save(PF_TIME);
        else
                me->set(PF_TIME, 0);
}
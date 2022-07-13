
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL 0364
#define THIS_PERFORM 03642
#define PF_START "03642"
#define PF_TIME "03642#"
#define PF_NAME "Ma Tâm Thuật"

#define SKILL_LEVEL 13
#define TIME_INTERVAL 7
#define SUB_MP 40

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level < SKILL_LEVEL)
                return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 13\n Sau khi sử dụng sẽ tránh né hoàn toàn 1 đòn tấn công kế tiếp của địch thủ. Trạng thái này sẽ duy trì trong 5 giây nếu không bị tấn công.", PF_NAME);
        result = sprintf(HIC " %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Sau khi sử dụng sẽ tránh né hoàn toàn 1 đòn tấn công kế tiếp của địch thủ. Trạng thái này sẽ duy trì trong 5 giây nếu không bị tấn công.",
                         PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
        return result;
}

// 函数：获取描述(持续)
string get_loop_desc(object me)
{
        if (me->get_perform(PF_START))
                return sprintf(PF_NAME "：\n　　Né tránh hoàn toàn 1 lần tấn công.\n");
        else
                return sprintf(PF_NAME "\n");
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        int level, interval, mp;
        object *user;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        interval = TIME_INTERVAL;

        if (gone_time(me->get_perform(PF_START)) < interval)
                return 1; // 小心准备 level

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 level
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
        me->set_time("pf", time());

        //        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        me->add_mp(-mp);
        CHAR_FIGHT_D->set_enmity1(me, 30);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2", 9);
        me->set_cast_file(__FILE__);
        interval = 5;
        //      me->set_cast_arg( sprintf( "%d", level ) );
        me->set_perform(PF_START, time());
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);

        user = get_scene_object_2(me, USER_TYPE);
        set_effect(me, EFFECT_03642, interval);
        send_user(me, "%c%w%w%c", 0x81, 3642, get_effect_3(me, EFFECT_03642), EFFECT_GOOD);
        send_user(user - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3642, 1, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 3642, 1, OVER_BODY, PF_ONCE);
        return 1;
}

// 函数：法术处理
int cast_done(object me)
{
        return 2; // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

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
        name = PF_NAME;
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));

        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}

void into_effect(object me) // 踏雪无痕(自用)
{
        send_user(me, "%c%w%w%c", 0x81, 3642, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3642, 0, EFFECT_GOOD);

        me->set_perform("03642#", 0);
}
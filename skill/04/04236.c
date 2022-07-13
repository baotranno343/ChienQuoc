
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL 0423
#define THIS_PERFORM 04236
#define PF_START "04236"
#define PF_NAME "Hàn Băng Trận"

#define SKILL_LEVEL 35
#define TIME_INTERVAL 15
#define SUB_MP (20 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 19 * 10)
#define ADD_AP (160 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 19 * 5)
#define ADD_INTERVAL 5

// 函数：获取符法效果
int get_cast_seal() { return 42100; } // 符纸顺旋

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 35 cấp\n Vật phẩm tiêu hao: 5 lá Bùa Giấy\n    Phát ra thần công cực hàn hộ thể trong phạm vi 7×7 ô, sát thương với 160 điểm Nội Công và làm tất cả mục tiêu bị Đông Cứng trong 5 giây";
        cur_level = (level - SKILL_LEVEL) / 19 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Vật phẩm tiêu hao: 5 lá Bùa Giấy\n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Phát ra thần công cực hàn hộ thể trong phạm vi 7×7 ô, sát thương với %d điểm Nội Công và làm tất cả mục tiêu bị Đóng Băng trong 5 giây.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d điểm Nội Công.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP, cur_level * 19 + SKILL_LEVEL, ADD_AP + 5);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        object *user, item;
        int level, mp, interval;
        int z, i, size;
        int ret, cp;
        object *char;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1;

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

        if (!objectp(item = present("Bùa Giấy", me, 1, MAX_CARRY * 4))) // || item->get_amount() < 3
        {
                printf(ECHO "Phải có Bùa Giấy mới có thể sử dụng \"" PF_NAME "\"."); // "使用\"" PF_NAME "\"得准备三张符纸."
                return 1;
        }

        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
        me->set_time("pf", time());

        user = get_scene_object_2(me, USER_TYPE);
        me->add_mp(-mp);
        item->add_amount(-5);

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());
        z = get_z(me), x = get_x(me), y = get_y(me);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me),
                  4236, 1, UNDER_FOOT, 4236, 1, UNDER_FOOT, PF_ONCE);
        char = get_range_object(z, x, y, 3, USER_TYPE) + get_range_object(z, x, y, 3, CHAR_TYPE) - ({me});
        cp = me->get_cp();
        me->set_cp(ADD_AP + cp);
        for (i = 0, size = sizeof(char); i < size; i++)
                if (who = char[i])
                {
                        if (who->get("anti_no_move")) //抗冻结
                        {
                                continue;
                        }
                        if (!who->can_be_fighted(me) || !me->can_fight(who))
                                continue; // 执行成功
                        if (get_effect(who, EFFECT_CHAR_NO_MOVE))
                                continue; // 执行成功
                        if (who->is_anti_effect())
                                continue;
                        send_user(who, "%c%c%c", 0x3d, 241, 1);             // 更改走路步数
                        set_effect(who, EFFECT_CHAR_NO_MOVE, ADD_INTERVAL); // 小心准备 me
                        CHAR_CHAR_D->init_loop_perform(who);
                        send_user(who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_NO_MOVE), EFFECT_BAD);
                        send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD);
                        CHAR_FIGHT_D->cast_done(me, who);
                        if (who && !who->is_die())
                                CHAR_FIGHT_D->set_enmity(me, who, 90);
                        if (who)
                                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9012, 1, OVER_BODY, PF_LOOP);
                        if (who)
                                CHAR_CHAR_D->init_loop_perform(who);
                }
        me->set_cp(cp);
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
        name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 19 + 1);
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
}

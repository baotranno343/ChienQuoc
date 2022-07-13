
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL 0417
#define THIS_PERFORM 04175
#define PF_START "04175"
#define PF_NAME "Mệnh Tế"

#define SKILL_LEVEL 31
#define TIME_INTERVAL 25
#define SUB_MP 150

// 函数：获取符法效果
// int get_cast_seal() { return 41100; }    // 符纸逆旋

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 31 cấp\n    Hy sinh Triệu hồi thú của mình để lấy 25%% Khí Huyết của nó chuyển hóa thành Khí Huyết cho toàn bộ thành viên Nhóm trong phạm vi 21×21 ô.";
        result = sprintf(HIC " %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Hy sinh Triệu hồi thú của mình để lấy 25%% Khí Huyết của nó chuyển hóa thành Khí Huyết cho toàn bộ thành viên Nhóm trong phạm vi 21×21 ô.",
                         PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
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

        if (me->get_perform(PF_START) == time())
                return 1;

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

        /*      if( !objectp( item = present("bùa giấy", me, 1, MAX_CARRY) ) )
        {
                printf( ECHO "您得有符纸才能使用\"" PF_NAME "\"." );
                return 1;
        }       */

        who = me->get("soldier");
        if (!who)
                return 1;

        if (!who->is_zombie() || who->get_owner() != me)
        {
                printf(ECHO "Chỉ đối với thú của mình mới có thể sử dụng \"" PF_NAME "\".");
                return 1;
        }

        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 2); // 所有出招２秒后能使用
        me->set_time("pf", time());

        me->set_enemy_2(who); // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user(user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN);
        //      send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);
        //      item->add_amount(-1);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2", 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg(who->get_char_id());
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());
        return 1;
}

// 函数：法术处理
int cast_done(object me)
{
        object who, *all, *team, *user;
        string arg;
        int z, x, y, i, size;
        int level, cp, hp;

        if (!stringp(arg = me->get_cast_arg()))
                return 1;

        if (!objectp(who = find_char(arg)))
                return 1;

        hp = who->get_max_hp();

        send_user(get_scene_object_2(who, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(who), get_y(who), 9414, 1, OVER_BODY, PF_ONCE);
        send_user(me, "%c%c%d", 0x2c, 0, getoid(who));
        who->remove_from_scene(FALL_ACT);
        destruct(who);
        all = me->get_team();
        if (all == 0)
                all = ({me});
        all -= ({0});
        size = sizeof(all);
        z = get_z(me), x = get_x(me), y = get_y(me);
        team = ({});
        for (i = 0; i < size; i++)
        {
                if (all[i] == me)
                        team += ({all[i]});
                else if (z == get_z(all[i]) && abs(x - get_x(all[i])) < 9 && abs(y - get_y(all[i])) < 9)
                        team += ({all[i]});
        }
        size = sizeof(team);
        hp /= 4; // Mặc định 4
        for (i = 0; i < size; i++)
                if (who = team[i])
                {
                        if ("/sys/user/attack"->can_use_help(me, who) == 0)
                                continue;
                        user = get_scene_object_2(who, USER_TYPE);
                        if (!who->no_recover() && !get_effect_3(who, EFFECT_USER_BURN))
                                who->add_hp(hp);
                        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 4175, 1, OVER_BODY, PF_ONCE);
                        send_user(user, "%c%d%w", 0x68, getoid(who), -hp);
                        CHAR_FIGHT_D->set_enmity2(me, who, 80 + hp / 2); // Mặc định là 80
                }
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
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 5, 0);
}

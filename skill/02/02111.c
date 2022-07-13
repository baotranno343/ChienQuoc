
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL 0211
#define THIS_PERFORM 02111
#define PF_START "02111"
#define PF_NAME "Khí Tráng Sơn Hà"

#define SKILL_LEVEL 5
#define TIME_INTERVAL 6
#define SUB_MP 0
#define ADD_AP 50 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 8
#define ADD_ENMITY 80 * yuan + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 30 + ret
#define ADD_RATE 150

// 函数:获取法力
int get_sub_mp(object me)
{
        int level = me->get_skill(THIS_SKILL);
        return SUB_MP;
}

// 函数:获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\nCông kích cận chiến.\n    Tấn công cận chiến 1 mục tiêu.: Vận dụng nguyên khí toàn thân tấn công đối thủ, mỗi điểm nguyên khí tiêu hao tăng 50 điểm sát thương.";
        cur_level = (level - SKILL_LEVEL) / 10 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: Toàn bộ\n Tái sử dụng sau: %d giây\n    Tấn công cận chiến 1 mục tiêu.: Vận dụng nguyên khí toàn thân tấn công đối thủ, mỗi điểm nguyên khí tiêu hao tăng %d điểm sát thương, đồng thời có tỉ lệ gia tăng chính xác khi tấn công.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d \n" NOR "    Mỗi điểm nguyên khí tiêu hao gia tăng sát thương khi tấn công.",
                         PF_NAME, cur_level, SKILL_LEVEL, TIME_INTERVAL, ADD_AP, cur_level * 10 + SKILL_LEVEL, ADD_AP + 8, ADD_RATE);
        return result;
}

// 函数:命令处理
int main(object me, object who, int x, int y, string arg)
{
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1; // 小心准备 level

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 level
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

        if (me->get_weapon_code() != UNARMED)
        {
                printf(ECHO "Sử dụng \"" PF_NAME "\" phải trang bị triển thủ");
                return 1;
        }
        if (me->get_gender() != 1 && !CHAR_FIGHT_D->attack_action(me, who, 1010))
                return 1;
        else if (me->get_gender() == 1 && !CHAR_FIGHT_D->attack_action(me, who, 2010))
                return 1;
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2", 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg(sprintf("%s", who->get_char_id()));
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());
        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_LOOP);

        return 1;
}

// 函数:特殊技处理(动作)
int perform_action(object me, object who)
{
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1; // 小心准备 level

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 level
        {
                printf(ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp);
                return 1;
        }

        if (me->get_weapon_code() != UNARMED)
        {
                printf(ECHO "Sử dụng \"" PF_NAME "\" phải trang bị triển thủ");
                return 1;
        }

        if (me->get_gender() != 1 && !CHAR_FIGHT_D->attack_action(me, who, 1010))
                return 1;
        else if (me->get_gender() == 1 && !CHAR_FIGHT_D->attack_action(me, who, 2010))
                return 1;

        me->add_mp(-mp);
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        return 2; // 执行成功
}

// 函数:特殊技处理
int perform_done(object me, object who)
{
        int level, mp, yuan, rate, ret;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        //      if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        /*      if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }       */

        if (me->get_weapon_code() != UNARMED)
        {
                printf(ECHO "Sử dụng \"" PF_NAME "\" phải trang bị triển thủ");
                return 1;
        }

        me->set_perform_file(0);
        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 21111, 1, UNDER_FOOT, PF_ONCE);

        yuan = me->get_yuan();
        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, (ADD_AP)*yuan); // 小心准备 me
        me->add_yuan(-yuan);

        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, ADD_ENMITY);

        return 2; // 执行成功
}

// 函数:特殊技处理
int cast_done(object me)
{
        int level, mp, yuan, rate, ret;
        object who;
        string arg;

        if (!stringp(arg = me->get_cast_arg()))
                return 1;
        if (!objectp(who = find_char(arg)))
                return 1;

        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 21111, 1, UNDER_FOOT, PF_ONCE);

        yuan = me->get_yuan();
        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, (ADD_AP)*yuan); // 小心准备 me
        me->add_yuan(-yuan);

        CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0, ADD_RATE); // Chính xác

        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, ADD_ENMITY);

        return 2; // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数:能否使用特技
void can_perform(object me)
{
        int interval;
        if (me->get_skill(THIS_SKILL) < SKILL_LEVEL)
        {
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME);
                return;
        }
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, PF_NAME);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, PF_NAME);
        if (me->get_gender() == 1)
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 2, 10, 5, 0);
        else
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 1, 10, 5, 0);
}

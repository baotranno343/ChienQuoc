
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <action.h>

#define THIS_SKILL 0241
#define THIS_PERFORM 02416
#define PF_START "02416"
#define PF_NAME "Lôi Đình Kích"

#define SKILL_LEVEL 35
#define TIME_INTERVAL 18 - (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 8
#define SUB_MP 0
#define SUB_YUAN 3
#define ADD_AP 30 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 8 * 25

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
                return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 35\n Chiêu thức tối thượng của Bá Vương Thương Pháp với uy lực kinh hồn, tăng thêm 30 điểm Ngoại Công khi sát thương và tấn công mục tiêu 2 lần liên tiếp.", PF_NAME);
        cur_level = (level - SKILL_LEVEL) / 8 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Chiêu thức tối thượng của Bá Vương Thương Pháp với uy lực kinh hồn, tăng thêm %d điểm Ngoại Công khi sát thương và tấn công mục tiêu 2 lần liên tiếp.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n Tăng thêm %d điểm Ngoại Công，Thời gian tái sử dụng giảm còn %d giây.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP, cur_level * 8 + SKILL_LEVEL, ADD_AP + 25, TIME_INTERVAL - 1);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1; // 小心准备 me

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
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
        if (!CHAR_FIGHT_D->attack_action(me, who, 1060))
                return 1;
        me->add_yuan(-SUB_YUAN);
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

// 函数：特殊技处理(动作)
int perform_action(object me, object who)
{
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1; // 小心准备 me

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
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

        if (!CHAR_FIGHT_D->attack_action(me, who, 1060))
                return 1;

        me->add_mp(-mp);
        me->add_yuan(-SUB_YUAN);

        return 2; // 执行成功
}
int perform_action_npc(object me, object who)
{
        int level, mp;

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
        {
                return 0;
        }

        if (!CHAR_FIGHT_D->attack_action(me, who, 36))
                return 0;
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());
        me->add_mp(-mp);
        return 2; // 执行成功
}
// 函数：特殊技处理
int perform_done(object me, object who)
{
        object *user;
        int level, mp, rate;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        //      if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        /*      if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }       */

        /*      if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }       */

        if (me->get_weapon_code() == UNARMED)
        {
                printf(ECHO "Sử dụng \" %s \" phải trang bị binh khí.", PF_NAME);
                return 1;
        }
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());
        me->set_perform_file(0);
        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(who),
                  2416, 1, OVER_BODY, 2416, 1, OVER_BODY, 2416, 1, OVER_BODY, PF_ONCE);
        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 80);

        if (!who)
                return 2;                                     // 执行成功
        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP); // 小心准备 me
        return 2;                                             // 执行成功
}

// 函数：特殊技处理
int cast_done(object me)
{
        object *user;
        int level, mp, rate;
        object who;
        string arg;

        if (!stringp(arg = me->get_cast_arg()))
                return 1;
        if (!objectp(who = find_char(arg)))
                return 1;
        send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(who),
                  2416, 1, OVER_BODY, 2416, 1, OVER_BODY, 2416, 1, OVER_BODY, PF_ONCE);
        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 80);

        if (!who)
                return 2;                                     // 执行成功
        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP); // 小心准备 me
        return 2;                                             // 执行成功
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
        name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 8 + 1);
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 1, 60, 5, 0);
}

int perform_done_npc(object me, object who)
{
        object *user;
        int level, mp, rate;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);

        me->set_perform_file(0);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(who),
                  24161, 1, OVER_BODY, 24162, 1, OVER_BODY, 24163, 1, OVER_BODY, PF_ONCE);

        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 80);

        if (!who)
                return 2;                             // 执行成功
        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE); // 小心准备 me

        return 2; // 执行成功
}
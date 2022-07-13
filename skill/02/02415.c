
// 单体远程技能  TIPS:[PF_CAST]  变异

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL 0241
#define THIS_PERFORM 02415
#define PF_START "02415"
#define PF_NAME "Phi Long Tầm Châu"

#define SKILL_LEVEL 28
#define TIME_INTERVAL 32 - (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 15 * 3
#define SUB_MP 0
#define SUB_YUAN 3
#define ADD_AP (80 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 15 * 45)

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 28\n Sử dụng trường thương như cưỡi rồng vượt mây truy kích một mục tiêu trong tầm nhìn, tăng thêm 80 điểm Ngoại Công khi sát thương và làm đối thủ bị Choáng trong 2 giây.", PF_NAME);
        cur_level = (level - SKILL_LEVEL) / 15 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Sử dụng trường thương như cưỡi rồng vượt mây truy kích một mục tiêu trong tầm nhìn, tăng thêm %d điểm Ngoại Công khi sát thương và làm đối thủ bị Choáng trong 2 giây.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n Tăng thêm %d điểm Ngoại Công,Thời gian tái sử dụng giảm còn %d giây.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP, cur_level * 15 + SKILL_LEVEL, ADD_AP + 45, TIME_INTERVAL - 3);
        return result;
}

int cast_done(object me);

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        object item;
        int z, x0, y0, d;
        int act, pf;
        int level, mp, lasting;
        int i, size, size2;

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
        if (!objectp(item = me->get_equip(WEAPON_TYPE)) || (lasting = item->get_lasting()) < 1000)
        {
                printf(ECHO "Sử dụng \"" PF_NAME "\" độ bền vũ khí phải lớn hơn 10");
                return 1;
        }

        z = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);

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
                //              z = get_z(me);

                if (!inside_screen(get_x(me), get_y(me), x, y))
                        return 1;
                if (!objectp(who = get_xy_object(z, x, y, CHAR_TYPE)) && !objectp(who = get_xy_object(z, x, y, USER_TYPE)))
                        return 1;
                /*              if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
                        me->set_perform( PF_START, time() );

                        me->to_front_xy(x, y);
                        user = get_scene_object_2(me, USER_TYPE);
                        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

                        me->add_mp(-mp);
                        me->add_yuan( -SUB_YUAN );
                        item->add_lasting( - lasting / 2 );

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 9);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }       */
        }

        me->set_enemy_2(who); // 远程目标锁定

        me->add_mp(-mp);
        me->add_yuan(-SUB_YUAN);
        lasting = item->get_max_lasting();
        item->add_lasting(-lasting / 20);

        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x42, getoid(me), time2(), 1, 50, me->to_front_xy(x, y), 0);

        //        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2", 9);
        //        me->set_cast_file(__FILE__);
        me->set_cast_arg(sprintf("%s,%d,%d,%d,%d", who->get_char_id(), level, item->get("ap"), lasting, item->get_max_lasting()));
        cast_done(me);
        return 1;
}

// 函数：法术处理
int cast_done(object me)
{
        object who, owner, *user;
        string arg;
        int level, ap, lasting, lasting2, damage, rate, p, double_flag;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        if (!stringp(arg = me->get_cast_arg()) || sscanf(arg, "%s,%d,%d,%d,%d", arg, level, ap, lasting, lasting2) != 5)
                return 1;
        if (!objectp(who = find_char(arg)))
                return 1;

        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 24151, 1, OVER_BODY, 24152, 1, OVER_BODY, PF_ONCE);
        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c", 0x8a, getoid(me), time2(),
                  get_x(me), get_y(me), getoid(who), 24155, 1, OVER_BODY);

        if (!who->can_be_fighted(me) || !me->can_fight(who))
                return 1;
        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP);
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 90);

        if (who)
        {
                if (get_effect(who, EFFECT_CHAR_FAINT) || get_effect(who, EFFECT_CHAR_FAINT_0))
                        return 1; // 执行成功
                if (who->is_anti_effect())
                        return 2;
                if (who->get_perform("02222#"))
                        return 2;
                if (who->get("anti_faint"))
                        return 2;
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT, 2); // 小心准备 me
                CHAR_CHAR_D->init_loop_perform(who);
                if (get_heart_state(who) == MAGIC_STAT)
                        send_user(user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END); // 结束施法动作
                send_user(who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD);
                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP);
        }
        return 2; // 执行成功
}

// 函数：命令处理
int perform_action_npc(object me, object who)
{
        int act, pf;

        if (distance_between(who, me) > 12)
                return 0;

        pf = 60; // 抄自 /sys/user/fight

        if (!(act = pf / 10)) // pf: [动作序号][光影序号]
        {
                pf = 0;
                act = 1 + random(3); // 无指定动作序号，随机
        }

        me->to_front_xy(get_x(who), get_y(who));
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), act, pf, get_d(me), getoid(who));

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg(who->get_char_id());

        return 1;
}

// 函数：法术处理
int cast_done_npc(object me)
{
        object who, owner, *user;
        string arg;
        int level, ap, lasting, lasting2, damage, rate, p, double_flag;
        arg = me->get_cast_arg();
        if (!objectp(who = find_char(arg)))
                return 1;
        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 24151, 1, OVER_BODY, 24152, 1, OVER_BODY, PF_ONCE);
        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c", 0x8a, getoid(me), time2(),
                  get_x(me), get_y(me), getoid(who), 24155, 1, OVER_BODY);

        if (!who->can_be_fighted(me) || !me->can_fight(who))
                return 1;
        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, 0);
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 90);

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
        name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 15 + 1);
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 10, 1, 50, 9, 0);
}

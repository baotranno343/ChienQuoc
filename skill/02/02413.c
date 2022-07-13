
// 法术＋出招  TIPS:[PF_CAST]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <action.h>

#define THIS_SKILL 0241
#define THIS_PERFORM 02413
#define PF_START "02413"
#define PF_NAME "Thiên Lý Tất Sát"

#define SKILL_LEVEL 23
#define TIME_INTERVAL 20 - (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 9
#define SUB_MP 0
#define SUB_YUAN 2
#define ADD_INTERVAL 2
#define ADD_AP 70 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 9 * 25

int perform_done(object me, object who);

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 23\n Thương pháp hung bạo truy kích một mục tiêu trong tầm nhìn, tăng thêm 70 điểm Ngoại Công khi sát thương và làm đối thủ bị Choáng trong 2 giây.", PF_NAME);
        cur_level = (level - SKILL_LEVEL) / 9 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Thương pháp hung bạo truy kích một mục tiêu trong tầm nhìn, tăng thêm %d điểm Ngoại Công khi sát thương và làm đối thủ bị Choáng trong 2 giây.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n Tăng thêm %d điểm Ngoại Công，Thời gian tái sử dụng giảm còn %d giây.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP, cur_level * 9 + SKILL_LEVEL, ADD_AP + 25, TIME_INTERVAL - 1);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        int z, x0, y0, d;
        int act, pf;
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

        z = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);

        if (who)
        {
                if (!inside_screen_2(me, who))
                        return 1;
                //                if( distance_between(me, who) > 10 ) return 1;    // 距离过远

                x = get_x(who);
                y = get_y(who);
        }
        //        else if( objectp( who = me->get_enemy_2() ) && distance_between(me, who) <= 6 )
        else if (objectp(who = me->get_enemy_2()) && inside_screen_2(me, who))
        {
                x = get_x(who);
                y = get_y(who);
        }
        else
        {
                //              z = get_z(me);

                if (abs(x - x0) > 10 || abs(y - y0) > 10)
                        return 1; // 距离过远
                                  //              if( !inside_screen(x0, y0, x, y) ) return 1;

                if (!objectp(who = get_xy_object(z, x, y, CHAR_TYPE)) && !objectp(who = get_xy_object(z, x, y, USER_TYPE)))
                        return 1;
        }

        switch (d = me->to_front_xy(x, y)) // 获取背面坐标(背面之背面)
        {
        case 1:
                x++;
                break;
        default:
                x++;
                y--;
                break;
        case 3:
                y--;
                break;
        case 4:
                x--;
                y--;
                break;
        case 5:
                x--;
                break;
        case 6:
                x--;
                y++;
                break;
        case 7:
                y++;
                break;
        case 8:
                x++;
                y++;
                break;
        }

        if (!inside_map(z, x, y))
                return 1; // 坐标非法
        if (get_block(z, x, y) & IS_CHAR_BLOCK)
                return 1; // 无法落脚
        if (!from_to(z, x0, y0, x - x0, y - y0, MAP_BLOCK))
                return 1; // 无法穿越

        me->set_enemy_2(who); // 远程目标锁定

        me->add_to_scene(z, x, y, d, 32411);

        pf = me->get_gender() == 1 ? 23 : 23; // 抄自 /sys/user/fight

        if (!(act = pf / 10)) // pf: [动作序号][光影序号]
        {
                pf = 0;
                act = 1 + random(3); // 无指定动作序号，随机
        }

        //	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), act, pf, get_d(me), 0 );

        me->add_mp(-mp);
        me->add_yuan(-SUB_YUAN);
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        //      set_heart_state(me, MAGIC_STAT);
        //      set_heart_count_2(me, 9);

        if (!CHAR_FIGHT_D->attack_action(me, who, 1030, 8))
                return 1;
        //        me->set_perform_file(__FILE__);    // 以下模拟物理出招（法术＋出招）
        //        me->set_perform_enable_time(time());
        me->set_enemy_3(who);
        perform_done(me, who);

        return 1;
}

// 函数：法术处理
int cast_done(object me) // 无目标时
{
        string arg;

        if (!stringp(arg = me->get_cast_arg()))
                return 1;

        return 1; // 打到空地

        return 2; // 执行成功
}

// 函数：特殊技处理
int perform_done(object me, object who) // 有目标时
{
        object *user;
        int level, mp, ret;

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

        me->set_perform_file(0);
        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 2413, 1, OVER_BODY, PF_ONCE);

        if (!who->can_be_fighted(me) || !me->can_fight(who))
                return 2; // 执行成功

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_SPEAR, ADD_AP); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 60);

        if (!who)
                return 2; // 执行成功
        if (who->is_anti_effect())
                return 2;
        if (who->get("anti_faint"))
                return 2;
        if (get_effect(who, EFFECT_CHAR_FAINT) || get_effect(who, EFFECT_CHAR_FAINT_0))
                return 2; // 执行成功
        if (who->get_perform("02222#"))
                return 2;
        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 24131, 1, OVER_BODY, PF_ONCE);
        if (ret > 0)
        {
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT, ADD_INTERVAL); // 小心准备 me
                CHAR_CHAR_D->stop_loop_perform_faint(who);
                CHAR_CHAR_D->init_loop_perform(who);
                if (get_heart_state(who) == MAGIC_STAT)
                        send_user(user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END); // 结束施法动作
                send_user(who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD);
                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP);
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
        name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 9 + 1);
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 8, 1, 30, 7, 0);
}

// 函数：特殊技处理
int perform_done_npc(object me, object who) // 有目标时
{
        object *user;
        int level, mp, ret;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        me->set_perform_file(0);
        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 2413, 1, OVER_BODY, PF_ONCE);

        if (!who->can_be_fighted(me) || !me->can_fight(who))
                return 2; // 执行成功

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_SPEAR, ADD_AP); // 小心准备 me
        if (who && !who->is_die())
                CHAR_FIGHT_D->set_enmity(me, who, 60);
        if (!who)
                return 2; // 执行成功
        if (who->is_anti_effect())
                return 2;
        if (who->get("anti_faint"))
                return 2;
        if (get_effect(who, EFFECT_CHAR_FAINT) || get_effect(who, EFFECT_CHAR_FAINT_0))
                return 2; // 执行成功
        if (who->get_perform("02222#"))
                return 2;
        send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 24131, 1, OVER_BODY, PF_ONCE);
        if (ret > 0)
        {
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT, ADD_INTERVAL); // 小心准备 me
                CHAR_CHAR_D->stop_loop_perform_faint(who);
                CHAR_CHAR_D->init_loop_perform(who);
                if (get_heart_state(who) == MAGIC_STAT)
                        send_user(user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END); // 结束施法动作
                send_user(who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD);
                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP);
        }
        return 2; // 执行成功
}

int perform_action_npc(object me, object who)
{
        int z, x0, y0, x, y, d;
        int act, pf;
        int level, mp;

        if ((level = me->get_skill(THIS_SKILL)) < SKILL_LEVEL)
                return 1;

        if (gone_time(me->get_perform(PF_START)) < TIME_INTERVAL)
                return 1; // 小心准备 me

        if (!who)
                return 0;
        if (!inside_screen_2(me, who))
                return 1;

        z = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);
        x = get_x(who);
        y = get_y(who);

        switch (d = me->to_front_xy(x, y)) // 获取背面坐标(背面之背面)
        {
        case 1:
                x++;
                break;
        default:
                x++;
                y--;
                break;
        case 3:
                y--;
                break;
        case 4:
                x--;
                y--;
                break;
        case 5:
                x--;
                break;
        case 6:
                x--;
                y++;
                break;
        case 7:
                y++;
                break;
        case 8:
                x++;
                y++;
                break;
        }

        if (!inside_map(z, x, y))
                return 1; // 坐标非法
        if (get_block(z, x, y) & IS_CHAR_BLOCK)
                return 1; // 无法落脚
        if (!from_to(z, x0, y0, x - x0, y - y0, MAP_BLOCK))
                return 1; // 无法穿越

        me->set_enemy_2(who); // 远程目标锁定

        me->add_to_scene(z, x, y, d, 32411);

        pf = me->get_gender() == 1 ? 23 : 23; // 抄自 /sys/user/fight

        if (!(act = pf / 10)) // pf: [动作序号][光影序号]
        {
                pf = 0;
                act = 1 + random(3); // 无指定动作序号，随机
        }

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        if (!CHAR_FIGHT_D->attack_action(me, who, 1030, 8))
                return 1;
        me->set_enemy_3(who);
        perform_done_npc(me, who);

        return 1;
}
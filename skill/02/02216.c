
// 单体远程技能  TIPS:[PF_CAST]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL 0221
#define THIS_PERFORM 02216
#define PF_START "02216"
#define PF_NAME "Khai Thiên Tịch Địa"

#define SKILL_LEVEL 35
#define TIME_INTERVAL 4
#define SUB_MP 40 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 8
#define ADD_AP (25 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 10)
int cast_done(object me);

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 35 cấp\n    Tuyệt kĩ Đao pháp tối thượng, tăng thêm 200 điểm sát thương khi tấn công tất cả mục tiêu trong phạm vi tùy ý trước mặt.";
        cur_level = (level - SKILL_LEVEL) / 10 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tuyệt kĩ Đao pháp tối thượng, tăng thêm %d điểm sát thương khi tấn công tất cả mục tiêu trong phạm vi tùy ý trước mặt.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d sát thương.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP, cur_level * 10 + SKILL_LEVEL, ADD_AP + 250);
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

        if (me->get_weapon_code() != BLADE)
                if (me->get_weapon_code() != SWORD)
                {
                        printf(ECHO "Sử dụng \"" PF_NAME "\" phải trang bị đao hoặc kiếm");
                        return 1;
                }
        z = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);

        if (who)
        {
                //              if( !inside_screen_2(me, who) ) return 1;
                if (distance_between(me, who) > 5)
                        return 1; // 距离过远

                x = get_x(who);
                y = get_y(who);
        }
        /*      else if( objectp( who = me->get_enemy_2() ) && distance_between(me, who) <= 6 )
//      else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }       */
        else
        {
                //              z = get_z(me);
                if (x > x0 + 5)
                        x = x0 + 5;
                if (x < x0 - 5)
                        x = x0 - 5;
                if (y > y0 + 5)
                        y = y0 + 5;
                if (y < y0 - 5)
                        y = y0 - 5;
        }
        if (!inside_map(z, x, y))
                return 1; // 坐标非法
        if (get_block(z, x, y) & IS_MAP_BLOCK)
                return 1; // 无法落脚
        if (x == x0 && y == y0)
                return 1;
        if (!from_to(z, x0, y0, x - x0, y - y0, MAP_BLOCK))
                return 1; // 无法穿越
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 32411, 1, OVER_BODY, PF_ONCE);
        me->add_to_scene(z, x, y, me->to_front_xy(x, y));

        if (me->get_gender() == 2)
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 60, get_d(me), 0);
        else
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), 0);

        me->add_mp(-mp);

        //        set_heart_state(me, MAGIC_STAT);
        //        set_heart_count_2(me, 9);
        me->set_cast_file(0);
        me->set_cast_arg(sprintf("%d,%d,%d,%d,%d,%d", level, z, x0, y0, x - x0, y - y0));
        cast_done(me);
        return 1;
}

// 函数：法术处理
int cast_done(object me)
{
        object *char, user, who;
        string arg;
        int z, x, y, dx, dy, p;
        int level, ap, damage, damage2, i, size, count;
        int *dxs, *dys;

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        me->set_perform(PF_START, time());

        if (!stringp(arg = me->get_cast_arg()) || sscanf(arg, "%d,%d,%d,%d,%d,%d", level, z, x, y, dx, dy) != 6)
                return 1;
        dxs = ({});
        dys = ({});
        char = ({});
        if (dy == 0)
        {
                char += get_line_object(z, x, y, dx, 0, USER_TYPE) + get_line_object(z, x, y, dx, 0, CHAR_TYPE);
        }
        else if (dx > 0)
        {
                for (i = 0; i <= dx; i++)
                {
                        char += get_line_object(z, x + i, y, 0, dy, USER_TYPE) + get_line_object(z, x + i, y, 0, dy, CHAR_TYPE);
                }
        }
        else if (dx < 0)
        {
                for (i = 0; i <= -dx; i++)
                {
                        char += get_line_object(z, x - i, y, 0, dy, USER_TYPE) + get_line_object(z, x - i, y, 0, dy, CHAR_TYPE);
                }
        }
        else
        {
                char += get_line_object(z, x, y, 0, dy, USER_TYPE) + get_line_object(z, x, y, 0, dy, CHAR_TYPE);
        }
        count = 0;
        for (i = 0, size = sizeof(char); i < size; i++)
                if (who = char[i])
                {
                        if (!who->can_be_fighted(me) || !me->can_fight(who))
                                continue;
                        count++;
                        if (count <= 5)
                                send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 22162, 1, OVER_BODY, 22163, 1, OVER_BODY, PF_ONCE);
                        CHAR_FIGHT_D->attack_done(me, who, HIT_BLADE, ADD_AP);
                        if (who && !who->is_die())
                                CHAR_FIGHT_D->set_enmity(me, who, 80);
                }
        me->set_cast_file(0);
        return 2; // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_XY2; }

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
        if (me->get_gender() == 1)
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 1, 60, 7, 0);
        else
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, 2, 60, 7, 0);
}

int perform_action_npc(object me, object who)
{
        int z, x0, y0, d, x, y;
        int act, pf;
        int level, mp;

        if (me->get_mp() < (mp = SUB_MP)) // 小心准备 me
        {
                return 0;
        }

        z = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);
        if (distance_between(me, who) > 6)
                return 0; // 距离过远
        x = get_x(who);
        y = get_y(who);
        d = get_front_xy(x0, y0, x, y);
        switch (d)
        {
        case 1:
                x += 1;
                break;
        case 2:
                x += 1;
                y += 1;
                break;
        case 3:
                y -= 1;
                break;
        case 4:
                x -= 1;
                y -= 1;
                break;
        case 5:
                x -= 1;
                break;
        case 6:
                x -= 1;
                y += 1;
                break;
        case 7:
                y += 1;
                break;
        case 8:
                x += 1;
                y += 1;
                break;
        }
        if (abs(x - x0) > 6 || abs(y - y0) > 6)
                return 0; // 距离过远
        if (!objectp(who = get_xy_object(z, x, y, CHAR_TYPE)) && !objectp(who = get_xy_object(z, x, y, USER_TYPE)))
        {
                if (!inside_map(z, x, y))
                        return 0; // 坐标非法
                if (get_block(z, x, y) & IS_CHAR_BLOCK)
                        return 0; // 无法落脚
                if (!from_to(z, x0, y0, x - x0, y - y0, MAP_BLOCK))
                        return 0; // 无法穿越

                me->add_to_scene(z, x, y, me->to_front_xy(x, y));
                me->to_front(get_front_xy(x, y, x0, y0));
                pf = 36; // 抄自 /sys/user/fight

                if (!(act = pf / 10)) // pf: [动作序号][光影序号]
                {
                        pf = 0;
                        act = 1 + random(3); // 无指定动作序号，随机
                }
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 60, get_d(me), 0);
                me->add_mp(-mp);
                set_heart_state(me, MAGIC_STAT);
                set_heart_count_2(me, 9);
                me->set_cast_file(__FILE__);
                me->set_cast_arg(sprintf("%d,%d,%d,%d,%d,%d", level, z, x0, y0, x - x0, y - y0));

                return 1;
        }

        return 0;
}

int cast_done_npc(object me)
{
        object *char, user, who;
        string arg;
        int z, x, y, dx, dy;
        int level, ap, damage, damage2, i, size;

        if (!stringp(arg = me->get_cast_arg()) || sscanf(arg, "%d,%d,%d,%d,%d,%d", level, z, x, y, dx, dy) != 6)
                return 1;

        char = get_line_object(z, x, y, dx, dy, USER_TYPE) + get_line_object(z, x, y, dx, dy, CHAR_TYPE) - ({me});

        ap = me->get_ap();
        damage = ap / (2 - level / 100); // 小心除数为零

        for (i = 0, size = sizeof(char); i < size; i++)
                if (who = char[i])
                {
                        if (!who->can_be_fighted(me) || !me->can_fight(who))
                                continue;

                        damage2 = CHAR_FIGHT_D->correct_damage(me, who, damage, ap);

                        if (who->is_npc()) // 抄自 /sys/user/fight
                        {
                                if (who->get_enemy_4() == me)
                                        who->set_attack_time(time()); // 同一个人：更新持续时间
                                else if (gone_time(who->get_attack_time()) > 12)
                                {
                                        who->set_enemy_4(me);
                                        who->set_attack_time(time()); // 不同的人：更新持续敌手
                                }
                                if (damage >= who->get_max_damage())
                                        who->init_enemy_damage(me, damage); // 记录最强伤害(NPC)
                                user = who->get_owner();
                        }
                        else
                                user = who;

                        if (user)
                                send_user(user, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage2, get_d(who), 0, HIT_BLADE, 1);
                        send_user(me, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage2, get_d(who), 0, HIT_BLADE, 1);
                        CHAR_DIE_D->is_enemy_die(me, who, damage2);
                }

        return 2; // 执行成功
}
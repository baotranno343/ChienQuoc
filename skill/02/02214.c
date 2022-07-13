
// 单体远程技能  TIPS:[PF_CAST]  变异

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>
#include <action.h>

#define THIS_SKILL 0221
#define THIS_PERFORM 02214
#define PF_START "02214"
#define PF_NAME "Lưu Tinh Truy Mạng"

#define SKILL_LEVEL 18
#define TIME_INTERVAL 6
#define SUB_MP 26 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 6
#define ADD_DAMAGE (30 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 5)
#define ADD_AP (30 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 * 10)
int cast_done(object me);

// 函数：获取描述
string get_desc(object me)
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level < SKILL_LEVEL)
                return HIR + PF_NAME + "\n Võ công yêu cầu: 18 cấp\n    Truy sát đao thức, chỉ trong chớp mắt di chuyển đến sau lưng mục tiêu và tấn công, gây choáng 1 giây, tăng thêm 30 điểm sát thương và tăng 30%% độ chính xác.";
        cur_level = (level - SKILL_LEVEL) / 10 + 1;
        result = sprintf(HIC " %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Truy sát đao thức, chỉ trong chớp mắt di chuyển đến sau lưng mục tiêu và tấn công, gây choáng 1 giây, tăng thêm %d điểm sát thương và tăng %d%% độ chính xác.\n " HIC "Cấp tiếp theo:\n " NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d điểm sát thương và tăng %d%% độ chính xác.",
                         PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP, ADD_DAMAGE, cur_level * 10 + SKILL_LEVEL, ADD_AP + 10, ADD_DAMAGE + 15);
        return result;
}

// 函数：命令处理
int main(object me, object who, int x, int y, string arg)
{
        int z, x0, y0, x1, y1, d;
        int act, pf;
        int level, mp, ret;
        object *user;

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
                if (!inside_screen_2(me, who))
                        return 1;
                x = get_x(who);
                y = get_y(who);
                x1 = x;
                y1 = y;
        }
        else
                return 1;
        switch (get_d(who))
        {
        case 1:
                x--;
                break;
        case 2:
                x--;
                y++;
                break;
        case 3:
                y++;
                break;
        case 4:
                x++;
                y++;
                break;
        case 5:
                x++;
                break;
        case 6:
                x++;
                y--;
                break;
        case 7:
                y--;
                break;
        case 8:
                x--;
                y--;
                break;
        }
        if (get_block(z, x, y) & IS_MAP_BLOCK)
                return 1; // 无法落脚
        if (x == x0 && y == y0)
                return 1;
        if (!from_to(z, x0, y0, x - x0, y - y0, MAP_BLOCK))
                return 1; // 无法穿越
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 32411, 1, OVER_BODY, PF_ONCE);
        me->add_to_scene(z, x, y, 3);
        me->to_front_xy(x1, y1);

        me->set_perform(PF_START, time());
        if (me->get_gender() == 2)
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 60, get_d(me), 0);
        else
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), 0);
        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_BLADE, ADD_AP, 0, ADD_DAMAGE); // 小心准备 me
        me->add_mp(-mp);
        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);
        if (ret > 0)
        {
                if (!who || who->is_die())
                        return 2;
                if (who->is_anti_effect())
                        return 2;
                if (who->get("anti_faint"))
                        return 2;
                if (get_effect(who, EFFECT_CHAR_FAINT) || get_effect(who, EFFECT_CHAR_FAINT_0))
                        return 2;
                if (who->get_perform("02222#"))
                        return 2;
                if (get_effect(who, EFFECT_CHAR_9145))
                        return 2; // 执行成功

                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT, 1);
                CHAR_CHAR_D->stop_loop_perform_faint(who);
                CHAR_CHAR_D->init_loop_perform(who);
                if (get_heart_state(who) == MAGIC_STAT)
                        send_user(user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END); // 结束施法动作
                send_user(who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD);
                send_user(user - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD);
                send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP);
        }
        return 1;
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
        name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL) - SKILL_LEVEL) / 10 + 1);
        interval = TIME_INTERVAL - gone_time(me->get_perform(PF_START));
        if (interval < 0)
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name);
        else
                send_user(me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name);
        if (me->get_gender() == 1)
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 10, 1, 60, 7, 0);
        else
                send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 10, 2, 60, 7, 0);
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

        send_user(me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0);

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
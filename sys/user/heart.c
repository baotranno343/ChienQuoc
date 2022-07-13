
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <cmd.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：人物心跳处理
void heart_beat_attack(object me) // 每 0.1 秒处理
{
        object who;
        int x0, y0, x, y, d;
        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
                return;

        if (!objectp(who = me->get_enemy()))
                return;

        if ((get_effect(me, EFFECT_CHAR_LAZY)) && me->inc_attack_speed() % 2)
        {
                // 在冰冻状态下继续启动动作控制的自动机，以免停止攻击
                set_heart_state(me, WALK_STAT);
                set_heart_count_2(me, 10);
                return; // 战斗速度减半(漫天缤纷)
        }

        //      if( distance_between(me, who) < 15 )
        {
                if (me->perform_action(who)) // 特技出招(动作)
                {
                        me->set_enemy_3(who);
                        set_heart_state(me, FIGHT_STAT);
                        set_heart_count_2(me, 7);
                        me->add_2("go_count.count2", 7);

                        if (who = me->get_enemy_5()) // 顺势推舟
                        {
                                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 23211, 1, OVER_BODY, PF_ONCE);
                        }
                }
                else if (CHAR_FIGHT_D->attack_action(me, who)) // 普通攻击(动作)
                {
                        me->set_enemy_3(who);
                        set_heart_state(me, FIGHT_STAT);
                        set_heart_count_2(me, 7);
                        me->add_2("go_count.count2", 7);

                        if (who = me->get_enemy_5()) // 顺势推舟
                        {
                                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 23211, 1, OVER_BODY, PF_ONCE);
                        }
                }
        }
        //      else    me->set_enemy(0);
}

// 函数：人物心跳处理
void heart_beat_cast(object me) // 每 0.8 秒处理
{
        object *char;
        string file;
        int flag;

        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
                return;

        if (stringp(file = me->get_cast_file()) && load_object(file))
        {
                file->cast_done(me); // 1: 法术失败；2: 法术成功 -- 没有必要区分

                me->set_cast_file(0); // 初始化参数
                me->set_cast_arg("");

                char = get_scene_object_2(me, USER_TYPE);
                send_user(char, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END); // 结束施法动作
                if (flag = file->get_cast_seal())
                        send_user(char, "%c%d%w%c%c%c", 0x6f, getoid(me), flag, 1, UNDER_FOOT, PF_STOP); // 结束符法效果
        }
}

// 函数：人物心跳处理
// void heart_beat_other( object me ) { }    // 每１秒处理

//查找可以跟随的玩家
int check_follow(object me, object who, int jump)
{
        int x, y, z, dist;
        if (who->is_store_open())
                return 0;
        if (get_effect(who, EFFECT_CHAR_BUSY))
                return 0;
        if (get_effect(who, EFFECT_CHAR_FAINT) || get_effect(who, EFFECT_CHAR_FAINT_2) || get_effect(who, EFFECT_SLEEP) || get_effect(who, EFFECT_CHAR_NO_MOVE) || get_effect(who, EFFECT_CHAR_FREEZE) || get_effect(who, EFFECT_CHAR_SHUT))
                return 0;
        if (get_effect(who, EFFECT_CHAR_DREAM_1) || get_effect(who, EFFECT_CHAR_DREAM))
                return 0;
        //距离在1到15格内则可以跟随走路或者跳转
        if (jump)
        {
                z = jump / 1000000;
                x = jump % 1000000 / 1000;
                y = jump % 1000000 % 1000;
                if (z != get_z(who))
                        return 0;
                if (abs(x - get_x(who) > 15) || abs(y - get_y(who) > 15))
                        return 0;
        }
        else
        {
                if (get_z(me) != get_z(who))
                        return 0;
                dist = distance_between(me, who);
                if (dist > 15)
                        return 0;
                else if (dist <= 1)
                        return 0;
        }

        return 1;
}
//跟随玩家
void follow_user(object me, object who, int jump)
{
        int x0, y0, z0, x, y, z, p, dist, count;

        if (!check_follow(me, who, jump))
                return;
        if (jump) //跳转
        {
                z = get_z(me);
                x = get_x(me);
                y = get_y(me);
                who->add_to_scene(z, x, y);
                return;
        }
        else
                send_user(who, "%c%c%d%d%d", 0xA5, 2, me->get_number(), x0, y0);
}
//跟随队伍
void team_follow(object me, int jump)
{
        int i, size;
        object *nTeam, *nMember;

        nTeam = me->get_team();
        if (!nTeam)
                return;
        nTeam -= ({me, 0});
        size = sizeof(nTeam);
        if (!size)
                return;
        nMember = ({});
        for (i = 0; i < size; i++)
        {
                if (nTeam[i]->get("team_follow") == 0)
                        continue;
                nMember += ({nTeam[i]});
        }
        if (!(size = sizeof(nMember)))
                return;
        for (i = 0; i < size; i++)
                follow_user(me, nMember[i], jump);
}

#include <npc.h>
#include <cmd.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：人物心跳处理
void heart_beat_walk(object me) // 每 0.1 秒处理
{
        object who;
        int x, y, walk, speed;

        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
                return;

        if (get_effect(me, EFFECT_CHAR_LAZY) || get_effect(me, EFFECT_CHAR_SLOW))
                speed = me->get_walk_speed() * 2;
        else
                speed = me->get_walk_speed();

        if (me->get_action_mode() == 1) //主动寻敌
        {

                if (time() - me->get("2122") < 6)
                {

                        ;
                }
                else
                {
                        if (time() - me->get("att_time") > 4)
                        {
                                if ((who = me->get_main_enemy()) && who->can_fight(me)) // 搜索何人攻击(最重要的敌人)
                                        me->set_enemy(who);
                                else if (!me->is_quanDoan() &&who = get_near_object(get_z(me), get_x(me), get_y(me), me->get_max_seek(), USER_TYPE)) // 搜索最近玩家
                                {

                                        me->auto_fight(who);
                                        me->init_enemy_damage(who, 0);
                                        me->set("att_time", time());
                                }
                                else if (me->is_quanDoan()) // 搜索最近玩家
                                {

                                        if (who = get_near_object(get_z(me), get_x(me), get_y(me), me->get_max_seek(), CHAR_TYPE))
                                        {

                                                if (!me->can_fight(who))
                                                {

                                                        GO_CMD->main_npc(me, sprintf("%d", random(8) + 1));
                                                }
                                                else
                                                {

                                                        me->auto_fight(who);
                                                        me->init_enemy_damage(who, 0);
                                                }
                                        }
                                        else
                                        {

                                                GO_CMD->main_npc(me, sprintf("%d", random(8) + 1));
                                        }
                                }
                        }
                }
        }
        if (me->get_action() == 0)
                return;
        if (gone_time(me->get_attack_time()) > 10)
                me->init_enemy_damage(0, 0); // 清除伤害状态

        if (objectp(who = me->get_enemy()))
        {
                if (who->is_die())
                {
                        me->set_enemy(0);
                        //                        if (me->get_action_mode()==0) me->set_action_mode(2);
                }
                else
                {
                        if (!me->get_action())
                                return;
                        x = get_x(me);
                        y = get_y(me);

                        me->follow_user();

                        x = abs(x - get_x(me));
                        y = abs(y - get_y(me));
                        walk = (x > y) ? x : y;

                        if (walk > 0) //是否走路
                        {
                                set_heart_state(me, 0);
                                if (speed > 2 * walk + 1)
                                        set_heart_count_2(me, speed);
                                else
                                        set_heart_count_2(me, 2 * walk + 1); // walk * 10 / 4
                        }
                }
        }
}

// 函数：人物心跳处理
void heart_beat_attack(object me) // 每 0.1 秒处理
{
        object who;
        int speed;

        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
                return;
        if (me->get_save("sungvatthach") > 0)
        {
                if (gone_time(me->get("sungvatthachtime")) >= 1)
                {
                        me->delete ("sungvatthachtime");
                        me->add_save("sungvatthach", -2);
                        me->add_hp(100);
                        me->add_mp(100);
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE);
                }
                me->set("sungvatthachtime", time());
        }

        //        if( me->get_action_mode()==0 ) return;		// 被动型不攻击
        //        if (me->get_action()==2) return;		// 赶回主人处，不攻击
        if (get_effect(me, EFFECT_CHAR_LAZY))
                speed = me->get_attack_speed() * 2;
        else
                speed = me->get_attack_speed();

        if (objectp(who = me->get_enemy()))
        {
                if (who->is_die())
                {
                        me->set_enemy(0);
                }
                else if (!get_effect_3(me, EFFECT_CHAR_BLIND) && me->perform_action(who)) // 特技出招(动作)(暗器、法术投掷)
                {
                        me->set_enemy_3(who);
                        //                      	set_heart_state(me, FIGHT_STAT);
                        set_heart_count_2(me, 7);
                }
                else if (CHAR_FIGHT_D->attack_action(me, who)) // 普通攻击(动作)
                {
                        me->set_enemy_3(who);
                        set_heart_state(me, FIGHT_STAT);
                        set_heart_count_2(me, 7);
                }
        }
}

// 函数：人物心跳处理
void heart_beat_cast(object me) // 每 0.8 秒处理
{
        object *char;
        string file;
        int flag;

        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
                return;
        if (me->get_save("sungvatthach") > 0)
        {
                if (gone_time(me->get("sungvatthachtime")) >= 1)
                {
                        me->delete ("sungvatthachtime");
                        me->add_save("sungvatthach", -2);
                        me->add_hp(100);
                        me->add_mp(100);
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE);
                }
                me->set("sungvatthachtime", time());
        }

        //        if( me->get_action_mode()==0 ) return;

        if (stringp(file = me->get_cast_file()) && load_object(file))
        {
                file->cast_done_npc(me); // 1: 法术失败；2: 法术成功 -- 没有必要区分
                if (!me)
                        return;
                me->set_cast_file(0); // 初始化参数
                me->set_cast_arg("");

                char = get_scene_object_2(me, USER_TYPE);
                send_user(char, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END); // 结束施法动作
                if (flag = file->get_cast_seal())
                        send_user(char, "%c%d%w%c%c%c", 0x6f, getoid(me), flag, 1, UNDER_FOOT, PF_STOP); // 结束符法效果
        }
}

// 函数：人物心跳处理
void heart_beat_other(object me) // 每１秒处理
{
        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
                return;

        if (!me->get_action())
                return;

        if (!me->get_enemy()) // 没有仇敌
        {
                if (have_scene_object(get_z(me), get_x(me), get_y(me), USER_TYPE))
                        set_heart_idle(me, 0);
                else
                        set_heart_idle(me, range_value(get_heart_idle(me) + 1, 1, 10));

                switch (me->get_char_type())
                {
                case FIGHTER_TYPE:
                case FIGHTER_TYPE_2:
                        if (!random(20 / range_value(get_heart_idle(me), 1, 10)))
                                GO_CMD->main_npc(me, sprintf("%d", random(8) + 1)); // 随机走路
                        break;
                }
        }
}

// 函数：人物心跳处理
void heart_beat_8sec(object me) // 每８秒处理
{
        if (me->is_zombie())
        {
                me->add_hp(me->get_max_hp() / 100);
                me->add_mp(me->get_max_mp() / 100);
                if (get_effect(me, EFFECT_CHAR_HALFGOD))
                        set_effect(me, EFFECT_CHAR_HALFGOD, 100);
        }
}

// -------------------------------------------------------------

// 函数：跟随对手(心跳之中调用)
void follow_user(object me)
{
        object who, *char, owner;
        string cmd = "", place;
        int z, z0, x0, y0, xy0, x, y, d, p;
        int *dir, i, size;

        if (!objectp(who = me->get_enemy()))
        {
                if (!me->get_action())
                        return;
                if (have_scene_object(get_z(me), get_x(me), get_y(me), USER_TYPE))
                        ;
                else
                {
                        place = me->get_start_place();
                        if (place)
                        {
                                sscanf(place, "%d", p);
                                if (p > 0 && (abs((p / 1000) - get_x(me)) > 4 || abs((p % 1000) - get_y(me)) > 4))
                                {
                                        me->add_to_scene(get_z(me), p / 1000, p % 1000, 3);
                                }
                        }
                }
                return;
        }

        z = get_z(who);
        x = get_x(who);
        y = get_y(who);
        z0 = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);
        xy0 = x0 * 1000 + y0;
        d = distance_between(me, who);

        if (z != z0 || d > 20) // 过远放弃
        {
                me->set_enemy(0); // stop_fight();
                if (have_scene_object(z0, x0, y0, USER_TYPE))
                        ;
                else
                {
                        place = me->get_start_place();
                        if (place)
                        {
                                sscanf(place, "%d", p);
                                if (p > 0 && (abs((p / 1000) - get_x(me)) > 4 || abs((p % 1000) - get_y(me)) > 4))
                                {
                                        me->add_to_scene(z0, p / 1000, p % 1000, 3);
                                }
                        }
                }
                return;
        }

        if (me->is_smart_caster()) // 游击战模式
        {
                if (d >= 6) // 接近对手
                {
                        p = get_valid_path(z, x0, y0, x, y);
                }
                else if (d >= 3) // 站立不动
                {
                        return;
                }
                else // 离开对手
                {
                        if (x0 > x)
                        {
                                if (y0 > y)
                                {
                                        if (p = get_valid_path(z, x0, y0, (x + 4), y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, x, y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y - 4))
                                                ;
                                }
                                else if (y0 == y)
                                {
                                        if (p = get_valid_path(z, x0, y0, (x + 4), y))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, x, y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, x, y - 4))
                                                ;
                                }
                                else
                                {
                                        if (p = get_valid_path(z, x0, y0, (x + 4), y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, x, y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y - 4))
                                                ;
                                }
                        }
                        else if (x0 == x)
                        {
                                if (y0 > y)
                                {
                                        if (p = get_valid_path(z, x0, y0, x, y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y))
                                                ;
                                }
                                else if (y0 == y)
                                        ;
                                else
                                {
                                        if (p = get_valid_path(z, x0, y0, x, y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y))
                                                ;
                                }
                        }
                        else
                        {
                                if (y0 > y)
                                {
                                        if (p = get_valid_path(z, x0, y0, (x - 4), y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, x, y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y + 4))
                                                ;
                                }
                                else if (y0 == y)
                                {
                                        if (p = get_valid_path(z, x0, y0, (x - 4), y))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y + 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, x, y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, x, y + 4))
                                                ;
                                }
                                else
                                {
                                        if (p = get_valid_path(z, x0, y0, (x - 4), y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, x, y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x + 4), y - 4))
                                                ;
                                        else if (p = get_valid_path(z, x0, y0, (x - 4), y + 4))
                                                ;
                                }
                        }
                }
        }
        else if (d > 1)
                p = get_valid_path(z, x0, y0, x, y); // 接近对手    // 普通 NPC
        else
        {
                me->set_action(me->get_next_action());
                return;
        }

        if (p) // 找到可走路径
        {
                cmd = sprintf("%d", p);

                switch (me->get_walk_step())
                {
                case 0:
                case 1:
                        if (strlen(cmd) > 1)
                                cmd = cmd[0..0];
                        break;
                case 2:
                        if (strlen(cmd) > 2)
                                cmd = cmd[0..1];
                        break;
                default:
                        break;
                }
                GO_CMD->main_npc(me, cmd);
        }
        else // 向后寻找
        {
                dir = ({});
                if (p = get_valid_path(z, x0, y0, (x - 3), y + 3))
                        dir += ({p});
                if (p = get_valid_path(z, x0, y0, (x - 3), y - 3))
                        dir += ({p});
                if (p = get_valid_path(z, x0, y0, (x - 3), y))
                        dir += ({p});
                if (p = get_valid_path(z, x0, y0, (x + 3), y + 3))
                        dir += ({p});
                if (p = get_valid_path(z, x0, y0, (x + 3), y - 3))
                        dir += ({p});
                if (p = get_valid_path(z, x0, y0, (x + 3), y))
                        dir += ({p});
                if (p = get_valid_path(z, x0, y0, x, y + 3))
                        dir += ({p});
                if (p = get_valid_path(z, x0, y0, x, y - 3))
                        dir += ({p});
                size = sizeof(dir);
                if (size > 0)
                        p = dir[random(size)];
                else
                        p = 0;
                if (p) // 找到可走路径
                {
                        cmd = sprintf("%d", p);

                        switch (me->get_walk_step())
                        {
                        case 0:
                        case 1:
                                if (strlen(cmd) > 1)
                                        cmd = cmd[0..0];
                                break;
                        case 2:
                                if (strlen(cmd) > 2)
                                        cmd = cmd[0..1];
                                break;
                        default:
                                break;
                        }
                        GO_CMD->main_npc(me, cmd);
                        //                      me->to_front_xy(x, y);    // 转回目标方向
                }
                else if (sizeof_range_object(z, x0, y0, 1, CHAR_TYPE) + sizeof_range_object(z, x0, y0, 1, USER_TYPE) < 9) // 随机乱走
                {
                        dir = ({});
                        if (!(get_block(z, x0 + 1, y0) & IS_CHAR_BLOCK))
                                dir += ({111});
                        if (!(get_block(z, x0 + 1, y0 - 1) & IS_CHAR_BLOCK))
                                dir += ({222});
                        if (!(get_block(z, x0, y0 - 1) & IS_CHAR_BLOCK))
                                dir += ({333});
                        if (!(get_block(z, x0 - 1, y0 - 1) & IS_CHAR_BLOCK))
                                dir += ({444});
                        if (!(get_block(z, x0 - 1, y0) & IS_CHAR_BLOCK))
                                dir += ({555});
                        if (!(get_block(z, x0 - 1, y0 + 1) & IS_CHAR_BLOCK))
                                dir += ({666});
                        if (!(get_block(z, x0, y0 + 1) & IS_CHAR_BLOCK))
                                dir += ({777});
                        if (!(get_block(z, x0 + 1, y0 + 1) & IS_CHAR_BLOCK))
                                dir += ({888});

                        if ((size = sizeof(dir)) && (p = dir[random(size)])) // 找到可走路径
                        {
                                cmd = sprintf("%d", p);

                                switch (me->get_walk_step())
                                {
                                case 0:
                                case 1:
                                        if (strlen(cmd) > 1)
                                                cmd = cmd[0..0];
                                        break;
                                case 2:
                                        if (strlen(cmd) > 2)
                                                cmd = cmd[0..1];
                                        break;
                                default:
                                        break;
                                }
                                GO_CMD->main_npc(me, cmd);

                                //                              me->to_front_xy(x, y);    // 转回目标方向
                        }
                        else // 随机攻击挡路者
                        {
                                if (objectp(who = me->get_owner()) && who->is_user()) // 有主 NPC(僵尸)
                                {
                                        if (size = sizeof(char = get_range_object_2(me, 1, USER_TYPE) + get_range_object_2(me, 1, CHAR_TYPE)))
                                        {
                                                for (i = 0; i < size; i++)
                                                        if (char[i]->can_be_fighted(me) && me->can_fight(char[i]))
                                                        {
                                                                me->start_fight(char[i]);
                                                                break;
                                                        }
                                        }
                                }
                                else // 普通 NPC
                                {
                                        if (size = sizeof(char = get_range_object_2(me, 1, USER_TYPE)))
                                        {
                                                me->start_fight(char[random(size)]);
                                        }
                                        else if (size = sizeof(char = get_range_object_2(me, 1, CHAR_TYPE)))
                                        {
                                                for (i = 0; i < size; i++)
                                                        if (objectp(who = char[i]->get_owner()) && who->is_user())
                                                        {
                                                                me->start_fight(char[i]);
                                                                break;
                                                        }
                                        }
                                }
                        }
                }
        }
}

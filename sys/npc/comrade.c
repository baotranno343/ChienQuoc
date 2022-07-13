
#include <cmd.h>
#include <effect.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

/*
object get_near_object2(object * char, int z, int x, int y)
{
        int i, size, min, cur_i;
        int x0, y0, z0, dx, dy;
        size = sizeof(char);
        cur_i = -1;
        if ( size==0 ) return 0;
        for (i=0;i<size;i++)
        {
                if (!char[i]) continue;
                z0 = get_z(char[i]);
                x0 = get_x(char[i]);
                y0 = get_y(char[i]);
                if (z0!=z) continue;
                if (cur_i==-1)
                {
                        dx = abs(x-x0);
                        dy = abs(y-y0);
                        if (dx>dy) min=dx;
                        else min=dy;
                        cur_i = i;
                }
                else
                {
                        dx = abs(x-x0);
                        dy = abs(y-y0);
                        if (dx>dy) dy=dx;
                        if (min>dy)
                        {
                                min = dy;
                                cur_i = i;
                        }
                }
        }
        if (cur_i==-1) return 0;
        return char[cur_i];
}       */

// 函数：人物心跳处理
void heart_beat_walk(object me) // 每 0.1 秒处理
{
        object map, who, *see, *char;
        string cmd;
        int z, x, y, x1, y1, dx, p, p2;
        int walk, seek, flag, *dir, i, size;

        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE))
                return;

        if (!me->get_action())
                return;

        if (who = me->get_main_enemy()) // 搜索何人攻击(最重要的敌人)
                me->set_enemy(who);
        else
        {
                z = get_z(me);
                x = get_x(me);
                y = get_y(me);
                seek = me->get_max_seek();

                see = get_range_object(z, x, y, seek, USER_TYPE) + get_range_object(z, x, y, seek, CHAR_TYPE); // 人物可见范围

                char = filter_array(see, (
                                             : objectp($1) && $1->get_manager() != $2->get_manager()
                                             :),
                                    me); // 所在不同帮派    // get_org_name() 是字串运算

                if (objectp(who = get_near_char(char, z, x, y)))
                        me->auto_fight(who);
        }

        if (gone_time(me->get_attack_time()) > 10)
                me->init_enemy_damage(0, 0); // 清除伤害状态

        z = get_z(me);
        x = get_x(me);
        y = get_y(me);

        if (objectp(who = me->get_enemy()))
        {
                me->set_distance_x(0); // 有敌人时，重设中线Ｘ距离

                if (who->is_die())
                {
                        me->set_enemy(0);
                        flag = 1;
                }
                else
                        me->follow_user();
        }
        else
                flag = 1;

        if (flag && objectp(map = get_map_object(z)) && (MAP_D->is_inside_battle(z) || map->is_changping2())) // 跟随指定路线
        {

                p = 0;

                if (map->is_inside_attack(z, x, y)) // 在攻击方阵地
                {

                        if (me->get_front() == 1) // 攻击方
                        {

                                if (map->is_inside_road_1(z, x, y)) // 在路线１内
                                        p2 = QUEST_BATTLE->get_comrade_point(z, 10);
                                else if (!map->is_inside_road_3(z, x, y)) // 在路线２内
                                        p2 = QUEST_BATTLE->get_comrade_point(z, 11);
                                else
                                        p2 = QUEST_BATTLE->get_comrade_point(z, 12);

                                p = get_valid_path(z, x, y, p2 / 1000, p2 % 1000);
                        }
                        else // 防守方
                        {
                                p2 = QUEST_BATTLE->get_valid_manager_xy(z, 1);
                                p = get_valid_path(z, x, y, p2 / 1000, p2 % 1000);
                        }
                }
                else if (map->is_inside_defense(z, x, y)) // 在防守方阵地
                {
                        if (me->get_front() == 1) // 攻击方
                        {
                                p2 = QUEST_BATTLE->get_valid_manager_xy(z, 2);
                                p = get_valid_path(z, x, y, p2 / 1000, p2 % 1000);
                        }
                        else // 防守方
                        {
                                if (map->is_inside_road_1(z, x, y)) // 在路线１内
                                        p2 = QUEST_BATTLE->get_comrade_point(z, 15);
                                else if (!map->is_inside_road_3(z, x, y)) // 在路线２内
                                        p2 = QUEST_BATTLE->get_comrade_point(z, 16);
                                else
                                        p2 = QUEST_BATTLE->get_comrade_point(z, 17);

                                p = get_valid_path(z, x, y, p2 / 1000, p2 % 1000);
                        }
                }
                else if (map->is_inside_road_1(z, x, y)) // 在路线１内
                {

                        if (!(dx = me->get_distance_x()))
                        {
                                dx = x - map->get_road_1_x(y);
                                me->set_distance_x(dx); // 初始化中线Ｘ距离
                        }
                        if (me->get_front() == 1) // 攻击方
                        {
                                x1 = map->get_road_1_x(y + 3);
                                y1 = y + 3;
                        }
                        else // 防守方
                        {
                                x1 = map->get_road_1_x(y - 3);
                                y1 = y - 3;
                        }
                        p = get_valid_path(z, x, y, (x1 + dx), y1);
                        if (!p)
                                p = get_valid_path(z, x, y, x1, y1);
                }
                else if (!map->is_inside_road_3(z, x, y)) // 在路线２内
                {

                        if (!(dx = me->get_distance_x()))
                        {
                                dx = x - map->get_road_2_x(y);
                                me->set_distance_x(dx); // 初始化中线Ｘ距离
                        }
                        if (me->get_front() == 1) // 攻击方
                        {
                                x1 = map->get_road_2_x(y + 3);
                                y1 = y + 3;
                        }
                        else // 防守方
                        {
                                x1 = map->get_road_2_x(y - 3);
                                y1 = y - 3;
                        }
                        p = get_valid_path(z, x, y, (x1 + dx), y1);
                        if (!p)
                                p = get_valid_path(z, x, y, x1, y1);
                }
                else // 在路线３内
                {

                        if (!(dx = me->get_distance_x()))
                        {
                                dx = x - map->get_road_3_x(y);
                                me->set_distance_x(dx); // 初始化中线Ｘ距离
                        }
                        if (me->get_front() == 1) // 攻击方
                        {
                                x1 = map->get_road_3_x(y + 3);
                                y1 = y + 3;
                        }
                        else // 防守方
                        {
                                x1 = map->get_road_3_x(y - 3);
                                y1 = y - 3;
                        }
                        p = get_valid_path(z, x, y, (x1 + dx), y1);
                        if (!p)
                                p = get_valid_path(z, x, y, x1, y1);
                }

                if (p) // 找到可走路径
                {

                        cmd = sprintf("%d", p);

                        switch (me->get_walk_step())
                        {
                        default:
                                if (strlen(cmd) > 1)
                                        cmd = cmd[0..0];
                                break;
                        case 2:
                                if (strlen(cmd) > 2)
                                        cmd = cmd[0..1];
                                break;
                        }

                        GO_CMD->main_npc(me, cmd);
                }
                else if (sizeof_range_object(z, x, y, 1, CHAR_TYPE) + sizeof_range_object(z, x, y, 1, USER_TYPE) < 9) // 随机乱走
                {

                        dir = ({});
                        if (!(get_block(z, x + 1, y) & IS_CHAR_BLOCK))
                                dir += ({111});
                        if (!(get_block(z, x + 1, y - 1) & IS_CHAR_BLOCK))
                                dir += ({222});
                        if (!(get_block(z, x, y - 1) & IS_CHAR_BLOCK))
                                dir += ({333});
                        if (!(get_block(z, x - 1, y - 1) & IS_CHAR_BLOCK))
                                dir += ({444});
                        if (!(get_block(z, x - 1, y) & IS_CHAR_BLOCK))
                                dir += ({555});
                        if (!(get_block(z, x - 1, y + 1) & IS_CHAR_BLOCK))
                                dir += ({666});
                        if (!(get_block(z, x, y + 1) & IS_CHAR_BLOCK))
                                dir += ({777});
                        if (!(get_block(z, x + 1, y + 1) & IS_CHAR_BLOCK))
                                dir += ({888});

                        if ((size = sizeof(dir)) && (p = dir[random(size)])) // 找到可走路径
                        {
                                cmd = sprintf("%d", p);

                                switch (me->get_walk_step())
                                {
                                default:
                                        if (strlen(cmd) > 1)
                                                cmd = cmd[0..0];
                                        break;
                                case 2:
                                        if (strlen(cmd) > 2)
                                                cmd = cmd[0..1];
                                        break;
                                }

                                GO_CMD->main_npc(me, cmd);
                        }
                }
        }

        x = abs(x - get_x(me));
        y = abs(y - get_y(me));
        walk = (x > y) ? x : y;

        if (walk > 0)
        {
                set_heart_state(me, 0);
                set_heart_count_2(me, 2 * walk + 1); // walk * 10 / 4
        }
}

// 函数：判断可以战斗
int can_fight(object me, object who)
{
        if (me->get_no_fight())
                return 0;
        if (me == who)
                return 0; // 禁止攻击自己

        if (me->get_manager() == who->get_manager())
                return 0; // 禁止攻击帮众    // get_org_name() 是字串运算

        return 1;
}

// 函数：可以接受战斗
int can_be_fighted(object me, object who)
{
        if (me->get_no_fight())
                return 0;

        if (me->get_manager() == who->get_manager())
                return 0; // 禁止攻击帮众    // get_org_name() 是字串运算

        return 1;
}


#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
varargs int main(object me, string arg, int server) // server 是否系统端走路，用于 EFFECT_CHAR_DREAM
{
        object map, *user, *user2, *npc, *item, who;
        string chan, id;
        int z0, x0, y0, z1, x1, y1, z, x, y, dx, dy, d, walk, time2;
        int busy, p, i, size;
        int current_count, heart, count, walkspeed;

        if (!arg || arg == "")
                return 1;
        me->set("new_heart", 1); // 新走路的标志

        if (sscanf(arg, ">%d", d)) // 转身指令(不管忙乱)
        {
                switch (d)
                {
                case 1:
                        me->to_front(1);
                        break;
                default:
                        me->to_front(2);
                        break;
                case 3:
                        me->to_front(3);
                        break;
                case 4:
                        me->to_front(4);
                        break;
                case 5:
                        me->to_front(5);
                        break;
                case 6:
                        me->to_front(6);
                        break;
                case 7:
                        me->to_front(7);
                        break;
                case 8:
                        me->to_front(8);
                        break;
                }
                return 1;
        }
        // 修改出问题的双倍时间
        /*        
        if ( gone_time( me->get_login_time())+ me->get_game_time()+2*3600<me->get_double_time())
        {
        	me->set_double_time(gone_time( me->get_login_time())+ me->get_game_time()+2*3600);
        }
*/
        z0 = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);

        if (me->is_store_open())
        {
                //              notify( "您在摆摊，不能乱跑。" );
                send_user(me, "%c%w%w", 0x07, x0, y0); // 坐标修正
                return 1;
        }
        if (busy = get_effect(me, EFFECT_CHAR_BUSY))
        {
                notify("Bạn còn phải bận %d giây", busy);
                send_user(me, "%c%w%w%c", 0x07, x0, y0, 1); // 坐标修正
                return 1;
        }
        if (get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_NO_MOVE) || get_effect(me, EFFECT_CHAR_FREEZE) || get_effect(me, EFFECT_CHAR_SHUT))
        {
                send_user(me, "%c%w%w%c", 0x07, x0, y0, 2); // 坐标修正
                return 1;
        }
        if ((get_effect(me, EFFECT_CHAR_DREAM_1) || get_effect(me, EFFECT_CHAR_DREAM)) && !server) // 梦游(随机走路)失魂
        {
                send_user(me, "%c%w%w%c", 0x07, x0, y0, 3); // 坐标修正
                return 1;
        }

        CHAR_CHAR_D->stop_loop_perform_go(me); // 中断走路会影响的效果
        // 判断中断效果是否影响了位置
        if (get_z(me) != z0 || get_x(me) != x0 || get_y(me) != y0)
                return 1;

        current_count = me->get_2("go_count.count2");

        if (sscanf(arg, "%d,%d %s %d", x, y, arg, time2) != 4)
        {
                return 1;
        }
        // 比较服务器记录的走路记录和玩家发来的对不对得上
        if (current_count < time2)
        {
                current_count = time2;
                me->set_2("go_count.count2", current_count);
        }
        else if (current_count > time2)
        {
                notify("客户端时钟不对");
                send_user(me, "%c%w%w%c%w", 0x07, x0, y0, 4, current_count - time2); // 时间戳不对
                return 1;
        }
        if (current_count > get_heart_timer(me))
        {
                if (get_heart_beat(me))
                {
                        notify("客户端时钟过快");
                        send_user(me, "%c%w%w%c%w", 0x07, x0, y0, 5, current_count - get_heart_timer(me)); // 时间戳不对
                        return 1;
                }
        }
        if (x0 != x || y0 != y)
        {
                send_user(me, "%c%w%w%c", 0x07, x0, y0, 6); // 坐标修正
                return 1;
        }
        if (!arg || arg == "")
        {
                send_user(me, "%c%w%w%c", 0x07, x0, y0, 7); // 坐标修正
                return 1;
        }
        walkspeed = 3;
        if (get_effect(me, EFFECT_CHAR_SLOW) || (get_effect(me, EFFECT_CHAR_LAZY) || (get_effect(me, EFFECT_CHAR_INVISIBLE) && !get_effect(me, EFFECT_03643) && !me->get_save("no_visible"))))
                walkspeed = 6;
        if (get_effect(me, EFFECT_CHAR_SLOW) || (get_effect(me, EFFECT_CHAR_LAZY) || (get_effect(me, EFFECT_CHAR_INVISIBLE) && !get_effect(me, EFFECT_03643) && !me->get_save("no_visible"))) && sizeof(arg) > 1)
                arg = arg[0..0]; // 隐身，移动变慢

        else if (sizeof(arg) > 3)
                arg = arg[0..1];

        if (!(p = from_here(z0, x0, y0, arg, IS_MAP_BLOCK))) // 能否通过？
        {
                send_user(me, "%c%w%w%c", 0x07, x0, y0, 9); // 坐标修正
                return 1;
        }
        x = p / 10000;
        y = (p % 10000) / 10;
        d = p % 10;

        if (x0 == x && y0 == y) // 没有移动
        {
                send_user(me, "%c%w%w%c", 0x07, x0, y0, 10); // 坐标修正
                return 1;
        }
        if (!inside_map(z0, x, y)) // 坐标错误
        {
                send_user(me, "%c%w%w%c", 0x07, x0, y0, 11); // 坐标修正
                return 1;
        }
        if (get_effect(me, EFFECT_CHAR_CHAN) // 被人缠住(粘手)
            && stringp(chan = me->get_save("pf.chan")) && sscanf(chan, "%d:(%d,%d)", z1, x1, y1) == 3 && (abs(x1 - x) > 2 || abs(y1 - y) > 2))
        {
                send_user(me, "%c%w%w%c", 0x07, x0, y0, 12); // 坐标修正
                return 1;
        }
        if (objectp(who = me->get_quest("escort.robber#"))                              // 寻找蒙面人
            && who->is_escort_robber() && !inside_screen(x, y, get_x(who), get_y(who))) // 移动受限制  // !inside_screen_2(me, who)
        {
                if (get_z(me) != get_z(who)) // 如果地图不对
                {
                        who->destruct_npc_callout(who, me);
                }
                else
                {
                        notify(who->get_name() + "Xuất hiện, hành động của bạn bị ảnh hưởng");
                        send_user(me, "%c%w%w%c", 0x07, x0, y0, 13); // 坐标修正
                        return 1;
                }
        }
        if (me->get_attack_move() && me->get_enemy())
        {
                printf(ECHO "你中止了“自动射击”。");
                me->set_enemy(0); // 取消自动攻击目标
        }

        if (me->get_char_action() != DEFAULT_ACT)
                me->set_char_action(DEFAULT_ACT); // 恢复站立状态(中止小动作)

        dx = abs(x0 - x);
        dy = abs(y0 - y);
        walk = (dx > dy) ? dx : dy;

        // 判断是否走路过快
        me->add_2("go_count.count2", walk * walkspeed);

        set_heart_state(me, WALK_STAT);
        //set_heart_count_2( me, range_value( current_count + (4 * walk+1)/2, -10, MAX_NUMBER ) );    // walk * 10 / 4
        if (me->get_attack_move() == 0 && objectp(who = me->get_enemy()))
        {
                if (distance_between(me, who) == 1)
                        set_heart_count_2(me, range_value(current_count + 2 * walk, -10, MAX_NUMBER));
        }
        else
                set_heart_count_2(me, range_value(current_count + 4 * walk, -10, MAX_NUMBER));
        //tell_user(me, ECHO "get_heart_count_2 %d。heat_beat %d", get_heart_count_2(me), get_heart_timer(me) );

        dx = (x / AREA_SIZE) - (x0 / AREA_SIZE);
        dy = (y / AREA_SIZE) - (y0 / AREA_SIZE);

        if (dx == 0 && dy == 0) // 本场景内行走
        {
                remove_block(z0, x0, y0, CHAR_BLOCK);
                set_x(me, x);
                set_y(me, y);
                set_d(me, d);
                set_block(z0, x, y, CHAR_BLOCK);

                user = get_scene_object(z0, x, y, USER_TYPE);
                if (sizeof(arg) == 1)
                        send_user(user, "%c%d%d%w%w%s", 0x67, getoid(me), time2(), x0, y0, arg);
                else
                        send_user(user, "%c%d%d%w%w%c%c%c%s", 0x47, getoid(me), time2(), x0, y0, x - x0, y - y0, d, arg);

                me->set_no_fight(MAP_D->is_inside_safe_zone(z0, x, y) ? 1 : 0); // 安全区判断
        }
        else // 跨越场景行走
        {
                if (dx < 0)
                {
                        if (dy < 0)
                        {
                                dx = 0x12e;
                                dy = 0x1d2;
                        }
                        else if (dy > 0)
                        {
                                dx = 0x1e8;
                                dy = 0x5e;
                        }
                        else
                        {
                                dx = 0x128;
                                dy = 0x52;
                        }
                }
                else if (dx > 0)
                {
                        if (dy < 0)
                        {
                                dx = 0x5e;
                                dy = 0x1e8;
                        }
                        else if (dy > 0)
                        {
                                dx = 0x1d2;
                                dy = 0x12e;
                        }
                        else
                        {
                                dx = 0x52;
                                dy = 0x128;
                        }
                }
                else
                {
                        if (dy < 0)
                        {
                                dx = 0xe;
                                dy = 0x1c0;
                        }
                        else
                        {
                                dx = 0x1c0;
                                dy = 0xe;
                        }
                }

                remove_block(z0, x0, y0, CHAR_BLOCK); // 删除阻挡

                user = get_scene_object(z0, x0, y0, USER_TYPE, dx); // 删除对象
                npc = get_scene_object(z0, x0, y0, CHAR_TYPE, dx);
                item = get_scene_object(z0, x0, y0, ITEM_TYPE, dx);
                user->remove_to_user(me);
                npc->remove_to_user(me);
                item->remove_to_user(me);

                item = get_scene_object(z0, x0, y0, SEAL_TYPE, dx);
                item->remove_to_user_2(me);

                set_x(me, x);
                set_y(me, y);
                set_d(me, d); // 设置坐标，增加阻挡
                set_block(z0, x, y, CHAR_BLOCK);
                move_object(me, z0, x, y, USER_TYPE); // 移动玩家

                user2 = get_scene_object(z0, x, y, USER_TYPE, dy); // 新增对象
                npc = get_scene_object(z0, x, y, CHAR_TYPE, dy);
                item = get_scene_object(z0, x, y, ITEM_TYPE, dy);
                user2->show_to_user(me);
                npc->show_to_user(me);
                item->show_to_user(me);

                item = get_scene_object(z0, x, y, SEAL_TYPE, dy);
                item->show_to_user_2(me);

                me->show_to_scene(user2, x0, y0, d, 0);
                user2 = get_scene_object_2(me, USER_TYPE) + user;
                if (sizeof(arg) == 1)
                        send_user(user2, "%c%d%d%w%w%s", 0x67, getoid(me), time2(), x0, y0, arg);
                else
                        send_user(user2, "%c%d%d%w%w%c%c%c%s", 0x47, getoid(me), time2(), x0, y0, x - x0, y - y0, d, arg);

                send_user(user, "%c%d", 0x78, getoid(me));

                if (MAP_D->is_inside_safe_zone(z0, x, y)) // 安全区判断
                {
                        me->set_no_fight(1);
                }
                else
                {
                        me->set_no_fight(0);

                        npc = get_range_object_2(me, 6, CHAR_TYPE);
                        if (sizeof(npc))
                                npc->init_heart_beat_idle();
                }
        }

        if (!MAP_D->is_inside_copy(z0) && (p = get_jumpout(z0, x, y))                         // 跳转另一场景	副本场景不允许跳转
            && (!objectp(who = me->get_quest("escort.robber#")) || !who->is_escort_robber())) // 寻找蒙面人
        {
                z = p / 1000000;
                x = (p % 1000000) / 1000;
                y = p % 1000; // get_jumpout 内含 z

                if ((who = me->get_quest("escort.npc")) // 运镖人物
                    && who->get_owner() == me && inside_screen_2(me, who))
                        who->add_to_scene(z, x, y, d);
                if ((who = me->get_2("orgtask2.npc")) // 帮派任务
                    && who->get_owner() == me && inside_screen_2(me, who))
                        who->add_to_scene(z, x, y, d);

                if (p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK))
                {
                        x = p / 1000;
                        y = p % 1000;

                        me->set_login_flag(2); // 跳转保护
                        set_invisible(me, 1);
                        set_effect(me, EFFECT_USER_LOGIN, 4);

                        me->add_to_scene(z, x, y, d);

                        //                      if( z != z0 ) if( map = get_map_object(z) ) notify( map->get_name() );    // 显示地图名
                }
        }
        else if (MAP_D->is_inside_battle(z0)) // 战场
        {
                if (objectp(map = get_map_object(z0))) // 获取战场对象
                {
                        who = me->get_manager();
                        d = getoid(me);

                        if (map->get_manager() == who) // 攻击方
                        {
                                user = map->get_user_dbase();
                                send_user(user, "%c%c%d%w%w", 0x54, 10, d, x, y);
                                //                              for( i = 0, size = sizeof(user); i < size; i ++ )
                                //                                      if( objectp( who = user[i] ) ) send_user( who, "%c%c%d%w%w", 0x54, 10, d, x, y );
                        }
                        else if (map->get_manager_2() == who) // 防守方
                        {
                                user = map->get_user_2_dbase();
                                send_user(user, "%c%c%d%w%w", 0x54, 10, d, x, y);
                                //                              for( i = 0, size = sizeof(user); i < size; i ++ )
                                //                                      if( objectp( who = user[i] ) ) send_user( who, "%c%c%d%w%w", 0x54, 10, d, x, y );
                        }
                }
        }
        else if (arrayp(user = me->get_team())) // 更新队员坐标
        {
                user -= ({me, 0});
                user = filter_array(user, (
                                              : $1 && get_z($1) == $2:),
                                    z0);
                send_user(user, "%c%c%d%w%w", 0x54, 10, me->get_number(), x, y);
        }
        z0 = get_z(me);
        if (get_block(z0, x, y) & SEAL_BLOCK)
        {
                item = get_range_object_2(me, 0, SEAL_TYPE);
                if (sizeof(item) > 0)
                {
                        if (item[0]->is_self_seal())
                                item[0]->heart_beat_loop(0, 0, 0, 0, 0, 0, 0, 0);
                }
        }
        return 1;
}

// 函数：命令处理
int main_npc(object me, string arg)
{
        object map, *user, *user2, *npc, who;
        string chan;
        int z0, x0, y0, z1, x1, y1, z, x, y, dx, dy, d, p;

        if (!arg || arg == "")
                return 1;

        if (!me->is_moveable())
                return 1; // 不允许移动

        if (get_effect(me, EFFECT_CHAR_BUSY) || get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_NO_MOVE) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_CHAR_FREEZE) || get_effect(me, EFFECT_CHAR_SHUT))
                return 1;

        if (sizeof(arg) > 3)
                arg = arg[0..3];

        z0 = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);

        if (!(p = from_here(z0, x0, y0, arg, IS_CHAR_BLOCK)))
                return 1; // 能否通过？

        x = p / 10000;
        y = (p % 10000) / 10;
        d = p % 10;

        if (x0 == x && y0 == y)
                return 1; // 没有移动

        if (!inside_map(z0, x, y))
                return 1; // 坐标错误

        if (me->cannot_enter_city() && !me->get_owner() && MAP_D->is_inside_safe_zone(z0, x, y))
                return 1; // 怪物不能进城(小心亲友、宠物)

        if (get_effect(me, EFFECT_CHAR_CHAN) // 被人缠住(粘手)
            && stringp(chan = me->get_save("pf.chan")) && sscanf(chan, "%d:(%d,%d)", z1, x1, y1) == 3 && (abs(x1 - x) > 2 || abs(y1 - y) > 2))
        {
                //              send_user(me, "%c%w%w", 0x07, x0, y0);    // 坐标修正
                return 1;
        }

        dx = (x / AREA_SIZE) - (x0 / AREA_SIZE);
        dy = (y / AREA_SIZE) - (y0 / AREA_SIZE);

        if (dx == 0 && dy == 0) // 本场景内行走
        {
                remove_block(z0, x0, y0, CHAR_BLOCK);
                set_x(me, x);
                set_y(me, y);
                set_d(me, d);
                set_block(z0, x, y, CHAR_BLOCK);

                user = get_scene_object(z0, x, y, USER_TYPE);
                if (sizeof(arg) == 1)
                        send_user(user, "%c%d%d%w%w%s", 0x67, getoid(me), time2(), x0, y0, arg);
                else
                        send_user(user, "%c%d%d%w%w%c%c%c%s", 0x47, getoid(me), time2(), x0, y0, x - x0, y - y0, d, arg);

                me->set_no_fight(MAP_D->is_inside_safe_zone(z0, x, y) ? 1 : 0); // 安全区判断
        }
        else // 跨越场景行走
        {
                if (dx < 0)
                {
                        if (dy < 0)
                        {
                                dx = 0x12e;
                                dy = 0x1d2;
                        }
                        else if (dy > 0)
                        {
                                dx = 0x1e8;
                                dy = 0x5e;
                        }
                        else
                        {
                                dx = 0x128;
                                dy = 0x52;
                        }
                }
                else if (dx > 0)
                {
                        if (dy < 0)
                        {
                                dx = 0x5e;
                                dy = 0x1e8;
                        }
                        else if (dy > 0)
                        {
                                dx = 0x1d2;
                                dy = 0x12e;
                        }
                        else
                        {
                                dx = 0x52;
                                dy = 0x128;
                        }
                }
                else
                {
                        if (dy < 0)
                        {
                                dx = 0xe;
                                dy = 0x1c0;
                        }
                        else
                        {
                                dx = 0x1c0;
                                dy = 0xe;
                        }
                }

                remove_block(z0, x0, y0, CHAR_BLOCK); // 删除阻挡
                user = get_scene_object(z0, x0, y0, USER_TYPE, dx);

                set_x(me, x);
                set_y(me, y);
                set_d(me, d); // 设置坐标，增加阻挡
                set_block(z0, x, y, CHAR_BLOCK);
                objectp(who = me->get_owner()) && who->is_user() ? move_object(me, z0, x, y, USER_TYPE) : move_object(me, z0, x, y, CHAR_TYPE); // 移动 NPC
                user2 = get_scene_object(z0, x, y, USER_TYPE, dy);

                me->show_to_scene(user2, x0, y0, d, 0);
                user2 = get_scene_object_2(me, USER_TYPE) + user;
                if (sizeof(arg) == 1)
                        send_user(user2, "%c%d%d%w%w%s", 0x67, getoid(me), time2(), x0, y0, arg);
                else
                        send_user(user2, "%c%d%d%w%w%c%c%c%s", 0x47, getoid(me), time2(), x0, y0, x - x0, y - y0, d, arg);

                send_user(user, "%c%d", 0x78, getoid(me));

                if (MAP_D->is_inside_safe_zone(z0, x, y)) // 安全区判断
                {
                        me->set_no_fight(1);
                }
                else
                {
                        me->set_no_fight(0);

                        if (objectp(me->get_owner()))
                        {
                                npc = get_range_object_2(me, 6, CHAR_TYPE);
                                if (sizeof(npc))
                                        npc->init_heart_beat_idle();
                        }
                }
        }

        if (objectp(who = me->get_owner()) && who->is_user())
        {
                if (get_z(who) != get_z(me))
                {
                        send_user(who, "%c%c%d%w%w", 0x2c, 7, getoid(me), -1, -1); // 更新召唤兽坐标
                }
                else
                        send_user(who, "%c%c%d%w%w", 0x2c, 7, getoid(me), x, y); // 更新召唤兽坐标
        }

        return 1;
}

// -------------------------------------------------------------

// 函数：虚影快速移动
int main_fly(object me, int x, int y, int d, int flag)
{
        object map, *user, *user2, *npc, *item, who;
        int z0, x0, y0, z, dx, dy;
        int p, i, size;

        z0 = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);

        if (abs(x - x0) > 10 || abs(y - y0) > 10)
                return 1; // 距离过远
        if (!inside_map(z0, x, y))
                return 1; // 坐标非法
        if (get_block(z0, x, y) & IS_CHAR_BLOCK)
                return 1; // 无法落脚
        if (!from_to(z0, x0, y0, x - x0, y - y0, MAP_BLOCK))
                return 1; // 无法穿越

        if (objectp(who = me->get_quest("escort.robber#"))                              // 寻找蒙面人
            && who->is_escort_robber() && !inside_screen(x, y, get_x(who), get_y(who))) // 移动受限制  // !inside_screen_2(me, who)
                return 1;

        dx = (x / AREA_SIZE) - (x0 / AREA_SIZE);
        dy = (y / AREA_SIZE) - (y0 / AREA_SIZE);

        if (dx == 0 && dy == 0) // 本场景内瞬移
        {
                remove_block(z0, x0, y0, CHAR_BLOCK);
                set_x(me, x);
                set_y(me, y);
                set_d(me, d);
                set_block(z0, x, y, CHAR_BLOCK);

                user = get_scene_object(z0, x, y, USER_TYPE);
                //                send_user( user, "%c%d%d%w%w%w%w%c%c", 0x87, getoid(me), time2(), x0, y0, x, y, d, flag );

                me->set_no_fight(MAP_D->is_inside_safe_zone(z0, x, y) ? 1 : 0); // 安全区判断
        }
        else // 跨越场景瞬移
        {
                if (dx < 0)
                {
                        if (dy < 0)
                        {
                                dx = 0x12e;
                                dy = 0x1d2;
                        }
                        else if (dy > 0)
                        {
                                dx = 0x1e8;
                                dy = 0x5e;
                        }
                        else
                        {
                                dx = 0x128;
                                dy = 0x52;
                        }
                }
                else if (dx > 0)
                {
                        if (dy < 0)
                        {
                                dx = 0x5e;
                                dy = 0x1e8;
                        }
                        else if (dy > 0)
                        {
                                dx = 0x1d2;
                                dy = 0x12e;
                        }
                        else
                        {
                                dx = 0x52;
                                dy = 0x128;
                        }
                }
                else
                {
                        if (dy < 0)
                        {
                                dx = 0xe;
                                dy = 0x1c0;
                        }
                        else
                        {
                                dx = 0x1c0;
                                dy = 0xe;
                        }
                }

                remove_block(z0, x0, y0, CHAR_BLOCK); // 删除阻挡

                user = get_scene_object(z0, x0, y0, USER_TYPE, dx); // 删除对象
                npc = get_scene_object(z0, x0, y0, CHAR_TYPE, dx);
                item = get_scene_object(z0, x0, y0, ITEM_TYPE, dx);
                user->remove_to_user(me);
                npc->remove_to_user(me);
                item->remove_to_user(me);

                item = get_scene_object(z0, x0, y0, SEAL_TYPE, dx);
                item->remove_to_user_2(me);

                set_x(me, x);
                set_y(me, y);
                set_d(me, d); // 设置坐标，增加阻挡
                set_block(z0, x, y, CHAR_BLOCK);
                move_object(me, z0, x, y, USER_TYPE); // 移动玩家

                user2 = get_scene_object(z0, x, y, USER_TYPE, dy); // 新增对象
                npc = get_scene_object(z0, x, y, CHAR_TYPE, dy);
                item = get_scene_object(z0, x, y, ITEM_TYPE, dy);
                user2->show_to_user(me);
                npc->show_to_user(me);
                item->show_to_user(me);

                item = get_scene_object(z0, x, y, SEAL_TYPE, dy);
                item->show_to_user_2(me);

                me->show_to_scene(user2, x0, y0, d, 0);
                user2 = get_scene_object_2(me, USER_TYPE) + user;
                send_user(user2, "%c%d%d%w%w%w%w%c%c", 0x87, getoid(me), time2(), x0, y0, x, y, d, flag);

                send_user(user, "%c%d", 0x78, getoid(me));

                if (MAP_D->is_inside_safe_zone(z0, x, y)) // 安全区判断
                {
                        me->set_no_fight(1);
                }
                else
                {
                        me->set_no_fight(0);

                        npc = get_range_object_2(me, 6, CHAR_TYPE);
                        if (sizeof(npc))
                                npc->init_heart_beat_idle();
                }
        }

        if (!MAP_D->is_inside_copy(z0) && (p = get_jumpout(z0, x, y))                         // 跳转另一场景
            && (!objectp(who = me->get_quest("escort.robber#")) || !who->is_escort_robber())) // 寻找蒙面人
        {
                z = p / 1000000;
                x = (p % 1000000) / 1000;
                y = p % 1000; // get_jumpout 内含 z

                if ((who = me->get_quest("escort.npc")) // 运镖人物
                    && who->get_owner() == me && inside_screen_2(me, who))
                        who->add_to_scene(z, x, y, d);

                if (p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK))
                {
                        x = p / 1000;
                        y = p % 1000;

                        me->set_login_flag(2); // 跳转保护
                        set_invisible(me, 1);
                        set_effect(me, EFFECT_USER_LOGIN, 4);

                        me->add_to_scene(z, x, y, d);

                        //                      if( z != z0 ) if( map = get_map_object(z) ) notify( map->get_name() );    // 显示地图名
                }
        }
        else if (MAP_D->is_inside_battle(z0)) // 战场
        {
                if (objectp(map = get_map_object(z0))) // 获取战场对象
                {
                        who = me->get_manager();
                        d = getoid(me);

                        if (map->get_manager() == who) // 攻击方
                        {
                                user = map->get_user_dbase();
                                send_user(user, "%c%c%d%w%w", 0x54, 10, d, x, y);
                                //                              for( i = 0, size = sizeof(user); i < size; i ++ )
                                //                                      if( objectp( who = user[i] ) ) send_user( who, "%c%c%d%w%w", 0x54, 10, d, x, y );
                        }
                        else if (map->get_manager_2() == who) // 防守方
                        {
                                user = map->get_user_2_dbase();
                                send_user(user, "%c%c%d%w%w", 0x54, 10, d, x, y);
                                //                              for( i = 0, size = sizeof(user); i < size; i ++ )
                                //                                      if( objectp( who = user[i] ) ) send_user( who, "%c%c%d%w%w", 0x54, 10, d, x, y );
                        }
                }
        }
        else if (arrayp(user = me->get_team())) // 更新队员坐标
        {
                user -= ({me, 0});
                user = filter_array(user, (
                                              : $1 && get_z($1) == $2:),
                                    z0);
                send_user(user, "%c%c%d%w%w", 0x54, 10, me->get_number(), x, y);
        }

        if (get_effect(me, EFFECT_CHAR_CHAN))
                set_effect(me, EFFECT_CHAR_CHAN, 1); // 移除粘手效果
        z0 = get_z(me);
        if (get_block(z0, x, y) & SEAL_BLOCK)
        {
                item = get_range_object_2(me, 0, SEAL_TYPE);
                if (sizeof(item) > 0)
                {
                        if (item[0]->is_self_seal())
                                item[0]->heart_beat_loop(0, 0, 0, 0, 0, 0, 0, 0);
                }
        }
        return 1;
}

// 函数：虚影快速移动
int main_fly_npc(object me, int x, int y, int d, int flag)
{
        object map, *user, *user2, *npc, who;
        int z0, x0, y0, z, dx, dy;
        int p, i, size;

        z0 = get_z(me);
        x0 = get_x(me);
        y0 = get_y(me);

        if (abs(x - x0) > 10 || abs(y - y0) > 10)
                return 1; // 距离过远
        if (!inside_map(z0, x, y))
                return 1; // 坐标非法
        if (get_block(z0, x, y) & IS_CHAR_BLOCK)
                return 1; // 无法落脚
        if (!from_to(z0, x0, y0, x - x0, y - y0, MAP_BLOCK))
                return 1; // 无法穿越

        dx = (x / AREA_SIZE) - (x0 / AREA_SIZE);
        dy = (y / AREA_SIZE) - (y0 / AREA_SIZE);

        if (dx == 0 && dy == 0) // 本场景内行走
        {
                remove_block(z0, x0, y0, CHAR_BLOCK);
                set_x(me, x);
                set_y(me, y);
                set_d(me, d);
                set_block(z0, x, y, CHAR_BLOCK);

                user = get_scene_object(z0, x, y, USER_TYPE);
                send_user(user, "%c%d%d%w%w%w%w%c%c", 0x87, getoid(me), time2(), x0, y0, x, y, d, flag);

                me->set_no_fight(MAP_D->is_inside_safe_zone(z0, x, y) ? 1 : 0); // 安全区判断
        }
        else // 跨越场景行走
        {
                if (dx < 0)
                {
                        if (dy < 0)
                        {
                                dx = 0x12e;
                                dy = 0x1d2;
                        }
                        else if (dy > 0)
                        {
                                dx = 0x1e8;
                                dy = 0x5e;
                        }
                        else
                        {
                                dx = 0x128;
                                dy = 0x52;
                        }
                }
                else if (dx > 0)
                {
                        if (dy < 0)
                        {
                                dx = 0x5e;
                                dy = 0x1e8;
                        }
                        else if (dy > 0)
                        {
                                dx = 0x1d2;
                                dy = 0x12e;
                        }
                        else
                        {
                                dx = 0x52;
                                dy = 0x128;
                        }
                }
                else
                {
                        if (dy < 0)
                        {
                                dx = 0xe;
                                dy = 0x1c0;
                        }
                        else
                        {
                                dx = 0x1c0;
                                dy = 0xe;
                        }
                }

                remove_block(z0, x0, y0, CHAR_BLOCK); // 删除阻挡
                user = get_scene_object(z0, x0, y0, USER_TYPE, dx);

                set_x(me, x);
                set_y(me, y);
                set_d(me, d); // 设置坐标，增加阻挡
                set_block(z0, x, y, CHAR_BLOCK);
                objectp(who = me->get_owner()) && who->is_user() ? move_object(me, z0, x, y, USER_TYPE) : move_object(me, z0, x, y, CHAR_TYPE); // 移动 NPC
                user2 = get_scene_object(z0, x, y, USER_TYPE, dy);

                me->show_to_scene(user2, x0, y0, d, 0);
                user2 = get_scene_object_2(me, USER_TYPE) + user;
                send_user(user2, "%c%d%d%w%w%w%w%c%c", 0x87, getoid(me), time2(), x0, y0, x, y, d, flag);

                send_user(user, "%c%d", 0x78, getoid(me));

                if (MAP_D->is_inside_safe_zone(z0, x, y)) // 安全区判断
                {
                        me->set_no_fight(1);
                }
                else
                {
                        me->set_no_fight(0);

                        if (objectp(me->get_owner()))
                        {
                                npc = get_range_object_2(me, 6, CHAR_TYPE);
                                if (sizeof(npc))
                                        npc->init_heart_beat_idle();
                        }
                }
        }

        if (objectp(who = me->get_owner()) && who->is_user())
        {
                if (get_z(who) != get_z(me))
                {
                        send_user(who, "%c%c%d%w%w", 0x2c, 7, getoid(me), -1, -1); // 更新召唤兽坐标
                        me->set_owner(0);
                }
                else
                        send_user(who, "%c%c%d%w%w", 0x2c, 7, getoid(me), x, y); // 更新召唤兽坐标
        }

        if (get_effect(me, EFFECT_CHAR_CHAN))
                set_effect(me, EFFECT_CHAR_CHAN, 1); // 移除粘手效果

        return 1;
}

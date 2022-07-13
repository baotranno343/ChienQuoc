#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <item.h>
#include <map.h>
#include <action.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：中断持续效果
void stop_loop_perform(object me)
{
        if (get_effect_3(me, EFFECT_CHAR_ATTACK))
                set_effect(me, EFFECT_CHAR_ATTACK, 1); // 顺势推舟(自用)
        if (get_effect_3(me, EFFECT_CHAR_MOVE))
                set_effect(me, EFFECT_CHAR_MOVE, 1); // 踏雪无痕(自用)
        if (get_effect_3(me, EFFECT_CHAR_INVISIBLE))
                set_effect_2(me, EFFECT_CHAR_INVISIBLE, 1, 1); // 隐身(自用) ## 2 ##
        if (get_effect_3(me, EFFECT_CHAR_CHANGE))
                set_effect(me, EFFECT_CHAR_CHANGE, 1); // 乾坤挪移(自用)

        if (get_effect_3(me, EFFECT_CHAR_ADD_DP))
                set_effect(me, EFFECT_CHAR_ADD_DP, 1); // 金钟罩(＋防御)(自用)
        if (get_effect_3(me, EFFECT_CHAR_ADD_PP))
                set_effect(me, EFFECT_CHAR_ADD_PP, 1); // 护体金光(＋法防)(自用)
        if (get_effect_3(me, EFFECT_CHAR_MISS))
                set_effect(me, EFFECT_CHAR_MISS, 1); // 灵气甲(自用)
        if (get_effect_3(me, EFFECT_CHAR_IMMORTAL))
                set_effect(me, EFFECT_CHAR_IMMORTAL, 1); // 不死之身(不死)(自用)

        if (get_effect_3(me, EFFECT_USER_HURT))
                set_effect_2(me, EFFECT_USER_HURT, 1, 1); // 护身毒环(自用)

        if (get_effect_3(me, EFFECT_CHAR_POWERUP))
                set_effect(me, EFFECT_CHAR_POWERUP, 1); // 金针渡厄(他用)
}

// 函数：中断持续效果(不良)
void stop_loop_perform_4(object me)
{
        if (get_effect_3(me, EFFECT_CHAR_FAINT))
                set_effect(me, EFFECT_CHAR_FAINT, 1); // 眩晕(无法动作)
        if (get_effect_3(me, EFFECT_CHAR_FAINT_2))
                set_effect(me, EFFECT_CHAR_FAINT_2, 1); // 眩晕(无法动作)(麻沸散)

        if (get_effect_3(me, EFFECT_CHAR_ARMORFALL))
                set_effect(me, EFFECT_CHAR_ARMORFALL, 1); // 蚀甲(他用)?

        if (get_effect_3(me, EFFECT_CHAR_SHUT))
                set_effect(me, EFFECT_CHAR_SHUT, 1); // 困敌(不能行走)
        if (get_effect_3(me, EFFECT_CHAR_NO_PF))
                set_effect(me, EFFECT_CHAR_NO_PF, 1); // 封魔诀(他用)
        if (get_effect_3(me, EFFECT_CHAR_LAZY))
                set_effect(me, EFFECT_CHAR_LAZY, 1); // 延缓(攻击移动变慢)
        if (get_effect_3(me, EFFECT_CHAR_SLOW))
                set_effect(me, EFFECT_CHAR_SLOW, 1); // 延缓(攻击变慢)
        if (get_effect_3(me, EFFECT_CHAR_DREAM_1))
                set_effect(me, EFFECT_CHAR_DREAM_1, 1); // 梦游(随机走路)失魂(保护状态)
        if (get_effect_3(me, EFFECT_CHAR_DREAM))
                set_effect_2(me, EFFECT_CHAR_DREAM, 1, 1); // 梦游(随机走路)失魂
        if (get_effect_3(me, EFFECT_CHAR_CHAOS))
                set_effect(me, EFFECT_CHAR_CHAOS, 1); // 混乱(鼠标反转)
        if (get_effect_3(me, EFFECT_CHAR_WOUND))
                set_effect(me, EFFECT_CHAR_WOUND, 1); // 负伤(－攻击－防御)
        if (get_effect_3(me, EFFECT_CHAR_BLOOD))
                set_effect_2(me, EFFECT_CHAR_BLOOD, 1, 1); // 流血(不断减血)

        if (get_effect_3(me, EFFECT_USER_BURN))
                set_effect_2(me, EFFECT_USER_BURN, 1, 1); // 燃烧(减少耐久)
}

// 函数：中断持续效果(神打)
void stop_loop_perform_5(object me)
{
        //        if( get_effect_3(me, EFFECT_CHAR_HALFGOD) ) set_effect(me, EFFECT_CHAR_HALFGOD, 1);    // 神打(自用)
}

// 函数：中断持续效果(其它)
void stop_loop_perform_8(object me)
{
        string file, arg;
        if (get_effect_3(me, EFFECT_USER_HERB))
                "/effect/herb"->effect_herb_break(me); // 采集草药(中断)
        if (get_effect_3(me, EFFECT_TRAVEL))
                "/sys/task/travel"->effect_break(me); // 驿站传送(中断)

        if (get_effect_3(me, EFFECT_CON_HP_MP))
                "/sys/item/food"->effect_recover_break(me); // 吃食物(中断)
        if (get_effect_3(me, EFFECT_CON_MP))
                "/sys/item/food"->effect_recover_break2(me); // 吃食物(中断)

        if (get_effect_3(me, EFFECT_USER_RECOVER))
                PF_FILE_03481->effect_recover_break(me); // 休整(中断)

        if (get_effect_3(me, EFFECT_USER_THUNDER))
                PF_FILE_04236->effect_thunder_break(me); // 雷龙诀(中断)

        if (get_effect_3(me, EFFECT_USER_WORK))
                TASK_WORKER_D->effect_work_break(me);
        if (get_effect_3(me, EFFECT_OPEN_BOX))
                "/npc/00/2001"->effect_break(me);
        if (get_effect_3(me, EFFECT_MINE))
                "/npc/00/2002"->effect_break(me);
        if (get_effect_3(me, EFFECT_CONJURE))
                "/effect/zombie"->effect_break(me);
        if (get_effect_3(me, EFFECT_PROGRESS))
        {
                file = me->get_progress_file();
                arg = me->get_progress_arg();
                if (file)
                        file->effect_break(me, arg);
        }
        if (get_effect_3(me, EFFECT_PROGRESS2))
        {
                file = me->get_progress_file();
                arg = me->get_progress_arg();
                if (file)
                        file->effect_break(me, arg);
        }
}

// 函数：中断持续效果(被攻击)
void stop_loop_perform_be_attack(object me)
{
        string file, arg;
        if (get_effect_3(me, EFFECT_USER_ESCAPE))
                ITEM_0497_FILE->effect_escape_break(me); // 逃离战场(中断)
        if (get_effect_3(me, EFFECT_USER_HERB))
                "/effect/herb"->effect_herb_break(me); // 采集草药(中断)
                                                       //        if( get_effect_3(me, EFFECT_TRAVEL) ) "/sys/task/travel"->effect_break(me);    		// 驿站传送(中断)

        if (get_effect_3(me, EFFECT_CON_HP_MP))
                "/sys/item/food"->effect_recover_break(me); // 吃食物(中断)
        if (get_effect_3(me, EFFECT_CON_MP))
                "/sys/item/food"->effect_recover_break2(me); // 吃食物(中断)
        if (get_effect_3(me, EFFECT_USER_RECOVER))
                PF_FILE_03481->effect_recover_break(me); // 休整(中断)
        if (get_effect_3(me, EFFECT_USER_WORK))
                TASK_WORKER_D->effect_work_break(me);
        if (get_effect_3(me, EFFECT_OPEN_BOX))
                "/npc/00/2001"->effect_break(me);
        if (get_effect_3(me, EFFECT_MINE))
                "/npc/00/2002"->effect_break(me);
        //   if( get_effect_3(me, EFFECT_CONJURE) )	"/effect/zombie"->effect_break(me);
        if (get_effect_3(me, EFFECT_SLEEP))
                set_effect(me, EFFECT_SLEEP, 1); // 昏迷
        if (get_effect_3(me, EFFECT_PROGRESS2))
        {
                file = me->get_progress_file();
                arg = me->get_progress_arg();
                if (file)
                        file->effect_break(me, arg);
        }
}

// 函数：中断持续效果(眩晕，梦游)
void stop_loop_perform_faint(object me)
{
        if (get_effect_3(me, EFFECT_USER_ESCAPE))
                ITEM_0497_FILE->effect_escape_break(me); // 逃离战场(中断)
        if (get_effect_3(me, EFFECT_USER_HERB))
                "/effect/herb"->effect_herb_break(me); // 采集草药(中断)
        if (get_effect_3(me, EFFECT_TRAVEL))
                "/sys/task/travel"->effect_break(me); // 驿站传送(中断)
        if (get_effect_3(me, EFFECT_USER_THUNDER))
                PF_FILE_04236->effect_thunder_break(me); // 雷龙诀(中断)
        if (get_effect_3(me, EFFECT_CON_HP_MP))
                "/sys/item/food"->effect_recover_break(me); // 吃食物(中断)
        if (get_effect_3(me, EFFECT_CON_MP))
                "/sys/item/food"->effect_recover_break2(me); // 吃食物(中断)
        if (get_effect_3(me, EFFECT_USER_RECOVER))
                PF_FILE_03481->effect_recover_break(me); // 休整(中断)
        if (get_effect_3(me, EFFECT_USER_WORK))
                TASK_WORKER_D->effect_work_break(me);
        if (get_effect_3(me, EFFECT_OPEN_BOX))
                "/npc/00/2001"->effect_break(me);
        if (get_effect_3(me, EFFECT_MINE))
                "/npc/00/2002"->effect_break(me);
        if (get_effect_3(me, EFFECT_CONJURE))
                "/effect/zombie"->effect_break(me);
}

// 函数：中断持续效果(其它)(全)
void stop_loop_perform_9(object me)
{
        if (get_effect_3(me, EFFECT_USER_ESCAPE))
                ITEM_0497_FILE->effect_escape_break(me); // 逃离战场(中断)
        stop_loop_perform_8(me);
}

// 函数：走路中断持续效果(其它)
void stop_loop_perform_go(object me)
{
        string file, arg;
        if (get_effect_3(me, EFFECT_USER_HERB))
                "/effect/herb"->effect_herb_break(me); // 采集草药(中断)
        if (get_effect_3(me, EFFECT_TRAVEL))
                "/sys/task/travel"->effect_break(me); // 驿站传送(中断)

        if (get_effect_3(me, EFFECT_USER_ESCAPE))
                ITEM_0497_FILE->effect_escape_break(me); // 逃离战场(中断)
        if (get_effect_3(me, EFFECT_USER_RECOVER))
                PF_FILE_03481->effect_recover_break(me); // 休整(中断)

        if (get_effect_3(me, EFFECT_USER_THUNDER))
                PF_FILE_04236->effect_thunder_break(me); // 雷龙诀(中断)

        if (get_effect_3(me, EFFECT_USER_WORK))
                TASK_WORKER_D->effect_work_break(me);
        if (get_effect_3(me, EFFECT_OPEN_BOX))
                "/npc/00/2001"->effect_break(me);
        if (get_effect_3(me, EFFECT_MINE))
                "/npc/00/2002"->effect_break(me);
        if (get_effect_3(me, EFFECT_CONJURE))
                "/effect/zombie"->effect_break(me);
        if (get_effect_3(me, EFFECT_PROGRESS))
        {
                file = me->get_progress_file();
                arg = me->get_progress_arg();
                if (file)
                        file->effect_break(me, arg);
        }
        if (get_effect_3(me, EFFECT_PROGRESS2))
        {
                file = me->get_progress_file();
                arg = me->get_progress_arg();
                if (file)
                        file->effect_break(me, arg);
        }
}

// 函数：中断毒药效果
void stop_poison_effect(object me)
{
        if (get_effect_3(me, EFFECT_CHAR_POISON))
                set_effect_2(me, EFFECT_CHAR_POISON, 1, 1); // 毒药(解除) ## 2 ##
        if (get_effect_3(me, EFFECT_CHAR_POISON_2))
                set_effect_2(me, EFFECT_CHAR_POISON_2, 1, 1); // 毒药(解除) ## 2 ##

        if (get_effect_3(me, EFFECT_CHAR_5215))
                set_effect(me, EFFECT_CHAR_5215, 1); // 软筋散(解除)

        if (get_effect_3(me, EFFECT_CHAR_DREAM_1))
                set_effect(me, EFFECT_CHAR_DREAM_1, 1); // 迷神散(解除)
        if (get_effect_3(me, EFFECT_CHAR_DREAM))
                set_effect_2(me, EFFECT_CHAR_DREAM, 1, 1); // 迷神散(解除) ## 2 ##
}

// =============================================================

// 函数：初始化持续效果
void init_loop_perform(object me)
{
        int *pf = ({});
        object map, item;
        string name1, name2;
        if (me->is_user()) // 玩家
        {
                if (get_effect_3(me, EFFECT_USER_HERB))
                        pf += ({00131, 10, OVER_BODY}); // 采集草药(自用)
                map = get_map_object(get_z(me));
                if (map && (map->get_map_type() == BATTLE_MAP) && (me->is_die() == 0))
                {
                        name1 = map->get_war_attack();
                        name2 = map->get_war_defense();
                        if (map->is_changping())
                        {
                                if (me->get_2("changping.country") == "Tần Quốc")
                                        pf += ({9005, 1, OVER_BODY});
                                else if (me->get_2("changping.country") == "Triệu Quốc")
                                        pf += ({9006, 1, OVER_BODY});

                                if ("Tần Quốc" == name1)
                                        pf += ({9005, 1, OVER_BODY});
                                else if ("Triệu Quốc" == name2)
                                        pf += ({9006, 1, OVER_BODY});
                        }
                        else
                        {

                                if (me->get_org_name() == name1)
                                        pf += ({9005, 1, OVER_BODY});
                                else if (me->get_org_name() == name2)
                                        pf += ({9006, 1, OVER_BODY});
                        }
                }
        }
        else // ＮＰＣ
        {
                //                if( !me->get_action() ) pf += ({ 9414, 1, UNDER_FOOT });    // 召唤兽停止
                if (get_effect_3(me, EFFECT_NPC_0531_1))
                        pf += ({5311, 1, OVER_BODY}); // 迷魂诀(他用)
                if (get_effect_3(me, EFFECT_CHAR_SOUL_LOCK))
                        pf += ({42531, 1, OVER_BODY});
        }
        if (get_effect_3(me, EFFECT_CHAR_FAINT))
                pf += ({9002, 1, OVER_BODY}); // 眩晕(无法动作)
        if (get_effect_3(me, EFFECT_CHAR_FAINT_2))
                pf += ({9002, 1, OVER_BODY}); // 眩晕(无法动作)(麻沸散)
        if (get_effect_3(me, EFFECT_SLEEP))
                pf += ({9015, 1, OVER_BODY}); // 眩晕(无法动作)
        if (get_effect_3(me, EFFECT_CHAR_NO_MOVE))
                pf += ({9012, 1, UNDER_FOOT}); // 困敌

        if (get_effect_3(me, EFFECT_CHAR_IMMORTAL))
                pf += ({32540, 1, OVER_BODY}); // 不死之身(不死)(自用)

        if (get_effect_3(me, EFFECT_CHAR_SHUT))
                pf += ({34821, 1, UNDER_FOOT}); //

        if (get_effect_3(me, EFFECT_CHAR_INVISIBLE))
                pf += ({9000, 1, UNDER_FOOT}); // 隐身(自用)
        if (get_effect_3(me, EFFECT_USER_HURT))
                pf += ({36321, 3, UNDER_FOOT}); // 护身毒环

        //                if( get_effect_3(me, EFFECT_CHAR_HALFGOD2) ) pf += ({ 41710, 1, UNDER_FOOT });    // 神打(自用)

        if (get_effect_3(me, EFFECT_CHAR_DANCE) || get_effect_3(me, EFFECT_CHAR_SING))
                pf += ({01011, 10, OVER_BODY}); // 跳舞/唱歌

        if (get_effect_3(me, EFFECT_CHAR_SLOW))
                pf += ({9012, 1, OVER_BODY});
        if (get_effect_3(me, EFFECT_CHAR_LAZY))
                pf += ({9012, 1, OVER_BODY});
        if (get_effect_3(me, EFFECT_CHAR_NO_PF))
                pf += ({9010, 1, OVER_BODY});
        if (get_effect_3(me, EFFECT_CHAR_SUPPRESS))
                pf += ({9569, 1, OVER_BODY});
        //                if( get_effect_3(me, EFFECT_CHAR_CHAOS) ) pf += ({ 9018, 1, OVER_BODY });
        if (get_effect_3(me, EFFECT_CHAR_DREAM_1))
                pf += ({9016, 1, OVER_BODY});
        if (get_effect_3(me, EFFECT_CHAR_DREAM))
                pf += ({53112, 1, OVER_BODY});
        if (get_effect_3(me, EFFECT_USER_BURN))
                pf += ({9026, 1, OVER_BODY});
        if (get_effect_3(me, EFFECT_CHAR_WOUND))
                pf += ({9020, 1, OVER_BODY});
        if (get_effect_3(me, EFFECT_CHAR_POISON))
                pf += ({9096, 1, OVER_BODY});
        if (get_effect_3(me, EFFECT_CHAR_POISON_2))
                pf += ({9096, 1, OVER_BODY});
        if (me->is_leader())
                pf += ({9111, 1, OVER_BODY});

        if (item = me->get_equip(109))
        {
                if (item->is_nangcap())
                {
                        if (item->get("ap") >= 800 || item->get("cp") >= 800)
                        {
                                pf += ({4176, 1, OVER_BODY});
                        }
                }
        }

        if (item = me->get_equip(107)) //如果玩家法宝装备栏还装备淬月之环，那么继续播放法术效果。
        {
                if (item->get_name() == "Thối Nguyệt Chi Hoàn" || item->get_name() == "Nhật Nguyệt Tinh Thần")
                {
                        pf += ({9009, 1, UNDER_FOOT});
                }
                if (item->get_name() == "Cửu Long Thần Hỏa Trảo")
                {
                        pf += ({9321, 1, UNDER_FOOT});
                }
                if (item->get_name() == "Thổ Hành Châu")
                {
                        pf += ({9322, 1, UNDER_FOOT});
                }
                if (item->get_name() == "Linh Tê Hoàn")
                {
                        pf += ({9323, 1, UNDER_FOOT});
                }
                if (item->get_name() == "Khu Thần Lệnh")
                {
                        pf += ({9324, 1, UNDER_FOOT});
                }
                if (item->get_name() == "Nhiếp Hồn Linh")
                {
                        pf += ({9325, 1, UNDER_FOOT});
                }
                if (item->get_name() == "Chuông Hám Thiên")
                {
                        pf += ({9326, 1, UNDER_FOOT});
                }
                if (item->get_name() == "Chân Long Thiên Tử Ấn - Ngoại")
                {
                        pf += ({51313, 1, UNDER_FOOT});
                        //   pf += ({9325, 1, UNDER_FOOT});
                }
                if (item->get_name() == "Chân Long Thiên Tử Ấn - Nội")
                {
                        pf += ({51313, 1, UNDER_FOOT});
                        //     pf += ({9326, 1, UNDER_FOOT});
                }
        }
        me->set_loop_pf(pf);
}

// 函数：发送持续效果的时间
void send_loop_perform_time(object me, int *pf) // 发给自己
{
        int i, size;
        if (arrayp(pf))
        {
                size = sizeof(pf);
                for (i = 0; i < size; i += 2)
                {
                        if (pf[i + 1] != -1)
                                send_user(me, "%c%w%c%w", 0x50, pf[0], 0xff, pf[1]);
                }
        }
}

// 函数：发送持续效果
void send_loop_perform(object me, mixed user)
{
        object *user2;
        int id = getoid(me), i = 1;
        int *pf;
        // if (user->get("anhieuung") == 1)
        //       return;
        // user -= ({me});
        pf = me->get_loop_pf();

        if (user->get("anhieuung") == 1)
        {
                if (member_array(9000, pf) > -1)
                        pf = ({9000, 1, UNDER_FOOT});
                else
                        return;
        }
        if (arrayp(pf))
                switch (sizeof(pf))
                {
                case 3:
                        send_user(user, "%c%d%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], PF_LOOP);
                        break;
                case 6:
                        send_user(user, "%c%d%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], PF_LOOP);
                        break;
                case 9:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], PF_LOOP);
                        break;
                case 12:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], PF_LOOP);
                        break;
                case 15:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], PF_LOOP);
                        break;
                case 18:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], PF_LOOP);
                        break;
                case 21:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], PF_LOOP);
                        break;
                case 24:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], PF_LOOP);
                        break;
                case 27:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], PF_LOOP);
                        break;
                case 30:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], PF_LOOP);
                        break;
                case 33:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], PF_LOOP);
                        break;
                case 36:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], PF_LOOP);
                        break;
                case 39:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], PF_LOOP);
                        break;
                case 42:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], PF_LOOP);
                        break;
                case 45:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], PF_LOOP);
                        break;
                case 48:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], PF_LOOP);
                        break;
                case 51:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], pf[50], PF_LOOP);
                        break;
                case 54:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], pf[50], pf[51], pf[52], pf[53], PF_LOOP);
                        break;
                case 57:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], pf[50], pf[51], pf[52], pf[53], pf[54], pf[55], pf[56], PF_LOOP);
                        break;
                case 60:
                        send_user(user, "%c%d%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%w%c%c%c", 0x6f, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], pf[50], pf[51], pf[52], pf[53], pf[54], pf[55], pf[56], pf[57], pf[58], pf[59], PF_LOOP);
                        break;
                default:
                        break;
                }
}

// 函数：发送持续效果(辅助函数)
private
void send_loop_perform_3(object me, int *pf, int flag) // 发给自己
{
        if (arrayp(pf))
                switch (sizeof(pf))
                {
                case 2:
                        send_user(me, "%c%w%w%c", 0x81, pf[0], pf[1], flag);
                        break;
                case 4:
                        send_user(me, "%c%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], flag);
                        break;
                case 6:
                        send_user(me, "%c%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], flag);
                        break;
                case 8:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], flag);
                        break;
                case 10:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], flag);
                        break;
                case 12:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], flag);
                        break;
                case 14:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], flag);
                        break;
                case 16:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], flag);
                        break;
                case 18:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], flag);
                        break;
                case 20:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], flag);
                        break;
                case 22:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], flag);
                        break;
                case 24:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], flag);
                        break;
                case 26:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], flag);
                        break;
                case 28:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], flag);
                        break;
                case 30:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], flag);
                        break;
                case 32:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], flag);
                        break;
                case 34:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], flag);
                        break;
                case 36:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], flag);
                        break;
                case 38:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], flag);
                        break;
                case 40:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], flag);
                        break;
                case 42:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], flag);
                        break;
                case 44:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], flag);
                        break;
                case 46:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], flag);
                        break;
                case 48:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], flag);
                        break;
                case 50:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], flag);
                        break;
                case 52:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], pf[50], pf[51], flag);
                        break;
                case 54:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], pf[50], pf[51], pf[52], pf[53], flag);
                        break;
                case 56:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], pf[50], pf[51], pf[52], pf[53], pf[54], pf[55], flag);
                        break;
                case 58:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], pf[50], pf[51], pf[52], pf[53], pf[54], pf[55], pf[56], pf[57], flag);
                        break;
                case 60:
                        send_user(me, "%c%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c", 0x81, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], pf[30], pf[31], pf[32], pf[33], pf[34], pf[35], pf[36], pf[37], pf[38], pf[39], pf[40], pf[41], pf[42], pf[43], pf[44], pf[45], pf[46], pf[47], pf[48], pf[49], pf[50], pf[51], pf[52], pf[53], pf[54], pf[55], pf[56], pf[57], pf[58], pf[59], flag);
                        break;
                default:
                        break;
                }
}

// 函数：发送持续效果(辅助函数)
private
void send_loop_perform_4(object me, mixed user, int *pf, int flag) // 发给别人
{
        int id = getoid(me);

        if (arrayp(pf))
                switch (sizeof(pf))
                {
                case 1:
                        send_user(user, "%c%d%w%c%c", 0x83, id, pf[0], 1, flag);
                        break;
                case 2:
                        send_user(user, "%c%d%w%w%c%c", 0x83, id, pf[0], pf[1], 1, flag);
                        break;
                case 3:
                        send_user(user, "%c%d%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], 1, flag);
                        break;
                case 4:
                        send_user(user, "%c%d%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], 1, flag);
                        break;
                case 5:
                        send_user(user, "%c%d%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], 1, flag);
                        break;
                case 6:
                        send_user(user, "%c%d%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], 1, flag);
                        break;
                case 7:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], 1, flag);
                        break;
                case 8:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], 1, flag);
                        break;
                case 9:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], 1, flag);
                        break;
                case 10:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], 1, flag);
                        break;
                case 11:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], 1, flag);
                        break;
                case 12:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], 1, flag);
                        break;
                case 13:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], 1, flag);
                        break;
                case 14:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], 1, flag);
                        break;
                case 15:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], 1, flag);
                        break;
                case 16:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], 1, flag);
                        break;
                case 17:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], 1, flag);
                        break;
                case 18:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], 1, flag);
                        break;
                case 19:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], 1, flag);
                        break;
                case 20:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], 1, flag);
                        break;
                case 21:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], 1, flag);
                        break;
                case 22:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], 1, flag);
                        break;
                case 23:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], 1, flag);
                        break;
                case 24:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], 1, flag);
                        break;
                case 25:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], 1, flag);
                        break;
                case 26:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], 1, flag);
                        break;
                case 27:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], 1, flag);
                        break;
                case 28:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], 1, flag);
                        break;
                case 29:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], 1, flag);
                        break;
                case 30:
                        send_user(user, "%c%d%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%w%c%c", 0x83, id, pf[0], pf[1], pf[2], pf[3], pf[4], pf[5], pf[6], pf[7], pf[8], pf[9], pf[10], pf[11], pf[12], pf[13], pf[14], pf[15], pf[16], pf[17], pf[18], pf[19], pf[20], pf[21], pf[22], pf[23], pf[24], pf[25], pf[26], pf[27], pf[28], pf[29], 1, flag);
                        break;
                default:
                        break;
                }
}

// 函数：发送持续效果
void send_loop_perform_2(object me, mixed user)
{
        int time, *pf, *pf2, i = 1;
        // if (user->get("anhieuung") == 1)
        //         return;

        pf = ({});
        pf2 = ({});                                                      // pf 好的效果；pf2 坏的效果
        if (me->is_npc() || objectp(user) && me != user || arrayp(user)) // 发给别人
        {
                if (arrayp(user))
                {
                        user -= ({me});
                        if (sizeof(user) == 0)
                                return;
                }
                if (me->is_user()) // 玩家
                {
                        if (me->get_perform(PF_FLAG_03172) && time() - me->get_perform(PF_FLAG_03172) < 1800)
                                pf += ({3172}); // 元气复生(自用)
                        if (get_effect_3(me, EFFECT_REBOUND))
                                pf += ({3173}); // 护体金罡(自用)

                        if (me->get_perform("03191"))
                                pf += ({3191}); //
                        if (me->get_perform("03192"))
                                pf += ({3192}); //
                        if (me->get_perform("02221#"))
                                pf += ({2221});
                        if (me->get_perform("02222#"))
                                pf += ({2222});
                        if (me->get_perform("05016#"))
                                pf += ({5016});

                        //                        if( me->get_perform(PF_FLAG_02214) ) pf += ({ 2214 });    // 泼风三式(自用)
                        //                        if( me->get_perform(PF_FLAG_02514) ) pf += ({ 2514 });    // 横扫千军(自用)
                }
                else // ＮＰＣ
                {
                        if (get_effect_3(me, EFFECT_NPC_0531_1))
                                pf += ({5311}); // 迷魂诀(他用)
                }
                //                        if( gone_time( me->get_perform(PF_FLAG_03485) ) < 180 ) pf += ({ 3485 });    // 九死一生
                if (me->get_perform(PF_FLAG_03486))
                        pf += ({3486}); // 九死一生(被动)

                if (me->get_perform(PF_FLAG_03172) && time() - me->get_perform(PF_FLAG_03172) < 1800)
                        pf += ({3172}); // 九死一生(被动)

                if (get_effect_3(me, EFFECT_CHAR_FAINT))
                        pf2 += ({9002}); // 眩晕(无法动作)
                if (get_effect_3(me, EFFECT_CHAR_FAINT_2))
                        pf2 += ({9002}); // 眩晕(无法动作)(麻沸散)

                if (get_effect_3(me, EFFECT_CHAR_ATTACK))
                        pf += ({2321}); // 顺势推舟(自用)

                if (get_effect_3(me, EFFECT_CHAR_ADD_DP))
                        pf += ({3251}); // 金钟罩(＋防御)(自用)
                if (get_effect_3(me, EFFECT_CHAR_ADD_PP))
                        pf += ({3252}); // 护体金光(＋法防)(自用)
                if (get_effect_3(me, EFFECT_CHAR_IMMORTAL))
                        pf += ({3254}); // 不死之身(不死)(自用)

                if (get_effect_3(me, EFFECT_USER_RECOVER))
                        pf += ({3481}); // 休整(自用)
                if (get_effect_3(me, EFFECT_03484))
                        pf += ({3484}); //
                if (get_effect_3(me, EFFECT_CHAR_SHUT))
                        pf2 += ({3482}); // 困敌(不能行走)

                if (get_effect_3(me, EFFECT_CHAR_INVISIBLE))
                {
                        pf += ({3631}); // 隐身(自用)
                }
                if (get_effect_3(me, EFFECT_USER_HURT))
                        pf += ({3632}); // 护身毒环(自用)

                if (get_effect_3(me, EFFECT_CHAR_MOVE))
                        pf += ({3641}); // 踏雪无痕(自用)
                if (get_effect_3(me, EFFECT_03642))
                        pf += ({3642}); //
                if (get_effect_3(me, EFFECT_03643))
                        pf += ({3643}); //

                if (get_effect_3(me, EFFECT_CHAR_ARMORFALL))
                        pf2 += ({4143}); // 蚀甲(他用)
                if (get_effect_3(me, EFFECT_CHAR_POWERFALL))
                        pf2 += ({4144}); // 蚀心(他用)
                if (get_effect_3(me, EFFECT_CHAR_FALL))
                        pf2 += ({4145}); // 蚀魂(他用)
                if (get_effect_3(me, EFFECT_MP_FALL))
                        pf2 += ({4148}); //
                if (get_effect_3(me, EFFECT_DOUBLE_USE))
                        pf2 += ({4141}); //
                if (get_effect_3(me, EFFECT_MAGIC_4243))
                        pf2 += ({4243}); // 变身术

                if (get_effect_3(me, EFFECT_CHAR_HALFGOD2))
                        pf += ({4171}); // 神打(自用)
                if (get_effect_3(me, EFFECT_CHAR_CHANGE))
                        pf += ({4251}); // 乾坤挪移(自用)
                if (get_effect_3(me, EFFECT_CHAR_MISS))
                        pf += ({4252}); // 灵气甲(自用)
                if (get_effect_3(me, EFFECT_CHAR_MISS2))
                        pf += ({5911}); //

                if (get_effect_3(me, EFFECT_CHAR_POWERUP))
                        pf += ({5011}); // 金针渡厄(他用)
                if (get_effect_3(me, EFFECT_CHAR_POWERUP2))
                        pf += ({5012}); //
                if (get_effect_3(me, EFFECT_CHAR_POWERUP3))
                        pf += ({5014}); //
                if (get_effect_3(me, EFFECT_NO_WEAPON))
                        pf += ({2114}); // 武器禁用
                if (get_effect_3(me, EFFECT_NO_CLOTH))
                        pf += ({2516}); // 防具禁用

                if (get_effect_3(me, EFFECT_CHAR_NO_PF))
                        pf2 += ({9010}); // 封魔诀(他用)
                if (get_effect_3(me, EFFECT_CHAR_LAZY))
                        pf2 += ({9012}); // 延缓(攻击移动变慢)
                if (get_effect_3(me, EFFECT_CHAR_SLOW))
                        pf2 += ({9012}); // 延缓(攻击变慢)
                if (get_effect_3(me, EFFECT_CHAR_DREAM_1))
                        pf2 += ({9016}); // 梦游(随机走路)失魂(保护状态)
                if (get_effect_3(me, EFFECT_CHAR_DREAM))
                        pf2 += ({9016}); // 梦游(随机走路)失魂
                if (get_effect_3(me, EFFECT_CHAR_CHAOS))
                        pf2 += ({9018}); // 混乱(鼠标反转)
                if (get_effect_3(me, EFFECT_CHAR_WOUND))
                        pf2 += ({9020}); // 负伤(－攻击－防御)
                if (get_effect_3(me, EFFECT_CHAR_BLOOD))
                        pf2 += ({9022}); // 流血(不断减血)
                if (get_effect_3(me, EFFECT_2123_ARMORFALL))
                        pf2 += ({2123}); //
                if (get_effect_3(me, EFFECT_SLEEP))
                        pf2 += ({9002}); //
                if (get_effect_3(me, EFFECT_CHAR_BLIND))
                        pf2 += ({9024}); //
                if (get_effect_3(me, EFFECT_02614))
                        pf2 += ({2614}); //
                if (get_effect_3(me, EFFECT_02616))
                        pf2 += ({2616}); //
                if (get_effect_3(me, EFFECT_CHAR_NO_MOVE))
                        pf2 += ({9002}); //

                if (get_effect_3(me, EFFECT_USER_SP))
                        pf += ({2123}); //
                if (get_effect_3(me, EFFECT_DODGE))
                        pf += ({2422}); //
                if (get_effect_3(me, EFFECT_EXCITE))
                        pf += ({3162}); //

                if (get_effect_3(me, EFFECT_USER_BURN))
                        pf2 += ({9026}); // 燃烧(减少耐久)

                if (get_effect_3(me, EFFECT_CHAR_POISON))
                        pf2 += ({9096}); // 中毒
                if (get_effect_3(me, EFFECT_CHAR_POISON_2))
                        pf2 += ({9096}); // 中毒

                if (get_effect_3(me, EFFECT_CHAR_KING))
                        pf += ({9150}); // Thiên Vương Tán
                if (get_effect_3(me, EFFECT_CHAR_KING_2))
                        pf2 += ({9152}); // Thiên Vương Tán 2

                if (get_effect_3(me, EFFECT_CHAR_SUPPRESS))
                        pf2 += ({9561}); // 压制法宝

                if (get_effect_3(me, EFFECT_USER_DP))
                        pf += ({3291}); // 加物防
                if (get_effect_3(me, EFFECT_USER_PP))
                        pf += ({3292}); // 加法防

                if (get_effect_3(me, EFFECT_1808))
                        pf += ({1808});
                if (get_effect_3(me, EFFECT_1809))
                        pf += ({1809});
                if (get_effect_3(me, EFFECT_1810))
                        pf += ({1810});
                if (get_effect_3(me, EFFECT_1811))
                        pf += ({1811});

                send_loop_perform_4(me, user, pf, EFFECT_GOOD);
                send_loop_perform_4(me, user, pf2, EFFECT_BAD);
        }
        if ((objectp(user) && me == user) || (arrayp(user) && member_array(me, user) != -1)) // 发给自己
        {
                if (me->is_user()) // 玩家
                {
                        if (me->get_perform(PF_FLAG_03172) && time() - me->get_perform(PF_FLAG_03172) < 1800)
                                pf += ({3172, 30000}); // 元气复生(自用)
                        if (time = get_effect_3(me, EFFECT_REBOUND))
                                pf += ({3173, time}); // 护体金罡
                        if (me->get_perform("03191"))
                                pf += ({3191, 30000}); //
                        if (me->get_perform("03192"))
                                pf += ({3192, 30000}); //

                        //                        if( me->get_perform(PF_FLAG_02214) ) pf += ({ 2214, -1 });    // 泼风三式(自用)
                        //                        if( me->get_perform(PF_FLAG_02514) ) pf += ({ 2514, -1 });    // 横扫千军(自用)
                }
                else // ＮＰＣ
                {
                        if (time = get_effect_3(me, EFFECT_NPC_0531_1))
                                pf += ({5311, time}); // 迷魂诀(他用)
                }
                //                        if( me->get_perform(PF_FLAG_03485) ) pf += ({ 3485, -1 });    // 背水一战(被动)
                //                        if( me->get_perform(PF_FLAG_03486) ) pf += ({ 3486, -1 });    // 九死一生(被动)
                if (time = get_effect_3(me, EFFECT_CHAR_FAINT))
                        pf2 += ({9002, time}); // 眩晕(无法动作)
                if (time = get_effect_3(me, EFFECT_CHAR_FAINT_2))
                        pf2 += ({9002, time}); // 眩晕(无法动作)(麻沸散)

                if (time = get_effect_3(me, EFFECT_CHAR_ATTACK))
                        pf += ({2321, time}); // 顺势推舟(自用)
                if (time = get_effect_3(me, EFFECT_RENSHEN))
                        pf += ({0006, time}); //
                if (time = get_effect_3(me, EFFECT_XUESHI_HP))
                        pf += ({0002, time}); //
                if (time = get_effect_3(me, EFFECT_FALISHI_MP))
                        pf += ({0004, time}); //
                if (time = get_effect_3(me, EFFECT_ITEM_9165))
                        pf += ({9165, time}); //

                if (time = get_effect_3(me, EFFECT_USER_EXCHANGE_HP))
                        pf += ({0443, time}); //
                if (time = get_effect_3(me, EFFECT_USER_EXCHANGE_MP))
                        pf += ({0444, time}); //
                if (time = get_effect_3(me, EFFECT_USER_EXCHANGE_AP))
                        pf += ({0445, time}); //
                if (time = get_effect_3(me, EFFECT_USER_EXCHANGE_CP))
                        pf += ({0446, time}); //

                if ((time = me->get_2("jg_effect_buff.sz1")) || (time = me->get_2("jg_effect_buff.sz2")) || (time = me->get_2("jg_effect_buff.sz3")))
                        pf += ({4033, time});

                if (time = get_effect_3(me, EFFECT_CHAR_ADD_DP))
                        pf += ({3251, time}); // 金钟罩(＋防御)(自用)
                if (time = get_effect_3(me, EFFECT_CHAR_ADD_PP))
                        pf += ({3252, time}); // 护体金光(＋法防)(自用)
                if (time = get_effect_3(me, EFFECT_CHAR_IMMORTAL))
                        pf += ({3254, time}); // 不死之身(不死)(自用)

                if (time = get_effect_3(me, EFFECT_USER_RECOVER))
                        pf += ({3481, time}); // 休整(自用)
                if (time = get_effect_3(me, EFFECT_03484))
                        pf += ({3484, time}); //
                if (time = get_effect_3(me, EFFECT_CHAR_SHUT))
                        pf2 += ({3482, time}); // 困敌(不能行走)

                if (time = get_effect_3(me, EFFECT_CHAR_INVISIBLE))
                {
                        pf += ({3631, 30000}); // 隐身(自用)
                }
                if (time = get_effect_3(me, EFFECT_USER_HURT))
                        pf += ({3632, time}); // 护身毒环(自用)

                if (time = get_effect_3(me, EFFECT_CHAR_MOVE))
                        pf += ({3641, time}); // 踏雪无痕(自用)
                if (time = get_effect_3(me, EFFECT_03642))
                        pf += ({3642, time}); //
                if (time = get_effect_3(me, EFFECT_03643))
                        pf += ({3643, time}); //

                if (time = get_effect_3(me, EFFECT_CHAR_ARMORFALL))
                        pf2 += ({4143, time}); // 蚀甲(他用)
                if (time = get_effect_3(me, EFFECT_CHAR_POWERFALL))
                        pf2 += ({4144, time}); // 蚀心(他用)
                if (time = get_effect_3(me, EFFECT_CHAR_FALL))
                        pf2 += ({4145, time}); // 蚀魂(他用)
                if (time = get_effect_3(me, EFFECT_MP_FALL))
                        pf2 += ({4148, time}); //
                if (time = get_effect_3(me, EFFECT_DOUBLE_USE))
                        pf2 += ({4141, time}); //
                if (time = get_effect_3(me, EFFECT_MAGIC_4243))
                        pf2 += ({4243, time}); // 变身术

                if (time = get_effect_3(me, EFFECT_CHAR_HALFGOD2))
                        pf += ({4171, time}); // 神打(自用)
                if (time = get_effect_3(me, EFFECT_CHAR_CHANGE))
                        pf += ({4251, time}); // 乾坤挪移(自用)
                if (time = get_effect_3(me, EFFECT_CHAR_MISS))
                        pf += ({4252, time}); // 灵气甲(自用)
                if (time = get_effect_3(me, EFFECT_CHAR_MISS2))
                        pf += ({5911, time}); //
                if (me->get_perform("02221#"))
                        pf += ({2221, 30000});
                if (me->get_perform("02222#"))
                        pf += ({2222, 30000});
                if (me->get_perform("05016#"))
                        pf += ({5016, 30000});

                if (time = get_effect_3(me, EFFECT_CHAR_POWERUP))
                        pf += ({5011, time}); // 金针渡厄(他用)
                if (time = get_effect_3(me, EFFECT_CHAR_POWERUP2))
                        pf += ({5012, time}); //
                if (time = get_effect_3(me, EFFECT_CHAR_POWERUP3))
                        pf += ({5014, time}); //

                if (time = get_effect_3(me, EFFECT_CHAR_NO_PF))
                        pf2 += ({9010, time}); // 封魔诀(他用)
                if (time = get_effect_3(me, EFFECT_NO_WEAPON))
                        pf2 += ({2114, time}); // 武器禁用
                if (time = get_effect_3(me, EFFECT_NO_CLOTH))
                        pf2 += ({2516, time}); // 防具禁用

                if (time = get_effect_3(me, EFFECT_CHAR_LAZY))
                        pf2 += ({9012, time}); // 延缓(攻击移动变慢)
                if (time = get_effect_3(me, EFFECT_CHAR_SLOW))
                        pf2 += ({9012, time}); // 延缓(攻击变慢)
                if (time = get_effect_3(me, EFFECT_CHAR_DREAM_1))
                        pf2 += ({9016, time}); // 梦游(随机走路)失魂(保护状态)
                if (time = get_effect_3(me, EFFECT_CHAR_DREAM))
                        pf2 += ({9016, time}); // 梦游(随机走路)失魂
                if (time = get_effect_3(me, EFFECT_CHAR_CHAOS))
                        pf2 += ({9018, time}); // 混乱(鼠标反转)
                if (time = get_effect_3(me, EFFECT_CHAR_WOUND))
                        pf2 += ({9020, time}); // 负伤(－攻击－防御)
                if (time = get_effect_3(me, EFFECT_CHAR_BLOOD))
                        pf2 += ({9022, time}); // 流血(不断减血)
                if (time = get_effect_3(me, EFFECT_2123_ARMORFALL))
                        pf2 += ({2123, time}); //
                if (time = get_effect_3(me, EFFECT_SLEEP))
                        pf2 += ({9002, time}); //
                if (time = get_effect_3(me, EFFECT_CHAR_BLIND))
                        pf2 += ({9024, time}); //
                if (time = get_effect_3(me, EFFECT_02614))
                        pf2 += ({2614, time}); //
                if (time = get_effect_3(me, EFFECT_02616))
                        pf2 += ({2616, time}); //
                if (time = get_effect_3(me, EFFECT_CHAR_NO_MOVE))
                        pf2 += ({9002, time}); //

                if (time = get_effect_3(me, EFFECT_USER_SP))
                        pf += ({2421, time}); //
                if (time = get_effect_3(me, EFFECT_DODGE))
                        pf += ({2422, time}); //
                if (time = get_effect_3(me, EFFECT_EXCITE))
                        pf += ({3162, time}); //

                if (time = get_effect_3(me, EFFECT_USER_BURN))
                        pf2 += ({9026, time}); // 燃烧(减少耐久)

                if (time = get_effect_3(me, EFFECT_CHAR_POISON))
                        pf2 += ({9096, time}); // 中毒
                if (time = get_effect_3(me, EFFECT_CHAR_POISON_2))
                        pf2 += ({9096, time}); // 中毒

                if (time = get_effect_3(me, EFFECT_CHAR_KING))
                        pf += ({9150, time}); // Thiên Vương Tán
                if (time = get_effect_3(me, EFFECT_CHAR_KING_2))
                        pf2 += ({9152, time}); // Thiên Vương Tán 2

                if (time = get_effect_3(me, EFFECT_CHAR_SUPPRESS))
                        pf2 += ({9561, time}); // 压制法宝

                if (time = get_effect_3(me, EFFECT_USER_DP))
                        pf += ({3291, time}); // Thiên Vương Tán
                if (time = get_effect_3(me, EFFECT_USER_PP))
                        pf += ({3292, time}); // Thiên Vương Tán

                if (time = get_effect_3(me, EFFECT_1808))
                        pf += ({1808, time});
                if (time = get_effect_3(me, EFFECT_1809))
                        pf += ({1809, time});
                if (time = get_effect_3(me, EFFECT_1810))
                        pf += ({1810, time});
                if (time = get_effect_3(me, EFFECT_1811))
                        pf += ({1811, time});
                if (time = get_effect_3(me, EFFECT_RECOVER_YUAN))
                        pf += ({298, time});
                if (time = get_effect_3(me, EFFECT_USER_PK))
                        pf += ({2214, time});
                // if (me->get_save("nlkhoa") >= 0)
                //         pf += ({782, 30000}); // Ngân Lượng khoá // skill
                if (me->get_vip())
                        pf += ({7401, 999});
                if (me->get("team_follow"))
                        pf += ({0011, -1});
                send_loop_perform_3(me, pf, EFFECT_GOOD);
                send_loop_perform_3(me, pf2, EFFECT_BAD);
                //                if (me->get_login_flag()<3) send_loop_perform_time(me, pf);
        }
}

// 函数：获取持续状态描述
string get_loop_desc(object me, int pf)
{
        switch (pf)
        {
        case 0002:
                return "/item/sell/0002"->get_loop_desc(me);
        case 0004:
                return "/item/sell/0004"->get_loop_desc(me);
        case 0006:
                return "/item/sell/0006"->get_loop_desc(me);
        case 0011:
                return "Theo sau nhóm";
        case 0298:
                return "/item/sell/0042"->get_loop_desc(me);

        case 0443:
                return "/npc/party/exchange_angel"->get_loop_desc1(me);
        case 0444:
                return "/npc/party/exchange_angel"->get_loop_desc2(me);
        case 0445:
                return "/npc/party/exchange_angel"->get_loop_desc3(me);
        case 0446:
                return "/npc/party/exchange_angel"->get_loop_desc4(me);

        case 1808:
                return "/item/final/91/1808"->get_loop_desc(me);
        case 1809:
                return "/item/final/91/1809"->get_loop_desc(me);
        case 1810:
                return "/item/final/91/1810"->get_loop_desc(me);
        case 1811:
                return "/item/final/91/1811"->get_loop_desc(me);

        case 2123:
                return "/skill/02/02123"->get_loop_desc(me);
        case 2114:
                return "/skill/02/02114"->get_loop_desc(me);
        case 2214:
                return "/cmd/base/set"->get_loop_desc(me);
        case 2221:
                return "/skill/02/02221"->get_loop_desc(me);
        case 2222:
                return "/skill/02/02222"->get_loop_desc(me);
        case 2321:
                return PF_FILE_02321->get_loop_desc(me);
        case 2421:
                return "/skill/02/02421"->get_loop_desc(me);
        case 2422:
                return "/skill/02/02422"->get_loop_desc(me);

        case 2516:
                return "/skill/02/02516"->get_loop_desc(me);
        case 2614:
                return "/skill/02/02614"->get_loop_desc(me);
        case 2616:
                return "/skill/02/02616"->get_loop_desc(me);

        case 3161:
                return "/skill/03/03161"->get_loop_desc(me);
        case 3162:
                return "/skill/03/03162"->get_loop_desc(me);
        case 3172:
                return PF_FILE_03172->get_loop_desc(me);
        case 3173:
                return PF_FILE_03173->get_loop_desc(me);
        case 3191:
                return "/skill/03/03191"->get_loop_desc(me);
        case 3192:
                return "/skill/03/03192"->get_loop_desc(me);

        // case 3251 : return PF_FILE_03251->get_loop_desc(me);
        case 3252:
                return PF_FILE_03252->get_loop_desc(me);
        case 3254:
                return PF_FILE_03254->get_loop_desc(me);

        case 3291:
                return "/skill/03/03291"->get_loop_desc(me);
        case 3292:
                return "/skill/03/03291"->get_loop_desc2(me);

        case 3481:
                return PF_FILE_03481->get_loop_desc(me);
        case 3482:
                return PF_FILE_03482->get_loop_desc(me);
        case 3484:
                return PF_FILE_03484->get_loop_desc(me);
        case 3485:
                return PF_FILE_03485->get_loop_desc(me);
        case 3486:
                return PF_FILE_03486->get_loop_desc(me);

        case 3631:
                return "/skill/03/03683"->get_loop_desc(me);
        case 3632:
                return PF_FILE_03632->get_loop_desc(me);
        case 3641:
                return PF_FILE_03641->get_loop_desc(me);
        case 3642:
                return "/skill/03/03642"->get_loop_desc(me);
        case 3643:
                return "/skill/03/03643"->get_loop_desc(me);

        case 4033:
                if (me->get_2("jg_effect_buff.sz1"))
                {
                        return "/item/08/0841"->get_pet_desc();
                }
                else if (me->get_2("jg_effect_buff.sz2"))
                {
                        return "/item/08/0842"->get_pet_desc();
                }
                else if (me->get_2("jg_effect_buff.sz3"))
                {
                        return "/item/08/0843"->get_pet_desc();
                }
        case 4141:
                return "/skill/04/04141"->get_loop_desc(me);
        case 4143:
                return PF_FILE_04143->get_loop_desc(me);
        case 4144:
                return PF_FILE_04144->get_loop_desc(me);
        case 4145:
                return PF_FILE_04145->get_loop_desc(me);
        case 4148:
                return "/skill/04/04148"->get_loop_desc(me);

        case 4171:
                return PF_FILE_04171->get_loop_desc(me);

        case 4243:
                return "/skill/04/04211"->get_loop_desc(me);
        case 4251:
                return PF_FILE_04251->get_loop_desc(me);
        case 4252:
                return PF_FILE_04252->get_loop_desc(me);

        case 5011:
                return PF_FILE_05011->get_loop_desc(me);
        case 5012:
                return "/skill/05/05012"->get_loop_desc(me);
        case 5013:
                return "/skill/05/05013"->get_loop_desc(me);
        case 5014:
                return "/skill/05/05014"->get_loop_desc(me);
        case 5016:
                return "/skill/05/05016"->get_loop_desc(me);
        case 5311:
                return PF_FILE_05311->get_loop_desc(me);
        case 5911:
                return "/skill/05/05911"->get_loop_desc(me);

        case 7401:
                return "/item/sell/0061"->get_loop_desc(me);

        case 9002:
                return PF_FILE_LOOP->get_loop_faint_desc(me);

        case 9010:
                return PF_FILE_LOOP->get_loop_no_pf_desc(me);
        case 9012:
                return PF_FILE_LOOP->get_loop_slow_desc(me);
        case 9013:
                return PF_FILE_LOOP->get_loop_lazy_desc(me);
        case 9016:
                return PF_FILE_LOOP->get_loop_dream_desc(me);
        case 9018:
                return PF_FILE_LOOP->get_loop_chaos_desc(me);
        case 9020:
                return PF_FILE_LOOP->get_loop_wound_desc(me);
        case 9022:
                return PF_FILE_LOOP->get_loop_blood_desc(me);
        case 9024:
                return PF_FILE_LOOP->get_loop_blind_desc(me);
        case 9026:
                return PF_FILE_LOOP->get_loop_burn_desc(me);
        case 9096:
                return "/skill/03/03632"->get_loop_desc2(me);

        case 9150:
                return PF_FILE_LOOP->get_loop_king_desc(me);
        case 9152:
                return PF_FILE_LOOP->get_loop_king_2_desc(me);
        case 9154:
                return "/sys/item/food"->get_loop_desc(me);
        case 9156:
                return "/sys/item/food"->get_loop_desc2(me);
        case 9158:
                return "/sys/item/food"->get_loop_desc3(me);

        case 9561:
                return PF_FILE_LOOP->get_loop_suppress_desc(me);
        case 9165:
                return "/item/91/9165"->get_loop_desc(me);

        case 9998:
                return "item/08/0001"->get_loop_desc();
        case 9999:
                return "item/08/0002"->get_loop_desc();
        // case 782:  // Ngân Lượng Khóa // Skill
        //         return PF_FILE_LOOP->nlkhoa(me);
        default:
                return "";
        }
}

// =============================================================

// 函数：征状结束效果

void effect_attack_done(object me) // 顺势推舟(自用)
{
        send_user(me, "%c%w%w%c", 0x81, 2321, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 2321, 0, EFFECT_GOOD);

        me->set_perform("02321", time());
        me->set_perform("02321#", 0);
        send_user(me, "%c%w%c%w", 0x50, PF_NO_02321, 0xff, 0);
}

void effect_add_dp_done(object me) // 金钟罩(＋防御)(自用)
{
        send_user(me, "%c%w%w%c", 0x81, 3161, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3161, 0, EFFECT_GOOD);

        USER_ENERGY_D->count_dp(me);

        me->set_perform("03161", time());
        me->set_perform("03161#", 0);
        send_user(me, "%c%w%c%w", 0x50, 3161, 0xff, 0);
}

void effect_add_pp_done(object me) // 护体金光(＋法防)(自用)
{
        send_user(me, "%c%w%w%c", 0x81, 3252, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3252, 0, EFFECT_GOOD);

        USER_ENERGY_D->count_pp(me); // cp/pp 影响 ap/dp, 所以放前
        USER_ENERGY_D->count_dp(me);

        me->set_perform("03252", time());
        me->set_perform("03252#", 0);
        send_user(me, "%c%w%c%w", 0x50, PF_NO_03252, 0xff, 0);
}

void effect_immortal_done(object me) // 不死之身(不死)(自用)
{
        if (me->get_perform("03254#"))
        {
                send_user(me, "%c%w%w%c", 0x81, 3254, 0, EFFECT_GOOD);
                send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3254, 0, EFFECT_GOOD);
                init_loop_perform(me);
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 32540, 1, OVER_BODY, PF_STOP);

                //	        me->set_perform( "03254", time() );
                me->set_perform("03254#", 0);
                //	        send_user( me, "%c%w%c%w", 0x50, PF_NO_03254, 0xff, 0 );
        }
}

void effect_invisible_done(object me) // 隐身(自用)
{
        if (get_effect_3(me, EFFECT_CHAR_INVISIBLE) && me->get_mp() >= 10)
        {
                if (me->get_save("no_visible"))
                        return;
                ;
                set_effect_2(me, EFFECT_CHAR_INVISIBLE, 3000, 10); // 每十秒减血
                me->add_mp(-10);
                return; // 能量不足，无法隐身
        }
        if (get_effect_3(me, EFFECT_CHAR_INVISIBLE) && me->get_mp() >= 10)
        {
                me->add_mp(-10);
                return; // 能量不足，无法隐身
        }
        send_user(me, "%c%w%w%c", 0x81, 3631, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3631, 0, EFFECT_GOOD);
        init_loop_perform(me);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9000, 1, UNDER_FOOT, PF_STOP);

        set_invisible(me, 0);
        send_user(me, "%c%c%c", 0x3d, 241, 2); // 恢复走路步数

        me->set_perform("03643", time());
        me->set_perform("03643#", 0);
        send_user(me, "%c%w%c%w", 0x50, 03683, 0xff, 0);
        set_effect_2(me, EFFECT_CHAR_INVISIBLE, 0, 0);
}

void effect_move_done(object me) // 踏雪无痕(自用)
{
        send_user(me, "%c%w%w%c", 0x81, 3641, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3641, 0, EFFECT_GOOD);

        me->set_save("03641", 0);
        //        USER_ENERGY_D->count_sp(me);

        me->set_perform("03641", time());
        me->set_perform("03641#", 0);
        send_user(me, "%c%w%c%w", 0x50, PF_NO_03641, 0xff, 0);
}

void effect_armorfall_done(object me) // 蚀甲(他用)
{
        int point;

        send_user(me, "%c%w%w%c", 0x81, 4143, 0, EFFECT_BAD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 4143, 0, EFFECT_BAD);

        if (me->is_user())
        {
                me->delete ("pf.armorfall");
                me->delete ("pf.armorfall2");
                me->delete_save_2("pf.armorfall");
                me->delete_save_2("pf.armorfall2");
                USER_ENERGY_D->count_pp(me); // cp/pp 影响 ap/dp, 所以放前
                USER_ENERGY_D->count_dp(me);
        }
        else
        {
                point = me->get("pf.armorfall"); // 有 BUG: 可能 CP/AP 会比原来高
                me->add_dp(-point);
                point = me->get("pf.armorfall2");
                me->add_pp(-point);
                me->delete ("pf.armorfall");
                me->delete ("pf.armorfall2");
        }
}

void effect_powerfall_done(object me) // 蚀心(他用)
{
        int point;

        send_user(me, "%c%w%w%c", 0x81, 4144, 0, EFFECT_BAD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 4144, 0, EFFECT_BAD);

        if (me->is_user())
        {
                me->set_save_2("pf.powerfall", 0);
        }
        else
        {
                point = me->get("pf.powerfall"); // 有 BUG: 可能 CP/AP 会比原来高
        }
}

void effect_fall_done(object me) // 蚀魂(他用)
{
        int point;
        if (me->is_user())
                point = me->get_save_2("pf.fall");
        else
                point = me->get("pf.fall");
        if (me->is_nianshou())
                point = 0;
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x68, getoid(me), -point);
        if (me->add_hp(point) < 1)
                me->set_hp(1);
        if (!get_effect_3(me, EFFECT_CHAR_FALL)) // 循环征状 set_effect_2
        {
                if (me->is_user())
                        point = me->set_save_2("pf.fall", 0);
                me->set("pf.fall", 0);
                send_user(me, "%c%w%w%c", 0x81, 4145, 0, EFFECT_BAD);
                send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 4145, 0, EFFECT_BAD);
        }
}

void effect_fmp_done(object me) // 蚀魄
{
        int point;
        if (me->is_user())
                point = me->get_save_2("pf.fmp");
        else
                point = me->get("pf.fmp");
        if (me->is_nianshou())
                point = 0;
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x6d, getoid(me), -point);
        me->add_mp(point);
        if (me->get_mp() < 0)
                me->set_mp(0);

        if (!get_effect_3(me, EFFECT_MP_FALL)) // 循环征状 set_effect_2
        {
                if (me->is_user())
                        point = me->set_save_2("pf.fmp", 0);
                me->set("pf.fmp", 0);
                send_user(me, "%c%w%w%c", 0x81, 4148, 0, EFFECT_BAD);
                send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 4148, 0, EFFECT_BAD);
        }
}

void effect_halfgod_done(object me) // 神打(自用)
{
        send_user(me, "%c%w%w%c", 0x81, 4171, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 4171, 0, EFFECT_GOOD);
        init_loop_perform(me);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 41710, 1, UNDER_FOOT, PF_STOP);

        USER_ENERGY_D->count_dp(me);

        me->set_save("04171", 0);
        send_user(me, "%c%w%c%w", 0x50, 4171, 0xff, 0);
}

void effect_change_done(object me) // 乾坤挪移(自用)
{
        send_user(me, "%c%w%w%c", 0x81, 4251, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 4251, 0, EFFECT_GOOD);

        me->set_change_hurt(0); // 没放入 USER_ENERGY_D

        me->set_perform("04251", time());
        me->set_perform("04251#", 0);
        send_user(me, "%c%w%c%w", 0x50, PF_NO_04251, 0xff, 0);
}

void effect_miss_done(object me) // 乾坤挪移
{
        send_user(me, "%c%w%w%c", 0x81, 4252, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 4252, 0, EFFECT_GOOD);

        me->set_save("pf.miss", 0);
        //        me->set_perform( "04252", time() );
        //        me->set_perform( "04252#", 0 );
        //        send_user( me, "%c%w%c%w", 0x50, PF_NO_04252, 0xff, 0 );
}

void effect_miss2_done(object me) // 灵气甲(自用)
{
        send_user(me, "%c%w%w%c", 0x81, 5911, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 5911, 0, EFFECT_GOOD);
        if (me->is_user())
                me->set_save("05911", 0);
        else
                me->set("05911", 0);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 10711, 1, OVER_BODY, PF_STOP);
}

void effect_powerup_done(object me) // 银针渡厄(他用)
{
        int point;
        send_user(me, "%c%w%w%c", 0x81, 5011, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 5011, 0, EFFECT_GOOD);
        if (me->is_user())
        {
                me->set_save("05011", 0);
                USER_ENERGY_D->count_ap(me);
        }
        else
        {
                me->add_ap(-me->get("05011"));
                me->set("05011", 0);
        }
}

void effect_powerup2_done(object me) // 金针渡厄(他用)
{
        int point;
        send_user(me, "%c%w%w%c", 0x81, 5012, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 5012, 0, EFFECT_GOOD);
        if (me->is_user())
        {
                me->set_save("05012", 0);
                USER_ENERGY_D->count_cp(me);
        }
        else
        {
                me->add_cp(-me->get("05012"));
                me->set("05012", 0);
        }
}

void effect_powerup3_done(object me) // 强体术(他用)
{
        int point;
        send_user(me, "%c%w%w%c", 0x81, 5014, 0, EFFECT_GOOD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 5014, 0, EFFECT_GOOD);
        if (me->is_user())
        {
                me->set_save("05014", 0);
                USER_ENERGY_D->count_max_hp(me);
        }
        else
        {
                me->add_max_hp(-me->get("05014"));
                me->set("05014", 0);
        }
}

void effect_no_pf_done(object me) // 封魔诀(他用)
{
        send_user(me, "%c%w%w%c", 0x81, 9010, 0, EFFECT_BAD);
        send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 9010, 0, EFFECT_BAD);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9010, 1, OVER_BODY, PF_STOP);
        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 21131, 1, OVER_BODY, PF_STOP);
}

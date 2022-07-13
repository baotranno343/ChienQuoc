
#include <equip.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main(object me, string arg2)
{
        object who, owner, map;
        int busy, count, time;
        string arg;
        me->set("new_heart", 1); // 新走路的标志
                                 //	if (me->get_ride()) return 1;
        if (me->is_store_open())
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }
        if (busy = get_effect(me, EFFECT_CHAR_BUSY))
        {
                return 1;
        }
        if (get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FREEZE) || get_effect(me, EFFECT_CHAR_DREAM_1) || get_effect(me, EFFECT_CHAR_DREAM))
                return 1;

        if (!arg2)
                return 1;
        if (sscanf(arg2, "%d %s", time, arg) != 2)
        {
                return 1;
        }
        count = me->get_2("go_count.count2");
        if (time > count)
        {
                count = time;
                me->set_2("go_count.count2", count);
        }
        else if (count > time)
        {
                notify("客户端时钟不对");
                return 1;
        }
        if (count > get_heart_timer(me))
        {
                notify("客户端时钟过快");
                return 1;
        }
        if (!objectp(who = find_char(arg)))
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }
        if (me == who)
        {
                return 1;
        }
        if (who->is_user() && who->get_login_flag() < 3)
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }
        if (who->is_die())
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }

        if (!inside_screen_2(me, who))
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }
        owner = who;
        if (who->get_ower())
                owner = who->get_owner();
        if (!who->can_be_fighted(me) || !me->can_fight(who))
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }

        if (me->get_char_action() != DEFAULT_ACT)
                me->set_char_action(DEFAULT_ACT); // 恢复站立状态(中止小动作)

        if (get_effect(me, EFFECT_CHAR_INVISIBLE))
                set_effect_2(me, EFFECT_CHAR_INVISIBLE, 1, 1); // 隐身(中断)
        me->set_enemy(0);
        me->start_fight(who);
        if (who->is_npc())
                who->start_fight(me); // 玩家需主动还击
        me->to_front_xy(get_x(who), get_y(who));
        if (!who->is_npc())
                me->set_clean_pk_time(0); //重新累计
        USER_HEART_D->heart_beat_attack(me);
        return 1;
}

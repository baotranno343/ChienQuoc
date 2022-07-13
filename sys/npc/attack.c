
#include <npc.h>
#include <effect.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：判断可以战斗
int can_fight(object me, object who)
{
        object map;

        if (me->get_no_fight())
                return 0;

        if (me == who)
                return 0; // 禁止攻击自己
                          //	map = get_map_object(get_z(me));
                          //	if (map->get_no_fight()) return 0;

        if (get_effect(me, EFFECT_MAGIC_4243))
                return 0;

        if (who->is_quanDoan())
        {
                if (me->is_quanDoan() && who->get_idChuQuanDoan() == me->get_idChuQuanDoan())
                {
                        return 0;
                }
        }

        if (me->is_quanDoan())
        {

                if (who->get_char_type() != FIGHTER_TYPE && !who->is_quanDoan())
                {

                        return 0;
                }
        }

        return 1;
}

// 函数：可以接受战斗
int can_be_fighted(object me, object who)
{
        object map;

        if (me->get_no_fight() && !me->cannot_enter_city())
                return 0; // 在安全区，且能进城(使玩家能打本不应进城的怪)
                          //    map = get_map_object(get_z(me));
                          //	if (map->get_no_fight()) return 0;
        if (me->is_quanDoan() && who->is_user())
        {
                return 0;
        }

        return 1;
}

// 函数：自动战斗
void auto_fight(object me, object who)
{
        object enemy;
        int d;

        switch (me->get_char_type())
        {
        case FIGHTER_TYPE:
        case FIGHTER_TYPE_2:
        case 132:

                d = distance_between(me, who);

                if (d > me->get_max_seek())
                        return;

                if (get_effect(me, EFFECT_NPC_0531_1)) // 被魅惑状态
                {
                        if (d > 1)
                                return;
                        set_effect(me, EFFECT_NPC_0531_1, 1);
                }
                if (enemy = me->get_enemy())
                {
                        if (enemy == who)
                                return;

                        if (distance_between(me, enemy) < d)
                                return;
                }

                me->start_fight(who);
                break;

        default:
                break;
        }
}


// 自用技能  TIPS:[PF_SELF]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <action.h>
#include <action.h>

#define THIS_SKILL      11002
#define THIS_PERFORM    11002
#define PF_START       "11002"
#define PF_NAME        "猛兽怒嚎"

#define SKILL_LEVEL     13
#define ADD_INTERVAL    1


// 函数：法术处理
int cast_done( object me )
{
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }



// 函数：命令处理
int perform_action_npc( object me, object who )
{
        int level;

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );


        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 3);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%d", level ) );

        return 1;
}

int cast_done_npc( object me )
{
        object *user, *char, who;
        string arg;
        int z, x, y;
        int level, ret, interval, i, size;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        level = to_int(arg);

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 34831, 1, OVER_BODY, PF_ONCE );

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        char = get_range_object(z, x, y, 10, USER_TYPE) + get_range_object(z, x, y, 10, CHAR_TYPE) - ({ me });

        interval = ADD_INTERVAL;    // 小心准备 me

        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] ) 
        {
                if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;    // 以下为附加效果！


                ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0, 0, -100);    // 小心准备 me
                if(     get_effect(who, EFFECT_CHAR_NO_PF)
                ||      get_effect(who, EFFECT_CHAR_NO_PF_0) ) continue;    // 执行成功
		if (who->get_perform("02221#")) continue;
                ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0, 0, -100);    // 小心准备 me
        	if (who->is_anti_effect()) continue;
        	if ( random(100) < who->get_anti_NoPF() ) continue ;	//抗封魔率
                if( ret > 0 ) 
                {
                        user = get_scene_object_2(who, USER_TYPE);
                        CHAR_CHAR_D->stop_loop_perform_faint(who);
                        set_effect(who, EFFECT_CHAR_NO_PF, interval);
                        if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                        send_user( who, "%c%w%w%c", 0x81, 9010, get_effect_3(who, EFFECT_CHAR_NO_PF), EFFECT_BAD );
                        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9010, 1, EFFECT_BAD );

                }
        }

        return 2;    // 执行成功
}

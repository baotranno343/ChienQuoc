
#include <effect.h>
#include <skill.h>

// 函数：跳舞效果
void into_dance_effect( object me ) 
{
        if( !me->is_die() ) me->add_hp( me->get("actor.dance") );

        if( !get_effect(me, EFFECT_CHAR_DANCE) )
        {
                CHAR_CHAR_D->init_loop_perform(me);
                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 01011, 10, OVER_BODY, PF_STOP );
        }
}

// 函数：唱歌效果
void into_sing_effect( object me ) 
{
        if( !me->is_die() ) me->add_mp( me->get("actor.sing") );

        if( !get_effect(me, EFFECT_CHAR_SING) )
        {
                CHAR_CHAR_D->init_loop_perform(me);
                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 01011, 10, OVER_BODY, PF_STOP );
        }
}

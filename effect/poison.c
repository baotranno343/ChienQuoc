
#include <skill.h>
#include <effect.h>

// 函数：中毒处理
void into_effect( object me )
{
        int poison = me->get_poison();
	if (me->is_nianshou())	poison =0;
        me->set_hp( range_value( me->get_hp() - poison, 1, me->get_hp() ) );
//      send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9024, 1, OVER_BODY, PF_LOOP );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x70, getoid(me), poison );

        if( !get_effect(me, EFFECT_CHAR_POISON) ) 
        {
                me->set_poison(0);
                set_effect_2(me, EFFECT_CHAR_POISON, 0, 0);
                send_user( me, "%c%w%w%c", 0x81, 9096, 0, EFFECT_BAD );
                send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9096, 0, EFFECT_BAD );
        }
}

// 函数：中毒处理
void into_effect_2( object me )
{
        int poison = me->get_poison_2();
	if (me->is_nianshou())	poison =0;
        me->set_hp( range_value( me->get_hp() - poison, 1, me->get_hp() ) );
//      send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9024, 1, OVER_BODY, PF_LOOP );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x70, getoid(me), poison );

        if( !get_effect(me, EFFECT_CHAR_POISON_2) ) 
        {
                me->set_poison_2(0);
                set_effect_2(me, EFFECT_CHAR_POISON_2, 0, 0);
                send_user( me, "%c%w%w%c", 0x81, 9096, 0, EFFECT_BAD );
                send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9096, 0, EFFECT_BAD );
        }
}


#include <skill.h>

// 函数：被魅惑状态(ＮＰＣ)
void into_effect_2( object me ) 
{
        object *user;

        me->set_action(1);    // 恢复正常
        user = get_scene_object_2(me, USER_TYPE);
//      send_user( me, "%c%w%w%c", 0x81, 5311, 0, EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 5311, 0, EFFECT_GOOD );
        CHAR_CHAR_D->init_loop_perform(me);
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 5311, 1, OVER_BODY, PF_STOP );
}

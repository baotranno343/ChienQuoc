
#include <skill.h>

// 函数：气血、法力变为１
void into_effect( object me ) 
{
        send_user( me, "%c%w%w%c", 0x81, 9152, 0, EFFECT_BAD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9152, 0, EFFECT_BAD );

        USER_ENERGY_D->count_max_hp(me);
        USER_ENERGY_D->count_max_mp(me);
        USER_ENERGY_D->count_cp(me);    // cp/pp 影响 ap/dp, 所以放前
        USER_ENERGY_D->count_pp(me);
        USER_ENERGY_D->count_ap(me);
        USER_ENERGY_D->count_dp(me);
}


#include <npc.h>
#include <effect.h>

// 函数：清除连线保护
void into_effect( object me )
{
        if( me->get_login_flag() < 3 )    // 与 inh/char/cmd 同步
        {
                me->set_login_flag(3);
//              me->set_char_type(PLAYER_TYPE_2);
                me->add_pk(0);    // 显示ＰＫ状态
                if( !get_effect(me, EFFECT_CHAR_INVISIBLE) ) set_invisible(me, 0);    // 没有隐身时
                if( gone_time( me->get_login_time() ) < 25 ) USER_TASK_D->auto_give_task(me);    // 只在登录时(故意多5秒)
        }
}

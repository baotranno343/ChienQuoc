
#include <effect.h>

// 函数：读书效果
void into_effect( object me ) 
{
        int skill = me->get_save("study");
        if( !me->get_skill(skill) ) return;
        USER_SKILL_D->improve_skill_2(me, skill, 250);

        if( !get_effect(me, EFFECT_USER_STUDY) )
        {
                send_user(me, "%c%s", '!', "您无法从翻阅得残破不全的书中领悟到什么。");
        }
}

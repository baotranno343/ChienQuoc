
/*
备注：该命令主要用于将系统端一些功能，放到客户端去，而减少系统的负载。特别针对于涉及心跳的。
*/

/*
警告：更改此处任何数值，注意是否需要同时更改客户端！！！
*/

#include <skill.h>

#define ADD_03484       03484           // 增加物理攻击(“兵法”被动技能)
#define ADD_03485       03485           // 增加物理防御(“兵法”被动技能)
#define ADD_03486       03486           // 补满玩家元气(“兵法”被动技能)

// 函数：命令处理
int main( object me, string arg )
{
/*	
        switch( to_int(arg) )
        {
        case ADD_03484 : 

                if(     me->get_skill(SKILL_0348) >= 50    // 要求“兵法”等级
                &&      me->get_hp() <= me->get_max_hp() / 2 )    // 生命低于 50%
                {
                        me->set_perform( PF_FLAG_03484, time() );
                        USER_ENERGY_D->count_ap(me);    // 提升攻击力
                        send_user( me, "%c%w%w%c", 0x81, 3484, -1, EFFECT_GOOD );
                        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3484, 1, EFFECT_GOOD );
                }

                return 1;

        case ADD_03485 : 

                if(     me->get_skill(SKILL_0348) >= 52    // 要求“兵法”等级
                &&      me->get_hp() <= me->get_max_hp() / 2 )    // 生命低于 50%
                {
                        me->set_perform( PF_FLAG_03485, time() );
                        USER_ENERGY_D->count_dp(me);    // 提升防御力
                        send_user( me, "%c%w%w%c", 0x81, 3485, -1, EFFECT_GOOD );
                        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3485, 1, EFFECT_GOOD );
                }

                return 1;

        case ADD_03486 : 

                if( me->get_yuan() >= me->get_max_yuan() ) return 1;

                if(     me->get_skill(SKILL_0348) >= 80    // 要求“兵法”等级
                &&      me->get_hp() < me->get_max_hp() / 10 )    // 生命低于 10%
                {
                        me->set_perform( PF_FLAG_03486, time() );
                        me->set_yuan( me->get_max_yuan() );    // 补满玩家元气
                        send_user( me, "%c%w%w%c", 0x81, 3486, -1, EFFECT_GOOD );
                        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3486, 1, EFFECT_GOOD );
                }

                return 1;
        }
*/
        return 1;
}

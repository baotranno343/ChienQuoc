
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <action.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      11006
#define THIS_PERFORM    11006
// Trọng Ích
#define PF_NAME        "重辟"



// 函数：命令处理
int perform_action_npc( object me, object who )
{
        int z, d, x0, y0;
        int level, mp, ret;
        object *user;

	CHAR_FIGHT_D->attack_action(me, who);
        ret = CHAR_FIGHT_D->attack_done(me, who,HIT_NORMAL);    // 小心准备 me
	if ( !who ) return 2;
	if ( who->is_die() ) return 2;
        if (who->get("anti_faint")) return 2;
        if (ret >0 && random(100) < 10)
        {
        	if (!who) return 1;
	        if(     get_effect(who, EFFECT_CHAR_FAINT)
	        ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) return 1;    // 执行成功
	        if (who->get_perform("02222#")) return 1;
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT, 3);    // 小心准备 me
                CHAR_CHAR_D->init_loop_perform(who);
                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );	        
        }
        return 1;
}

// 函数：特殊技处理
int cast_done( object me )
{
        return 2;    // 执行成功
}
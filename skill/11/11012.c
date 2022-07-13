
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <action.h>

#define THIS_SKILL      11012
#define PF_NAME        "冰霜咒"

// 函数：获取符法效果
int get_cast_seal() { return 9102; }    // 符纸顺旋

// 函数：命令处理
int perform_action_npc( object me, object who )
{
        object *user;

        if( !inside_screen_2(me, who) ) return 0;

        me->to_front_xy( get_x(who), get_y(who) );
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), me->get_skill(THIS_SKILL) ) );

        return 1;
}

// 函数：法术处理
int cast_done_npc( object me )
{
        object *char,*nTarget,*user,who;
        string arg;
        int i,size,z, x, y;
        int level, ret;

	char = get_range_object(get_z(me), get_x(me), get_y(me), 10, USER_TYPE) + get_range_object(get_z(me), get_x(me), get_y(me), 10, CHAR_TYPE) - ({ me,0 });
	nTarget = ({});
	for(i=0,size=sizeof(char);i<size;i++)
	{
		if ( me->can_fight(char[i]) )
			nTarget += ({char[i]});	
	}
	who=nTarget[random(sizeof(nTarget))];

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 
                4234, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        ret = CHAR_FIGHT_D->cast_done(me, who);    // 小心准备 me
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,100);
        if( !who ) return 2;    // 执行成功
	if( !me ) return 2;    // 执行成功
		
//        if(     get_effect(who, EFFECT_CHAR_FAINT)
//        ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) return 2;    // 执行成功
        if (who->get_perform("02222#")) return 2;

        if( get_effect(who, EFFECT_CHAR_9145) ) return 2;    // 执行成功

	if (ret>0)
	{
                if( !get_effect(who, EFFECT_CHAR_NO_MOVE) && !get_effect(who, EFFECT_CHAR_FAINT_0) )
                {         
                	if (who->get_perform("02222#")) return 2;       
	                user = get_scene_object_2(who, USER_TYPE);
	                set_effect(who, EFFECT_CHAR_NO_MOVE, 20);    // 小心准备 me
	                set_effect(who, EFFECT_CHAR_FAINT_0, 22); 
	                CHAR_CHAR_D->init_loop_perform(who);
	                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
	                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_NO_MOVE), EFFECT_BAD );
	                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
	                send_user( user, "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 34721, 10, UNDER_FOOT, 34722, 10, UNDER_FOOT, PF_LOOP );	        
	                CHAR_CHAR_D->init_loop_perform(who);
                }	
	}
        return 2;    // 执行成功
}


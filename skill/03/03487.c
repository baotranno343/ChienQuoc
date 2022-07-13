
// 自用技能  TIPS:[PF_SELF]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <action.h>
#include <action.h>

#define THIS_SKILL      0348
#define THIS_PERFORM    03487
#define PF_START       "03487"
#define PF_TIME        "03487#"
#define PF_NAME        "Sư Tử Hống"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   20
#define SUB_MP          0
#define SUB_YUAN        4
#define ADD_INTERVAL    4

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 150\n Dồn tất cả nguyên khí tinh nguyên trời đất,Thét lên 1 tiếng trời long đất lở, khiến cho những đối thủ xung quanh bị Choáng trong 4 giây.", PF_NAME);
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Dồn tất cả nguyên khí tinh nguyên trời đất,Thét lên 1 tiếng trời long đất lở, khiến cho những đối thủ xung quanh bị Choáng trong 4 giây.", 
        	PF_NAME, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL);
        return result;	
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp;
        object *user, *char;
        int z;
        int ret, interval, i, size;
        
        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("03487")==0) return 1;
		
        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        me->add_mp(-mp);
        me->add_yuan( -SUB_YUAN );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 1);
        me->add_2("go_count.count2",1);
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 34831, 6, OVER_BODY, PF_ONCE );

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        char = get_range_object(z, x, y, 6, USER_TYPE) + get_range_object(z, x, y, 6, CHAR_TYPE) - ({ me });

        interval = ADD_INTERVAL;    // 小心准备 me

        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] ) 
        {
                if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;    // 以下为附加效果！

//                if(     get_effect(who, EFFECT_CHAR_FAINT)
//                ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) continue;    // 执行成功
				if(      get_effect(who, EFFECT_CHAR_FAINT_0) ) continue;
                if (who->get_perform("02222#")) continue;
		ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0, 0, -100);    // 小心准备 me
		if (!who) continue;
		if (who->is_anti_effect()) continue;
		if (who->get("anti_faint")) continue;
                if( ret > 0 ) 
                {
                        user = get_scene_object_2(who, USER_TYPE);
                        set_effect(who, EFFECT_CHAR_FAINT, interval);
                        CHAR_CHAR_D->stop_loop_perform_faint(who);
                        CHAR_CHAR_D->init_loop_perform(who);
                        if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                        send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
                        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );
                }
        }
        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform( object me )
{
        int interval;
		if (me->get_save("03487")==0) return;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, PF_NAME );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}

// 函数:命令处理
int perform_action_npc( object me, object who )
{
        int level, mp;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                return 0;
        }
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 1);
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

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        level = to_int(arg);

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 34831, 6, OVER_BODY, PF_ONCE );

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        char = get_range_object(z, x, y, 25, USER_TYPE) + get_range_object(z, x, y, 25, CHAR_TYPE) - ({ me });

        interval = ADD_INTERVAL;    // 小心准备 me

        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] ) 
        {
        	if (!me) return 2;
                if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;    // 以下为附加效果！

//                if(     get_effect(who, EFFECT_CHAR_FAINT)
//                ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) continue;    // 执行成功
				  if(      get_effect(who, EFFECT_CHAR_FAINT_0) ) continue;    // 执行成功
		if (who->get_perform("02222#")) continue;
                ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0, 0, -100);    // 小心准备 me
                if( ret > 0 ) 
                {
                        user = get_scene_object_2(who, USER_TYPE);
                        CHAR_CHAR_D->stop_loop_perform_faint(who);
                        set_effect(who, EFFECT_CHAR_FAINT, interval);
                        CHAR_CHAR_D->init_loop_perform(who);
                        if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                        send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
                        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );
                }
        }

        return 2;    // 执行成功
}

// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0422
#define THIS_PERFORM    04224
#define PF_START       "04224"
#define PF_TIME        "04224#"
#define PF_NAME        "Âm Dương Hộ Thể"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   45 - ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 1
#define SUB_MP          10000 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 20
#define ADD_INTERVAL    25 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 100


// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 30 cấp\n    Dùng đạo hạnh của tiên gia để hộ thân, trong suốt thời gian tác dụng sẽ giảm tất cả sát thương nhận được chỉ còn 1 điểm Khí Huyết mất đi。";
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Dùng đạo hạnh của tiên gia để hộ thân, trong %d giây sẽ giảm tất cả sát thương nhận được chỉ còn 1 điểm Khí Huyết mất đi。\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tiên Thân Vô Địch kéo dài %d giây,Thời gian tái sử dụng giảm còn %d giây。", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_INTERVAL, cur_level*150+SKILL_LEVEL, ADD_INTERVAL + 100, TIME_INTERVAL - 1 );
        return result;    
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        if( me->get_perform(PF_START) )
                return sprintf( PF_NAME "：\n　　Tất cả sát thương nhận được chỉ còn 1 điểm Khí Huyết tiêu hao。\n" );
        else    return sprintf( PF_NAME "\n" );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, interval, mp;
        object *user;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("04224")==0) return 1;
		
        interval = TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;    // 小心准备 me

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) 
        {
        	notify( "你处于封印状态中。" );
        	return 1;
        }
        me->add_mp(-mp);
        CHAR_FIGHT_D->set_enmity1(me,20);
        
        interval = ADD_INTERVAL;    // 小心准备 me

        me->set_perform( PF_START, time() );
        me->set_perform( "03254#",interval);
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );

        user = get_scene_object_2(me, USER_TYPE);
        set_effect_2(me, EFFECT_CHAR_IMMORTAL, 1, interval);
        send_user( me, "%c%w%w%c", 0x81, 3254, get_effect_3(me, EFFECT_CHAR_IMMORTAL), EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3254, 1, EFFECT_GOOD );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 32549, 1, OVER_BODY, PF_ONCE );
        CHAR_CHAR_D->init_loop_perform(me);
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 32540, 1, OVER_BODY, PF_LOOP );

        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object *user;
        int level, interval;
/*
        level = me->get_skill(THIS_SKILL);
        interval = ADD_INTERVAL;    // 小心准备 me

        me->set_perform( PF_START, time() );
        me->set_perform( PF_TIME, interval );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, interval );

        user = get_scene_object_2(me, USER_TYPE);
        set_effect(me, EFFECT_CHAR_IMMORTAL, interval);
        send_user( me, "%c%w%w%c", 0x81, 3254, get_effect_3(me, EFFECT_CHAR_IMMORTAL), EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3254, 1, EFFECT_GOOD );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 32549, 1, OVER_BODY, PF_ONCE );
        CHAR_CHAR_D->init_loop_perform(me);
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 32540, 1, OVER_BODY, PF_LOOP );

        // 效果见 energy_d.c
*/
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
		if (me->get_save("04224")==0) return;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/15+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
}

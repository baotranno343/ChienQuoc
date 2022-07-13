
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0329	
#define THIS_PERFORM    03298
#define PF_START       "03298"
#define PF_TIME        "03298#"
#define PF_NAME        "Đệ Nhất Thái Cực"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   30
#define SUB_MP          ( 0 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/150 * 1 )
#define ADD_EFFECT	1500
#define ADD_TIME	( 30 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/150 * 120 )
#define ADD_ENMITY	1*mp + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/150*30 + ret


// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 150\n Liên tục trong 30 giây hoá giải sát thương nhận được.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        result = sprintf(HIY" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao : Toàn Bộ \n Sát thương nhận được: %d điểm\n Tái sử dụng sau: %d giây\n Liên tục trong %d giây Hoá giải sát thương nhận được ( Chuyển hoá %d％ Nội Lực đã mất để hoá giải sát thương ).\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n Liên tục trong %d giây Hoá giải sát thương nhận được ( Chuyển hoá %d％ Nội Lực đã mất để hoá giải sát thương ).", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_TIME, ADD_EFFECT, cur_level*150+SKILL_LEVEL, ADD_TIME+120, ADD_EFFECT);     	
        return result;
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        if( me->get_perform(PF_START) )
                return sprintf(  " %s :\n Tăng thêm %d ％Thân Thủ.\n", PF_NAME, me->get_save("03641") );
        else    return sprintf( PF_NAME "\n" );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, interval, mp, ret;
        object *user;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("03298")==0) return 1;
		
        interval = TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->add_mp(-mp);
       	CHAR_FIGHT_D->set_enmity1(me,20);	
        
	interval = ADD_TIME;
//      me->set_cast_arg( sprintf( "%d", level ) );
        me->set_perform( PF_START, time() );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );	
        user = get_scene_object_2(me, USER_TYPE);
        set_effect(me, EFFECT_CHAR_MOVE, interval );
        send_user( me, "%c%w%w%c", 0x81, 3641, get_effect_3(me, EFFECT_CHAR_MOVE), EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3641, 1, EFFECT_GOOD );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 51144, 40, OVER_BODY, PF_ONCE );
		send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 51141, 40, OVER_BODY, PF_ONCE );
	me->set_save("03641", ADD_EFFECT);
	
	mp = me->get_mp();
        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, (ADD_TIME)*mp );    // 小心准备 me
        me->add_mp( -mp );

        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,ADD_ENMITY);
			
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
		if (me->get_save("03298")==0) return;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
}

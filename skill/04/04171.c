
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0417
#define THIS_PERFORM    04171
#define PF_START       "04171"
#define PF_TIME        "04171#"
#define PF_NAME        "Thần Tuệ Pháp Chú"

#define SKILL_LEVEL     10
#define TIME_INTERVAL   2
#define SUB_MP          ( 30 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 10 * 30 )
#define ADD_DP    	( 30 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 10 * 30 )

// 函数：获取符法效果
int get_cast_seal() { return 9103; }    // 符纸逆旋
int cast_done( object me );

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 10 cấp\n    Liên tục trong vòng 30 phút nâng cao 30 điểm Ngoại Kháng của bản thân.";
        cur_level = (level - SKILL_LEVEL)/10 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Liên tục trong vòng 30 phút nâng cao %d điểm Ngoại Kháng của bản thân.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Liên tục trong vòng 30 phút nâng cao %d điểm Ngoại Kháng của bản thân.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, 2, ADD_DP, cur_level*10+SKILL_LEVEL, ADD_DP + 30 );
        return result;	
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        if (get_effect(me, EFFECT_CHAR_HALFGOD2))
                return sprintf( PF_NAME "：\n　　Gia tăng %d điểm Ngoại Kháng.\n", 
                        me->get_save("04171") );
        else    return sprintf( PF_NAME "\n" );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user;
        int level, mp, interval;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        interval = TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        user = get_scene_object_2(me, USER_TYPE);
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);
	cast_done(me);
	CHAR_FIGHT_D->set_enmity1(me,20);
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object *user;
        int level, interval;

        level = me->get_skill(THIS_SKILL);
        interval = 1800;    // 小心准备 me

        me->set_perform( PF_START, time() );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );

        user = get_scene_object_2(me, USER_TYPE);
        set_effect(me, EFFECT_CHAR_HALFGOD2, interval);
        send_user( me, "%c%w%w%c", 0x81, 4171, get_effect_3(me, EFFECT_CHAR_HALFGOD2), EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 4171, 1, EFFECT_GOOD );
        CHAR_CHAR_D->init_loop_perform(me);
//        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 41710, 1, UNDER_FOOT, PF_LOOP );
	me->set_save("04171", ADD_DP);
        USER_ENERGY_D->count_dp(me);

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;

        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10+1);
        interval = TIME_INTERVAL + me->get_perform(PF_TIME) - gone_time( me->get_perform(PF_START)  );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
}


// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0348
#define THIS_PERFORM    03484
#define PF_START       "03484"
#define PF_TIME        "03484#"
#define PF_NAME        "Sinh Tử Thần Lực"

#define SKILL_LEVEL     21
#define TIME_INTERVAL   70 - ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 15 * 5
#define SUB_MP          0
#define SUB_YUAN        4
#define ADD_TIME	9 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 15 
#define ADD_AP		30 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 15 * 30
#define ADD_DP		60 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 15 * 60


// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 21 cấp\n    Trong 9 giây tăng thêm 30 điểm Ngoại Công và 60 điểm Ngoại Kháng";
        cur_level = (level - SKILL_LEVEL)/15 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Trong %d giây tăng thêm %d điểm Ngoại Công và %d điểm Ngoại Kháng.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Trong %d giây tăng thêm %d điểm Ngoại Công và %d điểm Ngoại Kháng.Thời gian tái sủ dụng giảm còn %d giây.",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_TIME, ADD_AP, ADD_DP, cur_level*15+SKILL_LEVEL, ADD_TIME +50, ADD_AP + 30, ADD_DP + 60, TIME_INTERVAL - 5 );
	return result;
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        if( me->get_perform(PF_START) )
                return sprintf( PF_NAME "：\n　　Gia tăng Ngoại Công và Ngoại Kháng.\n" );
        else    return sprintf( PF_NAME "\n" );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, interval, mp;
        object *user;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        interval = TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
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
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2",9);
        interval = ADD_TIME;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
	set_effect(me, EFFECT_03484, interval);
        user = get_scene_object_2(me, USER_TYPE);
        send_user( me, "%c%w%w%c", 0x81, 3484, get_effect_3(me, EFFECT_03484), EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3484, 1, EFFECT_GOOD );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 32521, 1, OVER_BODY, PF_ONCE );
	me->set_save("3484_1", ADD_AP);
	me->set_save("3484_2", ADD_DP);
        USER_ENERGY_D->count_ap(me);
        USER_ENERGY_D->count_dp(me);

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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}

void into_effect(object me)
{
        send_user( me, "%c%w%w%c", 0x81, 3484, 0, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3484, 0, EFFECT_GOOD );	
	me->set_save("3484_1", 0);
	me->set_save("3484_2", 0);
        USER_ENERGY_D->count_ap(me);
        USER_ENERGY_D->count_dp(me);	
}
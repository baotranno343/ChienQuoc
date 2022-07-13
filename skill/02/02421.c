
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0242
#define THIS_PERFORM    02421
#define PF_START       "02421"
#define PF_TIME        "02421#"
#define PF_NAME        "Mãnh Hổ Bộ Pháp"

#define SKILL_LEVEL     7
#define TIME_INTERVAL   2
#define SUB_MP          0
#define SUB_YUAN        1
#define ADD_SP		10 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/11*2

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR" %s \n Võ công yêu cầu: Cấp 7\n Bộ pháp tăng cường khả năng tránh né của Cấm Vệ Quân, tăng thêm 10%% Thân Thủ trong 120 giây.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/11 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Bộ pháp tăng cường khả năng tránh né của Cấm Vệ Quân, tăng thêm %d %% Thân Thủ trong 120 giây.\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: " HIR "Cấp %d " NOR"\n Tăng thêm %d %% Thân Thủ trong 120 giây.",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_SP, cur_level*11+SKILL_LEVEL, ADD_SP+2 );
	return result;
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
	if (get_effect(me, EFFECT_USER_SP))
		return sprintf("Tăng %d %%Thân Thủ .\n", me->get_save("02421#") );
        return "Gia tăng phần trăm né tránh\n";
}


// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, interval, mp, z, add, level2;
        object *user;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        interval = TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
        who = me;
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        me->add_mp(-mp);
        me->add_yuan( -SUB_YUAN );
        CHAR_FIGHT_D->set_enmity1(me,20);	

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
         me->add_2("go_count.count2",9);
         
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
	return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        int level, interval, mp, z, add, level2;
        object *user, who;
        string arg;
        interval = 120;
        if( !stringp( arg = me->get_cast_arg() ) ) return 2;
        who = me;

        me->set_perform( PF_TIME, interval );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        add = ADD_SP;
	user = get_scene_object_2(who, USER_TYPE);
	if (who->is_anti_effect()) return 2;
	set_effect(who, EFFECT_USER_SP, interval);
	send_user( who, "%c%w%w%c", 0x81, 2421, get_effect_3(who, EFFECT_USER_SP), EFFECT_GOOD );
	send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 2421, 1, EFFECT_GOOD );
	who->set_save("02421#", add);
	if (who->is_user()) USER_ENERGY_D->count_sp(who);
	
	send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 2710, 1, OVER_BODY, PF_ONCE );
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
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/11+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}

void effect_done(object me)
{
	me->set_save("02421#", 0);
        send_user( me, "%c%w%w%c", 0x81, 2421, 0, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 2421, 0, EFFECT_GOOD );
        if (me->is_user()) USER_ENERGY_D->count_dp(me);
}

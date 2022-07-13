
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0316
#define THIS_PERFORM    03162
#define PF_START       "03162"
#define PF_TIME        "03162#"
#define PF_NAME        "Trấn Cổ Thần Uy"

#define SKILL_LEVEL     33
#define TIME_INTERVAL   10
#define SUB_MP          0
#define SUB_YUAN        1
#define ADD_AP		18 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/16

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level, interval;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 33 cấp\n    Trong thời gian sử dụng sẽ tăng sát thương công kích cho toàn bộ thành viên Nhóm trong phạm vi tầm nhìn.";
        cur_level = (level - SKILL_LEVEL)/16 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Trong thời gian sử dụng sẽ tăng %d%% sát thương công kích cho toàn bộ thành viên Nhóm trong phạm vi tầm nhìn.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Trong thời gian sử dụng sẽ tăng %d%% sát thương công kích cho toàn bộ thành viên Nhóm trong phạm vi tầm nhìn.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP, cur_level*16+SKILL_LEVEL, ADD_AP+2 );
	return result;  
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
        if( get_effect(me, EFFECT_EXCITE ) )
                return sprintf( PF_NAME ":\n　　Gia tăng %d%% công kích.\n", me->get_save(PF_TIME) );
        else    return sprintf( PF_NAME "\n" );
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, interval, mp, i, size, z;
        object *user, *team, *all;

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
        interval = 60;

        me->set_perform( PF_TIME, interval );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        
        all = me->get_team();
        if (all==0) all = ({ me });
        all -= ({ 0 });
        size = sizeof(all);
        z = get_z(me), x = get_x(me), y = get_y(me);
        team = ({ });
        for (i=0;i<size;i++)
        {
        	if (all[i]==me) team += ({ all[i] });
        	else
        	if (z==get_z(all[i])&& abs(x-get_x(all[i]))<9 && abs(y-get_y(all[i]))<9)
        		team += ({ all[i] });
        }
	size = sizeof(team);
	for (i=0;i<size;i++) if (who = team[i])
	{
		if ("/sys/user/attack"->can_use_help(me, who)==0) continue;
		if (who->is_anti_effect()) continue;
	        user = get_scene_object_2(who, USER_TYPE);
	        set_effect(who, EFFECT_EXCITE, interval);
	        send_user( who, "%c%w%w%c", 0x81, 3162, get_effect_3(who, EFFECT_EXCITE), EFFECT_GOOD );
	        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 3162, 1, EFFECT_GOOD );
	        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 3162, 1, OVER_BODY, PF_ONCE );
	        who->set_save(PF_TIME, ADD_AP);
	        CHAR_FIGHT_D->set_enmity2(me,who,250 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/10*50);
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
        string name;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/16+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, MAGIC_ACT_BEGIN, 0, 9, 0);
}

void effect_done(object me)
{
	    me->set_save("03162#", 0);
        send_user( me, "%c%w%w%c", 0x81, 3162, 0, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3162, 0, EFFECT_GOOD );	
}
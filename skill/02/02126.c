
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <action.h>

#define THIS_SKILL      0212
#define THIS_PERFORM    02126
#define PF_START       "02126"
#define PF_TIME        "02126#"
#define PF_NAME        "Hàng Long Hữu Hối"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   60
#define SUB_MP          ( 0 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 1 )
#define ADD_CP          ( 500 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 500 )


// 函数：获取符法效果
int get_cast_seal() { return 9103; }    // 符纸顺旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level, size;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: 150 cấp\n Chưởng pháp gọi rồng tấn công đối thủ.Có xác xuất 100％ khi đánh trúng mục tiêu khiến mục tiêu choáng 10 giây.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/150 + 1;
		size = 9 + (level/ 80 )*400;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Chưởng pháp gọi rồng tấn công đối thủ.Tăng %d Nội Công và Có xác xuất 100％ khi đánh trúng mục tiêu khiến mục tiêu choáng 10 giây.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n  Tăng %d Nội Công。", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_CP, cur_level*150+SKILL_LEVEL, ADD_CP + 500, 9 + ((cur_level*150+SKILL_LEVEL)/ 80 )*400 );
        return result;  
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user;
        int z;
        int level, mp;
		int size, size2;


        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("02126")==0) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );        
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_ONCE );

        me->add_mp(-mp);
		
		size = 9 + (level/ 80 )*400;
        size2 = size;
		
        CHAR_FIGHT_D->set_enmity1(me,80);	

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 1);
        me->add_2("go_count.count2",1);
        send_user(me, "%c", 0x01);
        me->set_cast_file(__FILE__);
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object *user, who;
        string arg;
        int z, x, y;
        int level, ret;
	
		send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        set_effect_2(me, EFFECT_PROGRESS, 1, 0);
        me->set_progress_file(__FILE__);
        me->set_enemy(0);        
        send_user(me, "%c%c%w%s", 0x5a, 0, 1, "Hàng Long Hữu Hối……");
        return 2;    // 执行成功
}


void into_effect(object me, string arg)
{
        object *user, *char, who;
        int z, x, y;
        int level, mp, rate, i, size, count, ret;
	int add, cp;
	add = ADD_CP;
	cp = me->get_cp();
	me->set_cp(add+cp*1/1);
        z = get_z(me);  x = get_x(me);  y = get_y(me);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x50, getoid(me), time2(), MAGIC_ACT_END );
        char = get_range_object(z, x, y, 20, USER_TYPE) + get_range_object(z, x, y, 20, CHAR_TYPE) - ({ me });
        count = 0;
        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] ) 
        {
                if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;
		count ++;
		if (count<=100)
//       	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 5116, 1, OVER_BODY, PF_ONCE );
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 42341, 3, OVER_BODY, PF_ONCE );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 42351, 2, OVER_BODY, PF_ONCE );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9026, 5, OVER_BODY, PF_ONCE );
                 ret = CHAR_FIGHT_D->cast_done(me, who);
				 ret += CHAR_FIGHT_D->cast_done(me, who);
				 ret += CHAR_FIGHT_D->cast_done(me, who);
				 ret += CHAR_FIGHT_D->cast_done(me, who);
				 ret += CHAR_FIGHT_D->cast_done(me, who);
	        if ( who && !who->is_die() )
	        	CHAR_FIGHT_D->set_enmity(me,who,90);
				
	        if (ret>0 && who && random100()<100)
	        {	        	
//		        if (who->is_anti_effect())continue;
//       		if (who->get("anti_faint")) continue;
//			if(     get_effect(who, EFFECT_CHAR_FAINT)
//			||      get_effect(who, EFFECT_CHAR_FAINT_0) ) continue;    // 执行成功
			if(      get_effect(who, EFFECT_CHAR_FAINT_0) ) continue;
//			if (who->get_perform("02222#")) continue;
		        user = get_scene_object_2(who, USER_TYPE);
		        set_effect(who, EFFECT_CHAR_FAINT, 10);    // 小心准备 me
		        CHAR_CHAR_D->init_loop_perform(who);
		        if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
		        send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
		        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
		        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );
			}	
        }	
	me->set_cp(cp);
	if( !get_effect_3(me, EFFECT_PROGRESS) ) 
	{
		send_user(me, "%c%c%c", 0x5a, 1, 1);
	}
}

void effect_break(object me, string arg)
{
	object who, owner;
	int add, time;
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	set_effect_2(me, EFFECT_PROGRESS, 0, 0);	
}


// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
		if (me->get_save("02126")==0) return;
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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 5, 0);
}

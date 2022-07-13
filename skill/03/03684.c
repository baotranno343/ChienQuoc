
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0368
#define THIS_PERFORM    03684
#define PF_START       "03684"
#define PF_NAME        "Thích Sát"

#define SKILL_LEVEL     9
#define TIME_INTERVAL   2
#define SUB_MP          ( 13 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/15 * 4 )
#define ADD_AP		( 50 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/15 * 40 )


// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR" %s \n Võ công yêu cầu: Cấp 9\n Tuyệt kĩ ám sát tăng thêm 50 điểm Ngoại Công khi sát thương mục tiêu, đồng thời còn làm đối thủ Trọng Thương liên tục trong 16 giây sau.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/15 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Tuyệt kĩ ám sát tăng thêm %d điểm Ngoại Công khi sát thương mục tiêu, đồng thời còn làm đối thủ Trọng Thương liên tục trong 16 giây sau.\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: " HIR "Cấp %d " NOR"\n    Tăng thêm %d điểm Ngoại Công.",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP, cur_level*15+SKILL_LEVEL, ADD_AP + 40 );
	return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, act, pf;
        int level, mp, d, hp, damage;
        object *user;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;

                x = get_x(who);  y = get_y(who);
        }
        else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }
        else
        {
		return 1;
        }	
	if (get_z(who)!=get_z(me)||abs(get_x(me)-get_x(who))>1||abs(get_y(me)-get_y(who))>1) 
	{
                printf( ECHO "Sử dụng \"" PF_NAME "\" cần phải đứng gần nhau" );
                return 1;		
	}        
	d = get_front_xy( get_x(who), get_y(who), get_x(me), get_y(me) );

	if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 1;    // 执行成功
	me->set_enemy_2(who);    // 远程目标锁定
        pf = 20;    // 抄自 /sys/user/fight

        if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
        {
	        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	}
       
        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x42, getoid(me), time2(), 1, 90, get_d(me), getoid(who) );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2",9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id() );
	
	hp = who->get_hp();
	CHAR_FIGHT_D->throwing_done( me, who, HIT_NONE, ADD_AP );
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,90);	

	if (who)
	{
		if (who->is_anti_effect()) return 2;
		damage = hp - who->get_hp();
		if (damage>0)
		{
			if (damage<8) damage = 8;
	        	if (get_effect(who, EFFECT_CHAR_BLOOD))
	        	{
	        		if (who->is_user() && who->get_save("char_blood")>damage/8) return 1;
	        		if (who->is_npc() && who->get("char_blood")>damage/8) return 1;
	        	}        	
	                user = get_scene_object_2(who, USER_TYPE);
	                set_effect_2(who, EFFECT_CHAR_BLOOD, 8, 2);
	                send_user( who, "%c%w%w%c", 0x81, 9022, get_effect_3(who, EFFECT_CHAR_BLOOD), EFFECT_BAD );
	                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9022, 1, EFFECT_BAD );
	                CHAR_CHAR_D->init_loop_perform(who);
	                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9022, 1, OVER_BODY, PF_LOOP );
	        	if (who->is_user()) who->set_save("char_blood", damage/8);
	        	else who->set("char_blood", damage/8);    			
		}
	}
	
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );      
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 10, 2, 20, 9, 0);
}

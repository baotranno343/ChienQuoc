
// 暗器技能  TIPS:[PF_THROWING]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0261
#define THIS_PERFORM    02610
#define PF_START       "02610"
#define PF_NAME        "Bạo Vũ Lê Hoa"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   5
#define SUB_MP          500

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 150\n Phóng ra 7 ám khí cực độc truy sát mục tiêu.", PF_NAME);
        result = sprintf(HIY" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Phóng ra 7 ám khí cực độc truy sát mục tiêu khiến mục tiêu Mù Loà trong 3 giây.", 
        	PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
        return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, act, pf;
        int level, mp, speed;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("02610")==0) return 1;
		
        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( me->get_weapon_code() != THROWING ) 
        {
                printf( ECHO "使用“" PF_NAME "”得装备暗器。" );
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
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
//                        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                        me->set_time( "pf", time() );

	                pf = 53;    // 抄自 /sys/user/fight

                	if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
                	{
		                pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	                }

                        me->to_front_xy(x, y);
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), 0 );

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 9);
                        //me->add_2("go_count.count2",9);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );
			send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        		me->set_perform( PF_START, time() );
                        return 1;
                }
        }
//        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        pf = 53;    // 抄自 /sys/user/fight

        if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
        {
	        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	}

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), getoid(who) );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        speed = 7 - me->get_sp()/60;
        if (speed<1) speed = 1;
        set_heart_count_2(me, speed);
        me->add_2("go_count.count2",speed);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object who;
        string arg;
        int z, x, y;
        int level, ap, ret;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
//              send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 26121, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

//	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 51143, 2, OVER_BODY, PF_ONCE );
//	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 5116, 1, OVER_BODY, PF_ONCE );
//	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 34829, 2, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 51141, 1, OVER_BODY, PF_ONCE );
//	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 4236, 2, OVER_BODY, PF_ONCE );
//	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 3637, 3, OVER_BODY, PF_ONCE );
    send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 32511, 1, OVER_BODY, PF_ONCE );
//	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 3292, 2, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 32521, 2, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                get_x(me), get_y(me), getoid(who), 51141, 1, OVER_BODY  );			

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,90);	

        ret += CHAR_FIGHT_D->throwing_done(me, who, HIT_THROWING);  if( !who ) return 2;    // 执行成功        
        ret += CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE); if( !who ) return 2;    // 执行成功 
		ret += CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE); if( !who ) return 2;    // 执行成功
		ret += CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE); if( !who ) return 2;    // 执行成功
		ret += CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE); if( !who ) return 2;    // 执行成功
		ret += CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE); if( !who ) return 2;    // 执行成功
		ret += CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE); if( !who ) return 2;    // 执行成功
//        if (who->is_anti_effect()) return 2;
//        if (who->get("anti_blind")) return 2;
        if (ret>0)
        {
                set_effect(who, EFFECT_CHAR_BLIND, 3);    // 小心准备 me
                send_user( who, "%c%w%w%c", 0x81, 9024, 6, EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9024, 1, EFFECT_BAD );
                send_user( who, "%c%c%c", 0x3d, 243, 1);    // 玩家失明
        	
        }
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        int level, interval, interval2;
        int speed;
        speed=7-me->get_sp()/60;
        if (speed<1) speed = 1;
		if (me->get_save("02610")==0) return;
        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = TIME_INTERVAL;    // 小心准备 me
        interval2 = interval - gone_time( me->get_perform(PF_START) );
        if( interval2 < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), interval, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), interval, interval2, PF_NAME );
	
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0,10, 1, 60, speed, 0);
}

int perform_action_npc(object me, object who)
{
        int x,y,z, act, pf;
        int level, mp, speed;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;



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
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
                        me->set_time( "pf", time() );

	                pf = 53;    // 抄自 /sys/user/fight

                	if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
                	{
		                pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	                }

                        me->to_front_xy(x, y);
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), 0 );

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 9);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        pf = 53;    // 抄自 /sys/user/fight

        if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
        {
	        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	}

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), getoid(who) );

        set_heart_state(me, MAGIC_STAT);
        speed = 7 - me->get_sp()/60;
        if (speed<1) speed = 1;
        set_heart_count_2(me, speed);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );

        return 1;
}

int cast_done_npc( object me )
{
        object who;
        string arg;
        int z, x, y;
        int level, ap, ret;
        me->set_perform( PF_START, time() );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 51141, 3, OVER_BODY, PF_ONCE );
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 36411, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,90);	

        ret = CHAR_FIGHT_D->throwing_done(me, who, HIT_THROWING);  if( !who ) return 2;    // 执行成功        
        ret += CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE); if( !who ) return 2;    // 执行成功        
        if (who->is_anti_effect()) return 2;
        if (who->get("anti_blind")) return 2;
        if (ret>0)
        {
                set_effect(who, EFFECT_CHAR_BLIND, 3);    // 小心准备 me
                send_user( who, "%c%w%w%c", 0x81, 9024, 6, EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9024, 1, EFFECT_BAD );
                send_user( who, "%c%c%c", 0x3d, 243, 1);    // 玩家失明
        	
        }
        return 2;    // 执行成功
}
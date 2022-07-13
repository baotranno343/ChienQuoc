
// 暗器技能  TIPS:[PF_THROWING]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0261
#define THIS_PERFORM    02616
#define PF_START       "02616"
#define PF_NAME        "Hấp Tinh Ma Châm"

#define SKILL_LEVEL     27
#define TIME_INTERVAL   2
#define SUB_MP          15 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/15 * 2
#define SUB_EFFECT      (10 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/15 * 15)

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 27\n Ám chiêu hút tinh lực của đối thủ, khi tấn công sẽ làm mục tiêu mất tổng cộng 100 điểm Pháp Lực trong 20 giây.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/15 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Ám chiêu hút tinh lực của đối thủ, khi tấn công sẽ làm mục tiêu mất tổng cộng %d điểm Pháp Lực trong 20 giây.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: "HIR "Cấp %d \n" NOR "    khi tấn công sẽ làm mục tiêu mất tổng cộng %d điểm Pháp Lực trong 20 giây.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, SUB_EFFECT*10, cur_level*15+SKILL_LEVEL, (SUB_EFFECT+15)*10);
        return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z, act, pf;
        int level, mp, speed;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( me->get_weapon_code() != THROWING ) 
        {
                printf( ECHO "Sử dụng \"" PF_NAME "\" phải trang bị ám khí" );
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

	                pf = 64;    // 抄自 /sys/user/fight

                	if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
                	{
		                pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	                }

                        me->to_front_xy(x, y);
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 40, get_d(me), 0 );

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 9);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }

//        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        pf = 64;    // 抄自 /sys/user/fight

        if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
        {
	        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	}

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 40, get_d(me), getoid(who) );

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
        int level, ret;
        int interval, sub_effect;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 26141, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 26161, 1, OVER_BODY, 26162, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        ret = CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE);    // 小心准备 me
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,60);	

        if (!who) return 2;
        if (who->is_anti_effect()) return 2;
	if (ret>0)
	{
		sub_effect = SUB_EFFECT;
                interval = 20;    // 小心准备 me                
                set_effect_2(who, EFFECT_02616, interval/2, 2);
                send_user( who, "%c%w%w%c", 0x81, 2616, get_effect_3(who, EFFECT_02616), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 2616, 1, EFFECT_BAD );
		who->set("02616", -sub_effect);    // 小心准备 me
                if( who->is_user() )
                {
                	who->set_save("02616", -sub_effect);  
                }		
	}
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
        
        int speed;
        speed=7-me->get_sp()/60;
        if (speed<1) speed = 1;

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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0,10,1, 40, speed, 0);
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        if( get_effect(me, EFFECT_02616) )
        {
        	if (me->is_npc())
                	return sprintf( PF_NAME "：\n　　每次减少%d点法力.\n", -me->get("02616") );
                else
                	return sprintf( PF_NAME "：\n　　每次减少%d点法力.\n", -me->get_save("02616") );
	}               
        else    return sprintf( PF_NAME "\n    持续减少法力." );
}

void into_effect( object me ) 
{
        int point;
        if (me->is_user()) point = me->get_save("02616");
        else point = me->get("02616");        
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w", 0x6d, getoid(me), -point );
        me->add_mp(point);
        if( !get_effect_3(me, EFFECT_02616) )    // 循环征状 set_effect_2
        {
	        if (me->is_user()) point = me->set_save("02616", 0);
	        me->set("02616", 0);
                send_user( me, "%c%w%w%c", 0x81, 2616, 0, EFFECT_BAD );
                send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 2616, 0, EFFECT_BAD );                
        }
}
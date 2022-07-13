
// 暗器技能  TIPS:[PF_THROWING_AREA]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0426
#define THIS_PERFORM    04262
#define PF_START       "04262"
#define PF_NAME        "Phong Vũ Phá Địch"

#define SKILL_LEVEL     40
#define TIME_INTERVAL   2
#define SUB_MP          50 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/40*20
#define ADD_AP          100 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/40*60
#define ADD_AP2          80 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/40*40

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 40\n Tuyệt kỹ phá địch với sức mạnh như vũ bão, tăng 100 ngoại công tấn công địch thủ ( đối với quái vật sẽ giảm 80 điểm ngoại kháng ).", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/40 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Tuyệt kỹ phá địch với sức mạnh như vũ bão, gia tăng %d ngoại công tấn công địch thủ ( đối với quái vật sẽ giảm %d điểm ngoại kháng ).\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Gia tăng %d ngoại công ( đối với quái vật sẽ giảm %d điểm ngoại kháng ).",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP, ADD_AP2, cur_level*40+SKILL_LEVEL, ADD_AP+60, ADD_AP2+40 );
	return result;
}

// 函数:命令处理
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
		if ( me->get_fam_name() != "Côn Luân" )
        {
                printf( ECHO "Phái Côn Luân mới có thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }
        if( me->get_weapon_code() != BLADE ) 
        {
                printf( ECHO "Sử dụng \"" PF_NAME "\" phải trang bị Đao pháp." );
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
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 0, get_d(me), 0 );

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
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 0, get_d(me), getoid(who) );

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

// 函数:法术处理
int cast_done( object me )
{
        object who, *user;
        string arg;
        int z, x, y;
        int level, ret;
        int interval, sub_effect, time;
        
        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
            //    send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 26141, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

//	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 26149, 1, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 23132, 2, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%d%w%w%d%w%c%c%w%c%c", 0x8a, getoid(me), time2(),
                get_x(me), get_y(me), getoid(who), 23132, 1, OVER_BODY  );        

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, ADD_AP);    // 小心准备 me
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,80);	

        if (!who) return 2;
        if (who->is_anti_effect()) return 2;
	if (ret>0)
	{
			if (get_effect_3(who, EFFECT_NO_CLOTH_0)) return 2;
                send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 23132, 1, OVER_BODY, PF_ONCE );    // 技能成功
                time = 5;
                set_effect(who, EFFECT_NO_CLOTH, time);  
                set_effect(who, EFFECT_NO_CLOTH_0, time+2);  
                CHAR_CHAR_D->init_loop_perform(who);
                send_user( who, "%c%w%w%c", 0x81, 2516, time, EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 2516, 1, EFFECT_BAD );
                if (who->is_user())
                {
                	USER_ENERGY_D->count_all_prop(who);
                }
                else
                {
                	who->set("04262", ADD_AP2);
                	who->add_dp(-(ADD_AP2*1));
                }       	                
	}
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数:能否使用特技
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
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0,10, 6, 64, speed, 0);
}
void into_effect( object me )
{
		send_user( me, "%c%w%w%c", 0x81, 2516, 0, EFFECT_BAD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 2516, 0, EFFECT_BAD );
		if (me->is_user())
		{
			CHAR_CHAR_D->init_loop_perform(me);
        	USER_ENERGY_D->count_all_prop(me);
        	send_user( me, "%c%w%w%c", 0x81, 2516, 0, EFFECT_BAD );
        }
        else
        {                	
                me->add_dp(me->get("04262"));       
                me->set("04262", 0); 	
        }
    //    send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 2516, 0, EFFECT_BAD );
        
}
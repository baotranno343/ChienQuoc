
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0414
#define THIS_PERFORM    04143
#define PF_START       "04143"
#define PF_TIME        "04143#"
#define PF_NAME        "Thực Giáp"

#define SKILL_LEVEL     5
#define TIME_INTERVAL   2
#define SUB_MP          ( 15 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 5 * 5 )
#define SUB_EFFECT      ( 40 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 5 * 10 )
#define SUB_EFFECT2      ( 40 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 5 * 5 )
#define ADD_INTERVAL    120

// 函数:获取符法效果
int get_cast_seal() { return 9103; }    // 符纸逆旋

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR" %s \n Võ công yêu cầu: Cấp 5\ Bùa chú ăn mòn hộ giáp, giảm 40 điểm Ngoại Kháng và giảm 40 điểm Nội Kháng của đối thủ. Hiệu quả duy trì liên tục trong 2 phút.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/5 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Bùa chú ăn mòn hộ giáp, giảm %d điểm Ngoại Kháng và giảm %d điểm Nội Kháng của đối thủ. Hiệu quả duy trì liên tục trong 2 phút.\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: " HIR "Cấp %d " NOR"\n giảm %d điểm Ngoại Kháng và giảm %d điểm Nội Kháng của đối thủ.",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, SUB_EFFECT, SUB_EFFECT2, cur_level*5+SKILL_LEVEL, SUB_EFFECT + 10, SUB_EFFECT2 + 5 );
	return result;
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
        if( get_effect(me, EFFECT_CHAR_ARMORFALL ) )
                return sprintf( PF_NAME ":\n　　Ngoại Kháng : %d điểm, \n    Nội Kháng : %d điểm.\n", me->get("pf.armorfall"), me->get("pf.armorfall2") );
        else    return sprintf( PF_NAME "\n" );
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user;
        int z;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
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
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
                        me->to_front_xy(x, y);
                        user = get_scene_object_2(me, USER_TYPE);
                        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
                        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 5);
                        me->add_2("go_count.count2",5);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );
			send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        		me->set_perform( PF_START, time() );
                        return 1;
                }
        }

        if( me == who )
        {
                printf( ECHO "Chính mình không thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }
        if( !who->can_be_fighted(me) || !me->can_fight(who) )
        {
                printf( ECHO "Chỉ đối với đối phương mới có thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }

        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
         me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        object who;
        string arg;
        int z, x, y;
        int level, ret, interval, sub_effect, flag=0;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                        41431, 1, OVER_BODY, 41432, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 
                41431, 1, OVER_BODY, 41432, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 以下为附加效果！

        if( get_effect(who, EFFECT_CHAR_HALFGOD) ) return 2;    // 处于神打状态下不成功
        level = me->get_skill(THIS_SKILL);
        sub_effect = SUB_EFFECT;
        if (-who->get("pf.armorfall")>sub_effect) return 2;
        if (get_effect_3(who, EFFECT_CHAR_POWERFALL)) flag += 1;
        if (get_effect_3(who, EFFECT_CHAR_FALL)) flag += 1;
        if (get_effect_3(who, EFFECT_MP_FALL)) flag += 1;
//        if (flag>=2) return 2;

	ret = CHAR_FIGHT_D->cast_done(me, who, 0, -100); 
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,90);	

	if (!who) return;
	if (who->is_anti_effect()) return 2;
	if (who->get("anti_curse")) return 2;
        if( ret > 0 )
        {                
                interval = ADD_INTERVAL;    // 小心准备 me                
		if( who->is_npc() )
		{
                	who->add_dp(-who->get("pf.armorfall"));
                	who->add_pp(-who->get("pf.armorfall2"));			
		}
                set_effect(who, EFFECT_CHAR_ARMORFALL, interval);
                send_user( who, "%c%w%w%c", 0x81, 4143, get_effect_3(who, EFFECT_CHAR_ARMORFALL), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 4143, 1, EFFECT_BAD );
		who->set("pf.armorfall", -sub_effect);    // 小心准备 me
		who->set("pf.armorfall2", -SUB_EFFECT2);    // 小心准备 me
                if( who->is_user() )
                {
                	who->set_save_2("pf.armorfall", -sub_effect);    // 小心准备 me
                	who->set_save_2("pf.armorfall2", -SUB_EFFECT2);
                        USER_ENERGY_D->count_pp(who);    // cp/pp 影响 ap/dp, 所以放前
                        USER_ENERGY_D->count_dp(who);
                }
                else
                {
                        level = who->get("pf.armorfall");
                        who->add_dp(level);
                        level = who->get("pf.armorfall2");
                        who->add_pp(level);
                        
                }

                // 效果见 energy_d.c
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

        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/5+1);
        interval = 2 - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 2, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 2, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 10, MAGIC_ACT_BEGIN, 0, 5, 0);
}

int perform_action_npc( object me, object who )
{
        object *user;
        int x,y,z;
        int level, mp;

        if( get_effect(me, EFFECT_CHAR_HALFGOD) )    // 同\"神打\"互斥
        {
                return 0;
        }

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 0;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                return 0;
        }

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 0;

                x = get_x(who);  y = get_y(who);
        }
        else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }
        else
        {
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 0;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {

                        me->to_front_xy(x, y);
                        user = get_scene_object_2(me, USER_TYPE);
                        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
                        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

                        me->add_mp(-mp);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 5);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }

        if( me == who )
        {
                return 0;
        }
        if( !who->can_be_fighted(me) || !me->can_fight(who) )
        {
                return 0;
        }
        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );

        return 1;
}

int cast_done_npc( object me )
{
        object who;
        string arg;
        int z, x, y;
        int level, rate, interval, sub_effect;

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                        41431, 1, OVER_BODY, 41432, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 
                41431, 1, OVER_BODY, 41432, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 以下为附加效果！
	if (who->is_anti_effect()) return 2;
	if (who->get("anti_curse")) return 2;
        if( get_effect(who, EFFECT_CHAR_ARMORFALL) ) return 2;    // 执行成功
        level = me->get_skill(THIS_SKILL);
        sub_effect = 30 + ((level-15)/5)*5*2;
        if (-who->get("pf.armorfall")>sub_effect) return 2;        

        rate = 40 * me->get_level() / range_value( who->get_level(), 1, MAX_NUMBER ) + me->get_lucky() - who->get_lucky();
        if( get_effect(me, EFFECT_CHAR_BLIND) ) rate /= 2;    // 失明(命中减半)

        if( random(100) < range_value(rate, 5, 80) )
        {
                interval = ADD_INTERVAL;    // 小心准备 me

                who->set("pf.armorfall", -sub_effect);    // 小心准备 me

                set_effect(who, EFFECT_CHAR_ARMORFALL, interval);
                send_user( who, "%c%w%w%c", 0x81, 4143, get_effect_3(who, EFFECT_CHAR_ARMORFALL), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 4143, 1, EFFECT_BAD );

                if( who->is_user() )
                {
                	who->set_save_2("pf.armorfall", -sub_effect);
                        USER_ENERGY_D->count_pp(who);    // cp/pp 影响 ap/dp, 所以放前
                        USER_ENERGY_D->count_dp(who);
                }
                else
                {
                        level = who->get("pf.armorfall");
                        who->add_pp(level);
                        who->add_dp(level);
                }

                // 效果见 energy_d.c
        }
        return 2;    // 执行成功
}

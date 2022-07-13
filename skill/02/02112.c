
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0211
#define THIS_PERFORM    02112
#define PF_START       "02112"
#define PF_NAME        "Thốn Kình"

#define SKILL_LEVEL     12
#define TIME_INTERVAL   2
#define SUB_MP        	0
#define SUB_YUAN        2
#define ADD_AP          10 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 10 * 2
#define ADD_ENMITY	280 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/10*110 + ret

// 函数:获取法力
int get_sub_mp( object me )
{
        int level = me->get_skill(THIS_SKILL);
        return SUB_MP;
}

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 12 cấp\n    Ám kình phát qua quyền thủ có thể công phá lục phũ ngũ tạng khiến cho đối phương bị Trọng Thương.";
        cur_level = (level - SKILL_LEVEL)/10 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Ám kình phát qua quyền thủ có thể công phá lục phũ ngũ tạng khiến cho đối phương bị Trọng Thương trong %d giây.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Làm đối thủ trọng thương trong %d giây.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP, cur_level*10+SKILL_LEVEL, ADD_AP + 2, );
        return result;        	
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

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

        if( me->get_weapon_code() != UNARMED )
        {
                printf( ECHO "Sử dụng \"" PF_NAME "\" phải trang bị triển thủ" );
                return 1;
        }
	if( !CHAR_FIGHT_D->attack_action(me, who, 1020) ) return 1;
	me->add_yuan( -SUB_YUAN );
	set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2", 5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s", who->get_char_id() ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );	

        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_LOOP );

        return 1;
}

// 函数:特殊技处理(动作)
int perform_action( object me, object who )
{
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

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

        if( me->get_weapon_code() != UNARMED )
        {
                printf( ECHO "Sử dụng \"" PF_NAME "\" phải trang bị triển thủ" );
                return 1;
        }

        if( !CHAR_FIGHT_D->attack_action(me, who, 1020) ) return 1;

        me->add_mp(-mp);
        me->add_yuan( -SUB_YUAN );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 2;    // 执行成功
}

// 函数:特殊技处理
int perform_done( object me, object who )
{
        object *user;
        int level, mp, rate, ret, time;        

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

//      if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

/*      if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }       */

/*      if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }       */

        if( me->get_weapon_code() != UNARMED )
        {
                printf( ECHO "Sử dụng \"" PF_NAME "\" phải trang bị triển thủ" );
                return 1;
        }

        me->set_perform_file(0);
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP );    // 删除聚气
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21121, 1, OVER_BODY, PF_ONCE );    // 

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0);    // 小心准备 me

        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,ADD_ENMITY);

        if( !ret ) return 2;    // 执行成功
	if (!who) return 2;
        if( get_effect(who, EFFECT_CHAR_9145) ) return 2;    // 执行成功
        if (who->is_anti_effect()) return 2;
        if (who->get("anti_wound")) return 2;
        time = ADD_AP;
        if (get_effect(who, EFFECT_CHAR_WOUND)<time)
        {   	
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_WOUND, time);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user( who, "%c%w%w%c", 0x81, 9020, get_effect_3(who, EFFECT_CHAR_WOUND), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9020, 1, EFFECT_BAD );
                CHAR_CHAR_D->init_loop_perform(who);
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9020, 1, OVER_BODY, PF_LOOP );
		if (who->is_user())
		{
	                USER_ENERGY_D->count_ap(who);
        	        USER_ENERGY_D->count_dp(who);
		}
        }

        return 2;    // 执行成功
}

// 函数:特殊技处理
int cast_done( object me )
{
        object *user;
        int level, mp, rate, ret, time;        
        object who;
        string arg;             

	if( !stringp( arg = me->get_cast_arg() ) ) return 1;
	if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP );    // 删除聚气
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21121, 1, OVER_BODY, PF_ONCE );    // 

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0);    // 小心准备 me

        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,ADD_ENMITY);

        if( !ret ) return 2;    // 执行成功
	if (!who) return 2;
        if( get_effect(who, EFFECT_CHAR_9145) ) return 2;    // 执行成功
        if (who->is_anti_effect()) return 2;
        if (who->get("anti_wound")) return 2;
        time = ADD_AP;
        if (get_effect(who, EFFECT_CHAR_WOUND)<time)
        {   	
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_WOUND, time);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user( who, "%c%w%w%c", 0x81, 9020, get_effect_3(who, EFFECT_CHAR_WOUND), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9020, 1, EFFECT_BAD );
                CHAR_CHAR_D->init_loop_perform(who);
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9020, 1, OVER_BODY, PF_LOOP );
		if (who->is_user())
		{
	                USER_ENERGY_D->count_ap(who);
        	        USER_ENERGY_D->count_dp(who);
		}
        }

        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_CHAR; }


// 函数:能否Sử dụng 特技
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
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
        send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 1, 10, 5, 0);
}

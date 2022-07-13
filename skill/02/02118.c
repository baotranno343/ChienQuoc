
// 法术  TIPS:[PF_SELF_AREA]  变异

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <action.h>

#define THIS_SKILL      0211
#define THIS_PERFORM    02118
#define PF_START       "02118"
#define PF_NAME        "Đại Hải Vô Lượng"

#define SKILL_LEVEL     40
#define TIME_INTERVAL   3
#define SUB_MP        	0
#define SUB_YUAN        3

#define ADD_ENMITY	360 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/10*250 + ret
#define ADD_AP		(60 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/16*20)

// 函数:获取描述
string get_desc( object me )
{	
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 40 cấp\n    Nguyên khí bạo kình phát tán, tăng thêm 60 điểm sát thương và làm Choáng tất cả mục tiêu xung quanh trong 2 giây.";
        cur_level = (level - SKILL_LEVEL)/16 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Nguyên khí bạo kình phát tán, tăng thêm %d điểm sát thương và làm Choáng tất cả mục tiêu xung quanh trong 2 giây.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng thêm %d điểm sát thương.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP, cur_level*16+SKILL_LEVEL, ADD_AP+20 );
	return result;   	
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp;
        object *char, *user;
        int z, i, size, ret;

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

	if (me->get_gender()==2) send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 80, get_d(me), 0 );    // 9: 施法动作
	else send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 60, get_d(me), 0 );    // 9: 施法动作

        me->add_mp(-mp);
        me->add_yuan( -SUB_YUAN );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        
        level = me->get_level();

//        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me), 
//                21181, 1, OVER_BODY, 21182, 1, UNDER_FOOT, PF_ONCE );

//      if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        char = get_range_object(z, x, y, 4, USER_TYPE) + get_range_object(z, x, y, 4, CHAR_TYPE) - ({ me });

        for( i = 0, size = sizeof(char); i < size; i ++ ) 
                if( who = char[i] ) 
                {
                	if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;
//                	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21181, 1, OVER_BODY, PF_ONCE );    // 技能成功
                	ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, ADD_AP, 0, 0, 0, 2);

		        if ( who && !who->is_die() )
		        	CHAR_FIGHT_D->set_enmity(me,who,ADD_ENMITY);
        	
		        if (ret >0)
		        {
		        	if (!who) continue;
		        	if (who->is_anti_effect())continue;
        			if (who->get("anti_faint")) continue;
			        if(     get_effect(who, EFFECT_CHAR_FAINT)
			        ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) continue;    // 执行成功
			        if (who->get_perform("02222#")) continue;
		                user = get_scene_object_2(who, USER_TYPE);
		                set_effect(who, EFFECT_CHAR_FAINT, 2);    // 小心准备 me
		                CHAR_CHAR_D->init_loop_perform(who);
		                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
		                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
		                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
		                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );	        
		        }                	
                }
        
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);        
        me->add_2("go_count.count2", 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%d", level ) );        

        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        object *char, who;
        string arg;
        int level, mp;
        int z, x, y, i, size;
/*
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        level = to_int(arg);

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me), 
                21181, 1, OVER_BODY, 21182, 1, UNDER_FOOT, PF_ONCE );

//      if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        char = get_range_object(z, x, y, 2, USER_TYPE) + get_range_object(z, x, y, 2, CHAR_TYPE) - ({ me });

        for( i = 0, size = sizeof(char); i < size; i ++ ) 
                if( who = char[i] ) CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0, 0, 0, 0, 2);

        set_effect(me, EFFECT_CHAR_FREEZE, 1);
*/
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

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
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/16+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
        if( me->get_gender()==1)
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 1, 60, 9, 0);
        else
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 1, 80, 9, 0);                
}

int perform_action_npc( object me, object who )
{
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 0;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                return 0;
        }
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%d", level ) );

        return 1;
}

int cast_done_npc( object me )
{
        object *char, who;
        string arg;
        int level, mp;
        int z, x, y, i, size, ret;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        level = to_int(arg);

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me), 
                21181, 1, OVER_BODY, 21182, 1, UNDER_FOOT, PF_ONCE );

//      if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        char = get_range_object(z, x, y, 10, USER_TYPE) + get_range_object(z, x, y, 10, CHAR_TYPE) - ({ me });

        for( i = 0, size = sizeof(char); i < size; i ++ ) 
                if( who = char[i] ) 
                {
                	ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0, 0, 0, 0, 2);
		        if ( who && !who->is_die() )
		        	CHAR_FIGHT_D->set_enmity(me,who,ADD_ENMITY);
                }

        return 2;    // 执行成功
}
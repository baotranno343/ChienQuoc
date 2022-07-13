
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0251
#define THIS_PERFORM    02518
#define PF_START       "02518"
#define PF_TIME        "02518#"
#define PF_NAME        "Bá Khí Phong Thuật"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   40
#define SUB_MP        	0
#define SUB_YUAN        2
#define ADD_AP          10 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/150

#define ADD_ENMITY	480 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/150*120 + ret

int perform_done( object me, object who );

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
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 150 cấp\n    Sử dụng ngoại công hùng mạnh tạo ra 1 trận pháp yêu thuật ngăn cản đối thủ chạy trốn.";
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Sử dụng ngoại công hùng mạnh tạo ra 1 trận pháp yêu thuật ngăn cản đối thủ chạy trốn trong %d giây.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Sử dụng ngoại công hùng mạnh tạo ra 1 trận pháp yêu thuật ngăn cản đối thủ chạy trốn trong %d giây.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_AP, cur_level*150+SKILL_LEVEL, ADD_AP + 1 );
	return result;        	
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("02518")==0) return 1;
		
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

        if( me->get_weapon_code() == UNARMED ) 
        {
                printf( ECHO "Sử dụng \" %s \" phải trang bị binh khí.", PF_NAME );
                return 1;
        }
        me->add_yuan( -SUB_YUAN );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
	if (me->get_gender()==2) send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 50, get_d(me), 0 );    // 9: 施法动作
	else send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 50, get_d(me), 0 );    // 9: 施法动作        
        perform_done(me, 0);
        return 1;
}


// 函数:特殊技处理
int perform_done( object me, object who )
{
        int z, x, y, i, size;
        int level, mp, interval, ret, flag;    
        object * char;    
	flag = 0;
        me->set_perform_file(0);
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP );    // 删除聚气
        z = get_z(me), x = get_x(me), y = get_y(me);
        char = get_range_object(z, x, y, 5, USER_TYPE) + get_range_object(z, x, y, 5, CHAR_TYPE) - ({ me });
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2", 5);        
        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] ) 
        {
                if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;        
        	ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0);    // 小心准备 me
			ret += CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0);    // 小心准备 me
//			ret += CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0);    // 小心准备 me
//			ret += CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 0);    // 小心准备 me

	        if ( who && !who->is_die() )
        		CHAR_FIGHT_D->set_enmity(me,who,ADD_ENMITY);
	        if( !who ) continue;
		if (who->is_anti_effect()) continue;
        	if( get_effect(who, EFFECT_CHAR_CHAN) ) continue;    // 执行成功

        	if( get_effect(who, EFFECT_CHAR_9145) ) continue;    // 执行成功
        
//        	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21153, 1, OVER_BODY, PF_ONCE );    // 
	        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 51141, 1, OVER_BODY, PF_ONCE );    //
			if( ret>0 ) 
	        {	                
	                who->set_save( "pf.chan", sprintf( "%d:(%d,%d)", z, x, y ) );
	                interval = ADD_AP;    // 小心准备 level
	                set_effect(who, EFFECT_CHAR_CHAN, interval);	
			if (flag==0)
//	                	send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
//	                        	21151, interval, OVER_TILE, 21152, interval, OVER_TILE, PF_ONCE );
						send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
	                        	51141, interval, OVER_TILE, 3642, interval, OVER_TILE, PF_ONCE );		
			flag = 1;	                        
	        }
	}
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
		if (me->get_save("02518")==0) return;
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
        if( me->get_gender()==1)
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 2, 50, 5, 0);
        else
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 1, 50, 5, 0);                
}

int perform_action_npc( object me, object who )
{
        if( !CHAR_FIGHT_D->attack_action(me, who, 15) ) return 0;

        set_heart_state(me, FIGHT_STAT);
        set_heart_count_2(me, 7);
        me->set_perform_file(__FILE__);
        
        return 1;
}

int perform_done_npc( object me, object who )
{
        int z, x, y;
        int level, mp, interval, ret;
        
        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        me->set_perform_file(0);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP );    // 删除聚气

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, ADD_AP);    // 小心准备 me

        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,90);

        if( !who ) return 2;    // 执行成功
	if (who->is_anti_effect()) return 2;
        if( get_effect(who, EFFECT_CHAR_CHAN) ) return 2;    // 执行成功

        if( get_effect(who, EFFECT_CHAR_9145) ) return 2;    // 执行成功

        if( ret>0 ) 
        {
                z = get_z(who);  x = get_x(who);  y = get_y(who);
                who->set_save( "pf.chan", sprintf( "%d:(%d,%d)", z, x, y ) );

                interval = 8;    // 小心准备 level
                set_effect(who, EFFECT_CHAR_CHAN, interval);

                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                        21151, interval, OVER_TILE, 21152, interval, OVER_TILE, PF_ONCE );
        }

        return 2;    // 执行成功
}

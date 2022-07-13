
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0251
#define THIS_PERFORM    02512
#define PF_START       "02512"
#define PF_NAME        "Đại Hải Cuồng Đào"

#define SKILL_LEVEL     29
#define TIME_INTERVAL   20 - (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/9 
#define SUB_MP          0
#define SUB_YUAN        4
#define ADD_DAMAGE      20 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/9*5

// 函数：获取法力
int get_sub_mp( object me ) 
{ 
        int level = me->get_skill(THIS_SKILL);
        return SUB_MP; 
}

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR" %s \n Võ công yêu cầu: Cấp 29\n Côn thức mạnh mẽ bất tận như biển to sóng dữ, tăng thêm 20 điểm Ngoại Công khi tấn công và làm đối thủ Choáng trong 3 giây.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/9 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Côn thức mạnh mẽ bất tận như biển to sóng dữ, tăng thêm %d điểm Ngoại Công khi tấn công và làm đối thủ Choáng trong 3 giây.\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: " HIR "Cấp %d " NOR"\n Tăng thêm %d điểm Ngoại Công khi tấn công, đồng thời giảm thời gian tái sử dụng xuống %d giây.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL, ADD_DAMAGE, cur_level*9+SKILL_LEVEL, ADD_DAMAGE + 5, TIME_INTERVAL - 1 );
        return result;	
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
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
	if( !CHAR_FIGHT_D->attack_action(me, who, 1020) ) return 1;
	me->add_yuan( -SUB_YUAN );
	set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
          me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s", who->get_char_id() ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );	
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_LOOP );

        return 1;
}

// 函数：特殊技处理(动作)
int perform_action( object me, object who )
{
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
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

        if( !CHAR_FIGHT_D->attack_action(me, who, 1020) ) return 1;

        me->add_mp(-mp);
        me->add_yuan( -SUB_YUAN );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 2;    // 执行成功
}

// 函数：特殊技处理
int perform_done( object me, object who )
{
        int z, x, y, d, p;
        int level, mp, ret;
	object * user;        

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

//      if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 me

/*      if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }       */

/*      if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }       */

        if( me->get_weapon_code() == UNARMED ) 
        {
                printf( ECHO "Sử dụng \" %s \" phải trang bị binh khí.", PF_NAME );
                return 1;
        }

        me->set_perform_file(0);
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP );    // 删除聚气
	me->set("add_damage", ADD_DAMAGE);
        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_STICK);    // 小心准备 me
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,90);	

        me->set("add_damage", 0);
        if( !who ) return 2;    // 执行成功
        if (who->is_anti_effect()) return 2;
        if (who->get("anti_faint")) return 2;
        if (ret >0)
        {
	        if(     get_effect(who, EFFECT_CHAR_FAINT)
	        ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) return 1;    // 执行成功
	        if (who->get_perform("02222")) return 1;
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT, 3);    // 小心准备 me
                CHAR_CHAR_D->init_loop_perform(who);
                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );	        
        }
        return 2;    // 执行成功
}

// 函数：特殊技处理
int cast_done( object me )
{
        int z, x, y, d, p;
        int level, mp, ret;
	object * user;        
        string arg;     
        object who;

	if( !stringp( arg = me->get_cast_arg() ) ) return 1;
	if( !objectp( who = find_char(arg) ) ) return 1;
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP );    // 删除聚气
	me->set("add_damage", ADD_DAMAGE);
        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_STICK);    // 小心准备 me
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,90);	

        me->set("add_damage", 0);
        if( !who ) return 2;    // 执行成功
        if (who->is_anti_effect()) return 2;
        if (who->get("anti_faint")) return 2;
        if (ret >0)
        {
	        if(     get_effect(who, EFFECT_CHAR_FAINT)
	        ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) return 1;    // 执行成功
	        if (who->get_perform("02222#")) return 1;
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT, 3);    // 小心准备 me
                CHAR_CHAR_D->init_loop_perform(who);
                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );	        
        }
        return 2;    // 执行成功
}

// 函数：命令处理(动作)
int perform_action_npc( object me, object who )
{
        if( !CHAR_FIGHT_D->attack_action(me, who, 22) ) return 0;

        set_heart_state(me, FIGHT_STAT);
        set_heart_count_2(me, 7);
        me->set_perform_file(__FILE__);

        return 1;    // 执行成功
}

// 函数：命令处理
int perform_done_npc( object me, object who )
{
        int z, x, y, d, p;
        int level, ret;
	object * user;
        me->set_perform_file(0);

        level = me->get_skill(THIS_SKILL);

        ret = CHAR_FIGHT_D->attack_done(me, who, HIT_STICK );    // 小心准备 me
        if ( who && !who->is_die() )
        	CHAR_FIGHT_D->set_enmity(me,who,90);	

        if( !who ) return 1;    // 执行成功

        if (ret >0)
        {
	        if(     get_effect(who, EFFECT_CHAR_FAINT)
	        ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) return 2;    // 执行成功
	        if (who->get_perform("02222#")) return 2;
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT, 3);    // 小心准备 me
                CHAR_CHAR_D->init_loop_perform(who);
                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );	        
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

        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/9+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
				send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 1, 20, 5, 0);
}

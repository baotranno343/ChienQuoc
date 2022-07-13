
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0329
#define THIS_PERFORM    03292
#define PF_START       "03292"
#define PF_TIME        "03292#"
#define PF_NAME        "Đại Chu Thiên"

#define SKILL_LEVEL     15
#define TIME_INTERVAL   2
#define SUB_MP          40 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/11*40
#define ADD_AP		30 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/11*22

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 15 cấp\n    Đại thừa chu thiên pháp chú có khả năng tăng cao Ngoại Kháng và Nội Kháng của bản thân và toàn Nhóm trong 60 phút\n";
        cur_level = (level - SKILL_LEVEL)/11 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Vật phẩm tiêu hao： Chu Thiên Tâm Pháp\n    Đại thừa chu thiên pháp chú có khả năng tăng cao %d Ngoại Kháng và Nội Kháng của bản thân và toàn Nhóm trong 60 phút.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Đại thừa chu thiên pháp chú có khả năng tăng cao %d Ngoại Kháng và Nội Kháng của bản thân và toàn Nhóm trong 60 phút.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_AP, cur_level*11+SKILL_LEVEL, ADD_AP+35 );
	return result;  
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, interval, mp, z, add, level2;
        object *user, item, owner;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        interval = TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;    // 小心准备 level

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) 
        {
        	notify( "Bạn bị trạng thái phong ấn" );
        	return 1;
        }        
        if (!who) return 1;
        if (who!=me)
        {
        	if (who->is_user())
        	{
	        	if (!me->get_leader()||me->get_leader()!=who->get_leader())
		        {
		                printf( ECHO "Chính mình hoặc đồng đội mới có thể sử dụng " PF_NAME );
		                return 1;
		        }
		}
		else
		{
			owner  = who->get_owner();
			if (owner!=me)
			{
		        	if (!owner || !me->get_leader()||me->get_leader()!=owner->get_leader())
			        {
			                printf( ECHO "Chính mình hoặc đồng đội mới có thể sử dụng " PF_NAME );
			                return 1;
			        }
			}			       			
		}	
		if ("/sys/user/attack"->can_use_help(me, who)==0)
		{				
			printf( ECHO "Đối với đối phương không thể sử dụng " PF_NAME );
			return 1;				
		}			      
        }      
        if( !objectp( item = present("Chu Thiên Tâm Pháp", me, 1, MAX_CARRY*4) ) )
        {
                printf( ECHO "Phải có Chu Thiên Tâm Pháp mới có thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }       
        if (who->is_anti_effect()) return 2;
        item->add_amount(-1); 
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d", who->get_char_id(), level ) );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
	return 1;
}      

// 函数：法术处理
int cast_done( object me )
{  
        int level, interval, mp, z, add, level2;
        object *user, who;	
        string arg;
        interval = 3600;
        if( !stringp( arg = me->get_cast_arg() ) ) return 2;
        if( sscanf(arg, "%s,%d", arg, level) != 2 ) return 2;
        if( !objectp( who = find_char(arg) ) ) return 2;        
        if (!who) return 2;
        	
        CHAR_FIGHT_D->set_enmity2(me,who,30);
            
        me->set_perform( PF_TIME, interval );        
        
        level2 = who->get_level();
        if ( level > level2+15) add = ADD_AP - (level-level2-15)/11*22;
        else add = ADD_AP;        
	user = get_scene_object_2(who, USER_TYPE);
//	if (add >= who->get_save("03291#") && add >= who->get("03291#"))
	{
		set_effect(who, EFFECT_USER_DP, interval);
		send_user( who, "%c%w%w%c", 0x81, 3291, get_effect_3(who, EFFECT_USER_DP), EFFECT_GOOD );
		send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 3291, 1, EFFECT_GOOD );
		
		if (who->is_user()) 
		{
			who->set_save("03291#", add);
			USER_ENERGY_D->count_dp(who);
		}
		else
		{
			who->add_dp(-who->get("03291#"));
			who->set("03291#", add);
			who->add_dp(add);
		}
	}
//	if (add >= who->get_save("03292#") && add >= who->get_save("03292#"))
	{
		set_effect(who, EFFECT_USER_PP, interval);
		send_user( who, "%c%w%w%c", 0x81, 3292, get_effect_3(who, EFFECT_USER_PP), EFFECT_GOOD );
		send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 3292, 1, EFFECT_GOOD );
		
		if (who->is_user()) 
		{
			who->set_save("03292#", add);
			USER_ENERGY_D->count_pp(who);
		}
		else
		{
			who->add_pp(-who->get("03292#"));
			who->set("03292#", add);
			who->add_pp(add);			
		}
	}
	send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 3292, 1, OVER_BODY, PF_ONCE );		 
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
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 1, 1, MAGIC_ACT_BEGIN, 0, 5, "Chu Thiên Tâm Pháp");
}

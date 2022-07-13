
// 多体远程技能  TIPS:[PF_CAST_AREA]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0425
#define THIS_PERFORM    04257
#define PF_START       "04257"
#define PF_TIME        "04257#"
#define PF_NAME        "Càn Khôn Linh Quái Tâm Pháp"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   2
#define SUB_MP          ( 200 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 2 )
#define ADD_EFFECT      ( 200000 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 200000 )

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 150 cấp\n    Tâm Pháp Cao Cấp Côn Luân,Gia tăng 200 ngàn Khí Huyết cho bản thân hoặc đồng đội";
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Tâm Pháp Cao Cấp Côn Luân,Gia tăng %d Khí Huyết cho bản thân hoặc đồng đội。\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tâm Pháp Cao Cấp Côn Luân,Gia tăng %d Khí Huyết cho bản thân hoặc đồng đội。",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_EFFECT, cur_level*150+SKILL_LEVEL, ADD_EFFECT+300 );
	return result;
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        if( get_effect(me, EFFECT_CHAR_POWERUP3) )
                return sprintf( PF_NAME "：\n　　Gia tăng %d Khí Huyết。\n", me->get("05014")+me->get_save("05014") );
        else    return sprintf( PF_NAME "\n" );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z;
        int level, mp;
	object owner;
        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("04257")==0) return 1;
        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;
	        if (who!=me)
	        {
	        	if (who->is_user())
	        	{
		        	if (!me->get_leader()||me->get_leader()!=who->get_leader())
			        {
			                printf( ECHO "只能对自己或者队友使用" PF_NAME );
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
				                printf( ECHO "只能对自己或者队友使用" PF_NAME );
				                return 1;
				        }
				}			       			
			}		    
			if ("/sys/user/attack"->can_use_help(me, who)==0)
			{				
				printf( ECHO "你无法对对方使用" PF_NAME );
				return 1;				
			}			  
	        }
                z = get_z(who);  x = get_x(who);  y = get_y(who);
        }
        else
        {
                return 1;
        }
	if (who->is_anti_effect()) return 1;

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg(who->get_char_id());
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object *char, who;
        string arg;
        int z, x, y;
        int level, level2, interval, effect, i, size, hp;        

        if( !stringp( arg = me->get_cast_arg() ) || !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 5014, 1, OVER_BODY, PF_ONCE );

        level = me->get_skill(THIS_SKILL);
        interval = 3600;    // 小心准备 me
        effect = ADD_EFFECT;    // 小心准备 me
        level2 = who->get_level();
        if (level - 20 - level2>0) effect = effect - (level - 20 - level2)/10*40;
	
        if( get_effect(who, EFFECT_CHAR_POWERUP3) )
        {
        	if (who->is_user() && who->get_save("05014")>effect) return 1;
        	if (who->is_npc() && who->get("05014")>effect) return 1;
        }
        set_effect(who, EFFECT_CHAR_POWERUP3, interval);
        if (who->is_user() )
        {
		who->set_save("05014", effect);
		USER_ENERGY_D->count_max_hp(who);
	}
	else
        {
        	hp = who->get_hp();
        	who->add_max_hp(-who->get("05014"));
		who->set("05014", effect);
		who->add_max_hp(effect);
		who->set_hp(hp);
	}	                
        send_user( who, "%c%w%w%c", 0x81, 5014, get_effect_3(who, EFFECT_CHAR_POWERUP3), EFFECT_GOOD );
        send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 5014, 1, EFFECT_GOOD );
	CHAR_FIGHT_D->set_enmity2(me,who,40);

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
		if (me->get_save("04257")==0) return;
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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0,10, MAGIC_ACT_BEGIN, 0, 5, 0);
}

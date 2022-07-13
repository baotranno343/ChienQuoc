
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <action.h>

#define THIS_SKILL      0212
#define THIS_PERFORM    02123
#define PF_START       "02123"
#define PF_NAME        "Lạc Kích"

#define SKILL_LEVEL     16
#define TIME_INTERVAL   2
#define SUB_MP        	0
#define SUB_YUAN        2
#define ADD_AP          0

#define ADD_ENMITY	480 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/40*300 + ret

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

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
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 16 cấp\n    Chiêu thức cận chiến với đòn thế vũ bão, gây sát thương đồng thời làm đối thủ giảm 10%% phòng thủ trong 20 giây.";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Chiêu thức cận chiến với đòn thế vũ bão, gây sát thương đồng thời làm đối thủ giảm 10%% phòng thủ trong 20 giây.", 
        	PF_NAME, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL);
        return result;	
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
        return "Lạc Kích:Giảm 10%% phòng thủ.\n";
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp,enmity;
        object *user;
        int ret;

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

        me->add_mp(-mp);
        me->add_yuan( -SUB_YUAN );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        if (me->get_gender()==2)
        {
        	if( !CHAR_FIGHT_D->attack_action(me, who, 3100) ) return 1;        
        }
        else
        {
        	if( !CHAR_FIGHT_D->attack_action(me, who, 1100) ) return 1;        
        }        
        ret = CHAR_FIGHT_D->attack_done(me, who);        
        if ( who && !who->is_die() )
        {
        	enmity = ADD_ENMITY ;
        	CHAR_FIGHT_D->set_enmity(me,who,enmity);
        }

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);  
         me->add_2("go_count.count2",9);      
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%d", level ) );           
        if (!who) return 1;
        if (who->is_anti_effect()) return 2;
        if( get_effect(who, EFFECT_2123_ARMORFALL) ) return 1; 
        if (ret>0)
        {
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_2123_ARMORFALL, 20);
                CHAR_CHAR_D->init_loop_perform(who);
                send_user( who, "%c%w%w%c", 0x81, 2123, 20, EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 2123, 1, EFFECT_BAD );                
		if (who->is_user())
		{
        	        USER_ENERGY_D->count_dp(who);
		}        	
        }             

        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数:能否使用特技
void can_perform( object me )
{
        int interval;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, PF_NAME );
	if( me->get_gender()==1)
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 1, 0, 9, 0);
        else
        	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, SUB_YUAN, 1, 3, 0, 9, 0);
}

void effect_done( object me )
{
	if (me->is_user()) USER_ENERGY_D->count_dp(me);
	CHAR_CHAR_D->init_loop_perform(me);
        send_user( me, "%c%w%w%c", 0x81, 2123, 0, EFFECT_BAD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 2123, 0, EFFECT_BAD );        
				
}
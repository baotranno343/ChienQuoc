
// 单体远程技能  TIPS:[PF_CAST]
#include <effect.h>
#include <ansi.h>
#include <skill.h>
#include <action.h>

#define THIS_SKILL      0501
#define THIS_PERFORM    05013
#define PF_START       "05013"
#define PF_NAME        "Tẩy Trần Quyết"

#define SKILL_LEVEL     16
#define TIME_INTERVAL   2
#define SUB_MP          25


// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 16 cấp\n    Đạo thuật hóa giải bùa chú nguyền rủa đã mắc phải trên bản thân hoặc đồng đội";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Đạo thuật hóa giải bùa chú nguyền rủa đã mắc phải trên bản thân hoặc đồng đội", 
        	PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
        return result;	
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int z;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
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
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

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
	if ("/sys/user/attack"->can_use_help(me, who)==0)
	{				
		printf( ECHO "Đối với đối phương thể sử dụng " PF_NAME );
		return 1;				
	} 

        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        me->add_mp(-mp);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id() );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object who, owner;
        string arg;
        int z, x, y;
	int i, size, time, pos, *all;
	int * allbad = ({ EFFECT_CHAR_BLOOD, EFFECT_USER_BURN, EFFECT_CHAR_LAZY, EFFECT_CHAR_SLOW, EFFECT_CHAR_NO_MOVE, EFFECT_CHAR_CHAOS, EFFECT_CHAR_BLIND, EFFECT_NO_WEAPON, EFFECT_2123_ARMORFALL, EFFECT_02614, EFFECT_CHAR_FAINT, EFFECT_02616, EFFECT_CHAR_ARMORFALL, EFFECT_CHAR_POWERFALL, EFFECT_CHAR_FALL, EFFECT_SLEEP, EFFECT_MP_FALL, });
	int * allgood = ({ EFFECT_CHAR_ADD_DP, EFFECT_EXCITE, EFFECT_REBOUND, EFFECT_USER_DP, EFFECT_USER_SP, EFFECT_DODGE, EFFECT_03484, EFFECT_CHAR_MOVE, EFFECT_CHAR_HALFGOD2, EFFECT_CHAR_POWERUP,  EFFECT_CHAR_POWERUP2, EFFECT_CHAR_POWERUP3, EFFECT_CHAR_NO_PF_0, });        
        
        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 53121, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( !objectp( who = find_char(arg) ) ) return 1;
        if( !who->can_be_fighted(me) || !me->can_fight(who) )
        	all = allbad;
        else
        	all = allgood;
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 53121, 1, OVER_BODY, PF_ONCE );
	size = sizeof(all);
	time = 0; pos = -1;
	for (i =0;i<size;i++) if (time < get_effect_3(who, all[i])) 
	{
		time = get_effect_3(who, all[i]);
		pos = i;
	}
        if (pos!=-1)
        {
        	if (all[pos]<192) set_effect(who, all[pos], 1);
        	else set_effect_2(who, all[pos], 1, 1);
        }
	CHAR_FIGHT_D->set_enmity2(me,who,80);
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0,10, MAGIC_ACT_BEGIN, 0, 5, 0);
}

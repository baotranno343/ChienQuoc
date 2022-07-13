
// 自用持续技能  TIPS:[PF_SELF]
#include <effect.h>
#include <ansi.h>
#include <skill.h>
#include <action.h>

#define THIS_SKILL      0325
#define THIS_PERFORM    03253
#define PF_START       "03253"
#define PF_NAME        "Định Tâm Quyết"

#define SKILL_LEVEL     10
#define TIME_INTERVAL   2
#define SUB_MP          35


// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 10 cấp\n    Hóa giải lập tức 1 trạng thái bất thường trên bản thân.";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Hóa giải lập tức 1 trạng thái bất thường trên bản thân.", 
        	PF_NAME, SKILL_LEVEL, SUB_MP, TIME_INTERVAL);
        return result;	
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp;
	int i, size, time, pos;
        int * all = ({ EFFECT_CHAR_BLOOD, EFFECT_USER_BURN, EFFECT_CHAR_LAZY, EFFECT_CHAR_SLOW, EFFECT_CHAR_NO_MOVE, EFFECT_CHAR_CHAOS, EFFECT_CHAR_BLIND, EFFECT_NO_WEAPON, EFFECT_2123_ARMORFALL, EFFECT_02614, EFFECT_02616, EFFECT_CHAR_ARMORFALL, EFFECT_CHAR_POWERFALL, EFFECT_SLEEP, EFFECT_CHAR_FALL, EFFECT_MP_FALL, });
        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;    // 小心准备 level

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
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );

        me->add_mp(-mp);

	CHAR_FIGHT_D->set_enmity1(me,50);
	
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
          me->add_2("go_count.count2",5);
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 32531, 1, OVER_BODY, PF_ONCE );
	size = sizeof(all);
	time = 0; pos = -1;
	for (i =0;i<size;i++) if (time < get_effect_3(me, all[i])) 
	{
		time = get_effect_3(me, all[i]);
		pos = i;
	}
        if (pos!=-1)
        {
        	if (all[pos]<96) set_effect(me, all[pos], 1);
        	else set_effect_2(me, all[pos], 1, 1);
        }
        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        string arg;
        int level;
	int i, size, time, pos;
/*	
        int * all = ({ EFFECT_CHAR_BLIND, EFFECT_CHAR_WOUND, 
        	EFFECT_CHAR_BLOOD, EFFECT_CHAR_CHAOS, EFFECT_CHAR_LAZY, EFFECT_USER_BURN, 
        	EFFECT_CHAR_NO_PF, EFFECT_CHAR_ARMORFALL, 
        	EFFECT_CHAR_POWERFALL, EFFECT_CHAR_FALL, });
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        level = to_int(arg);

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 32531, 1, OVER_BODY, PF_ONCE );
	size = sizeof(all);
	time = 0; pos = -1;
	for (i =0;i<size;i++) if (time < get_effect(me, all[i])) 
	{
		time = get_effect(me, all[i]);
		pos = i;
	}
        if (pos!=-1)
        {
        	if (all[pos]<96) set_effect(me, all[pos], 1);
        	else set_effect_2(me, all[pos], 1, 1);
        }
*/
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 1, MAGIC_ACT_BEGIN, 0, 5, 0);
}

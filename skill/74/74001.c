#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#define PF_START       "74001"
#define TIME_INTERVAL   5

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74001; }
// 函数：获取技能类型
string get_name() { return "Biểu Diễn"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 0; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Nể tình vì chủ nhân biểu diễn!\n";
}
// 函数：获取指令类型
int get_perform_type() { return ON_ME_P; }

// 函数：能否使用指令
void can_perform( object me ,object pet)
{
        send_user( me, "%c%c%d%d%c%c%w%w%s", 0xA1,19,getoid(pet),get_id(),1, get_perform_type(), TIME_INTERVAL, 0, get_name() );
}

int perform_action_npc( object me, object who )
{
        int action = DEFAULT_ACT;
	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 2;
	if ( get_effect(me, EFFECT_MAGIC_CARD) )
		return 2;
	me->set_perform( PF_START, time() );
	send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
	action = random(3);
        switch( action )
        {
             default:
	     case 0 : action = ATTACK_ACT;  break;
	     case 1 : action = MAGIC_ACT;  break;
	     case 2 : action = STAND_ACT;  break;
	}
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), action );

        return 1;
}

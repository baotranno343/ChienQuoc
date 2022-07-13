
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#define PF_START       "74243"
#define TIME_INTERVAL   1800
#define TIME_LASTING   900
//#define TIME_INTERVAL   600
//#define TIME_LASTING   300

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74243; }
// 函数：获取技能类型
string get_name() { return "Biến Thân"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\nSử dụng sẽ biến Bảo Thú thành Kỳ Lân \nTất cả thuộc tính gia tăng gấp đôi \nDuy trì 15 phút \nTái sử dụng 30 phút .";
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
        int level;
	object owner;
	
        if( ( !me->get_skill(get_id()) ) ) return 0;
	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 0;
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) return 0;
        if( get_effect(me, EFFECT_MAGIC_CARD)) return 0;    // 执行成功
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        return 1;
}

int cast_done_npc( object me )
{
	int i;
	object who;
	
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );
        if( get_effect(me, EFFECT_MAGIC_CARD)) return 2;    // 执行成功
        send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
        me->set_perform( PF_START, time() );	
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me), 
                4176, 1, OVER_BODY, 4176, 1, UNDER_FOOT, PF_ONCE );

	set_effect_2(me, EFFECT_MAGIC_CARD, 1,TIME_LASTING);
	
	i = me->get_char_picid();
	me->set_save("primary_shape",i);
	me->set_save("change_shape",8100);
	me->set_char_picid(8100);
	NPC_PET_D->count_max_hp(me);
	NPC_PET_D->count_max_mp(me);
	NPC_PET_D->count_ap(me);
	NPC_PET_D->count_dp(me);
	NPC_PET_D->count_cp(me);
	NPC_PET_D->count_pp(me);
	NPC_PET_D->count_sp(me);

	me->add_to_scene(get_z(me), get_x(me), get_y(me)); 
	me->send_info();
        return 2;    // 执行成功
}
//参战时发送给客户端还有多少冷冻时间
int perform_lasting(object me)
{
	int i;
	i = TIME_INTERVAL - gone_time( me->get_perform(PF_START));
	if ( i > 0 )
	{
        	send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, i ) ;
        	
        }
}
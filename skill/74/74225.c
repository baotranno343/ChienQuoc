// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#define PF_START       "74225"
#define TIME_INTERVAL   20

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74225; }
// 函数：获取技能类型
string get_name() { return "Cao Cấp Ma Nhãn"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, sử dụng sẽ phát hiện ẩn thân trong phạm vi 20x20 \ntái sử dụng sau 20 giây";
}
// 函数：获取指令类型
int get_perform_type() { return ON_ME_P; }

// 函数：能否使用指令
void can_perform( object me ,object pet)
{
        send_user( me, "%c%c%d%d%c%c%w%w%s", 0xA1,19,getoid(pet),get_id(),1, get_perform_type(), 1, 0, get_name() );
}
int perform_action_npc( object me, object who )
{
        int level, mp=50;
        if( ( !me->get_skill(get_id()) ) ) return 0;
	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 0;
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) return 0;
        if( me->get_mp() < mp )  return 0;
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        me->add_mp(-mp);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        return 1;
}

int cast_done_npc( object me )
{
	object *char,owner,who;
	int i,size,x,y,z;
        send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
        me->set_perform( PF_START, time() );	
	owner = me->get_owner();
//        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me), 
//                32531, 1, OVER_BODY, 32531, 1, UNDER_FOOT, PF_ONCE );
        z = get_z(me);  x = get_x(me);  y = get_y(me);
        char = get_range_object(z, x, y, 20, USER_TYPE) + get_range_object(z, x, y, 20, CHAR_TYPE) - ({ me , owner });
        for( i = 0, size = sizeof(char); i < size; i ++ ) 
	{
		who = char[i];
//		if( !who->can_be_fighted(me) || !me->can_fight(who) )	continue;
		if( !get_effect_3(who, EFFECT_CHAR_INVISIBLE) ) 
			continue;
		set_effect_2(who, EFFECT_CHAR_INVISIBLE, 1, 1 ); 
		send_user( get_scene_object( get_z(who), x=get_x(who), y=get_y(who), USER_TYPE ), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                        32531, 1, OVER_BODY, 32531, 1, OVER_BODY, PF_ONCE );
	}
        return 2;    // 执行成功
}

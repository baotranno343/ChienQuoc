// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#define PF_START       "74239"
#define TIME_INTERVAL   15

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74239; }
// 函数：获取技能类型
string get_name() { return "Khốn Địch Thuật"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, sử dụng có tỷ lệ 30% không cho kẻ địch di chuyển \ntrong phạm vi 3x3 \nTái sử dụng sau 15 giây.";
}
// 函数：获取指令类型
int get_perform_type() { return ON_CHAR_P; }

// 函数：能否使用指令
void can_perform( object me ,object pet)
{
        send_user( me, "%c%c%d%d%c%c%w%w%s", 0xA1,19,getoid(pet),get_id(),1, get_perform_type(), TIME_INTERVAL, 0, get_name() );
}
int perform_action_npc( object me, object who )
{
        int level, mp=50;

        if( ( !me->get_skill(get_id()) ) ) return 0;
	if( !inside_screen_2(me, who) ) return 0;
	if( !who->can_be_fighted(me) || !me->can_fight(who) )	return 0;
	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 0;
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) return 0;
        if( me->get_mp() < mp )  return 0;
        me->to_front_xy(get_x(who), get_y(who));
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        me->add_mp(-mp);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id());
        return 1;
}


int cast_done_npc( object me )
{
	int x,y,z,interval;
	object who;
	string arg;
	
        send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
        me->set_perform( PF_START, time() );	
        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;
        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
	if ( random100() >= 30 )
		return 2;
	if (who->is_anti_effect()) return 2;
        if( get_effect(who, EFFECT_CHAR_CHAN) ) return 2;    // 执行成功
        if( get_effect(who, EFFECT_CHAR_9145) ) return 2;    // 执行成功
        z = get_z(who);  x = get_x(who);  y = get_y(who);
        who->set_save( "pf.chan", sprintf( "%d:(%d,%d)", z, x, y ) );
        interval = 6;    
        set_effect(who, EFFECT_CHAR_CHAN, interval);
        send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                21151, interval, OVER_TILE, 21152, interval, OVER_TILE, PF_ONCE );
        return 2;    // 执行成功
}

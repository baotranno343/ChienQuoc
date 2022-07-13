// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#define PF_START       "74139"
#define TIME_INTERVAL   20

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74139; }
// 函数：获取技能类型
string get_name() { return "Trói Buộc"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 0; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, Sử dụng có thể làm mục tiêu không di chuyển trong 3 giây \ntái sử dụng sau 20 giây ";
}
// 函数：获取指令类型
int get_perform_type() { return ON_CHAR_P; }

// 函数：能否使用指令
void can_perform( object me ,object pet)
{
        send_user( me, "%c%c%d%d%c%c%w%w%s", 0xA1,19,getoid(pet),get_id(),1, get_perform_type(), TIME_INTERVAL, 0, get_name() );
}
//是否远程法术
int is_caster() { return 1; }

int perform_action_npc( object me, object who )
{
        int level, mp=15;

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
	int rate;
	object who,*user;
	string arg;

        send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
        me->set_perform( PF_START, time() );	
        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;
        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
        user = get_scene_object_2(who, USER_TYPE);
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 23156, 1, OVER_BODY, PF_ONCE );
	if (who->is_anti_effect()) return 2;
	if (who->get("anti_slow")) return 2;
        if(     get_effect(who, EFFECT_CHAR_SLOW)
        ||      get_effect(who, EFFECT_CHAR_SLOW_0) ) return 2;    // 执行成功
        set_effect(who, EFFECT_CHAR_SLOW, 3);
        send_user( who, "%c%w%w%c", 0x81, 9012, get_effect_3(who, EFFECT_CHAR_SLOW), EFFECT_BAD );
        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9012, 1, EFFECT_BAD );
        send_user(who, "%c%c%c", 0x3d, 241, 1);    // 更改走路步数
	send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 34821, 1, UNDER_FOOT, PF_LOOP );
        return 2;    // 执行成功
}



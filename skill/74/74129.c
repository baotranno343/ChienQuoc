// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#define PF_START       "74129"
#define TIME_INTERVAL   2

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74129; }
// 函数：获取技能类型
string get_name() { return "Nhiếp Hồn"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 0; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, khiến bảo thú khi công kích cận chiến Hấp thụ khí huyết 5%.";
}
// 函数：获取指令类型
int get_perform_type() { return ON_CHAR_P; }

// 函数：能否使用指令
void can_perform( object me ,object pet)
{
        send_user( me, "%c%c%d%d%c%c%w%w%s", 0xA1,19,getoid(pet),get_id(),1, get_perform_type(), TIME_INTERVAL, 0, get_name() );
}

//攻击速度
int get_attack_speed() { return 12; }

int perform_action_npc( object me, object who )
{
        int level, mp=15;

        if( ( !me->get_skill(get_id()) ) ) return 0;
        if( !inside_screen_2(me, who) ) return 0;
	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 0;
	if( !who->can_be_fighted(me) || !me->can_fight(who) )	return 0;
        if( me->get_mp() < mp )  return 0;
	if( !CHAR_FIGHT_D->attack_action(me, who) ) return 0; 
        me->add_mp(-mp);
        me->set_perform( PF_START, time() );
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id());
        return 1;
}

int cast_done_npc( object me )
{
	int rate;
	object who;
	string arg;

        send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;
        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
	me->set_absorb_hp(5);
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 
                3252, 1, OVER_BODY, 3252, 1, UNDER_FOOT, PF_ONCE );
	CHAR_FIGHT_D->attack_done(me, who);
	me->set_absorb_hp(0);
        me->set_enemy_3(who);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 7);  
        return 1;
}

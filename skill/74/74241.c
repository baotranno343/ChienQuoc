// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#define PF_START       "74241"
#define TIME_INTERVAL   30

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74241; }
// 函数：获取技能类型
string get_name() { return "Xung Phong"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, sử dụng sẽ khiến bảo thú biến đến bên địch \ncông kích \nTái sử dụng sau 30 giây";
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

//攻击速度
int get_attack_speed() { return 12; }

int perform_action_npc( object me, object who )
{
        int level, mp=50,x,y,z,p;

        if( ( !me->get_skill(get_id()) ) ) return 0;
	if( !inside_screen_2(me, who) ) return 0;
	if( !who->can_be_fighted(me) || !me->can_fight(who) )	return 0;
	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 2;
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) return 0;
        if( me->get_mp() < mp )  return 0;
        z = get_z(who);
	p=get_valid_xy(z,get_x(who),get_y(who),IS_CHAR_BLOCK);
	if ( !p )
		return 0;
	x = p/1000; y = p%1000;
	me->add_to_scene(z,x,y);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 9413, 1, OVER_BODY, PF_ONCE );    
	if( !CHAR_FIGHT_D->attack_action(me, who) ) return 0; 
        me->add_mp(-mp);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id());
        return 1;
}

int cast_done_npc( object me )
{
	int x,y,z,i,size,p,j,x0,y0;
	object who,*char,owner,*target,*user;
	string arg;
	
        send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
        me->set_perform( PF_START, time() );
	if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;
	if( !inside_screen_2(me, who) ) return 1;
        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
	p = CHAR_FIGHT_D->attack_done(me, who);
	if ( !who ) return 2;
	if ( who->is_die() ) return 2;
	if ( p )
	{
		if (who->is_anti_effect()) return 2;
		if (who->get("anti_faint")) return 2;
	        if(     get_effect(who, EFFECT_CHAR_FAINT)
	        ||      get_effect(who, EFFECT_CHAR_FAINT_0) ) return 2;    // 执行成功
		user = get_scene_object_2(who, USER_TYPE);
		set_effect(who, EFFECT_CHAR_FAINT, 1);
	        CHAR_CHAR_D->init_loop_perform(who);
	        if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
	        send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
	        send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
	        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );	        
	}
        return 2;    // 执行成功
}

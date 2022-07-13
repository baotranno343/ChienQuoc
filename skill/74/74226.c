// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74226; }
// 函数：获取技能类型
string get_name() { return "Lôi Điện Giao Gia"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, Dùng lôi điện tấn công mục tiêu phạm vị 3x3.";
}
// 函数：获取指令类型
int get_perform_type() { return ON_XY_P; }

// 函数：能否使用指令
void can_perform( object me ,object pet)
{
        send_user( me, "%c%c%d%d%c%c%w%w%s", 0xA1,19,getoid(pet),get_id(),1, get_perform_type(), 1, 0, get_name() );
}
//是否远程法术
int is_caster() { return 1; }

int perform_action_npc( object me, object who, int x, int y, string arg )
{
        int level, mp=50;

        if( ( !me->get_skill(get_id()) ) ) return 0;
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) return 0;
        if( me->get_mp() < mp )  return 0;
        me->to_front_xy(x, y);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        me->add_mp(-mp);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg(sprintf("%d %d %d",get_z(me),x,y));
        return 1;
}

int cast_done_npc( object me )
{
	int x,y,z,rate;
	int i,size;
	object who,*char,owner;
	string arg;

        send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        if( sscanf(arg,"%d %d %d",z,x,y) != 3 ) return 1;
        owner = me->get_owner();
        char = get_range_object(z, x, y, 1, USER_TYPE) + get_range_object(z, x, y, 1, CHAR_TYPE) - ({ me , owner });
        if ( !(size=sizeof(char)) )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                        25164, 1, OVER_BODY, 25164, 1, OVER_BODY, PF_ONCE );
		return ;        	
        }
	for(i=0;i<size;i++)
	{
		who = char[i];
		if( !inside_screen_2(me, who) ) continue;
	        if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;    // 执行成功
	        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 
	                25164, 1, OVER_BODY, 25164, 1, UNDER_FOOT, PF_ONCE );
		if ( rate=who->get("anti_thunder") )	//抗雷
			CHAR_FIGHT_D->cast_done(me, who, 0, -1*(20+rate), 0 );
		else
			CHAR_FIGHT_D->cast_done(me, who, 0, -20, 0 );
	}
        return 2;    // 执行成功
}


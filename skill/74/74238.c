// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#define PF_START       "74238"
#define TIME_INTERVAL   2

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74238; }
// 函数：获取技能类型
string get_name() { return "Hộ Thân Cường Khí"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, có 50% tỷ lệ đánh lui đối phương 6 bước \nKhông có hiệu quả với BOSS.";
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
	int rate,x,y,z,x0,y0,x1,y1,flag1,flag2;
	int i,p;
	object who;
	string arg;
	
        send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
        me->set_perform( PF_START, time() );	
        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;
        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
        if ( random100() < 50 )
        	return ;
	z = get_z(who); x = get_x(who); y = get_y(who);
	x0 = get_x(me); y0 = get_y(me);
	if ( x - x0 > 0 )
		flag1 = 1;
	else if ( x - x0 < 0 )
		flag1 = -1;
	else
		flag1 = 0;
	if ( y - y0 > 0 )
		flag2 = 1;
	else if ( y - y0 < 0 )
		flag2 = -1;
	else
		flag2 = 0;
	for(i=6;i>=0;i--)
	{
		x1 = x + flag1*i;
		y1 = y + flag2*i;
		if ((p=get_valid_xy(z,x1,y1,IS_CHAR_BLOCK)) && p/1000==x1 && p%1000==y1 )
			break;
	}
	if ( i < 0 )
	{
		y1 = y; x1=x;
	}
	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 2571, 1, OVER_BODY, PF_ONCE );    // 补发指令
	who->add_to_scene(z,x1,y1);
	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x1, y1, 2571, 1, OVER_BODY, PF_ONCE );    // 补发指令
        return 2;    // 执行成功
}

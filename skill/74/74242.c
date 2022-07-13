// 部分自动生成：/make/skill/makeski74

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#define PF_START       "74242"
#define TIME_INTERVAL   2

// 函数：宠物技能
int is_pet_skill() { return 1; }
// 函数：获取技能ID
int get_id() { return 74242; }
// 函数：获取技能类型
string get_name() { return "Tâm Thể Tương Thông"; }
// 函数：获取技能类型（0、被动；1、主动）
int get_type() { return 1; }
// 函数：获取技能等级（0、普通；1、高级）
int get_level() { return 1; }
// 函数：获取描述
string get_desc( object me )
{
	return HIC+get_name()+"\n Kỹ năng của Bảo thú, sử dụng sẽ đem thương tổn trên bảo thú truyền qua \nchủ nhân theo tỷ lệ 2:1 \nVà ngược lại tỷ lệ 1:2 \nHiệu quả duy trì 10 phút";
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
        int level, mp=50;

        if( ( !me->get_skill(get_id()) ) ) return 0;
	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 0;
        if( get_effect(me, EFFECT_CHAR_NO_PF) ) return 0;
        if( me->get_mp() < mp )  return 0;
        if( get_effect(me, EFFECT_CHAR_SOUL_LOCK)) return 0;    // 执行成功
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        me->add_mp(-mp);
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        return 1;
}

int cast_done_npc( object me )
{
	int rate;
	object who;
	string arg;
	
        send_user( me->get_owner(), "%c%c%d%d%c%w", 0xA1,27,0,get_id(),0xff, 0 );
        me->set_perform( PF_START, time() );	
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me), 
                3123, 1, OVER_BODY, 3123, 1, UNDER_FOOT, PF_ONCE );
        if( get_effect(me, EFFECT_CHAR_SOUL_LOCK)) return 2;    // 执行成功
	set_effect_2(me, EFFECT_CHAR_SOUL_LOCK, 1, 600 ); 
//        set_effect(me, EFFECT_CHAR_SOUL_LOCK, 600);
        send_user( me, "%c%w%w%c", 0x81, 3123, get_effect_3(me, EFFECT_CHAR_SOUL_LOCK), EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3123, 600, EFFECT_GOOD );
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 42531, 1, OVER_BODY, PF_LOOP );	        
        CHAR_CHAR_D->init_loop_perform(me);
        return 2;    // 执行成功
}

// 开关技能  TIPS:[PF_SWITCH]
#include <effect.h>
#include <ansi.h>
#include <skill.h>

#define THIS_SKILL      0319
#define THIS_PERFORM    03192
#define PF_FLAG        "03192"
#define PF_NAME        "Kim Cương Thân Pháp"

#define SKILL_LEVEL     30
#define SUB_YUAN        4
#define TIME_INTERVAL   2

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 30 cấp\n    Hấp thụ linh khí tự nhiên để hộ thể, nâng cao phòng thủ. Trong thời gian sử dụng tăng thêm 35%% Ngoại Kháng, nhưng giảm đi 50%% Ngoại Công. Trong trạng thái phòng thủ không thể thay đổi trang bị.";
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Nguyên khí tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Hấp thụ linh khí tự nhiên để hộ thể, nâng cao phòng thủ. Trong thời gian sử dụng tăng thêm 35%% Ngoại Kháng, nhưng giảm đi 50%% Ngoại Công. Trong trạng thái phòng thủ không thể thay đổi trang bị.\n    Sử dụng thêm lần nữa để huỷ.\n", 
        	PF_NAME, SKILL_LEVEL, SUB_YUAN, TIME_INTERVAL);
        return result;
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
        if( me->get_perform(PF_FLAG) )
                return sprintf( "Kim cương:\n　　Tăng 35%% ngoại kháng，Giảm 50%% công kích ngoại công.\n" );
        else    return sprintf( "Kim cương\n" );
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{	
	int enmity;
	if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) return 1;
        if( me->get_perform(PF_FLAG) )    // 关闭
        {
        	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 0, get_d(me), 0 );
	        set_effect(me, EFFECT_PROGRESS2, 4);
	        me->set_progress_file(__FILE__);
		send_user(me, "%c%c%w%s", 0x5a, 0, 4, "Thi triển Kim Cương Thân……");        	
		return 1;
        }        
        if( me->get_yuan() < SUB_YUAN )
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Nguyên khí.", PF_NAME, SUB_YUAN );
                return 1;
        }        
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 2, 0, get_d(me), 0 );
	me->add_yuan( -SUB_YUAN );
	set_effect(me, EFFECT_PROGRESS2, 4);
	me->set_progress_file(__FILE__);
	send_user(me, "%c%c%w%s", 0x5a, 0, 4, "Thi triển Kim Cương Thân……");        	
	enmity = 60 + (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/30*50 ;
	CHAR_FIGHT_D->set_enmity1(me,enmity); 
	return 1;	
}

// 函数:法术处理
int into_effect( object me , string arg)
{
	if( me->get_perform(PF_FLAG) )    // 关闭
	{
		me->delete_perform(PF_FLAG);
		send_user(me, "%c%c%c", 0x5a, 1, 1);
		USER_ENERGY_D->count_ap(me);
		USER_ENERGY_D->count_dp(me);
		USER_ENERGY_D->count_pp(me);
	        send_user( me, "%c%w%w%c", 0x81, 3192, 0, EFFECT_GOOD );
	        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3192, 0, EFFECT_GOOD );
		
	}
	else
	{
		me->set_perform(PF_FLAG, 1);
		me->set_perform("03191", 0);
		send_user(me, "%c%c%c", 0x5a, 1, 1);
		USER_ENERGY_D->count_ap(me);
		USER_ENERGY_D->count_dp(me);	
		USER_ENERGY_D->count_pp(me);	
	        send_user( me, "%c%w%w%c", 0x81, 3192, 30000, EFFECT_GOOD );
	        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3192, 1, EFFECT_GOOD );		
	        send_user( me, "%c%w%w%c", 0x81, 3191, 0, EFFECT_GOOD );
	        send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 3191, 0, EFFECT_GOOD );
	        
	}
}

void effect_break(object me, string arg)
{
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	set_effect(me, EFFECT_PROGRESS2, 0 );	
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform( object me )
{
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, TIME_INTERVAL, 0, PF_NAME );
                return;
        }	
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, PF_NAME );
}

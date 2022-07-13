
// 召唤技能  TIPS:[PF_CALL]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0413
#define THIS_PERFORM    04130
#define PF_START       "04130"
#define PF_NAME        "Triệu Hoán Chú"

#define SKILL_LEVEL     1
#define SUB_MP          0


// 函数：获取符法效果
int get_cast_seal() { return 9103; }    // 符纸逆旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR" %s \n Võ công yêu cầu: Cấp 1\n Thu lại Triệu hồi thú của mình.", PF_NAME);
        result = sprintf(HIC" %s \n " NOR "Võ công yêu cầu: Cấp %d \n Tái sử dụng sau: %d giây\n Thu lại Triệu hồi thú của mình.", 
        	PF_NAME, SKILL_LEVEL, 2 );
        return result;  
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{

	object * user, soldier, * zombie;
	int flag = 0;
	int i, size;
	who = me->get("soldier");
	if (!who) return 1;
	if (who->get_owner()!=me)
        {
                printf( ECHO "Đối phương không phải thú của bạn" );
                return 1;
        }	
        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );        
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );        
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(who), get_y(who), 9414, 1, OVER_BODY, PF_ONCE );
	send_user(me, "%c%c%d", 0x2c, 0, getoid(who));
	who->remove_from_scene(FALL_ACT);
	destruct(who);	
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END );
        return 2;    // 执行成功
}


// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 5, 0);
}


// 召唤技能  TIPS:[PF_CALL]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0414
#define THIS_PERFORM    04147
#define PF_START       "04147"
#define PF_NAME        "Huyết Ma Chú"

#define TIME_INTERVAL	2
#define SKILL_LEVEL     3
#define SUB_HP          ( 30 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 10 * 34 )


// 函数：获取符法效果
int get_cast_seal() { return 9103; }    // 符纸逆旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 3 cấp\n    Lấy 30 điểm Khí Huyết của bản thân chuyển đổi thành 45 điểm Pháp Lực.";
        cur_level = (level - SKILL_LEVEL)/10 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Khí Huyết tiêu hao： %d điểm\n Tái sử dụng sau: %d giây\n    Lấy %d điểm Khí Huyết của bản thân chuyển đổi thành %d điểm Pháp Lực.\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: " HIR "Cấp %d " NOR"\n    Lấy %d điểm Khí Huyết của bản thân chuyển đổi thành %d điểm Pháp Lực.",
        	PF_NAME, cur_level, 
        	SKILL_LEVEL, SUB_HP, 2, SUB_HP, SUB_HP*12/10,
        	cur_level*10+SKILL_LEVEL, SUB_HP + 34, (SUB_HP + 34)*12/10 );
	return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
	object * user, soldier, * zombie;
	int flag = 0;
	int i, size, hp;
	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;
        if( me->get_hp() < ( hp = SUB_HP ) )    // 小心准备 me
        {
                printf( ECHO "Khí Huyết không đủ, không thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }	
		if( me->get_fam_name() != "Mao Sơn" )
        {
                printf( ECHO "Môn phái Mao Sơn mới có thể sử dụng \"" PF_NAME "\" ." );
                return 1;
        }
	
        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 4147, 1, OVER_BODY, PF_ONCE );
        me->add_hp(-hp);
        me->add_mp(hp*120/10);
	me->set_perform( PF_START, time() );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
	CHAR_FIGHT_D->set_enmity1(me,20);
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }


// 函数：能否使用特技
void can_perform( object me )
{
        int level, interval, interval2;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = TIME_INTERVAL;    // 小心准备 me
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), interval, 0, PF_NAME );

}

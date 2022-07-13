
// 召唤技能  TIPS:[PF_CALL]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0411
#define THIS_PERFORM    04110
#define PF_START       "04110"
#define PF_NAME        "法力转移"
#define TIME_INTERVAL	1

#define SKILL_LEVEL     5
#define SUB_MP          20 + me->get_skill(THIS_SKILL) * (me->get_skill(THIS_SKILL)+1)/20


// 函数：获取符法效果
int get_cast_seal() { return 41100; }    // 符纸逆旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        return sprintf( "［" PF_NAME "］辅助法术，将自己 %d 法术力转换为召唤兽的法术力，%s%d 级可用\n",
                SUB_MP, level < SKILL_LEVEL ? HIR : "", SKILL_LEVEL );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{

	object * user, soldier, * zombie;
	int flag = 0;
	int i, size, mp;
	if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;
        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }	
        who = me->get("soldier");
        if (!who) return 1;
	if (who->get_owner()!=me)
        {
                printf( ECHO "对方不是您的召唤生物。" );
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
        me->set_cast_file(__FILE__);	
        who->add_mp(mp);
        me->add_mp(-mp);
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 42411, 2, OVER_BODY, PF_ONCE );
	me->set_perform( PF_START, time() );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
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
        int level, interval, interval2;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = TIME_INTERVAL;    // 小心准备 me
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), interval, 0, PF_NAME );

}

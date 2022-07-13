
// 自用技能  TIPS:[PF_SELF]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <equip.h>

#define THIS_SKILL      0513
#define THIS_PERFORM    05131
#define PF_START       "05131"
#define PF_NAME        "炼丹"

#define SKILL_LEVEL     13

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        return sprintf( "［" PF_NAME "］按配方炼制药物，%s%d 级可用\n",
                level < SKILL_LEVEL ? HIR : "", SKILL_LEVEL );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) return 1;

        if( me->get_perform(PF_START) == time() ) return 1;
        send_user( me, "%c%s", '!', "炼药功能尚未开放。" );
	return;          

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg("");

        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(me), 
                51311, 16, OVER_BODY, 51312, 1, OVER_BODY, 51313, 1, UNDER_FOOT, PF_ONCE );    // 丹鼎速度特殊！

        send_user( me, "%c%c", 0x25, 1 );    // 打开炼药界面

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
}

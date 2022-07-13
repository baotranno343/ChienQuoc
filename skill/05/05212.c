
// 自用技能  TIPS:[PF_SELF]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <equip.h>

#define THIS_SKILL      0521
#define THIS_PERFORM    05212
#define PF_START       "05212"
#define PF_NAME        "炼毒"

#define SKILL_LEVEL     35
#define SUB_MP          30
#define ADD_POISON      me->get_pf_value_2(THIS_SKILL, SKILL_LEVEL_SQUARE, poison, 100)    // 警告：me, poison 得准备好

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数：获取要求等级
int get_skill_level() { return SKILL_LEVEL; }

// 函数：获取法力
int get_sub_mp( object me ) { return SUB_MP; }

// 函数：获取增加毒性
int get_add_poison( object me, int poison )
{
        return ADD_POISON;    // 小心准备 me, poison
}

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        return sprintf( "［" PF_NAME "］将毒药研磨成毒粉，以涂在武器上面。消耗法力：%d，%s%d 级可用\n基础技能要求：中医药理\n",
                SUB_MP, level < SKILL_LEVEL ? HIR : "", SKILL_LEVEL );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( me->get_perform(PF_START) == time() )  return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

//      me->add_mp(-mp);

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
                52121, 16, OVER_BODY, 52122, 1, OVER_BODY, 52123, 1, UNDER_FOOT, PF_ONCE );    // 丹鼎速度特殊！

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


#include <ansi.h>
#include <skill.h>

#define JOB_ACTOR_D     "/inh/job/actor"

#define THIS_PERFORM    00102
#define PF_NAME        "唱歌"

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "［" PF_NAME "］\n使对方持续增加法力\n"; 
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        JOB_ACTOR_D->do_sing(me, who, arg);

        return 1;
}

// 函数：获取指令类型
int get_perform_type() { return ON_CHAR_7; }

// 函数：能否使用指令
void can_perform( object me )
{
        if( me->is_actor() ) 
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
}

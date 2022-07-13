#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define PF_FLAG        "11004"
#define PF_NAME        "超级无敌狗狗拳"


// 函数：命令处理(动作)
int perform_action_npc( object me, object who )
{
        if( !CHAR_FIGHT_D->attack_action(me, who, 36) ) return 0;

        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE);    // 小心准备 me
        if( !who ) return 2;    // 执行成功
        CHAR_FIGHT_D->attack_done(me, who, HIT_NONE);    // 小心准备 me

        return 1;    // 执行成功
}

int perform_done_npc( object me, object who )
{
        return 2;    // 执行成功
}
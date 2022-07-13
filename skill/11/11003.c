
// 开关技能  TIPS:[PF_SWITCH]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0251
#define THIS_PERFORM    02514
#define PF_NAME        "横扫千军"

#define SKILL_LEVEL     6
#define TIME_INTERVAL   2
#define SUB_MP          0
#define SUB_YUAN        1

int perform_done_npc( object me, object who );

// 函数：命令处理(动作)
int perform_action_npc( object me, object who )
{

        if( !CHAR_FIGHT_D->attack_action(me, who, 2040) ) return 0;

        perform_done_npc(me, who);

        return 1;    // 执行成功
}

// 函数：命令处理
int perform_done_npc( object me, object who )
{
        object *char;
        int i, size;

//        if( distance_between(me, who) > 1 ) return 0;
        me->set_perform_2_file(0);

        char = get_range_object_2(me, 1, USER_TYPE) - ({ me })+ get_range_object_2(me, 1, CHAR_TYPE); 
        for( i = 0, size = sizeof(char); i < size; i ++ ) 
        {
                if( who = char[i] ) CHAR_FIGHT_D->attack_done(me, who);
        }
        return 2;    // 执行成功
}


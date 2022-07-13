
// 开关技能  TIPS:[PF_SWITCH]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>


#define THIS_SKILL      11001
#define THIS_PERFORM    02214
#define PF_FLAG        "11001"
#define PF_NAME        "Hoành Tảo"
// Hoành tảo
#define SKILL_LEVEL     32
#define ADD_AP          me->get_pf_value_2(THIS_SKILL, SKILL_LEVEL_SQUARE, 16, 160)    // 警告：me 得准备好

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

void perform_done_npc( object me, object who );

// 函数：命令处理(动作)
int perform_action_npc( object me, object who )
{
        if( !CHAR_FIGHT_D->attack_action(me, who, 2040) ) return 0;

        perform_done_npc(me, who);

        return 1;    // 执行成功
}

// 函数：特殊技处理
int perform_done_npc( object me, object who )
{
        object *char;
        int z, x, y, d;
        int level, mp, ap, i, size;
	string arg;
	

        me->set_perform_2_file(0);

        z = get_z(me);  x = get_x(me);  y = get_y(me);  d = get_d(me);

        switch( d )
        {
       case 1 : char = get_area_object(z, (x + 1), y - 1, (x + 1), y + 1, USER_TYPE) 
                     + get_area_object(z, (x + 1), y - 1, (x + 1), y + 1, CHAR_TYPE);
                break;
      default : char = get_area_object(z, x, y - 1, (x + 1), y, USER_TYPE) 
                     + get_area_object(z, x, y - 1, (x + 1), y, CHAR_TYPE) - ({ me });
                break;
       case 3 : char = get_area_object(z, (x - 1), y - 1, (x + 1), y - 1, USER_TYPE) 
                     + get_area_object(z, (x - 1), y - 1, (x + 1), y - 1, CHAR_TYPE);
                break;
       case 4 : char = get_area_object(z, (x - 1), y - 1, x, y, USER_TYPE) 
                     + get_area_object(z, (x - 1), y - 1, x, y, CHAR_TYPE) - ({ me });
                break;
       case 5 : char = get_area_object(z, (x - 1), y - 1, (x - 1), y + 1, USER_TYPE) 
                     + get_area_object(z, (x - 1), y - 1, (x - 1), y + 1, CHAR_TYPE);
                break;
       case 6 : char = get_area_object(z, (x - 1), y, x, y + 1, USER_TYPE) 
                     + get_area_object(z, (x - 1), y, x, y + 1, CHAR_TYPE) - ({ me });
                break;
       case 7 : char = get_area_object(z, (x - 1), y + 1, (x + 1), y + 1, USER_TYPE) 
                     + get_area_object(z, (x - 1), y + 1, (x + 1), y + 1, CHAR_TYPE);
                break;
       case 8 : char = get_area_object(z, x, y, (x + 1), y + 1, USER_TYPE) 
                     + get_area_object(z, x, y, (x + 1), y + 1, CHAR_TYPE) - ({ me });
                break;
        }

        ap = ADD_AP;    // 小心准备 me

        for( i = 0, size = sizeof(char); i < size; i ++ ) 
                if( who = char[i]  ) CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, ap);

        return 2;    // 执行成功
}

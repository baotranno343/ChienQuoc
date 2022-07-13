
// 挖宝的恶犬专用攻击

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>


#define THIS_SKILL      11001
#define THIS_PERFORM    02214
#define PF_FLAG        "11001"
#define PF_NAME        "攻击加延缓"



void perform_done_npc( object me, object who );

// 函数：命令处理(动作)
int perform_action_npc( object me, object who )
{
        int level;

	if( CHAR_FIGHT_D->attack_action(me, who) )
	{
	        set_heart_state(me, MAGIC_STAT);
	        set_heart_count_2(me, 3);
	        me->set_cast_file(__FILE__);
	        me->set("att",who);
	}

        return 1;
}

int cast_done_npc( object me )
{
	int ret;
	object who;
	
	who = me->get("att");
	if ( !who )
		return 2;
	ret = CHAR_FIGHT_D->attack_done(me, who);
        if (!who) return 2;
        if (who->is_anti_effect()) return 2;
        if ( !who->get("anti_slow") && ret>0)
        {
	        if(     get_effect(who, EFFECT_CHAR_SLOW)
	        ||      get_effect(who, EFFECT_CHAR_SLOW_0) ) return 2;    // 执行成功
                set_effect(who, EFFECT_CHAR_SLOW, 6);
                send_user( who, "%c%w%w%c", 0x81, 9012, get_effect_3(who, EFFECT_CHAR_SLOW), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9012, 1, EFFECT_BAD );
                send_user(who, "%c%c%c", 0x3d, 241, 1);    // 更改走路步数
        }		
        return 2;    // 执行成功
}
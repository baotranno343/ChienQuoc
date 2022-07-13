#include <ansi.h>
#include <action.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <cmd.h>

#define THIS_SKILL      11009
#define THIS_PERFORM    11009
#define PF_NAME        "釜底抽薪"

int perform_action_npc( object me, object who )
{
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 15);
        me->set_cast_file(__FILE__);
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9102, 1, UNDER_FOOT, PF_LOOP );
	SAY_CMD->say(me, "小鬼们，快快放下手中的武器投降吧！！"); 
        return 1;
}

int cast_done_npc( object me )
{
	int x,y,z,rate;
	int i,size;
	object who,*char,owner;
	string arg;
	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9102, 1, UNDER_FOOT, PF_STOP );
	z=get_z(me);y=get_y(me);x=get_x(me);
        char = get_range_object(z, x, y, 10, USER_TYPE) ;
	size=sizeof(char);
	for(i=0;i<size;i++)
	{
		who = char[i];
		if( !inside_screen_2(me, who) ) continue;
	        if( !who->can_be_fighted(me) || !me->can_fight(who) ) continue;
        	if ( who->get_2("suit_effect.no_drop") ) return 2;  //套装           

                send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21141, 1, OVER_BODY, PF_ONCE );    // 技能成功
                set_effect(who, EFFECT_NO_WEAPON, 6);  
                CHAR_CHAR_D->init_loop_perform(who);
                send_user( who, "%c%w%w%c", 0x81, 2114, 6, EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 2114, 6, EFFECT_BAD );
                if (who->is_user())
                {
                	USER_ENERGY_D->count_all_prop(who);
                	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w", 0x7c, getoid(who), UNARMED );    
                }

	}
        return 2;    // 执行成功
}

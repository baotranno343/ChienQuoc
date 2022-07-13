
// 物理技能  TIPS:[PF_HIT]

#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0281
#define THIS_PERFORM    02810
#define PF_START       "02811"
#define PF_NAME        "Thanh Phong Quyết"


// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        return 1;
}

// 函数：特殊技处理(动作)
int perform_action( object me, object who )
{
        int level, mp;

        if( !CHAR_FIGHT_D->attack_action(me, who, 0, 9) ) 
        {
        	return 1;
        }
	me->set_perform_file(__FILE__);
	me->set_perform_enable_time(time());
        return 2;    // 执行成功
}

// 函数：特殊技处理
int perform_done( object me, object who )
{
        int cp, cp0;
        int double_flag, random, id, magic;
        object item, owner;
        string family;
        if( objectp( item = me->get_equip(WEAPON_TYPE) ))
        	cp0 = item->get("cp");
        else cp0 = 1;
        
	family = me->get_fam_name();
	switch(family)
	{
	case "Mao Sơn":
		magic = 27111;
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), magic, 1, OVER_BODY, PF_ONCE );
		break;
	case "Vân Mộng Cốc":
		magic = 28111;
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), magic, 1, OVER_BODY, PF_ONCE );
		break;		
	case "Thục Sơn":
		magic = 23132;
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), magic, 1, OVER_BODY, PF_ONCE );
		break;
	case "Huế Style":
		magic = 23132;
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), magic, 1, OVER_BODY, PF_ONCE );
		break;	
	default:
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 42311, 1, OVER_BODY, 42312, 1, OVER_BODY, PF_ONCE );
		break;				
	}	
	cp = me->get_cp();
	me->set_cp(cp0);
	CHAR_FIGHT_D->cast_done(me, who);
	me->set_cp(cp);	                      
        return 2;    // 执行成功
}


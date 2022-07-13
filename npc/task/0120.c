
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：远程攻击的怪
int is_caster() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 0901; }

// 函数：构造处理
void create()
{
        set_name("夜明鬼");

        set_level(29);
	set_max_hp(400);
	set_ap(150);
	set_dp(265);
	set_cp(140);
	set_pp(230);
	set_sp(90);
	set_walk_speed(4);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{        
        if ( objectp(who) && who->get_legend(TASK_06, 19)&&!who->get_legend(TASK_06, 20) )
        {
		who->set_legend(TASK_06, 20);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,25,"神灵的怨恨(完成)" );
		send_user(who, "%c%s",'!', "夜明鬼 1/1");
	}
        
}
// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action( object who ) { return PF_FILE_04232->perform_action_npc( this_object(), who ); }

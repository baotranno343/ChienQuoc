
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
int get_char_picid() { return 0053; }

// 函数：构造处理
void create()
{
        set_name("甑九");

        set_level(120);
	set_max_hp(3000);
	set_ap(780);
	set_dp(660);
	set_cp(100);
	set_pp(440);
	set_sp(320);
	set_walk_speed(3);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

// 函数：获取装备代码
int get_weapon_code() { return THROWING; }

void check_legend_task( object who )
{
	int p;
	object item;
        if ( objectp(who) && who->get_legend(TASK_46, 3)&&!who->get_legend(TASK_46, 4) )
        {
		who->set_legend(TASK_46, 4);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,65,"刀魂传说2(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_QINGUO,65);
		send_user(who, "%c%s",'!', "甑九 1/1");
	}	
}
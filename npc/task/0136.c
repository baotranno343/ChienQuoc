
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;

// 函数：获取人物造型
int get_char_picid() { return 8010; }

// 函数：构造处理
void create()
{
        set_name("水魅");

        set_level(52);
	set_max_hp(1100);
	set_ap(370);
	set_dp(420);
	set_cp(100);
	set_pp(200);
	set_sp(160);
	set_walk_speed(4);
	set_attack_speed(13);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_12, 19) && !who->get_legend(TASK_12, 20) )
        {
		who->set_legend(TASK_12, 20);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,7,"郑国渠里的哭声(完成)" );
		send_user(who, "%c%s",'!', "水魅 1/1");
	}
}

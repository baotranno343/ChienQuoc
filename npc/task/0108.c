
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;


// 函数：获取人物造型
int get_char_picid() { return 8012; }

// 函数：构造处理
void create()
{
        set_name("Mã Tặc Phùng Đại Long");

        set_level(22);
	set_max_hp(360);
	set_ap(160);
	set_dp(210);
	set_cp(148);
	set_pp(130);
	set_sp(90);
	set_walk_speed(3);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

void check_legend_task( object who )
{
        if ( objectp(who) && who->get_legend(TASK_04, 23)&&!who->get_legend(TASK_04, 24) )
        {
		who->set_legend(TASK_04, 24);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,11,"惩恶扬善(完成)" );
		send_user(who, "%c%s",'!', "Mã Tặc Phùng Đại Long 1/1");
	}	
}
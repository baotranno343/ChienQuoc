
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
inherit LEGEND_NPC;
object boss1;

// 函数：获取人物造型
int get_char_picid() { return 0600; }

// 函数：构造处理
void create()
{
        set_name("恶将胡");

	set_max_hp(400);
	set_ap(30);
	set_dp(20);
	set_pp(10);
	set_sp(30);
	set_walk_speed(6);
	set_attack_speed(30);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);    
}

void create_npc()
{
	remove_call_out("create_npc");
	if ( !objectp(boss1) )
	{
		boss1 = new("npc/task/0100");
		if ( boss1 )
			boss1->add_to_scene(3,159,85,4);
	}
	else if ( get_z(boss1) != 3 || get_x(boss1) != 159 || get_y(boss1) != 85 )
		boss1->add_to_scene( 3, 159, 85, 4, 40971, 0, 40971, 0 );
	call_out("create_npc",180);
}

void check_legend_task( object who )
{
 	if ( who->get_legend(TASK_NEWBIE_02, 14)&&!who->get_legend(TASK_NEWBIE_02, 15) )
        {
		who->set_legend(TASK_NEWBIE_02, 15);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,20,"惩治恶将(已经完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,20);
		send_user( who, "%c%s", '!', HIY"惩治恶将"NOR" 任务完成");			
		who->add_exp(50);
		who->add_potential(1);
		send_user(who,"%c%s",';',"你得到50点经验和1点潜能");
	}	
}
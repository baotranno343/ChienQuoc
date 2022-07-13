
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
int get_char_picid() { return 0052; }

// 函数：构造处理
void create()
{
        set_name("杜毒");

        set_level(116);
	set_max_hp(4954);
	set_ap(700);
	set_dp(633);
	set_cp(843);
	set_pp(368);
	set_sp(270);
	set_walk_speed(4);
	set_attack_speed(15);
        set_max_seek(4);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

// 函数：获取装备代码
int get_weapon_code() { return THROWING; }

// 函数：特技攻击对手
int perform_action( object who ) { return PF_FILE_01611->perform_action_npc( this_object(), who ); }

void check_legend_task( object who )
{
	int p;
	object item;
        if ( objectp(who) && who->get_legend(TASK_44, 7)&&!who->get_legend(TASK_44, 8) )
        {
		item = new("item/98/0218");
        	if ( !item )
        		return ;
        	p = item->move(who,-1);
        	if ( !p )
        		return;
        	item->add_to_user(p);
		who->set_legend(TASK_44, 8);
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,63,"漂亮的床（2）(完成)" );
		USER_TASK_D->send_task_intro(who,2,TID_WEIGUO,63);
		send_user(who, "%c%s",'!', "杜毒 1/1");
	}	
}
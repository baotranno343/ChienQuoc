
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit SLAVE;

// 函数：是否不能进城
int cannot_enter_city() { return 1; }
// 函数：获取人物造型
//int get_char_picid() { return 5209; }
// 函数：获取召唤兽类型
int get_zombie_type() { return 99; }     // 判断种类
//int is_general_slave() { return 1; }

int is_caster() { return get("caster"); }

int is_zombie() { return 0; }  

// 函数：构造处理
void create()
{
        set_name("Sĩ Binh");

        set_level(65);
	set_max_hp(1500);
	set_ap(420);
	set_dp(500);
	set_cp(0);
	set_pp(350);
	set_sp(350);
	set_walk_speed(3);
	set_attack_speed(20);
        set_max_seek(8);

        setup();
        set_char_type(FIGHTER_TYPE);  
}


// 函数：死亡奖励(在线更新)
void win_bonus( object who )
{
	int p,size,i;
	object owner,me=this_object();
	
	if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return ;

	owner = get_owner();
	if ( objectp(owner) )
	{
		owner->add_hate(1);
		owner->set("guard",owner->get("guard")-({me}));
	}
	NPC_NPC_D->win_bonus(me,who);
}

int perform_action( object who ) 
{
	object me=this_object();


	if ( me->get_char_picid() == 602 )
	{
//		if( !inside_screen_2(me, who) ) return 1;
//	        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 1;    // 执行成功
		return PF_FILE_01611->perform_action_npc( me, who );
	}
	return 0;
}

//法术攻击
int perform_done_npc(object me, object who)
{
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 2813, 1, OVER_BODY, PF_ONCE );    // 技能成功
	CHAR_FIGHT_D->cast_done(me, who);
	return 2;
}
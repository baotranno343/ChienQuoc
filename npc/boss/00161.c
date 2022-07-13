
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>

inherit SLAVE;
int silent,attract;
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return 0901; }
// 函数：获取召唤兽类型
int get_zombie_type() { return 99; }     // 判断种类
//int is_general_slave() { return 1; }

int is_caster() { return get("caster"); }

int is_zombie() { return 0; }  

int get_hp_attract() { return attract; }
// 函数：构造处理
void create()
{
        set_name("Du Hồn Quỷ");

        set_level(70);
	set_max_hp(10000);
	set_ap(0);
	set_dp(150);
	set_cp(0);
	set_pp(150);
	set_sp(500);
	set_walk_speed(2);
	set_attack_speed(20);
        set_max_seek(8);

        set_head_color(0x5000);

        setup();
	set("anti_05311",1);	
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
	int i,x,y,x1,y1,z2,x2,y2,damage;
	object me=this_object();
	object user, owner, *char;
//	y = get_y(me);  x = get_x(me); 
//	y1 = get_y(who);  x1 = get_x(who); 
	if ( gone_time(silent) >= 2 && distance_between(me, who) == 1 )
	{
		silent = time();
		attract=50+random(51);
		who->add_hp(-attract);
		who->add_mp(-(50+random(51)));
		who->add_yuan(-1);
	}
	else attract = 0;
        if ( !who->get("anti_slow") )
        {
	        if(     get_effect(who, EFFECT_CHAR_SLOW)
	        ||      get_effect(who, EFFECT_CHAR_SLOW_0) ) return 2;    // 执行成功
                set_effect(who, EFFECT_CHAR_SLOW, 6);
                send_user( who, "%c%w%w%c", 0x81, 9012, get_effect_3(who, EFFECT_CHAR_SLOW), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9012, 1, EFFECT_BAD );
                send_user(who, "%c%c%c", 0x3d, 241, 1);    // 更改走路步数
        }

	return 0;
}

//法术攻击
int perform_done_npc(object me, object who)
{
	return 2;
}


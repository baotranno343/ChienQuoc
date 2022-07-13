#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <public.h>
#include <time.h>
#include <effect.h>

inherit NPC;
int is_boss() { return 1; }
int is_nianshou() { return 1; }
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return 8100; }

// 函数：构造处理
void create()
{
        set_name("Niên Thú");

	set_char_type(FIGHTER_TYPE_2);

	set_level(150);
	set_max_hp(5000+random(1000));
	set_walk_speed(4);  
	set_attack_speed(25);

        set("no_sk04211",1);	//变身术对其没有效果
        set("anti_sleep",1);	//不会昏迷
        set("anti_no_move",1);	//不会冻结

        setup();

	set_char_type(FIGHTER_TYPE_2);

}

// 函数：自动战斗(遇玩家时调用)
void auto_fight( object who ) { }

void heart_beat_walk()
{
	object me=this_object();
/*	if ( get_char_type() == OFFICER_TYPE )	//普通状态
	{
		return ;
	}*/
	if( !get_effect(me, EFFECT_CHAR_NO_PF_0) )		//不沉默
	{
		set_effect(me, EFFECT_CHAR_NO_PF_0, 3600);
	}
	if( !get_effect(me, EFFECT_CHAR_WOUND_0) )		//不负伤
	{
		set_effect(me, EFFECT_CHAR_WOUND_0, 3600);
	}	
	if( !get_effect(me, EFFECT_CHAR_FAINT_0) )		//不眩晕
	{
		set_effect(me, EFFECT_CHAR_FAINT_0, 3600);
	}
	if( !get_effect(me, EFFECT_CHAR_SHUT_0) )		//不囚禁
	{
		set_effect(me, EFFECT_CHAR_SHUT_0, 3600);
	}
	if( !get_effect(me, EFFECT_CHAR_DREAM_0) )		//不梦游
	{
		set_effect(me, EFFECT_CHAR_DREAM_0, 3600);
	}
	if( !get_effect(me, EFFECT_CHAR_LAZY_0) )		//不延缓
	{
		set_effect(me, EFFECT_CHAR_LAZY_0, 3600);
	}
	if( !get_effect(me, EFFECT_USER_BURN_0) )		//不燃烧
	{
		set_effect(me, EFFECT_USER_BURN_0, 3600);
	}
	if( !get_effect(me, EFFECT_CHAR_BLOOD_0) )		//不流血
	{
		set_effect(me, EFFECT_CHAR_BLOOD_0, 3600);
	}
	::heart_beat_walk();	
}

// 函数：死亡奖励
void win_bonus( object who ) { "sys/party/chunjie"->win_bonus_callout( this_object(), who ); }



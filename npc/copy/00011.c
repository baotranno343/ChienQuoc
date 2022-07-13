
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit BADMAN;
private int iAtt,iCast;

int set_attack(int i)
{
	return iAtt = i;
}
int set_caster(int i)
{
	return iCast = i;
}

// 函数：远程攻击的怪
int is_caster() { return iCast; }
//副本怪
int is_copy_npc() { return 1; }

// 函数：远程攻击的怪
// int is_caster() { return 1; }

// 函数：是否允许移动
// int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：跟随对手(心跳之中调用)
// void follow_user() { }    // 禁止跟随敌人


// 函数：构造处理
void create()
{
        set_name("幻境妖");

//        set_char_type(FIGHTER_TYPE);    // init_level 要用到
//        
//        set_head_color(0x0);
//
//        NPC_ENERGY_D->init_level( this_object(), 1+ random(2) );    // 
//        set_max_seek(4);

        setup();
	set("anti_05311",1);	//不能迷魂
//        set_char_type(FIGHTER_TYPE);    // 重设类型
}

//// 函数：获取装备代码
//int get_weapon_code() { return UNARMED; }
//
//// 函数：特技攻击对手
//int perform_action( object who ) { return 0; }    // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：掉宝奖励
void drop_items( object who ) 
{
	"sys/copy/mirror"->npc_die( this_object(), who ); 
}
//延迟X秒出现
void delay_appear(int z,int x ,int y,int sec)
{
	call_out("add_to_scene",sec,z,x,y);
}


// 函数：特技攻击对手
int perform_action( object who ) 
{ 
	if ( iAtt == 1 )
		return PF_FILE_04232->perform_action_npc( this_object(), who ); //五雷
	else if ( iAtt == 2)
		return PF_FILE_01611->perform_action_npc( this_object(), who ); //暗器
}

// 函数：修正奖励队伍,在副本内的都奖励
object *correct_bonus_team( object *team )
{
        object *team2,me;
        int i, size,z;

	me = this_object();
	z = get_z(me);
        team2 = ({ });
        size = sizeof(team);
        if( !size ) return team2;
        for( i = 0; i < size; i ++ ) 
                if( team[i] && !team[i]->is_die() && z == get_z(team[i]) )  
                        team2 += ({ team[i] });
        return team2;
}

// 函数：判断可以战斗
int can_fight( object who )
{ 
	object me=this_object(),owner;

	owner = who->get_owner();
	if ( !owner ) 
		owner = who;
	if ( me->get("team_id") != owner->get_team_id() )
		return 0;
	return ::can_fight(who);	
}
// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
	object me=this_object(),owner;

	owner = who->get_owner();
	if ( !owner ) 
		owner = who;
	if ( me->get("team_id") != owner->get_team_id() )
		return 0;
	return ::can_be_fighted(who);	
}


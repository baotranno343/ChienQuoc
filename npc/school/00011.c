
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>
#include <shouxi.h>

inherit BADMAN;
private string RealName;                    // 实名
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return get("PicId"); }
// 函数：获取召唤兽类型
int get_zombie_type() { return 99; }     // 判断种类
int is_tigerking_slave() { return 1; }

int is_zombie() { return 0; }  
void kickout1();

// 函数：构造处理
void create()
{
        set_name("Đại Đệ Tử cao quí");

        set_level(90);
	set_max_hp(8000);
	set_ap(550);
	set_dp(760);
	set_cp(100);
	set_pp(700);
	set_sp(600);
	set_walk_speed(3);
	set_attack_speed(10);
        set_max_seek(4);
        set_2( "talk", ([
                "kickout"            : (: kickout1 :),  
        ])); 
        setup();
        set_char_type(FIGHTER_TYPE_2);  
}
// 函数：获取人物名称
string get_real_name() { return RealName; }

// 函数：设置人物名称
string set_real_name( string name ) 
{ 
        return RealName = name; 
}
// 函数：获取人物名称
string get_short() 
{ 
	if ( stringp(get_real_name()) )
		return get_real_name() + "|" + get_name();
	else
		return get_name();
}
void kickout(object who)
{
	int x,y,z,p;
	object me,owner;
	
	me = this_object();

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;        	
	if (!who) return;		

	if (get_z(who) == get_z(me) )
	{ 	        
		z = who->get_2("shouxi.z");
		x = who->get_2("shouxi.x");
		y = who->get_2("shouxi.y");
		if( !( p = get_valid_xy( z, x, y, IS_CHAR_BLOCK ) ) ) return ;
		x = p / 1000;  y = p % 1000;
		who->add_to_scene(z, x, y, 3);
		if ( who->get_save("shouxiwin") )
		{
			SHOUXI->add_elect(who);
			who->delete_save("shouxiwin");
		}
	}
			
}

//是否战败
int fight_over(object player, object npc)
{
	if ( player->is_die() )
		return 0;
	if ( npc->get_hp() <= npc->get_max_hp() /10 )	//胜利
	{
		npc->set_char_type(NPC_TYPE);
		npc->set_enemy(0);
		player->set_enemy(0);
		player->set_save("shouxiwin",1);
//		send_user(player,"%c%s",';',"你战胜了首席大弟子！");
		send_user(player,"%c%c%w%s",':',3,0,sprintf("Ngươi đã chiến thắng Thủ Tịch Đại Đệ Tử !\n"ESC"Rời khỏi\ntalk %x# kickout",getoid(npc)));
//		kickout(player);
		return 1;
	}
	if ( player->get_hp() <= player->get_max_hp()/10 )	//失败
	{
		npc->set_char_type(NPC_TYPE);
		npc->set_enemy(0);
		player->set_enemy(0);   
//		send_user(player,"%c%s",';',"你的挑X战失败，希望你再接再厉！");
		send_user(player,"%c%c%w%s",':',3,0,sprintf("Ngươi đã thất bại, ngươi cần cố gắng thêm nữa !\n"ESC"Rời khỏi\ntalk %x# kickout",getoid(npc)));
//		kickout(player);
		return 1;
	}
	return 0;	
}

int can_fight( object who ) 
{ 
	if ( fight_over(who,this_object()) == 1 )
		return 0;
        return ::can_fight(who); 
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner, me;
        string leader;
        int id;
        me = this_object();

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;
        if( who->get_enemy() == me ) 
        {
		if ( fight_over(who,me) == 1 )
			return 0;        	
        	return 1;
        }


	if (me->get("user")==who->get_number())
	{
		if ( fight_over(who,me) == 1 )
			return 0;		
		return 1;            
	}
        
        return 0;
}

void kickout1() { kickout(this_player()); }

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object owner, *team, *team2, oldcity;
        string id, id2, leader;
        int i, size, p, x, y, z, oldz;


        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;        	
	if (!who) return;
	who->set_save("shouxiwin",1);
	me->kickout(who);
}
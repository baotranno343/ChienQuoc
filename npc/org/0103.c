#include <city.h>
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <music.h>
#include <task.h>

inherit NPC;
int iAtt,iWalk;
int summon_slave(object me );
// 函数：被剿强盗
int is_robber() { return 1; }

// 函数：门派人物
int is_boss() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Ác Nhân" + NPC_NAME_D->get_thief_name() );
        set_char_picid(1000);    // 蒙面人
	
        setup();
        set( "birthday", time() );
        set_char_type(FIGHTER_TYPE); 
}

// 函数：复位处理
void reset() 
{
        string member ;
        int number;
        object owner;
        object me = this_object();
        if( gone_time( get("birthday") ) >= 3600 )    // 30 分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }
        else
        {
                member = sprintf("%d",get("user"));
                owner = find_char( member);
                if (!owner)
                {
                        remove_from_scene();
                        destruct( this_object() );                	
                }
                else
                {
                	if (owner->get_save_2("orgtask2.id")!=sprintf("%x#", getoid(me)))
                	{
	                        remove_from_scene();
	                        destruct( this_object() );                       		
                	}
                }
        }
}

void init_level(int level)
{
	object me = this_object();
	NPC_ENERGY_D->init_level( me, level-5 );    // 
	me->set_max_hp(me->get_max_hp()*3/2);
	me->set_hp(me->get_max_hp());
	me->set_ap(me->get_ap()*12/10);
	me->set_walk_speed(4);
	me->set_attack_speed(20);
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner;
        object me = this_object();
        string leader, id;
	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() ) return 0;
        if( who->get_enemy() == me ) return 1;
        if (who->get_number()== me->get("user") ) return 1;
        
        if(   ( leader = who->get_leader() )
        &&    ( owner = find_player(leader) )
        &&    owner->get_number()== me->get("user")  )
                return 1;
        send_user( who, "%c%c%w%s", ':',3,get_char_picid(), get_name() + "：\n    Nói cho cái kia "+ me->get("target")+"，Lão tử không sợ trời không sợ đất, có bản lĩnh phóng ngựa lại đây !" );
        return 0;
}
int can_fight( object who ) 
{ 
        object owner;
        object me = this_object();
        string leader, id;
	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() )
	{
		set_enemy(0);
		return 0;
	}
        if( who->get_enemy() == this_object() ) return 1;

        if (who->get_number()== me->get("user") ) return 1;
	set_enemy(0);
        return 0;
}

// 函数：死亡奖励
void win_bonus( object who )
{
        object owner;
        object orgnpc;
        object me = this_object();
        string leader, id, name;
        int number, order, level, cash, exp, pot;
	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() ) return;
        if (who->get_number()!= me->get("user") )
        {
        	leader = who->get_leader();
        	if (!leader || leader=="") return;
        	who = find_player(leader);
        	if (!who) return;
        	if (who->get_number()!= me->get("user") ) return;
        }
        if (who->get_save_2("orgtask2.type")!=6) return;
        name = who->get_org_name();
        if (name=="") return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
	if (!objectp(orgnpc)) return;
	order = who->get_save_2("orgtask2.order");
	level = who->get_level();
	order ++;	
	exp = (level*8+order*order*level*4)*3/5;
	exp = exp * who->get_online_rate()/100;
	pot = order*10+level;
	pot = pot * who->get_online_rate()/100;
	cash = (500+level*6*(order-1))*3/6;	
	cash = cash * who->get_online_rate()/100;	
	number = who->get_number();        
        orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number)+1+order*2/9);
	orgnpc->add_stable(2);
	orgnpc->add_favour(2);        
	who->add_potential(pot);
	who->add_cash(cash);
	who->add_exp(exp);	
        send_user(who, "%c%s", ';', sprintf("Bạn nhận được kinh nghiệm %d, tiềm năng %d, ngân lượng %d, cống hiến bang phái %d, độ yên ổn tăng 2 điểm, nhân khí tăng 2 điểm", exp, pot, cash, 1+order*2/9));
        who->delete_save_2("orgtask2");	
        who->delete_2("orgtask2");	
	if (order>=10) 
	{
		order = 0;
		if (random100()<5*who->get_online_rate()/100) "/quest/box"->give_box(who);
	}
	who->set_save_2("orgtask2.order", order);        
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 6, "" );  
	send_user( who, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "" );				
        	
}


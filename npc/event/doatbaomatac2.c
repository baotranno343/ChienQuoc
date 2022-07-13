#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <public.h>
#include <time.h>

inherit BADMAN;

object robber;
int get_id_color() { return 0107215; }
// 函数：获取人物造型
int get_char_picid() { return 8013; }
void do_bonus();
// 函数：构造处理
void create()
{
        set_name("Đoạt Bảo Mã Tặc");
        set_2( "talk", ([
                 "bonus"         : (: do_bonus :),
        ]) );
	set_char_type(FIGHTER_TYPE_2);
	set_level(20);
	set("birthday",time());
        setup();
	set_char_type(FIGHTER_TYPE_2);

}
// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner, me, *team;
        string leader;
        int id, size;
        me = this_object();

        if( who->get_enemy() == this_object() ) return 1;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;
			team=who->get_team();
		      size=sizeof(team);
			  if(size>1)
		     {
		     	send_user(who,"%c%c%w%s",':',3,8013,"Đoạt Bảo Mã Tặc: \nĐi một mình mới có thể tấn công được ta. \n" ESC"Xác nhận");
		     	return 0;		     	          	      
		     }
	if (me->get("user")==who->get_number())
		return 1;            
        
        return 0;
}
void do_fight(int sec)
{
	object me = this_object(),who;
	who = me->get("fight");
	if ( !who ||  get_z(who) != me->get("doatbao_z") )
	{
		destruct(me);
		return ;	
	}
	sec--;
	if ( sec > 0 )
	{
		call_out("do_fight",1,sec);
	}
	else
	{
		me->add_to_scene(get("doatbao_z"),get("doatbao_x")+1+random(3),get("doatbao_y")+1+random(3),);	
	}		
}
// 函数：死亡奖励
void win_bonus( object who ) { "sys/party/doatbaomatac"->win_bonus_callout( this_object(), who ); }



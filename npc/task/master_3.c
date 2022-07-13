
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>

inherit BADMAN;

// 函数：被剿强盗
int is_robber() { return 1; }

// 函数：门派人物
int is_boss() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Đạo Tặc" );
        set_char_picid(8000);    // 蒙面人       

        setup();

        set( "birthday", time() );
}

void reset()
{
	__FILE__->reset2(this_object());
}

// 函数：复位处理
void reset2(object me) 
{
        string member ;
        int number;
        object owner;
        if( gone_time( me->get("birthday") ) >= 3600 )    // 60 分钟
        {
        	number = me->get("user");
                me->remove_from_scene();
                destruct( me );
                owner = find_any_char(sprintf("%d", number));
                if (owner) TASK_MASTER_D->send_task_intro(owner);
        }
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
        if( who->get_enemy() == this_object() ) return 1;

        if(   ( leader = who->get_leader() )
        &&    ( owner = find_player(leader) )
        &&      me->get("user") ==  owner->get_number() )
        {     
                return 1;
        }
	if (me->get("user")==who->get_number())
	{			
		return 1;            
	}

        send_user( who, "%c%s", '!', get_name() + "Không nghĩ người giống nhau" );
        return 0;
}

int can_fight( object who ) 
{ 
        object owner, me;
        string leader;
        int id;
        me = this_object();

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;
        if( who->get_enemy() == this_object() ) return 1;

        if(   ( leader = who->get_leader() )
        &&    ( owner = find_player(leader) )
        &&      me->get("user") ==  owner->get_number() )
        {     
                return 1;
        }

	if (me->get("user")==who->get_number())
	{			
		return 1;            
	}
	
        return 0;
}

// 函数：特技攻击对手
int do_perform_action( object who ) 
{ 
        object me = this_object();

        switch( get_fam_name() )
        {
      default : return 0;
case "Đào Hoa Nguyên" : if( get_level() >= 36 && random(100) < 5 )
                {
                        if( random(2) ) return PF_FILE_02114->main_npc_action(me, who); 
                        else return PF_FILE_02117->main_npc_action(me, who); 
                }
                else if( get_level() >= 33 && random(100) < 5 )
                        return PF_FILE_02114->main_npc_action(me, who); 
                return 0;
  case "Thục Sơn" : if( get_weapon_code() == BLADE )
                {
                        if( get_level() >= 15 && random(100) < 5 )
                                return PF_FILE_02212->main_npc_action(me, who); 
                }
                else if( get_weapon_code() == SWORD )
                {
                        if( get_level() >= 27 && random(100) < 5 )
                        {
                                if( random(2) ) return PF_FILE_02313->main_npc_action(me, who); 
                                else return PF_FILE_02314->main_npc_action(me, who); 
                        }
                        else if( get_level() >= 19 && random(100) < 5 )
                                return PF_FILE_02313->main_npc_action(me, who); 
                }
                return 0;
case "Cấm Vệ Quân" : if( get_weapon_code() == SPEAR )
                {
                        if( get_level() >= 16 && random(100) < 5 )
                                return PF_FILE_02412->main_npc_action(me, who); 
                }
                else if( get_weapon_code() == STICK )
                {
                        if( get_level() >= 47 && random(100) < 5 )
                        {
                                if( random(2) ) return PF_FILE_02513->main_npc_action(me, who); 
                                else return PF_FILE_02514->main_npc_action(me, who); 
                        }
                        else if( get_level() >= 22 && random(100) < 5 )
                                return PF_FILE_02513->main_npc_action(me, who); 
                }
                return 0;
  case "Đường Môn" : if( get_level() >= 35 && random(100) < 5 )
                        return PF_FILE_02615->main_npc_action(me, who); 
                else    return PF_FILE_01611->main_npc_action(me, who); 
  case "Mao Sơn" : if( !objectp( me->get("soldier") ) )
                {
                        if( get_level() >= 42 ) PF_FILE_04133->main_npc_action(me, who);
                        else if( get_level() >= 28 ) PF_FILE_04132->main_npc_action(me, who);
                        else if( get_level() >= 16 ) PF_FILE_04131->main_npc_action(me, who);
                }
                return 1;    // 只召唤，不攻击
case "Côn Luân" : if( get_level() >= 38 && random(100) < 3 )
                {
                        if( get_effect(me, EFFECT_CHAR_CHANGE) < 1 ) PF_FILE_04251->main_npc_action(me, who);
                }
                else    PF_FILE_04232->main_npc_action(me, who);
                return 1;
case "Vân Mộng Cốc" : return 0;    // 普通攻击，带毒
        }
        return 0;
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object owner, *team;
        string id, id2, leader, *team2;
        int i, size, status;

	owner = who;
	who = find_char(sprintf("%d",me->get("user")));
	if (!who) return;
	if (who->get_save_2("mastertask.type")==12)
	{
		if ( distance_between(who, me) > 31 )
		{
			who->set_save_2("mastertask.type", 0);
//			who->set_save_2("mastertask.time", 0);
			team2 = explode(who->get_save_2("mastertask.target"),"|");
			for(i=0,size=sizeof(team2);i<size;i++)
			{
				owner = find_char(team2[i]);
				if ( !objectp(owner) || owner == me )
					continue;
				owner->remove_from_scene();
				owner->before_destruct();
				destruct(owner);				
			}
			send_user(who, "%c%s", '!', "Ngươi xa rời mục tiêu quá xa, nhiệm vụ thất bại !");
			return ;			
		}		
		who->add_save_2("mastertask.status", 1);
		status = who->get_save_2("mastertask.status");
		if (status>=4)		
		{
			TASK_MASTER_D->send_task_desc(who,1);
			send_user(who, "%c%s", '!', "Nhiệm vụ hoàn thành, hãy tìm Tổng Quản Vương Phủ ");
		}
		else
		{
			TASK_MASTER_D->send_task_desc(who,0);
			send_user(who, "%c%s", '!', sprintf("Còn lại %d mục tiêu chưa hoàn thành", 4 - status ));
		}
		
	}
			
}

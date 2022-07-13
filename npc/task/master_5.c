
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>

inherit BADMAN;
void kickout();
// 函数:被剿强盗
int is_robber() { return 1; }

// 函数:门派人物
int is_boss() { return 1; }

// 函数:构造处理
void create()
{
        set_name( "Môn phái đệ tử" );

        setup();
        set_2( "talk", ([
                "kickout"            : (: kickout :),  
        ])); 
        set( "birthday", time() );
}
//是否战败
int fight_over(object player, object master)
{
	if ( player->is_die() )
		return 0;
	if ( master->get_hp() <= master->get_max_hp() /20 )	//胜利
	{
		master->set_char_type(NPC_TYPE);
		master->set_enemy(0);
		player->set_enemy(0);
		player->set_save_2("mastertask.status",99);
		send_user(player,"%c%c%w%s",':',3,get_char_picid(),sprintf("%s:\n    Quý phái quả nhiên võ nghệ cao siêu, tại hạ thật sự không thể thắng, mời trở về đi !\n"ESC"Rời tỷ võ\ntalk %x# kickout",master->get_name(),getoid(master)));
		return 1;
	}
	if ( player->get_hp() <= player->get_max_hp()/20 )	//失败
	{
		master->set_char_type(NPC_TYPE);
		master->set_enemy(0);
		player->set_enemy(0);    
		if ( player->get_gender() == 1 )
			send_user(player,"%c%c%w%s",':',3,get_char_picid(),sprintf("%s:\n    Vị sư huynh này, chả lẽ võ công quý môn phái lại xuống dôc như thế ư, ngươi hãy nghỉ ngơi đi ! \n"ESC"Rời tỷ võ\ntalk %x# kickout",master->get_name(),getoid(master)));
		else
			send_user(player,"%c%c%w%s",':',3,get_char_picid(),sprintf("%s:\n    Vị sư tỷ này, chả lẽ võ công quý môn phái lại xuống dôc như thế ư, ngươi hãy nghỉ ngơi đi ! \n"ESC"Rời tỷ võ\ntalk %x# kickout",master->get_name(),getoid(master)));
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
// 函数:复位处理
void reset() 
{
        string member ;
        object owner, who, oldcity;
        int number, oldz;
        if( gone_time( get("birthday") ) >= 3600 )    // 60 分钟
        {
        	oldz = get_z(this_object());
                oldcity = get_map_object(oldz);
                remove_from_scene();
                NEWBIE->destruct_virtual_map(oldcity, oldz);
        }

}

// 函数:可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner, me;
        string leader;
        int id;
        me = this_object();

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;
        if( who->get_enemy() == this_object() ) 
        {
		if ( fight_over(who,this_object()) == 1 )
			return 0;        	
        	return 1;
        }


	if (me->get("user")==who->get_number())
	{
		if ( fight_over(who,this_object()) == 1 )
			return 0;		
		return 1;            
	}
        
        return 0;
}

// 函数:特技攻击对手
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

// 函数:死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数:死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object owner, *team, *team2, oldcity;
        string id, id2, leader;
        int i, size, p, x, y, z, oldz;

//        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;        	
	if (!who) return;
	if (who->get_save_2("mastertask.type")==10)
	{
                oldz = get_z(who);
                oldcity = get_map_object(oldz);     	        
		send_user( who, "%c%s", ':', sprintf("%s:\nĐạ tạ sư huynh thủ hạ lưu tình, xin hãy quay về !", who->get_name(), ) );
		who->set_save_2("mastertask.status", 1);
		z = who->get_2("mastertask.z");
		x = who->get_2("mastertask.x");
		y = who->get_2("mastertask.y");
		if( !( p = get_valid_xy( z, x, y, IS_CHAR_BLOCK ) ) ) return ;
		x = p / 1000;  y = p % 1000;
		who->add_to_scene(z, x, y, 3);
		NEWBIE->destruct_virtual_map(oldcity, oldz);
		who->set_save_2("mastertask.status",99);
		TASK_MASTER_D->send_task_desc(who,1);
	}
			
}

void init_pic(object me, int type)
{
	int * armor_code = ({  20000, 20100, 30000, 30100, 40000, 40100, 50000, 50100, 80000, 80100, 60000, 60100, 70000, 70100, 10000, 10100, 10200, 10300 });
        int pic;
        type = type /10 - 1;
        pic = armor_code[type*2];
        me->set_armor_code(pic);
}

void kickout()
{
	__FILE__->kickout_call(this_player(),this_object());
}

void kickout_call( object who, object me )
{
        object owner, *team, *team2, oldcity;
        string id, id2, leader;
        int i, size, p, x, y, z, oldz;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;        	
	if (!who) return;		

	if (who->get_save_2("mastertask.type")==10)
	{ 	        
		z = who->get_2("mastertask.z");
		x = who->get_2("mastertask.x");
		y = who->get_2("mastertask.y");
		if( !( p = get_valid_xy( z, x, y, IS_CHAR_BLOCK ) ) ) return ;
		x = p / 1000;  y = p % 1000;
		who->add_to_scene(z, x, y, 3);
		if (who->get_save_2("mastertask.status")==99)
		{
                	oldz = get_z(who);
                	oldcity = get_map_object(oldz);    
	                me->remove_from_scene();
	                NEWBIE->destruct_virtual_map(oldcity, oldz);
	                destruct(me);
	                TASK_MASTER_D->send_task_desc(who,1);
		}

	}
			
}
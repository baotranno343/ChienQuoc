
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <task.h>

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
   
// 函数：被剿强盗
int is_robber() { return 1; }

// 函数：门派人物
int is_boss() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Thủ Vệ" );

        setup();

        set( "birthday", time() );
}

// 函数：复位处理
void reset() 
{
        string member ;
        object owner, who, oldcity;
        int number, oldz;
        if( gone_time( get("birthday") ) >= 3600 )    // 30 分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner, me;
        string leader;
        int id;
        me = this_object();

        if( who->get_enemy() == this_object() ) return 1;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;

	if (me->get("user")==who->get_number())
		return 1;            
        
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
//case "Côn Luân" : if( get_level() >= 38 && random(100) < 3 )
//                        return PF_FILE_04232->main_npc_action(me, who); 
//                else    return PF_FILE_01611->main_npc_action(me, who); 				
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
        object owner,npc, *all;
        int i, size;

        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;        	
	if (!who) return;
	all = get_scene_object_2(me, USER_TYPE);
	size = sizeof(all);
	for (i=0;i<size;i++) if (who=all[i])
	{
		if ( me->get("user") == who->get_number() )
		{
			npc = new("/npc/90/box");	
			if ( !npc )
				return ;
			npc->set("user",who->get_number());
			npc->set("level",me->get_level());
			npc->add_to_scene(get_z(me),get_x(me),get_y(me));
			break;
		}
	}			
}

void do_fight(int sec)
{
	object me = this_object(),who;
	who = me->get("fight");
	if ( !who ||  get_z(who) != me->get("f_z") )
	{
		destruct(me);
		return ;	
	}
	sec--;
	if ( sec > 0 )
	{
		tell_user(who,"Sau %d giây %s sẽ xuất hiện, mời chuẩn bị ứng chiến!",sec,get_name());
		call_out("do_fight",1,sec);
	}
	else
	{
		me->add_to_scene(get("f_z"),get("f_x"),get("f_y"),);	
	}		
}

// 函数：特技攻击对手
int perform_action( object who ) 
{ 
	object me = this_object();
	if( get_z(who)!=get_z(me) || !inside_screen_2(me, who)  )
		return 0;
	if ( iAtt == 1 )
		return PF_FILE_04232->perform_action_npc( this_object(), who ); //五雷
	else if ( iAtt == 2)
		return PF_FILE_01611->perform_action_npc( this_object(), who ); //暗器
}

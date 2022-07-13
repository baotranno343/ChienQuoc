
#include <ansi.h>
#include <item.h>
#include <npc.h>
#include <city.h>
#include <equip.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <public.h>

inherit ITEM;
inherit COMBINED;
inherit "/inh/equip/equip";

void check_seal( object item) ;

// 函数：Trận Kì识别
int is_flag() { return 1; }

int get_hide() {return 0;}

// 函数：自动装备类型
int is_auto_equip() { return 1; }

// 函数：Trận Kì识别
int get_item_type() { return ITEM_TYPE_FLAG; }

// 函数：获取装备类型
int get_equip_type() { return HAND_TYPE; }

// 函数：叠加上限
int get_max_combined() { return 10000; }

// 函数：获取装备描述
string get_equip_string() { return "[Môn phái thích hợp dùng]"; }

// 函数：获取耐久度
int get_lasting() { return 10; }

// 函数：获取最大耐久度
int get_max_lasting() { return 10; }

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name( "Trận Kì" );
        set_picid_1(0591);
        set_picid_2(0591);
        set_unit( "把" );
        set_value(60);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Vật phẩm dùng để bố trận";
}

// 函数：阵法开始
int do_start( object who )
{
        object item = this_object();
	check_seal(item);        
}


// 函数：心跳处理(循环)(在线更新)
void check_seal( object item)    // 每1秒处理
{
        object *char, owner, who, player, map, nguoichoi1, nguoichoi2;
        int cp, pp, pp0, pp2, damage;
        int z, x, y, d, i, size;
        int cp0, cp2, asp, dsp;
        int rate, id, double_flag, random;        
        
        remove_call_out( "check_seal" );

        z = get_z(item);  x = get_x(item);  y = get_y(item);  d = get_d(item);

        if(  !( owner = item->get_owner() )    // 有否主人
        ||      gone_time( item->get(SEAL_START) ) > item->get(SEAL_INTERVAL) )    // 阵法完否
        {
//              remove_map_seal( z, x, y, get_d(item) );    // 1: 3x3, 2: 5x5
                remove_block(z, x, y, SEAL_BLOCK);

                char = get_scene_object_2(item, USER_TYPE);

                switch( item->get(SEAL_AREA) )
                {
               case 1 : send_user( char, "%c%w%w%w%c%c%c", 0x4f, x, y, 
                               5912, 1, OVER_BODY, PF_STOP );
                        break;
               default : send_user( char, "%c%w%w%w%c%c%c", 0x4f, x, y, 
                               5913, 1, OVER_BODY, PF_STOP );
                        break;                        
                }

                if (item->get_name()=="Trận Kì") 
                {
                	destruct(item);
                }
                return;
        }

        char = get_range_object(z, x, y, d, USER_TYPE) + get_range_object(z, x, y, d, CHAR_TYPE) - ({ owner });

        cp = item->get(SEAL_CP);
	cp0 = cp;
	cp2 = cp;
        for( i = 0, size = sizeof(char); i < size; i ++ ) if( who = char[i] )
        {
                if( !who->can_be_fighted(owner) || !owner->can_fight(who) ) continue;
		map = get_map_object(get_z(owner));
	if ( owner->is_user() && who->is_user() && ( get_z(owner)<885 || map->is_org_map() || map->is_copy_scene() || map->is_pvp() ) ) 
	{	
		if ( owner->is_user() && who->is_user() && owner->get_attack_mode()!=1 && owner->get_pk()<100 && who->get_pk()<100 && !get_effect(who, EFFECT_USER_PK)  )
		{
	    owner->set_char_type( PK_TYPE );    // 主动ＰＫ状态
        set_effect(owner, EFFECT_USER_PK, 180);
		}
		else if ( owner->is_user() && who->is_user() && owner->get_attack_mode()!=1 && (owner->get_pk()>=100||get_effect(who, EFFECT_USER_PK)||who->get_pk()>=100) )
		{
	    set_effect(owner, EFFECT_USER_PK, 0);
		}
	}
	if ( owner->is_user() && who->is_pet() && ( get_z(owner)<885 || map->is_org_map() || map->is_copy_scene() || map->is_pvp() ) ) 
	{	
		nguoichoi1 = who->get_owner();	
		if ( owner->is_user() &&  who->is_pet() && nguoichoi1->is_user() && owner->get_attack_mode()!=1 && owner->get_pk()<100 && nguoichoi1->get_pk()<100 && !get_effect(nguoichoi1, EFFECT_USER_PK)  )
		{
	    owner->set_char_type( PK_TYPE );    // 主动ＰＫ状态
        set_effect(owner, EFFECT_USER_PK, 180);
		}
		else if ( owner->is_user() && who->is_pet() && nguoichoi1->is_user() && owner->get_attack_mode()!=1 && (owner->get_pk()>=100||get_effect(nguoichoi1, EFFECT_USER_PK)||nguoichoi1->get_pk()>=100) )
		{
	    set_effect(owner, EFFECT_USER_PK, 0);
		}
	}
/*	if ( owner->is_user() && who->is_zombie() && ( get_z(owner)<885 || map->is_org_map() || map->is_copy_scene() || map->is_pvp() ) ) 
	{	
		nguoichoi2 = who->get_owner();	
		if ( owner->is_user() &&  who->is_zombie() && nguoichoi2->is_user() && owner->get_attack_mode()!=1 && owner->get_pk()<100 && nguoichoi2->get_pk()<100 && !get_effect(nguoichoi2, EFFECT_USER_PK)  )
		{
	    owner->set_char_type( PK_TYPE );    // 主动ＰＫ状态
        set_effect(owner, EFFECT_USER_PK, 180);
		}
		else if ( owner->is_user() && who->is_zombie() && nguoichoi2->is_user() && owner->get_attack_mode()!=1 && (owner->get_pk()>=100||get_effect(nguoichoi2, EFFECT_USER_PK)||nguoichoi2->get_pk()>=100) )
		{
	    set_effect(owner, EFFECT_USER_PK, 0);
		}
	}*/
				
                pp = who->get_pp();  pp0 = who->get_pp_0();  pp2 = pp0 + random(pp - pp0);
                damage = (cp2 * 9 + pp2 * 47) / 50;
                damage = cp2 - cp2 * pp2 / range_value(damage, 1, MAX_NUMBER);                
                damage = CHAR_FIGHT_D->correct_damage_3(item, who, damage, cp);                
		if (who->is_nianshou())
		{
	                send_user( owner, "%c%s", '!', "Kỹ năng không có tác dụng với Niên Thú.");
			damage =0;
		}
                if( who->is_npc() )    // 抄自 /sys/user/fight
                {
                        if( who->get_enemy_4() == owner ) 
                                who->set_attack_time( time() );    // 同一个人：更新持续时间
                        else if( gone_time( who->get_attack_time() ) > 5 )
                        {
                                who->set_enemy_4(owner);
                                who->set_attack_time( time() );    // 不同的人：更新持续敌手
                        }
//                      if( !who->get_max_damage() ) who->init_enemy_damage(owner, 0);    // 记录最强伤害(NPC)
                        if( damage >= who->get_max_damage() ) who->init_enemy_damage(owner, damage);    // 记录最强伤害(NPC)
                        if (who->get_owner()) player = who->get_owner();
                }
                else player = who;
		
                //send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%d%w%c", 0x48, getoid(who), damage, get_d(who), 0, 0, 0 );
                if (player) send_user( player, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage, get_d(who), 0, 0, 0 );
                if (owner) send_user( owner, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage, get_d(who), 0, 0, 0 );
            //    CHAR_DIE_D->not_fight_die(owner, who, damage);
                CHAR_DIE_D->is_enemy_die(owner, who, damage);
        }
        call_out("check_seal", 2, item);
}

// 函数：列示给新玩家(对方进场景)
void show_to_user( object who )
{
        object item = this_object();

        switch( item->get(SEAL_AREA) )
        {
       case 1 : send_user( who, "%c%w%w%w%c%c%c", 0x4f, get_x(item), get_y(item), 
                        5912, 1, OVER_BODY, PF_LOOP );
                break;
      default : send_user( who, "%c%w%w%w%c%c%c", 0x4f, get_x(item), get_y(item), 
                        5913, 1, OVER_BODY, PF_LOOP );
                break;
        }
}

// 函数：删除给玩家看(对方离场景)
void remove_to_user( object who )
{
        object item = this_object();

        switch( item->get(SEAL_AREA) )
        {
       case 1 : send_user( who, "%c%w%w%w%c%c%c", 0x4f, get_x(item), get_y(item), 
                        5912, 1, OVER_BODY, PF_STOP );
                break;
      default : send_user( who, "%c%w%w%w%c%c%c", 0x4f, get_x(item), get_y(item), 
                        5913, 1, OVER_BODY, PF_STOP );
                break;
        }
}

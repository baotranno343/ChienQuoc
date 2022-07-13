
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit NPC;

// 函数：Hoàng Kim Thánh YĐạo Tặc
int is_warrior() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Đạo Tặc" + NPC_NAME_D->get_banditi_name() );
        set_char_picid(0251);    // Đạo Tặc

        switch( random(5) )
        {
		      default : set_weapon_code(UNARMED);  break;
		       case 1 : set_weapon_code(BLADE);  break;
		       case 2 : set_weapon_code(SWORD);  break;
		       case 3 : set_weapon_code(SPEAR);  break;
		       case 4 : set_weapon_code(STICK);  break;
        }
        set_walk_speed(4);
        set_attack_speed(15);

				set_max_seek(4);
        setup();

        set( "birthday", time() );
}

// 函数：复位处理
void reset()
{
        object who;
        string member, id;
        int i, size;

        if( gone_time( get("birthday") ) >= 600 )    // 10 分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }
/*        else
        {
                member = get("user");
		id = sprintf( "%x#", getoid( this_object() ) );
		if( !( who = find_player( member ) ) || who->get_task("warrior") != id ) member = "";
                if( sizeof( member -= ({ "" }) ) < 1 )
                {
                        remove_from_scene();
                        destruct( this_object() );
                }
                else    set("user", member);
        }*/
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner;
        string leader, id;

        if( who->get_enemy() == this_object() ) return 1;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return 0;

        if(   stringp( id = who->get_task("warrior") )
        &&      id == sprintf( "%x#", getoid( this_object() ) ) )
                return 1;

	send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),  "Ngươi không nhìn thấy ta, Ngươi không nhìn thấy ta." );
        return 0;
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object owner, map;
	object item,leader;
        string id, id2,name,owner_id;
        int level, level2, exp, exp2, pot, pot2,time,x,y,z;
        int i, size, p, x1,y1,z1;

        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;

//        id = sprintf( "%x#", getoid(me) );
//	id2 = who->get_task("warrior")

        level = me->get_level();
	
        z = me->get("xy.z");
        x = me->get("xy.x");
        y = me->get("xy.y");

        map = get_map_object( get_z(me) );
        name = map ? map->get_name() : "无名地图";

	z1 = get_z(me);  x1 = get_x(me);  y1 = get_y(me);
	owner_id = who->get_id();
/*        id = who->get_leader();
        if (!id) owner_id = who->get_id();
        else
        {
        	if ( leader = find_player(id ) )
        	{
        		owner_id = leader->get_id();
		}      
		else
			owner_id = who->get_id();  		
	}*/
        p = get_valid_xy(z1, x1, y1, IS_ITEM_BLOCK) ;
        item = new( "/item/98/0246" );
 	item->set_user_id(owner_id);
        item->add_to_scene(z, p / 1000, p % 1000);
        
	if( who )
        {
                send_user( who, "%c%w", 0x0d, MUSIC_TASK );
		write_user( who, ECHO "Nhiệm vụ hoàn thành, tìm vệ đội trưởng.");
		who->delete_task("warrior");
		who->delete_task("warrior_time");
		who->set_task("warrior_bonus",level);		//找卫队长领奖
		who->set_task("warrior_map",name);
		who->set_task("warrior_name",me->get_name());
		who->set_task("warrior_x",x);
		who->set_task("warrior_y",y);
		
        	TASK_BANDITI_D->clear_gold_task_desc(who);
        	TASK_BANDITI_D->send_gold_task_list(who);
	}
}


#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>

inherit NPC;

// 函数：要抓窃贼
int is_thief() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "Thiết Tặc" + NPC_NAME_D->get_thief_name() );
        set_char_picid(1000);    // 蒙面人

        setup();

        set( "birthday", time() );
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：复位处理
void reset() 
{
        object who;
        string *member, id;
        int i, size,iKind;

        if( gone_time( get("birthday") ) >= 1800 )    // 30 分钟
        {
                if(   ( who = find_player( sprintf("%d", get("task") ) ) )
                &&      who->get_quest("thief.flag") == 4    // 3. 失窃任务(人物)
                &&      who->get_quest("thief.thief") == sprintf( "%x#", getoid( this_object() ) ) )
                {
                	iKind = who->get_quest("thief.flag");
                        who->delete_quest("thief.flag");
                        who->delete_quest("thief.time");
                        who->delete_quest("thief.thief");
                        who->delete_quest("thief.z");
                        who->delete_quest("thief.x");
                        who->delete_quest("thief.y");
                        who->delete_quest("thief.count");
                        
		        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_THIEF,iKind,0,"" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_THIEF,iKind,"" ); 
			send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_THIEF,"" );                         
                }
                remove_from_scene();
                destruct( this_object() );
        }
        else
        {
                member = get("user");
                for( i = 0, size = sizeof(member); i < size; i ++ )
                        if( !( who = find_player( member[i] ) ) ) member[i] = "";
                if( sizeof( member - ({ "" }) ) < 1 )
                {
                        if(   ( who = find_player( sprintf("%d", get("task") ) ) )
                        &&      who->get_quest("thief.flag") == 4    // 3. 失窃任务(人物)
                        &&      who->get_quest("thief.thief") == sprintf( "%x#", getoid( this_object() ) ) )
                        {
                        	iKind = who->get_quest("thief.flag");
                                who->delete_quest("thief.flag");
                                who->delete_quest("thief.time");
                                who->delete_quest("thief.thief");
                                who->delete_quest("thief.z");
                                who->delete_quest("thief.x");
                                who->delete_quest("thief.y");
                                who->delete_quest("thief.count");
                                
			        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_THIEF,iKind,0,"" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_THIEF,iKind,"" ); 
				send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_THIEF,"" );                                 
                        }
                        remove_from_scene();
                        destruct( this_object() );
                }
        }
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner;

	if( who->is_npc() && objectp(owner = who->get_owner()) ) who = owner;
	if( who->is_npc() ) return 0;
        if( who->get_enemy() == this_object() ) return 1;

        if( get("task") == who->get_number() ) return 1;

        send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),  get_name() + ":\n    你看不见我……你看不见我……" );
        return 0;
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
        object map, owner, item;
        string *member,cTmp;
        int p, x, y, z,iKind;

        if( !me->can_be_fighted(who) ) return;

        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;

        if( me->get("task") != who->get_number() ) return;

        z = get_z(me);  

        if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) return;

	item = new( "/item/98/9870" );        

        member = ({ sprintf( "%d", who->get_number() ) });
        item->set("user", member);   

        write_user( who, ECHO + me->get_name() + "Kêu lên : đại hiệp xin tha cho ta !\n"
                ECHO "Bạn hiên ngang lẫm liệt nói : Hãy làm người tốt !" );

        send_user( who, "%c%s", '!', sprintf( "Đem" HIY " %s " NOR "giao cho Vương Bổ Đầu", item->get_name() ) );
	
	who->set_quest("thief.name",me->get_name());
	who->set_quest("thief.map",map->get_name());
	who->set_quest("thief.thief",item->get_name());
	who->set_quest("thief.bonus",4);
        item->set( "birthday", me->get("birthday") );
        item->set( "task", who->get_number() );
        
        if( USER_INVENTORY_D->can_carry(who, item)  >=1 )
        {
		cTmp = sprintf("Bạn nhận được " HIY "%s" NOR "！",item->get_name());
		x =item->move(who, -1);
		item->add_to_user(x);
	  	send_user( who, "%c%s", '>', cTmp);        	
        }
        else
        {
        	cTmp = sprintf("" HIY "%s" NOR "rơi trên mặt đất",item->get_name());
		x = get_x(me);  y = get_y(me);
	        if( !( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) ) return;        
	        x = p / 1000;  y = p % 1000;  
	        item->add_to_scene(z, x, y);      
	        map->add_reset(item);    // 加入复位列表
	        send_user( who, "%c%s", '>', cTmp);
	}

	iKind = who->get_quest("thief.flag");
        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_THIEF,iKind,0,"" );
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_THIEF,iKind,"" ); 
	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_THIEF,"" ); 
	TASK_THIEF_D->send_task_list(who);
}


#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit NPC;
int no_die;
int is_christmas() { return 1; }
int no_die() {return no_die;}
void follow_user( object me ) {}

// 函数：构造处理
void create()
{
        set_name( "诡异的飞贼" );
        set_char_picid(0202);    

        setup();

        set( "birthday", time() );
}

// 函数：复位处理
void reset() 
{
        object who;
        string *member, id;
        int i, size,iKind;

        if( gone_time( get("birthday") ) >= 1800 )    // 30 分钟
        {
                if(   ( who = find_player( sprintf("%d", get("task") ) ) )
                &&      who->get_quest("valentine.flag") == 2    // 2. 诡异的飞贼
                &&      who->get_quest("valentine.thief") == sprintf( "%x#", getoid( this_object() ) ) )
                {
                        iKind = who->get_quest("valentine.flag");
                        who->delete_quest("valentine.type");
                        who->delete_quest("valentine.time");
                        who->delete_quest("valentine.thief");
                        who->delete_quest("valentine.z");
                        who->delete_quest("valentine.x");
                        who->delete_quest("valentine.y");
                        who->delete_quest("valentine.count");

		        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_VALENTINE,iKind,0,"" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,iKind,"" ); 
			send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" ); 
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
                        &&      who->get_quest("valentine.flag") == 2    // 2. 诡异的飞贼
                        &&      who->get_quest("valentine.thief") == sprintf( "%x#", getoid( this_object() ) ) )
                        {
                        	iKind = who->get_quest("valentine.flag");
                                who->delete_quest("valentine.type");
                                who->delete_quest("valentine.time");
                                who->delete_quest("valentine.thief");
                                who->delete_quest("valentine.z");
                                who->delete_quest("valentine.x");
                                who->delete_quest("valentine.y");
	                        who->delete_quest("valentine.count");
                                
			        send_user( who, "%c%c%c%w%w%w%s", 0x51, 1, 4,TID_VALENTINE,iKind,0,"" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,iKind,"" ); 
				send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" );                                 
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

        send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),  get_name() + "：\n    你看不见我……你看不见我……" );
        return 0;
}

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
	int p;
	object item,owner;
	if( who->get_quest("valentine.flag") == 2 && who->get_quest("valentine.type") == 1)
	{
		if( owner = who->get_owner() ) who = owner;
	        if( who->is_npc() ) return;
		who->add_exp(50);
		who->set_quest("valentine.bonus",1);
		
		item = new("item/04/0421");
		if ( !item )
			return ;
		p = item->move(who,-1);
		if ( !p )
		{
			destruct(item);	
			return ;
		}
		item->add_to_user(p);
		send_user(who,"%c%s",'!',"得到了神秘的种子");
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"情人节任务" ); 
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,2,"诡异的飞贼(已完成)" ); 	
	}
}


#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 2001; }

// 有自己的do_look函数
int is_self_look() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Bảo Rương");
	set( "birthday", time() );
        setup();
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

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	object item;
	if (who->get_save_2("orgtask2.type")==3 && who->get_save_2("orgtask2.id")==sprintf("%x#", getoid(me)) && who->get_save_2("orgtask2.status")==1)	
	{
		item = present("Di Thất Bảo Vật", who, 1, MAX_CARRY*4);
		if (objectp(item)) return;
		set_effect(who, EFFECT_PROGRESS2, 6);
		who->set_progress_file(__FILE__);	
		who->set_progress_arg(sprintf("%x#", getoid(me)));
		send_user(who, "%c%c%w%s", 0x5a, 0, 6, "Đang mở……");
	}
}

// 函数：对话处理
void into_effect( object who, string arg )
{
	object me, item;	
	int p;
	send_user(who, "%c%c%c", 0x5a, 1, 1);
	if( arg && !( me = find_any_char(arg) ) ) return;
	if (who->get_save_2("orgtask2.type")==3 )	
	{
		item = present("Di Thất Bảo Vật", who, 1, MAX_CARRY*4);
		if (objectp(item)) return;
		item = new("item/01/0004");
		if ( !item ) return;	
		if( USER_INVENTORY_D->can_carry(who, item)  >=1 )
		{
                        p =item->move(who, -1);
                        item->add_to_user(p);		
                        send_user( who, "%c%s", ';', "Bạn nhận được Di Thất Bảo Vật !");
                        who->set_save_2("orgtask2.status", 2);
                        me->remove_from_scene();
			destruct(me);
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 3, "Tống Hồi Bảo Vật Di Thất" );  
		}
		else
		{
                       	destruct(item); 
                       	send_user( who, "%c%s", '!', "您身上没有空位！");				
		}					
	}		
}

void effect_break(object who, string arg)
{
	set_effect(who, EFFECT_OPEN_BOX, 0);
	send_user(who, "%c%c%c", 0x5a, 1, 0);
}

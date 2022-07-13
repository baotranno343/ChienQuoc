
#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <city.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 9306; }

// 函数：构造处理
void create()
{
        set_name("Người Đưa Tin");

        set_2( "talk", ([
                "welcome"    : (: do_welcome :),
        ]));
        setup();
        set( "birthday", time() );
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
                	if (owner->get_2("orgtask2.npc")!=me)
                	{
	                        remove_from_scene();
	                        destruct( this_object() );                       		
                	}
                }
        }

}

// 函数：对话处理
void do_look( object me )
{
	string result;
	object who = this_object();
	if ( me->get_save_2("orgtask2.type")==1  )
	{
		if ( who->get("user")==me->get_number() )
		{
			result = sprintf("%s：\n    Cám ơn ngươi, ta đã đỡ nhiều, ta nhờ người đưa thư tín về bang phái\n", who->get_name());
			result += sprintf(ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome\n", getoid(who));
			result += sprintf(ESC"Rời khỏi\nCLOSE\n");	
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );	
			
		}
	}
        	
}

// 函数：移动处理
void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	string name, result;
        object who;
        int p, z, x, y, flag, number, order, level, exp, pot, cash;
	object item, orgnpc;
	
        who = this_player();
	if ( who->get_save_2("orgtask2.type")==1  )
	{
		if ( me->get("user")==who->get_number() )
		{
			name = who->get_org_name();
			if (name=="") return;
			orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
			if (!objectp(orgnpc)) return;
			number = who->get_number();
			level = who->get_level();
			order = who->get_save_2("orgtask2.order");
			order ++;
			exp = (level*8+order*order*level*4)*3/5;
			exp = exp * who->get_online_rate()/100;
			pot = order*10+level;
			pot = pot * who->get_online_rate()/100;
			cash = (500+level*6*(order-1))*3/6;				
			cash = cash * who->get_online_rate()/100;
			orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number)+1+order*2/9);
			orgnpc->add_stable(1);
			orgnpc->add_favour(1);
			who->add_potential(pot);
			who->add_cash(cash);
			who->add_exp(exp);			
			result = sprintf("Bạn nhận được kinh nghiệm %d, tiềm nang %d, ngân lượng %d, cống hiến bang phái %d điểm, độ yên ổn tăng 1 điểm, nhân khí tăng 1 điểm\n", exp, pot, cash, 1+order*2/9);
			send_user( who, "%c%s", ';', result );	
			item = present("Thương Dược Người Đưa Tin", who, 1, MAX_CARRY*4) ;
			if (objectp(item))
			{
				item->remove_from_user();
				destruct(item);
			}
			who->delete_save_2("orgtask2");
			who->delete_2("orgtask2");
			if (order>=10) 
			{
				order = 0;
				if (random100()<5*who->get_online_rate()/100) "/quest/box"->give_box(who);
			}
			who->set_save_2("orgtask2.order", order);
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ORG, 1, "" );  
			send_user( who, "%c%c%c%w%s", 0x51, 1, 1, TID_ORG, "" );				
	                me->remove_from_scene();    
        	        destruct(me);		        	        	
		}
	}        
}

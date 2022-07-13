#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <effect.h>

inherit OFFICER;

void do_goto( string arg );
void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5205; }

// 函数：构造处理
void create()
{
        set_name("Cự Thú Đảo Xa Phu");
        set_city_name("Cự Thú Đảo");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me=this_object();
	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(" %s :\n Gần đây người đến thám hiểm ngày càng nhiểu, nhưng đều là đến thì nhiều, về thì ít, vị khách quan này xin hãy cẩn thận!\n"ESC"Làm phiền đưa ta về nước Chu đi\ntalk %x# welcome.23\n"ESC"Rời khỏi",me->get_name(),getoid(me)));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p;
        object who, item;     
        string result;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 23:
        	send_user(who, "%c%c%w%s", 0x5a, 0, 3, "Đang di chuyển……");	                
                who->set_2("travel.z", 80);
                who->set_2("travel.p", 330118);
                who->set_2("travel.money", 0);
                set_effect(who, EFFECT_TRAVEL, 3);
		break;
	}		
}

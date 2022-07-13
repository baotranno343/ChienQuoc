#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 2113; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	int iTime=time();

	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Ẩn sau trong bụi cỏ là một con sư tử đá quái dị. Sư tử tựa thế mơ hồ như từng trải qua phong ba bão táp, dưới nó ẩn chứa một lối đi thần bí. Ngươi có muốn dời sư tử đá qua một bên để tiến vào không?\n"ESC"Tiến vào\ntalk %x# welcome.1\n"ESC"Rời đi",id));
	
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag, p,iTime,i,size;
       	object who, item;
       	string name,*nTmp,tmp;
	mixed *mxTime;  
	  

        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
   		who->add_to_scene(804,32,44,get_d(who), 40971, 0, 40971, 0 );
        	break;

	}

}


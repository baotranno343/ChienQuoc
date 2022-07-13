#include <npc.h>
#include <ansi.h>
#include <action.h>
#include <task.h>
#include <skill.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0954; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tiểu Tinh Quái");
        set_city_name("Chu Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	int id=getoid(me);
	string cTmp;
	
	cTmp = who->get_2("changping.country");
	if ( cTmp == get_city_name() )
		send_user(who,"%c%s",':',sprintf( " %s :\n Ta là Tiểu Tinh Quái do Trương Quả Lão phái đến, ngươi muốn trở về Chu Quốc không? ta sẽ dẫn ngươi về.\n"
			ESC"Rời khỏi cuộc chiến Trường Bình\ntalk %x# welcome.3\n"
			ESC"Rời khỏi", get_name(),id ) 
				);
	else
		send_user(who,"%c%s",':',sprintf( " %s :\n Ta chỉ phụ trách đưa chiến sĩ %s về, còn lại ta không quản đến.\n"
			ESC"Rời khỏi", get_name(),get_city_name()) 
				);
	
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p,z,level,x,y;
        object who,item,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 3:
        	if( p = get_valid_xy(80, 243, 157, IS_CHAR_BLOCK) )
	        {
	                x = p/1000, y = p % 1000;
	                who->add_to_scene(80, x, y, 3);
	                CHAR_CHAR_D->init_loop_perform(who);
	                if ( who->get_2("changping.country") == "Tần Quốc" )
				send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9005, 1, OVER_BODY, PF_STOP );
			else
				send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9006, 1, OVER_BODY, PF_STOP );

	        }
        	break;

        }
}
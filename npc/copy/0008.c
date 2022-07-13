#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 2111; }
void do_welcome(string arg);
void do_accept(string arg);
void do_query(string arg);

// 函数：构造处理
void create()
{
	object me=this_object();
        set_name("Lăng Mộ Thạch Sư");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
                 "accept"         : (: do_accept :),
                 "query"         : (: do_query :),
        ]) );
//        set_head_color(0x39eb);
        setup();
}

void do_look(object who)
{
	int id,level;
	object me=this_object();

	id = getoid(me);
	level = who->get_level();
	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Hiện tại có thể trở lại Tầng 1, ngươi muốn trở lại không ?\n"ESC"Trở lại Tầng 1\ntalk %x# welcome.55\n"ESC"Huỷ bỏ",id,));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,id,tId,*nXy;
       	object who, item,map;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 55:
		tId = who->get_team_id();
        	if ( tId )
        	{
        		map = TEAM_D->get_copy_scene(tId,COPY_TOMB1);
        		if ( !map )
        			return ;
        		nXy = map->get("entrance2");
	        	send_user(who, "%c%c%w%s", 0x5a, 0, 1, "Đang di chuyển……");
		        who->set_2("travel.z", map->get_id());
		        who->set_2("travel.p", nXy[0]*1000+nXy[1]);
		        set_effect(who, EFFECT_TRAVEL, 1);
        	}
		break;
	}
}

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
        set_name("Cơ Quan Thạch Sư");
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
	object me=this_object(),map;

	id = getoid(me);
	map = me->get("map");
	if ( !map )
		return ;
	if ( map->get("open_gate") == 0 )
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Cơ Quan Thạch Sư vẫn chưa hoạt động, hãy đánh bại Dũng Tướng Quân và khởi động Cơ Quan Thạch đi !!\n"ESC"Rời khỏi");
	else
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Hiện tại đã có thể tiến đến tầng tiếp theo, ngươi muốn vào tầng tiếp theo không ?\n"ESC"Chuyển đến Tầng tiếp theo\ntalk %x# welcome.77\n"ESC"Huỷ bỏ",id,));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,id,tId,*nXy, level;
       	object who, item,map;
       	string legend;
        who = this_player();
        flag = to_int(arg);
        level = who->get_level();
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 77:
        	map = me->get("map");
		if ( !map )
			return ;
		if ( map->get("open_gate") == 0 )
			return ;
		tId = who->get_team_id();
        	if ( tId )
        	{
        		map = TEAM_D->get_copy_scene(tId,COPY_TOMB2);
        		if ( !map )	//创建副本
        		{
        			map = "sys/copy/tomb"->new_copy_tomb2(me,who);
        		}
        		if ( !map )
        			return ;
        		nXy = map->get("entrance1");
	        	send_user(who, "%c%c%w%s", 0x5a, 0, 1, "Truyền tống……");
		        who->set_2("travel.z", map->get_id());
		        who->set_2("travel.p", nXy[0]*1000+nXy[1]);
		        set_effect(who, EFFECT_TRAVEL, 1);
        	}
		break;
	}
}



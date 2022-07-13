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
	int id,level,z;
	object me=this_object(),map;

	id = getoid(me);
	z = get_z(me);
	if( !objectp( map = get_map_object(z) ) || !map->is_virtual_scene() ) 
		return;
	if ( map->get("beat_boss")>=2 )	
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Hiện tại ngươi có thể truyền tống trở về Thuý Hoa Sơn !!\n"ESC"Trở lại mặt đất\ntalk %x# welcome.55\n"ESC"Huỷ bỏ",id,));
//		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("这个石狮的传送机关已经被打开，你可以传送回上一层的陵墓或者回到翠华山的地面，你现在要回去吗？\n"ESC"回到地面\ntalk %x# welcome.55\n"ESC"回上一层\ntalk %x# welcome.88\n"ESC"取消",id,id));
	else
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Hiện tại Lăng Mộ Thạch Sư vẫn chưa mở ra, hãy đánh bại Cơ Quan Tướng Quân mới có thể mở ra Cơ quan một lần nữa !!\n"ESC"Rời khỏi");
		
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,id,tId,*nXy, level,z;
       	object who, item,map;
       	string legend;
        who = this_player();
        flag = to_int(arg);
        level = who->get_level();
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 55:
        	z = get_z(me);
		if( !objectp( map = get_map_object(z) ) || !map->is_virtual_scene() ) 
			return;
		if ( map->get("beat_boss") <2 )	
			return ;
        	send_user(who, "%c%c%w%s", 0x5a, 0, 1, "Truyền tống……");
	        who->set_2("travel.z", 82);
	        who->set_2("travel.p", 136117);
	        set_effect(who, EFFECT_TRAVEL, 1);
		break;
//        case 88:
//		z = get_z(me);
//		if( !objectp( map = get_map_object(z) ) || !map->is_virtual_scene() ) 
//			return;
//		if ( map->get("beat_boss") < 2  )	
//			return ;
//		tId = who->get_team_id();
//        	if ( tId )
//        	{
//        		map = TEAM_D->get_copy_scene(tId,COPY_TOMB2);
//        		if ( !map )
//        			return ;
//        		nXy = map->get("entrance2");
//	        	send_user(who, "%c%c%w%s", 0x5a, 0, 6, "传送中……");
//		        who->set_2("travel.z", map->get_id());
//		        who->set_2("travel.p", nXy[0]*1000+nXy[1]);
//		        set_effect(who, EFFECT_TRAVEL, 6);
//        	}
//		break;
	}
}



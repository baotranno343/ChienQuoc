#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5205; }
void do_welcome(string arg);
void do_accept(string arg);

// 函数：构造处理
void create()
{
        set_name("Trường Cảnh Xa Phu");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
}

void do_look(object who)
{
	int id;
	object me=this_object();
	id = getoid(me);
	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Trường Cảnh Xa Phu：\n     Ngươi muốn đi ra ngoài không ？ Ta có thể giúp ngươi！\n"
	ESC"Xác nhận\ntalk %x# welcome.1\n"
//	ESC"现在我们的清怪率是多少？\ntalk %x# welcome.2\n"
	ESC"Rời khỏi",id,));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,id,j,tId;
       	object who, map, npc;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 1:
		map = get_map_object(get_z(me));
		npc = map->get_owner();
		who->add_to_scene(get_z(npc),get_x(npc)+random(3),get_y(npc)+random(3));
//		who->add_to_scene(80,258,158);
        	break;
//        case 2:
//        	tId = who->get_team_id();
//        	map = TEAM_D->get_copy_scene(tId,COPY_MIRROR);
//		if ( !map )
//			return ;
//		i = map->get("copy_npc_die");
//		j = map->get("copy_npc_amount");
//		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("传送兔妖：\n    你们现在的清怪率是%d。想要发现王者的残魂的话，清怪率需要达到85。\n"ESC"离开",i*100/j));
//        	break;
        }

}

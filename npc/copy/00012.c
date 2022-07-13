#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 11; }
void do_welcome(string arg);
void do_accept(string arg);

// 函数：构造处理
void create()
{
        set_name("Truyền Tống Thỏ Yêu");
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
	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Truyền Tống Thỏ Yêu:\n     Nếu ngươi muốn quay về Chu Quốc cứ nói với ta, ta luôn sẵn sàng đưa cái hiệp sĩ về lại !!!\n"ESC"Ta muốn về Chu Quốc\ntalk %x# welcome.1\n"ESC"Hiện tại chúng ta đánh được nhiều ít quái vật ?\ntalk %x# welcome.2\n"ESC"Rời khỏi",id,id,));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,id,j,tId;
       	object who, map;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 1:
		who->add_to_scene(80,258,158);
        	break;
        case 2:
        	tId = who->get_team_id();
        	map = TEAM_D->get_copy_scene(tId,COPY_MIRROR);
		if ( !map )
			return ;
		i = map->get("copy_npc_die");
		j = map->get("copy_npc_amount");
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Truyền Tống Thỏ Yêu:\n    Hiện tại nhóm đã đánh được %d quái vật.Muốn phát hiện Boss phải đánh tới 85 quái vật.\n"ESC"Rời khỏi",i*100/j));
        	break;
        }

}

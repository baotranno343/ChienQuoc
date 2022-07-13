#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 2107; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
	object me=this_object();
        set_name("Cơ Quan Thạch"); // 机关石
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        set_head_color(0x99e7);
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
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Chỉ cần xoay chuyển tảng đá này là có thể mở ra một mất thất khác thông qua "HIR "Cơ Quan Thạch Sư"NOR ". Ngươi muốn khởi động tảng đá này phải không ?\n"ESC"Khởi động Cơ Quan Thạch\ntalk %x# welcome.67\n"ESC"Rời khỏi",id,));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,id,z,size;
       	object who, item,map,*nTeam;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 67:
        	nTeam = who->get_team();
        	if ( !nTeam )
        		return ;
        	map = me->get("map");
		if ( !map )
			return ;
		if ( map->get("open_gate") == 0 )
		if (get_effect(who, EFFECT_OPEN_BOX)) return;
		who->set("openbox",me);
		send_user(who, "%c%c%w%s", 0x5a, 0, 6, "Mở ra……");
		set_effect_2(who, EFFECT_OPEN_BOX, 1,6);				
		break;
	}
}

void into_effect( object who,object npc )
{
	int i,size,z;
	object map,*nTeam;
	nTeam = who->get_team();
	if ( !nTeam )
		return ;
	map = npc->get("map");
	if ( !map )
		return ;
	if ( map->get("open_gate") == 1 )
		return ;
	map->set("open_gate",1);
	z = get_z(npc);
	for(i=0,size=sizeof(nTeam);i<size;i++)
	{
		if ( get_z(nTeam[i]) != z )
			continue;
		send_user(nTeam[i],"%c%s",';',"Rầm, rầm, rầm.Cơ Quan Thạch Sư đã mở ra, hiện tại có thể tiến vào Tầng tiếp theo thông qua Cơ Quan Thạch Sư");
	}
}
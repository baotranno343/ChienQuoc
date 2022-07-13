#include <npc.h>
#include <ansi.h>
#include <cmd.h>
#include <public.h>

#define FILE_SENDER "npc/party/0042"
#define FILE_GUMU  "sys/party/gumu"

inherit OFFICER;

int get_char_picid()
{
	return 5205;
}

void do_welcome(string arg);
void create()
{
	set_name("Cổ Mộ Xa Phu");
	set_2("talk",(["welcome":(:do_welcome:)]));
	setup();
}

void do_look(object who)
{
	FILE_GUMU->do_look(who,this_object());
	
}

void do_welcome(string arg)
{
	object me=this_object();
	__FILE__->do_welcome2(me,arg);
}

void do_welcome2(object me, string arg)
{
	FILE_GUMU->do_welcome(me,this_player(),arg);
}

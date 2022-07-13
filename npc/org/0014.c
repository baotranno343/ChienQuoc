
#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>
#include <time.h>

inherit OFFICER;
inherit SAVE_F;
//inherit "/inh/char/group";

void do_info( string arg );

// 函数：获取人物造型
int get_char_picid() { return 9715; }

// 函数：构造处理
void create()
{
        object me = this_object();
        int time;        
        
        set_name( "Thần Cơ Viện Chủ" );

        set_2( "talk", ([
                "info"          : (: do_info :),
        ]) );

        setup();
}

void do_look( object who ) { "/sys/sys/manager"->do_look_6( who, this_object() ); }
void do_info( string arg ) { "/sys/sys/manager"->do_info_6( this_player(), this_object(), arg ); }

void check_item()
{
	__FILE__->check_item2(this_object());
}

void check_item2(object who)
{
	string name;
	object orgnpc;
	int day, hour, time;
	mixed *mxTime;
	name = who->get_org_name();
	if (name=="") return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );	
	if (!objectp(orgnpc)) return;
	mxTime = localtime(time());
	day = mxTime[TIME_YDAY];
	hour = mxTime[TIME_HOUR];	
	time = day * 2;
	if (hour>=12) time ++;
	if (orgnpc->get_producttime()!=time)
	{
		__FILE__->reset_item2(who);
		orgnpc->set_producttime(time);
	}
}

void reset_item()
{
	__FILE__->reset_item2(this_object());
}

void reset_item2(object who)
{
	string name, *list;
	object orgnpc;
	int count;
	name = who->get_org_name();
	if (name=="") return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );	
	if (!objectp(orgnpc)) return;	
	if (orgnpc->get_stable()<1000) return ;
	count = orgnpc->get_science()/2+1;
	list = "/quest/product2"->get_random_list(count);
	orgnpc->set_productfile2(list);
}
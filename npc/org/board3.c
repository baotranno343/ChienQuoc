#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>

inherit OFFICER;

void do_welcome(string arg);
// 函数：获取人物造型
int get_char_picid() { return 2006; }

// 函数：构造处理
void create()
{
        set_city_name("");
        set_name( "Bảng Xếp Hạng" );
        set_2("talk",(["welcome":(:do_welcome:)]));

        setup();
}
void do_look(object who)
{
	string result;
	object me=this_object();
	result=sprintf("                   Hoan nghênh đến với Bảng xếp Hạng Chiến Quốc\n");
	result+=sprintf(ESC HIY"Chiến Quốc Xếp Hạng Danh Nhân Đường\ntalk %x# welcome.1\n",getoid(me));
	result+=sprintf(ESC HIY"Chiến Quốc Xếp Hạng Bang Phái\ntalk %x# welcome.2\n",getoid(me));
	send_user(who,"%c%c%w%s",':',3,get_char_picid(),result);
}

void do_welcome(string arg)
{
	object me=this_object();
	__FILE__->do_welcome2(me,arg);
}

void do_welcome2(object me ,string arg)
{
	int flag,i,size,time;
	string result,*name;
	mapping org;
	object who,char;
	
	who=this_player();
	who->set_time("talk",0);
	if(!arg) return;
	flag=to_int(arg);
	switch(flag)
	{
		case 1:
			"sys/party/mingren"->do_look(who);
			break;
		case 2:
			 if( mapp( org = CITY_ZHOU->get_2("org") ) && arrayp( name = keys(org) ) )
		        {
				size = sizeof(name);
				for (i=0;i<size;i++)
				if (objectp( char = CITY_ZHOU->get_2("org." + name[i] ) ))
				{
					result = sprintf("%-4s%-12s%s", char->get_city_name(), char->get_org_name(), char->get_master_name() );
					time = char->get_create_time();
					time = time() - time;
					send_user(who, "%c%c%d%d%w%d%s", 0x95, 97, getoid(char), char->get_power(), char->sizeof_member_dbase(), time, result);
				}
		                
		        }
		        else    notify( "Trước mắt không có Bang Phái");
			break;
		
	}
}
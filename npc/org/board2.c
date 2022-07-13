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
	result=sprintf(" Hoan nghênh đến với Bảng Xếp Hạng Chiến Quốc - Loạn Thế Anh Hùng\n");
	result+=sprintf(ESC HIY"Xếp Hạng Thực Lực\ntalk %x# welcome.1\n",getoid(me));
	result+=sprintf(ESC HIY"Xếp Hạng Phú Hộ\ntalk %x# welcome.2\n",getoid(me));
	result+=sprintf(ESC HIY"Xếp Hạng Danh Sư\ntalk %x# welcome.3\n",getoid(me));
	result+=sprintf(ESC HIY"Xếp Hạng Công Đức\ntalk %x# welcome.4\n",getoid(me));
	result+=sprintf(ESC HIY"Xếp Hạng Đại Đệ Tử Môn Phái\ntalk %x# welcome.5\n",getoid(me));
	send_user(who,"%c%c%w%s",':',3,get_char_picid(),result);
}

void do_welcome(string arg)
{
	object me=this_object();
	__FILE__->do_welcome2(me,arg);
}

void do_welcome2(object me ,string arg)
{
	int flag,i,size,time,level,point,xy_family;
	string result,*name,family;
	mapping org;
	object who,char;
	
	who=this_player();
	who->set_time("talk",0);
	if(!arg) return;
	flag=to_int(arg);
	switch(flag)
	{
		case 1:
			"sys/party/mingren"->do_look1(who);
			break;
		case 2:
			"sys/party/mingren"->do_look2(who); 
			break;
		case 3:
			"sys/party/mingren"->do_look3(who);
			break;
		case 4:
			"sys/party/mingren"->do_look4(who);
			break;
		case 5:
			"sys/party/mingren"->do_look5(who);
			break;	
		
	}
}
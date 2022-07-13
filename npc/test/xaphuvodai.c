/****************************************/
/*************PVP场景传送员**************/
/****************************************/

#include <npc.h>
#include <ansi.h>
#include <effect.h>


inherit OFFICER;

mapping Map=([
		"Tỉ Võ Trường":({885,99,71}),
		]);

//获取NPC造型
int get_char_picid()
{
	return 5109;
}

void do_welcome(string arg);

//构造初始化
void create()
{
	set_name("Võ Đài Truyền Tống");
	set_2("talk",(["welcome":(:do_welcome:)]));
	setup();
}

//对话处理
void do_look(object who)
{
	string result;
	object me=this_object();
	
	result=sprintf(me->get_name()+":\n    Các vị bằng hữu muốn vào tỷ thý võ đài để xem thực lực của mình đến đâu không!\n");
	result+=sprintf(ESC "Ta muốn vào Võ Đài tỷ thý một phen\ntalk %x# welcome.8\n",getoid(me));
	result+=sprintf(ESC "Rời khỏi");
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
}

void do_welcome(string arg)
{
	object me=this_object();
	__FILE__->do_welcome2(me,arg);
}

void do_welcome2(object me,string arg)
{
	int flag,z,x,y,level,*zxy;
	string *key,result,mapname;
	object who;
	
	who=this_player();
	who->set_time("talk",0);
	level=who->get_level();
	if(!arg) return; 
	key=explode(arg," ");
	flag=to_int(key[0]);
	switch(flag)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			result=sprintf(me->get_name()+":\n    Ngươi muốn vào Võ Đài không?。\n");
			result+=sprintf(ESC "Tiến vào Võ Đài\ntalk %x# welcome.10 Tỉ Võ Trường\n",getoid(me));
			result+=sprintf(ESC "Rời khỏi");
			
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),result);
			break;	
		case 10:
			if(!sscanf(arg,"%d %s",flag,mapname)==2) return;
			zxy=Map[mapname];
			if(!zxy) return;
			z=zxy[0];x=zxy[1];y=zxy[2];
			__FILE__->send_ok(who,z,x,y);
			break;
			
	}
}

//可以传送
void send_ok(object who,int z,int x,int y)
{
	int p;
	object me=this_object();
	p=x*1000+y;
	send_user(who, "%c%c%w%s", 0x5a, 0, 3, "Đang di chuyển……");
        who->set_2("travel.z",z);
	who->set_2("travel.p",p);
	set_effect(who, EFFECT_TRAVEL, 3);
//	me->add_to_scene(z,x-2,y-2);
}
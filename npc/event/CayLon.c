#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>
#include <time.h>
#include <effect.h>
#include <skill.h>
#include <public.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 3031; }
void do_gift( string arg );
// 函数：构造处理
void create()
{
        set_name("");
		set_2( "talk", ([
				"gift"          : (: do_gift :),
        ]));
        setup();
}


void do_look(object who)
{
	int id = getoid( this_object() );
		if ( this_object()->get_save("cayto") == who->get_number() ) {
		send_user(who,"%c%c%w%s",':',3,0,sprintf("Bạn muốn tôi biến mất để trồng cây khác không ? \n"
		ESC HIC"Ta muốn...\ntalk %x# gift.2\n"
		ESC"Rời khỏi",id));
		}
		else {
		send_user(who,"%c%c%w%s",':',3,0,sprintf("Cây này không phải của bạn trồng ! \n"
		ESC HIC"Ta biết rồi\ntalk %x# gift.100\n"
		ESC"Rời khỏi",id));
		}
}
void do_gift( string arg )
{
        object me = this_object();
        __FILE__ ->do_gift2(me, arg);
}

void do_gift2( object me, string arg )
{
	int flag,id,i,p,iTime,iDay,iGio,rate,l,tien,z,x,y,x0,y0,exp,level;
	object who,item,item1,item2,item3,npc;
	string *nTmp,cFile,cTmp,cFinal,result;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);     
	iDay = mxTime[TIME_YDAY];
	iGio = mxTime[TIME_HOUR];
	
        who = this_player();
		id = getoid(me);
        flag = to_int(arg);
        who->set_time( "talk",  0);
		rate = random(100);
        switch(flag)
        {
       	case 1:
			break;
		case 2:
				if ( me->get_save("cayto") != who->get_number() ) {
				write_user(who, ECHO"Cây này không phải của bạn trồng" );
				return 0;
				}
			me->remove_from_scene();
			who->set_save("trongcay",1);
			send_user(who,"%c%s",';',"Bạn đã làm cây xanh biến mất !");
			break;
		}
}

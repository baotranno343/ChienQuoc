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
int get_char_picid() { return 3032; }
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
		if ( this_object()->get_save("tuoinuoc") == who->get_number() ) {
		send_user(who,"%c%c%w%s",':',3,0,sprintf("Bạn muốn tưới nước cho tôi không ? \n"
		ESC HIC"Ta muốn tưới nước\ntalk %x# gift.2\n"
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
				if ( me->get_save("tuoinuoc") != who->get_number() ) {
				write_user(who, ECHO"Cây này không phải của bạn trồng" );
				return 0;
				}
			if ( TASK_LEGEND_D->check_task_item_amount(who,"Thuỷ Lộ") < 1 )
			{
                write_user(who, ECHO "Bạn không có Thuỷ Lộ !");
                return ;
			}
			TASK_LEGEND_D->check_task_item1(who,"Thuỷ Lộ",1);
			me->remove_from_scene();
			z = get_z(who);  x0 = get_x(who);  y0 = get_y(who);
			p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK);
			if( !p )
        	return 0;
			x = p / 1000;  y = p % 1000;
			npc = new("npc/event/CayLon");
			if ( !npc )
			return 0;
			npc->set_save("cayto",who->get_number());
			npc->add_to_scene( z, x, y);
			level = who->get_level();
			exp = 5678+level*level*897;
			who->add_exp(exp);
			send_user(who,"%c%s",';', sprintf("Bạn đã tưới nước cho Cây, đồng thời bạn nhận được %d kinh nghiệm", exp));
			break;
		}
}		
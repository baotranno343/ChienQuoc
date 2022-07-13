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
int get_char_picid() { return 9963; }
void do_gift( string arg );
// 函数：构造处理
void create()
{
        set_name("Giám Ngục Quan");
		set_2( "talk", ([
				"gift"          : (: do_gift :),
        ]));
        setup();
}


void do_look(object who)
{
	int id = getoid( this_object() );
		send_user(who,"%c%c%w%s",':',3,9963,sprintf("Tuy ta là giám ngục quan của nước Chu, nhưng mà bản tính tham tiền thì không ai là không có, vậy nếu như ngươi hối lộ cho ta một số ngân lượng, ta có thể xem sét tội lỗi của ngươi và thả ngươi ra ! \n"
		ESC "Hối lộ 10 triệu ngân lượng\ntalk %x# gift.2\n"
	//	ESC "Kiểm tra thời gian còn lại trong Nhà Ngục\ntalk %x# gift.3\n"
		ESC"Rời khỏi",id,id));
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
				if ( who->get_cash() < 10000000 )
				{
					notify("Bạn không có đủ 10 triệu lượng");
					return;
				}
				who->delete_save("vaotu");
				who->set_save("gietnguoi",0);
				who->add_cash(-10000000);
				who->set_login_flag(2); 
                set_invisible(who, 1);
                set_effect(who, EFFECT_USER_LOGIN, 4);
				who->add_to_scene(80, 292, 184);	
			break;
		case 3:	
		send_user(who,"%c%c%w%s",':',3,9963,sprintf("Ngươi còn %d giây nữa sẽ được ra khỏi Nhà Ngục ! \nTuy ta là giám ngục quan của nước Chu, nhưng mà bản tính tham tiền thì không ai là không có, vậy nếu như ngươi hối lộ cho ta một số ngân lượng, ta có thể xem sét tội lỗi của ngươi và thả ngươi ra ! \n"
		ESC "Hối lộ 10 triệu ngân lượng\ntalk %x# gift.2\n"
		ESC"Rời khỏi",who->get_save("vaotu"),id));
			break;	
		}
}		
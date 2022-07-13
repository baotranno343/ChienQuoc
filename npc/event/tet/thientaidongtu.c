#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>
#include <time.h>
#include <effect.h>
#include <skill.h>

inherit OFFICER;

// 函数:获取人物造型
int get_char_picid() { return 7909; }
void do_gift( string arg );
// 函数：小贩识别
int is_seller() { return 4; }
// 有自己的do_look函数
int is_self_look() { return 1; }

void create()
{
        set_real_name("Thiện Tài Đồng Tử");
		set_name("Chiến Quốc Năm Mới Sứ Giả");
		set_2( "good", ([
                "01" : "/item/04/baozhu",			
        ]) );
        set_2( "talk", ([
				"gift"          : (: do_gift :),
        ]));

        setup();
}

void do_look( object who ) 
{
	int id = getoid( this_object() );
	object me = this_object();
	string result;
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Năm cũ đã qua, năm mới lại đến. Chúc bạn có một năm mới vui vẻ, an khang thịnh vượng. Ta chính là Thiện Tài Đồng Tử từ thiên đình ngao du xuống nhân gian để tham quan cái Tết của mọi người. Thế nào, sáng giờ đã nhận được Hồng bao Năm mới chưa, hahaha !\n"
		ESC "Mua Pháo tết\nlist %x#\n"
		ESC "Dùng Bánh tết đổi quà\ntalk %x# gift.11\n"								
		ESC"Rời khỏi",get_name(),id,id,id,id,id));		
		
}

void do_gift( string arg )
{
        object me = this_object();
        __FILE__ ->do_gift2(me, arg);
}

void do_gift2( object me, string arg )
{
	int flag,id,i,p,iTime,iDay,iGio,rate,l,tien,ben, tet1=0,tet2=0, tet3, tet4,bennhat2,bn2,level;
	object who,item,item1,item2,item3;
	string *nTmp,cFile,cTmp,cFinal,result,bennhat,bn;
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
       	case 11:
			if ( TASK_LEGEND_D->check_task_item_amount(who,"Bánh Tết") < 5 )
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),"Thiện Tài Đồng Tử :\n Ngươi không có đủ 5 cái Bánh tết, làm sao ta có thể đổi quà cho người ?\n"ESC"Xác nhận \nCLOSE\n"ESC"Rời khỏi");
				return ;
			}			
			if(USER_INVENTORY_D->get_free_count(who) < 1 )
			{
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),"Thiện Tài Đồng Tử :\n Hành trang của ngươi không đủ 1 ô trống !\n"ESC"Xác nhận \nCLOSE\n"ESC"Rời khỏi");
			return ;
			}
			TASK_LEGEND_D->check_task_item1(who,"Bánh Tết",5);	
			if ( random100() <	99 )
				item=new("item/event/lixi");
			else
				notify("Thao tác thất bại!");
			if ( item ) 
			{
				p=item->move2(who,-1);
				item->add_to_user(p);
			send_user(who,"%c%s",';',"Bạn đã thành công đổi được "+item->get_name()+", xin chúc mừng !");
			CHAT_D->sys_channel(0,sprintf(HIY"Xin chúc mừng "HIR"%s"HIY" tham gia sự kiện Tết nhận được "HIR"Hồng Bao Lì Xì"HIY"!",who->get_name()));
			}
			break;	
		}
}

#include <npc.h>
#include <ansi.h>
#include <time.h>

inherit OFFICER;
// 函数:获取人物造型
int get_char_picid() { return 853; }
void do_welcome(string arg);

// 函数:构造处理
void create()
{
        set_name("Vô Song Cung Thủ Vệ");
//        set_2( "talk", ([
//                 "welcome"         : (: do_welcome :),
//        ]) );
        setup();
}

void do_look(object who) { __FILE__->do_look_call(this_object(),who); }

void do_look_call(object me,object who)
{
	string org_name;
	
	org_name = "/sys/party/vstfix"->get_occupy_org();
	
	if ( !sizeof(org_name) )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s:\n Hiện tại Vô Song Thành đang ở trạng thái chưa ai chiếm lĩnh.\n"ESC"Rời khỏi",me->get_name()));
		return ;		
	}
	if ( "/sys/party/vstfix"->check_war_time() == 1 )
	{
		if ( org_name == who->get_org_name() )
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s:\n Hiện tại chính là thời gian công thành, hãy vào bảo vệ cung điện, đừng để Bang phái khác chiếm đoạt.\n"ESC"Rời khỏi",me->get_name()));
		else 
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s:\n Người tới là người nào ? ta phải kêu thủ vệ !\n"ESC"Rời khỏi",me->get_name()));
	}
	else 
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s:\n Vô Song Cung là "HIR "%s"NOR " cấm địa, Bang phái khác cấm vào.\n"ESC"Rời khỏi",me->get_name(),org_name));
}


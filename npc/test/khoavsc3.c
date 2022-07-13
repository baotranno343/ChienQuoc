#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 2006; }
void do_gift( string arg );
// 函数：构造处理
void create()
{
        set_name( "Chìa khoá Giáp" );
        set_2( "talk", ([
				"gift"          : (: do_gift :),
        ]));

        setup();
}
void do_look(object who)
{
	object me = this_object();
	string khoa1, khoa2, khoa3, khoa="";
	khoa1 = "/sys/party/vstfix"->get_mokhoa1() == 0 ? "Tắt" : "Bật";
	khoa2 = "/sys/party/vstfix"->get_mokhoa2() == 0 ? "Tắt" : "Bật";
	khoa3 = "/sys/party/vstfix"->get_mokhoa3() == 0 ? "Tắt" : "Bật";
	if ( "/sys/party/vstfix"->get_mokhoa1()>0 && "/sys/party/vstfix"->get_mokhoa2()>0 && "/sys/party/vstfix"->get_mokhoa3()>0 )
	khoa = "3 Khoá đã khởi động, ít phút sau mới có thể khởi động lại !";

	send_user(who, "%c%c%w%s",':',3, 2005, sprintf("Hiện tại chìa khoá này đang ở trạng thái : %s. \nChìa khoá Ất : Trạng thái ( %s ) \nChìa khoá Bính : Trạng thái ( %s ) \nChìa khoá Giáp : Trạng thái ( %s ) \n%s\n"
	ESC"%s\ntalk %x# gift.2\n"
	ESC"Rời khỏi\nCLOSE\n",khoa3,khoa1,khoa2,khoa3,khoa,
	"/sys/party/vstfix"->get_mokhoa3() == 0 ? "Ta muốn khởi động Khoá" : "Ta chỉ đến xem",getoid(me)));
}
void do_gift( string arg ) { __FILE__ ->do_gift2(this_object(), arg); }
void do_gift2( object me, string arg )
{
	int id, flag;
	object who;	
		who = this_player();
		id = getoid(me);
        flag = to_int(arg);
        who->set_time( "talk",  0);
		switch (flag)
		{
		case 2:
		if ( "/sys/party/vstfix"->checkctmk() != 1 ) return;
		if ( "/sys/party/vstfix"->check_war_time() != 1 ) return;
		if ( who->get_org_name()=="" ) return;
		if ( "/sys/party/vstfix"->get_mokhoa3() > 0 ) return;
		if ( get_effect_3(who, EFFECT_PROGRESS) ) return;
		if ( get_effect(who, EFFECT_PROGRESS2) ) return;	
				set_effect(who, EFFECT_PROGRESS2, 7);
				who->set_progress_file(__FILE__); 
				send_user(who, "%c%c%w%s", 0x5a, 0, 7, "Khởi động...");
		break;
		}
}
int into_effect( object who , string arg)
{
	int p, rate;
	object item, me;
	rate = random(100);
	send_user(who, "%c%c%c", 0x5a, 1, 1);
	
		if ( "/sys/party/vstfix"->get_mokhoa3() < 1 )
		{
			if ( "/sys/party/vstfix"->checkctmk() != 1 ) return 0;
			if ( "/sys/party/vstfix"->check_war_time() != 1 ) return 0;
		"/sys/party/vstfix"->add_mokhoa(1);
		"/sys/party/vstfix"->set_mokhoa3(1);
		notify("Bạn đã mở chìa khoá Giáp thành công !");
		USER_D->user_channel(sprintf("Chìa khoá Giáp đã bị %s "HIR "khởi động "NOR "!", who->get_name() ));
		if ( "/sys/party/vstfix"->get_mokhoa()>=3 ) 
		{
		USER_D->user_channel(sprintf("Chìa khoá của Vô Song Thành đều đã ở trong trạng thái khởi động, sau 7 giây tất cả những người ở trong Vô Song Cung sẽ bị đưa ra ngoài !" ));
		"/sys/party/vstfix"->do_hoatdongkhoa(7);
		}
		}	
	return 1;
}
void effect_break(object me, string arg)
{
	send_user(me, "%c%c%c", 0x5a, 1, 0);
	set_effect(me, EFFECT_PROGRESS2, 0 );	
}
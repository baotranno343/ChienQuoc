/*------------------------------------
	NPC Tái Tạo by Ben
------------------------------------*/	
#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5302; }
void do_welcome(string arg);
void do_accept(string arg);

void create()
{	  
        set_name("Nhân viên chuyển Kim Bảo");
		set_2( "talk", ([
                "welcome"	:( : do_welcome :),
		//		"giaotrangbi"         : (: do_accept :),
             ]));
        setup();

}

void do_welcome( string arg )
{
	__FILE__->do_welcome2(this_object(),arg);
}
void do_welcome2( object npc, string arg )
{
	int flag;
	object player  = this_player();
	flag = to_int(arg);
	switch(flag)
	{
		case 1: 
			break;
		case 2:
	        send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(),sprintf(npc->get_name() + ":\n"+"Ngươi hiện đang có %d Kim Nguyên Bảo ( %d Ngân Bảo ).\n" 
	        ESC "Ta biết rồi\nCLOSE\n"
			ESC "Thoát ra\nCLOSE\n","sys/sys/test_db"->get_yuanbao(player)/10,"sys/sys/test_db"->get_yuanbao(player))); 
			break;
		case 3:
			send_user( player, "%c%c%d%s", '?', 16, 5, "Bạn muốn chuyển Kim Bảo    cho số ID nào? Xin hãy nhập vào : \n" ESC "chuyenknb - %s\n" );
			break;	
	}
}
void do_look( object player )
{
	object npc = this_object();
	
	send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(), sprintf( "%s :\n"+"Ta đây chuyên phụ trách về vấn đề Kim Nguyên Bảo của thế giới Chiến Quốc, ta có thể giúp ngươi chuyển Kim Nguyên Bảo vào một người chơi có số ID do ngươi chỉ định. Nào! ngươi muốn ta giúp gì không? \n"
        ESC "Ta muốn chuyển Kim Nguyên Bảo qua người chơi khác\ntalk %x# welcome.3\n"
        ESC "Ta muốn kiểm tra Kim Nguyên Bảo của ta\ntalk %x# welcome.2\n"
        ESC "Rời khỏi\nCLOSE\n", npc->get_name(), getoid(npc), getoid(npc) ) );
}
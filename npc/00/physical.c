#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 9968; }
void do_welcome(string arg);
void do_accept(string arg);
void create()
{	  
        set_2( "talk", ([
                "welcome"	:( : do_welcome :),
				"accept"         : (: do_accept :),
             ]));
        setup();

        set_name( "Lương Phan Tiên" );
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
	        send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(),npc->get_name() + ":\n"+"Lương Ban Tiên có thể giúp bạn tái tạo chỉ số của trang bị, chỉ cần bạn đưa ông ta trang bị hoặc vũ khí Lam Kim, Hoàng Kim thêm một ít ngân lượng là đượcCó thể tái tạo nhiều lần, tuy nhiên chưa chắc là chỉ số của trang bị luôn trở nên tốt hơn, điều này còn tùy thuộc và sự may mắn của bạn, trang bị hoặc vũ khí đã tinh luyện hay chế tạo thành cũng có thể tái tạo chỉ số.\n" 
	        ESC "ALT+G  để giao trang bị\nCLOSE\n"
			ESC "Thoát ra\nCLOSE\n"); 
		break;
	}
}
void do_look( object player )
{
	object npc = this_object();
	
	send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(), sprintf( " %s :\n"+" Thiên linh linh, địa linh linh, yêu ma quỷ quái hãy hiện hình, vị khách quan đây, ấn đường đen, nhất định có chuyện không hay xảy ra, hay là để bần đạo xem giúp một quẻ! Muốn hỏi về tình duyên hay sự nghiệp?\n"
        ESC "Tái Tạo trang bị Hoàng Kim\ntalk %x# welcome.1\n"
        ESC "Tái Tạo trang bị Lam Kim\ntalk %x# welcome.1\n"
        ESC "Rời khỏi\nCLOSE\n", npc->get_name(), getoid(npc), getoid(npc) ) );
}

int accept_object( object me, object who, object item )
{
	return -99;
}

void do_accept( string arg )
{
	__FILE__->do_accept2(this_object(),arg);
}

void do_accept2( object me, object who, object item, string arg )
{
	int level, i, id;
	string cTmp, result;
	id = getoid( this_object() );
	if( !objectp( item = present( arg, who, 1, MAX_CARRY*4 ) ) )
		return ;
}		

#include <npc.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 9964; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name( "Thợ Cắt Tóc" );
        set_2( "talk", ([
				"welcome"          : (: do_welcome :),
        ]));

        setup();
}

void do_look( object who ) 
{
	int id = getoid( this_object() );
	send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Bạn chán kiểu tóc hiện tại của mình rồi à, đừng lo, hãy gặp tôi, tôi có thể cắt cho bạn bất kỳ kiểu tóc nào mà bạn muốn chỉ với 100.000 lượng.\n"
		ESC"Tóc kiểu 1 (Tóc cơ bản)\ntalk %x# welcome.1\n"
		ESC"Tóc kiểu 2 (Tóc môn phái Đào Hoa Nguyên)\ntalk %x# welcome.2\n"
		ESC"Tóc kiểu 3 (Tóc môn phái Thục Sơn)\ntalk %x# welcome.3\n"
		ESC"Tóc kiểu 4 (Tóc môn phái Cấm Vệ Quân)\ntalk %x# welcome.4\n"
		ESC"Tóc kiểu 5 (Tóc môn phái Đường Môn)\ntalk %x# welcome.5\n"
		ESC"Tóc kiểu 6 (Tóc môn phái Côn Luân)\ntalk %x# welcome.6\n"
		ESC"Tóc kiểu 7 (Tóc môn phái Vân Mộng Cốc)\ntalk %x# welcome.7\n"
		ESC"Tóc kiểu 8 (Tóc môn phái Mao Sơn)\ntalk %x# welcome.8\n"
		ESC"Rời khỏi",get_name(),id,id,id,id,id,id,id,id));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,id,gender;
	object who;
	
        who = this_player();
		id = getoid(me);
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
       	case 1:
       	case 2:
       	case 3:
       	case 4:
       	case 5:
       	case 6:
       	case 7:
       	case 8:
			if (who->get_gender() == 2) gender = 1000;
			who->add_cash(-100000);
			who->set_hair(gender+flag);
			who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Xong rồi đấy, cho tôi xin 100.000 lượng tiền công nhé.\n"
				ESC"Đóng lại",get_name()));
			break;
        }
}

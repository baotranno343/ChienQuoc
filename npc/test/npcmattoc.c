/*******************************
	NPC Đổi Tóc Và Khuôn Mặt
	Made by YeuChienQuoc
	File gốc: npcdoitoc.c
	Nguồn: trungviet
	Tối ưu hóa by trungviet
*******************************/

#include <npc.h>
#include <ansi.h>

inherit OFFICER;

// 函数:获取人物造型
int get_char_picid() { return 9958; }
void do_welcome( string arg );

// 函数:构造处理
void create()
{
        set_name( "Thợ Đổi Tóc Cấp Tốc" );
        set_2( "talk", ([
				"welcome"          : (: do_welcome :),
        ]));

        setup();
}

void do_look( object who ) 
{
	int id = getoid( this_object() );
	send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s : \nMỗi nhân vật đổi tóc miễn phí tối đa hai lần !!\n"
		ESC HIY"Tôi muốn đổi tóc Miễn phí\ntalk %x# welcome.1\n"
		ESC HIY"Tôi muốn đổi kiểu mặt Miễn phí\ntalk %x# welcome.4\n"
//		ESC	HIY"Tôi muốn dùng 1000 điểm Tiền Vàng để Đổi tóc\ntalk %x# welcome.2\n"
		ESC	HIY"Tôi muốn dùng 5 Kim Nguyên Bảo để Đổi tóc\ntalk %x# welcome.3\n"
		ESC"Rời khỏi",get_name(),id,id,id));
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
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy chọn một kiểu tóc mà ngươi thích.\n"
			ESC"(Vô Môn Phái)\ntalk %x# welcome.21\n"
			ESC"(Đào Hoa Nguyên)\ntalk %x# welcome.22\n"
			ESC"(Thục Sơn)\ntalk %x# welcome.23\n"
			ESC"(Cấm Vệ Quân)\ntalk %x# welcome.24\n"
			ESC"(Đường Môn)\ntalk %x# welcome.25\n"
			ESC"(Côn Luân)\ntalk %x# welcome.26\n"
			ESC"(Vân Mộng Cốc)\ntalk %x# welcome.27\n"
			ESC"(Mao Sơn)\ntalk %x# welcome.28\n"
//			ESC"Tóc Hôn Sa,Lễ Phục\ntalk %x# welcome.29\n"
//			ESC"Tóc Trạng Nguyên Phục,Phụng Quan Hà Ấp\ntalk %x# welcome.30\n"
			ESC"Thoát",get_name(),id,id,id,id,id,id,id,id,id,id));
			break;
		case 2:
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy chọn một kiểu tóc mà ngươi thích và nhớ trả ta 1000 điểm Tiền Vàng nhe.\n"
			ESC"(Vô Môn Phái)\ntalk %x# welcome.41\n"
			ESC"(Đào Hoa Nguyên)\ntalk %x# welcome.42\n"
			ESC"(Thục Sơn)\ntalk %x# welcome.43\n"
			ESC"(Cấm Vệ Quân)\ntalk %x# welcome.44\n"
			ESC"(Đường Môn)\ntalk %x# welcome.48\n"
			ESC"(Côn Luân)\ntalk %x# welcome.46\n"
			ESC"(Vân Mộng Cốc)\ntalk %x# welcome.47\n"
			ESC"(Mao Sơn)\ntalk %x# welcome.48\n"
//			ESC"Tóc Hôn Sa,Lễ Phục\ntalk %x# welcome.49\n"
//			ESC"Tóc Trạng Nguyên Phục,Phụng Quan Hà Ấp\ntalk %x# welcome.50\n"
			ESC"Thoát",get_name(),id,id,id,id,id,id,id,id,id,id));
			break;
		case 3:
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy chọn một kiểu tóc mà ngươi thích và nhớ trả ta 2 Kim Nguyên Bảo nhe.\n"
			ESC"(Vô Môn Phái)\ntalk %x# welcome.61\n"
			ESC"(Đào Hoa Nguyên)\ntalk %x# welcome.62\n"
			ESC"(Thục Sơn)\ntalk %x# welcome.63\n"
			ESC"(Cấm Vệ Quân)\ntalk %x# welcome.64\n"
			ESC"(Đường Môn)\ntalk %x# welcome.65\n"
			ESC"(Côn Luân)\ntalk %x# welcome.66\n"
			ESC"(Vân Mộng Cốc)\ntalk %x# welcome.67\n"
			ESC"(Mao Sơn)\ntalk %x# welcome.68\n"
//			ESC"Tóc Hôn Sa,Lễ Phục\ntalk %x# welcome.69\n"
//			ESC"Tóc Trạng Nguyên Phục,Phụng Quan Hà Ấp\ntalk %x# welcome.70\n"
			ESC"Thoát",get_name(),id,id,id,id,id,id,id,id,id,id));
			break;	
		case 4:
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy chọn một kiểu khuôn mặt mà ngươi thích.\n"
			ESC"Mặt kiểu 1 \ntalk %x# welcome.33\n"
			ESC"Mặt kiểu 2 \ntalk %x# welcome.34\n"
			ESC"Mặt kiểu 3 \ntalk %x# welcome.35\n"
			ESC"Mặt kiểu 4 \ntalk %x# welcome.36\n"
			ESC"Mặt kiểu 5 \ntalk %x# welcome.37\n"
			ESC"Thoát",get_name(),id,id,id,id,id));
			break;
		case 11:
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy chọn một kiểu tóc mà ngươi thích.\n"
			ESC"(Tóc cơ bản)\ntalk %x# welcome.21\n"
			ESC"(Đào Hoa Nguyên)\ntalk %x# welcome.22\n"
			ESC"(Thục Sơn)\ntalk %x# welcome.23\n"
			ESC"(Cấm Vệ Quân)\ntalk %x# welcome.24\n"
			ESC"(Đường Môn)\ntalk %x# welcome.25\n"
			ESC"(Côn Luân)\ntalk %x# welcome.26\n"
			ESC"(Vân Mộng Cốc)\ntalk %x# welcome.27\n"
			ESC"(Mao Sơn)\ntalk %x# welcome.28\n"
	//		ESC"Tóc Hôn Sa,Lễ Phục\ntalk %x# welcome.29\n"
	//		ESC"Tóc Trạng Nguyên Phục,Phụng Quan Hà Ấp\ntalk %x# welcome.30\n"
			ESC"Thoát",get_name(),id,id,id,id,id,id,id,id,id,id));
			break;
		case 12:
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy chọn một kiểu khuôn mặt mà ngươi thích.\n"
			ESC"Mặt kiểu 1 \ntalk %x# welcome.33\n"
			ESC"Mặt kiểu 2 \ntalk %x# welcome.34\n"
			ESC"Mặt kiểu 3 \ntalk %x# welcome.35\n"
			ESC"Mặt kiểu 4 \ntalk %x# welcome.36\n"
			ESC"Mặt kiểu 5 \ntalk %x# welcome.37\n"
			ESC"Thoát",get_name(),id,id,id,id,id));
			break;
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
			if (who->get_gender() == 2) gender = 1000;
			if(who->get_save_2("doitoc.score")>=2)
			{	
				send_user(who,"%c%s",':',me->get_name()+":\n    Ngươi đã đổi Tóc miễn phí 2 lần rồi \nKhông thể đổi tóc miễn phí được nữa đâu!!!\n"ESC"Rời khỏi.");
				return 0;
			}
			who->add_save_2("doitoc.score",1);
			who->add_exp(10);
			who->set_hair(gender+flag-20); //Thay đổi tóc theo case và giới tính (gender)
			who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who)); //Load lại nhân vật
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy thưởng thức diện mạo mới của ngươi đi nhé!\n"
			ESC"Đóng lại",get_name()));
			break;	
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
			if (who->get_cash() < 50000) // Nếu tiền trong người đối tượng who ít hơn 50000 Ngân lượng
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Số ngân lượng hiện có của bạn không đủ 50.000 lượng!"
				ESC"Rời khỏi",get_name())); 
				return;
			}
			if (who->get_gender() == 2) gender = 1000;
			who->add_cash(-50000); //Trừ 50000 Ngân lượng của đối tượng who
			who->set_photo(gender+flag-32); //Thay đổi khuôn mặt theo case va giới tính (gender)
			who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who)); //Load lại nhân vật
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy thưởng thức diện mạo mới của ngươi đi nhé!!!\n"
			ESC"Đóng lại",get_name()));
			break;
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
			if (who->get_gender() == 2) gender = 1000;
			if(who->get_save_2("diemtienvang.score")<1000)
			{	
				send_user(who,"%c%s",':',me->get_name()+":\n   Không đủ 1000 điểm Tiền Vàng!!!\n"ESC"Rời khỏi.");
				return 0;
			}
//			who->add_save_2("doitoc.score",1);
			who->add_save_2("diemtienvang.score",-1000);
			who->add_exp(10);
			who->set_hair(gender+flag-40); //Thay đổi tóc theo case và giới tính (gender)
			who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who)); //Load lại nhân vật
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy thưởng thức diện mạo mới của ngươi đi nhé!\n"
			ESC"Đóng lại",get_name()));
			break;
		case 61:
		case 62:
		case 63:
		case 64:
		case 65:
		case 66:
		case 67:
		case 68:
		case 69:
		case 70:
			if("sys/sys/test_db"->get_yuanbao(who)<50)
			{	
				send_user(who,"%c%s",':',me->get_name()+":\n   Không đủ 5 Kim Nguyên Bảo!!!\n"ESC"Rời khỏi.");
				return 0;
			}
			if (who->get_gender() == 2) gender = 1000;
			"sys/sys/test_db"->add_yuanbao(who,-50);
			who->add_exp(10);
			who->set_hair(gender+flag-60); //Thay đổi tóc theo case và giới tính (gender)
			who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who)); //Load lại nhân vật
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(" %s :\n Hãy thưởng thức diện mạo mới của ngươi đi nhé!\n"
			ESC"Đóng lại",get_name()));
			break;	
	}
}
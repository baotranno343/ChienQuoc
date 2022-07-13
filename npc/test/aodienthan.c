
#include <npc.h>
#include <ansi.h>

inherit OFFICER;

// 函数:获取人物造型
int get_char_picid() { return 9958; }
void do_welcome(string arg);

// 函数:构造处理
void create()
{
	set_name("Ảo Diện Thần");
	set_2("talk", (["welcome":(
								  : do_welcome:),
	]));

	setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	string ben, ben1;
	ben = who->get_save_2("doitoc.score") < 2 ? "Tôi muốn thay đổi kiểu tóc miễn phí" : "Tôi muốn dùng 10 Kim Bảo để thay đổi kiểu tóc";
	ben1 = who->get_save_2("doitoc.score") < 2 ? "Bây giờ có cơ hội miễn phí, ngươi hãy tận dụng !" : "Hiện tại cơ hội miễn phí của ngươi đã hết, ngươi có các lựa chọn để thay đổi diện mạo của ta dưới đây :";
	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf("%s : \nNày ! Ngươi có muốn thay đổi một chút diện mạo hiện tại không ? %s\n" ESC "%s\ntalk %x# welcome.1\n" ESC "Tôi muốn dùng 20.000 lượng để thay đổi khuôn mặt\ntalk %x# welcome.4\n"
																 //	ESC "Tôi muốn dùng 100.000 lượng để thay đổi màu tóc\ntalk %x# welcome.2\n"
																 ESC "Rời khỏi",
																 get_name(), ben1, ben, id, id, id));
}

void do_welcome(string arg)
{
	object me = this_object();
	__FILE__->do_welcome2(me, arg);
}

void do_welcome2(object me, string arg)
{
	int flag, id, gender;
	object who, who2;

	who = this_player();
	id = getoid(me);
	flag = to_int(arg);
	who->set_time("talk", 0);
	gender = who->get_gender() == 1 ? 0 : 1000;
	switch (flag)
	{
	case 1:
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf("%s :\n Hãy chọn một kiểu tóc mà ngươi thích.\n" ESC "Kiểu tóc Vô Môn Phái\ndoitoc2 + " + who->get_number() + " 1\n" ESC "Kiểu tóc Đào Hoa Nguyên\ndoitoc2 + " + who->get_number() + " 2\n" ESC "Kiểu tóc Thục Sơn\ndoitoc2 + " + who->get_number() + " 3\n" ESC "Kiểu tóc Cấm Vệ Quân\ndoitoc2 + " + who->get_number() + " 4\n" ESC "Kiểu tóc Đường Môn\ndoitoc2 + " + who->get_number() + " 5\n" ESC "Kiểu tóc Côn Luân\ndoitoc2 + " + who->get_number() + " 6\n" ESC "Kiểu tóc Vân Mộng Cốc\ndoitoc2 + " + who->get_number() + " 7\n" ESC "Kiểu tóc Mao Sơn\ndoitoc2 + " + who->get_number() + " 8\n"
																		 //	ESC HIY"Thay đổi màu tóc\ndoitoc2 998\n"
																		 //	ESC HIY"Thay đổi khuôn mặt\ndoitoc2 997\n"
																		 ESC "Thoát",
																	 get_name(), id, id, id, id, id, id, id, id, id, id));
		break;
		/*	case 2:
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf("%s :\n Hãy chọn màu tóc mà ngươi thích.\n"
			ESC"Xanh lá cây\ndoitoc2 - "+who->get_number()+" 1\n"
			ESC"Đỏ\ndoitoc2 - "+who->get_number()+" 2\n"
			ESC"Đen\ndoitoc2 - "+who->get_number()+" 3\n"
			ESC"Xanh da trời\ndoitoc2 - "+who->get_number()+" 4\n"
			ESC"Hồng\ndoitoc2 - "+who->get_number()+" 5\n"
			ESC"Trắng\ndoitoc2 - "+who->get_number()+" 6\n"
			ESC"Tím\ndoitoc2 - "+who->get_number()+" 7\n"
			ESC"Vàng\ndoitoc2 - "+who->get_number()+" 8\n"
			ESC"Olive\ndoitoc2 - "+who->get_number()+" 9\n"
			ESC"Cam\ndoitoc2 - "+who->get_number()+" 10\n"
			ESC"Hoàng Kim\ndoitoc2 - "+who->get_number()+" 11\n"
			ESC"Huỷ bỏ màu tóc\ndoitoc2 - "+who->get_number()+" 12\n"
			ESC HIY"Thay đổi kiểu tóc\ndoitoc2 999\n"
			ESC HIY"Thay đổi khuôn mặt\ndoitoc2 997\n"
			ESC"Thoát",get_name(),id,id,id,id,id,id,id,id,id,id,id,id,id,id,id,id));
			break;*/
	case 4:
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf("%s :\n Hãy chọn kiểu khuôn mặt mà ngươi thích.\n" ESC "Khuôn mặt 1 \ndoitoc2 @ 1\n" ESC "Khuôn mặt 2 \ndoitoc2 @ 2\n" ESC "Khuôn mặt 3 \ndoitoc2 @ 3\n" ESC "Khuôn mặt 4 \ndoitoc2 @ 4\n" ESC "Khuôn mặt 5 \ndoitoc2 @ 5\n"
																	 //	ESC HIY"Thay đổi kiểu tóc\ndoitoc2 999\n"
																	 //	ESC HIY"Thay đổi màu tóc\ndoitoc2 998\n"
																	 ESC "Thoát",
																	 get_name(), id, id, id, id, id));
		break;
		/*	if(who->get_save_2("doitoc.score")>=2)
			{	
				if ( "sys/sys/test_db"->get_yuanbao(who) < 100 )
				{
				send_user(who,"%c%c%w%s",':',3, 9958, me->get_name()+":\n Trên người ngươi không đủ 10 Kim Nguyên Bảo ! \n"ESC"Rời khỏi.");
				return 0;
				}
				"sys/sys/test_db"->add_yuanbao(who,-100);
			}*/
	}
}
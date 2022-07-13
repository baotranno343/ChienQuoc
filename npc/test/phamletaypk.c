
#include <npc.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5420; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Phạm Lễ");
		set_real_name("Tẩy PK");
        set_2( "talk", ([
				"welcome"          : (: do_welcome :),
        ]));

        setup();
}

void do_look( object who ) 
{
	int id = getoid( this_object() );
	send_user(who,"%c%c%w%s",':',3,get_char_picid(),get_name() + ":\n    Ta từng là một danh tướng nước Việt, nhưng nay đã trở thành một Thương Nhân chu du khắp thất quốc. Muốn giao dịch với ta có tiền chưa chắc đã đủ nên hãy xem cho kĩ thông tin về những dịch vụ của ta nhé! Phải tiêu hao 10%-30% điểm kinh nghiệm mới giảm đi 100 điểm PK. Giết người là tội tày đình cho nên ngươi phải chịu trừng phạt mà thôi.\n"+
		sprintf(ESC"Ta muốn sử dụng điểm Kinh Nghiệm để rửa tội\ntalk %x# welcome.1\n",id)+
		sprintf(ESC"Ta muốn kiểm tra điểm PK hiện tại\ntalk %x# welcome.2\n",id)+
		ESC"Thoát");
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,id,pk,exp;
	object who;
	
        who = this_player();
		id = getoid(me);
        flag = to_int(arg);
		pk = who->get_pk();
        exp = USER_EXP_D->get_level_exp(who->get_reincarnation(), who->get_level())*30/100*(who->get_pk()/100);
        who->set_time( "talk",  0);
        switch(flag)
        {
       	case 1:
			if ( who->get_pk() <= 0 )
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),get_name() + ":\n    Bạn là người đến đầu thú? trong thời gian này bạn không được phạm tội ah!");
				return 0;
			}
			else
			{
				send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(get_name() + ":\n    Cấp độ hiện tại của bạn là %d cấp, cần %d điểm Kinh Nghiệm để rửa tội.Bạn có chắc là muốn rửa tội?\n"
				ESC"Xác nhận\ntalk %x# welcome.11\n"
				ESC"Hủy bỏ",who->get_level(),exp,id));
				return 0;
			}
			break;
       	case 2:
			send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf(get_name() + ":\n    Số điểm PK hiện tại của bạn: %d điểm\n"
				ESC"Phản hồi\nlook %x#\n"
				ESC"Thoát",who->get_pk(),getoid(me)));
			break;
       	case 11:
			if ( who->get_upgrade_exp() < exp )
				return 0;
			send_user(who,"%c%s",';',sprintf("Bạn đã sử dụng %d điểm Kinh Nghiệm để rửa %d điểm PK!",exp,who->get_pk()));
			who->add_exp(-exp);
			who->add_pk(-pk);
			who->set_clean_pk_time(0);
			break;
        }
}

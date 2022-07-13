#include <npc.h>
#include <ansi.h>
#include <time.h>

inherit OFFICER;
// 函数:获取人物造型
int get_char_picid() { return 5109; }
void do_welcome(string arg);

// 函数:构造处理
void create()
{
        set_name("Vô Song Thành Thủ Vệ");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
}

void do_look(object who) { __FILE__->do_look_call(this_object(),who); }

void do_look_call(object me,object who)
{
	int id = getoid(me);

	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s:\n    Thành Vô Song, cử thế vô song! Vô Song Thành chính là tượng trưng cho địa vị và thế lực! Nếu có thể là chủ nhân của Vô Song Thành, đó sẽ là vinh quang rất lớn! Ngươi có muốn thử vào xem một chút không ?\n"
	ESC HIG"Mật mã thâm nhập vào Vô Song Thành\ntalk %x# welcome.101\n"
	ESC HIG"Tìm hiểu quy tắc công thành\ntalk %x# welcome.104\n"
	ESC HIG"Kiểm tra Bang hội công thành sắp tới\ntalk %x# welcome.107\n"
	ESC"Rời khỏi",me->get_name(),id,id,id));
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag, p,i,size,id,iTime,amount;
       	object who, item,*nTeam;
	  
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 101:
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s:\n Mật mã xâm nhập vào Vô Song Thành bao gồm :\n"
	ESC"Chuyển đến điện phía Đông Vô Song Thành\ntalk %x# welcome.1001\n"
	ESC"Chuyển đến điện phía Tây Vô Song Thành\ntalk %x# welcome.1002\n"
	ESC"Chuyển đến giữa Vô Song Thành\ntalk %x# welcome.1003\n"
	ESC"Chuyển đến võ trường phía Đông Vô Song Thành\ntalk %x# welcome.1004\n"
	ESC"Chuyển đến võ trường phía Tây Vô Song Thành\ntalk %x# welcome.1005\n"
	ESC"Rời khỏi",me->get_name(),getoid(me),getoid(me),getoid(me),getoid(me),getoid(me)));
        	break;	
		case 1001:		
		case 1002:		
		case 1003:		
		case 1004:		
		case 1005:
			"/sys/party/vstfix"->trans_into_wushuang(me,who,flag-1000);
			break;	
        case 104:
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n Quy tắc chiếm Vô Song Thành gồm :\n 1.Bang Chủ phải đến Chu Vương xin phép công thành. \n 2. Sau khi xin công thành, đến chỗ ta kiểm tra thời gian công thành ( ngày công thành là 2 ngày sau kể từ khi đăng kí công thành ). \n 3. Thời gian công thành là : mỗi đêm 7:30-9:00( chỉ diễn ra vào đêm công thành ). \n 4. Khi chiếm thành không được để bất kì người nào khác không phải Bang phái của mình trong Vô Song Cung. \n 5. Sau khi xin chiếm thành tại Quan Viên Vô Song Thành cố thủ đến 9:00 đêm sẽ hoàn toàn chiếm thành. \n"ESC"Rời khỏi", me->get_name(), ) );
        	break;	
        case 107:
        	"/sys/party/vstfix"->attack_list(me,who);
        	break;	
        	
        	
        }

}
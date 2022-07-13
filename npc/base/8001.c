
// 自动生成：/make/npc/make0001
#include <ansi.h>
#include <npc.h>
#include <cmd.h>

inherit OFFICER;

// 函数：当铺老板
int is_banker() { return 1; }
void do_welcome(string arg);
// 函数：获取人物造型
int get_char_picid() { return 5301; }

// 函数：构造处理
void create()
{
        set_name("Quản Khố");
        set_real_name("Quản Khố");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp= "";
	tmp += sprintf(ESC "Nhận lãnh Chiến Quốc Bảo Điển\ntalk %x# welcome.12\n",getoid(this_object()));
        send_user( who, "%c%c%w%s", ':', 3, get_char_picid(), 
                sprintf(" %s :\n "+"/quest/word"->get_normal_word(this_object())+"\n"
                        ESC "Tôi muốn sử dụng kho\npawn %x# 1\n"
			ESC "Tôi muốn mở rộng kho của tôi\npawn expand %x# 0\n"
                        + tmp +
                        ESC "Tôi chỉ xem qua vậy thôi\nCLOSE\n",get_name(), getoid(this_object()), getoid(this_object()) ) );	
	"/quest/help"->send_help_tips(who, 4);
}
void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}
void do_welcome2( object me, string arg )
{
	int flag,i,size,p,amount;
	object who,*inv,item;
	
	who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag) {
        	case 12:
			if(objectp(item = "/quest/zg_dict"->want_an_zgdict(me,who))) {
				p = item->move(who,-1);
				item->add_to_user(p);
				send_user(who,"%c%s",'!',"Ngươi đạt được Chiến Quốc Bảo Điển");
			}
        		break;
        }
}
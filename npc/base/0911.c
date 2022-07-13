#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：当铺老板
int is_banker() { return 1; }
void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5301; }

// 函数：构造处理
void create()
{
        set_name("Quản Khố Cự Thú Đảo");
        set_real_name("Quản Khố");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
        setup();
}

// 函数：对话处理
void do_look( object who )
{
        send_user( who, "%c%c%w%s", ':', 3, get_char_picid(), 
	sprintf(" %s :\n Quản lý kho trên đảo này, cần phải có dũng khí, ta không sợ thổ phỉ tấn công, chỉ sợ Cự Thú quái vật bắt đi!\n"
                        ESC "Ta muốn sử dụng kho\npawn %x# 1\n"
			ESC "Ta muốn mở rộng kho\npawn expand %x# 0\n"
                        ESC "Ta chỉ tiện thể xem xem\nCLOSE\n",get_name(), getoid(this_object()), getoid(this_object()) ) );
	"/quest/help"->send_help_tips(who, 4);                        
}
/*
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
        switch(flag)
        {	

	}
}
*/
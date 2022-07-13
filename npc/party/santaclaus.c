#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#define CHRISTMAS "sys/party/christmas"

inherit OFFICER;
int iStart,iFinish;

// 函数：获取人物造型
int get_char_picid() { return 9972; }
void do_welcome(string arg);
// 函数：构造处理
void create()
{
        set_name("Ông già Noel");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );

        setup();
	iStart = mktime(2020,11,22,0,0,0);	
	iFinish = mktime(2020,12,30,0,0,0);	

}

void do_look(object who)
{
        object me = this_object();
        
        if ( time() > iFinish )
        {
        	me->remove_from_scene();	
        	destruct(me);
        	return ;
        }
//	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    Tuy rằng Giáng sinh đã qua đi, nhưng thân lại là Ông già Noel thần kỳ không thể cứ như vậy rời đi. Vì cảm ơn mọi người đã nhiệt tình tham gia sự kiện vừa qua, chỉ cần người chơi đạt cấp độ 50 trở lên, trong khoảng thời gian này đến gặp ta có thể nhận lĩnh nhiều phần quà phong phú.\n"ESC"Vậy ta không khách khí nhé\ntalk %x# welcome.4\n"ESC"Lần sau lại tới.",me->get_name(),getoid(me)));
	CHRISTMAS->do_look(this_object(),who);
}


void do_welcome( string arg )
{
        object me = this_object();
        CHRISTMAS->do_welcome(me, arg);
}

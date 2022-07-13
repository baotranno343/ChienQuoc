#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 6010; }
void do_bonus();
void do_welcome(string arg);
void read_renwang();
void read_lifeskill();

// 函数：构造处理
void create()
{
        set_name("如意仙子");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
}

void do_look(object who)
{
	int id = getoid(this_object());

	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("如意仙子：\n    您好！我是如意仙子。欢迎您来到大话战国的世界，为了鼓励您的事业进取心，姐姐决定送给您一份礼物。\n"ESC"领取礼物\ntalk %x# welcome.1\n"ESC"离开",id));
	
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag, p,iTime,i,size;
       	object who, item;
       	string name;
	mixed *mxTime;    
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
     	        if ( who->get_level() < 10 )
     	        {
     	        	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"如意仙子：\n    你现在的等级还不到10级，礼物还暂时不能送给你。等你10级之后再来找我吧。");
			return ;
		}
		if ( who->get_save("ruyi_gift") )
        	{
     	        	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"如意仙子：\n    怎么？晶石的效果不错吧～精炼后的武器在消灭怪物之后的效率一定会更高。");
			return ;
		}
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("如意仙子：\n    到十级了，对武器装备都会有不同的要求了，如意仙子我决定送你3颗可以给武器装备附加属性的晶石，如果你按照从低到高的等级顺序，依次将这3颗晶石附加在武器或者防具上，你会看到它们的功能增强不少哦～记住，这些晶石只对20级以下的装备生效。\n"ESC"领取\ntalk %x# welcome.2\n"ESC"离开",getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() < 10 )
        		return ;
        	if ( who->get_save("ruyi_gift") )
        		return ;
		if ( TASK_LEGEND_D->can_carry_amount(who,6) != 1 )
        			return ;
		for(i=1;i<4;i++)
		{
			item = new("item/93/9343");
			item->set_level(i);
			p = item->move(who,-1);
			item->add_to_user(p);
		}
		for(i=1;i<4;i++)
		{
			item = new("item/93/9345");
			item->set_level(i);
			p = item->move(who,-1);
			item->add_to_user(p);
		}
		send_user(who,"%c%s",'!',"恭喜你得到如意仙子的礼物");
		who->set_save("ruyi_gift",1);
        	break;
	}

}
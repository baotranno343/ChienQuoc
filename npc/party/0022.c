#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>
#include <task.h>

#define _TEST

inherit OFFICER;
inherit SAVE_F;
int iStart1,iFinish1,year1,year2,mon1,mon2,day1,day2;
// 函数：获取人物造型
int get_char_picid() { return 5420; }
void do_welcome(string arg);

string get_save_file()	{ return "data/dodolook"SAVE_EXTENSION;}

// 函数：构造处理
void create()
{
        restore();
        set_real_name("七国游活动向导");
        set_name("糊葛");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
	set("mpLegend",([0:({32}),]));
        if ( !clonep(this_object()) )
        	return ;
        if (MAIN_D->get_host_type()==2)		//台湾除外
        	call_out("go_there",2);
}
string get_short() 
{ 
	if ( stringp(get_real_name()) )
		return get_name() + "|" + get_real_name();
	else
		return get_name();
}
void do_look(object who) { __FILE__->do_look_call(this_object(),who); }
void do_look_call(object me,object who)
{
	int id = getoid(me);
	int iTime=time();
	
	if (MAIN_D->get_host_type()==2)
		return ;
	if ( who->get_birthday() > iStart1 && iTime > iStart1 && iTime < iFinish1 && !who->get_save("dodolook") )	
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    我叫糊葛，来自另一个时空。我来寻找一个叫dodolook的女孩，你可曾见过她？\n"ESC"没见过\ntalk %x# welcome.2\n"ESC"见过\ntalk %x# welcome.3\n"ESC"打个招呼\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),id,id,id));
	else
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    我叫糊葛，来自另一个时空。我来寻找一个叫dodolook的女孩，你可曾见过她？\n"ESC"打个招呼\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),id,));
}

void do_welcome(string arg) { __FILE__->do_welcome_call(this_object(),arg); }

void do_welcome_call( object me,string arg )
{
	int flag, p,iTime,i,size,id,level,iLev;
       	object who, item;
       	string name,*nTmp,tmp;
	mixed *mxTime;  
	
	
	if (MAIN_D->get_host_type()==2)
		return ;
		
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
	case 2:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    噢！倘若你见到她的时候，还望你告知我一声！",me->get_name()));
		break;
	case 3:
		if ( who->get_birthday() < iStart1 )
		{
			send_user(who,"%c%s",'!',"活动期间创建的角色才能参加");
			return ;	
		}
        	if ( time() < iStart1 )
        	{
        		return ;	
        	}
        	if ( who->get_save("dodolook") )
        		return ;
               	if ( time() > iFinish1 )
        	{
        		return ;	
        	}
        	if ( who->get_level() < 10 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    胡说！就你的等级还没离开过新手村吧。我在这里好久了都没见过她，你不要欺骗我了。\n"ESC"承认自己撒谎\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),id,));
        		return ;	
        	}
        	
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    啊！真的？那太好了！你能帮我一个忙么？\n"ESC"愿意\ntalk %x# welcome.6\n"ESC"离开",me->get_name(),id,));
        	break;
	case 4:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    关于dodolook的战国冒险是一个很长的故事，还有无数奇异的冒险经历伴随其中。你很幸运加入到这个过程中来。想知道更多的细节？你可以去zg.mop.com看看，受益一定匪浅！",me->get_name()));
		break;
	case 5:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    没有关系，"HIR"等你到了十级可以离开这里的时候再来找我，那时我将会托付于你一件事！"NOR"也许我们真的有缘！看你衣衫褴褛，十分狼狈，不如我送你点好吃的吧！\n"ESC"接受馈赠\ntalk %x# welcome.7\n"ESC"离开",me->get_name(),id,));
		break;
	
	case 6:
        	if ( time() < iStart1 )
        	{
        		return ;	
        	}
        	if ( who->get_save("dodolook") )
        		return ;
               	if ( time() > iFinish1 )
        	{
        		return ;	
        	}
        	if ( who->get_level() < 10 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    胡说！就你的等级还没离开过新手村吧。我在这里好久了都没见过她，你不要欺骗我了。\n"ESC"承认自己撒谎\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),id,));
        		return ;	
        	}
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    据闻有人在魏国看到过dodolook的行踪，你前去打探一下。倘若寻不到的话，你就去拜访下魏昭王，说不定就是魏昭王把她抓起来了！\n"ESC"拜访魏昭王\ntalk %x# welcome.8\n"ESC"离开",me->get_name(),id,));
		break;
	case 7:
        	if ( who->get_save("dodolook_gift") )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你已经接受过馈赠了！",me->get_name()));
        		return ;	
        	}
        	if ( USER_INVENTORY_D->count_empty_carry(who) < 2 )
		{
			send_user(who,"%c%s",'!',"清理一下你的包包！");
			return ;	
		}	
		//行军散5个
		item = new("item/91/9100");
		item->set_amount(5);
		p = item->move(who,-1);
		item->add_to_user(p);
		//5级项链
		item = new("item/86/0001");
		item->set_bind(3);
		p = item->move(who,-1);
		item->add_to_user(p);
        	who->set_save("dodolook_gift",1);
        	send_user(who,"%c%s",'!',"你得到糊葛的馈赠");
		break;
	case 8:
		if ( time() < iStart1 )
        	{
        		return ;	
        	}
        	if ( who->get_save("dodolook") )
        		return ;
               	if ( time() > iFinish1 )
        	{
        		return ;	
        	}
        	if ( who->get_level() < 10 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    胡说！就你的等级还没离开过新手村吧。我在这里好久了都没见过她，你不要欺骗我了。\n"ESC"承认自己撒谎\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),id,));
        		return ;	
        	}
        	who->set_save("dodolook",1);
        	send_user(who,"%c%s",'!',"得到任务"HIR"拜访魏昭王");
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_DODOLOOK,"寻找dodolook" ); 
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DODOLOOK, 1, "拜访魏昭王" );
		break;		
	}


}

void go_there()
{
	object me=this_object();
	
	me->add_to_scene(802,78,43,2);
}

int set_open(object who,string arg)
{
	int date1,date2;
	if ( sscanf(arg ,"%d-%d",date1,date2) != 2 )
	{
		send_user(who,"%c%s",'!',"错误的格式！");	
		return 0;
	}
	year1 = date1 /10000;
	mon1 = date1 % 10000 / 100;
	day1 = date1 % 10000 % 100;
	year2 = date2 /10000;
	mon2 = date2 % 10000 / 100;
	day2 = date2 % 10000 % 100;
	if ( !year1 || !mon1 || !day1 || !year2 || !mon2 || !day2 )
	{
		send_user(who,"%c%s",'!',"错误的时间！");	
		return 0;
	}
	iStart1 = mktime(year1,mon1,day1,0,0,0);	
	iFinish1 = mktime(year2,mon2,day2,0,0,0);		
	if ( iStart1 > iFinish1 )
	{
		send_user(who,"%c%s",'!',"错误的时间！！");	
		return 0;
	}
	tell_user(who,"活动开启：%s！",arg);	
	send_user(who,"%c%s",'!',"寻找dodolook活动开启！");	
	save();
	return 1;
}

int set_close(object who)
{
	iStart1 = 0;	
	iFinish1 = 0;		
	send_user(who,"%c%s",'!',"寻找dodolook活动关闭！");	
	save();
	return 1;	
}
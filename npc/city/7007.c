
// 自动生成：/make/npc/make8007

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define DIPLOMAT_D      "/inh/city/diplomat"

inherit OFFICER;

void do_relation( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Yên Quốc Sử Tiết");
	set_real_name("Tần Khai");
        set_city_name("Yên Quốc");

        set_2( "talk", ([
                "relation"      : (: do_relation :),
                "welcome"	: (: do_welcome :),
        ]) );
 	set("mpLegend2",([0:({32*32+5,32*32+8,}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if (  who->get_legend(TASK_32,4) && !who->get_legend(TASK_32,5)  )
	{
		tmp += sprintf(ESC HIY "使节的信\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_32,5) && !who->get_legend(TASK_32,6)) || (who->get_legend(TASK_32,6) && !who->get_legend(TASK_32,8)) )
	{
		tmp = sprintf(ESC HIY "差事\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		DIPLOMAT_D->do_look( who, this_object() ); 
	
}
void do_relation( string arg ) { DIPLOMAT_D->do_relation( this_player(), this_object(), arg ); }


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p;
        object who,item,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if (  who->get_legend(TASK_32,4) && !who->get_legend(TASK_32,5)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哦？是齐国内政官孟尝君啊，不错，上次我还送了他夫人一对燕北的路大师制作的燕蝶手镯呢，他还有事找我帮忙，哦，是他夫人的事？哈哈哈，老夫明白，让我看看信。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_32,5) && !who->get_legend(TASK_32,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，原来是内政官夫人尝到上次我带给燕王喜的荔枝，想再多要点，可惜了，我带去的荔枝都是那个时节才有，现在除了一个地方还能保存荔枝外其他地方已经没有了。困魔阵是阴寒之地，那里的邪灵喜欢收集这种东西，并且能够保持长久不坏。如果你想帮助他取点回去，就去困魔阵碰碰运气吧。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_32,6) && !who->get_legend(TASK_32,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你还没找到荔枝，那只得麻烦你多跑几趟了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_32,7) && !who->get_legend(TASK_32,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    找来了荔枝，我还得派人送过去，路途遥远，又害怕荔枝坏掉，还真有点麻烦呀。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 2:
        	if(  who->get_legend(TASK_32,4) && !who->get_legend(TASK_32,5)  )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"赵国内政官的信",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_32,5);
			who->add_exp(58000);
			who->add_potential(850);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"使节的差事（1） 经验 58000 潜能 850 金钱 50000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,54,"" );
			me->do_welcome(1);
        	}
        	break;   
        case 3:
        	if ( who->get_legend(TASK_32,5) && !who->get_legend(TASK_32,6) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_32,6);
        		who->delete_save("ygsjlizi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,53,"使节的差事（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"使节的差事（2）");
        	}
        	break;
        case 4:
        	if ( who->get_legend(TASK_32,7) && !who->get_legend(TASK_32,8) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"荔枝",10) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_32,8);
        		who->delete_save("ygsjlizi");
			who->add_exp(65000);
			who->add_potential(920);
			who->add_cash(55000);
			send_user(who,"%c%s",';',"使节的差事（2） 经验 65000 潜能 920 金钱 55000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,53,"" );
        	}
        	break;
        case 99:	
		DIPLOMAT_D->do_look( who, me); 
        	break;
        }
}
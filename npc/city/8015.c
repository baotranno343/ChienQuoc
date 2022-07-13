
// 自动生成：/make/npc/make8014

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_enter();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 9390; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Chu Quốc Thủ Vệ");
        set_city_name("Chu Quốc");

        set_2( "talk", ([
                "enter"         : (: do_enter :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 13);
        set("out", 11);
 	set("mpLegend2",([0:({32*20+14}),]));
        setup();
}

string get_master() { return CITY_ZHOU->get_master(); }
string get_master_2() { return CITY_ZHOU->get_master_2(); }
string get_master_3() { return CITY_ZHOU->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( who->get_legend(TASK_20,13)&&!who->get_legend(TASK_20,15) )
	{
		tmp = sprintf(ESC HIY "菊花酒\ntalk %x# welcome.1\n",getoid(me));
	}

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look( who, me ); 
	
}
void do_enter() { GUARDER_D->do_enter( this_player(), this_object() ); }

void do_record() { GUARDER_D->do_record( this_player(), this_object() ); }

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_legend(TASK_20,13)&&!who->get_legend(TASK_20,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是秦国百姓仲莫叫你来的吧？他上次就给我打过招呼了，你拿这些雏菊去吧！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_20,14)&&!who->get_legend(TASK_20,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我母亲都在九月九日这天，采下初开的菊花和一点青翠的枝叶，掺和在准备酿酒的粮食中，然后一齐用来酿酒，放至第二年九月九日饮用。九九重阳，阳气旺盛才酿得出好酒。传说喝了这种酒，可以延年益寿。\n"ESC"离开", me->get_name()));
        	break;
        case 2:
        	if ( who->get_legend(TASK_20,13)&&!who->get_legend(TASK_20,14) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0092");
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!',"你携带的物品太多了");	
        			return;
        		}
        		item->add_to_user(p);
			who->set_legend(TASK_20,14);
			who->add_exp(7000);
			who->add_potential(260);
			who->add_cash(7500);
			send_user(who,"%c%s",';',"重阳节（2） 经验 7000 潜能 260 金钱 7500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,51,"" );
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,52,"重阳节（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"重阳节（3）");
        	}
        	break;   
        case 99:
        	GUARDER_D->do_look( who, me ); 
        	break;     
        }
}
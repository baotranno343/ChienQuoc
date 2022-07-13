
// 自动生成：/make/npc/make8012

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_out();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 5209; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Ngụy Quốc Thủ Vệ");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "out"           : (: do_out :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 13);
        set("out", 11);
//        set("level",30);
//        set("legend",({32*37+23}));
 	set("mpLegend",([25:({32*37+23}),]));
        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

void do_look( object who ) 
{ 
	string tmp="";
	object me = this_object();
	if ( who->get_level() >= 25 && !who->get_legend(TASK_37,23) )
	{
		tmp += sprintf(ESC HIY "临终委托\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look_2( who, me ); 
	
}
void do_out() { GUARDER_D->do_out( this_player(), this_object() ); }

void do_record() { GUARDER_D->do_record( this_player(), this_object() ); }

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
       	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
 	case 1:
        	if ( who->get_level() >=25 && !who->get_legend(TASK_37,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    想起那个人，我的心还久久不能平静，不是激动，不是愤怒，是心酸……\n    前些日子，魏城外来了一个人，他踉跄地走到我身边，将这枚棋子递给我，并请我将这枚棋子交给楚总管，当时我告诉他，这里是魏国，他有些绝望，告诉我他从很远的地方来，受了很重的伤，而这枚棋子是他联络楚总管的唯一方法，因为这是当初他们结义时留下的信物，他恳请我无论如何一定要送到楚总管手上，让楚总管知道，他的兄弟已经被人杀害。说完这番话，他重重地倒在了我身前……\n    现在，请你将这枚棋子送到楚总管手中吧，并且告诉他，我已将他的兄弟厚葬。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_level() >=25 && !who->get_legend(TASK_37,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0179",1);	
        		who->set_legend(TASK_37,23);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,66,"临终委托" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"临终委托");
        	}
        	break;       
   
        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;     
        }
}

// 自动生成：/make/npc/make8014

#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <task.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_enter();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 0552; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Yên Quốc Thủ Vệ");
        set_city_name("Yên Quốc");

        set_2( "talk", ([
                "enter"         : (: do_enter :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("out", 11);
        set("in", 13);
//       	set("level",92);
//	set("legend",({32*32+1}));
 	set("mpLegend",([90:({32*32+1}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,1) )
	{
		tmp = sprintf(ESC HIY "单刀\ntalk %x# welcome.1\n",getoid(me));
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
        int flag,p;
        object who,item,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    在困魔阵中有一些骸骨精，他们生前是上古神魔大战的将士，死后也不忘战斗，他们以自身的魔气淬炼了他们携带的单刀，使得他们的单刀无坚不摧，我们大将军非常希望得到这种刀装备我们的战士，你去困魔阵中杀掉骸骨精抢来8把单刀，给我们大将军验看一下。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,1)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_32,1);
        		who->delete_save("ygswdandao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,43,"单刀" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"单刀");
        	}
        	break;


        case 99:
        	GUARDER_D->do_look( who, me ); 
        	break;
        }
}
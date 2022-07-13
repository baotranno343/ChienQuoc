
// 自动生成：/make/npc/make8012

#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <task.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_out();
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
                "out"           : (: do_out :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 12);
        set("out", 10);
//       	set("level",93);
//	set("legend",({32*32+11}));
 	set("mpLegend",([90:({32*32+11}),]));
 	set("mpLegend2",([90:({32*32+13}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( (who->get_level() >= 90 && !who->get_legend(TASK_32,11)) || (who->get_legend(TASK_32,11) && !who->get_legend(TASK_32,13)) )
	{
		tmp = sprintf(ESC HIY "净化灵魂\ntalk %x# welcome.1\n",getoid(me));
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
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如今困魔阵中妖气冲天，困魔阵封印有松动趋势，恐怕如果任由其自行发展，会有意想不到的变化或者有妖人利用，我希望你能前往消灭尸魔八个、怨灵六个，压制一下妖气，避免百姓恐慌。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_32,11)  && !who->get_legend(TASK_32,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，你居然拿他们无能为力？莫非真的开始出现什么意料之外的变化了么？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_32,12)  && !who->get_legend(TASK_32,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    困魔阵中妖气已经减弱，相信暂时不会有什么变故了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,11)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_32,11);
        		who->delete_save("ygswsimo");
        		who->delete_save("ygswyuanling");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,44,"净化灵魂" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"净化灵魂");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_32,12) && !who->get_legend(TASK_32,13) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_32,13);
        		who->delete_save("ygswsimo");
        		who->delete_save("ygswyuanling");
			who->add_exp(63000);
			who->add_potential(905);
			who->add_cash(53500);
			send_user(who,"%c%s",';',"净化灵魂 经验 63000 潜能 905 金钱 53500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,44,"" );
        	}
        	break;

        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;
        }
}

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
        set("in", 13);
        set("out", 11);
//       	set("level",93);
//	set("legend",({32*32+17}));
 	set("mpLegend",([90:({32*32+17}),]));
 	set("mpLegend2",([90:({32*32+19}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( (who->get_level() >= 90 && !who->get_legend(TASK_32,17)) || (who->get_legend(TASK_32,17) && !who->get_legend(TASK_32,19)) )
	{
		tmp = sprintf(ESC HIY "堕落的力量\ntalk %x# welcome.1\n",getoid(me));
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
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我昨晚做了一个梦，梦见困魔阵中的骷髅妖与骸骨精们，不断的自相吞噬，成为越来越大的妖魔，最后冲天而起，化成冲天的黑雾，笼罩了整个大燕，黑雾过处，宫室人畜无一幸存，满目都是断壁残垣，断臂残肢，看的我心神俱裂，大叫醒来。太可怕了，如此看来，那些堕落了的骷髅妖与骸骨精们如若不消灭，必定日渐强大，祸国殃民啊，你速速先去消灭消灭骷髅妖、骸骨精各8只，我会找更多人竭力去阻止他们。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_32,17)  && !who->get_legend(TASK_32,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，莫非梦魇就将变为现实了么，这可如何是好？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_32,18)  && !who->get_legend(TASK_32,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这样子，一点点消耗他们的力量，应该可以把一场大祸化于无形了吧。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,17)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_32,17);
        		who->delete_save("ygswkulouy");
        		who->delete_save("ygswhaiguj");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,46,"堕落的力量" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"堕落的力量");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_32,18) && !who->get_legend(TASK_32,19) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_32,19);
        		who->delete_save("ygswkulouy");
        		who->delete_save("ygswhaiguj");
			who->add_exp(63000);
			who->add_potential(905);
			who->add_cash(53800);
			send_user(who,"%c%s",';',"堕落的力量 经验 63000 潜能 905 金钱 53800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,46,"" );
        	}
        	break;

        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;
        }
}
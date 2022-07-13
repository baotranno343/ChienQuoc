
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
int get_char_picid() { return 0600; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Thủ Vệ");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "enter"         : (: do_enter :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("out", 11);
        set("in", 13);
//        set("level",84);
//        set("legend",({32*28+17}));
 	set("mpLegend",([80:({32*28+17})]));
 	set("mpLegend2",([80:({32*28+19})]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who ) 
{ 
	string tmp="";
	object me = this_object();

	if ( (who->get_level() >= 80 && !who->get_legend(TASK_28,17)) || (who->get_legend(TASK_28,17) && !who->get_legend(TASK_28,19)))
	{
		tmp = sprintf(ESC HIY "不安的魂魄\ntalk %x# welcome.1\n",getoid(me));
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
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_28,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    万人坑里面怨气很重，因为当初大多是遭遇横死的异地商客，他们因为有欲望未曾满足，躁动不安，继而危害四周，他们依附怨气而拥有了强大的邪恶的力量，而怨气使得很多高人都望而却步，尤其是僵尸危害甚广，纠集起来，成为了一股巨大的邪恶势力，如果你能够消灭20个僵尸减弱他们的力量，那我会代替受害的百姓多谢你。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_28,17) && !who->get_legend(TASK_28,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你有胆量去，却没能力完成？可别叫我小看你！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_28,18) && !who->get_legend(TASK_28,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    果然是有胆量的人，不错！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
  
        	break;
	case 2:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_28,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,17);
			who->delete_save("zgswjiangsi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,50,"不安的魂魄" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"不安的魂魄");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_28,18) && !who->get_legend(TASK_28,19) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/62074",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,19);
			who->delete_save("zgswjiangsi");
			who->add_exp(50000);
			who->add_potential(700);
			who->add_cash(48000);
			send_user(who,"%c%s",';',"不安的魂魄 经验 50000 潜能 700 金钱 48000 祝融火枪图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,50,"" );
        	}
        	break; 
        case 99:
        	GUARDER_D->do_look( who, me ); 
        	break;     
        }
}
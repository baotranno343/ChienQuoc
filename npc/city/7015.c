
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
        set("out", 10);
        set("in", 12);
//       	set("level",92);
//	set("legend",({32*31+27}));
 	set("mpLegend",([90:({32*31+27}),110:({32*44+1}),]));
 	set("mpLegend2",([90:({32*31+29}),110:({32*44+3}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( (who->get_level() >= 90 && !who->get_legend(TASK_31,27)) || (who->get_legend(TASK_31,27) && !who->get_legend(TASK_31,29)) )
	{
		tmp = sprintf(ESC HIY "援助\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >= 110 && !who->get_legend(TASK_44,1)) || (who->get_legend(TASK_44,1) && !who->get_legend(TASK_44,3)) )
		tmp += sprintf(ESC HIY "黑暗笼罩\ntalk %x# welcome.4\n",getoid(me));

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
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_31,27)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，我们几个守卫上次追捕天牢逃犯严飞的时候结果被逃犯打伤，整日呕血，头也疼的厉害，据说那家伙是什么神武堂的堂主，后来找许多医师看，都无计可施，远方亲戚秦药师倒是建议我们去找气脉丹，说我们受的是内伤，一般药是治不得的，他说困魔阵中可以找到，不知这位壮士能否为我等跑一趟？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,27) && !who->get_legend(TASK_31,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    怎么？没有么？唉，看来我们只有等死了……\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_31,28) && !who->get_legend(TASK_31,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    再造之恩，席某先谢过了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_31,27)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,27);
        		who->delete_save("ygswqimaidan");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,42,"援助" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"援助");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_31,28) && !who->get_legend(TASK_31,29) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"气脉丹",5) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,29);
        		who->delete_save("ygswqimaidan");
			who->add_exp(62000);
			who->add_potential(900);
			who->add_cash(53000);
			send_user(who,"%c%s",';',"援助 经验 62000 潜能 900 金钱 53000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,42,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 110 && !who->get_legend(TASK_44,1)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    自从天降异象，地气紊乱，大乱将至，鬼蜮乱舞，城外被地煞门和天极门盘踞之后情况更加糟糕，如今整个城市被一堆妖魔鬼怪搅得天昏地暗，人们都惶惶不可终日，看大侠你武艺高强，宅心仁厚，定不忍百姓如此受苦，恳求你伸以援手，去消灭地煞门众守9个，太极门众守11个，拯救一下受苦受难的百姓吧。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_44,1) && !who->get_legend(TASK_44,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，街道上冷冷清清，家家关门闭户，不知道何时才能得到安宁啊……\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_44,2) && !who->get_legend(TASK_44,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    幸亏有你们这些仗义的侠客遏制了他们，我们百姓才能有一点生存的空间啊。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 5:
        	if ( who->get_level() >= 110 && !who->get_legend(TASK_44,1)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_44,1);
        		who->delete_save("ygswdismzs");
        		who->delete_save("ygswtaijmzs");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,51,"黑暗笼罩" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"黑暗笼罩");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_44,2) && !who->get_legend(TASK_44,3) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_44,3);
        		who->delete_save("ygswdismzs");
        		who->delete_save("ygswtaijmzs");
			who->add_exp(90000);
			who->add_potential(973);
			who->add_cash(93500);
			send_user(who,"%c%s",';',"黑暗笼罩 经验 90000 潜能 973 金钱 93500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,51,"" );
        	}
        	break;
        case 99:
        	GUARDER_D->do_look( who, me ); 
        	break;
        }
}
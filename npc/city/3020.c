
// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0452; }
void do_welcome(string arg);

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

int is_self_look() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Công Tượng");
        set_city_name("Triệu Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",56);
//	set("legend",({32*14+21}));
	set("mpLegend",([55:({32*14+21,32*17+1}),80:({32*28+20})]));
	set("mpLegend2",([55:({32*14+23,32*17+3}),80:({32*28+22})]));
	set_skill(0680, 80);
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_14,21) ) || ( who->get_legend(TASK_14,21) && !who->get_legend(TASK_14,23) ) )
	{
		tmp = sprintf(ESC HIY "长城泪\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_17,1) ) || ( who->get_legend(TASK_17,1) && !who->get_legend(TASK_17,3) ) )
	{
		tmp += sprintf(ESC HIY "夜空中的灵光\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( ( who->get_level() >= 80 && !who->get_legend(TASK_28,20) ) || ( who->get_legend(TASK_28,20) && !who->get_legend(TASK_28,22) ) )
	{
		tmp += sprintf(ESC HIY "最后一战\ntalk %x# welcome.7\n",getoid(me));
	}
	tmp += sprintf(ESC"学习生活技能\nlearn ? %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}
int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 1 ); }

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
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_14,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    做工匠的每日累死累活，不只是工作辛苦，还被雇主不当人看。\n    那恶工头赵四天天欺压我们，这都不说了，谁要我们生来就是苦命的娃，过分的是，他居然还克扣我们的工钱，这些工钱可是我们拿尊严拿性命换来的啊！\n    %s，你可要为我们做主啊！那赵四就在燕长城的匝道上。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	else if ( who->get_legend(TASK_14,21) && !who->get_legend(TASK_14,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我这条命是要丢在那长城上面了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_14,22) && !who->get_legend(TASK_14,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了，再也不会被人欺负了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_14,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_14,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,10,"长城泪" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"长城泪");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_14,22) && !who->get_legend(TASK_14,23) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/stuff/0257",2);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_14,23);
			who->add_exp(6000);
			who->add_potential(240);
			who->add_cash(6000);
			send_user(who,"%c%s",';',"长城泪 经验 6000 潜能 240 金钱 6000 铁套 2");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,10,"" );
        	}
        	break;   
 	case 4:
        	if ( who->get_level() >=55 && !who->get_legend(TASK_17,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    别看我是个老工匠了，可有些时候遇到一些问题还真难搞定，就说那些细活吧，有时候物品太小，还得在上面雕花打磨的，真是头痛。我知道有一种镜子，把它放在物品上，可以放大，我想有了这个东西，那些细活不是容易多了，这镜子就叫灵光镜，稀有东西，难得找到啊～\n    昨晚在燕长城的烽火台处，我见到有一道灵光射出，估计就是那灵光镜放射出来的，你去帮我找找吧！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_17,1) && !who->get_legend(TASK_17,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我得亲自去寻找那面宝镜。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_17,2) && !who->get_legend(TASK_17,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈…我发财了！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 5:
        	if( who->get_level() >=55 && !who->get_legend(TASK_17,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_17,1);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,20,"夜空中的灵光" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"夜空中的灵光");
        	}
        	break;       
        case 6:
        	if ( who->get_legend(TASK_17,2) && !who->get_legend(TASK_17,3) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"灵光镜",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_17,3);
			who->add_exp(6600);
			who->add_potential(250);
			who->add_cash(6200);
			send_user(who,"%c%s",';',"夜空中的灵光 经验 6600 潜能 250 金钱 6200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,20,"" );
        	}
        	break;     
 	case 7:
        	if ( who->get_level() >=80 && !who->get_legend(TASK_28,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我的儿子为了百姓的安全去了万人坑，与那些刀盾骷髅作战，他多次从死亡边缘逃了回来，直到我收到他的一封信，说是他们开始一场最大的战争，准备一举歼灭那些刀盾骷髅，之后就再也没有了他的消息，请你一定要替我报这个仇，去万人坑消灭掉他们。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_28,20) && !who->get_legend(TASK_28,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你实在是无能为力，那我考虑找别人来帮助我报这个仇！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_28,21) && !who->get_legend(TASK_28,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    终于报了这个仇，我该如何感谢你！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 8:
        	if( who->get_level() >=80 && !who->get_legend(TASK_28,20) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,20);
   			who->delete_save("zggjdaodkl");
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,51,"最后一战" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"最后一战");
        	}
        	break;       
        case 9:
        	if ( who->get_legend(TASK_28,21) && !who->get_legend(TASK_28,22) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/62076",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,22);
   			who->delete_save("zggjdaodkl");
			who->add_exp(51000);
			who->add_potential(705);
			who->add_cash(48800);
			send_user(who,"%c%s",';',"最后一战 经验 51000 潜能 705 金钱 48800 冰魄银针图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,51,"" );
        	}
        	break;   
        }
}
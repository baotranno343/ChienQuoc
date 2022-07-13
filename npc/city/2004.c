
// 自动生成：/make/npc/make8004

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

void do_build( string arg );
void do_upgrade( string arg );
void do_plant( string arg );
void do_food( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Nội Chính Quan");
	set_real_name("Thân Bất Hại");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "build"         : (: do_build :),
                "upgrade"       : (: do_upgrade :),
                "plant"         : (: do_plant :),
                "food"          : (: do_food:),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",16);
//	set("legend",({32*4+4}));
	set("mpLegend",([15:({32*4+4,32*4+11}),70:({32*22+21})]));
	set("mpLegend2",([0:({32*25+18,32*25+21,32*25+30,32*26+13,32*26+16,32*26+28,32*27+3,}),15:({32*4+6,32*4+12,}),70:({32*22+23,}),]));
        setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,4) ) || ( who->get_legend(TASK_04,4) && !who->get_legend(TASK_04,6) ) )
	{
		tmp = sprintf(ESC HIY "内政官的烦恼\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,11) ) || ( who->get_legend(TASK_04,11) && !who->get_legend(TASK_04,12) ) )
	{
		tmp += sprintf(ESC HIY "宫廷的喧闹\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( ( who->get_level() >= 70 && !who->get_legend(TASK_22,21) ) || ( who->get_legend(TASK_22,21) && !who->get_legend(TASK_22,23) ) )
	{
		tmp += sprintf(ESC HIY "烹鱼的佐料\ntalk %x# welcome.8\n",getoid(me));
	}
	if ( who->get_legend(TASK_25,17) && !who->get_legend(TASK_25,18) )
		tmp += sprintf(ESC HIY "出谋献策\ntalk %x# welcome.11\n",getoid(me));
	if ( (who->get_legend(TASK_25,18) && !who->get_legend(TASK_25,19)) || (who->get_legend(TASK_25,19) && !who->get_legend(TASK_25,21)) )
		tmp += sprintf(ESC HIY "挑战自己\ntalk %x# welcome.11\n",getoid(me));
	if ( who->get_legend(TASK_25,21) && !who->get_legend(TASK_25,22) )
		tmp += sprintf(ESC HIY "清除奸贼\ntalk %x# welcome.11\n",getoid(me));
	if ( who->get_legend(TASK_25,29) && !who->get_legend(TASK_25,30) )
		tmp += sprintf(ESC HIY "内政官的心事\ntalk %x# welcome.16\n",getoid(me));
	if ( who->get_legend(TASK_25,30) && !who->get_legend(TASK_26,1) )
		tmp += sprintf(ESC HIY "寻求帮助\ntalk %x# welcome.16\n",getoid(me));
	if ( who->get_legend(TASK_26,12) && !who->get_legend(TASK_26,13) )
		tmp += sprintf(ESC HIY "御史的担心\ntalk %x# welcome.19\n",getoid(me));
	if ( (who->get_legend(TASK_26,13) && !who->get_legend(TASK_26,14)) || (who->get_legend(TASK_26,14) && !who->get_legend(TASK_26,16)) )
		tmp += sprintf(ESC HIY "试探实力\ntalk %x# welcome.19\n",getoid(me));
	if ( who->get_legend(TASK_26,16) && !who->get_legend(TASK_26,17) )
		tmp += sprintf(ESC HIY "为民除害\ntalk %x# welcome.19\n",getoid(me));
	if ( who->get_legend(TASK_26,27) && !who->get_legend(TASK_26,28) )
		tmp += sprintf(ESC HIY "寻求方法\ntalk %x# welcome.24\n",getoid(me));
	if ( (who->get_legend(TASK_26,28) && !who->get_legend(TASK_27,1)) || (who->get_legend(TASK_27,1) && !who->get_legend(TASK_27,3)) )
		tmp += sprintf(ESC HIY "防止泄密\ntalk %x# welcome.24\n",getoid(me));
	if ( who->get_legend(TASK_27,3) && !who->get_legend(TASK_26,29) )
		tmp += sprintf(ESC HIY "上奏韩王\ntalk %x# welcome.24\n",getoid(me));
	if ("/sys/sys/count"->get_refine()&&who->get_city_name()==me->get_city_name())
		tmp += sprintf(ESC"收妖壶任务\ntalk %x# welcome.1000\n",getoid(me)); 
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INTERIOR_D->do_look( who, this_object() ); 
	
}

void do_build( string arg ) { INTERIOR_D->do_build( this_player(), this_object(), arg ); }
void do_upgrade( string arg ) { INTERIOR_D->do_upgrade( this_player(), this_object(), arg ); }
void do_plant( string arg ) { INTERIOR_D->do_plant( this_player(), this_object(), arg ); }
void do_food( string arg ) { INTERIOR_D->do_food( this_player(), this_object(), arg ); }

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object( who, this_object(), obj ); }

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p;
        object who,item;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        if (flag>=1000)
        {
        	"/sys/user/refine"->do_welcome(who, me, arg);
        	return;
        }        
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大侠你终于出现了！人心难测，小人难防。本官的得力助手吴孜，为了谋取私利，竟然偷取本国的机密要件。如果大王知道此事定会怪罪于我。还望%s能速将此叛徒除掉。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_04,5) && !who->get_legend(TASK_04,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下本官算是放心了，机密要件保住了，本官定要好好酬谢你。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_04,4) && !who->get_legend(TASK_04,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    都怪本官当初错信任了此人，如今本官准备亲自向大王认罪。\n"ESC"离开", me->get_name()));
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_04,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,2,"内政官的烦恼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"内政官的烦恼");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_04,5) && !who->get_legend(TASK_04,6) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/33/1771",2);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,6);
			who->add_exp(1100);
			who->add_potential(60);
			who->add_cash(1300);
			send_user(who,"%c%s",';',"内政官的烦恼 经验 1100 潜能 60 金钱 1300 地瓜解暑汤 2");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,2,"" );
        	}
        	break;
         case 4:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大侠你终于出现了！天生异象，必有妖魔祸害世间。最近有一群独眼兽在宫廷附近捣乱，闹的是鸡犬不宁，大王已经生气了。不知你可否愿意去翠华山杀20个独眼兽，给它们点颜色看看，大王一定会重谢你的。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_04,11) && !who->get_legend(TASK_04,12) )
			me->do_welcome(6);
        	break;
        case 5:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,11) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->delete_save_2("nzdujiaosou");
        		who->set_legend(TASK_04,11);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,5,"宫廷的喧闹" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"宫廷的喧闹");
        	}
        	break;
        case 6: 
        	if ( !who->get_legend(TASK_04,11) || who->get_legend(TASK_04,12) )
        		return ;
        	if ( who->get_save_2("nzdujiaosou") >= 20 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了，看那些独眼兽还敢如此猖狂！宫廷周围可以安宁一段日子了。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来宫廷最近是不得安宁了。那些独眼兽会越来越猖狂。\n"ESC"离开", me->get_name()));
        	break;
        case 7:
        	if ( !who->get_legend(TASK_04,11) || who->get_legend(TASK_04,12) || who->get_save_2("nzdujiaosou") < 20)
        		return ;
        	if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        	TASK_LEGEND_D->give_item(who,"/item/32/3282",3);
		TASK_LEGEND_D->task_finish(who);
		who->set_legend(TASK_04,12);
		who->delete_save_2("nzdujiaosou");
		who->add_exp(1300);
		who->add_potential(70);
		who->add_cash(1200);
		send_user(who,"%c%s",';',"宫廷的喧闹 经验 1300 潜能 70 金钱 1200 桔子 3");
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,5,"" );
        	break;
        case 8:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_22,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王说想吃红烧鱼，我好辛苦才在东海找到一条上等的好鱼交给厨房去做，但是他们却告诉我需要在弯道找到的上好葱、大蒜、姜来做佐料才可以做出上等的红烧鱼，现在弯道上贼匪满布，我们的兵士无法抽空去剿灭，麻烦你替我去弯道跑一趟把这些材料找回来好吗？我需要三个葱、一个姜和一个大蒜。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_22,21) && !who->get_legend(TASK_22,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果没有这些佐料，估计是很难做出一道适合大王口味的红烧鱼了。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_22,22) && !who->get_legend(TASK_22,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来今晚大王能吃到一道上等的红烧鱼了，我想大王今晚一定很开心。\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 9:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_22,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_22,21);
        		who->delete_save_2("hgnzgcong");
        		who->delete_save_2("hgnzgjiang");
        		who->delete_save_2("hgnzgdasuan");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,41,"烹鱼的佐料" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"烹鱼的佐料");
        	}
        	break;        	
        case 10:
        	if ( who->get_legend(TASK_22,22) && !who->get_legend(TASK_22,23) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"葱",3) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"姜",1) != 1 )
        		{
        			item = new("item/98/0104");
        			item->set_amount(3);
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			return;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"大蒜",1) != 1 )
        		{
        			item = new("item/98/0104");
        			item->set_amount(3);
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			item = new("item/98/0106");
        			item->set_amount(1);
        			p = item->move(who,-1);
        			item->add_to_user(p);        			
        			return;        			
        		}
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,23);
        		who->delete_save_2("hgnzgcong");
        		who->delete_save_2("hgnzgjiang");
        		who->delete_save_2("hgnzgdasuan");
			who->add_exp(26000);
			who->add_potential(440);
			who->add_cash(25000);
			send_user(who,"%c%s",';',"烹鱼的佐料 经验 26000 潜能 440 金钱 25000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,41,"" );
        	}
        	break;
        case 11:
        	if ( who->get_legend(TASK_25,17) && !who->get_legend(TASK_25,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    什么？竟然还有这样的事情，让我马上把这件事情上奏大王，当大王派人处理这件事。这位勇士你辛苦了，就先在这里休息一下吧，我会吩咐人拿一些赏赐给你。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_25,18) && !who->get_legend(TASK_25,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王已经阅读了刘方士的请命函后，察觉事态严重。现在，大王派在下募集有能之是开始围剿灵谷洞的妖物，我看阁下也是有能之士，如果阁下有兴趣的话，可以替我国出一分力，到灵谷洞一层除掉20只铜甲尸和20只侍卫亡灵。你除掉20只铜甲尸和20只侍卫亡灵后，回来我这里，我会给你丰厚的报酬的。\n"ESC"接受任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_25,19) && !who->get_legend(TASK_25,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    灵谷洞里面的怪物数量还在急剧增长，如果还不处理的话，恐怕总有一天我们韩国全国上下都会变成好象灵谷洞里面一样。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_25,20) && !who->get_legend(TASK_25,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你做得实在太出色了，居然在这么短的时间内就把20只铜甲尸和20只侍卫亡灵除掉。看来，你有实力帮助我们去实行这次围剿的一个最艰巨的任务。\n"ESC"完成任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_25,21) && !who->get_legend(TASK_25,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    其实灵谷洞之所以会有如此多的妖物急剧增长是有原因的，在灵谷洞的2层有一个妖道叫武之真，是他在使妖法让灵谷洞的妖怪数量急剧增长的。我估计武之真是秦国派来的，其目的就是要让我们韩国先被妖物灭亡，然后让秦国派兵占领我们韩国的国土。我决不允许这样的事情发生。你是个实力值得信赖的人，可以替我们去灵谷洞的2层把这个妖道除掉，让我们韩国的民众不至于被妖怪搞得生灵涂炭吗？你除掉这个妖道之后，可以直接去向韩国御史郑国那里报告。\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
         case 12:
        	if ( who->get_legend(TASK_25,17) && !who->get_legend(TASK_25,18) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"请命函",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_25,18);
			who->add_exp(35000);
			who->add_potential(520);
			who->add_cash(34000);
			send_user(who,"%c%s",';',"出谋献策 经验 35000 潜能 520 金钱 34000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,21,"" );
			me->do_welcome(11);
        	}
        	break;
	case 13:
        	if( who->get_legend(TASK_25,18) && !who->get_legend(TASK_25,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_25,19);
        		who->delete_save_2("hgnzgtongjs");
        		who->delete_save_2("hgnzgswwl1");        		
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,22,"挑战自己" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"挑战自己");
        	}
        	break;       
         case 14:
        	if ( who->get_legend(TASK_25,20) && !who->get_legend(TASK_25,21) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_25,21);
        		who->delete_save_2("hgnzgtongjs");
        		who->delete_save_2("hgnzgswwl1");  
			who->add_exp(34000);
			who->add_potential(510);
			who->add_cash(34000);
			send_user(who,"%c%s",';',"挑战自己 经验 34000 潜能 510 金钱 34000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,22,"" );
			me->do_welcome(11);
        	}
        	break;
	case 15:
        	if( who->get_legend(TASK_25,21) && !who->get_legend(TASK_25,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_25,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,23,"清除奸贼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"清除奸贼");
        	}
        	break;       
	case 16:
        	if ( who->get_legend(TASK_25,29) && !who->get_legend(TASK_25,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    什么？襄陵道那边的河水出了问题？看来这件事不可轻视。水可是我们百姓生活的源泉，如果那里的河水出问题了对我们韩国百姓子赢的影响就大了。我得好好查一查这件事。\n"ESC"完成任务\ntalk %x# welcome.17\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_25,30) && !who->get_legend(TASK_26,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    根据我现在掌握的情况来说，襄陵道那边的那条河应该是受了妖魔的诅咒。我现在马上写一封密件，你把这封密件交给本国的御史，让御史帮忙想办法尽快解除那条河的诅咒。但是你要注意千万别把密件的内容泄露出去，不然的话恐怕会引起国内恐慌。\n"ESC"接受任务\ntalk %x# welcome.18\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 17:
        	if ( who->get_legend(TASK_25,29) && !who->get_legend(TASK_25,30) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_25,30);
			who->add_exp(35000);
			who->add_potential(530);
			who->add_cash(36000);
			send_user(who,"%c%s",';',"内政官的心事 经验 35000 潜能 530 金钱 36000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,26,"" );
			me->do_welcome(16);
        	}
        	break;	
	case 18:
        	if ( who->get_legend(TASK_25,30) && !who->get_legend(TASK_26,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0122");
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!',"你携带的物品太多了");	
        			return ;
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_26,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,27,"寻求帮助" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻求帮助");
        	}
        	break;
	case 19:
        	if ( who->get_legend(TASK_26,12) && !who->get_legend(TASK_26,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    御史可是把一件头疼的事丢到我头上了，没有兵士我们无法对灵谷洞进行围剿，让我先想想其他办法吧。\n"ESC"完成任务\ntalk %x# welcome.20\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,13) && !who->get_legend(TASK_26,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我看你武功高强，如果你肯帮忙的话，那么事情就简单多了。但是要杀掉那土匪，先要除去他的爪牙。如果你愿意帮忙你话，那么你先去灵谷洞把那个土匪才操纵的30个恶灵和30个侍卫亡灵除掉。然后回来告诉我，我会告诉你那么土匪藏身在哪里的。\n"ESC"接受任务\ntalk %x# welcome.21\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,14) && !who->get_legend(TASK_26,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我看阁下您武功高强，英名盖世，我想你肯定可以将那些恶灵和亡灵侍卫除掉。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_26,15) && !who->get_legend(TASK_26,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我果然没有看错你，这下子我看这个土匪已经没有帮手了，现在除掉他对于你来说简直就是易如反掌。\n"ESC"完成任务\ntalk %x# welcome.22\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,16) && !who->get_legend(TASK_26,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好了，现在你可以动身到灵谷洞3层的南边角落将那个杀人越货、作恶多端的土匪马大杀掉了。放心，没有了他那些恶灵爪牙的话你消灭他将会是一件简单的事情。你消灭他之后回去御史那里汇报吧。他会给你一些奖励的。\n"ESC"接受任务\ntalk %x# welcome.23\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 20:
        	if ( who->get_legend(TASK_26,12) && !who->get_legend(TASK_26,13) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,13);
			who->add_exp(40000);
			who->add_potential(560);
			who->add_cash(38000);
			send_user(who,"%c%s",';',"御史的担心 经验 40000 潜能 560 金钱 38000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,32,"" );
			me->do_welcome(19);
        	}
        	break;
         case 21:
        	if ( who->get_legend(TASK_26,13) && !who->get_legend(TASK_26,14) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_26,14);
        		who->delete_save_2("hgnzgeling");
        		who->delete_save_2("hgnzgswwl");  
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,33,"试探实力" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"试探实力");
        	}
        	break;
	case 22:
        	if ( who->get_legend(TASK_26,15) && !who->get_legend(TASK_26,16) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,16);
        		who->delete_save_2("hgnzgeling");
        		who->delete_save_2("hgnzgswwl");  
			who->add_exp(39000);
			who->add_potential(580);
			who->add_cash(39000);
			send_user(who,"%c%s",';',"试探实力 经验 39000 潜能 580 金钱 39000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,33,"" );
			me->do_welcome(19);
        	}
        	break;
         case 23:
        	if ( who->get_legend(TASK_26,16) && !who->get_legend(TASK_26,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_26,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,34,"为民除害" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"为民除害");
        	}
        	break;
	case 24:
        	if ( who->get_legend(TASK_26,27) && !who->get_legend(TASK_26,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你要替乐师的父亲翻案？那个案件判决了，如果没有什么关键的证据出现的话我是不会改变判决的。什么？你找到了失窃的含鳞珠？那么好吧，我就受理你这件案件。\n"ESC"完成任务\ntalk %x# welcome.25\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,28) && !who->get_legend(TASK_27,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你这含鳞珠是在灵谷洞里面找回来的话那么乐师的父亲就肯定是冤枉了，因为乐师的父亲只是凡人之躯，而且连武功都不会，他是没可能把这含鳞珠放到哪个妖魔满布的洞穴。但是有一个人是可以自由进出灵谷洞的，他就是指证乐师父亲的那个无赖马小三。他现在应该就在你找到这个含鳞珠的地方附近，你替我去把他逮捕吧，如果他拒捕你就直接把他就地正法好了。\n"ESC"接受任务\ntalk %x# welcome.26\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_27,1) && !who->get_legend(TASK_27,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我估计这个无赖马小三一定会拒捕，现在他的罪证确凿。所以我建议你还是把他就地正法吧！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_27,2) && !who->get_legend(TASK_27,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    做得好，你果然把他就地就地正法了，他存心不良，有意要嫁祸给乐师的父亲，其目的原来是记恨十年前乐师父亲取代他作为御厨的事。\n"ESC"完成任务\ntalk %x# welcome.27\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_27,3) && !who->get_legend(TASK_26,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在这件案件已经真相大白了，但是乐师的父亲现在还被关押在大王的监狱里面。我这就写一封准放奏书，你将它交给大王。书里面已经把这次的事情写得清清楚楚，大王看过之后应该就会把乐师父亲释放。\n"ESC"接受任务\ntalk %x# welcome.28\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 25:
        	if ( who->get_legend(TASK_26,27) && !who->get_legend(TASK_26,28) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"含鳞珠",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,28);
			who->add_exp(43000);
			who->add_potential(620);
			who->add_cash(42000);
			send_user(who,"%c%s",';',"寻求方法 经验 43000 潜能 620 金钱 42000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,38,"" );
			me->do_welcome(24);
        	}
        	break;
         case 26:
        	if ( who->get_legend(TASK_26,28) && !who->get_legend(TASK_27,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_27,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,39,"防止泄密" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"防止泄密");
        	}
        	break;
	case 27:
        	if ( who->get_legend(TASK_27,2) && !who->get_legend(TASK_27,3) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/62072",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_27,3);
			who->add_exp(44000);
			who->add_potential(630);
			who->add_cash(43000);
			send_user(who,"%c%s",';',"防止泄密 经验 44000 潜能 630 金钱 43000 承影剑图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,39,"" );
			me->do_welcome(24);
        	}
        	break;
	case 28:
        	if( who->get_legend(TASK_27,3) && !who->get_legend(TASK_26,29) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0126");
        		if ( !item )
        			return ;
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!', "你携带的物品太多了");
        			return;
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_26,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,40,"上奏韩王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"上奏韩王");
        	}
        	break;
        case 99:	
		INTERIOR_D->do_look( who, me); 
        	break;
        }
}
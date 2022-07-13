
// 自动生成：/make/npc/make8002

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GENERAL_D       "/inh/city/general"

inherit OFFICER;

void do_patrol( string arg );
void do_soldier( string arg );
void do_armor( string arg );
void do_welcome( string arg );
//void do_defence( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5201; }

// 函数：构造处理
void create()
{
        set_name("Yên Quốc Đại Tướng Quân");
	set_real_name("Nhạc Nghi");
        set_city_name("Yên Quốc");

        set_2( "talk", ([
                "patrol"        : (: do_patrol :),
                "soldier"       : (: do_soldier :),
                "armor"         : (: do_armor :),
                "welcome"	: (: do_welcome :),
            //    "defence"	: (: do_defence :),
        ]) );
//        set("level",45);
//        set("legend",({32*11+24}));
	set("mpLegend",([45:({32*11+24}),50:({32*13+28}),90:({32*32+20}),110:({32*43+20})]));
	set("mpLegend2",([0:({32*32+3,}),45:({32*11+26}),50:({32*13+30}),90:({32*32+22}),110:({32*39+2,32*43+22,})]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

//void do_defence(string arg) { "/sys/party/defence"->do_defence(this_player(), this_object(), arg); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >=45 && !who->get_legend(TASK_11,24) ) || ( who->get_legend(TASK_11,24) && !who->get_legend(TASK_11,26) ) )
	{
		tmp = sprintf(ESC HIY "挑战\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >=50 && !who->get_legend(TASK_13,28) ) || ( who->get_legend(TASK_13,28) && !who->get_legend(TASK_13,30) ) )
	{
		tmp += sprintf(ESC HIY "安全隐患\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( who->get_legend(TASK_32,2) && !who->get_legend(TASK_32,3) )
	{
		tmp += sprintf(ESC HIY "单刀\ntalk %x# welcome.7\n",getoid(me));
	}
	if ( ( who->get_level() >=90 && !who->get_legend(TASK_32,20) ) || ( who->get_legend(TASK_32,20) && !who->get_legend(TASK_32,22) ) )
	{
		tmp += sprintf(ESC HIY "罪恶的源泉\ntalk %x# welcome.9\n",getoid(me));
	}
	if ( who->get_level() >=110 && who->get_legend(TASK_39,1) && !who->get_legend(TASK_39,2) )
	{
		tmp += sprintf(ESC HIY "求份差事\ntalk %x# welcome.12\n",getoid(me));
	}
	if ( ( who->get_level() >=110 && !who->get_legend(TASK_43,20) ) || ( who->get_legend(TASK_43,20) && !who->get_legend(TASK_43,22) ) )
	{
		tmp += sprintf(ESC HIY "补给\ntalk %x# welcome.14\n",getoid(me));
	}
//	if ("/sys/sys/count"->get_war_flag1()||"/sys/party/defence"->get_count())
//		tmp += sprintf(ESC HIY "Chiến Trường Thủ Thành\ntalk %x# defence.1\n",getoid(me));	
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GENERAL_D->do_look( who, me ); 
	
}
void do_patrol( string arg ) { GENERAL_D->do_patrol( this_player(), this_object(), arg ); }
void do_soldier( string arg ) { GENERAL_D->do_soldier( this_player(), this_object(), arg ); }
void do_armor( string arg ) { GENERAL_D->do_armor( this_player(), this_object(), arg ); }
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
        	if ( who->get_level() >=45 && !who->get_legend(TASK_11,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    让我看看你能不能对付这个挑战吧。你去长白山一带消灭10只花豹精，来证明你的能力！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_11,24) && !who->get_legend(TASK_11,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你得要加油，别辜负了我对你的期望。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_11,25) && !who->get_legend(TASK_11,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你果然不错。继续努力，年轻人！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_level() >=45 && !who->get_legend(TASK_11,24) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_11,24);
        		who->delete_save_2("huabaojing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,18,"挑战" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"挑战");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_11,25) && !who->get_legend(TASK_11,26) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_11,26);
        		who->delete_save_2("huabaojing");
			who->add_exp(5000);
			who->add_potential(160);
			who->add_cash(4000);
			send_user(who,"%c%s",';',"挑战 经验 5000 潜能 160 金钱 4000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,18,"" );
        	}
        	break;   
	case 4:
        	if ( who->get_level() >=50 && !who->get_legend(TASK_13,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    驻扎在燕长城上的那些刀盾兵都是当年从军营里叛逃出来的，说不定哪天他们又会策划一场大的暴动，这可是个大隐患啊，我每天都提心吊胆，想着要怎么解决这个问题，我想发动民间的力量来解决，可一直没有人帮我，你来得正好，你去燕长城消灭掉他们吧！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_13,28) && !who->get_legend(TASK_13,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你不能完成这件事情的话，那证明他们的能力太强，可能我要出兵了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_13,29) && !who->get_legend(TASK_13,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    单凭你一人的力量是远远不够的，如果还有能人志士，你可以叫他来找我！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 5:
		if ( who->get_level() >= 50 && !who->get_legend(TASK_13,28) ) 
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,28);
        		who->delete_save_2("jjdaodunbing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,22,"安全隐患" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"安全隐患");
        	}
		break;
	case 6:
		if ( who->get_legend(TASK_13,29) && !who->get_legend(TASK_13,30) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,30);
        		who->delete_save_2("jjdaodunbing");
			who->add_exp(5800);
			who->add_potential(230);
			who->add_cash(4700);
			send_user(who,"%c%s",';',"安全隐患 经验 5800 潜能 230 金钱 4700");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,22,"" );
        	}
		break;
	case 7:
		if ( who->get_legend(TASK_32,2) && !who->get_legend(TASK_32,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，这就是传说中的魔刀么，我要好好研究一下，军需官，赏！\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 8:
        	if ( who->get_legend(TASK_32,2) && !who->get_legend(TASK_32,3) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"单刀",8) != 1 )
        			return;
        		who->delete_save("ygswdandao");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_32,3);
			who->add_exp(62000);
			who->add_potential(900);
			who->add_cash(53000);
			send_user(who,"%c%s",';',"单刀 经验 62000 潜能 900 金钱 53000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,43,"" );
        	}
        	break;
	case 9:
        	if ( who->get_level() >=90 && !who->get_legend(TASK_32,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    当年烈焰也是我手下副将，随我征战四方，谁知道他不服管教，后来竟然拿我方机密卖于敌国，几乎令我们全军覆没，要不是最近他花光了卖国求荣来的财宝，又开始在附近烧杀掳掠，一个逃回来的女子告诉我们他酒醉后说的话，我们还真没法把他同数年前那场大战的通敌之人联系起来，如此大奸大恶之徒，实在是难以容忍他继续逍遥在世上，简直是我们大燕的耻辱！我命你速速前去涿鹿的石门村，将烈焰碎尸万断！\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_32,20) && !who->get_legend(TASK_32,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    烈焰不除，本将军心头之恨难解，也对不起当初那场大战中死去的数万将士！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_32,21) && !who->get_legend(TASK_32,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    烈焰的尸体在何处！来人，将烈焰鞭尸后，割下头颅挂于军营上方，尸体剁碎了喂狗！让每个人牢记叛徒的下场！\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 10:
		if ( who->get_level() >= 90 && !who->get_legend(TASK_32,20) ) 
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_32,20);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,47,"罪恶的源泉" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"罪恶的源泉");
        	}
		break;
	case 11:
		if ( who->get_legend(TASK_32,21) && !who->get_legend(TASK_32,22) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_32,22);
			who->add_exp(68000);
			who->add_potential(915);
			who->add_cash(57000);
			send_user(who,"%c%s",';',"罪恶的源泉 经验 68000 潜能 915 金钱 57000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,47,"" );
        	}
		break;
	case 12:
		if ( who->get_level() >=110 && who->get_legend(TASK_39,1) && !who->get_legend(TASK_39,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，最近我们军队确实在招兵买马，如果他有兴趣，你可以叫他来试试。\n"ESC"完成任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 13:
		if ( who->get_level() >=110 && who->get_legend(TASK_39,1) && !who->get_legend(TASK_39,2) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_39,2);
			who->add_exp(48000);
			who->add_potential(610);
			who->add_cash(45000);
			send_user(who,"%c%s",';',"求份差事 经验 48000 潜能 610 金钱 45000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,93,"" );
        	} 
        	break; 
	case 14:
        	if ( who->get_level() >=110 && !who->get_legend(TASK_43,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    吾王雄才大略，本将军英明神武，本军将士狼狈为奸……呃不对，是同心同德，本国百姓万众一心，吾王征服天下的时机已经成熟，我军不日即将起拔，俗话说三军未动，粮草先行，该死的催粮官居然还没有把我们军补给备齐，现在他领50军棍去了，怎么样，身为英雄的你，有没有报效国家的觉悟啊，现在命令你去困魔阵给本将军找8个南瓜、12个萝卜、7个鸡蛋回来，不找怎么样，哼哼，你想步催粮官的后尘吗，不过呢如果你能按时找回来本将军重重有赏！\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_43,20) && !who->get_legend(TASK_43,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    可不要小瞧这点东西，首先本将军要纠正你这种狭隘的观念，岂不闻人人动手，丰衣足食，众人拾柴火焰高？你还是速速前去吧。（画外音，军士拖着受了刑的催粮官经过，故意捅了捅催粮官受刑的地方，催粮官发出凄惨的叫声）\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_43,21) && !who->get_legend(TASK_43,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，不错看来你是本国的优秀百姓，除了许下的重赏之外，本将军决定授予你荣誉一等拥军百姓称号，呃，你问我本国一等百姓有多少，本将军讲究军法面前人人平等，哈哈哈哈……（在燕国将军的音波攻击中，你落荒而逃）\n"ESC"完成任务\ntalk %x# welcome.16\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 15:
		if ( who->get_level() >=110 && !who->get_legend(TASK_43,20) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_43,20);
        		who->delete_save("ygdjjnangua");
        		who->delete_save("ygdjjluobo");
        		who->delete_save("ygdjjjidan");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,50,"军营的补给" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"军营的补给");
        	}
		break;
	case 16:
		if ( who->get_legend(TASK_43,21) && !who->get_legend(TASK_43,22) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"大南瓜",8) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"大萝卜",12) != 1 )
        		{
				TASK_LEGEND_D->give_item(who,"item/98/0213",8);
        			return;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"土鸡蛋",7) != 1 )
        		{
				TASK_LEGEND_D->give_item(who,"item/98/0213",8);
				TASK_LEGEND_D->give_item(who,"item/98/0214",12);
        			return;
        		}
        		TASK_LEGEND_D->give_item(who,"item/product/62091",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_43,22);
        		who->delete_save("ygdjjnangua");
        		who->delete_save("ygdjjluobo");
        		who->delete_save("ygdjjjidan");
			who->add_exp(98000);
			who->add_potential(1100);
			who->add_cash(95000);
			send_user(who,"%c%s",';',"军营的补给 经验 98000 潜能 1100 金钱 95000 天魔棍图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,50,"" );
        	}
		break;
 	case 99:
 		GENERAL_D->do_look( who, me); 
 		break;
        }
}
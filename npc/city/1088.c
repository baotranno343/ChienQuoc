
// 自动生成：/make/npc/make8088

#include <npc.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

#define JOB_TRADER_D    "/inh/job/trader"

inherit OFFICER;
inherit "/inh/npc/trader";
int is_self_look() { return 1;}

void reset();
void do_good( string arg );
void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5401; }

// 函数：构造处理
void create()
{
        set_name("Tề Quốc Thương Nhân");
	set_real_name("Y Dốn");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "good"          : (: do_good :),
                "welcome"	: (: do_welcome :),
        ]) );
        reset();
//        set("level",39);
//        set("legend",({32*10+11}));
 	set("mpLegend",([35:({32*10+11}),95:({32*38+23,}),100:({32*35+27})]));
 	set("mpLegend2",([10:({32*3+12,32*3+19,32*30+23,32*30+26,}),35:({32*10+13}),100:({32*35+29})]));
        setup();
}

// 函数：复位处理
void reset()
{
	object me = this_object();
	me->set("reset_time", time());
        set_buy_rate( random(1001) );
        set_sell_rate( random(1001) );

        set_2( "good", ([
                "01" : "/item/99/9911",
                "02" : "/item/99/9912",
                "03" : "/item/99/9913",
        ]) );
        set_2( "list", ([
                "01" : 200,
                "02" : 250,
                "03" : 15,
        ]) );
}

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_NEWBIE_03,11) && !who->get_legend(TASK_NEWBIE_03,19) )
	{
		tmp = sprintf(ESC HIY "买椟还珠\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 35 && !who->get_legend(TASK_10,11) ) || ( who->get_legend(TASK_10,11) && !who->get_legend(TASK_10,13) ) )
		tmp += sprintf(ESC HIY "商人的生意经\ntalk %x# welcome.5\n",getoid(me));
	if ( who->get_legend(TASK_30,22) && !who->get_legend(TASK_30,23) )
		tmp += sprintf(ESC HIY "商人诉苦\ntalk %x# welcome.8\n",getoid(me));
	if ( (who->get_legend(TASK_30,23) && !who->get_legend(TASK_30,24)) || (who->get_legend(TASK_30,24) && !who->get_legend(TASK_30,26)))
		tmp += sprintf(ESC HIY "独闯古墓\ntalk %x# welcome.8\n",getoid(me));
	if ( who->get_legend(TASK_30,26) && !who->get_legend(TASK_30,27) )
		tmp += sprintf(ESC HIY "除掉恶匪\ntalk %x# welcome.8\n",getoid(me));
	if ( who->get_level() >= 95 && !who->get_legend(TASK_38,23) )
		tmp += sprintf(ESC HIY "讨好\ntalk %x# welcome.13\n",getoid(me));

	if ( ( who->get_level() >= 100 && !who->get_legend(TASK_35,27) ) || ( who->get_legend(TASK_35,27) && !who->get_legend(TASK_35,29) ) )
		tmp += sprintf(ESC HIY "罐中妖与罐中仙\ntalk %x# welcome.15\n",getoid(me));
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_normal_word(me) + "\n"ESC"交易\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		JOB_TRADER_D->do_look( who, this_object() ); 
	
}

void do_good( string arg ) { JOB_TRADER_D->do_good( this_player(), this_object(), arg ); }

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag;
        object who,item;   
	string *nTmp,tmp;     
 
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_NEWBIE_03,11) && !who->get_legend(TASK_NEWBIE_03,12) )
        		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    年轻人！是我兄弟叫你来的吧！是这样的：前些日子我收购了一颗名贵的珍珠，我想卖个好价钱，可一直找不到漂亮盒子装，郁闷死了。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_NEWBIE_03,12) && !who->get_legend(TASK_NEWBIE_03,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前些日子我收购了一颗名贵的珍珠，我想卖个好价钱，可一直找不到漂亮盒子装，你愿意去周国的妙手公输班那儿给我做个盒子吗？我不会亏待你的。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_NEWBIE_03,11) && !who->get_legend(TASK_NEWBIE_03,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我的盒子呢？公输班做好了吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_NEWBIE_03,18) && !who->get_legend(TASK_NEWBIE_03,19) )
        		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    终于可把你盼回来了！那公输班肯定是百般刁难吧？有了这个木盒，我的珍珠肯定会卖个高价的！辛苦你了，这是你的报酬！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_legend(TASK_NEWBIE_03,11) && !who->get_legend(TASK_NEWBIE_03,12) )
        	{
			who->add_exp(600);
			who->add_potential(20);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03,12);
			send_user(who,"%c%s",';',"买椟还珠 经验 600 潜能 20");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,7,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3 :
        	if ( who->get_legend(TASK_NEWBIE_03,12) && !who->get_legend(TASK_NEWBIE_03,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_NEWBIE_03,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,8,"买椟还珠(2)" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"买椟还珠(2)");
        	}
        	break;
        case 4:
        	if ( who->get_legend(TASK_NEWBIE_03,18) && !who->get_legend(TASK_NEWBIE_03,19) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip("",0,10,HEAD_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			if ( TASK_LEGEND_D->check_task_item(who,"木盒",1) != 1)
				return;
			TASK_LEGEND_D->give_item(who,tmp,1);
			who->add_exp(800);
			who->add_potential(50);
			who->add_cash(2000);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03,19);
			send_user(who,"%c%s",';',sprintf("买椟还珠 经验 800 潜能 50 金钱 2000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,6,"" );
        	}
        	break;
        case 5:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_10,11)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听人说军营里又来了不少新兵，这些人嗜酒如命，这应该是一笔大生意，要拿下它，我看得先贿赂他们的头。\n    听说东海渔村一带的虾兵蟹将窝藏了一批在地下埋藏了上百年的名酒，如果这时候有人能帮我找10坛这样的酒，让我拿去送给军营里的头，那可真是帮了我的大忙了，我一定会好好谢谢他的！\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,11) && !who->get_legend(TASK_10,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这名酒还真是不好找，看来我的发财大计很难实现啊！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_10,12) && !who->get_legend(TASK_10,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你可真是雪中送炭啊！这名酒我要是拿去贿赂军营里的头，他们肯定欢喜的很，以后都会把军营里酒的采购交给我来办了！嘿嘿，看来我要发财了！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 6:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_10,11)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,11);
        		who->delete_save_2("shrmingjiu");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,12,"商人的生意经" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"商人的生意经");
        	}
        	break;
       case 7:
        	if ( who->get_legend(TASK_10,12) && !who->get_legend(TASK_10,13) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"名酒",10) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_10,13);
			who->delete_save_2("shrmingjiu");
			who->add_exp(4000);
			who->add_potential(115);
			who->add_cash(3000);
			send_user(who,"%c%s",';',"商人的生意经 经验 4000 潜能 115 金钱 3000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,12,"" );
        	}
        	break;        
	case 8:
		if ( who->get_legend(TASK_30,22) && !who->get_legend(TASK_30,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，走多了夜路难免撞鬼啊！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,23) && !who->get_legend(TASK_30,24) )	
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呜呜呜，你说我怎么就这么倒霉呢，我整天都提防着有人抢我，财不敢露白，人不敢独行，结果还是被抢了，我没有想到自己雇佣的30个石狮居然同那抢劫的30个石虎是一伙的，他们后面都有人指挥着，我此恨难消啊，你快点去将军古墓二层把那背叛我的30个石狮和抢劫我的30个石虎杀掉!\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,24) && !who->get_legend(TASK_30,25) )	
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来你还是不行啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_30,25) && !who->get_legend(TASK_30,26) )	
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下终于有人能替我解决麻烦了。\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,26) && !who->get_legend(TASK_30,27) )	
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    上月去楚国贩青铜，刚刚赚了个钵盆满贯，我已经小心藏行踪，我穿的是破衫，踩的是草鞋，混迹在人群，我雇佣的护卫是猛虎下山。谁知那同行中，居然有马小七，一双毒眼将我看穿，原来那护卫，都是他手下，怎奈我千防万防也不防，大队中也有人肆无忌惮。结果我被洗劫，除了身上那身破烂，他们也看不惯，留下我步履蹒跚回家园。可恨那马小七，将军古墓四层北筑老巢，我有心把仇报，却又知道只有被他当早点，现在只有盼壮士为我扫除匪人钱财还。听说那马小七，负案累累恶滔天，你只要送他去阎王殿，保我们御史乐翻天。\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
			
		break;
        case 9:
        	if ( who->get_legend(TASK_30,22) && !who->get_legend(TASK_30,23) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,23);
			who->add_exp(70000);
			who->add_potential(820);
			who->add_cash(53000);
			send_user(who,"%c%s",';',"商人诉苦 经验 70000 潜能 820 金钱 53000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,41,"" );
			me->do_welcome(8);
        	}
        	break;
        case 10:
        	if ( who->get_legend(TASK_30,23) && !who->get_legend(TASK_30,24) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,24);
        		who->delete_save("qgsrshisi");
        		who->delete_save("qgsrshihu");		        		
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,42,"独闯古墓" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"独闯古墓");
        	}
        	break;
        case 11:
        	if ( who->get_legend(TASK_30,25) && !who->get_legend(TASK_30,26) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,26);
        		who->delete_save("qgsrshisi");
        		who->delete_save("qgsrshihu");	
			who->add_exp(69000);
			who->add_potential(800);
			who->add_cash(55000);
			send_user(who,"%c%s",';',"独闯古墓 经验 69000 潜能 800 金钱 55000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,42,"" );
			me->do_welcome(8);
        	}
        	break;
        case 12:
        	if ( who->get_legend(TASK_30,26) && !who->get_legend(TASK_30,27) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,27);       		
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,43,"除掉恶匪" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"除掉恶匪");
        	}
        	break;
	case 13:
		if ( who->get_level() >= 95 && !who->get_legend(TASK_38,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    素闻那赵王爱吃樱桃，可惜赵国并不盛产，所以赵王下令收集樱桃，以供他一饱口福。\n    我这最近到了一批好货，那樱桃鲜嫩欲滴，颗颗饱满，色泽又好，我想赵王一定会喜欢的，其实我也没别的意思，做生意的人，就想求点钱财。但我本是齐人，送樱桃给赵王定当不妥，所以还想请你去将樱桃交给赵王，赵王的赏金，我定会分你一半！\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 14:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_38,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/98/0183",1);
        		who->set_legend(TASK_38,23);       		
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,76,"讨好" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"讨好");
        	}
        	break;
        case 15:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_35,27)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    行商走路，常常碰到不少怪物，我们当然得审时度势，看是消灭还是绕道，以前听其他商人说过罐中妖凶恶，最近又有人传说罐中仙也是个狠角色，究竟怎么样我还是没有一个具体的概念，看这位大侠筋骨强健，身负宝器，定是降怪好手，不知道能不能前去消灭罐中妖18只，罐中仙6只帮我比较一下他们能力如何、究竟有什么特点。据说罐中妖多聚集在灵谷洞为恶，而罐中仙多游荡在九曲桥一带。\n"ESC"接受任务\ntalk %x# welcome.16\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_35,27) && !who->get_legend(TASK_35,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你无此慧眼，无法区分妖与仙什么不同，也不用苛求，我再找其他人问问吧。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_35,28) && !who->get_legend(TASK_35,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    他们外形都一样，只是妖弱仙强，哈哈，原来时间万物尽是一样，能力弱的就诬蔑为妖，强势者自诩为仙，所谓妖气仙风，不外是贬低别人，标榜自己的手段而已，上古诸仙，又哪个不是外形奇异，若不是能力超绝，早就堕入妖流了，听闻中古轩辕同蚩尤混战，本来两人均是奇形恶状，不过失败者不得完尸，自此成为千古恶魔之首，而成功者被浓墨重彩，自此成为仙之大成者，哈哈哈，我明了明了……\n"ESC"完成任务\ntalk %x# welcome.17\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 16:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_35,27)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,27);
        		who->delete_save("qgsrguanzx");
        		who->delete_save("qgsrguanzy");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,50,"罐中妖与罐中仙" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"罐中妖与罐中仙");
        	}
        	break;
	case 17:
        	if ( who->get_legend(TASK_35,28) && !who->get_legend(TASK_35,29) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/63036",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_35,29);
        		who->delete_save("qgsrguanzx");
        		who->delete_save("qgsrguanzy");
			who->add_exp(83000);
			who->add_potential(1040);
			who->add_cash(3000);
			send_user(who,"%c%s",';',"罐中妖与罐中仙 经验 83000 潜能 1040 金钱 72000 归元丹图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,50,"" );
        	}
        	break; 
        case 99:
        	JOB_TRADER_D->do_look( who, me ); 
        	break;
        }
}

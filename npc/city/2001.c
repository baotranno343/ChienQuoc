
// 自动生成：/make/npc/make8001

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

#define EMPEROR_D       "/inh/city/emperor"
#define EMPEROR_2_D     "/inh/city/emperor2"

inherit OFFICER;

void do_policy( string arg );
void do_relation( string arg );
void do_master( string arg );
void do_advice( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5101; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Hàn Vương");
	set_real_name("Hàn Vương An");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "policy"        : (: do_policy :),
                "relation"      : (: do_relation :),
                "master"        : (: do_master :),
                "advice"        : (: do_advice :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",72);
//	set("legend",({32*23+4}));
 	set("mpLegend",([70:({32*23+4,}),]));
 	set("mpLegend2",([0:({32*23+21,32*25+26,32*26+30,}),]));
        setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 70 && !who->get_legend(TASK_23,4) ) || ( who->get_legend(TASK_23,4) && !who->get_legend(TASK_23,5)) )
	{
		tmp += sprintf(ESC HIY "游魂\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_23,20) && !who->get_legend(TASK_23,21) )
	{
		tmp += sprintf(ESC HIY "解救游魂\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_25,25) && !who->get_legend(TASK_25,26) )
		tmp += sprintf(ESC HIY "上奏Hàn Vương\ntalk %x# welcome.4\n",getoid(me));
	if ( who->get_legend(TASK_25,26) && !who->get_legend(TASK_25,27) )
		tmp += sprintf(ESC HIY "与楚联盟\ntalk %x# welcome.4\n",getoid(me));
	if ( who->get_legend(TASK_26,29) && !who->get_legend(TASK_26,30) )
		tmp += sprintf(ESC HIY "上奏Hàn Vương\ntalk %x# welcome.7\n",getoid(me));
	if ( me->get_city_name() == who->get_city_name() )
	{
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			tmp += sprintf(ESC HIY "制作王之号角\ntalk %x# welcome.9\n",getoid(me));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			tmp += sprintf(ESC HIY "王之号角的雕琢\ntalk %x# welcome.9\n",getoid(me));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16)&& gone_time(who->get_save("wangzhhj"))>=86400 )
			tmp += sprintf(ESC HIY "索取王之号角\ntalk %x# welcome.9\n",getoid(me));
	}
	if ( who->get("master.type") != 69 && sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		EMPEROR_D->do_look( who, this_object() ); 
	
}
void do_policy( string arg ) { EMPEROR_D->do_policy( this_player(), this_object(), arg ); }
void do_relation( string arg ) { EMPEROR_2_D->do_relation( this_player(), this_object(), arg ); }    // ## 2 ##
void do_master( string arg ) { EMPEROR_D->do_master( this_player(), this_object(), arg ); }

void do_advice( string arg ) { EMPEROR_D->do_advice( this_player(), this_object(), arg ); }

// 接收心爱物品
int accept_object( object player, object obj ) 
{
	object who = this_object();
	return TASK_MASTER_D->accept_object( who, player, obj ); 
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,i,size,p,amount;
        object who,item, *inv;     
       	string *nTmp,tmp;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_23,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近经常本王做相同的一个梦，梦见本王在一个阴暗的山洞，洞里面有一群恶灵不断追杀本王，当本王在梦里面被这群恶灵杀害后，本王就会醒来。但是每次梦醒来本王都会在一个不同的陌生地方，有时候在郑城的东郊，有时候又会在襄陵道。这个梦，本王已经重复地做了十七遍了，现在本王的身体已经一天不如一天，御医们都出手无策。直到前两天，才有一个云游道士告诉本王：本王是中了邪术，而且施这邪术的人法力高强，普天之下估计只有茅山的茅真人才可以解得了这邪术。本王想请你前往茅山替本王向茅真人求教破解之法，并查出是哪个妖人对本王施的邪术。\n    路途凶险，还望你能结伴而行。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_23,4) && !who->get_legend(TASK_23,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    烦请阁下尽快替本王去找茅真人求救，本王这副残躯不知道能支持多久了……咳……咳……\n"ESC"离开", me->get_name()));
          	else if ( who->get_legend(TASK_23,20) && !who->get_legend(TASK_23,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊、本王现在觉得身体又充满生命力了！感谢你，这位英雄，是你救了本王的性命。马宁的事，本王深感遗憾，以后本王一定勤政爱民，尽力让百姓免受战争之苦。英雄，你救了本王，本王不知道该怎样报答你才好，这是本王的一点心意，还请你收下吧！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 2:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_23,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_23,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,45,"游魂（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"游魂（1）");
        	}
        	break;
        case 3:
		if (who->get_legend(TASK_23,20) && !who->get_legend(TASK_23,21))
		{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),70,HEAD_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			if ( TASK_LEGEND_D->check_task_item(who,"镜子",1) != 1 )
				return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,21);
			who->add_exp(85000);
			who->add_potential(14000);
			who->add_cash(86000);
			send_user(who,"%c%s",';',sprintf("游魂（7） 经验 85000 潜能 14000 金钱 86000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_MAOSHAN,6,"" );
		}
		break;		
	case 4:
        	if ( who->get_legend(TASK_25,25) && !who->get_legend(TASK_25,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你就是替本国除掉那个妖道的勇士吧？本王代表我韩国上下感谢你。但是这件事情的始末本王还没有完全了解。勇士你先在这休息一下，待本王阅读完这份奏书本王就会对你论功行赏。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_25,26) && !who->get_legend(TASK_25,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我已经详细阅读过御使的奏章了，看来现在为了防范秦国，我们也只好跟楚国联盟了。我这里有一封给楚国的联盟函，你把这封联盟函替我交给楚国的内政官，表示我们对联盟的诚意吧。你把信函拿到楚国的内政官那里你就可以获得你应得的赏赐了。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));

		break;	
	case 5:
        	if ( who->get_legend(TASK_25,25) && !who->get_legend(TASK_25,26) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"韩国御史的奏书",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_25,26);
			who->add_exp(36000);
			who->add_potential(520);
			who->add_cash(35000);
			send_user(who,"%c%s",';',"上奏Hàn Vương 经验 36000 潜能 520 金钱 35000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,24,"" );
			me->do_welcome(4);
        	}
        	break;
	case 6:
        	if( who->get_legend(TASK_25,26) && !who->get_legend(TASK_25,27) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0121");
        		if ( !item )
        			return ;
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!',"你携带的物品太多了");	
        			return ;
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_25,27);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,25,"与楚联盟" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"与楚联盟");
        	}
        	break;     
	case 7:
        	if ( who->get_legend(TASK_26,29) && !who->get_legend(TASK_26,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原来御厨是被人恶意嫁祸的？本王真是糊涂呀，要不是他儿子坚决要向申诉，这次我就冤枉好人了。那个嫁祸于人的无赖马小三真死不足惜，我这就命人去把御厨放了，让他回去跟他儿子乐师团聚。哈，又是一个大团圆结局了。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 8:
        	if ( who->get_legend(TASK_26,29) && !who->get_legend(TASK_26,30) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),80,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"准放奏书",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,30);
			who->add_exp(43000);
			who->add_potential(630);
			who->add_cash(43000);
			send_user(who,"%c%s",';',sprintf("上奏Hàn Vương 经验 43000 潜能 630 金钱 43000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,40,"" );
        	}
        	break;

	case 9:
		if ( me->get_city_name() != who->get_city_name() )
			return;
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，宫廷里的工匠可以帮助你将普通的号角加工为王之号角，你将号角交给我，我替你咨询下工匠，看还需要做哪些准备。\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠说将普通的号角雕琢成为王之号角需要花费很多珍贵的材料，他需要一些钱来购买这些材料，而单靠他一个人的力量是不可能拿出这么多钱的，我想你应该要帮助他承担一部分，他说雕琢王之号角对他来说也是一项挑战，所以他不收你一文的加工费，只需要你给他100万的材料费就够了。如果你还想雕琢王之号角的话，就将钱交给我吧，我会转交给工匠的。\n    你交钱24小时后就可以来找我索取王之号角了，我想24小时已经足够让工匠来做这件事情了。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16) && gone_time(who->get_save("wangzhhj"))>=86400 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠通宵达旦地工作，终于在你来之前将王之号角雕琢好了，你拿去看看吧。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 10:
		if ( me->get_city_name() == who->get_city_name() && who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
		{
        		if (TASK_LEGEND_D->check_task_item(who,"号角",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,14);
			who->add_exp(3000);
			who->add_potential(100);
			who->add_cash(2500);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,13,"" );
			send_user(who,"%c%s",';',"寻求大王的帮助 经验 3000 潜能 100 金钱 2500");
			me->do_welcome(19);
        	}		
		break;
	case 11:
		if ( me->get_city_name() == who->get_city_name() && who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( who->get_cash() < 1000000 )
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你身上的钱不足以让工匠购买雕琢王之号角的材料，请你凑齐了钱再来找我吧。\n"ESC"离开", me->get_name(),getoid(me)));
				return ;	
			}
			who->add_cash(-1000000);
			who->set_save("wangzhhj",time());
        		who->set_legend(TASK_40,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"Chu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,14,"王之号角的雕琢" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"王之号角的雕琢");
        	}		
		break;
	case 12:
		if ( me->get_city_name() == who->get_city_name() && who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16) && gone_time(who->get_save("wangzhhj"))>=86400 )
		{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;        		
			TASK_LEGEND_D->give_item(who,"item/std/0095",1); 			
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,16);
			who->delete_save("wangzhhj");
			who->add_exp(3000);
			who->add_potential(100);
			who->add_cash(2500);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,14,"" );
			send_user(who,"%c%s",';',"王之号角的雕琢 经验 3000 潜能 100 金钱 2500");
		}
		break;
	case 99:
 		EMPEROR_D->do_look( who, me); 
 		break;
        }
}
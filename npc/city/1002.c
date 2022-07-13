
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
//void do_defence( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5201; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tề Quốc Đại Tướng Quân");
	set_real_name("Điền Kị");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "patrol"        : (: do_patrol :),
                "soldier"       : (: do_soldier :),
                "armor"         : (: do_armor :),
                "welcome"	: (: do_welcome :),
            //    "defence"	: (: do_defence :),
        ]) );
//	set("level",74);
//	set("legend",({32*24+4})); 
	set("mpLegend",([70:({32*24+4,}),75:({32*24+20,}),100:({32*36+11}),]));
	set("mpLegend2",([0:({32*9+30,32*29+27,32*30+7,}),70:({32*24+6,}),75:({32*24+22,}),100:({32*36+13,32*36+28,}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

//void do_defence(string arg) { "/sys/party/defence"->do_defence(this_player(), this_object(), arg); }

void do_look( object who )
{
	int id;
	string tmp="";
	object me = this_object();
	
	id = getoid(me);
	if ( who->get_legend(TASK_09,28) && !who->get_legend(TASK_09,30) )
	{
		tmp = sprintf(ESC HIY "欺诈的天罚\ntalk %x# welcome.1\n",id);
	}
	if ( (who->get_level() >= 70 && !who->get_legend(TASK_24,4)) || (who->get_legend(TASK_24,4) && !who->get_legend(TASK_24,6)) )
	{
		tmp += sprintf(ESC HIY "罐中妖\ntalk %x# welcome.3\n",id);
	}
	if ( (who->get_level() >= 75 && !who->get_legend(TASK_24,20)) || (who->get_legend(TASK_24,20) && !who->get_legend(TASK_24,22)) )
	{
		tmp += sprintf(ESC HIY "该死的冤魂\ntalk %x# welcome.6\n",id);
	}
	if ( who->get_legend(TASK_29,26) && !who->get_legend(TASK_29,27) )
	{
		tmp += sprintf(ESC HIY "探访将军\ntalk %x# welcome.9\n",id);
	}
	if ( who->get_legend(TASK_29,27) && !who->get_legend(TASK_30,1) )
	{
		tmp += sprintf(ESC HIY "将军信函\ntalk %x# welcome.9\n",id);
	}
	if ( who->get_legend(TASK_30,6) && !who->get_legend(TASK_30,7) )
	{
		tmp += sprintf(ESC HIY "失而复得\ntalk %x# welcome.9\n",id);
	}
	if ( (who->get_level() >= 100 && !who->get_legend(TASK_36,11)) || (who->get_legend(TASK_36,11) && !who->get_legend(TASK_36,13)) )
	{
		tmp += sprintf(ESC HIY "临危不惧\ntalk %x# welcome.13\n",id);
	}
	if ( who->get_legend(TASK_36,26) && !who->get_legend(TASK_36,28) )
	{
		tmp += sprintf(ESC HIY "大齐的崛起\ntalk %x# welcome.16\n",id);
	}
//	if ("/sys/sys/count"->get_war_flag1()||"/sys/party/defence"->get_state())
//		tmp += sprintf(ESC HIY "Chiến Trường Thủ Thành\ntalk %x# defence.1\n",id);
	
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),id) +
		tmp +
		ESC"离开");
	else
		GENERAL_D->do_look( who, this_object() ); 
	
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
        string tmp;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_09,28) && !who->get_legend(TASK_09,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    善有善报，恶有恶报，不是不报，时候未到！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_09,29) && !who->get_legend(TASK_09,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这帮杂碎终于得到了应有的惩罚！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_legend(TASK_09,29) && !who->get_legend(TASK_09,30) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64029",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_09,30);
			who->add_exp(3500);
			who->add_potential(112);
			who->add_cash(3000);
			send_user(who,"%c%s",';',"欺诈的天罚 经验 3500 潜能 112 金钱 3000 碧龙行装图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,5,"" );
        	}
        	break;   
        case 3:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_24,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前一阵子我军的军粮库被一群罐中妖大肆破坏，虽然粮食没有损失，但是我们用来装食物的罐子全部被这群罐中妖抢走了，虽然那些食物罐被他们抢去之后就不可以再用来装粮食了，但是我们必须要对那群罐中妖施以惩戒，让他们以后不敢来我的军营捣乱。你去帮我消灭10只罐中妖，他们现在都已经逃到灵谷洞的一层了，事成之后我会好好的赏赐你的！\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_24,4) && !who->get_legend(TASK_24,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我交代你去办的事办好了没有？如果你连这样的小事情都办不好的话你也别幻想可以在这个乱世出人头地了！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_24,5) && !who->get_legend(TASK_24,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那群罐中妖看来以后也不敢来我的军营捣乱了，这是我承诺过给你的奖励，本将军是语出必行的，拿好吧！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 4:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_24,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,4);
        		who->delete_save_2("qgdjjguanzy");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,14,"罐中妖" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"罐中妖");
        	}
        	break; 
        case 5:
        	if ( who->get_legend(TASK_24,5) && !who->get_legend(TASK_24,6) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/65077",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,6);
        		who->delete_save_2("qgdjjguanzy");
			who->add_exp(28000);
			who->add_potential(490);
			who->add_cash(29000);
			send_user(who,"%c%s",';',"罐中妖 经验 28000 潜能 490 金钱 29000 幽魂项链图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,14,"" );
        	}
        	break;  
        case 6:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_24,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听王府里面的人说，最近齐王田建府里面经常闹鬼，搞得王府里面的人个个面容消瘦，无精打采。我决不允许这样的祸害威胁到大王！我已经派探子查到，在王府闹的鬼就是灵谷洞二层那些冤魂，你去灵谷洞二层去杀掉20个冤魂，让他们以后都不敢再来齐王田建府胡闹！\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_24,20) && !who->get_legend(TASK_24,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    赶快去吧！不杀死这些冤魂的话，王府每天晚上都不得安宁。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_24,21) && !who->get_legend(TASK_24,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好，这下就已经起到杀鸡警鸭的作用了！我看这些冤魂以后永远也不敢踏足齐王田建府半步。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 7:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_24,20) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,20);
        		who->delete_save_2("qgdjjyuanhun");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,17,"该死的冤魂" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"该死的冤魂");
        	}
        	break; 
        case 8:
        	if ( who->get_legend(TASK_24,21) && !who->get_legend(TASK_24,22) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64134",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,22);
        		who->delete_save_2("qgdjjyuanhun");
			who->add_exp(35000);
			who->add_potential(510);
			who->add_cash(33000);
			send_user(who,"%c%s",';',"该死的冤魂 经验 35000 潜能 510 金钱 33000 狂龙鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,17,"" );
        	}
        	break;  
        case 9:
        	if ( who->get_legend(TASK_29,26) && !who->get_legend(TASK_29,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎！一言难尽啊！\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_29,27) && !who->get_legend(TASK_30,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，前天来了两个刺客，搞得军营鸡飞狗跳，最后除了伤了我手下一个亲兵外，居然还将我的调兵信物威虎将军令偷去了，我们只抓住了一个刺客，可是她竟然宁死不招，现在我也没辙了，只好向御史大人求助了，你将我亲笔信函交给御史大人，看他是否有好办法。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,6) && !who->get_legend(TASK_30,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈！这下我可以放心了。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 10:
        	if ( who->get_legend(TASK_29,26) && !who->get_legend(TASK_29,27) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,27);
			who->add_exp(56000);
			who->add_potential(750);
			who->add_cash(53000);
			send_user(who,"%c%s",';',"探访将军 经验 56000 潜能 750 金钱 53000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,30,"" );
			me->do_welcome(9);
        	}
        	break; 
        case 11:
        	if ( who->get_legend(TASK_29,27) && !who->get_legend(TASK_30,1) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/98/0143",1);
        		who->set_legend(TASK_30,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,31,"将军信函" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"将军信函");
        	}
        	break;
        case 12:
        	if ( who->get_legend(TASK_30,6) && !who->get_legend(TASK_30,7) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"威虎将军令",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/final/33/1770",5);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,7);
			who->add_exp(63000);
			who->add_potential(800);
			who->add_cash(52000);
			send_user(who,"%c%s",';',"失而复得 经验 63000 潜能 800 金钱 52000 神秘果 5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,34,"" );
        	}
        	break;
        case 13:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,11)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本将军将要大规模选拔一批有理想、有智谋、有勇气、有武力的青年作为本军的王牌劲旅，本将军想出了几个考核项目，第一个首先就要做到能够临危不惧，年轻人你想接受挑战，成为光荣的一员吗，你就先去九曲桥消灭8只罐中仙，11只龟仙人吧！\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_36,11) && !who->get_legend(TASK_36,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呃，实在抱歉，看来我们军队不需要你。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_36,12) && !who->get_legend(TASK_36,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好样的，年轻人，第一轮海选通过，你回家等候下一轮通知吧！\n"ESC"完成任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 14:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,11)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_36,11);
        		who->delete_save("qgdjjguanzx");
        		who->delete_save("qgdjjguixr");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,53,"临危不惧" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"临危不惧");
        	}
        	break;
	case 15:
        	if ( who->get_legend(TASK_36,12) && !who->get_legend(TASK_36,13) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,13);
        		who->delete_save("qgdjjguanzx");
        		who->delete_save("qgdjjguixr");
			who->add_exp(80000);
			who->add_potential(955);
			who->add_cash(68000);
			send_user(who,"%c%s",';',"临危不惧 经验 80000 潜能 955 金钱 68000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,53,"" );
        	}
        	break; 
        case 16:
        	if ( who->get_legend(TASK_36,26) && !who->get_legend(TASK_36,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近不少义士都襄助我军不少武器，不知义士你可也是前来送武器的？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_36,27) && !who->get_legend(TASK_36,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，有这么多义士襄助，我军何愁不破匪秦？\n"ESC"完成任务\ntalk %x# welcome.17\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 17:
        	if ( who->get_legend(TASK_36,27) && !who->get_legend(TASK_36,28) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"利剑",10) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"快刀",10) != 1 )
        		{
        			TASK_LEGEND_D->give_item(who,"item/98/0171",10); 
        			return;
        		}
        		TASK_LEGEND_D->give_item(who,"item/final/16/1633",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,28);
        		who->delete_save("qwlijian");
        		who->delete_save("qwkuaidao");
			who->add_exp(84000);
			who->add_potential(1048);
			who->add_cash(73000);
			send_user(who,"%c%s",';',"大齐的崛起 经验 84000 潜能 1048 金钱 73000 当铺链接器 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,58,"" );
        	}
        	break; 
 	case 99:
 		GENERAL_D->do_look( who, me); 
 		break;
        }
}
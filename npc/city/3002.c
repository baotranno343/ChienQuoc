
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
        set_name("Triệu Quốc Đại Tướng Quân");
	set_real_name("Lý Mục");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "patrol"        : (: do_patrol :),
                "soldier"       : (: do_soldier :),
                "armor"         : (: do_armor :),
                "welcome"	: (: do_welcome :),
            //    "defence"	: (: do_defence :),
        ]) );
//	set("level",81);
//	set("legend",({32*27+7})); 
 	set("mpLegend",([80:({32*27+7,32*28+26}),60:({32*51+10}),105:({32*38+29,}),110:({32*43+26})]));
 	set("mpLegend2",([0:({32*29+3,32*41+17,32*41+25,32*42+4,}),60:({32*51+12}),80:({32*27+9,32*28+28,}),110:({32*39+4,32*43+28,})]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

//void do_defence(string arg) { "/sys/party/defence"->do_defence(this_player(), this_object(), arg); }


void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 80 && !who->get_legend(TASK_27,7)) || (who->get_legend(TASK_27,7) && !who->get_legend(TASK_27,9)) )
	{
		tmp += sprintf(ESC HIY "万人坑的骷髅\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >= 80 && !who->get_legend(TASK_28,26)) || (who->get_legend(TASK_28,26) && !who->get_legend(TASK_28,28)) )
	{
		tmp += sprintf(ESC HIY "证明实力\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( (who->get_legend(TASK_28,28) && !who->get_legend(TASK_29,1)) || (who->get_legend(TASK_29,1) && !who->get_legend(TASK_29,3)) )
	{
		tmp += sprintf(ESC HIY "秘密行动\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( who->get_level() >= 105 && !who->get_legend(TASK_38,29) )
		tmp += sprintf(ESC HIY "挖掘人才\ntalk %x# welcome.9\n",getoid(me));
	if ( who->get_level() >= 110 && who->get_legend(TASK_39,3) && !who->get_legend(TASK_39,4) )
		tmp += sprintf(ESC HIY "嘱托之事\ntalk %x# welcome.11\n",getoid(me));
	if ( who->get_legend(TASK_41,16) && !who->get_legend(TASK_41,17) )
		tmp += sprintf(ESC HIY "询问原由\ntalk %x# welcome.13\n",getoid(me));
	if ( who->get_legend(TASK_41,17) && !who->get_legend(TASK_41,18) )
		tmp += sprintf(ESC HIY "打探下落\ntalk %x# welcome.13\n",getoid(me));
	if ( who->get_legend(TASK_41,24) && !who->get_legend(TASK_41,25) )
		tmp += sprintf(ESC HIY "天门探险\ntalk %x# welcome.13\n",getoid(me));
	if ( who->get_legend(TASK_41,25) && !who->get_legend(TASK_41,26) )
		tmp += sprintf(ESC HIY "上奏赵王\ntalk %x# welcome.13\n",getoid(me));
	if ( who->get_legend(TASK_42,3) && !who->get_legend(TASK_42,4) )
		tmp += sprintf(ESC HIY "询问战果\ntalk %x# welcome.18\n",getoid(me));
	if ( who->get_legend(TASK_42,4) && !who->get_legend(TASK_42,5) )
		tmp += sprintf(ESC HIY "询查战报\ntalk %x# welcome.18\n",getoid(me));
	if ( (who->get_level() >= 110 && !who->get_legend(TASK_43,26)) || ( who->get_legend(TASK_43,26) && !who->get_legend(TASK_43,28) ))
		tmp += sprintf(ESC HIY "权力的象征\ntalk %x# welcome.21\n",getoid(me));
	if ( (who->get_level() >= 50 && !who->get_legend(TASK_2_01,10)) || (who->get_legend(TASK_2_01,10) && !who->get_legend(TASK_2_01,12)))
		tmp += sprintf(ESC HIY "收集机关构件\ntalk %x# welcome.24\n",getoid(me));
//	if ("/sys/sys/count"->get_war_flag1()||"/sys/party/defence"->get_count())
//		tmp += sprintf(ESC HIY "Chiến Trường Thủ Thành\ntalk %x# defence.1\n",getoid(me));
		
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
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
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if (who->get_level() >= 80 && !who->get_legend(TASK_27,7))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    万人坑里面最近集结了大批的骷髅军队，如果继续放任其骷髅增长的话，将会对我国安全造成重大威胁。所以我先发制人，在这些骷髅还没有正式成为威胁之前把他们歼灭，如果可以的话，你就帮助我去万人坑除掉20个刀盾骷髅和10个剑盾骷髅吧。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_27,7) && !who->get_legend(TASK_27,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果不先发制人除去那里的骷髅的话，我国将会面临重大威胁。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_27,8) && !who->get_legend(TASK_27,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，做得不错，这样一来我国军队就可以放心用于防范边疆了。这是给你的奖励，拿好了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if (who->get_level() >= 80 && !who->get_legend(TASK_27,7))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_27,7);
        		who->delete_save_2("zgdjjdaodkl");
        		who->delete_save_2("zgdjjjiandkl");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,41,"万人坑的骷髅" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"万人坑的骷髅");
        	}
        	break; 
        case 3:
        	if ( who->get_legend(TASK_27,8) && !who->get_legend(TASK_27,9) )
        	{
        		who->delete_save_2("zgdjjdaodkl");
        		who->delete_save_2("zgdjjjiandkl");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_27,9);
			who->add_exp(46000);
			who->add_potential(645);
			who->add_cash(45000);
			send_user(who,"%c%s",';',"万人坑的骷髅 经验 46000 潜能 645 金钱 45000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,41,"" );
        	}
        	break;   
        case 4:
        	if (who->get_level() >= 80 && !who->get_legend(TASK_28,26))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我可是Triệu Quốc Đại Tướng QuânLý Mục，想跟着我混吗，很好，可是我手下从来不收无名之辈，新来的可得投个投名状，如果仅仅让你收拾个小瘪三那就太没有价值了，那样你最多能够作个小校，要是你想做更高的，那么就得接受我更艰巨的挑战，怎么准备好了吗，那好，你去万人坑杀掉刀盾骷髅10只、剑盾骷髅10只、双刀骷髅8只，如果完好无缺的回来本大将军自然会重用你。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_28,26) && !who->get_legend(TASK_28,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    若你不能证明你自己的实力，我又怎能放心将那件重要的事情交给你去办呢？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_28,27) && !who->get_legend(TASK_28,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然你已经向我证明了你的实力，那么我会有更重要的事情交给你。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_28,28) && !who->get_legend(TASK_29,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    在邯郸城外的牧场，是一片荒芜之地，也常常成为心怀叵测人的藏身之地，最近得到密报，秦国派了一名刺客代号叫做李五的正躲藏在那里密谋行动，你赶快去干掉他，免得夜长梦多，切记谨慎行事。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_29,1) && !who->get_legend(TASK_29,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n   如果你不能杀掉他，那么你可以选择放弃，但是你必须答应我，不能走漏半点风声！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_29,2) && !who->get_legend(TASK_29,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你能单独完成这次行动，并且没有走漏半点风声，真不错！\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 5:
        	if (who->get_level() >= 80 && !who->get_legend(TASK_28,26))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,26);
        		who->delete_save("zgdjjdaodunkl");
        		who->delete_save("zgdjjjiandunkl");
        		who->delete_save("zgdjjsuangdaokl");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,52,"证明实力" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"证明实力");
        	}
        	break; 
        case 6:
        	if ( who->get_legend(TASK_28,27) && !who->get_legend(TASK_28,28) )
        	{
        		who->delete_save("zgdjjdaodunkl");
        		who->delete_save("zgdjjjiandunkl");
        		who->delete_save("zgdjjsuangdaokl");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,28);
			who->add_exp(52000);
			who->add_potential(710);
			who->add_cash(49000);
			send_user(who,"%c%s",';',"证明实力 经验 52000 潜能 710 金钱 49000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,52,"" );
			me->do_welcome(4);
        	}
        	break;     
        case 7:
        	if ( who->get_legend(TASK_28,28) && !who->get_legend(TASK_29,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,1);
 			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,53,"秘密行动" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"秘密行动");
        	}
        	break; 
        case 8:
        	if ( who->get_legend(TASK_29,2) && !who->get_legend(TASK_29,3) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64152",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,3);
			who->add_exp(52500);
			who->add_potential(730);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"秘密行动 经验 52500 潜能 730 金钱 50000 翻云头巾图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,53,"" );
        	}
        	break;
        case 9:
		if ( who->get_level() >= 105 && !who->get_legend(TASK_38,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    早就听说过秦国守卫是一个不可多得的人才，秦国用他来做守卫，实在是辱没了这个人才啊！\n    论资质，他比我们这军营里任何一个士兵还要聪慧；论刻苦，他比我们军营里任何一个士兵还要勤奋；论灵活，他比我们军营里任何一个士兵还要敏捷。\n    这样的一个人才，叫惜才之人怎能不爱呢！我希望你能说服他来我们赵国军队里做一名出色的将军！\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	break;	     
        case 10:
        	if ( who->get_level() >= 105 && !who->get_legend(TASK_38,29) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,29);
 			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,66,"挖掘人才" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"挖掘人才");
        	}
        	break;
	case 11:
		if ( who->get_level() >= 110 && who->get_legend(TASK_39,3) && !who->get_legend(TASK_39,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这事我知道了，还望此事你不要声张，如果泄密，“咔嚓！”明白我的意思吧。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 12:
		if ( who->get_level() >= 110 && who->get_legend(TASK_39,3) && !who->get_legend(TASK_39,4) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_39,4);
			who->add_exp(50000);
			who->add_potential(610);
			who->add_cash(48000);
			send_user(who,"%c%s",';',"嘱托之事 经验 50000 潜能 610 金钱 48000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,94,"" );
        	} 
        	break;
	case 13:
		if ( who->get_legend(TASK_41,16) && !who->get_legend(TASK_41,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，大王贪图眼前利益，我国将有大祸啊！\n"ESC"完成任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_41,17) && !who->get_legend(TASK_41,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，大王贪图城池，竟然收下了韩国太守冯亭贡献的上党郡，而秦国逐渐蚕食韩国领土，岂愿意放弃这块嘴边的肥肉啊，而如今韩国把上党郡献给赵国，是想把祸水引向赵国啊，秦国如此费尽周折却让我国得到了利益，如何能够甘心？然则君王所喜，仅见当前十六邑，却不知大祸将至，为臣之本分，只得全力备战。我听闻天门阵法玄妙无比，若是习得此阵法，所向披靡，百战不殆 ，不过此是天物，得到谈何容易？我一直希望能有能人异士能助我取得此书，我见这位壮士精华内敛，器宇不凡，不知可愿为本国当此重任？你去寻赵总管当可告诉你详情。\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_41,24) && !who->get_legend(TASK_41,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，终于拿到了天门阵法，本将军定将来犯之敌打个落花流水！\n"ESC"完成任务\ntalk %x# welcome.16\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_41,25) && !who->get_legend(TASK_41,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本将军现在对于将要到来的秦赵之战信心百倍，我想与其被动挨打，不如主动出击，我拟了一份请战书，请你代我交给大王，我想主动请缨，前往守卫上党郡，本将必大败敌军，决不会让大王失望。\n"ESC"接受任务\ntalk %x# welcome.17\n"ESC"离开", me->get_name(),getoid(me)));

		break;
        case 14:
		if ( who->get_legend(TASK_41,16) && !who->get_legend(TASK_41,17) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_41,17);
			who->add_exp(89000);
			who->add_potential(1500);
			who->add_cash(81000);
			send_user(who,"%c%s",';',"询问原由 经验 89000 潜能 1500 金钱 81000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,68,"" );
			me->do_welcome(13);
        	} 
        	break;
	case 15:
       		if ( who->get_legend(TASK_41,17) && !who->get_legend(TASK_41,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_41,18);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,69,"打探下落" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"打探下落");
        	}
        	break;
        case 16:
		if ( who->get_legend(TASK_41,24) && !who->get_legend(TASK_41,25) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"天门阵法",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_41,25);
			who->add_exp(94000);
			who->add_potential(1700);
			who->add_cash(84000);
			send_user(who,"%c%s",';',"天门探险 经验 94000 潜能 1700 金钱 84000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,71,"" );
			me->do_welcome(13);
        	} 
        	break;
	case 17:
       		if ( who->get_legend(TASK_41,25) && !who->get_legend(TASK_41,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0204",1); 
        		who->set_legend(TASK_41,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,72,"上奏赵王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"上奏赵王");
        	}
        	break;
	case 18:
		if ( who->get_legend(TASK_42,3) && !who->get_legend(TASK_42,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    廉将军的军报一俟送到我已经派传令兵发送了王府，怎么没有消息？\n"ESC"完成任务\ntalk %x# welcome.19\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,4) && !who->get_legend(TASK_42,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    什么？战报过了一个月都没有送到王府？这么紧要的事情我的传令兵居然没有通报？来人，把送战报的传令兵拖下去重责50军棍再上来问话，什么，没有回来过？事情严重了，这位壮士，看来只有你悄悄去民间向我国百姓打听下，有没有战报的蛛丝马迹。\n"ESC"接受任务\ntalk %x# welcome.20\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 19:
		if ( who->get_legend(TASK_42,3) && !who->get_legend(TASK_42,4) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_42,4);
			who->add_exp(94000);
			who->add_potential(1550);
			who->add_cash(84000);
			send_user(who,"%c%s",';',"询问战果 经验 94000 潜能 1550 金钱 84000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,74,"" );
			me->do_welcome(18);
        	} 
        	break;
	case 20:
		if ( who->get_legend(TASK_42,4) && !who->get_legend(TASK_42,5) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,5);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,75,"询查战报" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询查战报");
        	}
		break;
	case 21:
		if (who->get_level() >= 110 && !who->get_legend(TASK_43,26))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    （大将军挥退左右，）低低对道：“大侠可为我保密?都怪我一时糊涂，迷上了一个女子，哪里知道竟然是太极门的细作，他们下了迷神散将我掳到天门阵威胁我合作，我虚以委蛇，但是却被迫留下令旗作质押，令旗丢失可是死罪啊，如今我寝食难安，但是却万万不愿意与此等匪类合作，不知大侠可为我寻回令旗？如能成功，只要我权责之内，我定满足大侠的愿望！那令旗他们放在天门阵的3层，还望大侠能救我则个！”\n"ESC"接受任务\ntalk %x# welcome.22\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_43,26) && !who->get_legend(TASK_43,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我知道匪人人多势众，但我还是相信大侠的身手定能手到擒来！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_43,27) && !who->get_legend(TASK_43,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，壮士，我是多么感激你，多么热爱你，你找回了令旗，救了我一命，我真的不知道如何表达我对你的感激和热爱，我用我对英雄的礼节吧！（Triệu Quốc Đại Tướng QuânLý Mục坚实的臂膀将你紧紧拥抱，密密的胡茬扎得你如芒刺在背，你艰难的喘着气，挣脱出一只手来，颤抖着伸到大将军眼前，用坚定的眼神提醒着他。）\n"ESC"完成任务\ntalk %x# welcome.23\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 22:
		if (who->get_level() >= 110 && !who->get_legend(TASK_43,26))
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_43,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,59,"权力的象征" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"权力的象征");
        	}
		break;
        case 23:
		if ( who->get_legend(TASK_43,27) && !who->get_legend(TASK_43,28) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"令旗",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_43,28);
			who->add_exp(90000);
			who->add_potential(970);
			who->add_cash(93000);
			send_user(who,"%c%s",';',"权力的象征 经验 90000 潜能 970 金钱 93000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,59,"" );
        	} 
        	break;
        case 24:
        	if ( who->get_level() >= 50 && !who->get_legend(TASK_2_01,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本国与秦国边衅将起，秦国善使机关推动攻城利器，对此我十分头疼。这位壮士，听说秦国修建中的骊山陵墓里有许多机关兵俑，他们身上好像都有机关构件，你可否帮我去收集一些？\n"ESC"接受任务\ntalk %x# welcome.25\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_2_01,10) && !who->get_legend(TASK_2_01,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来那里还是太危险了，难道我赵国无望了吗？\n"ESC"离开", me->get_name(),));
		else if ( who->get_legend(TASK_2_01,11) && !who->get_legend(TASK_2_01,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    感谢你的帮助，你能号召更多的人来帮助我吗？\n"ESC"完成任务\ntalk %x# welcome.26\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 25:
        	if ( who->get_level() >= 50 && !who->get_legend(TASK_2_01,10) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_2_01,10);
        		who->delete_save("fb_qgjggj");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,101,"收集机关构件" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"收集机关构件");
		}
        	break;
        case 26:
        	if ( who->get_legend(TASK_2_01,11) && !who->get_legend(TASK_2_01,12) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"机关构件",10) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_2_01,12);
        		who->delete_save("fb_qgjggj");
			who->add_exp(12800);
			who->add_potential(500);
			who->add_cash(9600);
			send_user(who,"%c%s",';',"收集机关构件 经验 12800 潜能 500 金钱 9600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,101,"" );
        	}
        	break;
 	case 99:
 		GENERAL_D->do_look( who, me); 
 		break;
        }
}

// 自动生成：/make/npc/make8006

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define INQUISITOR_D    "/inh/city/inquisitor"

inherit OFFICER;

void do_elect( string arg );
void do_vote( string arg );
void do_score( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Ngự Sử");
	set_real_name("Trịnh Quốc");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "elect"         : (: do_elect :),
                "vote"          : (: do_vote :),
                "score"         : (: do_score :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",16);
//	set("legend",({32*4+7}));
	set("mpLegend",([15:({32*4+7}),]));
	set("mpLegend2",([0:({32*25+24,32*26+2,32*26+11,32*26+19,32*26+25,}),15:({32*4+8}),]));
        setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,7) ) || ( who->get_legend(TASK_04,7) && !who->get_legend(TASK_04,8) ) )
	{
		tmp = sprintf(ESC HIY "御史的烦恼\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_25,23) && !who->get_legend(TASK_25,24) )
		tmp += sprintf(ESC HIY "清除奸贼\ntalk %x# welcome.5\n",getoid(me));
	if ( who->get_legend(TASK_25,24) && !who->get_legend(TASK_25,25) )
		tmp += sprintf(ESC HIY "上奏韩王\ntalk %x# welcome.5\n",getoid(me));
	if ( who->get_legend(TASK_26,1) && !who->get_legend(TASK_26,2) )
		tmp += sprintf(ESC HIY "寻求帮助\ntalk %x# welcome.8\n",getoid(me));
	if ( who->get_legend(TASK_26,2) && !who->get_legend(TASK_26,3) )
		tmp += sprintf(ESC HIY "御史的建议\ntalk %x# welcome.8\n",getoid(me));
	if ( who->get_legend(TASK_26,10) && !who->get_legend(TASK_26,11) )
		tmp += sprintf(ESC HIY "商人哭诉\ntalk %x# welcome.11\n",getoid(me));
	if ( who->get_legend(TASK_26,18) && !who->get_legend(TASK_26,19) )
		tmp += sprintf(ESC HIY "为民除害\ntalk %x# welcome.11\n",getoid(me));
	if ( who->get_legend(TASK_26,19) && !who->get_legend(TASK_26,20) )
		tmp += sprintf(ESC HIY "寻人避难\ntalk %x# welcome.11\n",getoid(me));
	if ( who->get_legend(TASK_26,24) && !who->get_legend(TASK_26,25) )
		tmp += sprintf(ESC HIY "乐师的无奈\ntalk %x# welcome.16\n",getoid(me));
	if ( who->get_legend(TASK_26,25) && !who->get_legend(TASK_26,26) )
		tmp += sprintf(ESC HIY "寻求方法\ntalk %x# welcome.16\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INQUISITOR_D->do_look( who, this_object() ); 
	
}
void do_elect( string arg ) { INQUISITOR_D->do_elect( this_player(), this_object(), arg ); }
void do_vote( string arg ) { INQUISITOR_D->do_vote( this_player(), this_object(), arg ); }
void do_score( string arg ) { INQUISITOR_D->do_score( this_player(), this_object(), arg ); }
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
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大侠你终于出现了！王子犯法，与庶民同罪。本官我最近正准备调查一桩关于王族的大案，可是关系到此案的证据，在路过无定河的将军冢的时候被神秘刺客袭击，不小心丢失掉了。还望%s能帮本官寻回此案的证据，定重谢。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_04,7) && !who->get_legend(TASK_04,8) )
			me->do_welcome(4);
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,7) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->remove_task_item(who, "证据");                   	
        		who->set_legend(TASK_04,7);
			who->delete_save("yushizhengju");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,3,"御史的烦恼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"御史的烦恼");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_04,7) && !who->get_legend(TASK_04,8) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"证据",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,8);
			who->delete_save("yushizhengju");
			who->delete_save_2("yushizhengju");
			who->add_exp(1200);
			who->add_potential(70);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"御史的烦恼 经验 1200 潜能 70 金钱 1500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,3,"" );
        	}
        	break;
        case 4:
        	if ( !who->get_legend(TASK_04,7) || who->get_legend(TASK_04,8) )
        		return ;
        	if ( objectp(item=present("证据",who,1,MAX_CARRY)) && item->is_legend_item() == 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了，看那真凶往哪里逃？本官定要维护法纪之清明。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有此证据我如何将那罪犯绳之于法，看来此案只能作为一个悬案了。\n"ESC"离开", me->get_name()));
        	break;
	case 5:
        	if ( who->get_legend(TASK_25,23) && !who->get_legend(TASK_25,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    什么？你已经把武之真给除掉了？这位勇士这是身手不凡啊，我们韩国总算逃过一劫。我代表我们全国上下对你表示感谢。虽然这次的事件已经平息了，但是秦国这样的“虎狼之帮”肯定不会就此罢休的，我们还得认真商议防范秦国的计策。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_25,24) && !who->get_legend(TASK_25,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    以我们现在的实力是没可能单独防范秦国的进攻的。要防范秦国我们只有采取“合纵”的政策，联合其他国家一齐对抗秦国。楚国是与我们韩国唇齿之国，如果跟楚国“合纵”抗秦，秦国必然不敢轻举妄动。你替我把这一封奏书上呈给大王，上面把这次事件的详细经过和韩楚联盟的利害都写的很清楚，我想大王一定会作出英明的决策的。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));

		break;		
         case 6:
        	if ( who->get_legend(TASK_25,23) && !who->get_legend(TASK_25,24) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_25,24);
			who->add_exp(35000);
			who->add_potential(530);
			who->add_cash(36000);
			send_user(who,"%c%s",';',"清除奸贼 经验 35000 潜能 530 金钱 36000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,23,"" );
			me->do_welcome(5);
        	}
        	break;
	case 7:
        	if( who->get_legend(TASK_25,24) && !who->get_legend(TASK_25,25) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0120");
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
        		who->set_legend(TASK_25,25);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,24,"上奏韩王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"上奏韩王");
        	}
        	break;       
	case 8:
        	if ( who->get_legend(TASK_26,1) && !who->get_legend(TASK_26,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，如果那条河受诅咒了确实是一件严重的事。这种诅咒河水的诅咒我以前在一些文献上看见过。你先休息一下，让我先去查查是哪部文献上面记载过这样的诅咒。\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,2) && !who->get_legend(TASK_26,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    刚才我已经查到那部文献了，原来现在唯一懂得这种解除河水诅咒的方法的人叫做王真人，但是我们的户籍里面已经找不到他的居所了，在我国民间还是有很多人知道他的，你去找些我国的百姓打听一下他的消息吧！\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 9:
        	if ( who->get_legend(TASK_26,1) && !who->get_legend(TASK_26,2) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"密件",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,2);
			who->add_exp(36000);
			who->add_potential(550);
			who->add_cash(38000);
			send_user(who,"%c%s",';',"寻求帮助 经验 36000 潜能 550 金钱 38000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,27,"" );
			me->do_welcome(8);
        	}
        	break;
	case 10:
        	if( who->get_legend(TASK_26,2) && !who->get_legend(TASK_26,3) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_26,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,28,"御史的建议" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"御史的建议");
        	}
        	break;   
	case 11:
        	if ( who->get_legend(TASK_26,10) && !who->get_legend(TASK_26,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    林为的确是有冤情，但是杀害林为的妻子的土匪身处妖物满布的灵谷洞的最底层，我们要捉拿他有一定的难度。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,11) && !who->get_legend(TASK_26,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那杀害林为的妻子的土匪自持懂得操纵鬼灵之术，藏身在妖物满布的灵谷洞的最深处，想要捉拿他必须动员我国大量的兵士。但是我国的兵士现在都在边境提防秦国的进攻，一刻也不可以离开岗位，所以现在要捉拿那土匪有点困难。这件事我先交给内政官去处理，你去找他吧，他应该可以想到两全其美的方法。\n"ESC"接受任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,18) && !who->get_legend(TASK_26,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    想不到仅靠你的一己之力已经可以省去我们国家这么多的人力物力。在下对你实在是佩服呀！\n"ESC"完成任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,19) && !who->get_legend(TASK_26,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然你已经成功把土匪马大这个恶贼就地正法了，那么你就赶快去告诉林为你已经为他的妻子报仇了吧！相信林为听到这个消息之后一定会重新振作起来。其实事情到现在才解决我们官府也是无可奈何呀，现在这个乱世有时候甚至连我们官府都不能自保啊！\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
 
		break;
	case 12:
        	if ( who->get_legend(TASK_26,10) && !who->get_legend(TASK_26,11) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"状纸",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,11);
			who->add_exp(38000);
			who->add_potential(570);
			who->add_cash(38000);
			send_user(who,"%c%s",';',"商人哭诉 经验 38000 潜能 570 金钱 38000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,31,"" );
			me->do_welcome(11);
        	}
        	break;
	case 13:
        	if( who->get_legend(TASK_26,11) && !who->get_legend(TASK_26,12) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_26,12);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,32,"御史的担心" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"御史的担心");
        	}
        	break; 
	case 14:
        	if ( who->get_legend(TASK_26,18) && !who->get_legend(TASK_26,19) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,19);
			who->add_exp(40000);
			who->add_potential(590);
			who->add_cash(40000);
			send_user(who,"%c%s",';',"为民除害 经验 40000 潜能 590 金钱 40000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,34,"" );
			me->do_welcome(11);
        	}
        	break;
	case 15:
        	if( who->get_legend(TASK_26,19) && !who->get_legend(TASK_26,20) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_26,20);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,35,"寻人避难" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻人避难");
        	}
        	break; 
	case 16:
        	if ( who->get_legend(TASK_26,24) && !who->get_legend(TASK_26,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    其实我对这件案件也有不同的看法，因为我早已经认识乐师的父亲，所以我对他为人很了解，像这样忠厚的人是决不会做这种盗窃宝物的事情的。\n"ESC"完成任务\ntalk %x# welcome.17\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_26,25) && !who->get_legend(TASK_26,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    虽然他们已经把乐师的父亲定罪了，但是失窃的含鳞珠一直到现在都还没有找回来，如果能把失窃的含鳞珠找回来，那么就肯定可以替乐师的父亲翻案了。我有消息说那个被窃的含鳞珠被人藏在灵谷洞的最底层了。你去灵谷洞的三层查看一下吧，如果消息属实，那么你将找回来的含鳞珠送到我国内政官那里，他就会受理这件案的。\n"ESC"接受任务\ntalk %x# welcome.18\n"ESC"离开", me->get_name(),getoid(me)));
 
		break;
	case 17:
        	if ( who->get_legend(TASK_26,24) && !who->get_legend(TASK_26,25) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"诉苦书",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,25);
			who->add_exp(42000);
			who->add_potential(610);
			who->add_cash(42000);
			send_user(who,"%c%s",';',"乐师的无奈 经验 42000 潜能 610 金钱 42000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,37,"" );
			me->do_welcome(16);
        	}
        	break;
	case 18:
        	if( who->get_legend(TASK_26,25) && !who->get_legend(TASK_26,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_26,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,38,"寻求方法" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻求方法");
        	}
        	break; 
        case 99:	
		INQUISITOR_D->do_look( who, me); 
        	break;
        }
}
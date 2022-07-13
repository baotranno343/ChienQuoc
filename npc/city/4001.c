
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
        set_name("Ngụy Vương");
	set_real_name("Ngụy Chiêu Vương");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "policy"        : (: do_policy :),
                "relation"      : (: do_relation :),
                "master"        : (: do_master :),
                "advice"        : (: do_advice :),
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",91);
//        set("legend",({32*31+13}));
 	set("mpLegend",([90:({32*31+13}),]));
 	set("mpLegend2",([0:({32*34+20,32*35+26,}),90:({32*31+15}),]));
        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

void do_look( object who ) 
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 90 && !who->get_legend(TASK_31,13)) || (who->get_legend(TASK_31,13) && !who->get_legend(TASK_31,15)) )
	{
		tmp += sprintf(ESC HIY "通缉犯\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_34,19) && !who->get_legend(TASK_34,20) )
		tmp += sprintf(ESC HIY "奏请王命\ntalk %x# welcome.4\n",getoid(me));
	if ( who->get_legend(TASK_35,25) && !who->get_legend(TASK_35,26) )
		tmp += sprintf(ESC HIY "禀告Ngụy Vương\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_save("dodolook") == 1 )
		tmp += sprintf(ESC"拜访Ngụy Chiêu Vương\ntalk %x# welcome.21\n",getoid(me));
	if ( who->get_save("dodolook") == 2 || who->get_save("dodolook") == 3  )
		tmp += sprintf(ESC"寻回玉玺\ntalk %x# welcome.21\n",getoid(me));
	if ( me->get_city_name() == who->get_city_name() )
	{
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			tmp += sprintf(ESC HIY "制作王之号角\ntalk %x# welcome.8\n",getoid(me));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			tmp += sprintf(ESC HIY "王之号角的雕琢\ntalk %x# welcome.8\n",getoid(me));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16)&& gone_time(who->get_save("wangzhhj"))>=86400 )
			tmp += sprintf(ESC HIY "索取王之号角\ntalk %x# welcome.8\n",getoid(me));
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
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_31,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有人利用邪法操纵枪俑与剑俑，妄图在孟尝君替寡人祭祀祖宗陵园的时候实施刺杀，失败后逃到将军古墓里去了，这些胆大妄为之人必须严惩！你去将军古墓消灭此次行刺后潜逃的枪俑9只、剑俑12只，再看看能不能找出幕后操作之人的蛛丝马迹。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,13) && !who->get_legend(TASK_31,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你连几个剑俑枪俑都不能抓获，何谈其他？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_31,14) && !who->get_legend(TASK_31,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，干掉了，可是还是没有任何操作之人的线索？看来我们还得细细追查啊！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
 
        	break;
        case 2:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_31,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,13);
        		who->delete_save("wwqianyong");
        		who->delete_save("wwjianyong");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,35,"通缉犯" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"通缉犯");
        	}
        	break; 
        case 3:
        	if ( who->get_legend(TASK_31,14) && !who->get_legend(TASK_31,15) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/64161",1);
        		who->delete_save("wwqianyong");
        		who->delete_save("wwjianyong");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,15);
			who->add_exp(60000);
			who->add_potential(900);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"通缉犯 经验 60000 潜能 900 金钱 50000 云龙战靴图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,35,"" );
        	}
        	break;   
        case 4:
        	if ( who->get_legend(TASK_34,19) && !who->get_legend(TASK_34,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本王准奏，希望能以此肃清本国风气。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
	case 5:
        	if ( who->get_legend(TASK_34,19) && !who->get_legend(TASK_34,20) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"请命奏书",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/63035",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,20);
			who->add_exp(74000);
			who->add_potential(930);
			who->add_cash(62000);
			send_user(who,"%c%s",';',"奏请王命 经验 74000 潜能 930 金钱 62000 紫心丹图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,46,"" );
	      	}
        	break; 
        case 6:
		if ( who->get_legend(TASK_35,25) && !who->get_legend(TASK_35,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，如此宝物，本王就可以常常去逗弄爱妃们了。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 7:
        	if ( who->get_legend(TASK_35,25) && !who->get_legend(TASK_35,26) )
        	{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),100,ARMOR_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);  
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,26);
			who->add_exp(81000);
			who->add_potential(1100);
			who->add_cash(71000);
			send_user(who,"%c%s",';',sprintf("禀告Ngụy Vương 经验 81000 潜能 1100 金钱 71000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,61,"" );
        	}
        	break;			

	case 8:
		if ( me->get_city_name() != who->get_city_name() )
			return;
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，宫廷里的工匠可以帮助你将普通的号角加工为王之号角，你将号角交给我，我替你咨询下工匠，看还需要做哪些准备。\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠说将普通的号角雕琢成为王之号角需要花费很多珍贵的材料，他需要一些钱来购买这些材料，而单靠他一个人的力量是不可能拿出这么多钱的，我想你应该要帮助他承担一部分，他说雕琢王之号角对他来说也是一项挑战，所以他不收你一文的加工费，只需要你给他100万的材料费就够了。如果你还想雕琢王之号角的话，就将钱交给我吧，我会转交给工匠的。\n    你交钱24小时后就可以来找我索取王之号角了，我想24小时已经足够让工匠来做这件事情了。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16) && gone_time(who->get_save("wangzhhj"))>=86400 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠通宵达旦地工作，终于在你来之前将王之号角雕琢好了，你拿去看看吧。\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 9:
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
	case 10:
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
	case 11:
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
	case 21:
		if ( who->get_save("dodolook") == 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听说你是来找一个叫dodolook的女孩？不错，她的确是被本王藏起来了，最近来找她的人太多了，本王可不能轻信于你！除非你接受本王的考验：本王的玉玺丢了，如果你能去（楚方城2）帮本王寻回遗失的玉玺，本王将给你一个信物，它将会给你带来意想不到的惊喜。\n"ESC"寻回玉玺\ntalk %x# welcome.22\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_save("dodolook") == 2 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本王的玉玺你可曾寻到，没有寻到还敢回来见本王！\n"ESC"离开", me->get_name()));
		else if ( who->get_save("dodolook") == 3 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    英雄！你果然是英雄！看来本王没有看错人，拿着这个七国令。不要小看它，你不仅可以用它找到dodolook，而且还能用它换到你想要的东西哦！\n"ESC"完成任务\ntalk %x# welcome.23\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 22:
		if ( who->get_save("dodolook") == 1 )
		{
			if ( USER_INVENTORY_D->count_empty_carry(who) < 1 )
			{
				send_user(who,"%c%s",'!',"清理一下你的包包！");
				return ;	
			}
			who->add_exp(1000);
			who->add_cash(1000);
			who->add_potential(50);
			item = new("item/91/9100");
			item->set_amount(5);
			p = item->move(who,-1);
			item->add_to_user(p);
			send_user( who, "%c%s", '!', "得到任务 "HIR"寻回玉玺");
			who->set_save("dodolook",2);
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DODOLOOK, 1, "" );
			send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_DODOLOOK,"寻找dodolook" ); 
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DODOLOOK, 2, "寻回玉玺" );
			send_user(who,"%c%s",';',"拜访Ngụy Chiêu Vương 经验 1000 潜能 50 金钱 1000 行军散 5");
		}
		break;
	case 23:
		if ( who->get_save("dodolook") == 3 )
		{
			if ( USER_INVENTORY_D->count_empty_carry(who) < 2 )
			{
				send_user(who,"%c%s",'!',"清理一下你的包包！");
				return ;	
			}
                	if( !objectp( item = present("玉玺", who, 1, MAX_CARRY) ) || item->get("dodolook") != 1 )
                	{
				send_user( who, "%c%s", '!', "玉玺在哪里？");
                		return ;
                	}
                	item->remove_from_user();
                	destruct(item);
                	who->add_exp(2000);
			who->add_cash(2000);
			who->add_potential(50);
			item = new("item/91/9100");
			item->set_amount(5);
			p = item->move(who,-1);
			item->add_to_user(p);
			item = new("item/91/9110");
			item->set_amount(5);
			p = item->move(who,-1);
			item->add_to_user(p);
			item = new("item/04/7777");
			p = item->move(who,-1);
			item->add_to_user(p);
			who->set_save("dodolook",4);
			send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_DODOLOOK,"" ); 
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_DODOLOOK, 3, "" );
			send_user(who,"%c%s",';',"拜访Ngụy Chiêu Vương 经验 2000 潜能 50 金钱 2000 行军散 5 正气散 5 七国令 1");
			me->do_welcome(21);
		}
		break;

	case 99:
 		EMPEROR_D->do_look( who, me); 
 		break;
        }
}
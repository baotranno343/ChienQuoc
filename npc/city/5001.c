
// 自动生成：/make/npc/make8001

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

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
        set_name("Tần Vương");
	set_real_name("Doanh Chính");
        set_city_name("Tần Quốc");

        set_2( "talk", ([
                "policy"        : (: do_policy :),
                "relation"      : (: do_relation :),
                "master"        : (: do_master :),
                "advice"        : (: do_advice :),
                "welcome"	: (: do_welcome :),
        ]) );
 	set("mpLegend2",([0:({32*21+9,32*21+16,32*21+25,32*22+4,32*47+30,}),]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_21,8) && !who->get_legend(TASK_21,9) )
	{
		tmp = sprintf(ESC HIY "降旨修墓\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,15) && !who->get_legend(TASK_21,16) )
	{
		tmp += sprintf(ESC HIY "准备出使\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,24) && !who->get_legend(TASK_21,25) )
	{
		tmp += sprintf(ESC HIY "回奏Tần Vương\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( who->get_legend(TASK_22,3) && !who->get_legend(TASK_22,4) )
	{
		tmp += sprintf(ESC HIY "明辨是非\ntalk %x# welcome.6\n",getoid(me));
	}
	if ( who->get_legend(TASK_22,4) && !who->get_legend(TASK_22,5) )
	{
		tmp += sprintf(ESC HIY "真相大白\ntalk %x# welcome.6\n",getoid(me));
	}	

	if ( who->get_legend(TASK_47,29)&&!who->get_legend(TASK_47,30) ) 
		tmp += sprintf(ESC HIY "报效大王\ntalk %x# welcome.13\n",getoid(me)); 

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
        string tmp;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_21,8) && !who->get_legend(TASK_21,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此事既已准备周全，本王就下令郦山地宫即日开始动工。你去转告那工匠一声。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if (who->get_legend(TASK_21,8) && !who->get_legend(TASK_21,9))
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"修造信函",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,9);
			who->add_exp(15000);
			who->add_potential(370);
			who->add_cash(14000);
			send_user(who,"%c%s",';',"降旨修墓 经验 15000 潜能 370 金钱 14000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,30,"" );
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_21,15) && !who->get_legend(TASK_21,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    使节果然是高瞻远瞩，本王也不愿兄弟相残，徒让外人得利，你带本王口谕，着他即可出使赵国，完成本王重托。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,24) && !who->get_legend(TASK_21,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔……看来赵王迁还真是深谋远虑，可进可退啊……哈哈，本王可以放手进攻魏军，横扫宋齐了！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;  
	case 4:
        	if ( who->get_legend(TASK_21,15) && !who->get_legend(TASK_21,16) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,16);
			who->add_exp(17000);
			who->add_potential(380);
			who->add_cash(16000);
			send_user(who,"%c%s",';',"准备出使 经验 17000 潜能 380 金钱 16000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,33,"" );
        	}
        	break;
	case 5:
        	if (who->get_legend(TASK_21,24) && !who->get_legend(TASK_21,25))
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"回信函",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/63024",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,25);
			who->add_exp(18000);
			who->add_potential(400);
			who->add_cash(19000);
			send_user(who,"%c%s",';',"回奏Tần Vương 经验 18000 潜能 400 金钱 19000 活心丹图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,37,"" );
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_22,3) && !who->get_legend(TASK_22,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    奏书本王已经收到，至于大将军是否被冤屈，本王自有定夺。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_22,4) && !who->get_legend(TASK_22,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，本王一直都质疑许子高造谣生事的，说本王大将军忠君爱国，断不会行此叛逆之事，只是许子高言之凿凿，又挑动多名官员一起向本王施压，本王只得虚以委蛇，暂且委屈了大将军，但是本王一直等大将军亲自向本王澄清此事，好将这帮子奸贼一起拉下马，现在有了御史的奏折，那些被奸贼蒙蔽的官员也可以清醒了，现在本王就命你前去秦长城烽火台将妄图造成君将不和，动摇军心的奸贼许子高就地正法，以儆效尤！\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));

        	break; 
	case 7:
        	if (who->get_legend(TASK_22,3) && !who->get_legend(TASK_22,4))
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"奏书",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/61012",1);	
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,4);
			who->add_exp(22000);
			who->add_potential(410);
			who->add_cash(21000);
			send_user(who,"%c%s",';',"明辨是非 经验 22000 潜能 410 金钱 21000 南瓜饼图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,41,"" );
			me->do_welcome(6);
        	}
        	break;
	case 8:
        	if ( who->get_legend(TASK_22,4) && !who->get_legend(TASK_22,5) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_22,5);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,42,"真相大白" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"真相大白");
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
        case 13:
        	if ( who->get_legend(TASK_47,29)&&!who->get_legend(TASK_47,30) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，天佑我军，天佑寡人，有天为助，有将为驱，本王夙愿，指日可待。\n"ESC"完成任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 14:
        	if( who->get_legend(TASK_47,29)&&!who->get_legend(TASK_47,30) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/final/16/1618",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_47,30);
			who->add_exp(100000);
			who->add_potential(1500);
			who->add_cash(93000);
			send_user(who,"%c%s",';',"索取神剑5 经验 100000 潜能 1500 金钱 93000 困敌索 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,88,"" );
        	}
        	break;	
	case 99:
 		EMPEROR_D->do_look( who, me); 
 		break;
        }
}

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
        set_name("Yên Vương");
	set_real_name("Yên Vương Hỉ");
        set_city_name("Yên Quốc");

        set_2( "talk", ([
                "policy"        : (: do_policy :),
                "relation"      : (: do_relation :),
                "master"        : (: do_master :),
                "advice"        : (: do_advice :),
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",93);
//        set("legend",({32*32+23}));
 	set("mpLegend",([90:({32*32+23}),]));
 	set("mpLegend2",([90:({32*32+25,}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 90 && !who->get_legend(TASK_32,23)) || (who->get_legend(TASK_32,23) && !who->get_legend(TASK_32,25)) )
	{
		tmp = sprintf(ESC HIY "格杀勿论\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( me->get_city_name() == who->get_city_name() )
	{
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			tmp += sprintf(ESC HIY "制作王之号角\ntalk %x# welcome.4\n",getoid(me));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			tmp += sprintf(ESC HIY "王之号角的雕琢\ntalk %x# welcome.4\n",getoid(me));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16)&& gone_time(who->get_save("wangzhhj"))>=86400 )
			tmp += sprintf(ESC HIY "索取王之号角\ntalk %x# welcome.4\n",getoid(me));
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
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    寡人幼女宜姬去长白山游玩居然被一群妖邪惊吓，若不是护卫将军得力方才掩护公主安全撤离，宜姬必被妖邪所伤，饶是如此，她回来也是回来呓语不止，这批胆大妄为的妖孽竟然连本王爱女都不知礼敬，差点伤她，本王必将诛杀得他们闻风丧胆！你去困魔阵中诛杀骷髅妖、骸骨精、邪灵各五只，我倒要看看，那帮子妖孽到底知不知道悔悟！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_32,23)  && !who->get_legend(TASK_32,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    怎么你竟然还放任他们逍遥法外！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_32,24)  && !who->get_legend(TASK_32,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哼，那些妖邪必会来向本王认罪！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,23)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_32,23);
        		who->delete_save("ywkulouy");
        		who->delete_save("ywhaiguj");
        		who->delete_save("ywxieling");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,48,"格杀勿论" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"格杀勿论");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_32,24) && !who->get_legend(TASK_32,25) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_32,25);
        		who->delete_save("ywkulouy");
        		who->delete_save("ywhaiguj");
        		who->delete_save("ywxieling");
			who->add_exp(64000);
			who->add_potential(906);
			who->add_cash(53800);
			send_user(who,"%c%s",';',"格杀勿论 经验 64000 潜能 906 金钱 53800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,48,"" );
        	}
        	break;
	case 4:
		if ( me->get_city_name() != who->get_city_name() )
			return;
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，宫廷里的工匠可以帮助你将普通的号角加工为王之号角，你将号角交给我，我替你咨询下工匠，看还需要做哪些准备。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠说将普通的号角雕琢成为王之号角需要花费很多珍贵的材料，他需要一些钱来购买这些材料，而单靠他一个人的力量是不可能拿出这么多钱的，我想你应该要帮助他承担一部分，他说雕琢王之号角对他来说也是一项挑战，所以他不收你一文的加工费，只需要你给他100万的材料费就够了。如果你还想雕琢王之号角的话，就将钱交给我吧，我会转交给工匠的。\n    你交钱24小时后就可以来找我索取王之号角了，我想24小时已经足够让工匠来做这件事情了。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16) && gone_time(who->get_save("wangzhhj"))>=86400 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠通宵达旦地工作，终于在你来之前将王之号角雕琢好了，你拿去看看吧。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 5:
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
	case 6:
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
	case 7:
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
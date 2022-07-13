
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
        set_name("Triệu Quốc Nội Chính Quan");
	set_real_name("Bình Nguyên Quân");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "build"         : (: do_build :),
                "upgrade"       : (: do_upgrade :),
                "plant"         : (: do_plant :),
                "food"          : (: do_food:),
                "welcome"	: (: do_welcome :),	
        ]) );
//	set("level",63);
//	set("legend",({32*19+16}));
	set("mpLegend",([60:({32*19+16}),90:({32*32+4}),105:({32*42+23})]));
	set("mpLegend2",([0:({32*42+2,32*42+9,32*43+2,}),60:({32*19+18}),]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 60 && !who->get_legend(TASK_19,16) ) || ( who->get_legend(TASK_19,16) && !who->get_legend(TASK_19,18) ) )
	{
		tmp += sprintf(ESC HIY "收集美酒\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,4) )
		tmp += sprintf(ESC HIY "送给使节的信\ntalk %x# welcome.4\n",getoid(me));
	if ( who->get_legend(TASK_42,1) && !who->get_legend(TASK_42,2) )
		tmp += sprintf(ESC HIY "询问消息\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_legend(TASK_42,2) && !who->get_legend(TASK_42,3) )
		tmp += sprintf(ESC HIY "询问战果\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_legend(TASK_42,8) && !who->get_legend(TASK_42,9) )
		tmp += sprintf(ESC HIY "搜寻战报\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_level() >= 105 && !who->get_legend(TASK_42,23) )
		tmp += sprintf(ESC HIY "探访民情\ntalk %x# welcome.10\n",getoid(me));
	if ( who->get_legend(TASK_43,1) && !who->get_legend(TASK_43,2) )
		tmp += sprintf(ESC HIY "陈述实情\ntalk %x# welcome.10\n",getoid(me));
	if ( who->get_legend(TASK_43,2) && !who->get_legend(TASK_42,28) )
		tmp += sprintf(ESC HIY "枉法之徒\ntalk %x# welcome.10\n",getoid(me));
	if ("/sys/sys/count"->get_refine()&&who->get_city_name()==me->get_city_name())
		tmp += sprintf(ESC"收妖壶任务\ntalk %x# welcome.1000\n",getoid(me)); 
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INTERIOR_D->do_look( who, me ); 
	
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
        object who,item,obj;  
        string cmd1;
           
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
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_19,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    楚王考烈王要同我国联姻，大王通令各部敬献聘礼，我闻说赵长城那些军士常常劫掠域外商人美酒，端是香醇无比，最近本官预算有点紧张，夫人还等着我扣点预算给她买胭脂水粉，实在不能去市集买，买差了又显得我办事不利，那就委托你去赵长城帮我抢5坛美酒来吧，反正大家都是抢，大哥不说二哥，嘿嘿。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_19,16) && !who->get_legend(TASK_19,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，不会吧，这点酒都抢不来，那我拿你去给夫人跪搓衣板我拿钱去市场买得了。\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_19,17) && !who->get_legend(TASK_19,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿嘿，这样子又不违反夫人意志，又给大王交了差，我真是聪明。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 2:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_19,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_19,16);
        		who->delete_save_2("zgnzgmeijiu");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,35,"赵国的美酒" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"赵国的美酒");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_19,17) && !who->get_legend(TASK_19,18) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"美酒",5) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,18);
        		who->delete_save_2("zgnzgmeijiu");
			who->add_exp(7000);
			who->add_potential(280);
			who->add_cash(7000);
			send_user(who,"%c%s",';',"赵国的美酒 经验 7000 潜能 280 金钱 7000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,35,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    上次燕国使节秦开过来我们相谈甚欢，说到各地的风情物产，他更是如数家珍，最近我家夫人突然有点想法，我想麻烦一下他，具体事项我已经写在信中，听说你最近要去燕国办事，你帮我送一趟给他好么？\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 5:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,4) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/98/0148",1);
        		who->set_legend(TASK_32,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,54,"使节的差事（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"使节的差事（1）");
        	}
        	break;
	case 6:
		if ( who->get_legend(TASK_42,1) && !who->get_legend(TASK_42,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大将军的征战已有数月，怎么还没有消息呢？\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,2) && !who->get_legend(TASK_42,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    老将军廉颇出征已有数月，然而战报迟迟未到，我王焦急不安，你前往城外问问大将军可有战报送到？\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,8) && !who->get_legend(TASK_42,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我马上给大王送去!\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 7:
		if ( who->get_legend(TASK_42,1) && !who->get_legend(TASK_42,2) )
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_42,2);
			who->add_exp(95000);
			who->add_potential(1550);
			who->add_cash(83000);
			send_user(who,"%c%s",';',"询问消息 经验 95000 潜能 1550 金钱 83000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,73,"" );
			me->do_welcome(6);
        	}
		break;	
	case 8:
		if ( who->get_legend(TASK_42,2) && !who->get_legend(TASK_42,3) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,74,"询问战果" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询问战果");
        	}
		break;
	case 9:
		if ( who->get_legend(TASK_42,8) && !who->get_legend(TASK_42,9) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"战报",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/62088",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_42,9);
			who->add_exp(92000);
			who->add_potential(1700);
			who->add_cash(85000);
			send_user(who,"%c%s",';',"搜寻战报 经验 92000 潜能 1700 金钱 85000 碎星剑图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,77,"" );
        	}
		break;
	case 10:
		if ( who->get_level() >= 105 && !who->get_legend(TASK_42,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近感觉民间似乎怨气渐大，但是我这里却收不到什么确切的报告，我怕下面官员欺上瞒下，致使政令不通，民情不达，我希望你能作为本官特使深入民间听下声音，可否？\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_43,1) && !who->get_legend(TASK_43,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，牵涉大了，本官得知会同僚再做商议。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_43,2) && !who->get_legend(TASK_42,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原来是那典狱副使蔡九私通地方官，曲解法令，对百姓实行暴政。我已经知会了典狱官和相国大人，同意对蔡九实施严惩，谁知道蔡九听到风声躲进了天门阵，现在天门阵三层南部龟缩，他自以为高枕无忧，但却想不到我们有壮士这等人物襄助，你前去将蔡九铲除，铲除之后告知本国御史。\n"ESC"接受任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 11:
		if ( who->get_level() >= 105 && !who->get_legend(TASK_42,23) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,23);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,83,"探访民情" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"探访民情");
        	}
		break;
	case 12:
		if ( who->get_legend(TASK_43,1) && !who->get_legend(TASK_43,2) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"百姓的诉苦书",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_43,2);
			who->add_exp(99000);
			who->add_potential(1800);
			who->add_cash(91000);
			send_user(who,"%c%s",';',"陈述实情 经验 99000 潜能 1800 金钱 91000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,85,"" );
			me->do_welcome(10);
        	} 
		break;
	case 13:
		if ( who->get_legend(TASK_43,2) && !who->get_legend(TASK_42,28) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,28);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,86,"枉法之徒" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"枉法之徒");
        	}
		break;
        case 99:
        	INTERIOR_D->do_look( who, me ); 
        	break;
        }
}
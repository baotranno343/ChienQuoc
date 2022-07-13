
// 自动生成：/make/npc/make8012

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_out();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 5209; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tề Quốc Thủ Vệ");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "out"           : (: do_out :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 12);
        set("out", 10);
//        set("level",82);
//        set("legend",({32*27+25}));
 	set("mpLegend",([30:({32*37+27}),80:({32*27+25})]));
 	set("mpLegend2",([80:({32*27+27}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();

	if ( (who->get_level() >= 80 && !who->get_legend(TASK_27,25)) || (who->get_legend(TASK_27,25) && !who->get_legend(TASK_27,27)))
	{
		tmp = sprintf(ESC HIY "拭目以待\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 30 && !who->get_legend(TASK_37,27) )
		tmp += sprintf(ESC HIY "种庄稼的锄头\ntalk %x# welcome.4\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look_2( who, me ); 
	
}
void do_out() { GUARDER_D->do_out( this_player(), this_object() ); }

void do_record() { GUARDER_D->do_record( this_player(), this_object() ); }

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
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    %s，我们盼星星盼月亮终于盼到了解救我们苦难的人，可把你盼到了。想当年，我祖爷爷的爷爷为了造成这个万人坑不遗余力的坑杀了多少人，杀的手都软了，我祖爷爷的奶奶每天回去都心疼得直掉眼泪，如今那些万人坑中骷髅竟然敢欺压我祖爷爷的爷爷的尸骨，我祖爷爷的爷爷经常夜里对我哭诉，说那些被他坑杀的贱民如何如何整治他，他如何如何的凄惨，听的我泪如雨下啊，你赶紧去干掉10个该死的刀盾骷髅，我们拭目以待等着你的好消息啊！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),who->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_27,25) && !who->get_legend(TASK_27,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你这样子的软脚虾怎么担当得起以后大王交付你的重任呢？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_27,26) && !who->get_legend(TASK_27,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，看这些骷髅还敢造反不！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 2:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,25) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_27,25);
        		who->delete_save("qgswdaodkl");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,24,"拭目以待" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"拭目以待");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_27,26) && !who->get_legend(TASK_27,27) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_27,27);
        		who->delete_save("qgswdaodkl");
			who->add_exp(45500);
			who->add_potential(640);
			who->add_cash(44000);
			send_user(who,"%c%s",';',"拭目以待 经验 45500 潜能 640 金钱 44000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,24,"" );
        	}
        	break; 
        case 4:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_37,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前些日子孙老头去我家，说我进城方便，所以托我给他带把种庄稼用的锄头，他说一定要挑把好用又便宜的，我那天去到市集，挑了老半天，终于选到一把不错的锄头，价格也不错，但是自己一直没有时间给他送去，我看不如这样吧，你替我把这锄头送去给孙老头，我想他现在应该在城外的园圃干活呢。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 5:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_37,27) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/98/0180",1);
        		who->set_legend(TASK_37,27);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,72,"种庄稼的锄头" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"种庄稼的锄头");
        	}
        	break;
        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;     
        }
}
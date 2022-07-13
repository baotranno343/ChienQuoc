
// 自动生成：/make/npc/make0007

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

inherit OFFICER;

// 函数：修理师傅
int is_repairer() { return 1; }
void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5407; }

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Sửa Chữa");
	set_real_name("Bước Văn");
        set_city_name("Sở Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level", 35);
//        set("legend", ({ 32*9+16 }));
 	set("mpLegend",([35:({32*9+16}),]));
 	set("mpLegend2",([35:({32*9+18}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string tmp;
	"/quest/help"->send_help_tips(who, 52);
	if ( ( who->get_level() >= 35 && !who->get_legend(TASK_09,16) ) || ( who->get_legend(TASK_09,16) && !who->get_legend(TASK_09,18) ) )
	{
		tmp = get_name() + "：\n    "+"/quest/word"->get_normal_word(me) + "\n"+
			sprintf("\n"ESC"修理和鉴定\ntalk %x# welcome.99\n",getoid(me))+
               		sprintf(ESC HIY "山道里的鬼火\ntalk %x# welcome.1\n",getoid(me)) ;	
	}
	
	if ( stringp(tmp) )
	{
		tmp += ESC"离开";
		send_user( who, "%c%s", ':',tmp);
	}	
	else	
        	REPAIR_CMD->main( who, sprintf( "%x#", getoid( me ) ) );
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
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我这里有一批已经修理好的茅山道士的装备，正要送过去茅山，本来巫山里的大王豺狗武者，我已经用钱买通。我可以顺利经过那里，谁知最近巫山不知道从哪来的一只鬼精怪，挡住了我的去路。\n    我跟豺狗武者谈过这事，它说它也拿这只妖怪没办法，眼看交货的日期就要到了。不知道你能否帮我这个忙，把那只妖怪收拾掉。它就在巫山的巫山山道，我会给你不错的报酬！  \n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,16) && !who->get_legend(TASK_09,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我下次再也不去那玩了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_09,17) && !who->get_legend(TASK_09,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你可真是为百姓做了件好事啊！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,28,"山道里的鬼火" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"山道里的鬼火");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_09,17) && !who->get_legend(TASK_09,18) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),30,ARMOR_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_09,18);
			who->add_exp(2800);
			who->add_potential(110);
			who->add_cash(2000);
			send_user(who,"%c%s",';',sprintf("山道里的鬼火 经验 2800 潜能 110 金钱 2000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,28,"" );
        	}
        	break;   
 	case 99:
 		REPAIR_CMD->main( who, sprintf( "%x#", getoid( me ) ) );
 		break;
        }
}
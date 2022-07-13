
// 自动生成：/make/npc/make0007

#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

// 函数：修理师傅
int is_repairer() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5407; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Sửa Chữa");
	set_real_name("Thạch Thân");
        set_city_name("Ngụy Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level", 21);
//        set("legend", ({ 32*5+13 }));  
 	set("mpLegend",([20:({32*5+13}),]));
 	set("mpLegend2",([20:({32*5+15}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();	
	"/quest/help"->send_help_tips(who, 52);
	if ( ( who->get_level() >= 20 && !who->get_legend(TASK_05,13) ) || ( who->get_legend(TASK_05,13) && !who->get_legend(TASK_05,15) ) )
	{
		tmp = sprintf(ESC HIY "神秘的传说\ntalk %x# welcome.1\n",getoid(me));
	}

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_normal_word(me) + "\n"ESC"修理和鉴定\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		REPAIR_CMD->main( who, sprintf( "%x#", getoid( this_object() ) ) );
	
}
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
	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >=20 && !who->get_legend(TASK_05, 13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近传得沸沸扬扬的是什么，你知道吗？是一个灵桃从天而降！据说那灵桃还有治百病的功效，我家夫人一直身体状况欠佳，我想如果能找到那只灵桃，一定会使她的病有所起色。\n    你问我为什么自己不去找？你以为灵桃任何人都能找到吗？前些日子有个云游和尚告诉我，必须要一个叫%s的人才是这只灵桃的有缘人，我等了好久，终于等到你来，希望你能帮我这个忙。\n    据我打探到的消息，那只灵桃似乎落在了巨鹿的飞虎寨，你进入飞虎寨后直接往前走，看到那个装满水的大水缸后，我估计你就差不多要找到灵桃了。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),who->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_05,13) && !who->get_legend(TASK_05,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道那个灵桃的故事是别人糊弄我的吗？要是这样那就算了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_05,14) && !who->get_legend(TASK_05,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……还真有这回事啊！那太谢谢你了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,13)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,12,"神秘的传说" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"神秘的传说");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_05,14) && !who->get_legend(TASK_05,15) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),0,20,BOOTS_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"灵桃",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_05,15);
			who->add_exp(1300);
			who->add_potential(70);
			who->add_cash(1000);
			send_user(who,"%c%s",';',sprintf("神秘的传说 经验 1300 潜能 70 金钱 1000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,12,"" );
        	}
        	break;
        case 99:
        	REPAIR_CMD->main( who, sprintf( "%x#", getoid( me ) ) );
        	break;
        }
}
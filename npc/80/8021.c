
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5301; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Triệu Tổng Quản");
        set_city_name("Triệu Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
	set("mpLegend2",([0:({32*18+29,32*41+19,32*41+22,}),80:({32*38+14,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who ) 
{
	object me = this_object();
	string tmp="";
	
	if ("/sys/task/master"->do_look_quest10(who, me)>0) return;
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( who->get_legend(TASK_18,28) && !who->get_legend(TASK_18,29) )
	{
		tmp += sprintf(ESC HIY "贺礼\ntalk %x# welcome.1\n",getoid(me));
	}		
	if ( who->get_level() >= 80 && who->get_legend(TASK_38,13) && !who->get_legend(TASK_38,14) )
	{
		tmp += sprintf(ESC HIY "身世之谜\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( who->get_legend(TASK_41,18) && !who->get_legend(TASK_41,19) )
	{
		tmp += sprintf(ESC HIY "打探下落\ntalk %x# welcome.5\n",getoid(me));
	}
	if ( who->get_legend(TASK_41,19) && !who->get_legend(TASK_41,22) )
	{
		tmp += sprintf(ESC HIY "试探实力\ntalk %x# welcome.5\n",getoid(me));
	}
	if ( who->get_legend(TASK_41,22) && !who->get_legend(TASK_41,23) )
	{
		tmp += sprintf(ESC HIY "天门探险\ntalk %x# welcome.5\n",getoid(me));
	}
	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
			+ tmp +
			ESC"离开"
			);

}


int accept_money(object who, int gold)
{
	return "/sys/task/master"->accept_money(this_object(), who, gold);
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
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_18,28) && !who->get_legend(TASK_18,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿嘿，我代表我的老父和小弟多谢秦管家的祝福了。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_legend(TASK_18,28) && !who->get_legend(TASK_18,29) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"贺礼",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_18,29);
			who->add_exp(6800);
			who->add_potential(265);
			who->add_cash(6500);
			send_user(who,"%c%s",';',"贺礼 经验 6800 潜能 265 金钱 6500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,9,"" );

       		}
        	break;
        case 3:
        	if ( who->get_level() >= 80 && who->get_legend(TASK_38,13) && !who->get_legend(TASK_38,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    他还是找到了……\n    我隐瞒了这么久的秘密，还是被他发现了，唉。他是我的私生子，我会抽空去找他的，谢谢你了。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 4:
        	if ( who->get_level() >= 80 && who->get_legend(TASK_38,13) && !who->get_legend(TASK_38,14) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_38,14);
			who->add_exp(30000);
			who->add_potential(400);
			who->add_cash(22000);
			send_user(who,"%c%s",';',"身世之谜 经验 30000 潜能 400 金钱 22000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,50,"" );

       		}
        	break;
	case 5:
		if ( who->get_legend(TASK_41,18) && !who->get_legend(TASK_41,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大将军终于找到可以托付寻书的人了么，好，我一定把情形细细告诉你。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_41,19) && !who->get_legend(TASK_41,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天门阵法处于天门阵的层层守护之中，你先要破去阵图中的六劫煞，否则你还未碰到书就会离奇暴亡，幸亏我Quốc细作潜入天门阵多年终于探得了六劫煞之名及其关键，可叹之前已有多个壮士无谓身死，六劫煞破除必须得是内力精纯、心底毫无旁骛之人，按照六劫煞的六劫方位逐一杀掉30个守阵天兵和30个守阵神将，你破除了六劫煞之后来告知我，我再教你如何做。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_41,20) && !who->get_legend(TASK_41,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    怎么？你没有按照我的吩咐去破除六劫煞么？那你可不能去取阵法书，我可不想你达不成任务又白白送了性命！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_41,21) && !who->get_legend(TASK_41,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢天谢地，六劫煞终于破除了！你可仔细听好了，我告诉你怎么去取天门阵法，也容不得半点差错。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_41,22) && !who->get_legend(TASK_41,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天门阵法放置在一个加了符咒的箱子中，你必须秘念临、兵、斗、者、皆、阵、列、在、前五遍方可开启箱子，否则符咒内有小元阵法的机关就会突降小元雷煞将你顷刻间化为飞灰，切记切记！箱子在天门阵二层的西北处，你可细细寻找，牢记我的嘱咐！\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));

		break;
        case 6:
		if ( who->get_legend(TASK_41,18) && !who->get_legend(TASK_41,19) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_41,19);
			who->add_exp(91000);
			who->add_potential(1600);
			who->add_cash(83000);
			send_user(who,"%c%s",';',"打探下落 经验 91000 潜能 1600 金钱 83000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,69,"" );
			me->do_welcome(5);
        	} 
        	break;
	case 7:
       		if ( who->get_legend(TASK_41,19) && !who->get_legend(TASK_41,20) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_41,20);
        		who->delete_save("zzgshouztb");
        		who->delete_save("zzgshouzsj");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,70,"试探实力" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"试探实力");
        	}
        	break;        	
        case 8:
		if ( who->get_legend(TASK_41,21) && !who->get_legend(TASK_41,22) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_41,22);
        		who->delete_save("zzgshouztb");
        		who->delete_save("zzgshouzsj");
			who->add_exp(92000);
			who->add_potential(1400);
			who->add_cash(82000);
			send_user(who,"%c%s",';',"试探实力 经验 92000 潜能 1400 金钱 82000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,70,"" );
			me->do_welcome(5);
        	} 
        	break;
	case 9:
       		if ( who->get_legend(TASK_41,22) && !who->get_legend(TASK_41,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_41,23);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,71,"天门探险" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"天门探险");
        	}
        	break;  
        }
}
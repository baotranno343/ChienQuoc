
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_welcome(string arg);

//void do_task_finish();
int get_char_picid() { return 0251; }
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
// 函数：构造处理
void create()
{
        set_name("Tiễn Lão Cửu");
        set_city_name("Sở Quốc");

	set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//	set("level",11);
//	set("legend",({32*3+1,}));
	set("mpLegend",([10:({32*3+1}),]));
	set("mpLegend2",([10:({32*3+2,32*49+12}),]));
        setup();
}

// 函数：对话处理
void do_look( object who ) 
{
	string tmp="";
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, this_object() ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, this_object() ); 
		return ;
	}        

        tmp += CHAIN_D->get_chain_menu(who,this_object());
	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,2) )
		tmp += sprintf(ESC HIY "取回货物\ntalk %x# welcome.1\n",getoid(this_object()));
//	if( who->get_level() >= 10 && who->get_legend(TASK_37,13) && !who->get_legend(TASK_37,14) )
	if( who->get_legend(TASK_49, 11) && !who->get_legend(TASK_49, 12) && who->get_fam_name() != "")
		tmp += sprintf(ESC HIY "与门派向导的恩怨\ntalk %x# welcome.4\n",getoid(this_object()));

	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
			+ tmp +
			ESC"离开"
			);

}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag, date , status, p, z, x, y, i;
        object who, obj, item;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,1) )
        		send_user(who,"%c%s",':',sprintf("%s:\n    嘻嘻……这位小兄看来是一副囊中羞涩的样子……要不要大哥我帮你这个忙？ \n    五天前我负责托运一批货物，通过楚方城的时候却被那群贪得无厌的守卫扣押了！碍于我们与官府的关系，也不好亲自出面讨回。但是如果你能帮大哥这个忙，将这批货物“取”回来，多少银子我都会付你的。\n    怎样？干不干？楚方城的入口就在十里林以西，从郢城出发半时辰的路程就到了。我相信那匹货物还扣押在楚方城上。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
        	else if( objectp( present("钱老九的货物", who, 1, MAX_CARRY) ) )
        		send_user(who,"%c%s",':',sprintf("%s:\n    哈哈！不错不错！没想到这么轻易就到手了！！这是你的酬劳，拿好吧！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),getoid(me)));
		else
        		send_user(who,"%c%s",':',sprintf("%s:\n    货物呢？找到了吗？绝对就在楚方城上！给我好好的找啊！！\n"ESC"离开",me->get_name()));
        	break;
        case 2:
        	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,1) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,1,"取回货物" );	
        		who->set_legend(TASK_NEWBIE_03,1);
        		send_user( who, "%c%s", '!', "得到任务 "HIY"取回货物");
        	}
        	break;
        case 3:
        	if( !who->get_legend(TASK_NEWBIE_03,2) && objectp( item=present("钱老九的货物", who, 1, MAX_CARRY) ) )
        	{
        		item->remove_from_user();
        		destruct(item);
        		TASK_LEGEND_D->give_item(who,"/item/91/9100",3);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03, 2);
			who->add_exp(300);
			who->add_potential(30);
			who->add_cash(5000);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,1,"" );	        			
			send_user(who,"%c%s",';',"取回货物 经验 300 潜能 30 金钱 5000 行军散 3");
        	}
        	break;
        case 4:
//        	if( who->get_level() >= 10 && who->get_legend(TASK_37,13) && !who->get_legend(TASK_37,14) )
		if( who->get_legend(TASK_49, 11) && !who->get_legend(TASK_49, 12) && who->get_fam_name() != "")
        		send_user(who,"%c%s",':',sprintf("%s:\n    我们之间的问题是该解决了，谢谢你送来这封挑战书，我接下了！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),getoid(me)));
        	break;  
        case 5:
//        	if ( who->get_level() >= 10 && who->get_legend(TASK_37,13) && !who->get_legend(TASK_37,14) )
		if( who->get_legend(TASK_49, 11) && !who->get_legend(TASK_49, 12) && who->get_fam_name() != "")
		{
        		if (TASK_LEGEND_D->check_task_item(who,"挑战书",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"/item/32/3282",3); 
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_49,12);
			who->add_exp(300);
			who->add_potential(35);
			who->add_cash(1000);
			send_user(who,"%c%s",';',"门派向导的恩怨 经验 300 潜能 35 金钱 1000 桔子 3");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,118,"" );
        	}
        	break;    
        }
}


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
int get_char_picid() { return 0201; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chu Cuồng");
        set_city_name("Ngụy Quốc");


	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",23);
//	set("legend",({32*5+28}));
	set("mpLegend",([20:({32*5+28}),25:({32*7+10})]));
	set("mpLegend2",([20:({32*5+30}),25:({32*7+12})]));
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
	if ( ( who->get_level() >= 20 && !who->get_legend(TASK_05,28) ) || ( who->get_legend(TASK_05,28) && !who->get_legend(TASK_05,30) ) )
		tmp += sprintf(ESC HIY "传闻的宝藏\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( ( who->get_level() >= 25 && !who->get_legend(TASK_07,10) ) || ( who->get_legend(TASK_07,10) && !who->get_legend(TASK_07,12) ) )
		tmp += sprintf(ESC HIY "梦的困扰\ntalk %x# welcome.4\n",getoid(this_object()));

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
        int flag,p;
        object who,item,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,28)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    宝藏……哈哈，宝藏！\n    你说这个世界上真的有宝藏吗？我听说在一个很隐蔽的山洞里埋藏着大量的宝藏，但是要找到这批宝藏必须先找到一张青纹宝图，有了这张宝图才能找到那个山洞的确切位置，找到这张宝图才能证明这个埋藏宝藏的山洞真正存在！\n    据说这张宝图曾在白马庄的紫竹小居出现过，就在离桥边不远的地方，你仔细看看，或许埋在某块藏图石下。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_05,28) && !who->get_legend(TASK_05,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道我听错了吗？让我好好想想，应该不会错啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_05,29) && !who->get_legend(TASK_05,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这可真是太好了，这下我发大财了！哈哈……\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,28)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,28);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,18,"传闻的宝藏" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"传闻的宝藏");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_05,29) && !who->get_legend(TASK_05,30) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"青纹宝图",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64007",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_05,30);
			who->add_exp(1300);
			who->add_potential(60);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"传闻的宝藏 经验 1300 潜能 60 金钱 1200 古藤袍图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,18,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_07,10)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    梦魇……恶魔……\n    秀丽小姐前日做了个噩梦，她梦见7只褐尾蝎从她的耳、口、眼、鼻七窍钻进身体，当时她就被吓醒了，她觉得这似乎预兆着什么，这些日子来她一直寡寡欲欢，茶不思，饭不香，眼看人消瘦了不少，大夫说她身体上根本就没病，可能是精神上受到了惊吓，为了消灭秀丽小姐的心魔，我想过了很多办法，可都无济于事，现在只剩下唯一的一个办法了，可尽管我重金悬赏，很多人都不愿意去做这件事！他们都不愿意去沼泽那鬼地方。\n    你去沼泽杀7只褐尾蝎吧，然后通知我一声，我看秀丽小姐能不能好点。办好这件事，我不会亏待你的！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_07,10) && !who->get_legend(TASK_07,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果不能杀死那7只褐尾蝎，秀丽小姐的心里的这个结难解啦！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_07,11) && !who->get_legend(TASK_07,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    也不知道这个方法有没有效，不过还是谢谢你！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 5:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_07,10)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,10);
        		who->delete_save_2("heweixie");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,7,"梦的困扰" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"梦的困扰");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_07,11) && !who->get_legend(TASK_07,12) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,12);
			who->delete_save_2("heweixie");
			who->add_exp(2800);
			who->add_potential(90);
			who->add_cash(2000);
			send_user(who,"%c%s",';',"梦的困扰 经验 2800 潜能 90 金钱 2000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,7,"" );
        	}
        	break;     
        }
}
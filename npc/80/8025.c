
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
int get_char_picid() { return 7301; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Lí Tam Thẩm");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",23);
//	set("legend",({32*6+1}));
	set("mpLegend",([20:({32*37+21,32*6+1}),25:({32*6+28})]));
	set("mpLegend2",([20:({32*6+3,}),25:({32*6+30,}),]));
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
	if ( ( who->get_level() >= 20 && !who->get_legend(TASK_06,1) ) || ( who->get_legend(TASK_06,1) && !who->get_legend(TASK_06,3) ) )
		tmp += sprintf(ESC HIY "哭泣的冤魂\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( ( who->get_level() >= 25 && !who->get_legend(TASK_06,28) ) || ( who->get_legend(TASK_06,28) && !who->get_legend(TASK_06,30) ) )
		tmp += sprintf(ESC HIY "偷鸡贼\ntalk %x# welcome.4\n",getoid(this_object()));
	if ( who->get_level() >= 20 && !who->get_legend(TASK_37,21) )
		tmp += sprintf(ESC HIY "家庭聚会\ntalk %x# welcome.7\n",getoid(this_object()));

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
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_06,1)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你听到呜呜呜……的声音没有？越来越近了，听到没？唉，都好几天了，一直在不停地哭泣，真是哭得我心酸啊。\n    她说她生前是一个平凡人家的闺女，不知怎么就被恶匪钱三疤看上了，硬要她做小妾，那恶匪钱三疤无恶不作，是当地的地头蛇，她当然不从，可那恶匪钱三疤逼死了她的父母亲，要她就范，她抵死不从，就悬梁自尽了，好一个贞洁烈女啊！\n    她希望我能找人替她报仇，不知你可愿意帮她，那钱三疤就在萁关的青邱泽一带活动，你可以从周Quốc直接到萁关。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,1) && !who->get_legend(TASK_06,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来那恶匪钱三疤是不好惹，哎！只能怪那冤魂命苦了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,2) && !who->get_legend(TASK_06,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下那冤魂可以安心的投胎做人了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_06,1)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,19,"哭泣的冤魂" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"哭泣的冤魂");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_06,2) && !who->get_legend(TASK_06,3) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,3);
			who->add_exp(1400);
			who->add_potential(60);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"哭泣的冤魂 经验 1400 潜能 60 金钱 1200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,19,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,28)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    家里又要添置东西了，很多家具也得翻翻新了，我辛辛苦苦养了一群鸡，准备拿鸡蛋卖点钱，可就这群鸡还被贼惦记着了，今天一只明天两只的给我偷光了，真是气坏了我！这群贼，不教训教训他，我想他们会更加为非作歹。\n    据我观察发现那群偷鸡贼其实是一群草寇，他们不止是偷鸡，他们无恶不作，罪该万死！你去替我教训他们吧，他们一伙是20个人，就在平原一带流窜作案。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,28) && !who->get_legend(TASK_06,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    昨天隔壁赵婶家的鸡又被偷了！你可得尽快办好此事啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,29) && !who->get_legend(TASK_06,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太感谢你了！现在不止是我放心了，这附近的老百姓可都放心了，你是我们心目中的大英雄啊！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 5:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,28)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,28);
        		who->delete_save_2("toujizei");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,3,"偷鸡贼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"偷鸡贼");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_06,29) && !who->get_legend(TASK_06,30) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,30);
			who->delete_save_2("toujizei");
			who->add_exp(2500);
			who->add_potential(50);
			who->add_cash(1000);
			send_user(who,"%c%s",';',"偷鸡贼 经验 2500 潜能 50 金钱 1000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,3,"" );
        	}
        	break;        	
        case 7:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_37,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    城外临河镇的李德是我家侄儿，他已经很久没来过我家了，我们一大家子人也很久没有一起吃顿饭了，今天我想叫住得不远的亲戚们都来我家吃顿晚饭，但我自己要忙着做饭，没办法去请他们，还望你能帮我这个忙，去趟临河镇，将这个口信带给李德。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 8:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_37,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_37,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,65,"家庭聚会" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"家庭聚会");
        	}
        	break;
        }
}
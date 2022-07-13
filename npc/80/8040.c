
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_welcome(string arg);

//void do_task_finish();
int get_char_picid() { return 5601; }
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
// 函数：构造处理
void create()
{
        set_name("Lưu Đầu");
        set_city_name("Sở Quốc");

	set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//	set("level",12);
//	set("legend",({32*3+7,32*3+9}));
	set("mpLegend",([10:({32*3+7}),]));
	set("mpLegend2",([0:({32*32+30,32*33+3,}),10:({32*3+8,32*3+10,}),]));	
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
	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,10) )
		tmp += sprintf(ESC HIY "打造惊世之剑\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( who->get_legend(TASK_32,29) && !who->get_legend(TASK_32,30) )
		tmp += sprintf(ESC HIY "询问遗产\ntalk %x# welcome.6\n",getoid(this_object()));
	if ( (who->get_legend(TASK_32,30) && !who->get_legend(TASK_33,1)) || (who->get_legend(TASK_33,1) && !who->get_legend(TASK_33,3)) )
		tmp += sprintf(ESC HIY "杀人凶手\ntalk %x# welcome.6\n",getoid(this_object()));
	if ( who->get_legend(TASK_33,3) && !who->get_legend(TASK_33,4) )
		tmp += sprintf(ESC HIY "遗产的秘密\ntalk %x# welcome.6\n",getoid(this_object()));

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
        int flag, date , status, p, z, x, y, i,amount,size;
        object who, obj, item,*inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,7) )
        		send_user(who,"%c%s",':',sprintf("%s:\n    打造出像“干将莫邪”一样的神兵利刃一直是我多年以来的梦想。近来想自己打造一柄好剑的念头越来越强烈，然而要打造一把惊世神兵，天时，地利，人合缺一不可。\n    现在我十分需要一些"HIR"铸剑石"NOR"来实现这个心愿。我相信在"HIR"华山或者朝阳峰"NOR"一带应该都可以采集到这些矿石。可以的话你帮我收集3块铸剑，我会支付相应报酬的！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
        	else if( who->get_legend(TASK_NEWBIE_03,7) && !who->get_legend(TASK_NEWBIE_03,8) &&who->get_save_2("xuantieshi") >= 3 )
        		send_user(who,"%c%s",':',sprintf("%s:\n    没错没错！就是这种铸剑石！唔……看来石质的纯度相当高，打造一把好剑绝对没有问题……接下来还有准备些什么呢……对了对了……应该还要点……\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),getoid(me)));
        	else if( who->get_legend(TASK_NEWBIE_03,7) && !who->get_legend(TASK_NEWBIE_03,8) &&who->get_save_2("xuantieshi") < 3 )
        		send_user(who,"%c%s",':',sprintf("%s:\n    三块铸剑石……怎么？拿来了吗？\n"ESC"离开",me->get_name()));
        	else if( who->get_legend(TASK_NEWBIE_03,8)  && !who->get_legend(TASK_NEWBIE_03,9) )
			send_user(who,"%c%s",':',sprintf("%s:\n    铸剑石是有了，不过要铸出一把绝世好剑还是欠缺点什么……你听过关于“干将莫邪”这两把绝世名剑来历的传说吗？\n    莫邪为了帮助丈夫铸剑，甘愿自己跳入铸剑炉中，以自己的鲜血熔化了五山六合之金。最后干将终于铸造出了“干将”与“莫邪”两把天下名剑。不过传说终归是传说，我可不会真的去用人血来铸剑。但是要铸一把好剑，新鲜的血液还是必要的。以我多年的经验，相信用狗的血液也可以取代人血的功用。\n    在华山和朝阳峰一带的斑点狗非常多，如果你方便的话，就帮我这个忙，杀一只斑点狗回来吧！\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),getoid(me)));
        	else if( who->get_legend(TASK_NEWBIE_03,9)  && !who->get_legend(TASK_NEWBIE_03,10) && who->get_save_2("bandiangou") )
			send_user(who,"%c%s",':',sprintf("%s:\n    不错不错！用这只斑点狗的血液铸剑了是最适合不过的了！……接下来还有准备些什么呢……对了对了……必须随时留意炉火的温度……\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),getoid(me)));
        	else if( who->get_legend(TASK_NEWBIE_03,9)  && !who->get_legend(TASK_NEWBIE_03,10) && !who->get_save_2("bandiangou") )
			send_user(who,"%c%s",':',sprintf("%s:\n    怎么会？难道华山的斑点狗都被人杀光了吗？那朝阳峰上也没有了吗？\n"ESC"离开",me->get_name()));
        	break;
        case 2:
        	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->delete_save_2("xuantieshi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,4,"打造惊世之剑" );	
        		who->set_legend(TASK_NEWBIE_03,7);
        		send_user( who, "%c%s", '!', "得到任务 "HIY"打造惊世之剑");
        	}
        	break;
        case 3:
        	if( !who->get_legend(TASK_NEWBIE_03,8) && who->get_save_2("xuantieshi") >= 3  )
        	{
			if( !objectp( item = present("铸剑石", who, 1, MAX_CARRY) ) || item->is_xuantieshi() != 1 )
			{
				send_user(who,"%c%s",'!',"你的铸剑石呢?");
				return;	
			}			
			inv = all_inventory(who, 1, MAX_CARRY);
			for(i=0,size=sizeof(inv);i<size;i++)
			{
				if ( !objectp(inv[i]) || inv[i]->is_xuantieshi() != 1 )
					continue;
				amount += inv[i]->get_amount();		
			}
			if ( amount < 3 )
			{
				send_user(who,"%c%s",'!',"数量不够吧?");
				return;	
			}
			for(i=0,size=sizeof(inv);i<size;i++)
			{
				if ( !objectp(inv[i]) )
					continue;
				if ( inv[i]->get_name() != "铸剑石" || inv[i]->is_xuantieshi() != 1 )
					continue;
				inv[i]->remove_from_user();
				destruct(inv[i]);
			}
        		TASK_LEGEND_D->give_item(who,"item/final/33/1700",3);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03, 8);
			who->delete_save_2("xuantieshi");
			who->add_exp(500);
			who->add_potential(50);
			who->add_cash(1300);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,4,"" );	        			
			send_user(who,"%c%s",';',"打造惊世之剑 经验 500 潜能 50 金钱 1300 一口肉 3");
			me->do_welcome(1);
        	}
        	break;
        case 4:
        	if( who->get_legend(TASK_NEWBIE_03,8)  && !who->get_legend(TASK_NEWBIE_03,9) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,5,"斑点狗的血液" );	
        		who->set_legend(TASK_NEWBIE_03,9);
        		send_user( who, "%c%s", '!', "得到任务 "HIY"斑点狗的血液");
        	}
        	break;
        case 5:
        	if( !who->get_legend(TASK_NEWBIE_03,10) && who->get_save_2("bandiangou") >= 1  )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03, 10);
			who->delete_save_2("bandiangou");
			who->add_exp(550);
			who->add_potential(55);
			who->add_cash(1300);
			send_user(who,"%c%s",';',"斑点狗的血液 经验 550 潜能 55 金钱 1300");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,5,"" );	        			
        	}
        	break;     
        case 6:
        	if ( who->get_legend(TASK_32,29) && !who->get_legend(TASK_32,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，%s，我曾经是丁鹤年祖父的忘年交，他曾经嘱托过我，如果有人拿着这张虎皮遗书来找我，首先要叫他去完成一件极为重要的事情，当然这件事情要等到你愿意的时候，我才会告诉你。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),who->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_32,30) && !who->get_legend(TASK_33,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    丁鹤年的祖父曾经嘱托过我，如果有人拿着这张虎皮遗书来找我，首先要叫他去虚陵洞杀掉害死他的金精与木精，如果能替他报仇雪恨，那么我才能将遗产的秘密告诉他。他说能拿到虎皮遗书的人只会是他孙子或者他孙子的朋友，所以我可以放心的将这件事情交给你去做。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_33,1) && !who->get_legend(TASK_33,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    若你不能替他报仇，那么对你来说，这个秘密就永远只能是秘密了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_33,2) && !who->get_legend(TASK_33,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，你替他报了仇，那么你将得到这个遗产的秘密。\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_33,3) && !who->get_legend(TASK_33,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    关于这个遗产，其实我知道得也不多，丁鹤年的祖父曾经告诉我，他将一个宝箱放在华山一带，首先你要穿过虚陵洞，当你来到一个叫小山道的地方时，你离这个宝箱已经不远了，在快到另一个入口的地方有一大片空地，看到地上那个破罐子了吗？不要小瞧它，或许它底下就埋着宝箱。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));

        	break;         
        case 7:
        	if ( who->get_legend(TASK_32,29) && !who->get_legend(TASK_32,30) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"虎皮遗书",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_32,30);
			who->add_exp(31000);
			who->add_potential(605);
			who->add_cash(30000);
			send_user(who,"%c%s",';',"祖父的遗产（2） 经验 31000 潜能 605 金钱 30000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,32,"" );
			me->do_welcome(6);
        	}
        	break;
        case 8:
        	if( who->get_legend(TASK_32,30) && !who->get_legend(TASK_33,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,33,"祖父的遗产（3）" );	
        		who->set_legend(TASK_33,1);
        		who->delete_save("ltjinj");
        		who->delete_save("ltmuj");
        		send_user( who, "%c%s", '!', "得到任务 "HIY"祖父的遗产（3）");
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_33,2) && !who->get_legend(TASK_33,3) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,3);
        		who->delete_save("ltjinj");
        		who->delete_save("ltmuj");
			who->add_exp(37000);
			who->add_potential(633);
			who->add_cash(33500);
			send_user(who,"%c%s",';',"祖父的遗产（3） 经验 37000 潜能 633 金钱 33500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,33,"" );
			me->do_welcome(6);
        	}
        	break;
        case 10:
        	if( who->get_legend(TASK_33,3) && !who->get_legend(TASK_33,4) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,34,"祖父的遗产（4）" );	
        		who->set_legend(TASK_33,4);
        		send_user( who, "%c%s", '!', "得到任务 "HIY"祖父的遗产（4）");
        	}
        	break;
        }
}
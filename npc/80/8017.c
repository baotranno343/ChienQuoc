
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 0451; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Vương Thiết Tượng");
        set_city_name("Triệu Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
//        set("level",58);
//        set("legend",({32*17+16}));
	set("mpLegend",([55:({32*17+16,32*17+19,32*17+22}),105:({32*41+16})]));
	set("mpLegend2",([55:({32*17+18,32*17+21,32*17+24,}),0:({32*11+15,32*11+18,32*11+21,32*28+11,})]));
        setup();
}

void do_look( object who )
{
	object me = this_object();
	string tmp="";
	
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
	if ( who->get_legend(TASK_11,14) && !who->get_legend(TASK_11,15) )
		tmp += sprintf(ESC HIY "燕苍天的求助\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_legend(TASK_11,15) && !who->get_legend(TASK_11,16)) || (who->get_legend(TASK_11,16) && !who->get_legend(TASK_11,18)) )
		tmp += sprintf(ESC HIY "收集石炭\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_legend(TASK_11,18) && !who->get_legend(TASK_11,19)) || (who->get_legend(TASK_11,19) && !who->get_legend(TASK_11,21)) )
		tmp += sprintf(ESC HIY "教训恶人\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_legend(TASK_11,21) && !who->get_legend(TASK_11,22)) || (who->get_legend(TASK_11,22) && !who->get_legend(TASK_11,23)) )
		tmp += sprintf(ESC HIY "解决问题\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_level() >=55 && !who->get_legend(TASK_17,16)) || (who->get_legend(TASK_17,16) && !who->get_legend(TASK_17,18)) )
		tmp += sprintf(ESC HIY "孤魂怨叹\ntalk %x# welcome.8\n",getoid(me));
	if ( (who->get_level() >=55 && !who->get_legend(TASK_17,19)) || (who->get_legend(TASK_17,19) && !who->get_legend(TASK_17,21)) )
		tmp += sprintf(ESC HIY "长城奇遇\ntalk %x# welcome.11\n",getoid(me));
	if ( (who->get_level() >=55 && !who->get_legend(TASK_17,22)) || (who->get_legend(TASK_17,22) && !who->get_legend(TASK_17,24)) )
		tmp += sprintf(ESC HIY "神秘的荧光\ntalk %x# welcome.14\n",getoid(me));
	if ( who->get_legend(TASK_28,10) && !who->get_legend(TASK_28,11) )
		tmp += sprintf(ESC HIY "开启木箱的钥匙\ntalk %x# welcome.17\n",getoid(me));
	if ( who->get_legend(TASK_28,11) && !who->get_legend(TASK_28,12) )
		tmp += sprintf(ESC HIY "打造钥匙\ntalk %x# welcome.17\n",getoid(me));
	if ( who->get_level() >= 105 && !who->get_legend(TASK_41,16) )
		tmp += sprintf(ESC HIY "询问原由\ntalk %x# welcome.20\n",getoid(me));
			
	send_user(who,"%c%s",':',sprintf( "%s：\n    周Quốc的京都镖局尉迟老镖头武艺高强，生性豪爽，真是一条好汉！\n", get_name(),  ) 
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
        	if ( who->get_legend(TASK_11,14) && !who->get_legend(TASK_11,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，他这事还有点棘手，这样吧，你先去帮我办件事，我再想想办法，看有没有万无一失之策。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_11,15) && !who->get_legend(TASK_11,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    燕苍天这事还有点棘手，你去给我收集10个石炭来，再容我慢慢想办法。实在不知道去哪找的话，就去白云峰吧。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_11,16) && !who->get_legend(TASK_11,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    暂时我还没想到办法，你去继续收集石炭吧！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_11,17) && !who->get_legend(TASK_11,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这些石炭，可能会有点帮助，可经常捣乱的那个恶人怎么办呢！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_11,18) && !who->get_legend(TASK_11,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这些石炭，可能会有点帮助，可有个恶人经常来我铺子里捣乱，你去给我教训教训他，他就在牧场的最东边！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_11,19) && !who->get_legend(TASK_11,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我暂时还没想出更好的办法，你先去教训那恶人武藏了再来找我吧！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_11,20) && !who->get_legend(TASK_11,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    等等你来找我拿信吧，我把解决问题的方法写在了信上，希望能帮上燕苍天。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_11,21) && !who->get_legend(TASK_11,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你把这封信交给燕苍天吧，唉，也不知道能不能起到作用！\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_11,22) && !who->get_legend(TASK_11,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你可别耽误了燕苍天，他现在急着呢！\n"ESC"离开", me->get_name()));
        	break;
        case 2:
        	if( who->get_legend(TASK_11,14) && !who->get_legend(TASK_11,15) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,15);
			who->add_exp(4400);
			who->add_potential(140);
			who->add_cash(3800);
			send_user(who,"%c%s",';',"无奈的求助（1） 经验 4400 潜能 140 金钱 3800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,17,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if( who->get_legend(TASK_11,15) && !who->get_legend(TASK_11,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_11,16);
        		who->delete_save_2("wtjshitan");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,1,"无奈的求助（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"无奈的求助（2）");
        	}
        	break;
        case 4:
        	if( who->get_legend(TASK_11,17) && !who->get_legend(TASK_11,18) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"石炭",10) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64037",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,18);
        		who->delete_save_2("wtjshitan");
			who->add_exp(6000);
			who->add_potential(190);
			who->add_cash(4500);
			send_user(who,"%c%s",';',"无奈的求助（2） 经验 6000 潜能 190 金钱 4500 青龙冠图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,1,"" );
			me->do_welcome(1);
        	}
        	break;
        case 5:
        	if( who->get_legend(TASK_11,18) && !who->get_legend(TASK_11,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_11,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,2,"无奈的求助（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"无奈的求助（3）");
        	}
        	break;
        case 6:
        	if( who->get_legend(TASK_11,20) && !who->get_legend(TASK_11,21) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64034",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,21);
			who->add_exp(6000);
			who->add_potential(190);
			who->add_cash(4500);
			send_user(who,"%c%s",';',"无奈的求助（3） 经验 6000 潜能 190 金钱 4500 狂战盔图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,2,"" );
			me->do_welcome(1);
        	}
        	break;
        case 7:
        	if( who->get_legend(TASK_11,21) && !who->get_legend(TASK_11,22) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			item = new("item/98/0047");
			if ( !item  )
				return ;
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				send_user( who, "%c%s", '!', "你身上的东西太多了");
				return;
			}
			item->add_to_user(p);
        		who->set_legend(TASK_11,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,3,"无奈的求助（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"无奈的求助（4）");
        	}
        	break;
        case 8:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_17,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    晚上刚睡下，就看到床前站了一个人，他说他是一个游魂野鬼，叫我不要怕，他只是想找个人替他报仇！\n    他说仅仅因为区区二两银子，恶霸齐小六就害死了他，他死不瞑目，他一定要报此深仇大恨，无奈阴阳殊途，只得找人来帮他报仇雪恨！\n    我觉得你是最适合来做这事的，因为你不认识齐小六，与他无怨无仇，就算杀了他，也没人会认为是你干的，去吧，就在燕长城的匝道上。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_17,16) && !who->get_legend(TASK_17,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我只有去报官才能解决这个问题。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_17,17) && !who->get_legend(TASK_17,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下那个孤魂可以安息了！\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 9:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_17,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_17,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,25,"孤魂怨叹" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"孤魂怨叹");
        	}
        	break;
        case 10:
        	if ( who->get_legend(TASK_17,17) && !who->get_legend(TASK_17,18) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_17,18);
			who->add_exp(6700);
			who->add_potential(250);
			who->add_cash(6400);
			send_user(who,"%c%s",';',"孤魂怨叹 经验 6700 潜能 250 金钱 6400");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,25,"" );
        	}
        	break;   
        case 11:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_17,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前天经过燕长城的烽火台时，居然看见一个人，拿出一个号角仰天一吹，呼唤来了数条雷龙的降临，吓得我手足无措。\n    后来我才知道，原来这个号角就是传说中的神龙号角，能拿到神龙号角并吹响它的人，就能学会绝世神功——雷龙诀。我也非常想学雷龙诀，所以恳请你替我找到那神龙号角，我当时看见他将神龙号角放入了燕长城烽火台上的一个宝箱内，你去找找吧！\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_17,19) && !who->get_legend(TASK_17,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道是我眼睛看花了吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_17,20) && !who->get_legend(TASK_17,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……%s谢谢你了！\n"ESC"完成任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	break;
	case 12:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_17,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_17,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,26,"长城奇遇" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"长城奇遇");
        	}
        	break;
        case 13:
        	if ( who->get_legend(TASK_17,20) && !who->get_legend(TASK_17,21) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"神龙号角",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_17,21);
			who->add_exp(6800);
			who->add_potential(270);
			who->add_cash(6500);
			send_user(who,"%c%s",';',"长城奇遇 经验 6800 潜能 270 金钱 6500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,26,"" );
        	}
        	break;   
        case 14:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_17,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    昨天我路过燕长城的匝道处时，见到有一团神秘的荧光在上面飘动，我估计是失落已久的碧光石出现了，你愿意帮我寻到它吗？\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_17,22) && !who->get_legend(TASK_17,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这可真是太可惜了！要是能得到那宝石多好。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_17,23) && !who->get_legend(TASK_17,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……%s这可真是太谢谢你了！\n"ESC"完成任务\ntalk %x# welcome.16\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	break;
	case 15:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_17,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_17,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,27,"神秘的荧光" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"神秘的荧光");
        	}
        	break;
        case 16:
        	if ( who->get_legend(TASK_17,23) && !who->get_legend(TASK_17,24) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"碧光石",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_17,24);
			who->add_exp(7000);
			who->add_potential(260);
			who->add_cash(6300);
			send_user(who,"%c%s",';',"神秘的荧光 经验 7000 潜能 260 金钱 6300");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,27,"" );
        	}
        	break;   
        case 17:
        	if ( who->get_legend(TASK_28,10) && !who->get_legend(TASK_28,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    抱歉，我只是一个打铁的粗人，并不懂得打造精细之物，待我想想，应该会有别的办法。\n"ESC"完成任务\ntalk %x# welcome.18\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_28,11) && !who->get_legend(TASK_28,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我想想或许只有周Quốc的妙手公输班才能打造如此精细之物，你得去他那看看，或许他能帮得上你。\n"ESC"接受任务\ntalk %x# welcome.19\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 18:
        	if ( who->get_legend(TASK_28,10) && !who->get_legend(TASK_28,11) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,11);
			who->add_exp(23500);
			who->add_potential(430);
			who->add_cash(23000);
			send_user(who,"%c%s",';',"木箱的秘密（2） 经验 23500 潜能 430 金钱 23000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,48,"" );
        		me->do_welcome(17);
        	}
        	break; 
	case 19:
        	if ( who->get_legend(TASK_28,11) && !who->get_legend(TASK_28,12) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,12);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,49,"木箱的秘密（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"木箱的秘密（3）");
        	}
        	break;
        case 20:
       		if ( who->get_level() >= 105 && !who->get_legend(TASK_41,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我Quốc军队一向是我的最大货主，但最近我去送货的时候发现Triệu Quốc大将军李牧眉头紧锁，似乎有什么解决不了的烦心事，本来为大将军分忧乃是为臣本分，但是小心试探过多次将军也不说，无奈只有看义士是否能够帮到大将军了。\n"ESC"接受任务\ntalk %x# welcome.21\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 21:
       		if ( who->get_level() >= 105 && !who->get_legend(TASK_41,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_41,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,68,"询问原由" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询问原由");
        	}
        	break;
        }
}
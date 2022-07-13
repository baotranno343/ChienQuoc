
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>
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
int get_char_picid() { return 0053; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tôn Thiếu Gia");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",29);
//	set("legend",({32*7+22}));
 	set("mpLegend",([25:({32*7+22}),]));
 	set("mpLegend2",([0:({32*34+24,32*34+27,32*34+30,}),25:({32*7+24}),]));
        setup();
}

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
	if ( ( who->get_level() >= 25 && !who->get_legend(TASK_07,22) ) || ( who->get_legend(TASK_07,22) && !who->get_legend(TASK_07,24) ) )
		tmp += sprintf(ESC HIY "挑剔的晚餐\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( who->get_legend(TASK_34,23) && !who->get_legend(TASK_34,24) )
		tmp += sprintf(ESC HIY "替人说情\ntalk %x# welcome.4\n",getoid(this_object()));
	if ( (who->get_legend(TASK_34,24) && !who->get_legend(TASK_34,25)) || (who->get_legend(TASK_34,25) && !who->get_legend(TASK_34,27)) )
		tmp += sprintf(ESC HIY "面对挑衅\ntalk %x# welcome.4\n",getoid(this_object()));
	if ( (who->get_legend(TASK_34,27) && !who->get_legend(TASK_34,28)) || (who->get_legend(TASK_34,28) && !who->get_legend(TASK_34,30)) )
		tmp += sprintf(ESC HIY "灭掉孙少爷的威风\ntalk %x# welcome.4\n",getoid(this_object()));
	if ( who->get_legend(TASK_34,30) && !who->get_legend(TASK_35,1) )
		tmp += sprintf(ESC HIY "传达喜讯\ntalk %x# welcome.4\n",getoid(this_object()));

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
       	string *nTmp,tmp;   
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_07,22)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    晚餐想喝点清淡的汤，我对汤这东西可挑剔得很，首先，煲汤的原材料必须是最新鲜的，煲出来的汤才有可能原汁原味，而火候也必须要恰到好处，今天我想喝的这汤必须用3个莲藕、2个玉米、4个萝卜熬成，莲藕和玉米可以在沼泽地带杀毒刺蜂拿到，萝卜可以去大别山杀牛头怪拿到。\n    你去给我收集来这些做晚餐的材料，我会重赏！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_07,22) && !who->get_legend(TASK_07,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你是怎么办事的！你非得要我等到明天晚上才能喝到今晚的汤吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_07,23) && !who->get_legend(TASK_07,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    找来了？好吧，我这就吩咐下人去做，你拿好你的奖励吧！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_07,22)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,22);
        		who->delete_save_2("ssylianou");
        		who->delete_save_2("ssyyumi");
        		who->delete_save_2("ssyluobo");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,26,"挑剔的晚餐" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"挑剔的晚餐");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_07,23) && !who->get_legend(TASK_07,24) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"莲藕",3) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"玉米",2) != 1 )
        		{
        			item = new("item/98/0028");
        			item->set_amount(3);
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			return;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"萝卜",4) != 1 )
        		{
        			item = new("item/98/0028");
        			item->set_amount(3);
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			item = new("item/98/0029");
        			item->set_amount(2);
        			p = item->move(who,-1);
        			item->add_to_user(p);        			
        			return;        			
        		}

        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),30,HEAD_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			item->set_record(1);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move(who,-1);
			item->add_to_user(p);

			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,24);
        		who->delete_save_2("ssylianou");
        		who->delete_save_2("ssyyumi");
        		who->delete_save_2("ssyluobo");
			who->add_exp(3000);
			who->add_potential(60);
			who->add_cash(2000);
			send_user(who,"%c%s",';',sprintf("挑剔的晚餐 经验 3000 潜能 60 金钱 2000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,26,"" );
        	}
        	break;
        case 4:
		if ( who->get_legend(TASK_34,23) && !who->get_legend(TASK_34,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……又来了一个管闲事的！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_34,24) && !who->get_legend(TASK_34,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵，其实我只是对纱纤小姐颇为仰慕而已，哪里敢唐突佳人，做强逼之事呢?不过为了筹办婚事，我已经向火精和金精借了不少银钱，如果取消婚事这些银钱我也不能亏了才是啊，你代我去向火精和金精勾销这笔债务吧，用什么方法随你，帮我搞定就行。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_34,25) && !who->get_legend(TASK_34,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你想本少爷总不能做赔本的事情吧。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_34,26) && !who->get_legend(TASK_34,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，本少爷自当应诺，不过之前好像还有点麻烦哦。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_34,27) && !who->get_legend(TASK_34,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，但是朱老五也是我邀请的宾客，要是他赶来却告诉他婚礼取消他必定大闹一番，你如果能够打服让他不再闹事，我就同意你的请求。他如今正在虚陵洞西北处，你可去同他“好好”说一番。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_34,28) && !who->get_legend(TASK_34,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，免费回程了吧？朱老五可是本少爷豢养的死士，你那点三脚猫的本事也来学人家行侠仗义？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_34,29) && !who->get_legend(TASK_34,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊？朱老五死了？不可能！不可能，怎么可能……\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_34,30) && !who->get_legend(TASK_35,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    （孙少果然是孙少，经历了金牌打手被清洗之后还能够很快的回复过来）好，很好，这样子，我这就去解除同纱纤小姐的婚约，哈哈哈，等他同李德那个穷书生订婚的时候不要忘记通知我啊！\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 5:
        	if ( who->get_legend(TASK_34,23) && !who->get_legend(TASK_34,24) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,24);
			who->add_exp(75000);
			who->add_potential(940);
			who->add_cash(66000);
			send_user(who,"%c%s",';',"姻缘之路2 经验 75000 潜能 940 金钱 66000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,48,"" );
			me->do_welcome(4);
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_34,24) && !who->get_legend(TASK_34,25) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,25);
        		who->delete_save("ssyhuojing");
        		who->delete_save("ssyjinjing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,49,"姻缘之路3" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"姻缘之路3");
        	}
        	break;
	case 7:
        	if ( who->get_legend(TASK_34,26) && !who->get_legend(TASK_34,27) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,27);
        		who->delete_save("ssyhuojing");
        		who->delete_save("ssyjinjing");
			who->add_exp(75000);
			who->add_potential(940);
			who->add_cash(66000);
			send_user(who,"%c%s",';',"姻缘之路3 经验 75000 潜能 940 金钱 66000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,49,"" );
			me->do_welcome(4);
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_34,27) && !who->get_legend(TASK_34,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,28);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,50,"姻缘之路4" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"姻缘之路4");
        	}
        	break;
	case 9:
        	if ( who->get_legend(TASK_34,29) && !who->get_legend(TASK_34,30) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/final/15/1522",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,30);
			who->add_exp(77000);
			who->add_potential(980);
			who->add_cash(68000);
			send_user(who,"%c%s",';',"姻缘之路4 经验 77000 潜能 980 金钱 68000 强效法防 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,50,"" );
			me->do_welcome(4);
        	}
        	break;
        case 10:
        	if ( who->get_legend(TASK_34,30) && !who->get_legend(TASK_35,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,51,"姻缘之路5" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"姻缘之路5");
        	}
        	break;
        }

}

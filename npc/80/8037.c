
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
int get_char_picid() { return 0251; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Hạ Đầu Đảng");
        set_city_name("Tần Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
	set("mpLegend2",([0:({32*18+20,32*47+2,32*47+7,32*47+22,32*47+25,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
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
	if ( who->get_legend(TASK_18,19) && !who->get_legend(TASK_18,20) )
		tmp += sprintf(ESC HIY "请教用兵之法\ntalk %x# welcome.1\n",getoid(me));
        if ( who->get_legend(TASK_47,1)&&!who->get_legend(TASK_47,2) ) 
		tmp += sprintf(ESC HIY "询问配方\ntalk %x# welcome.3\n",getoid(me)); 
        if ( who->get_legend(TASK_47,2)&&!who->get_legend(TASK_47,3) ) 
		tmp += sprintf(ESC HIY "所差之药\ntalk %x# welcome.3\n",getoid(me)); 
        if ( who->get_legend(TASK_47,6)&&!who->get_legend(TASK_47,7) ) 
		tmp += sprintf(ESC HIY "解决困难\ntalk %x# welcome.3\n",getoid(me)); 
        if ( who->get_legend(TASK_47,21)&&!who->get_legend(TASK_47,22) ) 
		tmp += sprintf(ESC HIY "神剑之闻\ntalk %x# welcome.7\n",getoid(me)); 
        if ( who->get_legend(TASK_47,22)&&!who->get_legend(TASK_47,25) ) 
		tmp += sprintf(ESC HIY "加强实力\ntalk %x# welcome.7\n",getoid(me)); 
        if ( who->get_legend(TASK_47,25)&&!who->get_legend(TASK_47,26) ) 
		tmp += sprintf(ESC HIY "寻剑之路\ntalk %x# welcome.7\n",getoid(me)); 

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
		if  ( who->get_legend(TASK_18,19) && !who->get_legend(TASK_18,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此次作战事关重大，你可以叫将军挖好几条壕沟，掩盖上树枝与薄土，等待敌军到来时，叫他们措手不及，掉入陷阱，这样可扰乱军心。你回去把我的意见禀告将军吧。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_legend(TASK_18,19) && !who->get_legend(TASK_18,20) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_18,20);
			who->add_exp(6900);
			who->add_potential(260);
			who->add_cash(6600);
			send_user(who,"%c%s",';',"大展神威（2） 经验 6900 潜能 260 金钱 6600");
 			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,13,"大展神威（3）" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,12,"" );
 			send_user( who, "%c%s", '!', "得到任务 "HIY"大展神威（3）");
       		}
        	break;
        case 3:
		if  ( who->get_legend(TASK_47,1) && !who->get_legend(TASK_47,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此方补人之土气，需得导去人体中多余阴气，但是没有有效控制导流的方向和量，容易造成人阴气过虚以及体内脉象紊乱，容老夫想想该如何补救。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if  ( who->get_legend(TASK_47,2) && !who->get_legend(TASK_47,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    经过我多方查证，月见草可以弥补此药缺陷，每十二枚丹药配一株月见草，据老夫所知诛仙阵三层北部宝箱中常常藏有此类药材，你可速速前去找到交与秦药师，并将我嘱咐你的话转告与他。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));	
		else if  ( who->get_legend(TASK_47,6) && !who->get_legend(TASK_47,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵呵，你告诉秦老儿，谁怕谁啊，看谁先醉，只要别装醉把老夫撇下不付酒钱就得了！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 4:
        	if( who->get_legend(TASK_47,1) && !who->get_legend(TASK_47,2) )
        	{
			if (TASK_LEGEND_D->check_task_item(who,"炼药配方",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_47,2);
			who->add_exp(87000);
			who->add_potential(920);
			who->add_cash(91000);
			send_user(who,"%c%s",';',"炼药之路3 经验 87000 潜能 920 金钱 91000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,76,"" );
			me->do_welcome(3);
        	}
        	break;
        case 5:
        	if ( who->get_legend(TASK_47,2)&&!who->get_legend(TASK_47,3) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_47,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,77,"炼药之路4" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"炼药之路4");
       		}
        	break;
        case 6:
        	if( who->get_legend(TASK_47,6) && !who->get_legend(TASK_47,7) )
        	{    
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->task_finish(who);
			TASK_LEGEND_D->give_item(who,"item/product/63038",1); 		
        		who->set_legend(TASK_47,7);
			who->add_exp(86000);
			who->add_potential(1000);
			who->add_cash(91000);
			send_user(who,"%c%s",';',"炼药之路5 经验 86000 潜能 1000 金钱 91000 驱魔散图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,78,"" );
        	}
        	break;
        case 7:
        	if ( who->get_legend(TASK_47,21)&&!who->get_legend(TASK_47,22) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿嘿，想从我这里的得到神剑的消息可是要付出代价的。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_47,22)&&!who->get_legend(TASK_47,23) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哦，原来你是代大将军派来取剑的，他的代价已经付过了，我可以告诉你了，不过这取剑之地非常危险，大将军几个得力手下都折在里面了，我可希望快点得到大将军给我的全部允诺，这样吧，你去诛仙阵三层杀30个剑魂和30个枪魂，我利用这些魂气和杀气帮你铸起一道防护，但愿你能够平安取剑归来。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_47,23)&&!who->get_legend(TASK_47,24) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有我为你铸起的防护你无疑还是去送死啊，你难道连自己性命都不爱惜了么？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_47,24)&&!who->get_legend(TASK_47,25) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好了，年轻人，站直了，别趴下，我的施法可能会有点痛苦，你可得挺住！\n（天哪，这只是有点痛苦吗，莫非这就是传说中的分筋错骨手？我宁愿再去杀3000个枪魂……）\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_47,25)&&!who->get_legend(TASK_47,26) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("（夏侯党满意的看着缩成一团、全身哆嗦着、笼罩在似墨似朱的肤色中的你，嘿嘿直笑），好了，大功告成，你按照我刚才教你的阵法走位到诛仙阵三层西部角落，念一段破隐咒，神剑应该就藏在周围的箱子里。得到神剑之后直接交回大将军，可别想着私吞，神剑可不是你这种无福之人能够消受的。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", getoid(me)));
        	break;
        case 8:
        	if( who->get_legend(TASK_47,21)&&!who->get_legend(TASK_47,22) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_47,22);
			who->add_exp(98000);
			who->add_potential(1400);
			who->add_cash(91000);
			send_user(who,"%c%s",';',"索取神剑2 经验 98000 潜能 1400 金钱 91000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,85,"" );
			me->do_welcome(7);
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_47,22)&&!who->get_legend(TASK_47,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_47,23);
        		who->delete_save("xhdjianhun");
        		who->delete_save("xhdqianhun");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,86,"索取神剑3" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"索取神剑3");
       		}
        	break;
        case 10:
        	if( who->get_legend(TASK_47,24)&&!who->get_legend(TASK_47,25) )
        	{
        		who->delete_save("xhdjianhun");
        		who->delete_save("xhdqianhun");
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_47,25);
			who->add_exp(95000);
			who->add_potential(1500);
			who->add_cash(88000);
			send_user(who,"%c%s",';',"索取神剑3 经验 95000 潜能 1500 金钱 88000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,86,"" );
			me->do_welcome(7);
        	}
        	break;
        case 11:
        	if ( who->get_legend(TASK_47,25)&&!who->get_legend(TASK_47,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_47,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,87,"索取神剑4" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"索取神剑4");
       		}
        	break;
        }
}
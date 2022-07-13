
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
int get_char_picid() { return 7302; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Sa Tiêm Tiểu Tỷ");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",26);
//	set("legend",({32*6+22}));
 	set("mpLegend",([25:({32*6+22}),]));
 	set("mpLegend2",([0:({32*34+22,32*35+2,}),25:({32*6+24,}),]));
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
	if ( ( who->get_level() >= 25 && !who->get_legend(TASK_06,22) ) || ( who->get_legend(TASK_06,22) && !who->get_legend(TASK_06,24) ) )
		tmp += sprintf(ESC HIY "发绳\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( who->get_legend(TASK_34,21) && !who->get_legend(TASK_34,22) )
		tmp += sprintf(ESC HIY "打探消息\ntalk %x# welcome.4\n",getoid(this_object()));
	if ( who->get_legend(TASK_34,22) && !who->get_legend(TASK_34,23) )
		tmp += sprintf(ESC HIY "替人说情\ntalk %x# welcome.4\n",getoid(this_object()));
	if ( who->get_legend(TASK_35,1) && !who->get_legend(TASK_35,2) )
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
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,22)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    二姑家的大哥娶媳妇儿，爹叫我和他一起去庆祝，大家闺秀出门怎样也得打扮打扮，我也得打扮得漂亮点，别给爹丢脸了，想把这一头秀发编成几个辫子，可惜了身边只有发钗，没有发绳，拜托你给我找20个发绳来。\n    桂陵、牧野一带的草寇虽然凶猛，但是很疼家里的娘子，我估计他们身上会有发绳，所以你去那里肯定能找到，路程不远，所以希望你能快点给我找来，小女子给你道谢了。\n    从我这出去没多远就到了桂陵，赶紧去吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,22) && !who->get_legend(TASK_06,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我委托你找的发绳呢？可别耽误了我去喝喜酒！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,23) && !who->get_legend(TASK_06,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真是感谢你，嘻嘻，有了这些发绳，我能编个最漂亮的辫子，到时候一定会给爹脸上添光的！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,22)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,22);
        		who->delete_save_2("saqianfashen");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,1,"纱纤小姐的发绳" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"纱纤小姐的发绳");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_06,23) && !who->get_legend(TASK_06,24) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"发绳",20) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/62009",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,24);
			who->delete_save_2("saqianfashen");
			who->add_exp(2000);
			who->add_potential(60);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"纱纤小姐的发绳 经验 2000 潜能 60 金钱 1500 铜针图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,1,"" );
        	}
        	break;
        case 4:
		if ( who->get_legend(TASK_34,21) && !who->get_legend(TASK_34,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呜呜呜，我不想活了……我要私奔！可是天下之大，真的逃得了吗？\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_34,22) && !who->get_legend(TASK_34,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，两年前，我上街赏玩花灯的时候遇到了异地求学的书生李德，我们争猜灯谜，互不相让，后来彼此心折，诗词吟和，只等他求学有成，向爹爹禀明婚事了，但是不久前我们前去湘妃林游玩时我们不甚走失，我竟然遇到了孙少爷，他在那里多有轻薄之言，我慌忙走掉，找到李德赶紧回家，不料孙少爷竟然上我家提亲，我爹贪图富贵，竟然将我许了他，我哀求哭闹都无济于事，李德如今一介书生，整日愁眉苦脸也无计可施，我想孙少爷虽然轻薄，但当时看他尚是明理之人，我一介女子不好前去私自见他，你能帮我向孙少爷求情吗？\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_35,1) && !who->get_legend(TASK_35,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呜呜呜，真是太感谢了，除了以身相许，我拿什么感谢你都可以。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 5:
        	if ( who->get_legend(TASK_34,21) && !who->get_legend(TASK_34,22) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,22);
			who->add_exp(75000);
			who->add_potential(950);
			who->add_cash(65000);
			send_user(who,"%c%s",';',"姻缘之路1 经验 75000 潜能 950 金钱 65000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,47,"" );
			me->do_welcome(4);
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_34,22) && !who->get_legend(TASK_34,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,23);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,48,"姻缘之路2" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"姻缘之路2");
        	}
        	break;
	case 7:
        	if ( who->get_legend(TASK_35,1) && !who->get_legend(TASK_35,2) )
        	{
//        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 2 )
//        			return ;
			if(USER_INVENTORY_D->count_empty_carry(who) < 2 )
			{
			        send_user(who,"%c%s",';',"您身上没有足够空位！");
        			return;
			}
			TASK_LEGEND_D->task_finish(who);
			TASK_LEGEND_D->give_item(who,"item/91/9165",1);
			TASK_LEGEND_D->give_item(who,"item/91/9165",1);
			who->set_legend(TASK_35,2);
			who->add_exp(75000);
			who->add_potential(980);
			who->add_cash(67000);
			send_user(who,"%c%s",';',"姻缘之路5 经验 75000 潜能 980 金钱 67000 归元丹 2");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,51,"" );
        	}
        	break;
        }
}

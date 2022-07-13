
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5301; }
void do_welcome(string arg);
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
// 函数：构造处理
void create()
{
        set_name("Ngụy Quản Gia");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//	set("level",28);
//	set("legend",({32*7+13,}));
 	set("mpLegend",([25:({32*7+13}),]));
 	set("mpLegend2",([25:({32*7+15,32*7+18,32*7+21,}),]));
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
	if( (who->get_level() >= 25 && !who->get_legend(TASK_07,13)) || ( who->get_legend(TASK_07,13) && !who->get_legend(TASK_07,15)) )
		tmp += sprintf(ESC HIY "劫难之一\ntalk %x# welcome.1\n",getoid(this_object()));
	if( (who->get_legend(TASK_07,15) && !who->get_legend(TASK_07,16)) || ( who->get_legend(TASK_07,16) && !who->get_legend(TASK_07,18)) )
		tmp += sprintf(ESC HIY "劫难之二\ntalk %x# welcome.4\n",getoid(this_object()));
	if( (who->get_legend(TASK_07,18) && !who->get_legend(TASK_07,19)) || ( who->get_legend(TASK_07,19) && !who->get_legend(TASK_07,21)) )
		tmp += sprintf(ESC HIY "劫难之三\ntalk %x# welcome.7\n",getoid(this_object()));

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
        	if( who->get_level() >= 25 && !who->get_legend(TASK_07,13) )
        		send_user(who,"%c%s",':',sprintf("%s:\n    最近有点烦，有个听说算命很灵的先生前天突然跑来我家，塞给我三个锦囊，告诉我这个月我将有三个劫难，并交代我万万不可擅自打开这三个锦囊，一定得等到一个名叫%s的人来找我后，才能打开第一个锦囊，今天我终于等到你了！\n    我打开了第一个锦囊，里面说需要你给我收集20个南瓜，方能化解第一个劫难，而这种南瓜只有杀掉大别山一带的牛头怪才能得到。我想你不会拒绝我这个快要遭受劫难的人吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),who->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_07,13) && !who->get_legend(TASK_07,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果过了今天，还不能收集够20个南瓜，第一个劫难就要应验了，你能快点吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_07,14) && !who->get_legend(TASK_07,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢天谢地，第一个劫难终于有人愿意帮我化解了！化解第二个劫难是要杀猪妖和豺狗，不知又有谁愿意帮我。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_07,13)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,13);
        		who->delete_save_2("wgjnangua");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,8,"魏管家的劫难（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"魏管家的劫难（1）");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_07,14) && !who->get_legend(TASK_07,15) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"南瓜",20) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,15);
			who->delete_save_2("wgjnangua");
			who->add_exp(1800);
			who->add_potential(40);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"魏管家的劫难（1） 经验 1800 潜能 40 金钱 1500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,8,"" );
			me->do_welcome(4);
        	}
        	break;
        case 4:
        	if(who->get_legend(TASK_07,15) && !who->get_legend(TASK_07,16))
        		send_user(who,"%c%s",':',sprintf("%s:\n    谢天谢地，你终于帮助我化解了第一个劫难！而第二个锦囊是需要化解第一个劫难后才能打开的。\n    我刚刚看了，锦囊上说，需要化解第二个劫难，便需要去杀巫山、鄱阳湖附近的20只猪妖与10只豺狗，并且还说到，如果化解第一个劫难的人愿意帮助我去杀猪妖与豺狗，那会更好！\n    所以，我希望你还能替我跑这一趟，拜托！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_07,16) && !who->get_legend(TASK_07,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果是猪妖和豺狗的能力太强大，而导致你不能帮助我化解第二个劫难，我想这是上天对我的惩罚！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_07,17) && !who->get_legend(TASK_07,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    第一个劫难与第二个劫难都是你给我化解的，我要好好感谢你，当然，你能给我化解第三个劫难是最好不过了！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 5:
        	if (who->get_legend(TASK_07,15) && !who->get_legend(TASK_07,16))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,16);
        		who->delete_save_2("wgjzhuyao");
        		who->delete_save_2("wgjcaigou");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,9,"魏管家的劫难（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"魏管家的劫难（2）");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_07,17) && !who->get_legend(TASK_07,18) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,18);
			who->delete_save_2("wgjzhuyao");
        		who->delete_save_2("wgjcaigou");
			who->add_exp(1800);
			who->add_potential(40);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"魏管家的劫难（2） 经验 1800 潜能 40 金钱 1500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,9,"" );
			me->do_welcome(7);
        	}
        	break;
        case 7:
        	if(who->get_legend(TASK_07,18) && !who->get_legend(TASK_07,19))
        		send_user(who,"%c%s",':',sprintf("%s:\n    你已经给我化解了前两个劫难，算命先生说，如果你愿意帮我化解这三个劫难，那么你将得到上天的眷顾。\n    我刚刚打开锦囊，上面说第三个劫难需要找到神秘泥人，我依稀记得神秘泥人在太湖的堂里村出现过。\n    我想你是不会拒绝我的，对吧！\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开",me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_07,19) && !who->get_legend(TASK_07,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    其实最后一个劫难是最容易化解的，你能给我找回来那个神秘泥人吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_07,20) && !who->get_legend(TASK_07,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    悬着的一颗心终于放下来了！你帮了我这么大的忙，我真不知该如何感谢你才好！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 8:
        	if (who->get_legend(TASK_07,18) && !who->get_legend(TASK_07,19))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,10,"魏管家的劫难（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"魏管家的劫难（3）");
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_07,20) && !who->get_legend(TASK_07,21) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"神秘泥人",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/final/15/1501",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,21);
			who->add_exp(5800);
			who->add_potential(200);
			who->add_cash(5000);
			send_user(who,"%c%s",';',"魏管家的劫难（3） 经验 5800 潜能 200 金钱 5000 初级法力 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,10,"" );
        	}
        	break;
        }
}

// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5501; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Lí Phòng");
        set_city_name("Triệu Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));
	set("mpLegend2",([0:({32*14+14,32*43+8,32*43+11,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string tmp="";
	string *npc_info;
	
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}
	npc_info = who->get_quest("escort.npcinfo");
	if ( who->get_quest("escort.biaowang") && arrayp(npc_info) && 
		npc_info[1] == me->get_name())
		tmp += sprintf(ESC HIG "镖王争霸战\ntalk %x# welcome.21\n",getoid(me));
        else if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( who->get_legend(TASK_14,13) && !who->get_legend(TASK_14,14) )
		tmp += sprintf(ESC HIY "取名\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_43,7) && !who->get_legend(TASK_43,8) )
		tmp += sprintf(ESC HIY "查访知情人\ntalk %x# welcome.3\n",getoid(me));
	if ( who->get_legend(TASK_43,8) && !who->get_legend(TASK_43,11) )
		tmp += sprintf(ESC HIY "解除威胁\ntalk %x# welcome.3\n",getoid(me));
	if ( who->get_legend(TASK_43,11) && !who->get_legend(TASK_43,12) )
		tmp += sprintf(ESC HIY "寻回名单\ntalk %x# welcome.3\n",getoid(me));
			
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
	       	if ( who->get_legend(TASK_14,13) && !who->get_legend(TASK_14,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这个仪器可以叫做浑仪，那三个圆环分别叫子午环、赤道环、赤经环，这样吧，我呆会自会派人和Yên Quốc御史商量，你可以先行离去。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
    
        case 2:
        	if ( who->get_legend(TASK_14,13) && !who->get_legend(TASK_14,14) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/62041",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_14,14);
			who->add_exp(8000 );
			who->add_potential(480);
			who->add_cash(7000);
			send_user(who,"%c%s",';',"浑仪（3） 经验 8000 潜能 480 金钱 7000 玉蜂针图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,27,"" );
        	}
        	break;   
        case 3:
	       	if ( who->get_legend(TASK_43,7) && !who->get_legend(TASK_43,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，其实我在这里日久，自然是知道一些事情端倪的，但是事关重大，我不敢轻易开口啊！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
	       	else if ( who->get_legend(TASK_43,8) && !who->get_legend(TASK_43,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，看在我朋友的分上，我还是告诉你吧，不过在你没有把握干掉始作俑者之前，你千万莫要把我说出去，这可事关我一家大小的安危啊。最近这一带强盗龙九纠集了一帮子人在赵长城一带抢劫，要是只是抢劫恐怕还不足以让人心神剧裂，更为可怕的是龙九不知道从那个方士那里得知，要长生不老要吃掉活人的心脉100根，最近陆续起码有了五六十个人失踪在此，恐怕就是遭了他毒手，而龙九称，只要我们不揭发他，他就留我们活命，否则就拿我们家人的心脉去吃，哎，与这种丧尽天良的恶魔为邻，我们也是寝食难安，我们现在谁都不敢去买猪心牛心羊心吃，生怕会引起所有人呕吐出来，壮士你若是自忖不能杀死龙九，还是速速离去吧，要不然连累我们一家老小，你于心何忍啊。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
	       	else if ( who->get_legend(TASK_43,9) && !who->get_legend(TASK_43,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    据说他炼的是邪心大法，既然你知道奈何不了龙九，你还是速速离去吧，你斗不过就切莫牵连我们。\n"ESC"离开", me->get_name()));
	       	else if ( who->get_legend(TASK_43,10) && !who->get_legend(TASK_43,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天哪，这个恶魔终于死了，谢天谢地，我们可以睡个安稳觉了。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
	       	else if ( who->get_legend(TASK_43,11) && !who->get_legend(TASK_43,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎死者已矣，为今我所能做到的只有通知家属，准备后事了。那龙九活动之处，一定有那些失踪人员的名单，据说那名单被藏在天门阵三层中部的一个箱子里，你前去将它取回交给本Quốc典狱官。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));

        	break;		
        case 4:
	       	if ( who->get_legend(TASK_43,7) && !who->get_legend(TASK_43,8) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"拜访信",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_43,8);
			who->add_exp(96000);
			who->add_potential(1900);
			who->add_cash(92000);
			send_user(who,"%c%s",';',"查访知情人 经验 96000 潜能 1900 金钱 92000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,89,"" );
			me->do_welcome(3);
        	} 
		break;
	case 5:
		if ( who->get_legend(TASK_43,8) && !who->get_legend(TASK_43,9) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_43,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,90,"解除威胁" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"解除威胁");
        	}
		break;
        case 6:
	       	if ( who->get_legend(TASK_43,10) && !who->get_legend(TASK_43,11) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_43,11);
			who->add_exp(99000);
			who->add_potential(1800);
			who->add_cash(91000);
			send_user(who,"%c%s",';',"解除威胁 经验 99000 潜能 1800 金钱 91000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,90,"" );
			me->do_welcome(3);
        	} 
		break;
	case 7:
		if ( who->get_legend(TASK_43,11) && !who->get_legend(TASK_43,12) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_43,12);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,91,"寻回名单" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻回名单");
        	}
		break;
	case 21:
        case 22:
        	TASK_ESCORT_D->biaowang(me,who,flag);
        }
}
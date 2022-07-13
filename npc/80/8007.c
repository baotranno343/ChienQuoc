
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
int get_char_picid() { return 5301; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tề Tổng Quản");
        set_city_name("Tề Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",36);
//	set("legend",({32*9+19}));
	set("mpLegend",([35:({32*9+19,32*37+29}),90:({32*31+1}),100:({32*36+17})]));
	set("mpLegend2",([0:({32*29+17,32*29+20,}),35:({32*9+27,}),100:({32*36+19,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who ) 
{
	int id;
	object me = this_object();
	string tmp="";
	
	if ("/sys/task/master"->do_look_quest10(who, me)>0) return;
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
	id = getoid(me);
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( ( who->get_level() >= 35 && !who->get_legend(TASK_09,19) ) || ( who->get_legend(TASK_09,19) && !who->get_legend(TASK_09,20) ) )
		tmp += sprintf(ESC HIY "赵的求助\ntalk %x# welcome.1\n",id);
	if ( who->get_legend(TASK_09,26) && !who->get_legend(TASK_09,27) )
	{
		tmp += sprintf(ESC HIY "财政官的回复\ntalk %x# welcome.1\n",id);
	}		
	if ( who->get_legend(TASK_29,16) && !who->get_legend(TASK_29,17) )
	{
		tmp += sprintf(ESC HIY "打听消息\ntalk %x# welcome.4\n",id);
	}
	if ( (who->get_legend(TASK_29,17) && !who->get_legend(TASK_29,18)) || (who->get_legend(TASK_29,18) && !who->get_legend(TASK_29,20)))
	{
		tmp += sprintf(ESC HIY "接受考验\ntalk %x# welcome.4\n",id);
	}
	if ( who->get_legend(TASK_29,20) && !who->get_legend(TASK_29,21) )
	{
		tmp += sprintf(ESC HIY "水落石出\ntalk %x# welcome.4\n",id);
	}
	if ( who->get_level() >= 35 && !who->get_legend(TASK_37,29) )
		tmp += sprintf(ESC HIY "交换心得\ntalk %x# welcome.11\n",id);

	if ( who->get_level() >= 90 && !who->get_legend(TASK_31,1) ) 
		tmp += sprintf(ESC HIY "询问小贩\ntalk %x# welcome.9\n",id);
	if ( (who->get_level() >= 100 && !who->get_legend(TASK_36,17)) || (who->get_legend(TASK_36,17) && !who->get_legend(TASK_36,19)) )
		tmp += sprintf(ESC HIY "涅磐\ntalk %x# welcome.13\n",id);		
	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
			+ tmp +
			ESC"离开"
			);

}

// 函数：开始任务
// void do_task_start() { TASK_ESCORT_D->do_task_start( this_player(), this_object() ); }
// 函数：取消任务
// void do_task_cancel() { TASK_ESCORT_D->do_task_cancel( this_player(), this_object() ); }

int accept_money(object who, int gold)
{
	return "/sys/task/master"->accept_money(this_object(), who, gold);
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
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,19)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    秦、赵大战于长平，我Quốc与燕合力救赵。今赵军缺粮，派人到本王府，希望能给本Quốc财政官通报一声，借点粮食，有助于赵军继续攻秦。本总管希望你速速将此事禀报本Quốc财政官！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,19) && !who->get_legend(TASK_09,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来Triệu Quốc气数已尽，怪不得别人，财政官不肯帮他，也是预料之中，削弱自身Quốc力的事情谁都不愿去做！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_09,26) && !who->get_legend(TASK_09,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    果然是英明的决策！出于仁义救助面临危亡的Triệu Quốc，军威足以击退秦军，如果因为害怕削弱自身的Quốc力，而不帮助Triệu Quốc，这样为Quốc家考虑，显然是错误的策略！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,19)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,1,"唇亡齿寒（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"唇亡齿寒（1）");
        	}
        	break;
       case 3:
        	if ( who->get_legend(TASK_09,26) && !who->get_legend(TASK_09,27) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/61003",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_09,27);
			who->add_exp(3300);
			who->add_potential(100);
			who->add_cash(3000);
			send_user(who,"%c%s",';',"唇亡齿寒（4） 经验 3300 潜能 100 金钱 3000 油炸地瓜片图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,4,"" );
        	}
        	break;        
        case 4:
        	if ( who->get_legend(TASK_29,16) && !who->get_legend(TASK_29,17) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这个嘛！我得好好想想。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_29,17) && !who->get_legend(TASK_29,18) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    稀世宝玉可要看拥有他的人有没有福分，你去将军古墓二层杀掉30只石狮和30只石虎还能安全回来的话我可以考虑一下是否你消受得起。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_29,18) && !who->get_legend(TASK_29,19) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来你是不行啊！就这点本事，还想帮人寻宝？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_29,19) && !who->get_legend(TASK_29,20) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯～！不错，不错！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_29,20) && !who->get_legend(TASK_29,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这件事我是知道的，但是这个宝玉据说有邪气，凡是拥有它放在家中都会闹鬼，它的上一任主人财政官的堂哥一家就是被它给害死的，所以财政官虽然很喜欢它，可是为了不让家人收到危害，只得将他丢弃在某个地方，这个具体的你得去问财政官了。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));

	    	break;
        case 5:
        	if ( who->get_legend(TASK_29,16) && !who->get_legend(TASK_29,17) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,17);
			who->add_exp(50000);
			who->add_potential(700);
			who->add_cash(52000);
			send_user(who,"%c%s",';',"打听消息 经验 50000 潜能 700 金钱 52000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,26,"" );
			me->do_welcome(4);
        	}
        	break;   
	case 6:
        	if ( who->get_legend(TASK_29,17) && !who->get_legend(TASK_29,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,18);
        		who->delete_save("qzgshisi");
        		who->delete_save("qzgshihu");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,27,"接受考验" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"接受考验");
        	}
        	break;
        case 7:
        	if ( who->get_legend(TASK_29,19) && !who->get_legend(TASK_29,20) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,20);
        		who->delete_save("qzgshisi");
        		who->delete_save("qzgshihu");
			who->add_exp(53000);
			who->add_potential(710);
			who->add_cash(53000);
			send_user(who,"%c%s",';',"接受考验 经验 53000 潜能 710 金钱 53000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,27,"" );
			me->do_welcome(4);
        	}
        	break;   
	case 8:
        	if ( who->get_legend(TASK_29,20) && !who->get_legend(TASK_29,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,28,"水落石出" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"水落石出");
        	}
        	break;
        case 9:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_31,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我每次出宫都要买齐小贩的包子，可是最近经过老是看到他垂头丧气，可是我的身份又不方便动问，你去帮我看看有什么可以帮忙的地方。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 10:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_31,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,45,"询问小贩" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询问小贩");
        	}
        	break;
        case 11:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_37,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听闻秦管家管事有方，诺大一个秦王府被他管理得头头是道，主子仆人上下井然，俗话说，没规矩不成方圆，我看我还得向秦管家讨教讨教，关于怎样管理好这大大小小的仆人，还真得下一番工夫。我看不如你替我去趟Tần Quốc，向秦管家取这管理的经。\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 12:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_37,29) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_37,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,73,"交换心得" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"交换心得");
        	}
        	break;
        case 13:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,17)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    东海渔村一个月前突然百鸟汇集，原来竟然是天降祥瑞，凤凰临世，想不到几日前几个游手好闲的所谓大侠为了宝物竟然乘凤凰临产突施杀手，东海渔村突下天火，凤凰浴火而重生，也烧死了那几个贪心的家伙，我Quốc旅秦侨民马显报告说卜卦得知凤凰涅磐留下一块凤凰玉佩，传言有青春永驻的功效，王后闻说甚为挂念，命老夫觅人秘密寻找，本官见你聪明伶俐，又多次圆满完成交代你的任务，决定将这项美差交与你，如何，你可能胜任？\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_36,17) && !who->get_legend(TASK_36,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道是马显误报还是你搜寻的不够仔细？你再去看看，王后可是心急得很。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_36,18) && !who->get_legend(TASK_36,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    王后若见，必定欣喜若狂。哈哈哈……\n"ESC"完成任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 14:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,17)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_36,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,55,"涅磐" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"涅磐");
        	}
        	break;
	case 15:
        	if ( who->get_legend(TASK_36,18) && !who->get_legend(TASK_36,19) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"凤凰玉佩",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,19);
			who->add_exp(80000);
			who->add_potential(958);
			who->add_cash(69000);
			send_user(who,"%c%s",';',"涅磐 经验 80000 潜能 958 金钱 69000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,55,"" );
        	}
        	break; 
        }
}

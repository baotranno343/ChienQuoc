
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
int get_char_picid() { return 5802; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Lí Đồ");
        set_city_name("Tề Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
	set("mpLegend",([110:({32*44+24})]));
	set("mpLegend2",([0:({32*30+9,32*30+19,}),110:({32*44+26,}),]));
        setup();
}

// 函数：对话处理
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
	if ( who->get_legend(TASK_30,8) && !who->get_legend(TASK_30,9) )
	{
		tmp += sprintf(ESC HIY "询查原因\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_30,9) && !who->get_legend(TASK_30,10) )
	{
		tmp += sprintf(ESC HIY "明辨是非\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_30,18) && !who->get_legend(TASK_30,19) )
	{
		tmp += sprintf(ESC HIY "驯服恶霸\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >=110 && !who->get_legend(TASK_44,24)) || (who->get_legend(TASK_44,24) && !who->get_legend(TASK_44,26)) )
		tmp += sprintf(ESC HIY "忘恩负义之徒\ntalk %x# welcome.5\n",getoid(me));
	if ( who->get_legend(TASK_44,26) && !who->get_legend(TASK_44,27) ) 
		tmp += sprintf(ESC HIY "油菜籽\ntalk %x# welcome.5\n",getoid(me));

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
        	if ( who->get_legend(TASK_30,8) && !who->get_legend(TASK_30,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真是气死我了！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_30,9) && !who->get_legend(TASK_30,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    雷霸天是在是欺人太甚，我们的房子和他家的房子相邻，他居然说我家的屋檐占了他家的天井，墙壁进多了一寸，硬是动手拆了我们家的屋檐，砸开了半边墙，搞得我们家里下雨就漏水，风呼呼往里面刮，根本无法住人，只好搬到河对岸看守田地的临时房子里面来了，这位大侠可要为我们仗义执言啊。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_30,18) && !who->get_legend(TASK_30,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    终于可以不必挤在那个小窝棚了！大恩大德，这辈子没法子以身相许，待我来世再报吧！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_legend(TASK_30,8) && !who->get_legend(TASK_30,9) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,9);
			who->add_exp(62000);
			who->add_potential(770);
			who->add_cash(53000);
			send_user(who,"%c%s",';',"询查原因 经验 62000 潜能 770 金钱 53000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,35,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_30,9) && !who->get_legend(TASK_30,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,36,"明辨是非" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"明辨是非");
        	}
        	break; 
        case 4:
        	if ( who->get_legend(TASK_30,18) && !who->get_legend(TASK_30,19) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->task_finish(who);
			TASK_LEGEND_D->give_item(who,"item/final/91/1812",2);
			who->set_legend(TASK_30,19);
			who->add_exp(68000);
			who->add_potential(800);
			who->add_cash(51000);
			send_user(who,"%c%s",';',"驯服恶霸 经验 68000 潜能 800 金钱 51000 紫金丹 2");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,39,"" );
        	}
        	break;
        case 5:
        	if ( who->get_level() >= 110 && !who->get_legend(TASK_44,24)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，想当年我也是威风凛凛的将军啊，手下一呼百应，好不风光，想不到伴君如伴虎，尤其是碰上好色的君主更是无可奈何，王看上我的小妾洱娇竟然编造理由将我下狱，出来我已经一无所有，家没了，连当年那些属下也肆意殴打凌辱我，这就是所谓的忠诚，所谓的人情，你给我去干掉这些忘恩负义的家伙吧，什么，你说大王，大王岂是你可以置评的，你就给我干掉我那些忘恩负义的下属，枪魂，什么，我怎么会有非人类的属下，难道你不知道我是伟大的驭魂师吗，虽然我法力被废了，可是我还是能够知道他们在什么地方，诛仙阵里面，你给我干掉闹的最凶的10个，让他们知道，背叛我的下场！\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_44,24) && !who->get_legend(TASK_44,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我还以为你一身正气，是可以托付信任的人，结果原来世间鼠辈，不过耳耳，哼，我算是再次看清了！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_44,25) && !who->get_legend(TASK_44,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈……（李屠面目狰狞,状若疯狂,根本就忘记了旁人的存在,你壮着胆子,从他紧攥的手里掰出金子,赶紧闪人。）\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_44,26) && !who->get_legend(TASK_44,27) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我一向是恩怨分明，我忘不了别人给我的伤害，更加不会忘记别人对我的恩惠。前段时间我流浪街头的时候，是李浪收留了我给我一个容身之处，你要知道对于落魄之后受尽冷眼的我简直就是重生再造啊，也因此我对人情没有完全绝望，至少我的心中还有那么一点点温暖，我身无长物，也不能送他什么贵重的东西，只是听说最近他急需扩建作坊，需要大量的油菜籽，市面上的我买不起，我知道诛仙阵里面那些刀魂、剑魂、枪魂喜欢收集这种东西，只有请你帮我去找点来，能让我聊表心意。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 6:
        	if ( who->get_level() >= 110 && !who->get_legend(TASK_44,24)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_44,24);
        		who->delete_save("lituqianhun");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,66,"人情冷暖（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"人情冷暖（1）");
        	}
        	break;
	case 7:
        	if ( who->get_legend(TASK_44,25) && !who->get_legend(TASK_44,26) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_44,26);
        		who->delete_save("lituqianhun");
			who->add_exp(51000);
			who->add_potential(778);
			who->add_cash(50300);
			send_user(who,"%c%s",';',"人情冷暖（1） 经验 51000 潜能 778 金钱 50300");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,66,"" );
			me->do_welcome(5);
        	}
        	break; 
        case 8:
        	if ( who->get_legend(TASK_44,26) && !who->get_legend(TASK_44,27) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_44,27);
        		who->delete_save("lituyoucaizi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,67,"人情冷暖（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"人情冷暖（2）");
        	}
        	break;
        }
}


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
int get_char_picid() { return 5302; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Ngụy Tổng Quản");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",22);
//	set("legend",({32*5+22}));
 	set("mpLegend",([20:({32*5+22}),95:({32*34+21,32*35+3})]));
 	set("mpLegend2",([20:({32*5+24}),]));
        setup();
}

// 函数：对话处理
void do_look( object who ) 
{
	string tmp="";
	
	if ("/sys/task/master"->do_look_quest10(who, this_object())>0) return;
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
	if ( ( who->get_level() >= 20 && !who->get_legend(TASK_05,22) ) || ( who->get_legend(TASK_05,22) && !who->get_legend(TASK_05,24) ) )
		tmp += sprintf(ESC HIY "沉默的剑魂\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( who->get_level() >= 95 && !who->get_legend(TASK_34,21) )
		tmp += sprintf(ESC HIY "打探消息\ntalk %x# welcome.4\n",getoid(this_object()));
	if ( who->get_level() >= 95 && !who->get_legend(TASK_35,3) )
		tmp += sprintf(ESC HIY "探访奇事\ntalk %x# welcome.6\n",getoid(this_object()));

	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
			+ tmp +
			ESC"离开"
			);

}

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
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,22)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    人在江湖，身不由己，就连鬼魂也不例外。\n    最近很多人向我报告有一个剑魂为非作歹，正好昨天晚上他托梦告诉我，他活着的时候就是一个善良之人，死后本从未做过任何伤天害理，但是最近感受到一股邪恶的力量控制他的思想，让他神智不清，经常不受自己控制就去做一些伤害人的事情，他感到很懊恼，所以请求我的帮助。\n    经过我的调查，是一名叫赵术士的巫师在作法操纵他，所以请你前去消灭赵术士，他现在就在马陵道的古木丛林，我估计他又要开始施法了，你赶快去吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_05,22) && !who->get_legend(TASK_05,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来这个剑魂从此将不会沉默下去，不知将会有多少无辜的人死在它剑下。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_05,23) && !who->get_legend(TASK_05,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下这个剑魂可以好好安息了。%s你不知救了许多人的性命，我一定会好好酬谢你。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,22)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,16,"沉默的剑魂" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"沉默的剑魂");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_05,23) && !who->get_legend(TASK_05,24) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_05,24);
			who->add_exp(1200);
			who->add_potential(60);
			who->add_cash(1000);
			send_user(who,"%c%s",';',"沉默的剑魂 经验 1200 潜能 60 金钱 1000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,16,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_34,21)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，有情不能相聚，老夫听了也扼腕叹息啊，如此好的一段姻缘竟然被拆散，你想知道事情的原因吗？那就去问城西小村的纱纤小姐吧！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 5:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_34,21)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,47,"姻缘之路1" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"姻缘之路1");
        	}
        	break;
        case 6:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_35,3)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近临河镇据说有许多怪事发生，民间流言甚多，什么神仙下凡收坐骑，什么妖怪出洞找生祭，你好好去调查一番到底什么人在装神弄鬼，据说城西临河镇的孟求见闻识广，你去多向他求教一下吧。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 7:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_35,3)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,52,"探访奇事" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"探访奇事");
        	}
        	break;
        }
}
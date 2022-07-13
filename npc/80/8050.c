
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
        set_name("Yên Tổng Quản");
        set_city_name("Yên Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
	set("mpLegend2",([0:({32*27+11,32*32+10,}),40:({32*38+2,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who ) 
{
	string tmp="";
	object me = this_object();
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
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( who->get_legend(TASK_27,10) && !who->get_legend(TASK_27,11) )
		tmp += sprintf(ESC HIY "同心锁\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_legend(TASK_27,11) && !who->get_legend(TASK_27,12)) || (who->get_legend(TASK_27,12) && !who->get_legend(TASK_27,14)) )
		tmp += sprintf(ESC HIY "同心锁\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_32,9) && !who->get_legend(TASK_32,10) )
		tmp += sprintf(ESC HIY "论语\ntalk %x# welcome.5\n",getoid(me));
	if ( who->get_level() >= 40 && who->get_legend(TASK_38,1) && !who->get_legend(TASK_38,2) )
		tmp += sprintf(ESC HIY "紫葡萄\ntalk %x# welcome.7\n",getoid(me));

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
        object who,item;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_legend(TASK_27,10) && !who->get_legend(TASK_27,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天下的宝物我都知道，很多人都找我打听一些宝物的下落，但是我可不是这么轻易会告诉人我所知道的宝物的下落的哦。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if (who->get_legend(TASK_27,11) && !who->get_legend(TASK_27,12))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    每个来向我打听宝物的消息的人，我都会写给他一封写着这宝物的信。但是这封信必须是要用在灵谷洞一、二、三层分别找到给我的毛笔、砚台、墨块三样东西写成的。所以你必须要替我到灵谷洞找到这三样东西。但是那地方很危险，我想你最好还是找些人陪一起你去。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if (who->get_legend(TASK_27,12) && !who->get_legend(TASK_27,13))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你连那三样东西都找不回来的话我根本没兴趣告诉你想要找的东西在哪里。\n"ESC"离开", me->get_name()));
        	else if (who->get_legend(TASK_27,13) && !who->get_legend(TASK_27,14))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不错，你经得起这样的考验足够证明你是一个有能力的人了。既然你是有能力的人，我就告诉你你要找的东西的所在吧。拿好这封信，回去好好琢磨一下你就明白了。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
        case 2:
        	if ( who->get_legend(TASK_27,10) && !who->get_legend(TASK_27,11) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_27,11);
			who->add_exp(24000);
			who->add_potential(420);
			who->add_cash(22000);
			send_user(who,"%c%s",';',"同心锁（1） 经验 24000 潜能 420 金钱 22000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,42,"" );
			me->do_welcome(1);
        	}
        	break;
	case 3:
        	if( who->get_legend(TASK_27,11) && !who->get_legend(TASK_27,12) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_27,12);
        		who->delete_save_2("yzgmaobi");
        		who->delete_save_2("yzgyantai");
        		who->delete_save_2("yzgmokuai");
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,37,"同心锁（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"同心锁（2）");
        	}
        	break;   
        case 4:
        	if ( who->get_legend(TASK_27,13) && !who->get_legend(TASK_27,14) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"毛笔",1) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"砚台",1) != 1 )
        		{
        			item = new("item/98/0127");
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			return;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"墨块",1) != 1 )
			{
        			item = new("item/98/0127");
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			item = new("item/98/0128");
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			return;
        		}		        			
			item = new("item/98/0130");
			p = item->move(who,-1);
			item->add_to_user(p);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_27,14);
        		who->delete_save_2("yzgmaobi");
        		who->delete_save_2("yzgyantai");
        		who->delete_save_2("yzgmokuai");
			who->add_exp(26000);
			who->add_potential(450);
			who->add_cash(25000);
			send_user(who,"%c%s",';',"同心锁（2） 经验 26000 潜能 450 金钱 25000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,38,"燕王爱珍玩（3）" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,37,"" );
			me->do_welcome(1);
        	}
        	break;
        case 5:
        	if ( who->get_legend(TASK_32,9) && !who->get_legend(TASK_32,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，知我心者，赵管家也，老夫真是多谢了，今后他但凡有事，老夫必定义不容辞。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 6:
        	if ( who->get_legend(TASK_32,9) && !who->get_legend(TASK_32,10) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"论语",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_32,10);
			who->add_exp(58000);
			who->add_potential(850);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"论语 经验 58000 潜能 850 金钱 50000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,56,"" );
        	}
        	break;
        case 7:
        	if ( who->get_level() >= 40 && who->get_legend(TASK_38,1) && !who->get_legend(TASK_38,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我还以为他只是不想卖给我，没想到是这个原因，快把葡萄拿来给我尝尝。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
        case 8:
        	if ( who->get_level() >= 40 && who->get_legend(TASK_38,1) && !who->get_legend(TASK_38,2) )
		{
        		if (TASK_LEGEND_D->check_task_item(who,"紫葡萄",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_38,2);
			who->add_exp(4000);
			who->add_potential(130);
			who->add_cash(4000);
			send_user(who,"%c%s",';',"紫葡萄 经验 4000 潜能 130 金钱 4000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,90,"" );
        	}       		
        	break;
        }
}
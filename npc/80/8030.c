
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
int get_char_picid() { return 5505; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Mạnh Cầu");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",27);
//	set("legend",({32*7+1}));
 	set("mpLegend",([25:({32*7+1}),]));
 	set("mpLegend2",([0:({32*35+4,}),25:({32*7+3,32*7+9,}),]));
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
	if ( ( who->get_level() >= 25 && !who->get_legend(TASK_07,1) ) || ( who->get_legend(TASK_07,1) && !who->get_legend(TASK_07,3) ) )
		tmp += sprintf(ESC HIY "好朋友\ntalk %x# welcome.1\n",getoid(this_object()));
	if (  who->get_legend(TASK_07,3) && !who->get_legend(TASK_07,9)  )
		tmp += sprintf(ESC HIY "去燕的盘缠\ntalk %x# welcome.1\n",getoid(this_object()));
	if (  who->get_legend(TASK_35,3) && !who->get_legend(TASK_35,4)  )
		tmp += sprintf(ESC HIY "探访奇事\ntalk %x# welcome.6\n",getoid(this_object()));
	if (  who->get_legend(TASK_35,4) && !who->get_legend(TASK_35,5)  )
		tmp += sprintf(ESC HIY "询问情况\ntalk %x# welcome.6\n",getoid(this_object()));

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
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_07,1)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿，告诉你一个好消息，我将去拜访Yên Quốc的丁鹤年，这可是我朝思暮想了很久的事情！\n    Yên Quốc的丁鹤年是一个非常不错的人，我们神交已久，我对他的才学更是羡慕不已，从与他的书信往来中得知他就居住在Yên Quốc城内，一直想去拜访他，可从我这到Yên Quốc路途遥远，而我这家境……唉，不提也罢。最近想去拜访他的念头越来越强烈，苦于没有一件象样的礼物能拿得出手。\n    我听说易水的Yên Quốc巡逻兵爱喝酒，储藏了一批女儿红，你帮我这个忙，去那边给我找10坛来吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_07,1) && !who->get_legend(TASK_07,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，如果还不能找到女儿红，估计我不能去拜访丁兄了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_07,2) && !who->get_legend(TASK_07,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你已经给我找来了女儿红，实在是万分感谢！我现在终于有礼物送给丁兄了，与丁兄把酒言欢是一件多么惬意的事情啊！\n    可我算了下帐，我准备的盘缠似乎有些不够，路途遥远，我乃一介书生，如果盘缠花光，莫非要逼得我沿街乞讨？这可万万使不得！\n    我平日里就与Ngụy Quốc百姓乐羊比较交好，他现在居住在魏城内，你可否替我去找他借点盘缠，我从燕回来就还给他！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_07,3) && !who->get_legend(TASK_07,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你给我找来了女儿红，我终于有礼物送给丁兄了，可想了想，我的盘缠似乎不够，这可如何是好！平日里就与Ngụy Quốc百姓比较交好，他现在居住在魏城内，你可否替我去找他借点盘缠，我从燕回来就还给他！\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_07,4) && !who->get_legend(TASK_07,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    盘缠要到了吗？你可得快点啊，别担搁了我的行程。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_07,8) && !who->get_legend(TASK_07,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    其实我也知道Ngụy Quốc百姓乐羊条件不怎么样，但是他的生活能力比我强，他总是知道怎样过好日子，所以我才叫你去找他，这不，这么快你就给把我盘缠带来了！\n    这次真是太感谢你了，我终于能去拜访丁兄了。我马上就写信告诉丁兄这个好消息，我想他肯定也非常高兴！\n    等我从Yên Quốc回来，我会自己将钱还给孟求的。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));	
        	break;
        case 2:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_07,1)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,1);
        		who->delete_save_2("haopengyou");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,4,"送给丁兄的酒" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"送给丁兄的酒");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_07,2) && !who->get_legend(TASK_07,3) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"女儿红",10) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,3);
			who->delete_save_2("haopengyou");
			who->add_exp(1500);
			who->add_potential(30);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"送给丁兄的酒 经验 1500 潜能 30 金钱 1200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,4,"" );
			me->do_welcome(1);
        	}
        	break;
	case 4:
        	if ( who->get_legend(TASK_07,3) && !who->get_legend(TASK_07,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,5,"去燕的盘缠" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"去燕的盘缠");
        	}
        	break;
	case 5:
        	if ( who->get_legend(TASK_07,8) && !who->get_legend(TASK_07,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"盘缠",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,9);
			who->add_exp(5000);
			who->add_potential(160);
			who->add_cash(4000);
			send_user(who,"%c%s",';',"返还盘缠 经验 5000 潜能 160 金钱 4000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,5,"" );
        	}
        	break;
        case 6:
		if (  who->get_legend(TASK_35,3) && !who->get_legend(TASK_35,4)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，居然都惊动了总管大人了？哎，这可如何是好。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));	
		else if (  who->get_legend(TASK_35,4) && !who->get_legend(TASK_35,5)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近镇上百姓经常的牲口和贴身事物经常莫名其妙丢失，有些牲口还居然又突然出现在其他人的圈里或者贴身事物出现在邻居的房间，这么诡异的事情搞得我们都疑神疑鬼，苦不堪言，镇口的周童对于这些事情知道得更详细一些，你再去问问他吧。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));	

		break;
	case 7:
        	if (  who->get_legend(TASK_35,3) && !who->get_legend(TASK_35,4)  )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,4);
			who->add_exp(77000);
			who->add_potential(990);
			who->add_cash(69000);
			send_user(who,"%c%s",';',"探访奇事 经验 77000 潜能 990 金钱 69000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,52,"" );
			me->do_welcome(6);
        	}
        	break;	        	
        case 8:
        	if (  who->get_legend(TASK_35,4) && !who->get_legend(TASK_35,5)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,5);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,53,"询问情况" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询问情况");
        	}
        	break;
        }

}


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
int get_char_picid() { return 5501; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chu Đồng");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",26);
//	set("legend",({32*6+25}));
 	set("mpLegend",([25:({32*6+25}),]));
 	set("mpLegend2",([0:({32*35+6,32*35+9,32*35+12,}),25:({32*6+27}),]));
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
	if ( ( who->get_level() >= 25 && !who->get_legend(TASK_06,25) ) || ( who->get_legend(TASK_06,25) && !who->get_legend(TASK_06,27) ) )
		tmp += sprintf(ESC HIY "罪恶的土匪\ntalk %x# welcome.1\n",getoid(this_object()));
	if (  who->get_legend(TASK_35,5) && !who->get_legend(TASK_35,6)  )
		tmp += sprintf(ESC HIY "询问情况\ntalk %x# welcome.4\n",getoid(this_object()));
	if (  (who->get_legend(TASK_35,6) && !who->get_legend(TASK_35,7)) || (who->get_legend(TASK_35,7) && !who->get_legend(TASK_35,9)) )
		tmp += sprintf(ESC HIY "试练身手\ntalk %x# welcome.4\n",getoid(this_object()));
	if (  (who->get_legend(TASK_35,9) && !who->get_legend(TASK_35,10)) || (who->get_legend(TASK_35,10) && !who->get_legend(TASK_35,12)) )
		tmp += sprintf(ESC HIY "追杀贼匪\ntalk %x# welcome.4\n",getoid(this_object()));
	if (  who->get_legend(TASK_35,12) && !who->get_legend(TASK_35,13)  )
		tmp += sprintf(ESC HIY "解除奇事\ntalk %x# welcome.4\n",getoid(this_object()));

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
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,25)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本来我还打算叫爹带我出去玩，可昨天家里来了群土匪，把我家洗劫一空不说，还打了我爹，爹寡不敌众，现在伤得很严重，根本就起不了床！\n    我要给我爹报仇，可是我太小，所以只能请你帮忙，我记得那群土匪是15个人，你能给我去教训他们吗？\n    他们就聚集在牧野一带，你从我这里过去，穿过桂陵就到牧野了。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,25) && !who->get_legend(TASK_06,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    连你都不能消灭他们，看来我爹的仇报不了啦！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,26) && !who->get_legend(TASK_06,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你真是侠义之士！我长大了也要做像你一样的人。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,25)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,25);
        		who->delete_save_2("zuietufei");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,2,"罪恶的土匪" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"罪恶的土匪");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_06,26) && !who->get_legend(TASK_06,27) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/65014",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,27);
			who->delete_save_2("zuietufei");
			who->add_exp(1800);
			who->add_potential(70);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"罪恶的土匪 经验 1800 潜能 70 金钱 1200 金项链图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,2,"" );
        	}
        	break;
        case 4:
		if (  who->get_legend(TASK_35,5) && !who->get_legend(TASK_35,6)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这件事情的确透着奇怪，如果是偷，怎么有的牲口又会出现在其他人的圈里，有的贴身事物又出现在邻人的房间中，如果说牲口能卖钱，那么那些贴身事物估计没有什么卖头吧，莫非谁有什么特殊收集的嗜好，况且这么多牲口，居然能够做到毫无生息，那些贴身事物更是人都不离身的，如何能够得手？这些事情说不是神仙妖怪做的还真的不敢相信，不过这么多日琢磨我也有点头绪了，就不知道你肯不肯听我的。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));	
		else if (  who->get_legend(TASK_35,6) && !who->get_legend(TASK_35,7)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我似乎看到了水精和火精的身影，你去玄真洞杀掉30个水精和30个火精给我看看，结果如何就让我们拭目以待。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));	
		else if (  who->get_legend(TASK_35,7) && !who->get_legend(TASK_35,8)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，你不想调查这件事了么？这是我现在想出的唯一线索。\n"ESC"离开", me->get_name()));	
		else if (  who->get_legend(TASK_35,8) && !who->get_legend(TASK_35,9)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，让我们这两天再观察观察。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));	
		else if (  who->get_legend(TASK_35,9) && !who->get_legend(TASK_35,10)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    火精和水精一下子减少了不少数量，我猜有可能是他们的幕后人出现了，我昨天晚上一直埋伏在牲口圈周围，发现了贼匪石大龙的踪迹，很有可能这一系列案件都是他一手做的，我后来跟踪他到了玄真洞北部，不过我不是他的对手不敢轻举妄动，你去那里将他干掉应该我们村庄的这些怪事就会消失了吧。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));	
		else if (  who->get_legend(TASK_35,10) && !who->get_legend(TASK_35,11)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你也不是对手？这可如何是好？\n"ESC"离开", me->get_name()));	
		else if (  who->get_legend(TASK_35,11) && !who->get_legend(TASK_35,12)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好样的，看来我们可有一段安宁日子过了。\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));	
		else if (  who->get_legend(TASK_35,12) && !who->get_legend(TASK_35,13)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    虽然石大龙死无对证，不知道当初他是如何能够无声无息间做到这么多事情的，但是好歹现在小镇又恢复了祥和安宁，你代我回禀御史，让他宽心了。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));	

		break;
	case 5:
        	if (  who->get_legend(TASK_35,5) && !who->get_legend(TASK_35,6)  )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,6);
			who->add_exp(76000);
			who->add_potential(1100);
			who->add_cash(68000);
			send_user(who,"%c%s",';',"询问情况 经验 76000 潜能 1100 金钱 68000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,53,"" );
			me->do_welcome(4);
        	}
        	break;	        	
        case 6:
        	if (  who->get_legend(TASK_35,6) && !who->get_legend(TASK_35,7)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,7);
        		who->delete_save("ztsuijing");
        		who->delete_save("zthuojing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,54,"试练身手" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"试练身手");
        	}
        	break;
	case 7:
        	if (  who->get_legend(TASK_35,8) && !who->get_legend(TASK_35,9)  )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,9);
        		who->delete_save("ztsuijing");
        		who->delete_save("zthuojing");
			who->add_exp(78000);
			who->add_potential(1000);
			who->add_cash(65000);
			send_user(who,"%c%s",';',"试练身手 经验 78000 潜能 1000 金钱 65000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,54,"" );
			me->do_welcome(4);
        	}
        	break;
        case 8:
        	if (  who->get_legend(TASK_35,9) && !who->get_legend(TASK_35,10)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,55,"追杀贼匪" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"追杀贼匪");
        	}
        	break;
	case 9:
        	if (  who->get_legend(TASK_35,11) && !who->get_legend(TASK_35,12)  )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/final/15/1523",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,12);
			who->add_exp(79000);
			who->add_potential(1050);
			who->add_cash(67000);
			send_user(who,"%c%s",';',"追杀贼匪 经验 79000 潜能 1050 金钱 67000 强效法攻 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,55,"" );
			me->do_welcome(4);
        	}
        	break;
        case 10:
        	if (  who->get_legend(TASK_35,12) && !who->get_legend(TASK_35,13)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,56,"解除奇事" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"解除奇事");
        	}
        	break;
        }
}

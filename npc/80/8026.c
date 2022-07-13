
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
int get_char_picid() { return 5801; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Lí Đại Mao");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));
	set("mpLegend2",([0:({32*19+2,32*19+5,}),]));
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
	if ( who->get_legend(TASK_19,1) && !who->get_legend(TASK_19,2) )
		tmp += sprintf(ESC HIY "寻找大葫芦种子\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( (who->get_legend(TASK_19,2) && !who->get_legend(TASK_19,3)) || (who->get_legend(TASK_19,3) && !who->get_legend(TASK_19,5)) )
		tmp += sprintf(ESC HIY "何首乌\ntalk %x# welcome.1\n",getoid(this_object()));

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
        	if ( who->get_legend(TASK_19,1) && !who->get_legend(TASK_19,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此种子何等珍贵，我可不愿这样送人，若你想得到，需替我办件事。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_19,2) && !who->get_legend(TASK_19,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这个种子可是我求仙人才求到的，当初我求的是长生不老药他不肯给，听过易水的白鹭村有人形何首乌，磨粉服用可以长生不老，如果你能给我找来我就送个种子给你。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_19,3) && !who->get_legend(TASK_19,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果拿不来何首乌，这大葫芦种子我可不会送给你。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_19,4) && !who->get_legend(TASK_19,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，真是傻瓜，拿可以长生不老的人形何首乌换个好看不中用的大葫芦种子，真是傻的可爱啊！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_legend(TASK_19,1) && !who->get_legend(TASK_19,2) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,2);
			who->add_exp(3800);
			who->add_potential(165);
			who->add_cash(3550);
			send_user(who,"%c%s",';',"大葫芦（1） 经验 3800 潜能 165 金钱 3550");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,54,"" );
			me->do_welcome(1);
       		}
        	break;
	case 3:
        	if ( who->get_legend(TASK_19,2) && !who->get_legend(TASK_19,3) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_19,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,27,"大葫芦（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"大葫芦（2）");
        	}
        	break;      
        case 4:
        	if ( who->get_legend(TASK_19,4) && !who->get_legend(TASK_19,5) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"何首乌",1) != 1 )
        			return;
        		item = new("item/98/0084");
        		if ( !item )
        			return ;
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			send_user(who,"%c%s",'!', "你携带的物品太多了");	
        			destruct(item);
        			return;
        		}
        		item->add_to_user(p);
			who->set_legend(TASK_19,5);
			who->add_exp(3830);
			who->add_potential(165);
			who->add_cash(3500);
			send_user(who,"%c%s",';',"大葫芦（2） 经验 3830 潜能 165 金钱 3500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,27,"" );
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,10,"大葫芦（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"大葫芦（3）");
       		}
        	break;
        }
}
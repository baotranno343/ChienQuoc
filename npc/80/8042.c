
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_welcome(string arg);

//void do_task_finish();
int get_char_picid() { return 5501; }
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
// 函数：构造处理
void create()
{
        set_name("Tôn Lục");
        set_city_name("Sở Quốc");

	set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
//	set("level",11);
//	set("legend",({32*3+3,}));
	set("mpLegend",([10:({32*3+3}),]));
	set("mpLegend2",([10:({32*3+4}),]));
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
	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,4) )
		tmp += sprintf(ESC HIY "心上人的礼物\ntalk %x# welcome.1\n",getoid(this_object()));
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
        	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,3) )
        		send_user(who,"%c%s",':',sprintf("%s:\n    呜……呜……呜！没天理呀！难道要我单身一辈子？\n    前些日子我准备向酒店老板的女儿求婚，买了一串珍珠项链做定婚礼物。可是在经过桃花源时被一群可恶的独角仙抢走了，你去给我找回来吧！我敢肯定，那串项链绝对挂在某只独角仙的身上。我的终身幸福就握在你的手中，一定要帮我夺回定婚礼物呀！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
        	else if( objectp( item=present("珍珠项链", who, 1, MAX_CARRY) ) && item->is_xianglian() == 1 )
        		send_user(who,"%c%s",':',sprintf("%s:\n    找回来了！太好了，这下我的后半生不再孤独了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),getoid(me)));
		else
        		send_user(who,"%c%s",':',sprintf("%s:\n    唉，人算不如天算，看来我和她是有缘无份啊！\n"ESC"离开",me->get_name()));
        	break;
        case 2:
        	if( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,3) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,2,"心上人的礼物" );	
        		who->set_legend(TASK_NEWBIE_03,3);
        		send_user( who, "%c%s", '!', "得到任务 "HIY"心上人的礼物");
        	}
        	break;
        case 3:
        	if( !who->get_legend(TASK_NEWBIE_03,4) && objectp( item=present("珍珠项链", who, 1, MAX_CARRY) ) && item->is_xianglian() == 1 )
        	{
        		item->remove_from_user();
        		destruct(item);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03, 4);
			who->add_exp(320);
			who->add_potential(40);
			who->add_cash(1000);
			send_user(who,"%c%s",';',"心上人的礼物 经验 320 潜能 40 金钱 1000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,2,"" );	        			
        	}
        }
}
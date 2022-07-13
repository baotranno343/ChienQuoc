
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
int get_char_picid() { return 5805; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Triệu Mộc");
        set_city_name("Hàn Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
//	set("level",78);
//	set("legend",({32*25+29}));
 	set("mpLegend",([75:({32*25+29})]));
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
	if ( who->get_level() >=75 && !who->get_legend(TASK_25,29) )
		tmp += sprintf(ESC HIY "内政官的心事\ntalk %x# welcome.1\n",getoid(me));
			
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
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_25,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近我们在襄陵道猎到的小动物都好像有点不正常，后来我们发现是襄陵道那条河的河水出了问题，现在我们都不敢用那条河的河水了。但是那条河的河水是我们生活用水的主要来源呀，你能帮我们把这件事汇报给Hàn Quốc的内政官，让他去处理一下这件事吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_25,29) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_25,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,26,"内政官的心事" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"内政官的心事");
        	}
        	break;
        case 21:
        case 22:
        	TASK_ESCORT_D->biaowang(me,who,flag);
        	break;
	}
}
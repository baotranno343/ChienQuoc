
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
int get_char_picid() { return 5601; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Trình Lâm Khai");
        set_city_name("Ngụy Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
//	set("level",91);
//	set("legend",({32*31+16}));
 	set("mpLegend",([90:({32*31+16}),]));

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
	if ( who->get_level() >=90 && !who->get_legend(TASK_31,16) )
	{
		tmp += sprintf(ESC HIY "无人知晓的秘密\ntalk %x# welcome.1\n",getoid(me));
	}

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
        	if ( who->get_level() >=90 && !who->get_legend(TASK_31,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呃……这个秘密，我是准备将它深深地埋在心底，再也不拿出来见人，可最近听说一些奇怪的事情，那些……我估计它们是受人控制的，这件事，还想请你去一趟Yên Quốc，找程风谈谈。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >=90 && !who->get_legend(TASK_31,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,36,"秘密（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"秘密（1）");
        	}
        	break;
        case 21:
        case 22:
        	TASK_ESCORT_D->biaowang(me,who,flag);
        }
}

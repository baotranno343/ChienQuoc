
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
int get_char_picid() { return 0052; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Bành Tiêm Hào");
        set_city_name("Tần Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",40);
//	set("legend",({32*10+14}));
	set("mpLegend",([40:({32*10+14})]));
	set("mpLegend2",([40:({32*10+16,}),]));
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
	if ( ( who->get_level() >= 40 && !who->get_legend(TASK_10,14) ) || ( who->get_legend(TASK_10,14) && !who->get_legend(TASK_10,16) ) )
		tmp += sprintf(ESC HIY "狩猎计划\ntalk %x# welcome.1\n",getoid(me));
			
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
        	if ( who->get_level() >= 40 && !who->get_legend(TASK_10,14)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在可是狩猎的好季节。\n    我是一个猎人，我的生活来源就是靠打来的猎物换钱，每次到了狩猎的旺季，家里的情况就会宽裕很多，每年我都盼着这个时候呢！\n    我看你也是个习武之人，最近在东海渔村一带的虾兵蟹将也多了起来，你要是有兴趣的话，就去猎杀20只虾兵20只蟹将吧。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,14) && !who->get_legend(TASK_10,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    狩猎的好时机呀！如果不抓紧时间，可就没这么好的机会喽！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_10,15) && !who->get_legend(TASK_10,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你果然是个好猎手！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 40 && !who->get_legend(TASK_10,14)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,14);
        		who->delete_save_2("slxiabing");
        		who->delete_save_2("slxiejiang");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,16,"狩猎计划" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"狩猎计划");
        	}
        	break;
       case 3:
        	if ( who->get_legend(TASK_10,15) && !who->get_legend(TASK_10,16) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_10,16);
        		who->delete_save_2("slxiabing");
        		who->delete_save_2("slxiejiang");
			who->add_exp(4500);
			who->add_potential(130);
			who->add_cash(3200);
			send_user(who,"%c%s",';',"狩猎计划 经验 4500 潜能 130 金钱 3200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,16,"" );
        	}
        	break;        
        }
}
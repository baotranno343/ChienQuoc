
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
        set_name("Thôi Ngọc");
        set_city_name("Tề Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",103);
//	set("legend",({32*37+1}));
 	set("mpLegend",([100:({32*37+1})]));
 	set("mpLegend2",([100:({32*37+3})]));
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
	if ( ( who->get_level() >= 100 && !who->get_legend(TASK_37,1) ) || ( who->get_legend(TASK_37,1) && !who->get_legend(TASK_37,3) ) )
		tmp += sprintf(ESC HIY "攻破天门阵\ntalk %x# welcome.1\n",getoid(this_object()));

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
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_37,1)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我们跑镖的就怕路过天门阵，里面的守卫很厉害，硬闯根本没有几人通的过，使得我们每次跑镖都要绕远路，白白浪费好多时间，我们的雇主也有很大意见，听说大侠乃人中龙凤，Quốc之翘楚，可否为我等清理出一条通道来，就最近那条路消灭天罡门众守4个、守阵天兵3个、神将4个就可以勉强过镖了，崔某多谢了。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_37,1) && !who->get_legend(TASK_37,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，看来我们要继续绕远路了……\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_37,2) && !who->get_legend(TASK_37,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，大侠果然名副其实，小小匪类还不是手到擒来。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_37,1)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_37,1);
        		who->delete_save("cytiangmzs");
        		who->delete_save("cysouztb");
        		who->delete_save("cysouzsj");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,59,"攻破天门阵" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"攻破天门阵");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_37,2) && !who->get_legend(TASK_37,3) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_37,3);
        		who->delete_save("cytiangmzs");
        		who->delete_save("cysouztb");
        		who->delete_save("cysouzsj");
       			who->add_exp(80000);
			who->add_potential(960);
			who->add_cash(70000);
			send_user(who,"%c%s",';',"攻破天门阵 经验 80000 潜能 960 金钱 70000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,59,"" );
        	}
        	break;
 
        }
}
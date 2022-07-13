
// 自动生成：/make/npc/make-biao
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();
void do_welcome(string arg);

//void do_task_finish();
int get_char_picid() { return 5805; }
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});

// 函数：构造处理
void create()
{
        set_name("Mã Đại Hán");
        set_city_name("Hàn Quốc");
	set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
/*      set_2( "talk", ([
                "task"          : (: do_task_start :),
                "cancel"        : (: do_task_cancel :),
        ]));    */

        setup();
}

// 函数：对话处理
// void do_look( object who ) { TASK_ESCORT_D->do_look( who, this_object() ); }
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
	if ( who->get_level()>=30 && who->get_legend(TASK_49,13) && !who->get_legend(TASK_49,14) && gone_time( who->get_quest("escort.time") ) < 2400 )
		tmp += sprintf(ESC HIY "一探虚实\ntalk %x# welcome.1\n",getoid(this_object()));
	if ( who->get_level()>=30 && who->get_legend(TASK_49,13) && !who->get_legend(TASK_49,14) && gone_time( who->get_quest("escort.time") ) > 2400 )
		tmp += sprintf(ESC"一探虚实\ntalk %x# welcome.3\n",getoid(this_object()));
	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
			+ tmp +
			ESC"离开"
			);

}

// 函数：开始任务
// void do_task_start() { TASK_ESCORT_D->do_task_start( this_player(), this_object() ); }
// 函数：取消任务
// void do_task_cancel() { TASK_ESCORT_D->do_task_cancel( this_player(), this_object() ); }

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag, date , status, p, z, x, y, i,amount,size;
        object who, obj, item,*inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_level()>=30 && who->get_legend(TASK_49,13) && !who->get_legend(TASK_49,14) && gone_time( who->get_quest("escort.time") ) < 2400 )
        		send_user(who,"%c%s",':',sprintf("%s:\n    你总算是成功通过了尉迟老镖头的测试，现在你可以去找他运镖了，我想他会很乐意提供这个机会给你的！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
        	break;
        case 2:
		if ( who->get_level()>=30 && who->get_legend(TASK_49,13) && !who->get_legend(TASK_49,14) && gone_time( who->get_quest("escort.time") ) < 2400 )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"贵重物品",1) != 1 )
        			return;
                        who->delete_quest("escort.flag");
                        who->delete_quest("escort.leader");
                        who->delete_quest("escort.time");
                        who->delete_quest("escort.name");
                        who->delete_quest("escort.escort");
                        who->delete_quest("escort.npc");

                        who->delete_quest("escort.id");
                        who->delete_quest("escort.member");

                        who->delete_quest("escort.random");
                        who->delete_quest("escort.robber");
                        who->delete_quest("escort.robber#");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_49,14);
			who->add_cash(60000);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,15,"" );	        			
			send_user(who,"%c%s",';',"一探虚实 金钱 60000");
        	}
        	break;
        case 3:
		if ( who->get_level()>=30 && who->get_legend(TASK_49,13) && !who->get_legend(TASK_49,14) && gone_time( who->get_quest("escort.time") ) > 2400 )
        		send_user(who,"%c%s",':',sprintf("%s:\n    你已经超过了预定时间，运镖任务失败了。请放弃任务后，重新领取，我想尉迟老镖头会很乐意再给你机会的！\n"ESC"离开",me->get_name(),getoid(me)));
        	break;   
        }
}
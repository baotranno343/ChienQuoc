
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5401; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Yên Quản Gia");
        set_city_name("Yên Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
//	set("level",49);
//	set("legend",({32*13+1}));
	set("mpLegend",([45:({32*13+1}),]));
	set("mpLegend2",([45:({32*13+3}),]));
        setup();
}

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
	if ( ( who->get_level() >= 45 && !who->get_legend(TASK_13,1) ) || ( who->get_legend(TASK_13,1) && !who->get_legend(TASK_13,3) ) )
		tmp += sprintf(ESC HIY "心事重重\ntalk %x# welcome.1\n",getoid(me));
			
	send_user(who,"%c%s",':',sprintf( "%s：\n    周Quốc的京都镖局尉迟老镖头武艺高强，生性豪爽，真是一条好汉！\n", get_name(),  ) 
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
        	if ( who->get_level() >= 45 && !who->get_legend(TASK_13,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可坏了大事了，我把进贡燕王喜的宝物给弄丢了，这可是杀头大罪，这可如何是好啊！\n    我记得我从郑Quốc渠回来后就没看见了，当时还回去细细找了，可就是没找到，但是我也不能放过最后一丝希望，你去替我找找吧，那宝物叫碧龙球！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_13,1) && !who->get_legend(TASK_13,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下我心里可真是难受啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_13,2) && !who->get_legend(TASK_13,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下我悬着的心，总算是放下来了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >=45 && !who->get_legend(TASK_13,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,11,"心事重重" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"心事重重");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_13,2) && !who->get_legend(TASK_13,3) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"碧龙球",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,3);
			who->add_exp(5400);
			who->add_potential(190);
			who->add_cash(4900);
			send_user(who,"%c%s",';',"心事重重 经验 5400 潜能 190 金钱 4900");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,11,"" );
        	}
        	break;   
        }
}
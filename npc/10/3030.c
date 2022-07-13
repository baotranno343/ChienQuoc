
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 5401; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Ngọc Khí Thương");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*28+30,32*29+25,})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( who->get_legend(TASK_28,29) && !who->get_legend(TASK_28,30) ) 
		tmp += sprintf(ESC HIY "询问原因\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_28,30) && !who->get_legend(TASK_29,16) ) 
		tmp += sprintf(ESC HIY "打听消息\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_29,24) && !who->get_legend(TASK_29,25) ) 
		tmp += sprintf(ESC HIY "寻找宝物\ntalk %x# welcome.1\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0921))
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
        	if ( who->get_legend(TASK_28,29) && !who->get_legend(TASK_28,30) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，玉器就仿佛我的生命，而我苦恼也就是玉器的事情啊。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_28,29) && !who->get_legend(TASK_29,16) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我一生浸淫珠宝玉器，看过美玉不知凡几，但是传说中的稀世宝玉我却缘悭一面，惊鸿一瞥便再也难觅踪迹，我只想拥有他我就此生无憾了，但是山海茫茫，我的稀世宝玉到底藏身何处了呢，哎……听说齐总管见多识广，但是他似乎却不宵与同商人来往，只得拜托了你了。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_29,24) && !who->get_legend(TASK_29,25) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈……我终于梦想成真了！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));

	    	break;
        case 2:
        	if ( who->get_legend(TASK_28,29) && !who->get_legend(TASK_28,30) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,30);
			who->add_exp(48000);
			who->add_potential(680);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"询问原因 经验 48000 潜能 680 金钱 50000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,25,"" );
			me->do_welcome(1);
        	}
        	break;   
	case 3:
        	if ( who->get_legend(TASK_28,29) && !who->get_legend(TASK_29,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,26,"打听消息" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"打听消息");
        	}
        	break;  
        case 4:
        	if ( who->get_legend(TASK_29,24) && !who->get_legend(TASK_29,25) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"稀世宝玉",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/final/33/1775",5);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,25);
			who->add_exp(55000);
			who->add_potential(730);
			who->add_cash(52000);
			send_user(who,"%c%s",';',"寻找宝物 经验 55000 潜能 730 金钱 52000 神秘老火汤 5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,29,"" );
        	}
        	break; 
        }
}
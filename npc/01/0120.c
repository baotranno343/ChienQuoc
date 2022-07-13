
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5802; }

// 函数：构造处理
void create()
{
        set_name( "Hoàng Đại Thúc" );

        set_2( "talk", ([
                "welcome"         : (: do_welcome :),
        ]));

//        set("level", 8);
//        set("legend", ({ 32*2+28 }));
//	set("mpLegend",([5:({32*2+28,}),]));
        setup();
        if( !clonep(this_object()) ) return;
	"npc/task/0101"->create_npc();
}

// 函数：对话处理
void do_look( object who )
{
        string tmp="";

//	if ( who->get_level() >=5 && !who->get_legend(TASK_NEWBIE_02, 30) )
//		tmp = sprintf(ESC"正义之战\ntalk %x# welcome.1\n",getoid(this_object()));
        tmp += CHAIN_D->get_chain_menu(who,this_object());
	send_user(who,"%c%s",':',get_name()+":\n    在这坐了一天，也没钓上几条鱼，可能和季节有关吧，明天再来试试。\n"+tmp+ESC"离开");
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag;
	object who;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
//        switch(flag)
//        {
//	case 1:
//		if ( who->get_level() >=5 &&!who->get_legend(TASK_NEWBIE_02, 28) )
//			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    如果你是正义之士，那么，属于你的时刻到来了！别以为我每天无所事事的在这钓鱼，其实我是一个密探，奉命秘密探访恶霸李麻子的藏身之处，因身份特殊，自己不好露脸，所以请你帮我这忙，替我把藏身于新手村外蝴蝶岗的恶霸李麻子击毙，我会给你丰厚的报酬。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
//		else if ( who->get_legend(TASK_NEWBIE_02, 28)&&!who->get_legend(TASK_NEWBIE_02, 29) )
//			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    果然是作恶多端的恶霸，你居然不能杀掉他，不过你可以再去试试，或许这次可以成功！\n"ESC"离开",me->get_name()));			
//		else if ( who->get_legend(TASK_NEWBIE_02, 29)&&!who->get_legend(TASK_NEWBIE_02, 30) )
//			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    我果然没有看错人，这么快就替我杀死他了！或许以后你能成为我们的一员，嗯，我记得你了，出色的年轻人！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),getoid(me)));
//		break;
//	case 2:
//		if ( who->get_level() >=5 &&!who->get_legend(TASK_NEWBIE_02, 28) )
//		{	
//			who->set_legend(TASK_NEWBIE_02, 28);
//			//send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
//			//send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,22,"正义之战" ); 
//			send_user( who, "%c%s", '!', "你接受了"HIY"正义之战"NOR"任务");    
//       		}
//		break;
//	case 3:
//		if ( who->get_legend(TASK_NEWBIE_02, 29)&&!who->get_legend(TASK_NEWBIE_02, 30) )
//		{
//			who->set_legend(TASK_NEWBIE_02, 30);
//			who->add_exp(600);
//			who->add_potential(50);
//			who->add_cash(1500);
//			send_user(who,"%c%s",';',"正义之战 经验 600 潜能 50 金钱 1500");
//			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,22,"" );
//		}
//		break;
//	}
}


// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 0250; }

// 函数：构造处理
void create()
{
        set_name("Đổ Đồ Bính");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",32);
//        set("legend",({32*8+19}));
	set("mpLegend",([30:({32*8+19})]));
	set("mpLegend2",([30:({32*8+21,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 30 && !who->get_legend(TASK_08,19)) || (who->get_legend(TASK_08,19)&&!who->get_legend(TASK_08,21)) ) 
		tmp += sprintf(ESC HIY "迷途知返\ntalk %x# welcome.1\n",getoid(this_object())); 
        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0521))
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
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    赌博，是把杀人不见血的刀啊！\n    我迷恋上了赌博，家里的积蓄都被我偷偷的输光了，我头一犯昏将房屋也抵押掉了，现在夫人带着孩子回了娘家，并且表示，如果我不戒赌，就永远不回来了！现在我非常后悔，我发誓不再赌博，只要能找回房屋的抵押契约，我想夫人就会回来了。据说那抵押契约被人弄丢在大别山脚的松子岭，你能帮我寻回来吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_08,19) && !who->get_legend(TASK_08,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呜呜……看来我真的要无家可归了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_08,20) && !who->get_legend(TASK_08,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太感谢你了，我发誓再也不赌博，把自己的田种好。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"楚国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,19,"迷途知返" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"迷途知返");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_08,20) && !who->get_legend(TASK_08,21) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"抵押契约",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/61002",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,21);
			who->add_exp(2500);
			who->add_potential(80);
			who->add_cash(1900);
			send_user(who,"%c%s",';',"迷途知返 经验 2500 潜能 80 金钱 1900 地瓜解暑汤图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,19,"" );
        	}
        	break;   
   
        }
}
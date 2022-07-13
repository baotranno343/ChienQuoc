#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 0601; }

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Võ Sĩ");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",73);
//        set("legend",({32*23+22}));
 	set("mpLegend",([70:({32*23+22,}),]));
 	set("mpLegend2",([70:({32*23+24,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        if ( (who->get_level() >= 70 && !who->get_legend(TASK_23,22)) || (who->get_legend(TASK_23,22)&&!who->get_legend(TASK_23,24)) ) 
		tmp += sprintf(ESC HIY "抓壮丁\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_23,24)&&!who->get_legend(TASK_23,25)) || (who->get_legend(TASK_23,25)&&!who->get_legend(TASK_23,26)) ) 
		tmp += sprintf(ESC HIY "家书\ntalk %x# welcome.1\n",getoid(this_object())); 
		
        send_user( who, "%c%s", ':', sprintf( "%s：\n    跟这里的所有人一样，我的军旅生涯是从被抓壮丁开始的。从我离开村子那天起，我的女人就注定成了活寡妇。\n", get_name())
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
	       	if ( who->get_level() >= 70 && !who->get_legend(TASK_23,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近有一批壮丁在郑国渠发动暴动，大将军命令我们去把这批壮丁杀掉。想我当年也是一个壮丁，我实在不愿意亲手去杀害他们，令这些壮丁与他们的妻子阴阳相隔，但是大将军的命令我又不可以违抗。如果可以的话，你可以代替我去郑国渠杀掉10个壮丁吗？只10个就好了，我想你一定能轻易做到。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_23,22) && !who->get_legend(TASK_23,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果我不服从大将军的命令，我可能会被军法处死，为了她，我现在还不能死。\n"ESC"离开", me->get_name()));
       		else if (who->get_legend(TASK_23,23)&&!who->get_legend(TASK_23,24))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你已经杀掉那里的10个壮丁了吗？看来你还是很强的， 这样我也可以跟大将军交代了，希望那些死去的壮丁们的妻子不要过分伤心就好。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
	       	else if ( who->get_legend(TASK_23,24) && !who->get_legend(TASK_23,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    从军10年，我和我的女人没有再见过一面，脑海里只剩下女人撕碎心扉的哭泣和那张模糊的脸。我忍辱负重，发誓决不让自己死在战场上，因为我在等待荣归故里，和女人团聚的一天。\n    我不识字，不会写信，我的女人寻儿同样目不识丁。我经常叫同营的人帮我写信，尽管我知道寻儿也看不懂，但我只需要她明白我还活着。\n    今天同营的那位经常帮我写信的人告假，只得请你替我找那赵国白易写封信。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_23,25) && !who->get_legend(TASK_23,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    希望你可以尽快帮我找到赵国的白易，让他替我写一封信给寻儿，好让寻儿知道我还活着呀。\n"ESC"离开", me->get_name()));

        	break;
	case 2:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_23,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_23,22);
        		who->delete_save_2("hgwszuangding");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"韩国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,46,"武士的爱情（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"武士的爱情（1）");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_23,23) && !who->get_legend(TASK_23,24) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,24);
        		who->delete_save_2("hgwszuangding");
			who->add_exp(20000);
			who->add_potential(290);
			who->add_cash(20000);
			send_user(who,"%c%s",';',"武士的爱情（1） 经验 20000 潜能 290 金钱 20000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,46,"" );
			me->do_welcome(1);
       		}
        	break;
	case 4:
        	if ( who->get_legend(TASK_23,24) && !who->get_legend(TASK_23,25) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_23,25);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"韩国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,47,"武士的爱情（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"武士的爱情（2）");
        	}
        	break;  
        }
}
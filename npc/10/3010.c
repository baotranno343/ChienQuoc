
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5601; }

// 函数：构造处理
void create()
{
        set_name("Lí Phương Sĩ");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));          
	set("mpLegend2",([0:({32*26+6,32*26+9,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
        tmp += CHAIN_D->get_chain_menu(who,me);
        if ( who->get_legend(TASK_26,5) && !who->get_legend(TASK_26,6) ) 
		tmp += sprintf(ESC HIY "指明方向\ntalk %x# welcome.1\n",getoid(me)); 
        if ( (who->get_legend(TASK_26,6) && !who->get_legend(TASK_26,7)) || (who->get_legend(TASK_26,7) && !who->get_legend(TASK_26,9)) ) 
		tmp += sprintf(ESC HIY "最后的考验\ntalk %x# welcome.1\n",getoid(me)); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0301))
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
	       	if ( who->get_legend(TASK_26,5) && !who->get_legend(TASK_26,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你终于来了，不必担心，其实师父在十年前就已经算到韩国会有今天的劫数，所以在他仙逝之前已经把那套解除诅咒的方法教给了我！但是在我施展法术解除诅咒的时候我还需要你的帮助。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
	       	else if ( who->get_legend(TASK_26,6) && !who->get_legend(TASK_26,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    其实令到河水受诅咒的源头是灵谷洞三层的僵尸和疫鬼。所以在我施法解除河水的诅咒的同时，必须有一个武艺高强的人替我去灵谷洞的三层去杀掉这些诅咒河水的源头。我看你是个武艺高强的人，我现在就要施法解咒了，你也赶快去灵谷洞的三层杀掉30个僵尸和30个疫鬼，当你顺利杀掉这些诅咒的源头的时候，我的法事应该也做完了，到时候你就回来我这里吧。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
	       	else if ( who->get_legend(TASK_26,7) && !who->get_legend(TASK_26,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来你还是不行啊！\n    我已经在作法了，你也赶快去杀掉那些僵尸和疫鬼吧！想要解除河水的诅咒没有了你的帮助不行。\n"ESC"离开", me->get_name()));
	       	else if ( who->get_legend(TASK_26,8) && !who->get_legend(TASK_26,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵??????你可回来了，你看，河水已经恢复成原来的样子了，现在我们的百姓们也终于又可以像往常一样使用这条河的河水了。那边是韩王安送给你的礼物，我已经替你收下了。你就拿去吧。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if ( who->get_legend(TASK_26,5) && !who->get_legend(TASK_26,6) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,6);
			who->add_exp(37000);
			who->add_potential(550);
			who->add_cash(38000);
			send_user(who,"%c%s",';',"指明方向 经验 37000 潜能 550 金钱 38000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,29,"" );
			me->do_welcome(1);
        	}
        	break;     
	case 3:
        	if( who->get_legend(TASK_26,6) && !who->get_legend(TASK_26,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_26,7);
        		who->delete_save_2("lfsjiangsi");
        		who->delete_save_2("lfsyigui");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"韩国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,30,"最后的考验" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"最后的考验");
        	}
        	break;
	case 4:
        	if ( who->get_legend(TASK_26,8) && !who->get_legend(TASK_26,9) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->task_finish(who);
        		TASK_LEGEND_D->give_item(who,"item/product/61015",1);
        		who->set_legend(TASK_26,9);
        		who->delete_save_2("lfsjiangsi");
        		who->delete_save_2("lfsyigui");
			who->add_exp(38000);
			who->add_potential(550);
			who->add_cash(37000);
			send_user(who,"%c%s",';',"最后的考验 经验 38000 潜能 550 金钱 37000 杜康酒图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,30,"" );
        	}
        	break;   
        }
}  

// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5901; }

// 函数：构造处理
void create()
{
        set_name("Cổ Đồng Thương");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",51);
//        set("legend",({32*13+22}));
	set("mpLegend",([50:({32*13+22}),]));
	set("mpLegend2",([50:({32*13+24}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 50 && !who->get_legend(TASK_13,22)) || (who->get_legend(TASK_13,22)&&!who->get_legend(TASK_13,24)) ) 
		tmp += sprintf(ESC HIY "泥雕\ntalk %x# welcome.1\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    说起辨认古董，这天底下恐怕没几个人比得过我！\n", get_name())
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
	       	if ( who->get_level() >= 50 && !who->get_legend(TASK_13,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    民间有一门失传的手艺——泥雕。\n    他们可以用黑泥土雕塑出各种各样的飞禽走兽，鱼虫花鸟，可惜的是，这门手艺已经失传很久很久了，近日，我听说在燕长城一带出现了一批泥雕，可想而知，这是一批多么珍贵的泥雕，如果你能想办法找到10个的话，我一定花高价钱收购！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_13,22) && !who->get_legend(TASK_13,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在别人都还不知道此事，也不知这东西值钱，你可得赶紧给我找来！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_13,23) && !who->get_legend(TASK_13,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，这回可发大财了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >=50 && !who->get_legend(TASK_13,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,22);
        		who->delete_save_2("gdsnidiao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"燕国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,20,"泥雕" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"泥雕");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_13,23) && !who->get_legend(TASK_13,24) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"泥雕",10) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64077",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,24);
        		who->delete_save_2("gdsnidiao");
			who->add_exp(5700);
			who->add_potential(220);
			who->add_cash(4600);
			send_user(who,"%c%s",';',"泥雕 经验 5700 潜能 220 金钱 4600 鹤啸行装图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,20,"" );
        	}
        	break;   
		
        }
}
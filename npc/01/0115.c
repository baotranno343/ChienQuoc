
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5805; }

// 函数：构造处理
void create()
{
        set_name( "Lưu Đại Thúc" );

        set_2( "talk", ([
                "welcome"         : (: do_welcome :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	
	if (who->get_legend(TASK_NEWBIE_02, 7)&&!who->get_legend(TASK_NEWBIE_02, 8))
		tmp +=  sprintf(ESC HIY "小鸡咕咕的饲料\ntalk %x# welcome.1\n",getoid(this_object()));
	if (who->get_legend(TASK_41, 11)&&!who->get_legend(TASK_41, 12))
		tmp +=  sprintf(ESC "大木箱\ntalk %x# welcome.3\n",getoid(this_object()));

        tmp += CHAIN_D->get_chain_menu(who,this_object());
        send_user( who, "%c%c%w%s", ':', 3, get_char_picid(), 
                sprintf("%s：\n    自从教训了那些山鸡后，这日子比以前舒坦多了，想来想去，还是小鸡咕咕最乖巧。\n"
                        + tmp +
                        ESC "我只是随便看看\nCLOSE\n",get_name(), getoid(this_object()) ) );
}
// 函数：对话处理
void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,p;
	object who,item;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        	case 1:
			if (!who->get_legend(TASK_NEWBIE_02, 7)||who->get_legend(TASK_NEWBIE_02, 8)||who->get_legend(TASK_NEWBIE_02, 9) )
				return;
	                send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    你见到那只小鸡了吧？它是不是又在缠着你要吃的？呵呵，我就知道会这样。将这包饲料拿去喂它吧。小鸡会很高兴的。\n"ESC"得到饲料\ntalk %x# welcome.2\n"ESC"离开",getoid(me)));
        		break;
		case 2:
			if (!who->get_legend(TASK_NEWBIE_02, 7)||who->get_legend(TASK_NEWBIE_02, 8) ||who->get_legend(TASK_NEWBIE_02, 9))
				return;
			item = new("item/98/9887");
			p = item->move(who,-1);
			if ( !p )
			{
				send_user(who,"%c%s",'!',"你身上的东西太多了");				
				return ;
			}
			item->add_to_user(p);
			who->set_legend(TASK_NEWBIE_02, 8);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,16,"小鸡咕咕(已经完成)" );
			USER_TASK_D->send_task_intro(who,2,TID_NEWBIE_01,16);
			send_user(who,"%c%s",'!',"你得到小鸡饲料");	
			break;
	        case 3:
	        	if ( who->get_legend(TASK_41,11) && !who->get_legend(TASK_41,12) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我等了好久，他终于帮我把东西都收集齐了，谢谢你给我送过来！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
	        	break;
	        case 4:
	        	if ( who->get_legend(TASK_41,11) && !who->get_legend(TASK_41,12) )
			{
				if (TASK_LEGEND_D->check_task_item(who,"大木箱",1) != 1 )
	        			return;
				who->add_exp(250);
				who->add_potential(20);
				who->set_legend(TASK_41, 12);
				send_user(who,"%c%s",';',"运箱子 经验 250 潜能 20");			
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,33,"" );
			}
	        	break;
        }
}
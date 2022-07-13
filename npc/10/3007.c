
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 0450; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tề Tiểu Phiến");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      

 	set("mpLegend",([85:({32*38+15,}),]));
 	set("mpLegend2",([0:({32*31+2,32*31+5,32*31+8,}),85:({32*38+16,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int id;
	string tmp="";

	id = getoid(this_object());
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( who->get_legend(TASK_31,1) && !who->get_legend(TASK_31,2) ) 
		tmp += sprintf(ESC HIY "询问小贩\ntalk %x# welcome.1\n",id); 
        if ( (who->get_legend(TASK_31,2) && !who->get_legend(TASK_31,3)) || (who->get_legend(TASK_31,3) && !who->get_legend(TASK_31,5)) ) 
		tmp += sprintf(ESC HIY "解除疑惑\ntalk %x# welcome.1\n",id); 
        if ( (who->get_legend(TASK_31,5) && !who->get_legend(TASK_31,6)) || (who->get_legend(TASK_31,6) && !who->get_legend(TASK_31,8)) ) 
		tmp += sprintf(ESC HIY "除掉恶霸\ntalk %x# welcome.1\n",id); 
        if ( who->get_legend(TASK_31,8) && !who->get_legend(TASK_31,9) ) 
		tmp += sprintf(ESC HIY "告知内政官\ntalk %x# welcome.1\n",id); 
        if ( who->get_level() >= 85 && who->get_legend(TASK_38,15) && !who->get_legend(TASK_38,16) ) 
		tmp += sprintf(ESC HIY "弟弟的问候\ntalk %x# welcome.8\n",id); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0201))
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
        	if ( who->get_legend(TASK_31,1) && !who->get_legend(TASK_31,2) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真不知道该如何向你诉说！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,2) && !who->get_legend(TASK_31,3) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，头一件事情，就是我突然记起来上辈子的事情，我跑到隔壁韩三家找他媳妇，结果被闯入的强盗给杀了，结果阎王爷判定我为风流鬼让我做了小贩，现在故人早就投胎了，可是那强盗还在，他们现在也不做强盗了，改行做俑了，他们就是将军古墓的弓箭石俑和枪俑，你去帮我干掉他们，免得我老做噩梦。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,3) && !who->get_legend(TASK_31,4) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    算了，上辈子的债今生是还不了了。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_31,4) && !who->get_legend(TASK_31,5) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵…这下我不用担心了。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,5) && !who->get_legend(TASK_31,6) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有个叫张七龙的恶霸，强行让我交保护费，不然就要砸了我的摊子，我这是小本生意，勉强够维持生计，哪有多的钱给他啊！据说那张七龙现在在将军古墓五层的南部地带活动，你若将他杀掉就告诉我一声。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,6) && !who->get_legend(TASK_31,7) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我的准备搬家避难了。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_31,7) && !who->get_legend(TASK_31,8) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,8) && !who->get_legend(TASK_31,9) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我听说似乎这个恶霸同内政官有点什么关系，你最好去知会一下，免得他找你麻烦。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
 
	    	break;
        case 2:
        	if ( who->get_legend(TASK_31,1) && !who->get_legend(TASK_31,2) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,2);
			who->add_exp(70000);
			who->add_potential(840);
			who->add_cash(56000);
			send_user(who,"%c%s",';',"询问小贩 经验 70000 潜能 840 金钱 56000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,45,"" );
			me->do_welcome(1);
        	}
        	break;   
	case 3:
        	if ( who->get_legend(TASK_31,2) && !who->get_legend(TASK_31,3) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,3);
        		who->delete_save("qxfgongjsy");
        		who->delete_save("qxfqianyong");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,46,"解除疑惑" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"解除疑惑");
        	}
        	break;  
        case 4:
        	if ( who->get_legend(TASK_31,4) && !who->get_legend(TASK_31,5) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,5);
        		who->delete_save("qxfgongjsy");
        		who->delete_save("qxfqianyong");
			who->add_exp(69000);
			who->add_potential(830);
			who->add_cash(55000);
			send_user(who,"%c%s",';',"解除疑惑 经验 69000 潜能 830 金钱 55000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,46,"" );
			me->do_welcome(1);
        	}
        	break;  
	case 5:
        	if ( who->get_legend(TASK_31,5) && !who->get_legend(TASK_31,6) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,6);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,47,"除掉恶霸" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"除掉恶霸");
        	}
        	break;  
        case 6:
        	if ( who->get_legend(TASK_31,7) && !who->get_legend(TASK_31,8) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,8);
			who->add_exp(70000);
			who->add_potential(820);
			who->add_cash(57000);
			send_user(who,"%c%s",';',"除掉恶霸 经验 70000 潜能 820 金钱 57000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,47,"" );
			me->do_welcome(1);
        	}
        	break;  
	case 7:
        	if ( who->get_legend(TASK_31,8) && !who->get_legend(TASK_31,9) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,48,"告知内政官" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"告知内政官");
        	}
        	break;
        case 8:
        	if ( who->get_level() >= 85 && who->get_legend(TASK_38,15) && !who->get_legend(TASK_38,16) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，我也想回去啊！但是我想多赚点钱回去，让我爹我娘过上好点的日子！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 9:
        	if ( who->get_level() >= 85 && who->get_legend(TASK_38,15) && !who->get_legend(TASK_38,16) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_38,16);
			who->add_exp(30000);
			who->add_potential(400);
			who->add_cash(22000);
			send_user(who,"%c%s",';',"弟弟的问候 经验 30000 潜能 400 金钱 22000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,65,"" );
        	}
        	break; 
        }
}
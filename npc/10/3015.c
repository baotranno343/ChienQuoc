
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5505; }

// 函数：构造处理
void create()
{
        set_name("Nhạc Sư");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*26+23,}),]));
        setup();
}

// 函数：对话处理
// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
        tmp += CHAIN_D->get_chain_menu(who,me);
        if ( who->get_legend(TASK_26,22) && !who->get_legend(TASK_26,23) ) 
		tmp += sprintf(ESC HIY "百姓的好心\ntalk %x# welcome.1\n",getoid(me)); 
        if ( who->get_legend(TASK_26,23) && !who->get_legend(TASK_26,24) ) 
		tmp += sprintf(ESC HIY "乐师的无奈\ntalk %x# welcome.1\n",getoid(me)); 
    
        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0421))
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
	       	if ( who->get_legend(TASK_26,22) && !who->get_legend(TASK_26,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呜～～！很感谢大家都这么关心我呀。但是，现在这是什么世道呀！我父亲是冤枉的啊！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
	       	else if ( who->get_legend(TASK_26,23) && !who->get_legend(TASK_26,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我的父亲本来是大王宫中御厨，他已经在宫中侍奉了大王十多年了。但是，最近因为王府里面的一件宝物含鳞珠被窃，调查之下居然说是我父亲偷的。后来经过内政官审判，就把我父亲定罪收监了。但是我父亲生性忠厚，是绝对不会偷东西的，我一定要为我父亲申诉，你可以帮我将这封诉苦书交给韩国御史郑国吗？\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if ( who->get_legend(TASK_26,22) && !who->get_legend(TASK_26,23) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_26,23);
			who->add_exp(41000);
			who->add_potential(600);
			who->add_cash(41000);
			send_user(who,"%c%s",';',"百姓的好心 经验 41000 潜能 600 金钱 41000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,36,"" );
			me->do_welcome(1);
        	}
        	break;     
	case 3:
        	if( who->get_legend(TASK_26,23) && !who->get_legend(TASK_26,24) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0124");
        		if ( !item )
        			return ;
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!', "你携带的物品太多了");
        			return;
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_26,24);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"韩国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,37,"乐师的无奈" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"乐师的无奈");
        	}
        	break;
 
        }
}  
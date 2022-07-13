
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
        set_name("Lưu Phương Sĩ");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",77);
//        set("legend",({32*25+17}));  
 	set("mpLegend",([75:({32*25+17})]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
        tmp += CHAIN_D->get_chain_menu(who,me);
        if ( who->get_level() >= 75 && !who->get_legend(TASK_25,17) ) 
		tmp += sprintf(ESC HIY "出谋献策\ntalk %x# welcome.1\n",getoid(me)); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0311))
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
	       	if ( who->get_level() >= 75 && !who->get_legend(TASK_25,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近韩国国内到处妖物横行，灵谷洞那边每天妖气冲天，如果再不加以理会的话，很快我们韩国将会是妖物的天下。作为韩国国民我可不能对这事不闻不问，我看这件事定是有妖人想要加害于我们韩国。日前我已经把这件事的来龙去脉大致查清楚，你可以替我把这封请命函带到韩国内政官申不害那里去吗？让他上奏大王，派人去处理这件事！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >= 75 && !who->get_legend(TASK_25,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0119");
        		if ( !item )
        			return ;
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!',"你携带的物品太多了");	
        			return ;
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_25,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"韩国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,21,"出谋献策" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"出谋献策");
        	}
        	break;       
        }
}  
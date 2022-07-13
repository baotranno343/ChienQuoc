
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>
#include <equip.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 5805; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Yên Thương Thiên");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",44);
//        set("legend",({32*11+14}));     
	set("mpLegend",([40:({32*11+14})]));
	set("mpLegend2",([40:({32*11+23})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 40 && !who->get_legend(TASK_11,14)) || (who->get_legend(TASK_11,14)&&!who->get_legend(TASK_11,15)) ) 
		tmp += sprintf(ESC HIY "无奈的求助\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_11,22)&&!who->get_legend(TASK_11,23) ) 
		tmp += sprintf(ESC HIY "无奈的求助\ntalk %x# welcome.1\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    我最值得骄傲的事情就是，这辈子没有求过人！\n", get_name())
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
       	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 40 && !who->get_legend(TASK_11,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近遇到一件极其麻烦的事情，因为不能太张扬，所以不能找人商量，我只想找到一个人，能替我办好这件事，并且他要保守秘密，我绝不亏待他！\n    你愿意帮助我吗？愿意的话，你去找赵国的王铁匠，见到他后就说我那事该怎么办，他就会明白的！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_11,14) && !who->get_legend(TASK_11,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    丢人啊，一辈子没求过人，找你帮忙，你居然不愿意帮我。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_11,22)&&!who->get_legend(TASK_11,23) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    事到如今，只能按照王铁匠教的方法试试了！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
 	      	break;
     
        case 2:
        	if( who->get_level() >= 40 && !who->get_legend(TASK_11,14) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_11,14);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"燕国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,17,"无奈的求助（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"无奈的求助（1）");
        	}
        	break;

        case 3:
        	if( who->get_legend(TASK_11,22) && !who->get_legend(TASK_11,23) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"信",1) != 1 )
        			return;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),40,NECK_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,23);
			who->add_exp(4500);
			who->add_potential(145);
			who->add_cash(3900);
			send_user(who,"%c%s",';',sprintf("无奈的求助（4） 经验 4500 潜能 145 金钱 3900 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,3,"" );
        	}
        	break;
        }
}
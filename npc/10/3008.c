
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 7302; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Bối Bối");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",42);
//        set("legend",({32*11+6}));    
	set("mpLegend2",([0:({32*11+5,32*11+8,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( who->get_legend(TASK_11,4)&&!who->get_legend(TASK_11,5) ) 
		tmp += sprintf(ESC HIY "程强的信物\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_11,5) && !who->get_legend(TASK_11,6)) || (who->get_legend(TASK_11,6)&&!who->get_legend(TASK_11,8)) ) 
		tmp += sprintf(ESC HIY "大显身手\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_11,8) && !who->get_legend(TASK_11,9)) || (who->get_legend(TASK_11,9)&&!who->get_legend(TASK_11,10)) ) 
		tmp += sprintf(ESC HIY "交换信物\ntalk %x# welcome.1\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    深闺大院，让我有点无所适从……\n", get_name())
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
        	if ( who->get_legend(TASK_11,4)&&!who->get_legend(TASK_11,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这珍珠项链真漂亮，想必花了很多功夫才找到的，这程强看来是用心良苦啊。不过，我还得考验他一下。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_11,5) && !who->get_legend(TASK_11,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    俗话说，物以类聚，人以群分。既然程强找上你来送信物，那你肯定也是他值得信任的人，现在你去郑国渠打败30个劳役，我就相信你的能力，也相信程强的眼光。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_11,6) && !who->get_legend(TASK_11,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你可别让我失望，不然我对程强也会失去信心的。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_11,7) && !who->get_legend(TASK_11,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    果然不错!这程强没有看错人，也说明他的眼光相当有水准！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_11,8) && !who->get_legend(TASK_11,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    从你的努力可以看出，你是一个很有责任感的人，我相信程强也会像你一样，是一个能肩负起家庭重任的男人，这是我亲手做的糕点，请你将它交给程强。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_11,9) && !who->get_legend(TASK_11,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    糕点放久了会坏掉的，还是赶紧送去吧！\n"ESC"离开", me->get_name()));
        	break;
       case 2:
        	if ( who->get_legend(TASK_11,4) && !who->get_legend(TASK_11,5) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"珍珠项链",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,5);
			who->add_exp(4200);
			who->add_potential(130);
			who->add_cash(3500);
			send_user(who,"%c%s",';',"情锁秦宫（2） 经验 4200 潜能 130 金钱 3500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,4,"" );
			me->do_welcome(1);
        	}
        	break;        
        case 3:
        	if( who->get_legend(TASK_11,5) && !who->get_legend(TASK_11,6) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_11,6);
        		who->delete_save_2("bbkuyi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,5,"情锁秦宫（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"情锁秦宫（3）");
        	}
        	break;
        case 4:
 		if ( who->get_legend(TASK_11,7) && !who->get_legend(TASK_11,8) )
 		{
 			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/15/1507",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,8);
        		who->delete_save_2("bbkuyi");
			who->add_exp(5500);
			who->add_potential(180);
			who->add_cash(4000);
			send_user(who,"%c%s",';',"情锁秦宫（3） 经验 5500 潜能 180 金钱 4000 中级物攻 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,5,"" );
			me->do_welcome(1);
        	}
        	break;
        case 5:
        	if( who->get_legend(TASK_11,8) && !who->get_legend(TASK_11,9) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			item = new("item/98/0044");
			if ( !item  )
				return ;
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				send_user( who, "%c%s", '!', "你身上的东西太多了");
				return;
			}
			item->add_to_user(p);
        		who->set_legend(TASK_11,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"秦国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,6,"情锁秦宫（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"情锁秦宫（4）");
        	}
        	break;
        }
}
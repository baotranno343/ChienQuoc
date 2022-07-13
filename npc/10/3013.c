
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5401; }

// 函数：构造处理
void create()
{
        set_name("Lưu Lão Bản");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",48);
//        set("legend",({32*12+22}));
	set("mpLegend",([45:({32*12+22,32*12+28}),50:({32*14+15})]));
	set("mpLegend2",([45:({32*12+24,32*12+30}),50:({32*14+17})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 45 && !who->get_legend(TASK_12,22)) || (who->get_legend(TASK_12,22)&&!who->get_legend(TASK_12,24)) ) 
		tmp += sprintf(ESC HIY "河道霸王\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_level() >= 45 && !who->get_legend(TASK_12,28)) || (who->get_legend(TASK_12,28)&&!who->get_legend(TASK_12,30)) ) 
		tmp += sprintf(ESC HIY "众说纷纭\ntalk %x# welcome.7\n",getoid(this_object())); 
        if ( (who->get_level() >= 50 && !who->get_legend(TASK_14,15)) || (who->get_legend(TASK_14,15)&&!who->get_legend(TASK_14,17)) ) 
		tmp += sprintf(ESC HIY "二胡\ntalk %x# welcome.8\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0401))
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
	       	if ( who->get_level() >= 45 && !who->get_legend(TASK_12,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我是生意人，你也看出来了，做生意虽然能赚钱，但也非常辛苦，成天东奔西跑，在路上遇到打劫更是司空见惯。\n    上月我路过郑国渠，结果被一恶霸打劫。这恶霸如果不除，以后谁还敢从那里经过，你是否愿意解决此事？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_12,22) && !who->get_legend(TASK_12,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来以后准备改行换业了，这恶霸不走，谁还敢从那里路过。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_12,23) && !who->get_legend(TASK_12,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    %s你算是为我们这些生意人做了一件大好事！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >=45 && !who->get_legend(TASK_12,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_12,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"燕国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,8,"河道霸王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"河道霸王");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_12,23) && !who->get_legend(TASK_12,24) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->task_finish(who);
        		TASK_LEGEND_D->give_item(who,"item/product/64070",1);
			who->set_legend(TASK_12,24);
			who->add_exp(5100);
			who->add_potential(200);
			who->add_cash(4700);
			send_user(who,"%c%s",';',"河道霸王 经验 5100 潜能 200 金钱 4700 鲤鱼靴图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,8,"" );
        	}
        	break;   
	case 4:
        	if( who->get_level() >=45 && !who->get_legend(TASK_12,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_12,28);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"燕国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,10,"众说纷纭" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"众说纷纭");
        	}
        	break;       
        case 5:
        	if ( who->get_legend(TASK_12,29) && !who->get_legend(TASK_12,30) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64069",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_12,30);
			who->add_exp(5500);
			who->add_potential(200);
			who->add_cash(4800);
			send_user(who,"%c%s",';',"众说纷纭 经验 5500 潜能 200 金钱 4800 宣明鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,10,"" );
        	}
        	break;   
	case 7 :
	       	if ( who->get_level() >= 45 && !who->get_legend(TASK_12,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    郑国渠又有人失踪了，你知道吗？\n    最近大家都在讨论郑国渠一带经常有百姓离奇失踪之事，如今此事已弄得人心惶惶。不知你是否知道这世上有一种迷失鬼，它们专门迷惑人的心智，操纵人为他做一些伤天害理的事情，我猜想这次一连串的失踪，也和这迷失鬼有关，你前去郑国渠调查此事吧！\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_12,28) && !who->get_legend(TASK_12,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这世道可真是无奇不有啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_12,29) && !who->get_legend(TASK_12,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    %s这可真是谢谢你了！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		break;		
	case 8 :
	       	if ( who->get_level() >= 50 && !who->get_legend(TASK_14,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    音乐，是人的精神食粮；音乐，最能接近人的灵魂；音乐，最能触动人心底的那根弦……\n    我喜欢乐器，特别是二胡，因为它的声音带给我哀怨的感觉，如泣如诉，或许我作为一个生意人，不该如此多愁善感，但是我的确收藏了不少的二胡，并且还在继续收藏，听说长白山有很好的二胡，你去长白山给我找来好么？\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_14,15) && !who->get_legend(TASK_14,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n   唉，数来数去还是缺了那把二胡，你找到了吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_14,16) && !who->get_legend(TASK_14,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你给我找来刚好缺了的这把二胡。\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 9:
        	if( who->get_level() >= 50 && !who->get_legend(TASK_14,15) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_14,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"燕国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,28,"二胡" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"二胡");
        	}
        	break;       
        case 10:
        	if ( who->get_legend(TASK_14,16) && !who->get_legend(TASK_14,17) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"二胡",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_14,17);
			who->add_exp(6000);
			who->add_potential(240);
			who->add_cash(4800);
			send_user(who,"%c%s",';',"二胡 经验 6000 潜能 240 金钱 4800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,28,"" );
        	}
        	break; 
        }
}

// 自动生成：/make/npc/make8084

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5801; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Ngụy Quốc Bá Tánh");
	set_real_name("Nhạc Dương");
        set_city_name("Ngụy Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//	set("level",85);
//	set("legend",({32*29+10})); 
 	set("mpLegend",([85:({32*29+10}),95:({32*33+25})]));
 	set("mpLegend2",([0:({32*7+5,32*7+8,32*34+8,}),85:({32*29+12}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int id;
	string tmp="";
	object me = this_object();
	
	id = getoid(me);
	if ( who->get_legend(TASK_07,4) && !who->get_legend(TASK_07,5) )
	{
		tmp += sprintf(ESC HIY "去燕的盘缠\ntalk %x# welcome.1\n",id);
	}
	if ( who->get_legend(TASK_07,5) && !who->get_legend(TASK_07,8) )
	{
		tmp += sprintf(ESC HIY "换盘缠的芍药\ntalk %x# welcome.1\n",id);
	}
	if ( who->get_legend(TASK_07,8) && !who->get_legend(TASK_07,9) )
	{
		tmp += sprintf(ESC HIY "返还盘缠\ntalk %x# welcome.1\n",id);
	}
	if ( (who->get_level() >= 85 && !who->get_legend(TASK_29,10)) || (who->get_legend(TASK_29,10) && !who->get_legend(TASK_29,12)) )
	{
		tmp += sprintf(ESC HIY "绑匪的条件\ntalk %x# welcome.5\n",id);
	}
	if ( who->get_level() >= 95 && !who->get_legend(TASK_33,25) )
	{
		tmp += sprintf(ESC HIY "打探消息\ntalk %x# welcome.8\n",id);
	}
        if ( who->get_legend(TASK_34,7) && !who->get_legend(TASK_34,8) )
		tmp += sprintf(ESC HIY "Ngụy Quốc Bá Tánh\ntalk %x# welcome.8\n",id); 

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),id) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
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
        	if ( who->get_legend(TASK_07,4) && !who->get_legend(TASK_07,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，我现在手头也比较紧，一下子拿出这么多钱可能也有点困难，最近街上有人在卖花，我看赚钱挺快的，可能还得麻烦你去收集一些山芍药来，我拿去卖凑够盘缠了就给你！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_07,5) && !who->get_legend(TASK_07,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，你来得可真不是时候！刚好碰上我手头紧，一下子要拿出这么多钱还真有点困难，我给你想想办法吧！\n    有了！前天市集上有人在卖花，我上前打听了下，山芍药是价钱最高也是卖得最好的，不过这山芍药采起来可没那么容易，只有无定河的鬼火那才有。如果你想帮孟求这个忙，那你就去无定河找来山芍药吧，我想只要卖掉10个山芍药，就能凑够孟求的盘缠了。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_07,6) && !who->get_legend(TASK_07,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果不能收集到10个芍药，盘缠恐怕难以凑足。\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_07,7) && !who->get_legend(TASK_07,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下好了，盘缠终于凑够了，你拿去给孟求吧！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_07,8) && !who->get_legend(TASK_07,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这盘缠交给你了，你可得尽快转交给孟求，带在身上可得注意安全，别弄丢了！\n"ESC"离开", me->get_name(),getoid(me)));	
	
        	break;
	case 2:
        	if ( who->get_legend(TASK_07,4) && !who->get_legend(TASK_07,5) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,5);
			who->add_exp(1000);
			who->add_potential(10);
			who->add_cash(1000);
			send_user(who,"%c%s",';',"去燕的盘缠 经验 1000 潜能 10 金钱 1000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,5,"" );
			me->do_welcome(1);
        	}
        	break;      
	case 3:
        	if ( who->get_legend(TASK_07,5) && !who->get_legend(TASK_07,6) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_07,6);
        		who->delete_save_2("sansaoyao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,6,"换盘缠的芍药" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"换盘缠的芍药");
        	}
        	break;
        case 4:
        	if ( who->get_legend(TASK_07,7) && !who->get_legend(TASK_07,8) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"山芍药",10) != 1 )
        			return;
        		item = new("item/98/0026");
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				return;	
			}
			item->add_to_user(p);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,8);
			who->delete_save_2("sansaoyao");
			who->add_exp(1500);
			who->add_potential(30);
			who->add_cash(1300);
			send_user(who,"%c%s",';',"换盘缠的芍药 经验 1500 潜能 30 金钱 1300 盘缠 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,6,"" );
			USER_TASK_D->send_task_intro(who,2,TID_WEIGUO,5);
        	}
        	break;
        case 5:
        	if (who->get_level() >= 85 && !who->get_legend(TASK_29,10))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我儿子昨天同着邻居家的妞妞出去玩，结果妞妞哭着回来，说是有个很凶的大叔抓了我儿子，要我用祖传的玉雕去换，哎，都怪我以前得到的时候到处宣扬，其实这东西哪里是我祖传的，不过是我有次跟着一个貌似侠士进到将军古墓捡漏乘他不注意拣到的而已，那早就被我换了钱花光了，如今我哪里有那个本事自己一个人进去将军古墓再去拿玉雕啊，看来侠士倒是一副好筋骨，不知道能否救救我儿子，去将军古墓里收集20个玉雕？\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_29,10) && !who->get_legend(TASK_29,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    找不到玉雕可怎么办啊！我又不敢轻举妄动，万一他们恼羞成怒把我儿子……唉，真不敢想象！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_29,11) && !who->get_legend(TASK_29,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这20个玉雕，我就能把儿子赎回来了！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 6:
        	if (who->get_level() >= 85 && !who->get_legend(TASK_29,10))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,10);
        		who->delete_save("wgbxyudiao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,33,"绑匪的条件" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"绑匪的条件");
        	}
        	break; 
        case 7:
        	if ( who->get_legend(TASK_29,11) && !who->get_legend(TASK_29,12) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"玉雕",20) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64154",1);
        		who->delete_save("wgbxyudiao");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,12);
			who->add_exp(54000);
			who->add_potential(745);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"绑匪的条件 经验 54000 潜能 745 金钱 50000 飞羽冠图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,33,"" );
        	}
        	break;
        case 8:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_33,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前天，听城郊西处的李德说，紫云洞有一件神奇的宝物。你心动了吗？心动了就赶紧去问他本人。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_34,7) && !who->get_legend(TASK_34,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    了解！遵命！\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 9:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_33,25) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_33,25);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,37,"打探消息" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"打探消息");
        	}
        	break; 	   
        case 10:
        	if ( who->get_legend(TASK_34,7) && !who->get_legend(TASK_34,8) ) 
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/63034",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,8);
			who->add_exp(73000);
			who->add_potential(900);
			who->add_cash(60000);
			send_user(who,"%c%s",';',"Ngụy Quốc Bá Tánh 经验 73000 潜能 900 金钱 60000 紫金丹图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,41,"" );
        	}
        	break;
        }

}

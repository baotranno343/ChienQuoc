
// 自动生成：/make/npc/make8084

#include <npc.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0053; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Bá Tánh");
	set_real_name("Hàn Nhượng");
        set_city_name("Sở Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",14);
//        set("legend",({32*3+22}));
	set("mpLegend",([10:({32*3+22}),95:({32*33+19}),30:({32*8+4,32*8+28})]));
	set("mpLegend2",([0:({32*24+8,32*24+11,32*24+14,}),30:({32*8+6,32*8+30})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{ 
	int id;
	string tmp="";
	object me = this_object();
	id = getoid(me);
	if ( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,22) )
	{
		tmp = sprintf(ESC HIY "亡羊补牢\ntalk %x# welcome.1\n",id);
	}
	if ( (who->get_level() >= 30 && !who->get_legend(TASK_08,4)) || (who->get_legend(TASK_08,4)&&!who->get_legend(TASK_08,6)) )
	{
		tmp += sprintf(ESC HIY "山谷解迷\ntalk %x# welcome.3\n",id);
	}
	if ( (who->get_level() >= 30 && !who->get_legend(TASK_08,28)) || (who->get_legend(TASK_08,28)&&!who->get_legend(TASK_08,30)) )
	{
		tmp += sprintf(ESC HIY "九道谷里的宝物\ntalk %x# welcome.6\n",id);
	}
	if ( (who->get_legend(TASK_24,7) && !who->get_legend(TASK_24,8)) || (who->get_legend(TASK_24,14) && !who->get_legend(TASK_24,15)) )
	{
		tmp += sprintf(ESC HIY "茉莉花茶\ntalk %x# welcome.9\n",id);
	}	
	if ( (who->get_legend(TASK_24,8) && !who->get_legend(TASK_24,9)) || (who->get_legend(TASK_24,9) && !who->get_legend(TASK_24,11)) )
	{
		tmp += sprintf(ESC HIY "茉莉花\ntalk %x# welcome.9\n",id);
	}
	if ( (who->get_legend(TASK_24,11) && !who->get_legend(TASK_24,12)) || (who->get_legend(TASK_24,12) && !who->get_legend(TASK_24,14)) )
	{
		tmp += sprintf(ESC HIY "雪水\ntalk %x# welcome.9\n",id);
	}
	if ( who->get_level() >= 95 && !who->get_legend(TASK_33,19) )
		tmp += sprintf(ESC HIY "保持距离\ntalk %x# welcome.16\n",id);

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name()) +
		tmp +
		ESC"离开");
	else
		more_look_menu( who, sprintf( "%s：\n    %s\n", get_name(), "/quest/word"->get_country_word(me) ) );
	
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,i,size,p,amount;
        object who,item, *inv,item1;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,22) )
        	{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    奸臣当道，目无朝纲，扰乱法纪，国之将乱矣。听说我们大王和庄辛意见不统一，现在庄辛与大王达成协议，准备迁至赵国居住，好象需要帮忙，作为一个爱国有为青年，您就去看看吧，他就在洞庭湖的君山一带。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	}
        	break;
        case 2:
        	if ( who->get_level() >= 10 && !who->get_legend(TASK_NEWBIE_03,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_NEWBIE_03,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,9,"亡羊补牢(1)" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"亡羊补牢(1)");
        	}
        	break;
        case 3:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真是奇了怪了，怎么会有这样的事情呢？你想知道发生了什么事？\n    我前段日子上巫山打柴，打完柴准备回家的时候，在山上转来转去就是下不了山，要知道这条路我可是走了十多年了，不可能会迷路的！但是更奇怪的是，只要我在那里被困的时间超过一个时辰，我又突然能走出去了！\n    这到底是怎么回事呢？你能不能去那里给调查一下，看是不是巫山精灵在作怪！\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_08,4) && !who->get_legend(TASK_08,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    莫非我那天头晕了吗？可能是我自己老糊涂了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_08,5) && !who->get_legend(TASK_08,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原来是这么回事，那可恶的巫山精灵。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 4:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,14,"山谷解迷" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"山谷解迷");
        	}
        	break;
        case 5:
        	if ( who->get_legend(TASK_08,5) && !who->get_legend(TASK_08,6) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,6);
			who->add_exp(2300);
			who->add_potential(80);
			who->add_cash(1600);
			send_user(who,"%c%s",';',"山谷解迷 经验 2300 潜能 80 金钱 1600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,14,"" );
        	}
        	break;        
        case 6:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿，那边的%s，你听说过点石成金术吗？\n    我相信这个世界上任谁都会对点石成金术感兴趣，能将石头变成金子，多神奇啊！谁掌握了点石成金术不就不愁吃不愁喝了吗？对他来说，这片土地上有多少石头，就等于有多少金子。\n    你问我会不会？呵呵，我不会。但是我听说在大别山脚的九道谷里有枝绝世神笔，它的神奇之处就在于它能点石成金，如果你替我找来，我一定会好好报答你！\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	else if ( who->get_legend(TASK_08,28) && !who->get_legend(TASK_08,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道那只是个传说，哎……害我空欢喜一场。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_08,29) && !who->get_legend(TASK_08,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太好了！原来传说中真有这东西，真得好好好谢谢你。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 7:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,28);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,22,"九道谷里的宝物" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"九道谷里的宝物");
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_08,29) && !who->get_legend(TASK_08,30) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"桦木神笔",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,30);
			who->add_exp(2600);
			who->add_potential(100);
			who->add_cash(1900);
			send_user(who,"%c%s",';',"九道谷里的宝物 经验 2600 潜能 100 金钱 1900");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,22,"" );
        	}
        	break;  
        case 9:
        	if ( who->get_legend(TASK_24,7) && !who->get_legend(TASK_24,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我们楚国以前的确有这样的一种茉莉花茶，而且我也懂怎么泡这种茶喝。但是因为泡这种茶所需要收集的材料都很难找到，所以现在已经很少人泡这种茶喝了。\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_24,8) && !who->get_legend(TASK_24,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你真的想要喝这种茶，我可以告诉你制作的方法，但是前提是你必须先去收集好泡茶所用的茶叶。这种茉莉花茶的茶叶其实就是一种很稀有的茉莉花，这种茉莉花一般只生长在灵谷洞那边的豆兵身上，灵谷洞的豆兵可不好对付，如果你能在那里的豆兵身上取到那茉莉花回来的话，我就教你泡茶的方法。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_24,9) && !who->get_legend(TASK_24,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    茉莉花茶一般只生长在灵谷洞的豆兵身上，但是那些豆兵太强了，如果你没有办法取到那些茉莉花也就不要勉强了。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_24,10) && !who->get_legend(TASK_24,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你真的能从那些豆兵身上取到这些茉莉花啊？原来你的武功这么厉害！看来这次我们有希望可以再喝到这种好喝的茉莉花茶了！\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_24,11) && !who->get_legend(TASK_24,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这些茉莉花，泡出茉莉花茶是不成问题了，但是如果想要喝到真正茶味香浓的茉莉花茶的话最好还是用长白天池的雪水冲泡，这样的话泡出来的茉莉花茶不但茶味香浓，还可以有增进食欲，促进睡眠的功效。如果可以的话，你能去长白天池去找些雪水回来吗？对你来说这应该只是一件很简单的事情。那里的魍魉和花豹精身上都有可能有这些雪水。\n"ESC"接受任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_24,12) && !who->get_legend(TASK_24,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    雪水找到了吗？在长白天池的魍魉和花豹精身上就有，这个对你来说肯定不成问题了！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_24,13) && !who->get_legend(TASK_24,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你果然把雪水找回来了！现在我们终于又可以喝到这种不但茶味香浓、薰香扑鼻，而且可以增进食欲，促进睡眠的好茶，这是我们楚国农家最喜欢的茶了。放心，我现在马上就把泡这茶的方法告诉你。\n"ESC"完成任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_24,14) && !who->get_legend(TASK_24,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在，你拿着这些茉莉花茶和雪水吧，冲泡的方法你已经学会了，你可以用这些茉莉花茶跟雪水随时随地泡茶喝，也可以把这种香浓扑鼻的茶，泡给其他人喝，让其他国家的人也可以享受一下源自我们楚国的茉莉花茶呀！\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 10:
        	if ( who->get_legend(TASK_24,7) && !who->get_legend(TASK_24,8) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,8);
			who->add_exp(14000);
			who->add_potential(238);
			who->add_cash(13000);
			send_user(who,"%c%s",';',"茉莉花茶（1） 经验 14000 潜能 238 金钱 13000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,15,"" );
			me->do_welcome(9);
        	}
        	break;   
        case 11:
        	if ( who->get_legend(TASK_24,8) && !who->get_legend(TASK_24,9) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,9);
        		who->delete_save_2("cgbxmolihua");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,29,"茉莉花茶（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"茉莉花茶（2）");
        	}
        	break; 
        case 12:
        	if ( who->get_legend(TASK_24,10) && !who->get_legend(TASK_24,11) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"茉莉花",20) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,11);
        		who->delete_save_2("cgbxmolihua");
			who->add_exp(22000);
			who->add_potential(300);
			who->add_cash(21000);
			send_user(who,"%c%s",';',"茉莉花茶（2） 经验 22000 潜能 300 金钱 21000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,29,"" );
			me->do_welcome(9);
        	}
        	break;   
        case 13:
        	if ( who->get_legend(TASK_24,11) && !who->get_legend(TASK_24,12) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,12);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,30,"茉莉花茶（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"茉莉花茶（3）");
        	}
        	break; 
        case 14:
        	if ( who->get_legend(TASK_24,13) && !who->get_legend(TASK_24,14) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"雪水",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/65076",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,14);
			who->add_exp(22000);
			who->add_potential(300);
			who->add_cash(21000);
			send_user(who,"%c%s",';',"茉莉花茶（3） 经验 22000 潜能 300 金钱 21000 幽魂项链图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,30,"" );
			me->do_welcome(9);
        	}
        	break;  
        case 15:
        	if ( who->get_legend(TASK_24,14) && !who->get_legend(TASK_24,15) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			item = new("item/98/0114");
			if ( !item  )
				return ;
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
				send_user(who,"%c%s",'!',"你携带的物品太多了");
				return;
			}
			item->add_to_user(p);
			item1 = new("item/98/0115");
			if ( !item1 )
				return ;
			p = item1->move(who,-1);
			if ( !p )
			{
				destruct(item1);
				item->remove_from_user();
				destruct(item);
				send_user(who,"%c%s",'!',"你携带的物品太多了");
				return;
			}
			item1->add_to_user(p);			
        		who->set_legend(TASK_24,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,31,"茉莉花茶（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"茉莉花茶（4）");
        	}
        	break;
	case 16:
		if ( who->get_level() >= 95 && !who->get_legend(TASK_33,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那些火精、土精曾雇佣我来帮他们做一些不可告人之事，那时我鬼迷心窍就去了，现在有点后悔，它们害怕我把这件事情说出去，居然还要干掉我……干掉我！\n    所以，你看吧，永远都不要相信那些精灵。\n    问题是，我还有一些东西在它们手上，那些木槌、刨子我还是找工匠借的，你找到后直接交给他就是了。\n"ESC"接受任务\ntalk %x# welcome.17\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 17:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_33,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_33,19);
        		who->delete_save("cgbxmuz");
        		who->delete_save("cgbxpaoz");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,39,"保持距离" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"保持距离");        		
        	}
        	break;

        }
}
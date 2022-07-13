
// 自动生成：/make/npc/make0001

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：Quản Khố
int is_banker() { return 1; }
void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5301; }

// 函数：构造处理
void create()
{
        set_name("Quản Khố");
        set_real_name("Quản Khố");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level",32);
//        set("legend",({32*8+16}));
	set("mpLegend",([30:({32*8+16}),35:({32*9+13})]));
	set("mpLegend2",([30:({32*8+18}),35:({32*9+15})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( (who->get_level() >= 30 && !who->get_legend(TASK_08,16)) || (who->get_legend(TASK_08,16)&&!who->get_legend(TASK_08,18)) )
		tmp =  sprintf(ESC HIY "龙骨坡的灵光\ntalk %x# welcome.1\n",getoid(me));
	if ( ( who->get_level() >= 35 && !who->get_legend(TASK_09,13) ) || ( who->get_legend(TASK_09,13) && !who->get_legend(TASK_09,15) ) )
	{
		tmp += sprintf(ESC HIY "龙骨坡的遗骸\ntalk %x# welcome.4\n",getoid(me));
	}	
        send_user( who, "%c%c%w%s", ':', 1, get_char_picid(), 
                sprintf("%s：\n    "+"/quest/word"->get_normal_word(this_object())+"\n"
                        ESC "我想使用当铺\npawn %x# 1\n"
                        ESC "我要扩充我的当铺\npawn expand %x# 0\n"
                        + tmp +
                        ESC "我只是随便看看\nCLOSE\n", who->get_name(), getoid(this_object()), getoid(this_object()) ) );
	"/quest/help"->send_help_tips(who, 4);                        
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
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    曾经我拥有一颗照世宝石，它是那种通透的白色，周身散发着荧荧的冷光，这颗宝石是一位客人当在我这里的，当期是三个月，可三个月过之后，他却没有来取，所以这颗宝石就属于了我，你不知道，我是多么的宝贝那颗宝石，可越是自己珍惜的东西似乎越容易弄丢，在一次游玩中我不小心将那颗照世宝石遗失了，而昨晚，我看见巫山的龙骨坡方向有一道灵光直射云霄，那荧荧的冷光，我敢断定是照世宝石发出的！你赶快去巫山的龙骨坡替我寻回宝石吧。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_08,16) && !who->get_legend(TASK_08,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道是我分析错误了吗？可能那只是个传说罢了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_08,17) && !who->get_legend(TASK_08,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原来世上真有这东西，我真是太兴奋了。我一定会好好酬谢你。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,18,"龙骨坡的灵光" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"龙骨坡的灵光");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_08,17) && !who->get_legend(TASK_08,18) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"照世宝石",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,18);
			who->add_exp(2500);
			who->add_potential(80);
			who->add_cash(1700);
			send_user(who,"%c%s",';',"龙骨坡的灵光 经验 2500 潜能 80 金钱 1700");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,18,"" );
        	}
        	break;   
        case 4:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这几天有件事情被传得沸沸扬扬，在巫山的龙骨坡发现了一具遗骸，死相非常的难看，似乎死前受到过巨大的惊吓，官府派了不少人去调查，我出于好奇也过去看了。\n    他的脖子上有几道明显的抓痕，官府分析是被人掐住脖子窒息而死，但是我估计事情恐怕没有这么简单。据我所知，在巫山那带会有骨魔精出来害人，被它们杀害的人的标志就是脖子上会有几道抓痕，那是它们长长的爪子所致。\n    我看你也是个行侠仗义的武林中人，不如你去巫山的龙骨坡干掉它为民除害吧！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_09,13) && !who->get_legend(TASK_09,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真是可怕，我以后再也不去那里了。\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,14) && !who->get_legend(TASK_09,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……你真是为百姓做了一件大好事。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 5:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,27,"龙骨坡的遗骸" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"龙骨坡的遗骸");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_09,14) && !who->get_legend(TASK_09,15) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/15/1502",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_09,15);
			who->add_exp(2700);
			who->add_potential(110);
			who->add_cash(2000);
			send_user(who,"%c%s",';',"龙骨坡的遗骸 经验 2700 潜能 110 金钱 2000 初级物攻 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,27,"" );
        	}
        	break;   
        }
}

// 自动生成：/make/npc/make0015

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_info();

// 函数：获取人物造型
int get_char_picid() { return 7415; }
void do_exchange(string sArg);
void do_inputx(string sArg);
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tửu Lâu");

      	set_2( "talk", ([
                "info"  : (: do_info :),
                "do_exchange" : (: do_exchange :),
                "inputx"	: (: do_inputx :),
                "welcome"	: (: do_welcome :),
        ]));
        set_2( "good", ([
                "01" : "/item/31/3150",
                "02" : "/item/31/3151",
                "03" : "/item/31/3152",
                "04" : "/item/32/3280",
                "05" : "/item/32/3281",
                "06" : "/item/32/3282",
                "07" : "/item/32/3283",
                "08" : "/item/32/3284",
                "09" : "/item/32/3285",
		"10" : "/item/stuff/0219",
		"11" : "/item/stuff/0220",
		"12" : "/item/stuff/0221",
		"13" : "/item/stuff/0222",                
		"14" : "/item/stuff/0223",
		"15" : "/item/stuff/0224",         
		"16" : "/item/stuff/0159",      
		"17" : "/item/32/3204",
        ]) );

//        set("level",5);
//        set("legend",({32*2+12,32*40+22}));
	set("mpLegend",([5:({32*2+18,32*40+22}),0:({32*49+18,})]));
	set("mpLegend2",([5:({32*2+20,}),0:({32*49+20,})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object item;
	object me = this_object(), map;
        int id = getoid(me);
	string tmp;
	"/quest/help"->send_help_tips(who, 53);
	tmp = "";

	if ( who->get_legend(TASK_49, 8) && !who->get_legend(TASK_49, 9))
        	tmp += sprintf(ESC +HIY+ "丢失的手镯\ntalk %x# welcome.1\n",id);
	if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 18) )
        	tmp += sprintf(ESC +HIY+ "酿酒的原材料\ntalk %x# welcome.3\n",id);
	if ( who->get_legend(TASK_NEWBIE_02, 19) && !who->get_legend(TASK_NEWBIE_02, 20) )
		tmp += sprintf(ESC +HIY+ "酿酒的原材料\ntalk %x# welcome.3\n",id);
	if ( who->get_level() >= 5 &&!who->get_legend(TASK_40,22) )
		tmp +=  sprintf(ESC +HIY+ "食物的来源\ntalk %x# welcome.6\n",id);
	if ( !who->get_legend(TASK_49,18) )
		tmp +=  sprintf(ESC +HIY+ "偷吃的小野兔\ntalk %x# welcome.8\n",id);
	if ( who->get_legend(TASK_49,19) && !who->get_legend(TASK_49,20) )
		tmp +=  sprintf(ESC +HIY+ "偷吃的小野兔\ntalk %x# welcome.8\n",id);

        tmp += sprintf(ESC"Mua Thực phẩm\nlist %x#\n", id);
        tmp += sprintf(ESC"Tin đồn cửa hàng ở phố\ntalk %x# info\n", id);
        tmp += ESC"Rời khỏi\nCLOSE\n";
        send_user(who,"%c%s",':'," "+get_name()+" :\n "+"/quest/word"->get_normal_word(this_object())+"\n Khách quan, cần đổi gì không?\n"+ tmp);
}

// 函数：住宿处理
void do_info()
{
        object me, who;
        string result, info;
        me = this_object();  who = this_player();
        TASK_MASTER_D->do_info(me, who);
}

void do_exchange(string sArg)
{
	TASK_COLLECT_D->do_exchange(sArg,0015);
}

void do_inputx(string sArg)
{
	object me,who;
	me = this_object(); who = this_player();
	TASK_COLLECT_D->do_inputx(me,who,sArg,0015);
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag, date , status, p, z, x, y, i;
        object who, obj, item;
        string cmd1, cmd2, cmd3, cmd4, cmd5, result;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_legend(TASK_49, 8) && !who->get_legend(TASK_49, 9))
        		send_user(who,"%c%s",':',sprintf("%s\n    七国割据，群雄争霸。当年在战乱逃亡过程中，我的父母不幸去世，母亲临终前交给我的手镯，也被我弄丢了，往事不堪回首！\n    你愿意帮我找到丢失的手镯吗？我听人说好象在幽谷西北一带见过。如果你能把我的手镯完整的带回来，我一定好好的犒劳犒劳你。你找到手镯后先交给门派向导，听说门派向导有一套消毒的绝活，流失在外这么久了，应该请他进行一下消毒清理。\n"ESC"接受\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
        	break;
        case 2:
		if ( who->get_legend(TASK_49, 8) && !who->get_legend(TASK_49, 9))
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->delete_save_2("dssouzuo");
			who->delete_save_2("dssouzuo1");
	        	who->set_legend(TASK_49, 9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,117,"丢失的手镯" );
			send_user( who, "%c%s", '!', "你接受了"HIY"丢失的手镯"NOR"任务");
		}
               	break;
        case 3:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 18) )
        		send_user(who,"%c%s",':',sprintf("%s\n    我曾经听闻幽谷和清溪附近有一种斑点蛙，它们拥有一种叫小麦的东西，是酿酒的上等材料，我很希望能用这种小麦酿出上等的酒，使我这小酒馆的生意好一些。\n    如果你能给我带来3根小麦，我一定不会亏待你的。\n"ESC"接受\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_NEWBIE_02, 19) && !who->get_legend(TASK_NEWBIE_02, 20) )
        		send_user(who,"%c%s",':',sprintf("%s\n    不错！不错！你果然守信，说到做到。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),getoid(me)));
        	break;
	case 4:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 18) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_NEWBIE_02, 18);
			who->delete_save_2("baqiu_xiaomai");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,44,"酿酒的原材料" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"酿酒的原材料");	
		}
		break;
	case 5:
		if ( who->get_legend(TASK_NEWBIE_02, 19) && !who->get_legend(TASK_NEWBIE_02, 20) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"小麦",3) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->delete_save_2("baqiu_xiaomai");
			who->add_exp(220);
			who->add_potential(10);
			who->set_legend(TASK_NEWBIE_02, 20);
			send_user(who,"%c%s",';',"酿酒的原材料 经验 220 潜能 10");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,44,"" );			

		}
		break;
        case 6:
        	if ( who->get_level()>=5 && !who->get_legend(TASK_40, 22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我这酒店里提供的食物都是土生土长的，天上飞的，地上跑的，全是狩猎人给我送来的，保证绝对新鲜。\n    最近爱吃鱼的客人忽然就多了，原本供应鲜鱼的那位渔人有点忙不过来，我听说荒郊的孟大伯捕鱼技术不错，要不你去替我看看，看他是否愿意捕鱼了卖给我，也好解我燃眉之急。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
	       	break;
        case 7:
        	if ( who->get_level()>=5 && !who->get_legend(TASK_40, 22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_40,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,35,"食物的来源" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"食物的来源");
        	}
        	break;
        case 8:
		if( !who->get_legend(TASK_49, 18) )
        		send_user(who,"%c%s",':',sprintf("%s\n    我这家店虽然不大，但里面的美酒却名闻四方，很多客人远道前来品尝，生意非常红火。我在清溪有间小小的作坊，店里的美酒都是在那里酿造，没想到几天前一群小野兔跑进作坊里面偷吃，把我的作坊糟蹋得一塌糊涂。你去帮我教训教训这些小野兔，这些家伙一般在新手村外和清溪活动。\n"ESC"接受\ntalk %x# welcome.9\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_49, 19) && !who->get_legend(TASK_49, 20) )
        		send_user(who,"%c%s",':',sprintf("%s\n    多谢你帮我教训了它们，希望它们以后不要去我的作坊里面捣乱了，这里有几瓶我店里的米酒，你拿去尝尝吧，小心不要喝太多。\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开",me->get_name(),getoid(me)));
        	break;
	case 9:
		if( !who->get_legend(TASK_49, 18) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_49, 18);
			who->delete_save("jiudian_yetu");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,46,"偷吃的小野兔" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"偷吃的小野兔");	
		}
		break;
	case 10:
		if ( who->get_legend(TASK_49, 19) && !who->get_legend(TASK_49, 20) )
		{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;
			TASK_LEGEND_D->give_item(who,"item/stuff/0230",5); 
			TASK_LEGEND_D->task_finish(who);
			who->delete_save("jiudian_yetu");
			who->add_exp(150);
			who->add_potential(20);
			who->add_cash(500);
			who->set_legend(TASK_49, 20);
			send_user(who,"%c%s",';',"偷吃的小野兔 经验 150 潜能 20 金钱 500 米酒 5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,46,"" );			
		}
		break;
	case 99:
		TASK_COLLECT_D->do_talk_exchange( who, me,0015 );
		break;
        }
}

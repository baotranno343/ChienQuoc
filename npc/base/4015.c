
// 自动生成：/make/npc/make0015

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_talk_exchange();

void do_info();
void do_exchange(string sArg);
void do_inputx(string sArg);

// 函数：获取人物造型
int get_char_picid() { return 7415; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tửu Lâu");
	set_real_name("Mang Tử");

      	set_2( "talk", ([
                "info"  : (: do_info :),
                "do_exchange" : (: do_exchange :),
                "inputx"	: (: do_inputx :),   
                "exchange" : (: do_talk_exchange :),             	
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
                "10" : "/item/stuff/0165",
		"11" : "/item/stuff/0166",
		"12" : "/item/stuff/0167",
		"13" : "/item/stuff/0168",                
		"14" : "/item/stuff/0213",
		"15" : "/item/stuff/0214",
		"16" : "/item/stuff/0219",
		"17" : "/item/stuff/0220",
		"18" : "/item/stuff/0221",
		"19" : "/item/stuff/0222",                
		"20" : "/item/stuff/0223",
		"21" : "/item/stuff/0224",	
		"22" : "/item/stuff/0159",	
		"23" : "/item/32/3204",
        ]) );
//        set("level",24);
//        set("legend",({32*6+4}));
	set("mpLegend",([20:({32*6+4}),25:({32*6+13})]));
	set("mpLegend2",([20:({32*6+6}),25:({32*6+15})]));
        setup();
}

void do_talk_exchange()
{
	TASK_COLLECT_D->do_talk_exchange( this_player(), this_object(),4015 );
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
        if (who->get_level()>=20&&(!who->get_legend(TASK_06, 4)||!who->get_legend(TASK_06, 6)))
        {
        	tmp = sprintf(ESC HIY "狂妄的匪徒\ntalk %x# welcome.1\n",id);
        }
        if (who->get_level()>=25&&(!who->get_legend(TASK_06, 13)||!who->get_legend(TASK_06, 15)))
        {
        	tmp += sprintf(ESC HIY "巨鹿传说\ntalk %x# welcome.4\n",id);
        }
        tmp += sprintf(ESC"购买食物\nlist %x#\n", id);
//        tmp += sprintf(ESC"换取食物\ntalk %x# exchange\n",id);
        tmp += sprintf(ESC"坊间传闻\ntalk %x# info\n", id);
        tmp += ESC"离开\nCLOSE\n";
        send_user(who,"%c%s",':',get_name()+": \n    "+"/quest/word"->get_normal_word(this_object())+"\n    客官，需要换点什么吗？\n"+ tmp);
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
	TASK_COLLECT_D->do_exchange(sArg,4015);
}

void do_inputx(string sArg)
{
	object me,who;
	me = this_object(); who = this_player();
	TASK_COLLECT_D->do_inputx(me,who,sArg,4015);
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
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_06,4)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我上有老下有小，一大家人就靠我开这个酒店维持生活，我每天累死累活的就能糊个口，我容易吗？\n    可有个叫胡小四的家伙，他就欺负我老实，限定我每个月必须给他交30两银子的保护费，不然他就砸了我的店，可怜我这个酒店一个月还赚不了30两，这可如何是好啊！你能去马踏湖的鱼龙村替我教训他吗？从我这里过去，穿过马陵道、白马庄就到马踏湖了。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,4) && !who->get_legend(TASK_06,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    算了，我还是按时交纳贡饷，免得到时候性命不保。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,5) && !who->get_legend(TASK_06,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    %s果然厉害，这下再不用提心吊胆的过日子了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_06,4)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,20,"狂妄的匪徒" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"狂妄的匪徒");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_06,5) && !who->get_legend(TASK_06,6) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64009",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,6);
			who->add_exp(1600);
			who->add_potential(70);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"狂妄的匪徒 经验 1600 潜能 70 金钱 1500 细麻袍图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,20,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,13)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    用鹿角酿的酒再普通不过了，可是用玉鹿角酿的酒，我想普天之天，没有几个人尝过。\n    玉鹿，顾名思义，是皮毛像美玉一样晶莹剔透的一种鹿，世间罕见，而它的角更是价值连城，用玉鹿角酿出来的酒可以延年益寿，不少人想得到它，据我打听到的消息，这种鹿角还没有任何人找到过，平时酒店里人多口杂，我听到他们说在巨鹿附近有一枝巨鹿角，你是否有兴趣去寻找呢？因为玉鹿太珍贵，而知情的人又不多，所以你还得细心地慢慢地找寻，大概就在飞虎寨一带吧。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,13) && !who->get_legend(TASK_06,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来这稀世佳酿算是不可能出现了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,14) && !who->get_legend(TASK_06,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太好了，我一定将这神奇的酒酿造出来。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 5:
        	if ( who->get_level() >= 25 && !who->get_legend(TASK_06,13)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,23,"巨鹿传说" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"巨鹿传说");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_06,14) && !who->get_legend(TASK_06,15) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"玉鹿角",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,"item/product/65009",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,15);
			who->add_exp(1800);
			who->add_potential(80);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"巨鹿传说 经验 1800 潜能 80 金钱 1500 金项链图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,23,"" );
        	}
        	break;
        }
}
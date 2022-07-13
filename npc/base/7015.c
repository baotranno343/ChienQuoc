
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
void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5415; }

// 函数：构造处理
void create()
{
        set_name("Chủ Tửu Lâu");
	set_real_name("Tang Tôn");

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
//        set("level",46);
//        set("legend",({32*12+7}));
	set("mpLegend",([45:({32*12+7}),]));
	set("mpLegend2",([45:({32*12+9}),]));
        setup();
}

void do_talk_exchange()
{
	TASK_COLLECT_D->do_talk_exchange( this_player(), this_object(), 7015 );
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
        tmp += sprintf(ESC"购买食物\nlist %x#\n", id);
//        tmp += sprintf(ESC"换取食物\ntalk %x# exchange\n",id);
        tmp += sprintf(ESC"坊间传闻\ntalk %x# info\n", id);
	if ( ( who->get_level() >= 45 && !who->get_legend(TASK_12,7) ) || ( who->get_legend(TASK_12,7) && !who->get_legend(TASK_12,9) ) )
	{
		tmp += sprintf(ESC HIY "河道传说\ntalk %x# welcome.1\n",getoid(me));
	}
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
	TASK_COLLECT_D->do_exchange(sArg,7015);
}

void do_inputx(string sArg)
{
	object me,who;
	me = this_object(); who = this_player();
	TASK_COLLECT_D->do_inputx(me,who,sArg,7015);
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
        	if ( who->get_level() >=45 && !who->get_legend(TASK_12,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    在很久很久以前，曾经有一条蛟龙，它经常出现在郑国渠一带，可在某一次游玩时，它不小心将它最喜爱的宝龙珠遗落在那，寻找了很久，没有找到。最后，它郁郁而终……\n    后来，江湖盛传这颗宝龙珠能增加武术内力，所以大家都去寻找，可惜，至今为止，没有任何人找到，你去碰碰运气吧，或许能找到呢？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_12,7) && !who->get_legend(TASK_12,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道是我朋友骗我吗？不可能，我觉得这件事是真的。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_12,8) && !who->get_legend(TASK_12,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……我终于得到传说中的宝物了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_level() >=45 && !who->get_legend(TASK_12,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_12,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,3,"河道传说" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"河道传说");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_12,8) && !who->get_legend(TASK_12,9) )
        	{
			if ( TASK_LEGEND_D->check_task_item(who,"宝龙珠",1) != 1)
				return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_12,9);
			who->add_exp(4700);
			who->add_potential(180);
			who->add_cash(4000);
			send_user(who,"%c%s",';',"河道传说 经验 4700 潜能 180 金钱 4000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,3,"" );
        	}
        	break;   
        }
}
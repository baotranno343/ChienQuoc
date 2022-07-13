
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
void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5415; }

// 函数：构造处理
void create()
{
        set_name("Chủ Tửu Lâu");
	set_real_name("Thúc Hướng");

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
        setup();
 	set("mpLegend",([55:({32*50+28})]));
 	set("mpLegend2",([55:({32*50+30})]));

}

void do_talk_exchange()
{
	TASK_COLLECT_D->do_talk_exchange( this_player(), this_object(),5015 );
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
	if ( (who->get_level() >= 55 && !who->get_legend(TASK_2_00,28)) || 
		(who->get_legend(TASK_2_00,28) && !who->get_legend(TASK_2_00,30)) )
		tmp += sprintf(ESC HIY "大肆破坏\ntalk %x# welcome.1\n",id);
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
	TASK_COLLECT_D->do_exchange(sArg,5015);
}

void do_inputx(string sArg)
{
	object me,who;
	me = this_object(); who = this_player();
	TASK_COLLECT_D->do_inputx(me,who,sArg,5015);
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
		if ( who->get_level() >= 55 && !who->get_legend(TASK_2_00,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘘！噤声！我看你不是本地人，对秦国严刑峻法也看不惯的吧。秦王贪暴不仁，人人切齿。我奉王命前来，潜伏在这很久了，想要破坏骊山陵墓的建设，可是一直没有机会进行，你可以帮帮我吗？去杀掉那些苦役和工匠，就没有人帮他修陵了！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_2_00,28) && !who->get_legend(TASK_2_00,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，日子难过了……\n"ESC"离开", me->get_name(),));
		else if ( who->get_legend(TASK_2_00,29) && !who->get_legend(TASK_2_00,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈！太好了，这样我可以给上头交差了！这是给你的报酬，以后我就不认识你了……\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 2:
		if ( who->get_level() >= 55 && !who->get_legend(TASK_2_00,28) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_2_00,28);
        		who->delete_save("fb_sx_qlgj");
        		who->delete_save("fb_sx_qlky");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,102,"大肆破坏" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"大肆破坏");
		}
		break;        	
	case 3:
		if ( who->get_legend(TASK_2_00,29) && !who->get_legend(TASK_2_00,30) )
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_2_00,30);
        		who->delete_save("fb_sx_qlgj");
        		who->delete_save("fb_sx_qlky");
			who->add_exp(9800);
			who->add_potential(400);
			who->add_cash(19600);
			send_user(who,"%c%s",';',"大肆破坏 经验 9800 潜能 400 金钱 19600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,102,"" );
		}
		break;
        }
        
}
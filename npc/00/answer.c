#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <time.h>

#define ANSWER_TEMPLATE "quest/template"
inherit OFFICER;
void do_answer1(string arg);//回答问题模板
// 函数：获取人物造型
int get_char_picid() { return 0700; }

// 函数：构造处理
void create()
{
        set_name( "AYA狮子" );

        set_2( "talk", ([
                "answer"	: (: do_answer1:),
        ]));      
        setup();
}

// 函数：对话处理
void do_look( object who )
{
        object me = this_object();
        string tmp;
        int id = getoid(me);
 	tmp=sprintf(ESC"AYA狮子答题挑战\ntalk %x# answer.2\n",getoid(me));
	send_user( who, "%c%s", ':', me->get_name() + "：\n"+"比我丑的没我笨，比我笨的没我丑！你敢挑战我吗？我就是大名鼎鼎的战国智慧神AYA狮子～！！如果你连续答对10道题，可以获得本神的特别奖励哦～！\n" +
        tmp +
        ESC "离开\nCLOSE\n" );
}
void do_answer1(string arg)
{
	int day;
	mixed mxTime;
	object player = this_player();
	day = player->get_save_2("question.day");
	mxTime = localtime(time());
	if(mxTime[TIME_YDAY]!= day)
	{
		ANSWER_TEMPLATE->clear_tags(player);
		player->set_save_2("question.day",mxTime[TIME_YDAY]);//记录回答问题的第几天。
	}
	ANSWER_TEMPLATE->do_answer2(this_object(),arg);		
}

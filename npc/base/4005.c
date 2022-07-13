
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5405; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Trang Phục");
	set_real_name("Du Bá Nha");
        set_city_name("Ngụy Quốc");

        set_2( "good", ([
                "01" : "/item/60/7020",
                "02" : "/item/60/7030",
                "03" : "/item/60/7040",
                "04" : "/item/60/7050",
                "05" : "/item/60/7060",
                "06" : "/item/61/7020",
                "07" : "/item/61/7030",
                "08" : "/item/61/7040",
                "09" : "/item/65/7020",
                "10" : "/item/65/7030",
                "11" : "/item/65/7040",
                "12" : "/item/66/7020",
                "13" : "/item/66/7030",
                "14" : "/item/66/7040",

        ]) );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",22);
//	set("legend",({32*5+19}));        
 	set("mpLegend",([20:({32*5+19}),]));
 	set("mpLegend2",([20:({32*5+21}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	result += sprintf(ESC "哪里有适合我的装备？\ntalk %x# welcome.99\n", getoid(me) ) ;        	
	if ( ( who->get_level() >= 20 && !who->get_legend(TASK_05,19) ) || ( who->get_legend(TASK_05,19) && !who->get_legend(TASK_05,21) ) )
	{
		result += sprintf(ESC HIY "裁缝的梦想\ntalk %x# welcome.1\n",getoid(me));
	}
	result += sprintf( ESC "交易\nlist %x#\n" ESC "我只是随便看看\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), result );
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
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,19)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你知道千年蚕丝这个东西吗？它做成的衣服可以刀枪不入，冬暖夏凉。我一直想做一件这样的绝世宝衣，可千年蚕丝是可遇不可求的，所以这个愿望我一直没有达成，现在机会来了！\n    我听人说在马陵道的幽谷林里有一种蚕丝花，那些千年蚕偏爱这种花，所吐的丝也缠绕着它们，虽然能拿到千年蚕丝的机会不大，但是我还是想去试试，你替我跑一趟吧！\n    幽谷林中间的那丛白色的花就是蚕丝花了，你赶快去找找吧，去晚了机会更小。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_05,19) && !who->get_legend(TASK_05,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我得亲自前去寻找那传说中的千年蚕丝。不管是真是假，我都要将它找到来完成我的梦想。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_05,20) && !who->get_legend(TASK_05,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下太好了，我的梦想可以实现了。真不知道该如何报答你。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,19)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,15,"裁缝的梦想" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"裁缝的梦想");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_05,20) && !who->get_legend(TASK_05,21) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"千年蚕丝",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_05,21);
			who->add_exp(1100);
			who->add_potential(70);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"裁缝的梦想 经验 1100 潜能 70 金钱 1500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,15,"" );
        	}
        	break;
        case 99:	
		"/npc/base/0005"->do_welcome2(me, "99");
        	break;
        }
}
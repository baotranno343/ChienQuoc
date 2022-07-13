
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 3; }

// 函数：获取人物造型
int get_char_picid() { return 5404; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Vũ Khí");
	set_real_name("Trương Nghi");
        set_city_name("Ngụy Quốc");

        set_2( "good", ([
                "01" : "/item/79/1010",
                "02" : "/item/79/1020",
                "03" : "/item/79/1030",
                "04" : "/item/79/1040",

        ]) );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level", 21);
//        set("legend", ({ 32*5+10 }));   
 	set("mpLegend",([20:({32*5+10}),]));
 	set("mpLegend2",([20:({32*5+12}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	"/quest/help"->send_help_tips(who, 39);
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	result += sprintf(ESC "哪里有适合我的武器？\ntalk %x# welcome.99\n", getoid(me) ) ;        	
	if ( (who->get_level() >=20 && !who->get_legend(TASK_05, 10)) || (who->get_legend(TASK_05, 10) && !who->get_legend(TASK_05, 12)) )
	{
		result = result + sprintf( ESC HIY "锻造之路\ntalk %x# welcome.1\n", getoid(me) );
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
        	if ( who->get_level() >=20 && !who->get_legend(TASK_05, 10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿，你来得正好！\n    最近我这里生意大好，并且我发现像你们这样的武林中人对武器的要求实在是超乎我的想象，所以我决定锻造一批上好的武器来迎合你们的需求，当然，好的武器需要好的原材料，我现在缺的就是百炼精铁，听说有人在巨鹿的百丈原见过一块上好的百炼精铁，如果你想帮我这个忙的话，我绝不会亏待你的。\n    你出了魏国一直往北走，穿过桂陵、牧野、太行山就到巨鹿了，或者你可以从Triệu Quốc直接到巨鹿，这样可以节约不少时间，但是需要花费你一点路费哦。\n    到了巨鹿的百丈原你可以看到一块精铁矿石，采集回来交给我就是了。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_05,10) && !who->get_legend(TASK_05,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有找到吗？那可能是别人瞎说的！我自己再重新打听打听去。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_05,11) && !who->get_legend(TASK_05,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵！你看着吧！我一定打造出一把上好的武器。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,10)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,11,"锻造之路" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"锻造之路");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_05,11) && !who->get_legend(TASK_05,12) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"百炼精铁",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_05,12);
			who->add_exp(1000);
			who->add_potential(70);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"锻造之路 经验 1000 潜能 70 金钱 1200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,11,"" );
        	}
        	break;
        case 99:
        	"/npc/base/0004"->do_welcome2(me, "99");
        	break;
        }
}
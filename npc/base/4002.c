
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 有自己的do_look函数
int is_self_look() { return 1; }
// 函数：小贩识别
int is_seller() { return 5; }

// 函数：获取人物造型
int get_char_picid() { return 5402; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Tạp Hóa");
	set_real_name("Hồ Trành");
        set_city_name("Ngụy Quốc");

        set_2( "good", ([
                "01" : "/item/std/0401",
                "02" : "/item/std/0407",
                "04" : "/item/std/0409",
                "05" : "/item/std/0413",
                "06" : "/item/std/0591",
                "07" : "/item/32/3231",
                "08" : "/item/98/9871",
                "09" : "/item/std/9808",
                "10" : "/item/std/9819",
                "11" : "/item/std/9820",
		"12" : "/item/stuff/0505",
		"13" : "/item/stuff/0506",       
		"14" : "/item/49/4900",  	 
		"15" : "/item/std/0410",     
		"16" : "/item/08/0010",
		"17" : "/item/08/0011",
		"18" : "/item/08/0012", 
		"19" : "/item/44/4403",
		"20" : "/item/44/4406",
		"21" : "/item/stuff/0507",
        ]) );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//	set("level",22);
//	set("legend",({32*5+16}));
 	set("mpLegend",([20:({32*5+16}),]));
 	set("mpLegend2",([20:({32*5+18}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	"/quest/help"->send_help_tips(who, 41);
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	if ( (who->get_level() >= 20 && !who->get_legend(TASK_05, 16)) || (who->get_legend(TASK_05, 16) && !who->get_legend(TASK_05, 18)) )
	{
		result = result + sprintf( ESC HIY "英雄的磨练\ntalk %x# welcome.1\n", getoid(me) );
	}	

	result = result + sprintf( ESC "交易\nlist %x#\n" ESC "我只是随便看看\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%s", ':', result );

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
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,16)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    年纪轻轻的就想成为英雄？有志气是不错，但是得看你有没有那个能力！\n    你想证明给我看你有那个能力吗？好吧，你去马陵道的樱桃园打败那只骷髅魔，我得警告你，如果不行可别硬撑，那只骷髅魔很难缠，万一出了什么问题我可负不起这个责任。\n    你要去的话就朝着大梁城的正北方向走，一到马陵道你就能看到那只骷髅魔，记得要小心。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_05,16) && !who->get_legend(TASK_05,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    想成为英雄不是你想象的那么简单啊！看来你还得多磨练磨练。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_05,17) && !who->get_legend(TASK_05,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    小小年纪就已经具备成为英雄的潜质，前途无限啊！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,16)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,14,"英雄的磨练" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"英雄的磨练");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_05,17) && !who->get_legend(TASK_05,18) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->task_finish(who);
        		TASK_LEGEND_D->give_item(who,"item/product/64005",1);
			who->set_legend(TASK_05,18);
			who->add_exp(1100);
			who->add_potential(70);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"英雄的磨练 经验 1100 潜能 70 金钱 1200 随风行装图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,14,"" );
        	}
        	break;
        }
}

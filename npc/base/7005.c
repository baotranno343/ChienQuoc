
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
	set_real_name("Chung Tử Kì");
        set_city_name("Yên Quốc");

        set_2( "good", ([
                "01" : "/item/60/2020",
                "02" : "/item/60/2030",
                "03" : "/item/60/2040",
                "04" : "/item/60/2050",
                "05" : "/item/60/2060",
                "06" : "/item/61/2020",
                "07" : "/item/61/2030",
                "08" : "/item/61/2040",
                "09" : "/item/65/2020",
                "10" : "/item/65/2030",
                "11" : "/item/65/2040",
                "12" : "/item/66/2020",
                "13" : "/item/66/2030",
                "14" : "/item/66/2040",

        ]) );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",49);
//	set("legend",({32*13+4}));        
	set("mpLegend",([45:({32*13+4}),]));
	set("mpLegend2",([45:({32*13+6}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	if ( ( who->get_level() >= 45 && !who->get_legend(TASK_13,4) ) || ( who->get_legend(TASK_13,4) && !who->get_legend(TASK_13,6) ) )
		result += sprintf(ESC HIY "寒丝传说\ntalk %x# welcome.1\n",getoid(me));

	result += sprintf(ESC "哪里有适合我的装备？\ntalk %x# welcome.99\n", getoid(me) ) ;        	
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
        	if ( who->get_level() >= 45 && !who->get_legend(TASK_13,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    很小的时候，我就听师傅说过，寒丝是一种很难得的制衣原材料，我开了这么多年的服装店，也听说了不少关于寒丝的传闻，对这寒丝也慢慢的变得非常感兴趣。\n    最近我听说，在郑国渠一带出现过寒丝，你去替我找找行么？能找到的话，我一定不会亏待你！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_13,4) && !who->get_legend(TASK_13,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我得亲自出马，才能将那寒丝寻到。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_13,5) && !who->get_legend(TASK_13,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你了%s，真不知道该如何感谢你！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >=45 && !who->get_legend(TASK_13,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,12,"寒丝传说" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寒丝传说");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_13,5) && !who->get_legend(TASK_13,6) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"寒丝",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,6);
			who->add_exp(5400);
			who->add_potential(200);
			who->add_cash(5000);
			send_user(who,"%c%s",';',"寒丝传说 经验 5400 潜能 200 金钱 5000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,12,"" );
        	}
        	break; 
        case 99:
	        "/npc/base/0005"->do_welcome2(me, "99");
        	break;	  
        }
}
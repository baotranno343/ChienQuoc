
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
	set_real_name("Từ Phu Nhân");
        set_city_name("Yên Quốc");

        set_2( "good", ([
                "01" : "/item/72/1020",
                "02" : "/item/72/1030",
                "03" : "/item/72/1040",
                "06" : "/item/76/1020",
                "07" : "/item/76/1030",
                "08" : "/item/76/1040",
        ]) );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",47);
//	set("legend",({32*12+16}));
	set("mpLegend",([45:({32*12+16}),50:({32*13+13})]));
	set("mpLegend2",([45:({32*12+18}),50:({32*13+15})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	"/quest/help"->send_help_tips(who, 39);
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	if ( ( who->get_level() >= 45 && !who->get_legend(TASK_12,16) ) || ( who->get_legend(TASK_12,16) && !who->get_legend(TASK_12,18) ) )
		result += sprintf(ESC HIY "梦中奇闻\ntalk %x# welcome.1\n",getoid(me));
	if ( ( who->get_level() >= 50 && !who->get_legend(TASK_13,13) ) || ( who->get_legend(TASK_13,13) && !who->get_legend(TASK_13,15) ) )
		result += sprintf(ESC HIY "绝世神兵\ntalk %x# welcome.6\n",getoid(me));

	result += sprintf(ESC "哪里有适合我的武器？\ntalk %x# welcome.99\n", getoid(me) ) ;        	
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
	       	if ( who->get_level() >= 45 && !who->get_legend(TASK_12,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    昨晚梦中见一百姓在郑国渠一带哭喊着救命。今天就听说有人在那里失踪，你是否愿意前去打探一下？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_12,16) && !who->get_legend(TASK_12,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我所梦之事是真的，太可怕了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_12,17) && !who->get_legend(TASK_12,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下再也不会做这样的梦了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
          		
        	break;
	case 2:
        	if( who->get_level() >=45 && !who->get_legend(TASK_12,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_12,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,6,"梦中奇闻" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"梦中奇闻");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_12,17) && !who->get_legend(TASK_12,18) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64066",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_12,18);
			who->add_exp(5000);
			who->add_potential(180);
			who->add_cash(4500);
			send_user(who,"%c%s",';',"梦中奇闻 经验 5000 潜能 180 金钱 4500 唤云鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,6,"" );
        	}
        	break;   
	case 4:
        	if( who->get_level() >=50 && !who->get_legend(TASK_13,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,15,"绝世神兵" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"绝世神兵");
        	}
        	break;       
        case 5:
        	if ( who->get_legend(TASK_13,14) && !who->get_legend(TASK_13,15) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"巨灵神锤",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64075",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,15);
			who->add_exp(5700);
			who->add_potential(210);
			who->add_cash(4600);
			send_user(who,"%c%s",';',"绝世神兵 经验 5700 潜能 210 金钱 4600 战天甲图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,15,"" );
        	}
        	break;   
        case 6:
	       	if ( who->get_level() >= 50 && !who->get_legend(TASK_13,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    力大无比之人才能拿得起巨灵神锤，但是只要能拿起它，它的威力是常人无法想象的，除了能使你出招力度更大，还能增加你的内力，所以，巨灵神锤是不少武林中人梦寐以求的兵器。\n    据说有人在郑国渠一带见到这巨灵神锤，你去找找，看能不能找到。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_13,13) && !who->get_legend(TASK_13,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来此事是我平身最大的遗憾了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_13,14) && !who->get_legend(TASK_13,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵…这可真是太好了！真不知道该如何感谢你。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		break;        	
        case 99:
		"/npc/base/0004"->do_welcome2(me, "99");
        	break;
        }
}
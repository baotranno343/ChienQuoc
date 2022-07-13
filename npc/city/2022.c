
// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0451; }

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

int is_self_look() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Công Tượng");
        set_real_name("May Mặc 40~48");
        set_city_name("Hàn Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",19);
//	set("legend",({32*4+21}));
 	set("mpLegend",([15:({32*4+21}),]));
 	set("mpLegend2",([15:({32*4+22}),]));
	set_skill(0640, 39);
        set_2( "good", ([
                "01" : "/item/product/64048",
                "02" : "/item/product/64049",
                "03" : "/item/product/64050",
                "04" : "/item/product/64052",
                "05" : "/item/product/64053",
                "06" : "/item/product/64054",
                "07" : "/item/product/64055",
                "08" : "/item/product/64056",
                "09" : "/item/product/64057",
                "10" : "/item/product/64058",        
                "11" : "/item/product/64059",
                "12" : "/item/product/64060",
                "13" : "/item/product/64061",
                "14" : "/item/product/64062",      
                "15" : "/item/product/64063",
                "16" : "/item/product/64064",
                "17" : "/item/product/64065",
                "18" : "/item/product/64066",
                "19" : "/item/product/64067",
                "20" : "/item/product/64068",        
                "21" : "/item/product/64069",                                  
        ]) );		
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,21) ) || ( who->get_legend(TASK_04,21) && !who->get_legend(TASK_04,22) ) )
	{
		tmp = sprintf(ESC HIY "工匠的愿望\ntalk %x# welcome.1\n",getoid(me));
	}
	tmp += sprintf(ESC"Học kĩ năng\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"Mua công thức May Mặc 40 - 48\nlist %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}
int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 4 ); }
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
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,21)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不久前，婆婆上山采药，丢失了一棵佛龙珠。佛龙珠乃火龙修炼五百年之神物，能避寒取暖，冬天悬挂在屋内，温暖如春。我婆婆一直希望我能寻回佛龙珠，那是我家失传已久的宝物。据说最近有人在翠华山一带见到过，你能帮我寻回吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_04,21) && !who->get_legend(TASK_04,22) )
			me->do_welcome(3);
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,21)  )
        	{
	        	if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
	        	TASK_LEGEND_D->remove_task_item(who, "佛龙珠"); 
	       		who->set_legend(TASK_04,21);
			who->delete_save("folongzhu");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,10,"工匠的愿望" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"工匠的愿望");
        	}
        	break;
        case 3:
        	if ( !who->get_legend(TASK_04,21) || who->get_legend(TASK_04,22) )
        		return ;
        	if ( objectp(item=present("佛龙珠",who,1,MAX_CARRY)) && item->is_legend_item() == 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵！谢谢你啊！这下我的婆婆再也不会天天挂念着这件事情了。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我这愿望只能嘱咐我的儿子继续完成了。\n"ESC"离开", me->get_name()));
        	break;
        case 4:
        	if ( who->get_legend(TASK_04,21) && !who->get_legend(TASK_04,22) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"佛龙珠",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,22);
			who->delete_save("folongzhu");
			who->delete_save_2("folongzhu");
			who->add_exp(1800);
			who->add_potential(80);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"工匠的愿望 经验 1800 潜能 80 金钱 1500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,10,"" );
        	}
        	break;
        }
}
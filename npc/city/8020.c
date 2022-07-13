
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>
#include <task.h>
#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5416; }
void do_visit( string arg );
// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

int is_self_look() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Đầu Bếp Chu Quốc");
        set_real_name("Đầu Bếp1~80");
        set_city_name("Tề Quốc");
	set_skill(0610, 80);
        set_2( "talk", ([
                "visit"          : (: do_visit :),
        ]));  
        set_2( "good", ([
                "01" : "/item/product/61001",
                "02" : "/item/product/61002",
                "03" : "/item/product/61003",
                "04" : "/item/product/61004",
                "05" : "/item/product/61005",
                "06" : "/item/product/61006",
                "07" : "/item/product/61007",
                "08" : "/item/product/61008",
                "09" : "/item/product/61009",
                "10" : "/item/product/61010",
                "11" : "/item/product/61011",        
                "12" : "/item/product/61012",
                "13" : "/item/product/61013",
                "14" : "/item/product/61014",
                "15" : "/item/product/61015",      
                "16" : "/item/product/61016",
                "17" : "/item/product/61017",                                       
        ]) );	
 	set("mpLegend",([50:({32*50+4})]));
 	set("mpLegend2",([50:({32*50+6})]));
        setup();
}

void do_look( object who )
{
        object me = this_object();
	string cmd="";
	int id = getoid(me);
	if ( ( who->get_level() >=50 && !who->get_legend(TASK_2_00,4) ) || ( who->get_legend(TASK_2_00,4) && !who->get_legend(TASK_2_00,5) ) || ( who->get_legend(TASK_2_00,5) && !who->get_legend(TASK_2_00,6) ) ) 
		cmd = sprintf(ESC HIY "邪恶的厨师\ntalk %x# visit.1\n",id);
	if ( who->get_legend(TASK_2_00,20) && !who->get_legend(TASK_2_00,21) && who->get_save("baifang_js_0") != 1)
		cmd = sprintf(ESC HIY "拜访\ntalk %x# visit.4\n",getoid(me));
        send_user( who, "%c%c%w%s", ':', 3, 5416, 
        	sprintf("%s：\n    %s\n" +cmd+
	       	ESC "学习技能\nlearn ? %s\n" 
	       	ESC "购买酒食技能等级1-80级的配方\nlist %s\n"
        	ESC "关闭\nCLOSE\n", 
        	me->get_name(), "/quest/word"->get_country_word(this_object()), me->get_char_id(), me->get_char_id() ) );
}

void do_visit( string arg )
{
        object me = this_object();
        __FILE__ ->do_visit2(me, arg);
}

void do_visit2( object me, string arg )
{
	int flag,p;
	object who,item;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >=50 && !who->get_legend(TASK_2_00,4) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我从恩师学习厨艺，师傅德艺双馨，不光有厨艺还有一身好武艺。只是我比较不适合学武……我其实有一位师弟梁兴，他天生聪明，得到师傅大部真传，但却秉性不良，最后偷了师傅耗多年心血整理的师门祖传秘籍，打伤师傅，叛出师门……师傅又气又伤，就此一病不起，如今师傅病体缠绵将殁，唉！可叹我却无法为师傅报仇，诛却此贼。\n    看你似乎武艺高强，能否替我前去除掉他？听说他就在秦国成峤军营之中。\n"ESC"接受任务\ntalk %x# visit.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_2_00,4) && !who->get_legend(TASK_2_00,5) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来师弟武艺又提高了么……难道无法报仇了？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_2_00,5) && !who->get_legend(TASK_2_00,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉！师傅听说以后不知道会喜或是悲呢……\n"ESC"完成任务\ntalk %x# visit.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >=50 && !who->get_legend(TASK_2_00,4) ) 
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->delete_save("fb_002_001");
        		who->set_legend(TASK_2_00,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"Chu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,102,"邪恶的厨师" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"邪恶的厨师");
       		}
        	break;
        case 3:
        	if ( who->get_legend(TASK_2_00,5) && !who->get_legend(TASK_2_00,6) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->delete_save("fb_002_001");
        		who->set_legend(TASK_2_00,6);
			who->add_exp(6800);
			who->add_potential(400);
			who->add_cash(9600);
			send_user(who,"%c%s",';',"邪恶的厨师 经验 6800 潜能 400 金钱 9600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,102,"" );
		}
        	break;
        case 4:
		if ( who->get_legend(TASK_2_00,20) && !who->get_legend(TASK_2_00,21) && who->get_save("baifang_js_0") != 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你是新来的吧。既然大王派你来拜访我们，你可以到处看看，想学习什么技能。能够学习的生活技能除了酒食是不限制的以外，其他只能学习两种哦。如果不小心点错想忘记生活技能的话，可以去找申公豹。\n", me->get_name()));
			who->set_save("baifang_js_0",1);
			USER_TASK_D->send_task_intro(who,2,TID_ZHOUGUO,20);
		}
		if ( who->get_save("baifang_js_0") == 1 && who->get_save("baifang_js_1") == 1 && who->get_save("baifang_js_2") == 1 && who->get_save("baifang_js_2") == 1 && who->get_save("baifang_js_3") == 1 && who->get_save("baifang_js_4") == 1 && who->get_save("baifang_js_5") == 1 && who->get_save("baifang_js_6") == 1 && who->get_save("baifang_js_7") == 1 )
		{
			who->set_legend(TASK_2_00,21);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,20,"访问生活技能师傅(完成)" );
		}
        	break;
        }

}
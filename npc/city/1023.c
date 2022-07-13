
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0450; }
void do_welcome( string arg );

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
        set_name("Tề Quốc Công Tượng");
        set_real_name("Cơ Quan 61~79");
        set_city_name("Tề Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
        set_2( "good", ([
//                "01" : "/item/product/66037",
                "02" : "/item/product/66038",
                "03" : "/item/product/66039",
                "04" : "/item/product/66040",
                "05" : "/item/product/66041",
                "06" : "/item/product/66042",
                "07" : "/item/product/66043",
                "08" : "/item/product/66044",
                "09" : "/item/product/66045",
                "10" : "/item/product/66046",
                "11" : "/item/product/66047",        
                "12" : "/item/product/66048",
                "13" : "/item/product/66049",
                "14" : "/item/product/66050",
                "15" : "/item/product/66051",                                  
        ]) );
	set_skill(0660, 39);
 	set("mpLegend2",([70:({32*38+10}),]));
        setup();
}

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( who->get_level() >= 70 && who->get_legend(TASK_38,9) && !who->get_legend(TASK_38,10) )
		tmp += sprintf(ESC HIY "助人为乐\ntalk %x# welcome.1\n",getoid(me));
	
	tmp += sprintf(ESC"学习生活技能\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"购买Cơ Quan 技能等级61-79级的配方\nlist %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 8 ); }

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
        	if ( who->get_level() >= 70 && who->get_legend(TASK_38,9) && !who->get_legend(TASK_38,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天底下还是好人多啊！\n    就因为这些关心着我的人，我也会振作我自己的！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 2:
        	if ( who->get_level() >= 70 && who->get_legend(TASK_38,9) && !who->get_legend(TASK_38,10) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_38,10);
			who->add_exp(20000);
			who->add_potential(220);
			who->add_cash(25000);
			send_user(who,"%c%s",';',"助人为乐 经验 20000 潜能 220 金钱 25000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,49,"" );
        	}
        	break;  
        }
}
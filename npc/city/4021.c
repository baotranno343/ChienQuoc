
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0452; }
void do_welcome(string arg);

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
        set_name("Ngụy Quốc Công Tượng");
        set_real_name("Luyện Đơn 21~40");
        set_city_name("Ngụy Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",110);
//	set("legend",({32*39+5}));
	set("mpLegend",([105:({32*39+5,}),]));
	set_skill(0630, 39);
        set_2( "good", ([
                "01" : "/item/product/63007",
                "02" : "/item/product/63008",
                "03" : "/item/product/63009",
                "04" : "/item/product/63010",
                "05" : "/item/product/63011",
                "06" : "/item/product/63012",
                "07" : "/item/product/63013",
                "08" : "/item/product/63014",                
        ]) );		
        setup();
}

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( who->get_level() >= 105 && !who->get_legend(TASK_39,5) )
		tmp += sprintf(ESC HIY "手巧的工匠\ntalk %x# welcome.1\n",getoid(me));

	tmp += sprintf(ESC"学习生活技能\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"购买Luyện Đơn 技能等级21-40级的配方\nlist %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 2 ); }

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
			if ( who->get_level() >= 105 && !who->get_legend(TASK_39,5) )
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前些日子齐管家托我给他家小姐做一个首饰箱，并且交代要简单好用，式样也不需要太过华丽，因为他家小姐是一个很朴素的女子。\n    我做了好些日子才做好，用了上好的木材，朴素中不失档次，我想小姐一定会喜欢的。\n    请你帮我把这个首饰箱交给齐管家，如果我有时间的话我就自己去了，说实话，我还挺想见见那位与众不同的小姐。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
	        	break; 
	        case 2:
	        	if ( who->get_level() >= 105 && !who->get_legend(TASK_39,5) )
	        	{
	        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
	        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
	        			return ; 
				TASK_LEGEND_D->give_item(who,"item/98/0185",1); 
	        		who->set_legend(TASK_39,5);
				send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,68,"手巧的工匠" );
				send_user( who, "%c%s", '!', "得到任务 "HIY"手巧的工匠");
	        	}
	        	break;         	
        }
}
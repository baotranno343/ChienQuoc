
// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

int is_self_look() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 0451; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Công Tượng");
        set_real_name("May Mặc 1~29");
        set_city_name("Hàn Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",18);
//	set("legend",({32*4+19}));
 	set("mpLegend",([15:({32*4+19}),]));
 	set("mpLegend2",([15:({32*4+20}),]));
	set_skill(0640, 39);
        set_2( "good", ([
                "01" : "/item/product/64001",
                "02" : "/item/product/64002",
                "03" : "/item/product/64003",
                "04" : "/item/product/64004",
                "05" : "/item/product/64005",
                "06" : "/item/product/64006",
                "07" : "/item/product/64007",
                "08" : "/item/product/64008",
                "09" : "/item/product/64009",
                "10" : "/item/product/64010",
                "11" : "/item/product/64011",        
                "12" : "/item/product/64012",
                "13" : "/item/product/64013",
                "14" : "/item/product/64014",
                "15" : "/item/product/64015",      
                "16" : "/item/product/64016",
                "17" : "/item/product/64017",
                "18" : "/item/product/64018",
                "19" : "/item/product/64019",
                "20" : "/item/product/64020",
                "21" : "/item/product/64021",        
                "22" : "/item/product/64022",
                "23" : "/item/product/64023",
                "24" : "/item/product/64024",                                            
        ]) );	
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,19) ) || ( who->get_legend(TASK_04,19) && !who->get_legend(TASK_04,20) ) )
	{
		tmp = sprintf(ESC HIY "工匠的苦恼\ntalk %x# welcome.1\n",getoid(me));
	}
	tmp += sprintf(ESC"学习生活技能\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"购买May Mặc 技能等级1-29级的配方\nlist %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}
int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 1 ); }
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
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,19)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    修筑长城，抵御外侵。大王召我去修工事，可是我这人做工一定要喝米酒才能施展出神力，可惜家里的米酒已被喝完，你能帮我去找10坛米酒吗？我一定重重谢你。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_04,19) && !who->get_legend(TASK_04,20) )
			me->do_welcome(3);
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,19)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_04,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,9,"工匠的苦恼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"工匠的苦恼");
        	}
        	break;
        case 3:
        	if ( !who->get_legend(TASK_04,19) || who->get_legend(TASK_04,20) )
        		return ;
        	if ( TASK_LEGEND_D->check_task_item_amount(who,"米酒") >= 10  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈！%s谢谢你啊！这下我有力气做活了！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来这次做工得累跨我了。\n"ESC"离开", me->get_name()));
        	break;
        case 4:
        	if ( who->get_legend(TASK_04,19) && !who->get_legend(TASK_04,20) )
        	{
        		if (TASK_LEGEND_D->check_task_item1(who,"米酒",10) != 1 ) 
        			return;
        		TASK_LEGEND_D->give_item(who,"item/final/33/1700",3);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,20);
			who->add_exp(1600);
			who->add_potential(80);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"工匠的苦恼 经验 1600 潜能 80 金钱 1500 一口肉 3");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,9,"" );
        	}
        	break;
        }
}

// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0450; }
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
        set_name("Sở Quốc Công Tượng");
        set_real_name("Điêu Khắc 1~30");
        set_city_name("Sở Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",33);
//	set("legend",({32*8+22}));
	set("mpLegend",([30:({32*8+22})]));
	set("mpLegend2",([0:({32*33+21,}),30:({32*8+24,}),]));
	set_skill(0650, 39);
        set_2( "good", ([
                "01" : "/item/product/65001",
                "02" : "/item/product/65002",
                "03" : "/item/product/65003",
                "04" : "/item/product/65004",
                "05" : "/item/product/65005",
                "06" : "/item/product/65006",
                "07" : "/item/product/65007",
                "08" : "/item/product/65008",
                "09" : "/item/product/65009",
                "10" : "/item/product/65010",
                "11" : "/item/product/65011",        
                "12" : "/item/product/65012",
                "13" : "/item/product/65013",
                "14" : "/item/product/65014",
                "15" : "/item/product/65015",      
                "16" : "/item/product/65016",
                "17" : "/item/product/65017",
                "18" : "/item/product/65018",
                "19" : "/item/product/65019",
                "20" : "/item/product/65020",
                "21" : "/item/product/65021",                                                
        ]) );	
        setup();
}

// 函数：对话处理

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( ( who->get_level() >= 30 && !who->get_legend(TASK_08,22) ) || ( who->get_legend(TASK_08,22) && !who->get_legend(TASK_08,24) ) )
	{
		tmp = sprintf(ESC HIY "苍梧道的迷魂\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_33,20) && !who->get_legend(TASK_33,21) )
		tmp += sprintf(ESC HIY "归还工具\ntalk %x# welcome.4\n",getoid(this_object()));

	tmp += sprintf(ESC"学习生活技能\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"购买Điêu Khắc 技能等级1-30级的配方\nlist %s\n", me->get_char_id());
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
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大别山的苍梧道，你去过吗？\n    最近一段时间我常去那边做工，虽说那里悬崖陡峭，人烟稀少，但是一个人行走也从未出过事，直到那次……\n    那天活有点多，夜幕已笼罩了整个大地，我匆忙地往家赶，突然，我发现我的脚竟然不受我自己的控制，往悬崖边走去！当时，我惊呆了，我努力地想停住脚步，可我根本停不了！一直走到悬崖边缘，我眼看自己就要掉下悬崖，正在暗自着急的时候，又突然停了下来，我知道这附近有一只迷魂精灵，经常玩弄人，并且还使很多人无辜受伤甚至死去，所以我请你去一趟大别山的苍梧道，去将那害人的迷魂精灵给干掉！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_08,22) && !who->get_legend(TASK_08,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我下次再也不去那里做工了，还是自己的性命要紧。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_08,23) && !who->get_legend(TASK_08,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……下次再去那里做工就不用担心了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,20,"苍梧道的迷魂" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"苍梧道的迷魂");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_08,23) && !who->get_legend(TASK_08,24) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/16/1602",5);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,24);
			who->add_exp(2600);
			who->add_potential(90);
			who->add_cash(2000);
			send_user(who,"%c%s",';',"苍梧道的迷魂 经验 2600 潜能 90 金钱 2000 土制炸弹 5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,20,"" );
        	}
        	break;   
	case 4:
		if ( who->get_legend(TASK_33,20) && !who->get_legend(TASK_33,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我听说他发生了一些事情，还以为他没打算还给我了，没想到叫你送过来了，真是个守信用的人啊！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 5:
        	if ( who->get_legend(TASK_33,20) && !who->get_legend(TASK_33,21) )
        	{
			if ( TASK_LEGEND_D->check_task_item(who,"工匠的木槌",1) != 1)
				return;      		
			if ( TASK_LEGEND_D->check_task_item(who,"工匠的刨子",1) != 1)
			{
				TASK_LEGEND_D->give_item(who,"item/98/0157",1); 
				return;
			}
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,21);
        		who->delete_save("cgbxmuz");
        		who->delete_save("cgbxpaoz");
			who->add_exp(64000);
			who->add_potential(910);
			who->add_cash(55000);
			send_user(who,"%c%s",';',"保持距离 经验 64000 潜能 910 金钱 55000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,39,"" );
        	}
        	break;     
        }
}
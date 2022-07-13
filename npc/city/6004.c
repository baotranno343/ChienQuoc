
// 自动生成：/make/npc/make8004

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

void do_build( string arg );
void do_upgrade( string arg );
void do_plant( string arg );
void do_food( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Nội Chính Quan");
	set_real_name("Xuân Thân Quân");
        set_city_name("Sở Quốc");

        set_2( "talk", ([
                "build"         : (: do_build :),
                "upgrade"       : (: do_upgrade :),
                "plant"         : (: do_plant :),
                "food"          : (: do_food:),
                "welcome"	: (: do_welcome :),	
        ]) );
//	set("level",30);
//	set("legend",({32*8+1}));
 	set("mpLegend",([30:({32*8+1,32*9+7}),]));
 	set("mpLegend2",([0:({32*25+28,}),30:({32*8+3,32*9+9}),]));
        setup();
}

string get_master() { return CITY_CHU->get_master(); }
string get_master_2() { return CITY_CHU->get_master_2(); }
string get_master_3() { return CITY_CHU->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 30 && !who->get_legend(TASK_08,1) ) || ( who->get_legend(TASK_08,1) && !who->get_legend(TASK_08,3) ) )
	{
		tmp += sprintf(ESC HIY "守卫的衣服\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 30 && !who->get_legend(TASK_09,7) ) || ( who->get_legend(TASK_09,7) && !who->get_legend(TASK_09,9) ) )
	{
		tmp += sprintf(ESC HIY "珠丘的秘密\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( who->get_legend(TASK_25,27) && !who->get_legend(TASK_25,28) )
		tmp += sprintf(ESC HIY "与楚联盟\ntalk %x# welcome.7\n",getoid(me));
	if ("/sys/sys/count"->get_refine()&&who->get_city_name()==me->get_city_name())
		tmp += sprintf(ESC"收妖壶任务\ntalk %x# welcome.1000\n",getoid(me)); 
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INTERIOR_D->do_look( who, me ); 
	
}
void do_build( string arg ) { INTERIOR_D->do_build( this_player(), this_object(), arg ); }
void do_upgrade( string arg ) { INTERIOR_D->do_upgrade( this_player(), this_object(), arg ); }
void do_plant( string arg ) { INTERIOR_D->do_plant( this_player(), this_object(), arg ); }
void do_food( string arg ) { INTERIOR_D->do_food( this_player(), this_object(), arg ); }

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object( who, this_object(), obj ); }
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
        if (flag>=1000)
        {
        	"/sys/user/refine"->do_welcome(who, me, arg);
        	return;
        }        
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，终于找到一个能帮忙的人了。\n    据报，本国守卫的衣服已不足以御寒，但现在内政繁忙，不够人手去采购守卫的衣服，虽然数量不大，但也需要精挑细选，不仅要质量够好，足以御寒，还得物美价廉，据说沼泽一带的蛛蛛怪有一批很好的衣服，你看你是否跑上这一趟，我会按照衣服的质量付给你报酬的！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_08,1) && !who->get_legend(TASK_08,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果没有御寒的衣服，这些千里挑一的守卫会不会抗议呢？\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_08,2) && !who->get_legend(TASK_08,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你为我国做出了大贡献，我国守卫有了这些御寒的衣服，会更加尽力保护我们的楚城！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 2:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,1);
        		who->delete_save_2("cgyifu");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,13,"守卫的衣服" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"守卫的衣服");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_08,2) && !who->get_legend(TASK_08,3) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"衣服",6) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,3);
        		who->delete_save_2("cgyifu");
			who->add_exp(3500);
			who->add_potential(70);
			who->add_cash(3000);
			send_user(who,"%c%s",';',"守卫的衣服 经验 3500 潜能 70 金钱 3000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,13,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_09,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘘，这个事儿得小声点说！\n    我听别人说，有个宝物叫龙玉珠，遗失在大别山的珠丘一带，虽说我根本不知道这个宝物是用来干嘛的，但是直觉告诉我，它并不简单，如果流落到民间，可能会引起一场江湖争夺，到时候又不知道会有多少人葬身在这场江湖风暴下。\n    所以我派你去大别山的珠丘找到这颗龙玉珠，记住，千万不要走漏风声，不然会惹来杀身之祸！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_09,7) && !who->get_legend(TASK_09,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来必须我亲自带人去找才可以将那宝物寻到。\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,8) && !who->get_legend(TASK_09,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真是太好了！这下我可以将它献给大王，大王一定会更加重视我。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 5:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_09,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,25,"珠丘的秘密" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"珠丘的秘密");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_09,8) && !who->get_legend(TASK_09,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"龙玉珠",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_09,9);
			who->add_exp(2600);
			who->add_potential(100);
			who->add_cash(2100);
			send_user(who,"%c%s",';',"珠丘的秘密 经验 2600 潜能 100 金钱 2100");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,25,"" );
        	}
        	break;
	case 7:
        	if ( who->get_legend(TASK_25,27) && !who->get_legend(TASK_25,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    恩，“合纵”对抗强秦的确是一个不错的策略，但是我还必须把这封联盟函交给大王，让大王做决定。这位勇士你辛苦了，韩王安委托我给你的赏赐就在这里。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		break;		
	case 8:
        	if ( who->get_legend(TASK_25,27) && !who->get_legend(TASK_25,28) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"联盟函",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/61014",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_25,28);
			who->add_exp(36000);
			who->add_potential(540);
			who->add_cash(37000);
			send_user(who,"%c%s",';',"与楚联盟 经验 36000 潜能 540 金钱 37000 丰盛的晚餐图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,25,"" );
        	}
        	break;
        case 99:	
		INTERIOR_D->do_look( who, me); 
        	break;
        }

}

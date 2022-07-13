
// 自动生成：/make/npc/make8007

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define DIPLOMAT_D      "/inh/city/diplomat"

inherit OFFICER;

void do_relation( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Sử Tiết");
	set_real_name("Niếp Chính");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "relation"      : (: do_relation :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",17);
//	set("legend",({32*4+9}));
	set("mpLegend",([15:({32*4+9}),70:({32*22+24})]));
	set("mpLegend2",([15:({32*4+10}),70:({32*22+26})]));
        setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

void do_look( object who ) 
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,9) ) || ( who->get_legend(TASK_04,9) && !who->get_legend(TASK_04,10) ) )
	{
		tmp = sprintf(ESC HIY "出使重任\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 70 && !who->get_legend(TASK_22,24) ) || ( who->get_legend(TASK_22,24) && !who->get_legend(TASK_22,26) ) )
	{
		tmp += sprintf(ESC HIY "黄金鱼钩\ntalk %x# welcome.5\n",getoid(me));
	}
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		DIPLOMAT_D->do_look( who, this_object() ); 
	
}
void do_relation( string arg ) { DIPLOMAT_D->do_relation( this_player(), this_object(), arg ); }
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
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    百密必有一疏，大王派我出使秦国，可是我却将出使礼物玉龙睛弄丢了，离出使之日不远了。还望%s能帮我将那玉龙睛寻回来，本使定当酬谢。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_04,9) && !who->get_legend(TASK_04,10) )
			me->do_welcome(4);
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,9) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->remove_task_item(who, "玉龙睛");                   	
			who->delete_save("cushizhongren");
        		who->set_legend(TASK_04,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,4,"出使重任" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"出使重任");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_04,9) && !who->get_legend(TASK_04,10) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"玉龙睛",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,"item/final/33/1701",2);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,10);
			who->delete_save("cushizhongren");
			who->delete_save_2("cushizhongren");
			who->add_exp(1400);
			who->add_potential(70);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"出使重任 经验 1400 潜能 70 金钱 1200 烤地瓜 2");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,4,"" );
        	}
        	break;
        case 4:
        	if ( !who->get_legend(TASK_04,9) || who->get_legend(TASK_04,10) )
        		return ;
        	if ( objectp(item=present("玉龙睛",who,1,MAX_CARRY)) && item->is_legend_item() == 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下好了，有了玉龙睛我就可以完成这出使的重任了，%s真不知该如何报答你。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下完了，出使的时候拿不出玉龙睛，大王一定会杀了我的。\n"ESC"离开", me->get_name()));
        	break;
        case 5:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_22,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我特别喜欢钓鱼，据说在无定河畔有一种罕见的黄金鲤鱼，钓到这样的一条黄金鲤鱼是我们钓鱼者一生的愿望，当然这种黄金鲤鱼不是说钓就能钓的，钓这种鱼的钓具非常讲究，首先要有桂木做的鱼杆和桂木香料做鱼饵，还要用银丝做鱼丝，最后还需要用黄金做鱼钩，其他的我都已经准备好了，现在唯一缺少的就是做鱼钩的黄金，听说在弯道就有很多这些黄金。你能帮我去找些做鱼钩的黄金吗？如果你找到的话我会好好酬谢你的。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_22,24) && !who->get_legend(TASK_22,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，如果这鱼竿没有黄金鱼钩，会是多大的遗憾啊！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_22,25) && !who->get_legend(TASK_22,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这些黄金，我就可以请最好的工匠来给我锻造黄金鱼钩了。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 6:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_22,24) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_22,24);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,42,"金钩桂饵" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"金钩桂饵");
        	}
        	break;  
        case 7:
        	if ( who->get_legend(TASK_22,25) && !who->get_legend(TASK_22,26) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"黄金",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,26);
			who->add_exp(27000);
			who->add_potential(448);
			who->add_cash(25600);
			send_user(who,"%c%s",';',"金钩桂饵 经验 27000 潜能 448 金钱 25600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,42,"" );
        	}
        	break;
        case 99:	
		DIPLOMAT_D->do_look( who, me); 
        	break;
        }
}
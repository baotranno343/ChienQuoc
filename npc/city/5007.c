
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
        set_name("Tần Quốc Sử Tiết");
	set_real_name("Vương Ngạo");
        set_city_name("Tần Quốc");

        set_2( "talk", ([
                "relation"      : (: do_relation :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",68);
//	set("legend",({32*21+15,}));
	set("mpLegend",([65:({32*21+15}),]));
	set("mpLegend2",([0:({32*16+7}),65:({32*21+19}),]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if (  who->get_legend(TASK_16,6) && !who->get_legend(TASK_16,7)  )
	{
		tmp = sprintf(ESC HIY "赵国来访\ntalk %x# welcome.1\n",getoid(me));
	}
	if (  who->get_level() >= 65 && !who->get_legend(TASK_21,15)  )
	{
		tmp += sprintf(ESC HIY "准备出使\ntalk %x# welcome.3\n",getoid(me));
	}
	if (  (who->get_legend(TASK_21,16) && !who->get_legend(TASK_21,17)) || (who->get_legend(TASK_21,17) && !who->get_legend(TASK_21,19)) )
	{
		tmp += sprintf(ESC HIY "出使之难\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,19) && !who->get_legend(TASK_21,20) )
	{
		tmp += sprintf(ESC HIY "出使信函\ntalk %x# welcome.3\n",getoid(me));
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
        	if ( who->get_legend(TASK_16,6) && !who->get_legend(TASK_16,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这赵使节可受赵王赏识呀，这次又是派他出使我国。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_legend(TASK_16,6) && !who->get_legend(TASK_16,7) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_16,7);
			who->add_exp(5500);
			who->add_potential(230);
			who->add_cash(5100);
			send_user(who,"%c%s",';',"出使秦国 经验 5500 潜能 230 金钱 5100");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,8,"" );
        	}
        	break;   
        case 3:
        	if (  who->get_level() >= 65 && !who->get_legend(TASK_21,15)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现今齐国联合诸国意欲图谋我国，本使以为，我国与赵国本是同根生，都是大神蚩尤的子孙，如若修缮赵国的关系应该是最为容易，况且兄弟一心，其利断金，这样子既可破坏齐国意欲联合六国图谋我们的计划，也可以让赵国工商之利与我国矿产之丰互利互助，可谓互有裨益。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,16) && !who->get_legend(TASK_21,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本使虽然志在必得，然而却有他国奸细不愿我们秦赵修好，最近本使收到密报，有个叫做石七的奸细意欲破坏我们两家友好，意欲在我出使的路上行刺本使，本使死不足惜，叹只叹我秦赵兄弟之盟不成，反为外人所乘啊，据说那刺客埋伏在秦长城匝道一带，你可愿意前去将他铲除吗？\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,17) && !who->get_legend(TASK_21,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不杀掉那个奸细，恐怕这次出使，我将有性命之危，还望你全力以赴。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_21,18) && !who->get_legend(TASK_21,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下出使赵国就不用担心自己的性命了。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_21,19) && !who->get_legend(TASK_21,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    虽然说秦赵是同宗兄弟之邦，但是这次出使，我希望能够更好完成出使重任，加强胜算，我当初同赵国使节毛遂也有点交情，如果他能够在赵王迁身边吹吹风可以降低我出使的难度，但我使团行程已定，你能代我先行将出使信函交与赵国使节毛遂吗？\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
	case 4:
        	if (  who->get_level() >= 65 && !who->get_legend(TASK_21,15)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_21,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,33,"准备出使" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"准备出使");
        	}
        	break;
	case 5:
        	if ( who->get_legend(TASK_21,16) && !who->get_legend(TASK_21,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_21,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,34,"出使之难" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"出使之难");
        	}
        	break;
	case 6:
        	if ( who->get_legend(TASK_21,18) && !who->get_legend(TASK_21,19) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,19);
			who->add_exp(16500);
			who->add_potential(370);
			who->add_cash(16000);
			send_user(who,"%c%s",';',"出使之难 经验 16500 潜能 370 金钱 16000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,34,"" );
			me->do_welcome(3);
        	}
        	break;
	case 7:
        	if ( who->get_legend(TASK_21,19) && !who->get_legend(TASK_21,20) )
        	{
 			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
 			item = new("/item/98/0098");
 			p = item->move(who,-1);
 			if ( !p )
 			{
 				destruct(item);
 				send_user(who,"%c%s", '!', "你携带的物品太多了");	
 				return ;
 			}
 			item->add_to_user(p);
        		who->set_legend(TASK_21,20);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,35,"出使信函" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"出使信函");
        	}
        	break;
        case 99:	
		DIPLOMAT_D->do_look( who, me); 
        	break;
        }
}
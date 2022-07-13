
// 自动生成：/make/npc/make8010

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0651; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tần Quốc Thủ Vệ");
        set_city_name("Tần Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",43);
//        set("legend",({32*11+11}));
	set("mpLegend",([40:({32*11+11}),110:({32*43+17})]));
	set("mpLegend2",([40:({32*11+13}),]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who ) 
{ 
	string tmp="";
	object me = this_object();
        if ( (who->get_level() >= 40 && !who->get_legend(TASK_11,11)) || (who->get_legend(TASK_11,11)&&!who->get_legend(TASK_11,13)) ) 
		tmp += sprintf(ESC HIY "魔晴石\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_level() >= 110 && !who->get_legend(TASK_43,17) ) 
		tmp += sprintf(ESC HIY "朋友的帮助\ntalk %x# welcome.4\n",getoid(this_object())); 

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look_3( who, me ); 
	
}

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
        	if (who->get_level() >= 40 && !who->get_legend(TASK_11,11))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    一直以来，我都酝酿着要做件大事，当然，我是不会告诉你，我想要做什么的。如果你愿意帮助我成了这件大事，我一定不会亏待你的！\n    你先去给我找10个魔晴石来，去郑国渠就能收集到！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_11,11) && !who->get_legend(TASK_11,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果此事不成，你可得负担一半的责任！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_11,12) && !who->get_legend(TASK_11,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此事成功后，我一定会再给报酬给你的！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if(who->get_level() >= 40 && !who->get_legend(TASK_11,11))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_11,11);
        		who->delete_save_2("moqingshi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,7,"魔晴石" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"魔晴石");
        	}
        	break;
       case 3:
        	if ( who->get_legend(TASK_11,12) && !who->get_legend(TASK_11,13) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"魔晴石",10) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,13);
        		who->delete_save_2("moqingshi");
			who->add_exp(5800);
			who->add_potential(186);
			who->add_cash(4000);
			send_user(who,"%c%s",';',"魔晴石 经验 5800 潜能 186 金钱 4000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,7,"" );
        	}
        	break;     
        case 4:
        	if (who->get_level() >= 110 && !who->get_legend(TASK_43,17))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天有不测风云，人有旦夕祸福，谁知道好好的闺女怎么摊上这摊子毛病呢，城中百姓家中几个闺女最近每日夜里都闹头疼，请了几个大夫来都没有治好，越发作越厉害，眼睁睁看着活鲜鲜的大闺女那副痛不欲生的模样人都揪心啊。听说天门阵中多藏灵丹妙药，其中一味救急丹可以压制头疼，请大侠多加援手帮忙弄5颗救急丹给百姓吧，在此代表秦国百姓仲莫多谢你了。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 5:
        	if (who->get_level() >= 110 && !who->get_legend(TASK_43,17))
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_43,17);
        		who->delete_save("qgswjiujd");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,59,"朋友的帮助" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"朋友的帮助");
        	}
		break;
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;     
        }
}
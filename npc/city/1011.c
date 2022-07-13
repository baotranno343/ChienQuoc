
// 自动生成：/make/npc/make8010

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5209; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tề Quốc Thủ Vệ");
        set_city_name("Tề Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",81);
//        set("legend",({32*27+4}));
 	set("mpLegend",([80:({32*27+4}),85:({32*38+17})]));
 	set("mpLegend2",([80:({32*27+6}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();

	if ( (who->get_level() >= 80 && !who->get_legend(TASK_27,4)) || (who->get_legend(TASK_27,4) && !who->get_legend(TASK_27,6)))
	{
		tmp = sprintf(ESC HIY "侍卫亡灵\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 85 && !who->get_legend(TASK_38,17) )
		tmp += sprintf(ESC HIY "询问价格\ntalk %x# welcome.4\n",getoid(me));

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
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    在灵谷洞出没那些侍卫亡灵其实都是一些我们以前战死的战友，但是自从长平之战后，他们的灵魂被人操纵了，得不到安息。我们看到自己昔日的战友死后也得不到安息当然心里面是不舒服了。你能不能帮我们去灵谷洞解决这些亡灵侍卫，让他们得到安息？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_27,4) && !who->get_legend(TASK_27,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看着我们那些昔日的战友死后还要成为亡灵侍卫不得安息，我们心里面就像悬着块大石头放不下来一样。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_27,5) && !who->get_legend(TASK_27,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听到我们那些昔日的战友终于得到安息了，我们的心终于也放下来了。感谢你的帮忙，我想我们那些昔日战友在天之灵也会感激你的。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 2:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_27,4);
        		who->delete_save_2("qgswshiwwl");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,21,"侍卫亡灵" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"侍卫亡灵");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_27,5) && !who->get_legend(TASK_27,6) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_27,6);
        		who->delete_save_2("qgswshiwwl");
			who->add_exp(45000);
			who->add_potential(640);
			who->add_cash(44500);
			send_user(who,"%c%s",';',"侍卫亡灵 经验 45000 潜能 640 金钱 44500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,21,"" );
        	}
        	break;
        case 4:
       		if ( who->get_level() >= 85 && !who->get_legend(TASK_38,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    魏国商人那里有一批需要尽快处理的布匹出售，并且这批布并不是因为有质量问题才出售的，而是因为魏国商人要转行做别的生意，急需启动资金，所以才贱卖，这可是个好机会，或许我可以从买进卖出中小赚一笔，你去帮我问问魏国商人，那批布到底什么价格，你可不能自己偷偷的买走啊。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		break; 
	case 5:
		if ( who->get_level() >= 85 && !who->get_legend(TASK_38,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,75,"询问价格" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询问价格");
        	}
		break;
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;     
        }
}
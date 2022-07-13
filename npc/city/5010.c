
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
//        set("legend",({32*10+29}));
	set("mpLegend",([40:({32*10+29}),60:({32*19+22}),100:({32*39+11})]));
	set("mpLegend2",([100:({32*39+13})]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
        if ( (who->get_level() >= 40 && !who->get_legend(TASK_10,29)) || (who->get_legend(TASK_10,29)&&!who->get_legend(TASK_10,30)) ) 
		tmp += sprintf(ESC HIY "兄弟情深\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_level() >= 60 && !who->get_legend(TASK_19,22)) || (who->get_legend(TASK_19,22)&&!who->get_legend(TASK_19,23)) ) 
		tmp += sprintf(ESC HIY "找吕不韦谈谈\ntalk %x# welcome.3\n",getoid(this_object())); 
        if ( (who->get_level() >= 100 && !who->get_legend(TASK_39,11)) || (who->get_legend(TASK_39,11)&&!who->get_legend(TASK_39,13)) ) 
		tmp += sprintf(ESC HIY "控制数量\ntalk %x# welcome.5\n",getoid(this_object())); 

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
        	if (who->get_level() >= 40 && !who->get_legend(TASK_10,29))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我有个哥哥，也在做守卫，可他在燕国，我已经很久没有见到他了，请你把我的想念之情带给我哥哥好吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,29) && !who->get_legend(TASK_10,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我哥哥也想念我了吧？他还说了别的吗？\n"ESC"离开", me->get_name()));
        	break;
        case 2:
        	if(who->get_level() >= 40 && !who->get_legend(TASK_10,29))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,8,"兄弟情深" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"兄弟情深");
        	}
        	break;
	case 3:
        	if (who->get_level() >= 60 && !who->get_legend(TASK_19,22))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    吕不韦说你是他的心腹知交，托人四处找你，他最近有个事情要找你，你赶快回去赵国的赵府吧，说不定你立了什么大功赏赐抵的上你数年辛劳呢。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_19,22) && !who->get_legend(TASK_19,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你赶快去吧，他已经等急了。\n"ESC"离开", me->get_name()));
        	break;
        case 4:
        	if(who->get_level() >= 60 && !who->get_legend(TASK_19,22))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_19,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,22,"找吕不韦谈谈" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"找吕不韦谈谈");
        	}
        	break;
	case 5:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_39,11) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天门阵最近盲目扩招，使得守卫数量急剧增加，既严重威胁了本国的治安，他们的粮草储备也告急，最近他们的阵主私底下传函我王，希望能够借我王之手裁掉一部分不合格的守卫，同时减少开支，本着友邻互助的原则，我王在象征性的收取了他一坛美酒之后同意这种一举两得的合作要求，作为本国的十佳国民，你应该尽你一份义务，前去消灭5个天罡门众守、7个守阵天兵、7个守阵神将，至于原则，就以容易下手不伤己军为原则，不过千万不要杀多了，现在天门阵的阵主夫人还在同我王饮酒，你牢记要树立良好信誉，注意国际舆论影响，杀完之后回来报告我吧，我会转告大王的。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_39,11) && !who->get_legend(TASK_39,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我王对你这么低效率很有不满呢，说不定你的十佳国民称号是要改改了。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_39,12) && !who->get_legend(TASK_39,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，不错不错，不多不少，你拿好慢走，阵主夫人说了，今后欢迎你到天门阵做客，不过记得要戴面具哟。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 6:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_39,11) ) 
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,11);
        		who->delete_save("qgswtiangmzs");
        		who->delete_save("qgswsouztb");
        		who->delete_save("qgswsouzsj");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,55,"控制数量" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"控制数量");
        	}
        	break;
	case 7:
        	if ( who->get_legend(TASK_39,12) && !who->get_legend(TASK_39,13) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_39,13);
        		who->delete_save("qgswtiangmzs");
        		who->delete_save("qgswsouztb");
        		who->delete_save("qgswsouzsj");
			who->add_exp(80000);
			who->add_potential(960);
			who->add_cash(70000);
			send_user(who,"%c%s",';',"控制数量 经验 80000 潜能 960 金钱 70000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,55,"" );
        	}
        	break;
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;     
        }
}
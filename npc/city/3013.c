
// 自动生成：/make/npc/make8012

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_out();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 0600; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Thủ Vệ");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "out"           : (: do_out :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 12);
        set("out", 10);
//        set("level",83);
//        set("legend",({32*28+7}));
 	set("mpLegend",([80:({32*28+7,32*38+15}),]));
 	set("mpLegend2",([80:({32*28+9,}),]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who ) 
{ 
	string tmp="";
	object me = this_object();

	if ( (who->get_level() >= 80 && !who->get_legend(TASK_28,7)) || (who->get_legend(TASK_28,7) && !who->get_legend(TASK_28,9)))
	{
		tmp = sprintf(ESC HIY "木箱的秘密\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_28,9) && !who->get_legend(TASK_28,10) )
		tmp += sprintf(ESC HIY "开启木箱的钥匙\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_level() >= 80 && !who->get_legend(TASK_38,15) )
		tmp += sprintf(ESC HIY "弟弟的问候\ntalk %x# welcome.5\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look_2( who, me ); 
	
}

void do_out() { GUARDER_D->do_out( this_player(), this_object() ); }

void do_record() { GUARDER_D->do_record( this_player(), this_object() ); }

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
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_28,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我的记忆有些模糊了，但是我会尽量把我记得的细节告诉你。在万人坑的最底层有一只木箱，这是武林人士一辈子梦寐以求的东西，或许，它是一把开启财富之门的钥匙！\n    但是，我要警告你，%s，在万人坑潜伏着可怕的鬼怪，它们会忠心的守护着那只木箱。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),who->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_28,7) && !who->get_legend(TASK_28,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    或许那些守护着木箱的鬼怪太厉害，我看你还是找人帮助你吧！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_28,8) && !who->get_legend(TASK_28,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这只木箱完全密封，如果砸碎它恐怕不太合适，万一砸碎了里面的宝物可就得不偿失了，看来还需要一把钥匙。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_28,9) && !who->get_legend(TASK_28,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我只听说这城外有个王铁匠，我想既然他会打铁，那么打造一把钥匙应该也会很容易的，你去找他问问看。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 2:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_28,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,47,"木箱的秘密（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"木箱的秘密（1）");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_28,8) && !who->get_legend(TASK_28,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"木箱",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,9);
			who->add_exp(26000);
			who->add_potential(445);
			who->add_cash(25000);
			send_user(who,"%c%s",';',"木箱的秘密（1） 经验 26000 潜能 445 金钱 25000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,47,"" );
        		me->do_welcome(1);
        	}
        	break; 
	case 4:
        	if ( who->get_legend(TASK_28,9) && !who->get_legend(TASK_28,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,48,"木箱的秘密（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"木箱的秘密（2）");
        	}
        	break;
        case 5:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_38,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我哥哥去齐国做生意已经很久了，他一直都没有回家，我都不知道他现在过得好不好，听人说他的生意是越做越大啊，不止卖了西瓜、橘子、梨，连菠萝、香蕉他都有卖哦，还开了家分店专卖肉类，不如你去替我问问他的情况吧，告诉他，我和家人都很想念他。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 6:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_38,15) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,65,"弟弟的问候" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"弟弟的问候");
        	}
        	break;
        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;     
        }
}
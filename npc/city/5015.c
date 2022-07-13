
// 自动生成：/make/npc/make8014

#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <task.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_enter();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 0651; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tần Quốc Thủ Vệ");
        set_city_name("Tần Quốc");

        set_2( "talk", ([
                "enter"         : (: do_enter :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("out", 10);
        set("in", 12);
//       	set("level",40);
//	set("legend",({32*38+1}));
	set("mpLegend",([35:({32*38+1})]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{
	int id; 
	string tmp="";
	object me = this_object();
	
	id = getoid(me);
	if ( who->get_level() >= 35 && !who->get_legend(TASK_38,1) )
		tmp += sprintf(ESC HIY "紫葡萄\ntalk %x# welcome.1\n",id);

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look( who, me ); 
	
}
void do_enter() { GUARDER_D->do_enter( this_player(), this_object() ); }

void do_record() { GUARDER_D->do_record( this_player(), this_object() ); }

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
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_38,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那燕总管素来爱吃葡萄，他听说我家种了不少紫葡萄，垂涎三尺。他前些日子连续托人来向我买葡萄，可是这葡萄还没成熟，我当然不能卖给他，不然就砸了我自己的招牌。现在葡萄好了，我先送串去给他尝尝，如果他觉得好吃，再来买我的也不迟，麻烦你将这串葡萄送到燕总管手上。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_38,1) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/98/0181",1);
        		who->set_legend(TASK_38,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,90,"紫葡萄" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"紫葡萄");
        	}
        	break;
 
        case 99:
        	GUARDER_D->do_look( who, me ); 
        	break;
        }
}
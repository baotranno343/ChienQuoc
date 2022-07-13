
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
        set_name("Hàn Quốc Thủ Vệ");
        set_city_name("Hàn Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",70);
//        set("legend",({32*38+9}));
 	set("mpLegend",([65:({32*38+9,}),]));
 	set("mpLegend2",([75:({32*38+12,}),]));
        setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();

	if ( who->get_level() >= 65 && !who->get_legend(TASK_38,9) )
		tmp += sprintf(ESC HIY "助人为乐\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_level() >= 75 && who->get_legend(TASK_38,11) && !who->get_legend(TASK_38,12) )
		tmp += sprintf(ESC HIY "答谢\ntalk %x# welcome.3\n",getoid(me));

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
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_38,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    齐国工匠家遭到山贼洗劫一空，夫人女儿都惨死在山贼的刀下，只留下齐国工匠一人在家忍受着悲痛，孤独与茫然……\n    我想，虽然我和他不是亲人，不是朋友，甚至我们不同国家，但是我想伸出我的援助之手来帮助他，帮助他缓解这一连串的打击，帮助他度过这段最难熬的时间，帮助他恢复对生活的信心。\n    你去一趟齐国，将我的意思转达给齐国工匠，并告知他，不久我将前去齐国，陪伴他走过这段日子。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_38,9) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,49,"助人为乐" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"助人为乐");
        	}
        	break;
        case 3:
       		if ( who->get_level() >= 75 && who->get_legend(TASK_38,11) && !who->get_legend(TASK_38,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果真像你说的这样，那真是太好了，我也希望他能早日振作起来！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		
		break;
        case 4:
       		if ( who->get_level() >= 75 && who->get_legend(TASK_38,11) && !who->get_legend(TASK_38,12) )
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_38,12);
			who->add_exp(25000);
			who->add_potential(230);
			who->add_cash(25000);
			send_user(who,"%c%s",';',"答谢 经验 25000 潜能 230 金钱 25000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,74,"" );
        	}
		break;
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;     
        }
}

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
int get_char_picid() { return 5209; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tề Quốc Thủ Vệ");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "out"           : (: do_out :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 13);
        set("out", 11);
//        set("level",82);
//        set("legend",({32*27+22}));
 	set("mpLegend",([80:({32*27+22})]));
 	set("mpLegend2",([80:({32*27+24})]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();

	if ( (who->get_level() >= 80 && !who->get_legend(TASK_27,22)) || (who->get_legend(TASK_27,22) && !who->get_legend(TASK_27,24)))
	{
		tmp = sprintf(ESC HIY "悔恨的守卫\ntalk %x# welcome.1\n",getoid(me));
	}
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
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我的父亲一直念念不忘灵谷洞，说是他见过最美丽的地方，结果不顾一把年纪还偷偷前往，结果得知父亲前去后赶到的乡亲只抢回了奄奄一息的父亲，没两天他老人家就过世了，但他过世时虽然满身是伤，居然还是含笑的，灵谷洞这个所谓最美丽的地方也是有妖魔的地方啊，只恨当初我们点起人手去扫荡的时候竟然被上面阻止，说是莫将仙灵之地染满污秽，我职责所限，不敢私自违背命令前去，但恳求大侠为我走一趟，铲除10只铁甲尸为我父亲报仇。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_27,22) && !who->get_legend(TASK_27,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果此生不能报此仇，我想我到死都不会瞑目的。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_27,23) && !who->get_legend(TASK_27,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    干掉这些铁甲尸，也算是给我父亲报仇了，我要好好的报答你！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 2:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_27,22);
        		who->delete_save("qgswtiejiasi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,23,"悔恨的守卫" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"悔恨的守卫");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_27,23) && !who->get_legend(TASK_27,24) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_27,24);
        		who->delete_save("qgswtiejiasi");
			who->add_exp(45000);
			who->add_potential(638);
			who->add_cash(43800);
			send_user(who,"%c%s",';',"悔恨的守卫 经验 45000 潜能 638 金钱 43800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,23,"" );
        	}
        	break; 
        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;     
        }
}
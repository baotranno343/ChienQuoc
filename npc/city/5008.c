
// 自动生成：/make/npc/make8008

#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <task.h>

#define WARDER_D        "/inh/city/warder"

inherit OFFICER;

void do_faling();
void accept_task();

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tần Quốc Giám Ngục Quan");
        set_city_name("Tần Quốc");

        set_2( "talk", ([
                "faling"        : (: do_faling :),
                 "accept_task"	: (: accept_task :),
                 "welcome"          : (: do_welcome :),
        ]) );
//	set("level",63);
//	set("legend",({32*19+19}));
 	set("mpLegend",([60:({32*19+19}),]));
 	set("mpLegend2",([0:({32*22+7,32*22+15,}),60:({32*19+21}),]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 60 && !who->get_legend(TASK_19,19) ) || ( who->get_legend(TASK_19,19) && !who->get_legend(TASK_19,21)) )
	{
		tmp += sprintf(ESC HIY "追捕逃犯\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_22,6) && !who->get_legend(TASK_22,7) )
	{
		tmp += sprintf(ESC HIY "真相大白\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( who->get_legend(TASK_22,14) && !who->get_legend(TASK_22,15) )
		tmp += sprintf(ESC HIY "牵连之罪\ntalk %x# welcome.6\n",getoid(this_object()));
	if ( who->get_legend(TASK_22,15) && !who->get_legend(TASK_22,16) )
		tmp += sprintf(ESC HIY "劝谏秦王\ntalk %x# welcome.6\n",getoid(this_object()));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		WARDER_D->do_look( who, this_object() ); 
	
}
void do_faling() { WARDER_D->do_faling( this_player(), this_object() ); }

void accept_task() { WARDER_D->accept_task( this_player(), this_object() );}

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
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_19,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近侍卫玩忽职守，只顾搜刮油水，那些犯了军纪的犯人更加肆无忌惮，居然有人通过重重耳目探得了大王行猎，侍卫大多带去的消息，乘机里通外和，逃到了秦长城上，还计划停留一阵就逃往域外，大王已经震怒，如此藐视王威，若不立即抓捕处决并将使内外将臣群起效之，你速去秦长城将那20个弓兵乱刀杀死！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_19,19) && !who->get_legend(TASK_19,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果这次这么轻易的放过他们，以后会有更多的犯人以他们为榜样，给我添乱！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_19,20) && !who->get_legend(TASK_19,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这叫杀一儆百，看以后谁还敢乱来！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 2:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_19,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_19,19);
        		who->delete_save_2("qgtaofan");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,21,"追捕逃犯" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"追捕逃犯");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_19,20) && !who->get_legend(TASK_19,21) )
        	{
        		who->delete_save_2("qgtaofan");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,21);
			who->add_exp(7500);
			who->add_potential(300);
			who->add_cash(7000);
			send_user(who,"%c%s",';',"追捕逃犯 经验 7500 潜能 300 金钱 7000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,21,"" );
        	}
        	break;   
        case 4:
		if ( who->get_legend(TASK_22,6) && !who->get_legend(TASK_22,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王英明！此等小人不除，定是危害江山社稷之祸根。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 5:
        	if ( who->get_legend(TASK_22,6) && !who->get_legend(TASK_22,7) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/61013",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,7);
			who->add_exp(23000);
			who->add_potential(420);
			who->add_cash(22000);
			send_user(who,"%c%s",';',"真相大白 经验 23000 潜能 420 金钱 22000 女儿红图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,42,"" );
        	}
        	break;   
        case 6:
		if ( who->get_legend(TASK_22,14) && !who->get_legend(TASK_22,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这些士兵死的有些冤枉啊！太子是储君，他的事情谁敢干涉！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_22,15) && !who->get_legend(TASK_22,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王这样杀戮恐怕将会寒了为大王誓死效命的将士们的心啊，再说长城乃是防御犬戎侵我关中的战略要冲，要是将士们军心不稳，将来受害的可不止是长城内外的百姓，更是我王社稷啊，本官刚刚写了一封劝谏书，你转给内政官让他代为提点一下大王吧。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break; 
        case 7:
        	if ( who->get_legend(TASK_22,14) && !who->get_legend(TASK_22,15) )
        	{
			who->delete_save_2("qzgdaodunbing");
			who->delete_save_2("qzgqiangbing");
			who->delete_save_2("qzggongbing");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_22,15);
			who->add_exp(24000);
			who->add_potential(430);
			who->add_cash(22000);
			send_user(who,"%c%s",';',"牵连之罪 经验 24000 潜能 430 金钱 22000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,45,"" );
			me->do_welcome(6);
        	}
        	break;   
	case 8:
        	if ( who->get_legend(TASK_22,15) && !who->get_legend(TASK_22,16) )
        	{
 			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
 			item = new("/item/98/0103");
 			p = item->move(who,-1);
 			if ( !p )
 			{
 				destruct(item);
 				send_user(who,"%c%s", '!', "你携带的物品太多了");	
 				return ;
 			}
 			item->add_to_user(p);
        		who->set_legend(TASK_22,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,46,"劝谏秦王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"劝谏秦王");
        	}
        	break;  
        case 99:
        	WARDER_D->do_look( who, me ); 
        	break;
        }
}
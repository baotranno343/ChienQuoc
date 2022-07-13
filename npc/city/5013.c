
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
int get_char_picid() { return 0651; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tần Quốc Thủ Vệ");
        set_city_name("Tần Quốc");

        set_2( "talk", ([
                "out"           : (: do_out :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 12);
        set("out", 10);
//        set("level",63);
//        set("legend",({32*19+13}));
	set("mpLegend",([60:({32*19+13}),65:({32*20+7,32*38+7}),95:({32*38+27})]));
	set("mpLegend2",([60:({32*19+15}),65:({32*20+9,}),]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();

        if ( (who->get_level() >= 60 && !who->get_legend(TASK_19,13)) || (who->get_legend(TASK_19,13)&&!who->get_legend(TASK_19,15)) ) 
		tmp += sprintf(ESC HIY "无耻的叛徒\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_level() >= 65 && !who->get_legend(TASK_20,7)) || (who->get_legend(TASK_20,7)&&!who->get_legend(TASK_20,9)) ) 
		tmp += sprintf(ESC HIY "雄黄酒\ntalk %x# welcome.4\n",getoid(this_object())); 
	if ( who->get_level() >= 65 && !who->get_legend(TASK_38,7) )
		tmp += sprintf(ESC HIY "韩总管的托付\ntalk %x# welcome.7\n",getoid(me));
	if ( who->get_level() >= 95 && !who->get_legend(TASK_38,27) )
		tmp += sprintf(ESC HIY "恩怨\ntalk %x# welcome.9\n",getoid(me));

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
        	if (who->get_level() >= 60 && !who->get_legend(TASK_19,13))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有人密报秦长城上的士兵意图叛逃，大王密令绞杀，你去干掉刀盾兵和枪兵各10个，回来我会给你通报奖励的。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_19,13) && !who->get_legend(TASK_19,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我知道你是好人，可能你还是能力不够，不过你可以考虑叫上你的朋友帮你的忙。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_19,14) && !who->get_legend(TASK_19,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你肯替天行道，是个真正的%s！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),who->get_gender()==1?"大侠":"女侠",getoid(me)));
        	break;
        case 2:
        	if(who->get_level() >= 60 && !who->get_legend(TASK_19,13))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_19,13);
        		who->delete_save_2("qgswdaodunbing");
        		who->delete_save_2("qgswqiangbing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,20,"无耻的叛徒" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"无耻的叛徒");
        	}
        	break;
       case 3:
        	if ( who->get_legend(TASK_19,14) && !who->get_legend(TASK_19,15) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_19,15);
        		who->delete_save_2("qgswdaodunbing");
        		who->delete_save_2("qgswqiangbing");
			who->add_exp(7000);
			who->add_potential(280);
			who->add_cash(7000);
			send_user(who,"%c%s",';',"无耻的叛徒 经验 7000 潜能 280 金钱 7000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,20,"" );
        	}
        	break;     
        case 4:
        	if (who->get_level() >= 65 && !who->get_legend(TASK_20,7))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近从我那楚国亲戚那里学来做雄黄酒的方子，据说可以驱邪祛毒，端午晨时群龙行雨时摆上雄黄酒宴，还可祈求一个风调雨顺，五谷丰登的好年景，可是最近端午将至，雄黄脱销了，听说秦长城烽火台可以找到，你能帮我看看吗？\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,7) && !who->get_legend(TASK_20,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有雄黄就没办法酿雄黄酒哦。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_20,8) && !who->get_legend(TASK_20,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了雄黄终于可以试试我亲戚给的方子了，说不定酿好了还可以让内子拿去卖钱，哈哈！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 5:
        	if(who->get_level() >= 65 && !who->get_legend(TASK_20,7))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,49,"雄黄酒" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"雄黄酒");
        	}
        	break;
       case 6:
        	if ( who->get_legend(TASK_20,8) && !who->get_legend(TASK_20,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"雄黄",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_20,9);
			who->add_exp(7800);
			who->add_potential(280);
			who->add_cash(8000);
			send_user(who,"%c%s",';',"雄黄酒 经验 7800 潜能 280 金钱 8000");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,49,"" );
        	}
        	break;   
        case 7:
		if ( who->get_level() >= 65 && !who->get_legend(TASK_38,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    %s，你怎么还在这儿呀！难道你不知道韩总管正在到处找你吗？我也是昨天才接到通知，说韩国的韩总管花了很大的代价来寻找一个叫%s的人，也不知是为何事，我看你还是赶紧去问问，看那韩总管到底找你做什么！\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),who->get_name(),who->get_name(),getoid(me)));
		break;			
        case 8:
		if ( who->get_level() >= 65 && !who->get_legend(TASK_38,7) )
       		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,91,"韩总管的托付" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"韩总管的托付");
        	}
        	break;
        case 9:
		if ( who->get_level() >= 95 && !who->get_legend(TASK_38,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    赵国百姓的弟弟原本与我一同在朝廷当差，我们曾经是同甘共苦的好兄弟。如果没有那件事，或许我们现在还在一起大碗喝酒，大口吃肉。\n    我想，是我的苦苦相逼使他毅然放弃了守卫的差事，辗转去了赵国，做了一名甘于平凡的百姓。\n    我希望我的道歉能使他回来，可我自己实在是开不了这个口，不如你去替我办这件事吧！\n    你将我的和解之意转达给赵国百姓，我想她会告诉她弟弟的。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		break;			
        case 10:
		if ( who->get_level() >= 95 && !who->get_legend(TASK_38,27) )
       		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,27);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,92,"恩怨" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"恩怨");
        	}
        	break;
        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;     
        }
}

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
int get_char_picid() { return 5209; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Ngụy Quốc Thủ Vệ");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "enter"         : (: do_enter :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("out", 10);
        set("in", 12);
//       	set("level",24);
//	set("legend",({32*6+10}));
 	set("mpLegend",([20:({32*6+10}),85:({32*29+13}),95:({32*38+21}),]));
 	set("mpLegend2",([20:({32*6+12}),85:({32*29+15}),]));
        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( who->get_level() >= 20 && (!who->get_legend(TASK_06,10) || !who->get_legend(TASK_06,12)))
	{
		tmp = sprintf(ESC HIY "遥远的梦想\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >= 85 && !who->get_legend(TASK_29,13)) || (who->get_legend(TASK_29,13) && !who->get_legend(TASK_29,15)) )
	{
		tmp += sprintf(ESC HIY "成为守卫的条件\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( who->get_level() >= 95 && !who->get_legend(TASK_38,21) )
		tmp += sprintf(ESC HIY "换份工作\ntalk %x# welcome.7\n",getoid(me));

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
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_06,10)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    刀客胡子山，人称天下第一刀客，那把刀被他用得是出神入化，惊天地泣鬼神。\n    我曾经挑战过他，可都以失败告终，但是我能感觉到，每每与他决斗后，我都得到很大的提升，虽然如此，但是我却发现与他之间的差距越来越大，打败第一刀客胡子山扬名立万是我的梦想，可是经过这几番的挑战，我觉得这个梦想离我越来越遥远，我想如果你愿意的话，你可以试试去挑战他，他每天都会在马踏湖的灵谷崖一带练刀。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,10) && !who->get_legend(TASK_06,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道那胡子山刀法又进步了吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,11) && !who->get_legend(TASK_06,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……虽然不是我本人战胜了他，但我一样很高兴！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_06,10)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,22,"遥远的梦想" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"遥远的梦想");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_06,11) && !who->get_legend(TASK_06,12) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64010",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,12);
			who->add_exp(1600);
			who->add_potential(70);
			who->add_cash(1400);
			send_user(who,"%c%s",';',"遥远的梦想 经验 1600 潜能 70 金钱 1400 铜矛图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,22,"" );
        	}
        	break;
        case 4:
        	if (who->get_level() >= 85 && !who->get_legend(TASK_29,13))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你以为在这里站着就能做一名好守卫吗？其实成为守卫我容易嘛我，干啥都是需要很大的努力的，什么，你认为其实很轻松，去去去，年轻人啥都不会就爱冲动说大话，你说你不是说大话，好啊，你去将军古墓杀死 10只石虎，8只刀俑再回来找我。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_29,13) && !who->get_legend(TASK_29,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来你还不够格做一名守卫哦！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_29,14) && !who->get_legend(TASK_29,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来你还真能成为一名好守卫，只是不知道你有没有兴趣呢，每天站在这里还是挺枯燥的。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 5:
        	if (who->get_level() >= 85 && !who->get_legend(TASK_29,13))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,13);
        		who->delete_save("wgswshihu");
        		who->delete_save("wgswdaoyong");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,34,"成为守卫的条件" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"成为守卫的条件");
        	}
        	break; 
        case 6:
        	if ( who->get_legend(TASK_29,14) && !who->get_legend(TASK_29,15) )
        	{
        		who->delete_save("wgswshihu");
        		who->delete_save("wgswdaoyong");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,15);
			who->add_exp(52000);
			who->add_potential(720);
			who->add_cash(48000);
			send_user(who,"%c%s",';',"成为守卫的条件 经验 52000 潜能 720 金钱 48000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,34,"" );
        	}
        	break; 
        case 7:
		if ( who->get_level() >= 95 && !who->get_legend(TASK_38,21) )
  			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，每天都站在这里，像雕塑一般，日复一日，月复一月，年复一年。\n    我已经厌倦了这样的工作。\n    我听说齐国准备加固长城，或许我能去给他们工地上做巡逻兵，我想这样会比在这里做守卫有意思得多，可我自己也不敢太明目张胆的去询问，你能去给我问问齐国财政官吗，他掌管财政，肯定知道有无此计划？\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 8:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_38,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,67,"换份工作" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"换份工作");
        	}
        	break;
        case 99:
        	GUARDER_D->do_look( who, me ); 
        	break;
        }
}
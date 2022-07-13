
// 自动生成：/make/npc/make8010

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0552; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Yên Quốc Thủ Vệ");
        set_city_name("Yên Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",50);
//        set("legend",({32*38+1}));
	set("mpLegend",([50:({32*13+25,}),45:({32*38+3}),]));
	set("mpLegend2",([50:({32*13+27,}),0:({32*10+30}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
        if ( who->get_legend(TASK_10,29)&&!who->get_legend(TASK_10,30) ) 
		tmp += sprintf(ESC HIY "兄弟情深\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_level() >= 50 && !who->get_legend(TASK_13,25)) || (who->get_legend(TASK_13,25) && !who->get_legend(TASK_13,27)) ) 
		tmp += sprintf(ESC HIY "业余爱好\ntalk %x# welcome.3\n",getoid(this_object())); 
	if ( who->get_level() >= 45 && !who->get_legend(TASK_38,3) )
		tmp += sprintf(ESC HIY "丢失的夜明珠\ntalk %x# welcome.6\n",getoid(this_object()));

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
        	if ( who->get_legend(TASK_10,29) && !who->get_legend(TASK_10,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我和我兄弟快一年没见了，真是想念啊！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if( who->get_legend(TASK_10,29) && !who->get_legend(TASK_10,30) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_10,30);
			who->add_exp(4400);
			who->add_potential(140);
			who->add_cash(3800);
			send_user(who,"%c%s",';',"兄弟情深 经验 4400 潜能 140 金钱 3800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,8,"" );
        	}
        	break;
	case 3:
		if ( who->get_level() >= 50 && !who->get_legend(TASK_13,25) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    虽说我对下棋并不是很精通，但这也是我的爱好，因为爱好下棋，所以也很喜欢收集棋子，许多路过此地的旅行者都会给我收集棋子，你也去长白山帮我收集20个吧。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_13,25) && !who->get_legend(TASK_13,26) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没找到啊？奇怪了，别人都是很快送来的哦！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_13,26) && !who->get_legend(TASK_13,27) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然你这样支持我，那我也得给点报酬给你！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 4:
		if ( who->get_level() >= 50 && !who->get_legend(TASK_13,25) ) 
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,25);
        		who->delete_save_2("swqizhi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,21,"业余爱好" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"业余爱好");
        	}
		break;
	case 5:
		if ( who->get_legend(TASK_13,26) && !who->get_legend(TASK_13,27) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"棋子",10) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,27);
        		who->delete_save_2("swqizhi");
			who->add_exp(5700);
			who->add_potential(220);
			who->add_cash(4600);
			send_user(who,"%c%s",';',"业余爱好 经验 5700 潜能 220 金钱 4600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,21,"" );
        	}
		break;
	case 6:
		if ( who->get_level() >= 45 && !who->get_legend(TASK_38,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我捡到一颗夜明珠！\n    前些日子我捡到一颗夜明珠，本想拿到当铺换点钱，可听说赵王在走访我们燕国时不小心遗失了一颗夜明珠，我觉得这颗夜明珠肯定就是赵王遗失的那一颗，所以我想把它送还给赵王，以示我们燕国子民的高尚气节！不如你替我将这颗夜明珠送到赵王手上吧。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 7:
		if ( who->get_level() >= 45 && !who->get_legend(TASK_38,3) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/98/0182",1);
        		who->set_legend(TASK_38,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,54,"丢失的夜明珠" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"丢失的夜明珠");
        	}
		break;
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;     
        }
}
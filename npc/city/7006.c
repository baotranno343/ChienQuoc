
// 自动生成：/make/npc/make8006

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

#define INQUISITOR_D    "/inh/city/inquisitor"

inherit OFFICER;

void do_elect( string arg );
void do_vote( string arg );
void do_score( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Yên Quốc Ngự Sử");
	set_real_name("Tử Chi");
        set_city_name("Yên Quốc");

        set_2( "talk", ([
                "elect"         : (: do_elect :),
                "vote"          : (: do_vote :),
                "score"         : (: do_score :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",50);
//	set("legend",({32*13+10})); 
	set("mpLegend",([50:({32*13+10,32*14+7}),]));
	set("mpLegend2",([50:({32*13+12,32*14+9,32*14+12,}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 50 && !who->get_legend(TASK_13,10) ) || ( who->get_legend(TASK_13,10) && !who->get_legend(TASK_13,12) ) )
	{
		tmp = sprintf(ESC HIY "明镜传说\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 50 && !who->get_legend(TASK_14,7) ) || ( who->get_legend(TASK_14,7) && !who->get_legend(TASK_14,9) ) )
	{
		tmp += sprintf(ESC HIY "收集圆环\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( ( who->get_legend(TASK_14,9) && !who->get_legend(TASK_14,10) ) || ( who->get_legend(TASK_14,10) && !who->get_legend(TASK_14,12) ) )
	{
		tmp += sprintf(ESC HIY "收集轴\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( ( who->get_legend(TASK_14,12) && !who->get_legend(TASK_14,13) ) || ( who->get_legend(TASK_14,13) && !who->get_legend(TASK_14,14) ) )
	{
		tmp += sprintf(ESC HIY "取名\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INQUISITOR_D->do_look( who, this_object() ); 
	
}
void do_elect( string arg ) { INQUISITOR_D->do_elect( this_player(), this_object(), arg ); }
void do_vote( string arg ) { INQUISITOR_D->do_vote( this_player(), this_object(), arg ); }
void do_score( string arg ) { INQUISITOR_D->do_score( this_player(), this_object(), arg ); }

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
       	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 50 && !who->get_legend(TASK_13,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    传说有一面明镜，只要将它悬挂在门庭之上，就能让从这门庭经过的人受到熏陶，心智变得清明，任何贪赃枉法之念都会被它驱除，我想如果在我们王宫的门庭上挂上这样一面明镜，那么贪赃枉法之徒就会越来越少了，而我的工作也会越来越轻松。\n    有人曾在郑国渠一带见过那面明镜，你去帮我找来吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_13,10) && !who->get_legend(TASK_13,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这难道只是个传说吗？真希望此事确实存在。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_13,11) && !who->get_legend(TASK_13,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈……有了此明镜，我以后办案将会更加认真细致。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >=50 && !who->get_legend(TASK_13,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,14,"明镜传说" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"明镜传说");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_13,11) && !who->get_legend(TASK_13,12) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"明镜",1) != 1 )
        			return;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),50,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,12);
			who->add_exp(5800);
			who->add_potential(210);
			who->add_cash(5000);
			send_user(who,"%c%s",';',sprintf("明镜传说 经验 5800 潜能 210 金钱 5000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,14,"" );
        	}
        	break; 
        case 4:
        	if ( who->get_level() >= 50 && !who->get_legend(TASK_14,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    平时我还有点观察星星的爱好，想做个能更近距离的观察到他们的仪器，你去燕长城给我收集3个制作这个仪器的圆环来好吗？\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_14,7) && !who->get_legend(TASK_14,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这事可能是有点难度，不过还是希望你会帮助我。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_14,8) && !who->get_legend(TASK_14,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你，现在我可以开始动手做了，但是我可能还需要你的帮忙。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_14,9) && !who->get_legend(TASK_14,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    平时我还有点观察星星的爱好，想做个能更近距离的观察到他们的仪器，你去燕长城给我找到制作这个仪器需要的金属轴好吗？\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_14,10) && !who->get_legend(TASK_14,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这事可能是有点难度，不过还是希望你会帮助我。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_14,11) && !who->get_legend(TASK_14,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你，现在我可以开始动手做了，但是我可能还需要你的帮忙。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
         	else if ( who->get_legend(TASK_14,12) && !who->get_legend(TASK_14,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    仪器做好了，还得取个名字，还有那3个圆环，也得给他取个好名字，听说那赵国李防是一位高人，知识渊博，你去请教请教他吧。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_14,13) && !who->get_legend(TASK_14,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是否取好名字了？\n"ESC"离开", me->get_name()));
           		
        	break;
	case 5:
        	if( who->get_level() >=50 && !who->get_legend(TASK_14,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_14,7);
        		who->delete_save_2("ysyuanhuan");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,25,"浑仪（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"浑仪（1）");
        	}
        	break;       
        case 6:
        	if ( who->get_legend(TASK_14,8) && !who->get_legend(TASK_14,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"圆环",3) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_14,9);
        		who->delete_save_2("ysyuanhuan");
			who->add_exp(4000);
			who->add_potential(140);
			who->add_cash(2800);
			send_user(who,"%c%s",';',"浑仪（1） 经验 4000 潜能 140 金钱 2800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,25,"" );
			me->do_welcome(4);
        	}
        	break; 
	case 7:
        	if( who->get_legend(TASK_14,9) && !who->get_legend(TASK_14,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_14,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,26,"浑仪（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"浑仪（2）");
        	}
        	break;       
        case 8:
        	if ( who->get_legend(TASK_14,11) && !who->get_legend(TASK_14,12) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"轴",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_14,12);
			who->add_exp(4000);
			who->add_potential(140);
			who->add_cash(2800);
			send_user(who,"%c%s",';',"浑仪（2） 经验 4000 潜能 140 金钱 2800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,26,"" );
			me->do_welcome(4);
        	}
        	break; 
	case 9:
        	if( who->get_legend(TASK_14,12) && !who->get_legend(TASK_14,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_14,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,27,"浑仪（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"浑仪（3）");
        	}
        	break;    
        case 99:	
		INQUISITOR_D->do_look( who, me); 
        	break;  
        }
}
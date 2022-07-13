
// 自动生成：/make/npc/make8004

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

void do_build( string arg );
void do_upgrade( string arg );
void do_plant( string arg );
void do_food( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Yên Quốc Nội Chính Quan");
	set_real_name("Tô Đại");
        set_city_name("Yên Quốc");

        set_2( "talk", ([
                "build"         : (: do_build :),
                "upgrade"       : (: do_upgrade :),
                "plant"         : (: do_plant :),
                "food"          : (: do_food:),
                "welcome"	: (: do_welcome :),	
        ]) );
//	set("level",93);
//	set("legend",({32*32+14}));
 	set("mpLegend",([90:({32*32+14}),]));
 	set("mpLegend2",([90:({32*32+16}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 90 && !who->get_legend(TASK_32,14) ) || ( who->get_legend(TASK_32,14) && !who->get_legend(TASK_32,16) ) )
	{
		tmp += sprintf(ESC HIY "收集大枣\ntalk %x# welcome.1\n",getoid(me));
	}
	if ("/sys/sys/count"->get_refine()&&who->get_city_name()==me->get_city_name())
		tmp += sprintf(ESC"收妖壶任务\ntalk %x# welcome.1000\n",getoid(me)); 	
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INTERIOR_D->do_look( who, me ); 
	
}
void do_build( string arg ) { INTERIOR_D->do_build( this_player(), this_object(), arg ); }
void do_upgrade( string arg ) { INTERIOR_D->do_upgrade( this_player(), this_object(), arg ); }
void do_plant( string arg ) { INTERIOR_D->do_plant( this_player(), this_object(), arg ); }
void do_food( string arg ) { INTERIOR_D->do_food( this_player(), this_object(), arg ); }

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object( who, this_object(), obj ); }

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
        if (flag>=1000)
        {
        	"/sys/user/refine"->do_welcome(who, me, arg);
        	return;
        }        
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本官有亲人无意中患上一种暗疾，需要困魔阵中有阴气滋养的大枣才能治愈，你去困魔阵中帮我弄10个来。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_32,14) && !who->get_legend(TASK_32,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，我可真是口馋了，你可得给我尽快找过来啊。\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_32,15) && !who->get_legend(TASK_32,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，你动作真快，下次还找你！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 2:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_32,14) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_32,14);
        		who->delete_save("ygnzgdazao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,45,"收集大枣" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"收集大枣");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_32,15) && !who->get_legend(TASK_32,16) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"大枣",10) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_32,16);
        		who->delete_save("ygnzgdazao");
			who->add_exp(67000);
			who->add_potential(930);
			who->add_cash(56000);
			send_user(who,"%c%s",';',"收集大枣 经验 67000 潜能 930 金钱 56000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,45,"" );
        	}
        	break;

        case 99:
        	INTERIOR_D->do_look( who, me ); 
        	break;
        }
}
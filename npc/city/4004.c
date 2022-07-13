
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
        set_name("Ngụy Quốc Nội Chính Quan");
	set_real_name("Tín Lang Quân");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "build"         : (: do_build :),
                "upgrade"       : (: do_upgrade :),
                "plant"         : (: do_plant :),
                "food"          : (: do_food:),
                "welcome"	: (: do_welcome :),	
        ]) );
 	set("mpLegend2",([0:({32*34+6,})]));
        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

void do_look( object who )
{
	int id;
	string tmp="";
	object me = this_object();
	
	id = getoid(this_object());
        if ( who->get_legend(TASK_34,5) && !who->get_legend(TASK_34,6) )
		tmp += sprintf(ESC HIY "寻宝历险\ntalk %x# welcome.1\n",id); 
        if ( who->get_legend(TASK_34,6) && !who->get_legend(TASK_34,7) )
		tmp += sprintf(ESC HIY "防止泄密\ntalk %x# welcome.1\n",id); 
	if ("/sys/sys/count"->get_refine()&&who->get_city_name()==me->get_city_name())
		tmp += sprintf(ESC"收妖壶任务\ntalk %x# welcome.1000\n",id); 
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
        	if ( who->get_legend(TASK_34,5) && !who->get_legend(TASK_34,6) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，果然宝物，这下子我的宝贝儿子有救了。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_34,6) && !who->get_legend(TASK_34,7) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，这个宝物本来就是我家的，我不希望任何人知道，尤其是大王，你去警告那个常常散布流言的百姓不要再乱传此事！\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
        case 2:
        	if ( who->get_legend(TASK_34,5) && !who->get_legend(TASK_34,6) ) 
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"精灵珠",1) != 1 )
        			return;        			
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,6);
			who->add_exp(71000);
			who->add_potential(910);
			who->add_cash(62000);
			send_user(who,"%c%s",';',"寻宝历险 经验 71000 潜能 910 金钱 62000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,40,"" );
			me->do_welcome(1);
        	}
        	break;
	case 3:
        	if ( who->get_legend(TASK_34,6) && !who->get_legend(TASK_34,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,41,"魏国百姓" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"魏国百姓");
        	}
        	break;

        case 99:
        	INTERIOR_D->do_look( who, me ); 
        	break;
        }
}
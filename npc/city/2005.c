
// 自动生成：/make/npc/make8005

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define RESIDENT_D      "/inh/city/resident"

inherit OFFICER;

void do_enter( string arg );
void do_leave( string arg );
void do_shutup( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Hộ Tịch Quan");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "enter"         : (: do_enter :),
                "leave"         : (: do_leave :),
                "shutup"        : (: do_shutup :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",17);
//	set("legend",({32*4+13}));
 	set("mpLegend",([15:({32*4+13}),]));
 	set("mpLegend2",([15:({32*4+14}),]));
       setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 15 && !who->get_legend(TASK_04,13) ) || ( who->get_legend(TASK_04,13) && !who->get_legend(TASK_04,14)) )
	{
		tmp = sprintf(ESC HIY "户籍密件\ntalk %x# welcome.1\n",getoid(me));
	}

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		RESIDENT_D->do_look( who, this_object() ); 
	
}
void do_enter( string arg ) { RESIDENT_D->do_enter( this_player(), this_object(), arg ); }
void do_leave( string arg ) { RESIDENT_D->do_leave( this_player(), this_object(), arg ); }
void do_shutup( string arg ) { RESIDENT_D->do_shutup( this_player(), this_object(), arg ); }
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
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,13)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近记忆力一直在衰退，办事情丢三拉四。不久前在无定河青龙坛游玩时，不慎将一封户籍信件遗落在那里，那封户籍信件对本官来说非常重要，不知%s能否帮本官将那信件寻回并交还于我，本官定有厚谢。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	else if ( who->get_legend(TASK_04,13) && !who->get_legend(TASK_04,14) )
			me->do_welcome(3);
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,13)  )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->remove_task_item(who, "户籍信件");                   	
        		who->set_legend(TASK_04,13);
			who->delete_save("hujimijian");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,6,"户籍密件" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"户籍密件");
        	}
        	break;
        case 3:
        	if ( !who->get_legend(TASK_04,13) || who->get_legend(TASK_04,14) )
        		return ;
        	if ( objectp(item=present("户籍信件",who,1,MAX_CARRY)) && item->is_legend_item() == 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太好了！本官一定会好好报答你的！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然%s无法寻回，也就算了。本官只好再重新草拟一份。\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who)));
        	break;
        case 4:
        	if ( who->get_legend(TASK_04,13) && !who->get_legend(TASK_04,14) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"户籍信件",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,14);
			who->delete_save("hujimijian");
			who->delete_save_2("hujimijian");
			who->add_exp(1100);
			who->add_potential(60);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"户籍密件 经验 1100 潜能 60 金钱 1200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,6,"" );
        	}
        	break;
        case 99:	
		RESIDENT_D->do_look( who, me); 
        	break;
        }
}
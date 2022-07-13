
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
        set_name("Ngụy Quốc Thủ Vệ");
        set_city_name("Ngụy Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",85);
//        set("legend",({32*29+4}));
 	set("mpLegend",([85:({32*29+4})]));
 	set("mpLegend2",([85:({32*29+6})]));
        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( (who->get_level() >= 85 && !who->get_legend(TASK_29,4)) || (who->get_legend(TASK_29,4) && !who->get_legend(TASK_29,6)))
	{
		tmp += sprintf(ESC HIY "救人于危难\ntalk %x# welcome.1\n",getoid(me));
	}
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
        	if ( who->get_level() >=85 && !who->get_legend(TASK_29,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这日子可要怎么过呀！夫人生病，家里稍微值点钱的东西都当了，能借的都借了，虽然我在这能拿点俸禄，但是比起那些开销来，微不足道啊。如果你是个好心人，能不能给我找点灵芝草与小米，可能的话，还借点钱给我吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_29,4) && !who->get_legend(TASK_29,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我知道你是愿意帮我的，只是暂时还没有找到更好的办法！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_29,5) && !who->get_legend(TASK_29,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太感谢你了，你是我们家的大恩人！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_level() >=85 && !who->get_legend(TASK_29,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,4);
        		who->delete_save("wgswlingzc");
        		who->delete_save("wgswqian");
        		who->delete_save("wgswxiaomi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,31,"救人于危难" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"救人于危难");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_29,5) && !who->get_legend(TASK_29,6) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"灵芝草",1) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"钱",1) != 1 )
        		{
        			item = new("item/98/0138");
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			return;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"小米",10) != 1 )
        		{
        			item = new("item/98/0138");
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			item = new("item/98/0139");
        			p = item->move(who,-1);
        			item->add_to_user(p);        			
        			return;        			
        		}
        		TASK_LEGEND_D->give_item(who,"item/product/64153",1);
       			TASK_LEGEND_D->task_finish(who);
       			who->set_legend(TASK_29,6);
        		who->delete_save("wgswlingzc");
        		who->delete_save("wgswqian");
        		who->delete_save("wgswxiaomi");
			who->add_exp(53000);
			who->add_potential(740);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"救人于危难 经验 53000 潜能 740 金钱 50000 寒星头巾图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,31,"" );
        	}
        	break;  
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;     
        }
}
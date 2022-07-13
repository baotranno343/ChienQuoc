
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
        set_name("Tề Quốc Thủ Vệ");
        set_city_name("Tề Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",37);
//        set("legend",({32*9+28}));
 	set("mpLegend",([35:({32*9+28}),70:({32*38+11}),75:({32*25+1,})]));
 	set("mpLegend2",([75:({32*25+3,}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,28) )
	{
		tmp = sprintf(ESC HIY "欺诈的天罚\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >= 75 && !who->get_legend(TASK_25,1)) || (who->get_legend(TASK_25,1) && !who->get_legend(TASK_25,3)))
	{
		tmp += sprintf(ESC HIY "决定性的打击\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( who->get_level() >= 70 && !who->get_legend(TASK_38,11) )
	{
		tmp += sprintf(ESC HIY "答谢\ntalk %x# welcome.6\n",getoid(me));
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
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那泰山一带的黑熊、螳螂妖在10年前幻化为人，一行20人来到我国的大将军处想要当差，将军见他们体格高大，便应允了，但是一年之后，他们全部潜逃，偷走了我国的兵法，将军大怒，一直想要捉拿他们，可他们行为诡异，如今，终于追查到他们躲在泰山一带，欺诈是会受到天罚的！你消灭他们后去将军那领赏吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,28);
        		who->delete_save_2("swheixiong");
        		who->delete_save_2("swtanglang");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,5,"欺诈的天罚" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"欺诈的天罚");
        	}
        	break;
        case 3:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_25,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近灵谷洞的一些魍魉鬼经常想飘进城里来，但是因为有我们在守卫，所以他们一直未能得逞，但是如果让他们成功飘进来的话，我们城里面的百姓将不堪设想，为了不让我们城里面的百姓受到危害，你可以代替我们去灵谷洞对这些魍魉鬼作一次决定性的打击吗？我想只要一次性消灭他们20个魍魉的话，应该可以对他们造成决定性的打击了。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_25,1) && !who->get_legend(TASK_25,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我们是无法离开我们守卫的岗位的，所以就要麻烦你了，如果你觉得实在不行，你可以去找个帮手。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_25,2) && !who->get_legend(TASK_25,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你做得很好呀，这肯定是一次决定性的打击了，看来这些魍魉鬼以后都没有实力再像以前那样频繁地想要飘进城里了，我代表齐国百姓唐茂谢谢你。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
 
        	break;
	case 4:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_25,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_25,1);
        		who->delete_save_2("qgswwangliang");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,20,"决定性的打击" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"决定性的打击");
        	}
        	break;
        case 5:
        	if ( who->get_legend(TASK_25,2) && !who->get_legend(TASK_25,3) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64136",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_25,3);
        		who->delete_save_2("qgswwangliang");
			who->add_exp(40000);
			who->add_potential(560);
			who->add_cash(37000);
			send_user(who,"%c%s",';',"决定性的打击 经验 40000 潜能 560 金钱 37000 嗜天鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,20,"" );
        	}
        	break;
        case 6:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_38,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那个谁！对，就是你！\n    上次韩国守卫是叫你给我捎来他的口信吧？我非常感谢他这么善良的想要帮助我，这几天我也考虑了很久，我想振作还是得靠自己，所以我会调整好自己现在的状态，积极生活，还麻烦你再跑一趟，告诉韩国守卫，叫他安心在朝廷做事，不用过来我这边了，我会好好活下去的！\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		break;        		
        case 7:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_38,11) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,11);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,74,"答谢" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"答谢");
        	}
        	break;	   
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;     
        }
}
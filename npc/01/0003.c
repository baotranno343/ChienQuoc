
// 自动生成：/make/npc/make8084

#include <npc.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5501; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Trang Tân");
        set_city_name("Sở Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
	set("mpLegend2",([0:({32*3+23,}),1:({32*3+25,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_NEWBIE_03,22) && !who->get_legend(TASK_NEWBIE_03,28) )
	{
		tmp = sprintf(ESC HIY "亡羊补牢\ntalk %x# welcome.1\n",getoid(me));
	}

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    依我看来，如果大王不除掉身边只讲究奢侈淫乐的那四人，国将不国啊～～" + "\n",get_name()) +
		tmp +
		ESC"离开");
	else
		more_look_menu( who, sprintf( "%s：\n    依我看来，如果大王不除掉身边只讲究奢侈淫乐的那四人，国将不国啊～～\n", get_name() ) );
	
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
        string name,place;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_NEWBIE_03,22) && !who->get_legend(TASK_NEWBIE_03,23) )
        	{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我与大王已达成协议，王允许我暂居赵国，但这一路上风餐露宿，得准备点干粮才是呀。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	}
        	else if ( who->get_legend(TASK_NEWBIE_03,23) && !who->get_legend(TASK_NEWBIE_03,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我与大王已达成协议，王允许我暂居赵国，但这一路上风餐露宿，得准备点干粮才是呀。我刚听说上庸关的刀兵、剑兵囤储了一批干粮，这可是充饥的好东西呀！义士，你去给我找20包来吧！\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_NEWBIE_03,24) && !who->get_legend(TASK_NEWBIE_03,25) )
			me->do_welcome(4);
		else if ( who->get_legend(TASK_NEWBIE_03,25) && !who->get_legend(TASK_NEWBIE_03,26) )	
        		me->do_welcome(6);
        	if ( who->get_legend(TASK_NEWBIE_03,26) && !who->get_legend(TASK_NEWBIE_03,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    交给你办的事可得尽快！交给你办的事可得尽快！\n"ESC"离开", me->get_name()));
        	break;
        case 2:
        	if ( who->get_legend(TASK_NEWBIE_03,22) && !who->get_legend(TASK_NEWBIE_03,23) )
        	{
			who->add_exp(500);
			who->add_potential(10);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03,23);
			send_user(who,"%c%s",';',"亡羊补牢 经验 500 潜能 10");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,9,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_NEWBIE_03,23) && !who->get_legend(TASK_NEWBIE_03,24) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_NEWBIE_03,24);
        		who->delete_save_2("zxganliang");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_DONGTINGHU,"洞庭湖" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_DONGTINGHU,1,"亡羊补牢(2)" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"亡羊补牢(2)");
        	}
        	break;
        case 4:
		if ( !who->get_legend(TASK_NEWBIE_03,24) || who->get_legend(TASK_NEWBIE_03,25) )
			return ;
		if ( who->get_save_2("zxganliang")<20 )
        		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你可得快点，别耽误了我的搬迁大计！\n"ESC"离开", me->get_name()));
		else
        		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太谢谢你了，这20包干粮可帮了我的大忙！对我的搬迁计划起了不小的作用啊！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 5:
        	if ( who->get_save_2("zxganliang")<20 )
        		return ;
		inv = all_inventory(who, 1, MAX_CARRY);
		
		if( !objectp( item = present("干粮", who, 1, MAX_CARRY) ) || item->is_legend_item() != 1 )
		{
			send_user(who,"%c%s",'!',"你的干粮呢?");
			return;	
		}			
		for(i=0,size=sizeof(inv);i<size;i++)
		{
			if ( !objectp(inv[i]) )
				continue;
			if ( inv[i]->get_name() != "干粮" || inv[i]->is_legend_item() != 1 )
				continue;
			amount += inv[i]->get_amount();		
		}
		if ( amount < 20 )
		{
			send_user(who,"%c%s",'!',"数量不够吧?");
			return;	
		}
		for(i=0,size=sizeof(inv);i<size;i++)
		{
			if ( !objectp(inv[i]) )
				continue;
			if ( inv[i]->get_name() != "干粮" || inv[i]->is_legend_item() != 1 )
				continue;
			inv[i]->remove_from_user();
			destruct(inv[i]);
		}
		who->add_exp(900);
		who->add_potential(40);
		who->add_cash(1000);
		TASK_LEGEND_D->task_finish(who);
		who->set_legend(TASK_NEWBIE_03,25);
		who->delete_save_2("zxganliang");
		send_user(who,"%c%s",';',"亡羊补牢 经验 900 潜能 40 金钱 1000");
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_DONGTINGHU,1,"" );
		me->do_welcome(1);
        	break;  
        case 6:
        	if ( who->get_legend(TASK_NEWBIE_03,25) && !who->get_legend(TASK_NEWBIE_03,26) )
        	{
        		if ( !(name=who->get_save_2("zxkillnpc")) || !(place=who->get_save_2("zxkillnpc1")))
        		{
	        		name = ({"州侯","夏侯","鄢陵君","寿跟君"})[random(4)];
	        		who->set_save_2("zxkillnpc",name);
	        		if ( name == "州侯" )
	        			place = "楚方城1";
	        		else if ( name == "夏侯" )
	        			place = "楚方城2";
	        		else
	        			place = "楚方城3";
	        		who->set_save_2("zxkillnpc1",place);
	        	}
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    自古邪不压正，经过我的一片苦心劝说，大王终于省悟过来了，令我杀掉只知奢侈淫的%s，可我不能露面，你替我杀掉他们吧！%s就在%s，你尽快去吧！杀死他们后报告给楚国大将军项燕就是了！大王一定会按功行赏的。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),name,name,place,getoid(me)));
        	}
        	break;
        case 7:
        	if ( !who->get_legend(TASK_NEWBIE_03,25) || who->get_legend(TASK_NEWBIE_03,26) )
        		return;
        	if ( !(name=who->get_save_2("zxkillnpc")) || !(place=who->get_save_2("zxkillnpc1")))
        		return;
		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
		who->set_legend(TASK_NEWBIE_03,26);
		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_DONGTINGHU,"洞庭湖" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_DONGTINGHU,2,"亡羊补牢(3)" );
		send_user( who, "%c%s", '!', "得到任务 "HIY"亡羊补牢(3)");        	
        	break;      	
        }
}
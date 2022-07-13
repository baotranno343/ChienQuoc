
#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <task.h>

inherit OFFICER;

void do_welcome( string arg );
void do_visit( string arg );
// 函数：获取人物造型
int get_char_picid() { return 5402; } 

// 函数：构造处理
void create()
{
        set_name( "Dã Vị Thải Cấu Thương" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
                "visit"		: (: do_visit :),
        ]));    
	set("mpLegend2",([0:({32*49+2,32*49+4,}),]));
        setup();     
}

void do_look(object who)
{
	int id,id2=0;
	string cmd="";
	object pet,me=this_object();
	id = getoid(me);
        if( who->get_legend(TASK_49, 1) && !who->get_legend(TASK_49, 2) )
	{
		cmd = sprintf(ESC HIY "索要灵芝草\ntalk %x# visit.11\n",id);
	}
        if( who->get_legend(TASK_49, 2) && !who->get_legend(TASK_49, 3) )
	{
		cmd = sprintf(ESC HIY "头疼的毛病（2）\ntalk %x# visit.11\n",id);
	}
        if( who->get_legend(TASK_49, 3) && !who->get_legend(TASK_49, 4) && objectp(pet=USER_BEAST_D->have_beast(who,"赤褐蚁")))
	{
		cmd = sprintf(ESC HIY "头疼的毛病（2）\ntalk %x# visit.11\n",id);
	}
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    最近想去周国市集里面开个野味店，需要大量的野味，比方说：小山鸡、小兔子……如果你要是有的话，我愿意收购，至于价格嘛！包你满意，嘿嘿……\n"
	+ cmd
	+ ESC"300金收购小山鸡一只\ntalk %x# welcome.1\n"
	+ ESC"300金收购小野兔一只\ntalk %x# welcome.2\n"
	+ ESC"400金收购小蜜蜂一只\ntalk %x# welcome.3\n"
	+ ESC"400金收购小蚂蚁一只\ntalk %x# welcome.4\n"
	+ ESC"600金收购斑点蛙一只\ntalk %x# welcome.5\n"
	+ESC"离开",me->get_name(),id,id,id,id,id,));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,cash;
	object pet,who;
	string name;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        default:
        	name = "小山鸡";
        	cash = 300;
		break;
        case 2:
        	name = "小野兔";
        	cash = 300;
		break;
        case 3:
        	name = "小蜜蜂";
        	cash = 400;
		break;
        case 4:
        	name = "小蚂蚁";
        	cash = 400;
		break;
        case 5:
        	name = "斑点蛙";
        	cash = 600;
		break;
			
        }
        if ( !objectp(pet=USER_BEAST_D->have_beast(who,name)) )
	{
		send_user(who,"%c%s",'!',"你没有这样的野味");
		return ;
	}
	USER_BEAST_D->destruct_pet(who,pet);
	who->add_cash(cash);
	"/sys/sys/count"->add_income("山珍收购", cash);
	who->add_log("$sellpet", cash);
	send_user(who,"%c%s",'!',sprintf("你得到%d金",cash));
}

void do_visit( string arg )
{
        object me = this_object();
        __FILE__ ->do_visit2(me, arg);
}

void do_visit2( object me, string arg )
{
	int flag,cash,p;
	object pet,who,item;
	string name;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 11:
	        if( who->get_legend(TASK_49, 1) && !who->get_legend(TASK_49, 2) )
			send_user(who,"%c%s",':',sprintf("%s:\n    灵芝草何等珍贵，怎能说给就给！要灵芝草是要付出代价的，你想好了再来找我吧。\n"ESC"完成任务\ntalk %x# visit.12\n"ESC"离开",me->get_name(),getoid(me)));
		else if( who->get_legend(TASK_49, 2) && !who->get_legend(TASK_49, 3) )
			send_user(who,"%c%s",':',sprintf("%s:\n    其实我的要求并不高，我收购了这么多年的野味，啥都见过，也啥都收过，惟独有一样，从来没有收购过，那就是巴丘的赤褐蚁。    希望你能满足我这个心愿，抓一只赤褐蚁给我，我也就满足你的心愿——将灵芝草交给你！\n    先去杂货店老板那里买几条乾坤绳吧，是抓宠必需的。\n"ESC"接受任务\ntalk %x# visit.13\n"ESC"离开",me->get_name(),getoid(me)));
		else if( who->get_legend(TASK_49, 3) && !who->get_legend(TASK_49, 4) && objectp(pet=USER_BEAST_D->have_beast(who,"赤褐蚁")))
			send_user(who,"%c%s",':',sprintf("%s:\n    还算你遵守诺言，那我当然也不会食言，你拿着这颗灵芝草交给当铺老板去吧！\n"ESC"完成任务\ntalk %x# visit.14\n"ESC"离开",me->get_name(),getoid(me)));
			
		break;
	case 12:
	        if( who->get_legend(TASK_49, 1) && !who->get_legend(TASK_49, 2) )
		{
			who->add_exp(650);
			who->add_potential(20);
			who->add_cash(500);
			send_user(who,"%c%s",';',"头疼的毛病（1） 经验 650 潜能 20 金钱 500");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_49, 2);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,113,"" );
			me->do_visit(11);
		}
		break;
	case 13:
	       	if ( who->get_legend(TASK_49, 2) && !who->get_legend(TASK_49, 3))
        	{
/*			item = new("/item/49/4900");  
			if ( !item )
				return ;
			item->set_amount(10);
	                p =item->move(who, -1);
	                if ( p == 0 )
	                {
	                	destruct(item); 
	                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
	                	return ;
	                }
	                item->add_to_user(p);*/
	                if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;	
        		who->set_legend(TASK_49,3);
//			send_user(who,"%c%s",';',"你得到"HIY"10根乾坤绳");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,114,"头疼的毛病（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"头疼的毛病（2）");
        	}
        	break;
	case 14:
		if( who->get_legend(TASK_49, 3) && !who->get_legend(TASK_49, 4) && objectp(pet=USER_BEAST_D->have_beast(who,"赤褐蚁")))
		{
			item = new("/item/98/0198");  
			if ( !item )
				return ;
	                p =item->move(who, -1);
	                if ( p == 0 )
	                {
	                	destruct(item); 
	                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
	                	return ;
	                }
	                item->add_to_user(p);
			USER_BEAST_D->destruct_pet(who,pet);
			who->add_exp(550);
			who->add_potential(30);
//			who->add_cash(500);
			send_user(who,"%c%s",';',"头疼的毛病（2） 经验 550 潜能 30 灵芝草 1");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_49, 4);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,114,"" );

//			send_user( who, "%c%s", '!', "得到 "HIY"灵芝草"BLK"，请在物品栏右击灵芝草后触发下个任务");
			send_user(who,"%c%s",';',"头疼的毛病（2） 经验 550 潜能 30 灵芝草 1\n请在物品栏右击灵芝草后触发下个任务");
		}
		break;


        }

}

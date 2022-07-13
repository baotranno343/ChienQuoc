
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0012; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("奇怪的稻草人");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
	set("mpLegend",([0:({17,}),]));
	set("mpLegend2",([0:({19}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        int id = getoid( this_object() );

	if ( !who->get_legend(TASK_NEWBIE_00, 19))	
		tmp = sprintf(ESC  +HIY+"稻草人的委托\ntalk %x# welcome.1\n",id);
	send_user( who, "%c%s", ':', get_name() + "：\n    …………\n        (看上去有点与众不同的稻草人。)\n" +
		tmp +
		ESC"离开"
		);
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag, date , status, p, z, x, y, i;
        object who, item;     
        string cmd1, cmd2, cmd3, cmd4, cmd5, result;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);

        switch(flag)
        {
        case 1:
		if ( !who->get_legend(TASK_NEWBIE_00, 17) )
		{
	                 send_user( who, "%c%s", ':', sprintf("%s：\n    呃……那边的人类。\n"
	                 "    没错，就是叫你。\n"
	                 "    其实有一个问题已经困惑我好长一段时间了……\n"
	                 "    正如你所看到的，我整个身体除了一堆稻草外就只有布片和木杆了。因此那些该死的乌鸦便老是嘲笑我没大脑。虽然很生气，但这也是事实。如果我也像人类一样有一个大脑的话，那些乌鸦也不敢再嘲笑我了。\n"
	                 "    我听说清溪的丁大叔曾经在长白天池中取到了不少的灵石，如果用那些灵石作为我的脑袋应该相当不错。可惜我没有脚，不能走过去。如果你能帮我这个忙，我会很感激你的。\n"
	                 ESC "接受任务\ntalk %x# welcome.2\n"
	                 ESC "离开",
	                 me->get_name(), getoid(me) ) );
		}
		else if ( who->get_legend(TASK_NEWBIE_00, 18) && !who->get_legend(TASK_NEWBIE_00, 19) )
			send_user( who, "%c%s", ':',me->get_name()+":\n    太好啦！！我终于美梦成真了～你真是帮了我一个大忙啊。实在太感谢了。\n"+sprintf(ESC"完成任务\ntalk %x# welcome.3\n",getoid(me))+ESC"离开");
		else
			send_user( who, "%c%s", ':',me->get_name()+":\n    请暂时不要打扰我，我在思考一个很深奥的人生哲理。等你拿到灵石后，再来找我吧！\n"ESC"离开");
                break;
	case 2:
		if (who->get_legend(TASK_NEWBIE_00, 17))	
			return ;
		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
		who->set_legend(TASK_NEWBIE_00, 17);
		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,19,"稻草人的委托" );
		send_user( who, "%c%s", '!', "你接受了"HIY"稻草人的委托"NOR"任务");
		break;
	case 3:
		if ( who->get_legend(TASK_NEWBIE_00, 18) && !who->get_legend(TASK_NEWBIE_00, 19) )
		{
			if( !objectp( item = present("灵石", who, 1, MAX_CARRY) ) )
			{
				send_user(who,"%c%s",'!',"你的灵石呢?");
				return;
			}
			item->remove_from_user();
			destruct(item);
			TASK_LEGEND_D->task_finish(who);
			who->add_potential(30);
			who->add_exp(180);
			send_user(who,"%c%s",';',"稻草人的委托 经验 180 潜能 30 ");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,19,"" );	
			who->set_legend(TASK_NEWBIE_00, 19);
		}
		break;                                                                                                                                 
        }
}

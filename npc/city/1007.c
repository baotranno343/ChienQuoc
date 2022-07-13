
// 自动生成：/make/npc/make8007

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define DIPLOMAT_D      "/inh/city/diplomat"

inherit OFFICER;

void do_relation( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tề Quốc Sử Tiết");
	set_real_name("Ngưu Diễn");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "relation"      : (: do_relation :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",82);
//	set("legend",({32*27+19}));
 	set("mpLegend",([54:({32*50+7}),80:({32*27+19})]));
 	set("mpLegend2",([35:({32*37+26,}),54:({32*50+9}),80:({32*27+21,}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who ) 
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 80 && !who->get_legend(TASK_27,19) ) || ( who->get_legend(TASK_27,19) && !who->get_legend(TASK_27,21) ) )
	{
		tmp += sprintf(ESC HIY "灵谷洞之旅\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 35 && who->get_legend(TASK_37,25) && !who->get_legend(TASK_37,26) )
	{
		tmp += sprintf(ESC HIY "表弟的口信\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( ( who->get_level() >=54 && !who->get_legend(TASK_2_00,7) ) || ( who->get_legend(TASK_2_00,7) && !who->get_legend(TASK_2_00,8) ) || ( who->get_legend(TASK_2_00,8) && !who->get_legend(TASK_2_00,9) ) ) 
		tmp += sprintf(ESC HIY "怨鬼之灵\ntalk %x# welcome.6\n",getoid(me)); 
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		DIPLOMAT_D->do_look( who, this_object() ); 
	
}
void do_relation( string arg ) { DIPLOMAT_D->do_relation( this_player(), this_object(), arg ); }

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p;
        object who,item,item2,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我幼年贪玩的时候被匪人掳到了一个非常美丽的洞穴，虽然起初被那些铜甲尸吓了个半死，弄得狼狈不堪，但是幸好后来被一个老道长救了出来，之后大病了一场，但是对于里面诡异奇丽的景色仍然念念不忘，现在终于打听到那个地方叫做灵谷洞，可是其中险山恶水，非我所能前往，况且职责所限，必须时刻听从召唤，不能亲自前去。你可以代我前去再次探察一番吗，还有顺便帮我杀10只铜甲尸以出当年恶气。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_27,19) && !who->get_legend(TASK_27,20) )
 			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道我少时只是一时病痛之间的幻觉吗？哎，世间美梦莫非如此？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_27,20) && !who->get_legend(TASK_27,21) )
 			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原来少时经历果真不虚啊。……冷溪鸣泉，交错纵流，泻雪如玉，华彩四射，起落异石，惟妙惟肖，灵动若奇，遍布幽奥。洞口青帘，隐幽此间。谷含天光，纱雾如瀑。是为灵、谷之洞……不知何时本使才能重踏此洞啊。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 2:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,19) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->delete_save("qgsjtongjiasi");
        		who->set_legend(TASK_27,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,22,"灵谷洞之旅" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"灵谷洞之旅");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_27,20) && !who->get_legend(TASK_27,21) )
        	{
			who->delete_save("qgsjtongjiasi");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_27,21);
			who->add_exp(44000);
			who->add_potential(635);
			who->add_cash(43500);
			send_user(who,"%c%s",';',"灵谷洞之旅 经验 44000 潜能 635 金钱 43500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,22,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 35 && who->get_legend(TASK_37,25) && !who->get_legend(TASK_37,26) )
 			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我也好久没有见到我表弟他们一家了，真期待啊！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
        case 5:
        	if ( who->get_level() >= 35 && who->get_legend(TASK_37,25) && !who->get_legend(TASK_37,26) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_37,26);
			who->add_exp(2500);
			who->add_potential(60);
			who->add_cash(2000);
			send_user(who,"%c%s",';',"带口信给Tề Quốc Sử Tiết 经验 2500 潜能 60 金钱 2000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,44,"" );
        	}
        	break;
        case 6:
        	if ( who->get_level() >=54 && !who->get_legend(TASK_2_00,7) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你知道秦国有个成峤军营吗？听说是秦王的弟弟有心谋叛而私设的军营，军纪不严，常私掠人口进去不见出来。我担心怨气深重，将来兹事体大，你能否去替我收来怨鬼之灵，让我可以作法超度，以免今后会出来害人？这是搜魂法器，带它在身上杀死怨灵就能得到怨鬼之灵了。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_2_00,7) && !who->get_legend(TASK_2_00,8) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你还没有带来怨鬼之灵么？真担心啊！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_2_00,8) && !who->get_legend(TASK_2_00,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    感谢这位英雄，我现在可以作法超度亡魂怨鬼了……\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 7:
        	if ( who->get_level() >=54 && !who->get_legend(TASK_2_00,7) ) 
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			item = new("/item/98/0238");
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
        		who->set_legend(TASK_2_00,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,103,"怨鬼之灵" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"怨鬼之灵");
       		}
        	break;
        case 8:
        	if ( who->get_legend(TASK_2_00,8) && !who->get_legend(TASK_2_00,9) )
        	{
			if( !objectp( item = present("搜魂法器", who, 1, MAX_CARRY) ) )
			{
				send_user(who,"%c%s",'!',"你的搜魂法器呢?");
				return;	
			}
			if( !objectp( item2 = present("怨鬼之灵", who, 1, MAX_CARRY) ) )
			{
				send_user(who,"%c%s",'!',"你的怨鬼之灵呢?");
				return;	
			}
			item->remove_from_user();
			destruct(item);	
			item2->remove_from_user();
			destruct(item2);	
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_2_00,9);
			who->add_exp(9800);
			who->add_potential(500);
			who->add_cash(11600);
			send_user(who,"%c%s",';',"怨鬼之灵 经验 9800 潜能 500 金钱 11600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,103,"" );
		}
        	break;

        case 99:	
		DIPLOMAT_D->do_look( who, me); 
        	break;
        }
}
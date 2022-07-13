
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
        set_name("Tề Quốc Nội Chính Quan");
	set_real_name("Mạnh Thường Quân");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "build"         : (: do_build :),
                "upgrade"       : (: do_upgrade :),
                "plant"         : (: do_plant :),
                "food"          : (: do_food:),
                "welcome"	: (: do_welcome :),	
        ]) );
//	set("level",75);
//	set("legend",({32*24+17,}));
 	set("mpLegend",([75:({32*24+17,}),100:({32*36+14,}),]));
 	set("mpLegend2",([0:({32*31+10,32*39+24,}),75:({32*24+19,}),100:({32*36+16,}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who )
{
	int id;
	string tmp="";
	object me = this_object();
	
	id = getoid(me);
	if ( ( who->get_level() >= 75 && !who->get_legend(TASK_24,17) ) || ( who->get_legend(TASK_24,17) && !who->get_legend(TASK_24,19) ) )
	{
		tmp += sprintf(ESC HIY "搜寻官印\ntalk %x# welcome.1\n",id);
	}
        if ( who->get_legend(TASK_31,9) && !who->get_legend(TASK_31,10) ) 
		tmp += sprintf(ESC HIY "告知内政官\ntalk %x# welcome.4\n",id); 
        if ( who->get_legend(TASK_31,10) && !who->get_legend(TASK_31,11) ) 
		tmp += sprintf(ESC HIY "通告百姓\ntalk %x# welcome.4\n",id); 
	if ( (who->get_level() >= 100 && !who->get_legend(TASK_36,14)) || (who->get_legend(TASK_36,14) && !who->get_legend(TASK_36,16)) )
		tmp += sprintf(ESC HIY "瘟疫之灾\ntalk %x# welcome.7\n",id);
        if ( who->get_legend(TASK_39,23) && !who->get_legend(TASK_39,24) ) 
		tmp += sprintf(ESC HIY "寻求解救之道\ntalk %x# welcome.10\n",id); 
        if ( who->get_legend(TASK_39,24) && !who->get_legend(TASK_39,25) ) 
		tmp += sprintf(ESC HIY "赔礼道歉\ntalk %x# welcome.10\n",id); 
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
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_24,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你看起来挺强的，我有件事想委托你帮我去做一下，但是你可不能把这件事告诉别人。前几天我在批阅官文的时候，放在我桌子上面的一碗豆子突然变成一个豆兵把我手上的官印抢走了，没有了官印我就不可以批阅官文了，现在我已经积压了三天的官文没有批阅了，不把官印找回来的话恐怕很快就要惊动到大王。我必须在大王发觉之前把我的官印找回来，我已经派人打听过了，那个豆兵是在灵谷洞的豆兵的其中之一。我看你是足够强的，你去帮我把我的官印找回来吧。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_24,17) && !who->get_legend(TASK_24,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你可以快点把我的官印找回来吗？看来这件事已经瞒不了大王多久了。\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_24,18) && !who->get_legend(TASK_24,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我果然找对人了，多亏了你，不然让大王知道了我可就有麻烦了，我以后一定要更小心保护好我的官印，我会给你一笔很可观的报酬的！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 2:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_24,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,16,"搜寻官印" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"搜寻官印");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_24,18) && !who->get_legend(TASK_24,19) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"官印",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,19);
			who->add_exp(30000);
			who->add_potential(498);
			who->add_cash(30000);
			send_user(who,"%c%s",';',"搜寻官印 经验 30000 潜能 498 金钱 30000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,16,"" );
        	}
        	break;
	case 4:
        	if ( who->get_legend(TASK_31,9) && !who->get_legend(TASK_31,10) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这种祸害，壮士除得好！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,10) && !who->get_legend(TASK_31,11) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此等欺行霸市之徒，终于铲除，你代本官告知百姓让他们安心生意生活。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));

		break;
        case 5:
        	if ( who->get_legend(TASK_31,9) && !who->get_legend(TASK_31,10) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,10);
			who->add_exp(71000);
			who->add_potential(810);
			who->add_cash(56000);
			send_user(who,"%c%s",';',"告知内政官 经验 71000 潜能 810 金钱 56000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,48,"" );
			me->do_welcome(4);
        	}
        	break;  		
	case 6:
        	if ( who->get_legend(TASK_31,10) && !who->get_legend(TASK_31,11) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,11);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,49,"通告百姓" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"通告百姓");
        	}
        	break;
        case 7:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,14)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天哪，瘟神小两口吵架，结果瘟神躲到我们国家来兴风作浪，散播瘟疫，可恶，实在太可恶了，这位壮士，我要求你代表人民代表国家坚决对瘟神执行死刑！这种将自己私怨凌驾到百姓痛苦上的败类绝对不可以姑息迁忍！根据我们正义的眼线报告，瘟神正躲在白马庄肆意妄为，你速速前去消灭他！\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_36,14) && !who->get_legend(TASK_36,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    什么，那瘟神还很拽，你都没法子对付他？难道就任由我们百姓生活在水深火热中？你于心何忍啊，跟他讲什么道义，多找几个哥们，并肩子上！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_36,15) && !who->get_legend(TASK_36,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿嘿，这个死瘟神，终于变成死翘翘的瘟神了吧！犯我大齐者，虽神必诛！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 8:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,14)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_36,14);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,54,"瘟疫之灾" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"瘟疫之灾");
        	}
        	break;
	case 9:
        	if ( who->get_legend(TASK_36,15) && !who->get_legend(TASK_36,16) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/63037",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,16);
			who->add_exp(84000);
			who->add_potential(1040);
			who->add_cash(73000);
			send_user(who,"%c%s",';',"瘟疫之灾 经验 84000 潜能 1040 金钱 73000 六神丹图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,54,"" );
        	}
        	break; 
        case 10:
        	if ( who->get_legend(TASK_39,23) && !who->get_legend(TASK_39,24) ) 
 			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    他终于意识到了？唉，平时就不怎么好提醒他，既然他叫你问了，那你就帮他这个忙吧。\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_39,24) && !who->get_legend(TASK_39,25) ) 
 			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    冰冻三尺非一日之寒，他有今天的处境，也是很多平时的点滴小事积累起来的。不知他是否还记得他曾经借过齐国百姓唐茂的锄头，并且弄坏了就没还，所以你替他找把锄头来还给齐国百姓唐茂吧。他当初在天门阵的最低层想挖财宝，结果弄坏了，就顺手扔那里了，进门口的那里有几根石柱，或许锄头就扔哪个箱子里。\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));

		break;       	
	case 11:
        	if ( who->get_legend(TASK_39,23) && !who->get_legend(TASK_39,24) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_39,24);
			who->add_exp(36000);
			who->add_potential(600);
			who->add_cash(35000);
			send_user(who,"%c%s",';',"四面楚歌（1） 经验 36000 潜能 600 金钱 35000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,58,"" );
        		me->do_welcome(10);
        	}
        	break;
        case 12:
        	if ( who->get_legend(TASK_39,24) && !who->get_legend(TASK_39,25) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,25);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,62,"四面楚歌（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"四面楚歌（2）");
        	}
        	break;
        case 99:	
		INTERIOR_D->do_look( who, me); 
        	break;
        }

}        	
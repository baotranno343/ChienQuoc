
// 自动生成：/make/npc/make8010

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0050; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Thủ Vệ");
        set_city_name("Sở Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",15);
//        set("legend",({32*3+20}));
	set("mpLegend",([10:({32*37+17,}),15:({32*3+20}),90:({32*33+7}),95:({32*33+10,}),]));
	set("mpLegend2",([15:({32*3+21}),90:({32*33+9}),95:({32*33+12,}),]));
        setup();
}

string get_master() { return CITY_CHU->get_master(); }
string get_master_2() { return CITY_CHU->get_master_2(); }
string get_master_3() { return CITY_CHU->get_master_3(); }
void do_look( object who )
{ 
	int id;
	string tmp="";
	object me = this_object();
	id = getoid(me);

	if ( who->get_level() >= 10 && !who->get_legend(TASK_37,17) )
			tmp += ESC HIY "韩总管的帮助\n" + sprintf("talk %x# welcome.10\n", id); 
	if ( who->get_level() >= 15 && !who->get_legend(TASK_NEWBIE_03,21) )
	{
		tmp += sprintf(ESC HIY "孝顺的守卫\ntalk %x# welcome.1\n",id);
	}
	if ( ( who->get_level() >= 90 && !who->get_legend(TASK_33,7) ) || ( who->get_legend(TASK_33,7) && !who->get_legend(TASK_33,9) ) )
		tmp += sprintf(ESC HIY "多管闲事\ntalk %x# welcome.4\n",id);
	if ( ( who->get_level() >= 95 && !who->get_legend(TASK_33,10) ) || ( who->get_legend(TASK_33,10) && !who->get_legend(TASK_33,12) ) )
		tmp += sprintf(ESC HIY "铁观音茶\ntalk %x# welcome.7\n",id);

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
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_NEWBIE_03,20)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我母亲病得很重了，看了很多医生都无济于事，我打听到一个偏方，说用20个兽角熬成一碗水，喝了它就会痊愈。但自古忠孝不能两全，我每天还要在这看守城门，实在不能脱离岗位。你就帮我去找齐兽角吧！我一定会重重的谢你。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_save_2("souweisoujiao") < 20  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那兽角收集齐了吗？我母亲还等着它救命呢！\n"ESC"离开", me->get_name()));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真是太感谢你了！如果我母亲的病治好了，我一定会上门道谢的！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_NEWBIE_03,20)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_NEWBIE_03,20);
        		who->delete_save_2("souweisoujiao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,10,"孝顺的守卫" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"孝顺的守卫");        		
        	}
        	break;
        case 3:
        	if ( who->get_save_2("souweisoujiao") >= 20  )
        	{
			if ( TASK_LEGEND_D->check_task_item(who,"兽角",20) != 1)
				return;
        		who->delete_save_2("souweisoujiao");
			who->add_exp(850);
			who->add_potential(50);
			who->add_cash(1500);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03,21);
			send_user(who,"%c%s",';',"孝顺的守卫 经验 850 潜能 50 金钱 1500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,10,"" );
        	}
        	break;
	case 4:
		if ( who->get_level() >= 90 && !who->get_legend(TASK_33,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n   我从小有个异能，就是能听家禽的谈话，我母亲怕极了，都严禁我对他人说起，可是最近邻居家的鸡鸭都莫名其妙的失踪了，我忍不住又去听剩下那些鸡鸭的谈话，发现是虚陵洞的水精和土精把他们偷去说是要祭五脏庙，五脏庙在什么地方我不知道，可是我都把这些鸡鸭当成我自己的兄弟姐妹，不想他们有什么闪失，可是母亲不许我多管闲事，所以我想委托你帮我办办这件事，想必你一定乐于帮助我吧！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_33,7) && !who->get_legend(TASK_33,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道你连一点怜悯之心都没有吗，万物生灵，也是兄弟啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_33,8) && !who->get_legend(TASK_33,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你，看来你也是个热心肠的人。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 5:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_33,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_33,7);
        		who->delete_save("cgswsuijing");
        		who->delete_save("cgswtujing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,35,"多管闲事" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"多管闲事");        		
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_33,8) && !who->get_legend(TASK_33,9) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,9);
        		who->delete_save("cgswsuijing");
        		who->delete_save("cgswtujing");
			who->add_exp(63000);
			who->add_potential(908);
			who->add_cash(54500);
			send_user(who,"%c%s",';',"多管闲事 经验 63000 潜能 908 金钱 54500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,35,"" );
        	}
        	break;
	case 7:
		if ( who->get_level() >= 95 && !who->get_legend(TASK_33,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n   我老父最近突然说道多年没有品尝虚陵洞的铁观音茶了，说是当年他迷路碰到两位仙人要到的，说他最近可能不行了，催促我快点给点再寻来以偿心愿，可是我一介丁卒，哪里有那个能耐去虚陵洞找仙人要茶，听说大侠你身手不凡，也时常与仙人来往，可否完成老父这个心愿？只要20片可以泡一次的茶叶就好了。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_33,10) && !who->get_legend(TASK_33,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，我老父天天念叨，你能快点吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_33,11) && !who->get_legend(TASK_33,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔，果真仙茶，老远都闻到扑鼻的清香了！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 8:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_33,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_33,10);
        		who->delete_save("cgswtiegy");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,36,"铁观音茶" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"铁观音茶");        		
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_33,11) && !who->get_legend(TASK_33,12) )
        	{
			if ( TASK_LEGEND_D->check_task_item(who,"铁观音茶",20) != 1)
				return;
			TASK_LEGEND_D->give_item(who,"item/product/61016",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,12);
        		who->delete_save("cgswtiegy");
			who->add_exp(70000);
			who->add_potential(925);
			who->add_cash(58000);
			send_user(who,"%c%s",';',"铁观音茶 经验 70000 潜能 925 金钱 58000 神秘老火汤图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,36,"" );
        	}
        	break;
        case 10:
        	if ( who->get_level() >= 10 && !who->get_legend(TASK_37,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    母亲的身体一直很虚弱，现在冬天快来了，想给她买件厚实的棉袄过冬，可我手头有点拮据，所以我决定早做准备，多打几份工来凑足钱，我没念过书，很多东西不会，只能做点苦力活，突然想起那韩国韩总管是我家一个远房亲戚，你去问问他，看他能不能给我找个工钱高点的事做。\n    韩总管就在韩国王府里，你尽快去给我问问吧。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 11:
        	if ( who->get_level() >= 10 && !who->get_legend(TASK_37,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_37,17);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,43,"韩总管的帮助" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"韩总管的帮助");
        	}
        	break;
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;
        }
}
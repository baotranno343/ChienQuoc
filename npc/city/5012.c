
// 自动生成：/make/npc/make8012

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_out();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 0651; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tần Quốc Thủ Vệ");
        set_city_name("Tần Quốc");

        set_2( "talk", ([
                "out"           : (: do_out :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("in", 13);
        set("out", 11);
//        set("level",64);
//        set("legend",({32*20+4}));
	set("mpLegend",([60:({32*20+4}),100:({32*39+14})]));
	set("mpLegend2",([60:({32*20+6,}),100:({32*39+16,32*39+19,32*39+22,})]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
        if ( (who->get_level() >= 60 && !who->get_legend(TASK_20,4)) || (who->get_legend(TASK_20,4)&&!who->get_legend(TASK_20,6)) ) 
		tmp += sprintf(ESC HIY "杀人恶魔\ntalk %x# welcome.1\n",getoid(me)); 
        if ( (who->get_level() >= 100 && !who->get_legend(TASK_39,14)) || (who->get_legend(TASK_39,14)&&!who->get_legend(TASK_39,16)) ) 
		tmp += sprintf(ESC HIY "蓝魔之泪\ntalk %x# welcome.4\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_39,16) && !who->get_legend(TASK_39,17)) || (who->get_legend(TASK_39,17)&&!who->get_legend(TASK_39,19)) ) 
		tmp += sprintf(ESC HIY "棉线与皂角\ntalk %x# welcome.4\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_39,19) && !who->get_legend(TASK_39,20)) || (who->get_legend(TASK_39,20)&&!who->get_legend(TASK_39,22)) ) 
		tmp += sprintf(ESC HIY "究根问底\ntalk %x# welcome.4\n",getoid(this_object())); 

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look_2( who, me ); 
	
}
void do_out() { GUARDER_D->do_out( this_player(), this_object() ); }

void do_record() { GUARDER_D->do_record( this_player(), this_object() ); }

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
        	if (who->get_level() >= 60 && !who->get_legend(TASK_20,4))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近秦长城一带的百姓常常莫名其妙被分尸杀害，追查许久，终于发现原来是秦长城上杀人成瘾的刀盾兵所为，然而他们凶恶成性又异常狡猾，大王严令不许一个人漏网，但是又不能因此而同守城的将领起嫌隙，他命我们暗地里找个身手高强，又能严守秘密的壮士去执行此事，我看壮士正是适当人员，就请你走一趟，消灭那20个为非作歹，灭绝人性的刀盾兵吧。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,4) && !who->get_legend(TASK_20,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    恶魔不除，王法何在，天理何存，百姓何苦！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_20,5) && !who->get_legend(TASK_20,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    消灭了这群恶魔，这周围的老百姓可就安心多了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if(who->get_level() >= 60 && !who->get_legend(TASK_20,4))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,4);
        		who->delete_save_2("sarenemo");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,48,"杀人恶魔" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"杀人恶魔");
        	}
        	break;
	case 3:
        	if ( who->get_legend(TASK_20,5) && !who->get_legend(TASK_20,6) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_20,6);
        		who->delete_save_2("sarenemo");
			who->add_exp(7700);
			who->add_potential(270);
			who->add_cash(8000);
			send_user(who,"%c%s",';',"杀人恶魔 经验 7700 潜能 270 金钱 8000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,48,"" );
        	}
        	break;     
	case 4:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_39,14) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，最近有个神秘人物要做一件非常重要同时又难办的事情，需要天门阵的蓝魔之泪，那些守阵的神将身上一定有。你可别问我为什么要找这个，不然你会有更多的麻烦，这个神秘人物的这件秘密，你最好还是躲远点好。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_39,14) && !who->get_legend(TASK_39,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    找不来的话，永远都别想知道为什么！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_39,15) && !who->get_legend(TASK_39,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    说了你别问你还要问，你这不是拿自己小命当儿戏吗，我是不忍心你年纪轻轻就送了性命，你还是走吧，什么？你不怕？好，好，好，你等等我，我们找个僻静角落。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_39,16) && !who->get_legend(TASK_39,17) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，都说是为了你好了，你这不难为我嘛，我可不想被人骂作误人性命啊，这样吧，你先去天门阵收集5个棉线、7个皂角，回来再说吧。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_39,17) && !who->get_legend(TASK_39,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，说过不要有太大的好奇心，不然会惹来一身的麻烦！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_39,18) && !who->get_legend(TASK_39,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你还要问吗？如果还有好奇心的话，你是要付出代价的。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_39,19) && !who->get_legend(TASK_39,20) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你果真契而不舍啊，但是我担心你会遭到别人追杀，那你先去干掉天门阵2层的地煞门众守3个，3层的太极门众守6个，据说就是他们在监视和追杀你，你干掉了我就可以放心告诉你了。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_39,20) && !who->get_legend(TASK_39,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你不能完成我吩咐的事情，我是怎样都不会告诉你的！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_39,21) && !who->get_legend(TASK_39,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，你这个家伙果然上当了，我可没有什么秘密，是你非得究根问底的，我只不过是消遣下！\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 5:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_39,14) ) 
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,14);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,56,"究根问底（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"究根问底（1）");
        	}
        	break;
	case 6:
        	if ( who->get_legend(TASK_39,15) && !who->get_legend(TASK_39,16) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"蓝魔之泪",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_39,16);
			who->add_exp(35000 );
			who->add_potential(649);
			who->add_cash(55000);
			send_user(who,"%c%s",';',"究根问底（1） 经验 35000  潜能 649 金钱 55000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,56,"" );
        		me->do_welcome(4);
        	}
        	break;
        case 7:
        	if ( who->get_legend(TASK_39,16) && !who->get_legend(TASK_39,17) ) 
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,17);
        		who->delete_save("qgswmianxian");
        		who->delete_save("qgswzaojiao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,57,"究根问底（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"究根问底（2）");
        	}
        	break;
	case 8:
        	if ( who->get_legend(TASK_39,18) && !who->get_legend(TASK_39,19) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"棉线",5) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"皂角",7) != 1 )
        		{
				TASK_LEGEND_D->give_item(who,"item/98/0187",5);
        			return;
        		}
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_39,19);
        		who->delete_save("qgswmianxian");
        		who->delete_save("qgswzaojiao");
			who->add_exp(40000);
			who->add_potential(658);
			who->add_cash(38000);
			send_user(who,"%c%s",';',"究根问底（2） 经验 40000 潜能 658 金钱 38000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,57,"" );
        		me->do_welcome(4);
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_39,19) && !who->get_legend(TASK_39,20) ) 
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,20);
        		who->delete_save("qgswdisamzs");
        		who->delete_save("qgswtaijimzs");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,58,"究根问底（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"究根问底（3）");
        	}
        	break;
	case 10:
        	if ( who->get_legend(TASK_39,21) && !who->get_legend(TASK_39,22) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/64171",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_39,22);
        		who->delete_save("qgswdisamzs");
        		who->delete_save("qgswtaijimzs");
			who->add_exp(145000);
			who->add_potential(1500);
			who->add_cash(148000);
			send_user(who,"%c%s",';',"究根问底（3） 经验 145000 潜能 1500 金钱 148000 飞天战盔图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,58,"" );
        	}
        	break;
        case 99:
        	GUARDER_D->do_look_2( who, me ); 
        	break;     
        }
}
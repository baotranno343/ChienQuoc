
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5405; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Trang Phục");
	set_real_name("Tiên Vu lan");
        set_city_name("Sở Quốc");

        set_2( "good", ([
                "01" : "/item/60/0010",
                "02" : "/item/61/0010",
                "03" : "/item/65/0010",
                "04" : "/item/66/0010",
                "05" : "/item/88/0010",

        ]) );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level", 31);
//        set("legend", ({ 32*8+10 })); 
	set("mpLegend",([30:({32*8+10}),35:({32*9+10})]));
	set("mpLegend2",([30:({32*8+12}),35:({32*9+12})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	"/quest/help"->send_help_tips(who, 40);
	result = sprintf("%s：\n    "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	if ( (who->get_level() >= 30 && !who->get_legend(TASK_08,10)) || (who->get_legend(TASK_08,10)&&!who->get_legend(TASK_08,12)) )
	{
		result += sprintf(ESC HIY "沼泽惊魂\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 35 && !who->get_legend(TASK_09,10) ) || ( who->get_legend(TASK_09,10) && !who->get_legend(TASK_09,12) ) )
	{
		result += sprintf(ESC HIY "湖口村的血迹\ntalk %x# welcome.4\n",getoid(me));
	}
	result += sprintf(ESC "哪里有适合我的装备？\ntalk %x# welcome.99\n", getoid(me) ) ;        	
	result += sprintf( ESC "交易\nlist %x#\n" ESC "我只是随便看看\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), result );
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
       	string *nTmp,tmp;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    沼泽，本是一个阴气很重的地方，因为很少有人去，所以聚集了不少游魂野鬼，而这些游魂野鬼里，有少数是含恨死去的，所以，它们幻化为厉鬼，专门祸害那些因为有重要事情而不得不去沼泽的人，只要是遇见这些厉鬼的人，没一个能从沼泽走出来……\n    我想你是习武之人，应该肩负起惩恶扬善的重任，所以，这件事情交给你了！当然，我不会让你白做这件事的，你去沼泽边缘铲除掉厉鬼后，回来我这里，我会付给你报酬的。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_08,10) && !who->get_legend(TASK_08,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我以后再也不打那走了，我宁愿多走几步路都可以。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_08,11) && !who->get_legend(TASK_08,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了，以后从那路过就再也不用担心那厉鬼去作祟。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,16,"沼泽惊魂" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"沼泽惊魂");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_08,11) && !who->get_legend(TASK_08,12) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),30,HEAD_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,12);
			who->add_exp(2400);
			who->add_potential(80);
			who->add_cash(1800);
			send_user(who,"%c%s",';',sprintf("沼泽惊魂 经验 2400 潜能 80 金钱 1800 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,16,"" );
        	}
        	break;   
        case 4:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    黄鼠狼给鸡拜年——没安好心。\n    现在的黄鼠狼都成精了，不止是鸡，连家里养的猪啊羊啊之类的它们都敢咬，我听百姓说鄱阳湖那边的湖口村经常丢失牲口，估计就是黄鼠狼精们做的好事！\n    根据血迹的方向，我知道了黄鼠狼的老窝，但是我只不过是一个商人，所以没有能力去与它们决斗！但是这样拖下去也不是办法，所以你去鄱阳湖的湖口村瞅瞅吧，如果找到黄鼠狼精，你就干掉它吧！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_09,10) && !who->get_legend(TASK_09,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那妖精真有这么厉害吗？真是可怕！\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,11) && !who->get_legend(TASK_09,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下那里的老百姓可高兴了，呵呵……\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 5:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_09,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,26,"湖口村的血迹" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"湖口村的血迹");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_09,11) && !who->get_legend(TASK_09,12) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,2) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/66006",1);

        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),40,BOOTS_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			item->set_record(1);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move(who,-1);
			item->add_to_user(p);

			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_09,12);
			who->add_exp(2600);
			who->add_potential(90);
			who->add_cash(2200);
			send_user(who,"%c%s",';',sprintf("湖口村的血迹 经验 2600 潜能 90 金钱 2200 土制炸弹图纸 1 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,26,"" );
        	}
        	break;
        case 99:
        	"/npc/base/0005"->do_welcome2(me, "99");
        	break;     
        }
}
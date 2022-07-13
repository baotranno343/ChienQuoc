
// 自动生成：/make/npc/make8084

#include <npc.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5701; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tần Quốc Bá Tánh");
	set_real_name("Trọng Mạc");
        set_city_name("Tần Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",65);
//        set("legend",({32*20+10}));
	set("mpLegend",([65:({32*20+10}),70:({32*22+8}),105:({32*39+1})]));
	set("mpLegend2",([65:({32*20+12,32*20+15,32*20+18,}),0:({32*43+19}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( ( who->get_level() >= 65 && !who->get_legend(TASK_20,10) ) || ( who->get_legend(TASK_20,10) && !who->get_legend(TASK_20,12) ) )
	{
		tmp += sprintf(ESC HIY "祭祀的纸钱\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_legend(TASK_20,12) && !who->get_legend(TASK_20,13) ) || ( who->get_legend(TASK_20,13) && !who->get_legend(TASK_20,15) ) )
	{
		tmp += sprintf(ESC HIY "菊花酒\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_legend(TASK_20,15) && !who->get_legend(TASK_20,16) ) || ( who->get_legend(TASK_20,16) && !who->get_legend(TASK_20,18) ) )
	{
		tmp += sprintf(ESC HIY "老酒\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 70 && !who->get_legend(TASK_22,8) )
	{
		tmp += sprintf(ESC HIY "道听途说\ntalk %x# welcome.8\n",getoid(me));
	}
	if ( who->get_level() >= 105 && !who->get_legend(TASK_39,1) )
		tmp += sprintf(ESC HIY "求份差事\ntalk %x# welcome.10\n",getoid(me));
        if ( who->get_legend(TASK_43,18) && !who->get_legend(TASK_43,19) ) 
		tmp += sprintf(ESC HIY "朋友的帮助\ntalk %x# welcome.12\n",getoid(me)); 

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name()) +
		tmp +
		ESC"离开");
	else
		more_look_menu( who, sprintf( "%s：\n    %s\n", get_name(), "/quest/word"->get_country_word(me) ) );
	
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
        	if (who->get_level() >= 65 && !who->get_legend(TASK_20,10))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    九月初九重阳节，家人团聚愈发想念起亡妻来，听说秦长城上的纸钱能穿越无定河直达幽冥，不会被路上的小鬼们克扣，你能帮我找来吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,10) && !who->get_legend(TASK_20,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    过了重阳节再送钱给亡人，会不敬的。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_20,11) && !who->get_legend(TASK_20,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    直接兑付的纸钱找到了，除了对亡人的祭奠，还有对生人的欢聚，我们还差点东西。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,12) && !who->get_legend(TASK_20,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    九月称为菊月，重阳日称为菊节。乡俗这一日，设菊花宴，点菊花灯，饮菊花茶，品菊花酒，睡菊花枕，可百病不生，长生不老。今年重阳又到酿菊花酒的日子了，上次周国守卫说他老娘开了个很大的花圃，里面就有不少菊花，他早已允诺送我一点了，你就辛苦跑一趟，帮我弄来吧。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,13) && !who->get_legend(TASK_20,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    菊花呢？给我要来了吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_20,14) && !who->get_legend(TASK_20,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    九月九,九重阳,菊花做酒满缸香\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,15) && !who->get_legend(TASK_20,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    菊花有了，但是用来泡菊花的酒可不能太差，在秦有一个很出名的酒鬼，他在平阳镇，你去看看能不能从他那讨到老酒，当然，同酒鬼谋酒，无异于与虎谋皮，那你就直接一拳打晕他，省得他罗嗦。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,16) && !who->get_legend(TASK_20,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    一拳打晕他，别同他客气，就算他醒来也不敢怎么样。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_20,17) && !who->get_legend(TASK_20,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    古语有云：九月九日，佩茱萸，食莲耳，饮菊花酒，令长寿，今年的菊花酒我已经可以起坛了，壮士要不先来尝一口？\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 2:
        	if(who->get_level() >= 65 && !who->get_legend(TASK_20,10))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,10);
        		who->delete_save_2("qgbxzhiqian");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,50,"重阳节（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"重阳节（1）");
        	}
        	break;
       case 3:
        	if ( who->get_legend(TASK_20,11) && !who->get_legend(TASK_20,12) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"纸钱",5) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_20,12);
        		who->delete_save_2("qgbxzhiqian");
			who->add_exp(7800);
			who->add_potential(280);
			who->add_cash(8000);
			send_user(who,"%c%s",';',"重阳节（1） 经验 7800 潜能 280 金钱 8000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,50,"" );
        	}
        	break;    
	case 4:
        	if( who->get_legend(TASK_20,12) && !who->get_legend(TASK_20,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,51,"重阳节（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"重阳节（2）");
        	}
        	break; 
	case 5:
        	if ( who->get_legend(TASK_20,14) && !who->get_legend(TASK_20,15) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"菊花",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_20,15);
			who->add_exp(7000);
			who->add_potential(260);
			who->add_cash(7500);
			send_user(who,"%c%s",';',"重阳节（3） 经验 7000 潜能 260 金钱 7500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,52,"" );
			me->do_welcome(1);
        	}
        	break;  
	case 6:
        	if( who->get_legend(TASK_20,15) && !who->get_legend(TASK_20,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,53,"重阳节（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"重阳节（4）");
        	}
        	break; 
	case 7:
        	if ( who->get_legend(TASK_20,17) && !who->get_legend(TASK_20,18) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"老酒",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64100",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_20,18);
			who->add_exp(13000);
			who->add_potential(750);
			who->add_cash(17000);
			send_user(who,"%c%s",';',"重阳节（4） 经验 13000 潜能 750 金钱 17000 金丝行装图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,53,"" );
        	}
        	break; 
        case 8:
		if ( who->get_level() >= 70 && !who->get_legend(TASK_22,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近我老婆子在街上碰到王宫里面当差的女儿，听她悄悄的说秦宫里有妖魔作祟，但是她看见了来寻她的宫女不敢多说就赶紧离开了，应该这个时候秦宫会重金招募除妖的壮士，你不妨去试试看，你先去向秦总管试探试探。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 9:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_22,8) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_22,8);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,43,"道听途说" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"道听途说");
        	}
        	break; 
        case 10:
		if ( who->get_level() >= 105 && !who->get_legend(TASK_39,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    男子汉大丈夫，不该碌碌无为，而我活到现在，确实是没有闯出一番大事业，在秦过着平淡的日子，无所作为，我希望有一天我能成为将军，驰骋在战场上，而不是永远呆在家里耕种，我想，做将军需要从士兵做起，正好听到燕国军队需要士兵，我想我这次豁出去了，就算户籍官知道了要开除我的户籍，我也顾不上了，还麻烦你先去燕国大将军那里给我问问是否有此事。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 11:
        	if ( who->get_level() >= 105 && !who->get_legend(TASK_39,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,93,"求份差事" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"求份差事");
        	}
        	break; 
        case 12:
		if ( who->get_legend(TASK_43,18) && !who->get_legend(TASK_43,19) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真是万分感谢你啊，这下子至少我们闺女可以减少些痛苦了……恩人哪（Tần Quốc Bá TánhTrọng Mạc痛哭流涕状，抓住你死死不放手，疼的你龇牙咧嘴，奋力才从激动不已的Tần Quốc Bá TánhTrọng Mạc手里挣脱。）\n"ESC"完成任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
	case 13:
        	if ( who->get_legend(TASK_43,18) && !who->get_legend(TASK_43,19) ) 
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"救急丹",5) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_43,19);
        		who->delete_save("qgswjiujd");
			who->add_exp(91000);
			who->add_potential(1000);
			who->add_cash(92000);
			send_user(who,"%c%s",';',"朋友的帮助 经验 91000 潜能 1000 金钱 92000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,59,"" );
        	}
        	break;
        }
}
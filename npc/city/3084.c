
// 自动生成：/make/npc/make8084

#include <npc.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 7805; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Bá Tánh");
	set_real_name("Ngô Cơ");
        set_city_name("Triệu Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",54);
//        set("legend",({32*15+24}));
	set("mpLegend",([80:({32*27+10}),105:({32*39+23}),50:({32*15+24}),55:({32*16+14,32*16+20,32*16+23,32*16+26,32*17+7,32*17+25})]));
	set("mpLegend2",([0:({32*41+30,32*42+6,32*42+11,32*42+14,32*42+24,32*42+27,32*43+6,}),80:({32*27+15,32*27+18,}),100:({32*38+28,}),105:({32*40+4}),50:({32*15+26,}),55:({32*16+16,32*16+22,32*16+25,32*16+28,32*17+9,32*17+27,})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( ( who->get_level() >= 50 && !who->get_legend(TASK_15,24) ) || ( who->get_legend(TASK_15,24) && !who->get_legend(TASK_15,26) ) )
	{
		tmp += sprintf(ESC HIY "Sản xuất công cụ\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_16,14) ) || ( who->get_legend(TASK_16,14) && !who->get_legend(TASK_16,16) ) )
	{
		tmp += sprintf(ESC HIY "长城上的哭泣\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_16,20) ) || ( who->get_legend(TASK_16,20) && !who->get_legend(TASK_16,22) ) )
	{
		tmp += sprintf(ESC HIY "临终寄托\ntalk %x# welcome.7\n",getoid(me));
	}
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_16,23) ) || ( who->get_legend(TASK_16,23) && !who->get_legend(TASK_16,25) ) )
	{
		tmp += sprintf(ESC HIY "神衣传说\ntalk %x# welcome.10\n",getoid(me));
	}
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_16,26) ) || ( who->get_legend(TASK_16,26) && !who->get_legend(TASK_16,28) ) )
	{
		tmp += sprintf(ESC HIY "千里神行\ntalk %x# welcome.13\n",getoid(me));
	}
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_17,7) ) || ( who->get_legend(TASK_17,7) && !who->get_legend(TASK_17,9) ) )
	{
		tmp += sprintf(ESC HIY "夜半钟声\ntalk %x# welcome.16\n",getoid(me));
	}
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_17,25) ) || ( who->get_legend(TASK_17,25) && !who->get_legend(TASK_17,27) ) )
	{
		tmp += sprintf(ESC HIY "打家劫舍\ntalk %x# welcome.19\n",getoid(me));
	}
	if ( who->get_level() >= 80 && !who->get_legend(TASK_27,10) )
	{
		tmp += sprintf(ESC HIY "同心锁\ntalk %x# welcome.22\n",getoid(me));
	}
	if ( who->get_legend(TASK_27,14) && !who->get_legend(TASK_27,15) )
	{
		tmp += sprintf(ESC HIY "同心锁\ntalk %x# welcome.22\n",getoid(me));
	}
	if ( (who->get_legend(TASK_27,15) && !who->get_legend(TASK_27,16)) || (who->get_legend(TASK_27,16) && !who->get_legend(TASK_27,18)) )
	{
		tmp += sprintf(ESC HIY "同心锁\ntalk %x# welcome.22\n",getoid(me));
	}
	if ( who->get_level() >=100 && who->get_legend(TASK_38,27) && !who->get_legend(TASK_38,28) )
		tmp += sprintf(ESC HIY "恩怨\ntalk %x# welcome.27\n",getoid(me));
	if ( who->get_level() >=105 && !who->get_legend(TASK_39,23) )
		tmp += sprintf(ESC HIY "寻求解救之道\ntalk %x# welcome.29\n",getoid(me));
        if ( who->get_legend(TASK_40,3) && !who->get_legend(TASK_40,4) ) 
		tmp += sprintf(ESC HIY "亲力而为\ntalk %x# welcome.29\n",getoid(me)); 
	if ( who->get_legend(TASK_42,5) && !who->get_legend(TASK_42,6) )
		tmp += sprintf(ESC HIY "询查战报\ntalk %x# welcome.32\n",getoid(me));
	if ( who->get_legend(TASK_42,6) && !who->get_legend(TASK_41,30) )
		tmp += sprintf(ESC HIY "勇闯天门阵\ntalk %x# welcome.32\n",getoid(me));
	if ( who->get_legend(TASK_41,30) && !who->get_legend(TASK_42,7) )
		tmp += sprintf(ESC HIY "搜寻战报\ntalk %x# welcome.32\n",getoid(me));
	if ( who->get_legend(TASK_42,10) && !who->get_legend(TASK_42,11) )
		tmp += sprintf(ESC HIY "询查原因\ntalk %x# welcome.37\n",getoid(me));
	if ( who->get_legend(TASK_42,11) && !who->get_legend(TASK_42,14) )
		tmp += sprintf(ESC HIY "小试身手\ntalk %x# welcome.37\n",getoid(me));
	if ( who->get_legend(TASK_42,14) && !who->get_legend(TASK_42,15) )
		tmp += sprintf(ESC HIY "除掉刺客\ntalk %x# welcome.37\n",getoid(me));
	if ( who->get_legend(TASK_42,23) && !who->get_legend(TASK_42,24) )
		tmp += sprintf(ESC HIY "探访民情\ntalk %x# welcome.42\n",getoid(me));
	if ( who->get_legend(TASK_42,24) && !who->get_legend(TASK_42,27) )
		tmp += sprintf(ESC HIY "为民除害\ntalk %x# welcome.42\n",getoid(me));
	if ( who->get_legend(TASK_42,27) && !who->get_legend(TASK_43,1) )
		tmp += sprintf(ESC HIY "陈述实情\ntalk %x# welcome.42\n",getoid(me));
	if ( who->get_legend(TASK_43,5) && !who->get_legend(TASK_43,6) )
		tmp += sprintf(ESC HIY "询察起因\ntalk %x# welcome.47\n",getoid(me));
	if ( who->get_legend(TASK_43,6) && !who->get_legend(TASK_43,7) )
		tmp += sprintf(ESC HIY "查访知情人\ntalk %x# welcome.47\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name()) +
		tmp +
		ESC"Rời khỏi");
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
        int flag,p;
        object who,item,obj;  
        string cmd1;
       	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
 	case 1:
        	if ( who->get_level() >=50 && !who->get_legend(TASK_15,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Ngươi có thể tìm giúp ta Cái cuốc, Liêm đao, Bá ki được không ? nghe nói đánh Triệu Quốc Đao Thuẫn Binh hoặc Triệu Quốc Kiếm Thuẫn Bình tại Triệu Trường Thành đều có những công cụ này.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.2\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_15,24) && !who->get_legend(TASK_15,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Bộ công cụ kia ta không thể dùng!\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_15,25) && !who->get_legend(TASK_15,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Cám ơn ngươi, bây giờ có lẽ trồng trọt sẽ nhanh hơn.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.3\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_level() >=50 && !who->get_legend(TASK_15,24) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_15,24);
        		who->delete_save_2("bxcutou");
        		who->delete_save_2("bxliandao");
        		who->delete_save_2("bxboji");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,5,"Sản xuất công cụ" );
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Sản xuất công cụ");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_15,25) && !who->get_legend(TASK_15,26) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),50,WAIST_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"Cái cuốc",1) != 1 )
        			return;
			if (TASK_LEGEND_D->check_task_item(who,"Liêm đao",1) != 1 )
			{
				item = new("item/98/0068");
				p = item->move(who,-1);
				item->add_to_user(p);
        			return;
        		}
     			if (TASK_LEGEND_D->check_task_item(who,"Bá ki",1) != 1 )
        		{
				item = new("item/98/0068");
				p = item->move(who,-1);
				item->add_to_user(p);
        			item = new("item/98/0069");
				p = item->move(who,-1);
				item->add_to_user(p);
        			return;
        		}
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_15,26);
        		who->delete_save_2("bxcutou");
        		who->delete_save_2("bxliandao");
        		who->delete_save_2("bxboji");
			who->add_exp(6500);
			who->add_potential(265);
			who->add_cash(5600);
			send_user(who,"%c%s",';',sprintf("Sản xuất công cụ Kinh nghiệm 6500 Tiềm năng 265 Ngân luwọng 5600 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,5,"" );
        	}
        	break;  
 	case 4:
        	if ( who->get_level() >=55 && !who->get_legend(TASK_16,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    一个姑娘家的清白岂是能随意糟蹋的!可怜啊……\n    前几天我在燕长城的烽火台游玩，看到一个小姑娘被地痞欺负，我前去阻止，没想到他力大如牛，一把就将我推开，让我近不得身，可怜我眼睁睁的看着那如花似玉的小姑娘被他糟蹋!冤孽，冤孽啊!\n    你如果有侠义心肠，你就去燕长城的烽火台干掉那个叫石六的地痞吧，这家伙还不知道要害多少人!\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.5\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_16,14) && !who->get_legend(TASK_16,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这世道可真是乱啊!\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_16,15) && !who->get_legend(TASK_16,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这位%s可真是为民除害啊!\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.6\n"ESC"Rời khỏi", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	break;
	case 5:
        	if( who->get_level() >=55 && !who->get_legend(TASK_16,14) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_16,14);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,15,"长城上的哭泣" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"长城上的哭泣");
        	}
        	break;       
        case 6:
        	if ( who->get_legend(TASK_16,15) && !who->get_legend(TASK_16,16) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/stuff/0259",2);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_16,16);
			who->add_exp(6400);
			who->add_potential(230);
			who->add_cash(6500);
			send_user(who,"%c%s",';',"长城上的哭泣 经验 6400 潜能 230 金钱 6500 铁片 2");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,15,"" );
        	}
        	break;  
 	case 7:
        	if ( who->get_level() >=55 && !who->get_legend(TASK_16,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我的叔父临终前嘱咐我，不管用什么方法，一定要将燕长城烽火台上的三刀鬼除掉，我也不知道他们之间有什么恩怨，但是这是他的遗言，我也希望能达成他这个愿望.\n    可是我去燕长城挑战了三刀鬼三次，都没能成功，还差点丢了性命，听说三刀鬼号称三刀要人命，我能从他的刀下死里逃生已属万幸，所以想请你前去燕长城的烽火台除掉三刀鬼，完成我叔父的遗愿.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.8\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_16,20) && !who->get_legend(TASK_16,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我这个愿望是没有办法实现了.\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_16,21) && !who->get_legend(TASK_16,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    多谢%s大力相助!\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.9\n"ESC"Rời khỏi", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	break;
	case 8:
        	if( who->get_level() >=55 && !who->get_legend(TASK_16,20) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_16,20);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,17,"临终寄托" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"临终寄托");
        	}
        	break;       
        case 9:
        	if ( who->get_legend(TASK_16,21) && !who->get_legend(TASK_16,22) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/63017",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_16,22);
			who->add_exp(6600);
			who->add_potential(240);
			who->add_cash(6400);
			send_user(who,"%c%s",';',"临终寄托 经验 6600 潜能 240 金钱 6400 玉菩提图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,17,"" );
        	}
        	break;  
 	case 10:
        	if ( who->get_level() >=55 && !who->get_legend(TASK_16,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    小的时候跟人学女红，那时候只要是自己做出来的，啥玩意儿都觉得好，现在年纪大了，要求越来越高，所以就想做一件神衣，听说穿上这种用玉丝做成的神衣后，人看起来会年轻好几岁，真期待!\n    可是这玉丝是很难找的材料，听说有人曾经在燕长城的匝道上见到过，你愿意帮我找到它吗？\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.11\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_16,23) && !who->get_legend(TASK_16,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这或许只是个传说吧!我怎么能当真呢？\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_16,24) && !who->get_legend(TASK_16,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了，我的愿望终于要实现了.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.12\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
        	break;
	case 11:
        	if( who->get_level() >=55 && !who->get_legend(TASK_16,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_16,23);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,18,"神衣传说" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"神衣传说");
        	}
        	break;       
        case 12:
        	if ( who->get_legend(TASK_16,24) && !who->get_legend(TASK_16,25) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"玉丝",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_16,25);
			who->add_exp(6500);
			who->add_potential(230);
			who->add_cash(6300);
			send_user(who,"%c%s",';',"神衣传说 经验 6500 潜能 230 金钱 6300");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,18,"" );
        	}
        	break;  
 	case 13:
        	if ( who->get_level() >=55 && !who->get_legend(TASK_16,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    喂，那边的那个谁，千里马你听说过吧？不过我想你大概没听说过千里神行这种本领吧.\n    有一种工夫，学过之后，走起路似千里马，日行千里，不在话下，可我还真没见过哪个人有这样的神功，据说只要吃了神行露就可以神行千里了，难道你不想试试吗？只要你能在燕长城的匝道给我找到，我定会分你一半，我想一半的神行露吃下去，就算不能日行千里，五百里总可以吧，心动不如行动，赶紧去吧!\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.14\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_16,26) && !who->get_legend(TASK_16,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我还是老老实实做我的百姓吧!\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_16,27) && !who->get_legend(TASK_16,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈…我的出头之日来了.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.15\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
        	break;
	case 14:
        	if( who->get_level() >=55 && !who->get_legend(TASK_16,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_16,26);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,19,"千里神行" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"千里神行");
        	}
        	break;       
        case 15:
        	if ( who->get_legend(TASK_16,27) && !who->get_legend(TASK_16,28) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"神行露",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_16,28);
			who->add_exp(6500);
			who->add_potential(250);
			who->add_cash(6500);
			send_user(who,"%c%s",';',"千里神行 经验 6500 潜能 250 金钱 6500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,19,"" );
        	}
        	break;  
 	case 16:
        	if ( who->get_level() >=55 && !who->get_legend(TASK_17,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你说那坏了百年的钟突然自己响了，这事是不是忒奇怪？太诡异了!\n    我想钟响只有一个原因，就是一定有不干净的东西在作祟，我思来想去，大概是那冥之妖又出来作恶了，你去燕长城的匝道上除掉它吧!\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.17\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_17,7) && !who->get_legend(TASK_17,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这可真是恐怖，以后要小心行事.\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_17,8) && !who->get_legend(TASK_17,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真不愧为少年英雄啊!\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.18\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
        	break;
	case 17:
        	if( who->get_level() >=55 && !who->get_legend(TASK_17,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_17,7);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,22,"夜半钟声" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"夜半钟声");
        	}
        	break;       
        case 18:
        	if ( who->get_legend(TASK_17,8) && !who->get_legend(TASK_17,9) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_17,9);
			who->add_exp(6600);
			who->add_potential(250);
			who->add_cash(6700);
			send_user(who,"%c%s",';',"夜半钟声 经验 6600 潜能 230 金钱 6700");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,22,"" );
        	}
        	break;  
 	case 19:
        	if ( who->get_level() >=55 && !who->get_legend(TASK_17,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    赵五是个烧杀掳掠、无恶不作的家伙，最近他洗劫了不少百姓的家，搞得别人家破人亡，昨天我家也被他洗劫!\n    我和他无怨无仇，他居然这样对待我，这个梁子我是与他结定了!你先去给我教训他一顿吧，给他个下马威!\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.20\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_17,25) && !who->get_legend(TASK_17,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我得搬家了，不然下次再碰上那恶匪该怎么办？\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_17,26) && !who->get_legend(TASK_17,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真是太谢谢你了，总算出了我心中的一口恶气.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.21\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
        	break;
	case 20:
        	if( who->get_level() >=55 && !who->get_legend(TASK_17,25) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_17,25);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,28,"打家劫舍" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"打家劫舍");
        	}
        	break;       
        case 21:
        	if ( who->get_legend(TASK_17,26) && !who->get_legend(TASK_17,27) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_17,27);
			who->add_exp(6900);
			who->add_potential(260);
			who->add_cash(6800);
			send_user(who,"%c%s",';',"打家劫舍 经验 6900 潜能 260 金钱 6800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,28,"" );
        	}
        	break;  
 	case 22:
        	if ( who->get_level() >=80 && !who->get_legend(TASK_27,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我听说很多年前江湖上出现过一对宝物叫同心锁，只要两人分别佩戴，便可以随时找到对方.如果我和我的爱人都分别佩带了这对宝物，那么我们就不必长期忍受相思之苦了.我听说燕国的总管他对天下这宝物都很清楚，你可以替我去询问一下这件宝物的下落吗？\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.23\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_27,14) && !who->get_legend(TASK_27,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你给我向燕总管求得这封信，这样的话我就真的可以找到这对同心锁了.让我先看看这封信说什么，可能找同心锁的时候我还需要你的帮助.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.24\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_27,15) && !who->get_legend(TASK_27,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    根据燕总管给我的信里面的提示，这对同心锁应该就在万人坑里面的某一个骷髅身上.但是万人坑的骷髅我可打不过，所以我还需要你的帮忙，帮我去万人坑杀掉那里的骷髅，并找到在他们身上的同心锁.拜托了.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.25\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_27,16) && !who->get_legend(TASK_27,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    找不到同心锁，我和我的爱人相隔两个国家，每天我们都要受相思之苦的煎熬.\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_27,17) && !who->get_legend(TASK_27,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真的很感谢你，我有了这个同心锁，我和我的爱人就不必每天都要受相思之苦的煎熬了.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.26\n"ESC"Rời khỏi", me->get_name(),getoid(me)));

		break;
	case 23:
        	if( who->get_level() >=80 && !who->get_legend(TASK_27,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_27,10);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,42,"同心锁（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"同心锁（1）");
        	}
        	break;  
        case 24:
        	if ( who->get_legend(TASK_27,14) && !who->get_legend(TASK_27,15) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"燕总管的信",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_27,15);
			who->add_exp(24000);
			who->add_potential(420);
			who->add_cash(22000);
			send_user(who,"%c%s",';',"燕王爱珍玩（3） 经验 24000 潜能 420 金钱 22000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,38,"" );
			me->do_welcome(22);
        	}
        	break; 
	case 25:
        	if( who->get_legend(TASK_27,15) && !who->get_legend(TASK_27,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_27,16);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,43,"同心锁（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"同心锁（4）");
        	}
        	break;  
        case 26:
        	if ( who->get_legend(TASK_27,17) && !who->get_legend(TASK_27,18) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),80,NECK_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ; 
        		if (TASK_LEGEND_D->check_task_item(who,"同心锁",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_27,18);
			who->add_exp(100000);
			who->add_potential(1400);
			who->add_cash(100000);
			send_user(who,"%c%s",';',sprintf("燕王爱珍玩（4） 经验 100000 潜能 1400 金钱 100000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,43,"" );
        	}
        	break; 
	case 27:
		if ( who->get_level() >=100 && who->get_legend(TASK_38,27) && !who->get_legend(TASK_38,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我弟弟很满意现在的生活，没有勾心斗角，没有明争暗斗，我想，他是不会回去了.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.28\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		break;		
	case 28:
		if ( who->get_level() >=100 && who->get_legend(TASK_38,27) && !who->get_legend(TASK_38,28) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_38,28);
			who->add_exp(45000);
			who->add_potential(610);
			who->add_cash(40000);
			send_user(who,"%c%s",';',"恩怨 经验 45000 潜能 610 金钱 40000");
			send_user(who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,92,"" );
        	}
		break;
	case 29:
		if ( who->get_level() >=105 && !who->get_legend(TASK_39,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，昨天我终于嫁人了，结果周围亲戚朋友居然一个都没有来，新郎觉得娶我丢了面子，大发雷霆，关了门不许我进内屋，结果洞房花烛夜我居然呆在堂屋一个人度过，好不凄凉，为什么我的邻居亲友全都不愿意同我交往了呢，难道是平素我有什么得罪了他们了么，你去齐国内政官孟尝君那里帮我问问，好歹他是我所尊敬的长者，我平素也常常走动，应该会告诉我为什么吧.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.30\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_40,3) && !who->get_legend(TASK_40,4) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没想到齐国内政官还这样帮我，也谢谢你，你们说得对，有些事情是必须自己去弥补的.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.31\n"ESC"Rời khỏi", me->get_name(),getoid(me)));

		break;
	case 30:
        	if ( who->get_level() >=105 && !who->get_legend(TASK_39,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,23);
   			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,58,"四面楚歌（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"四面楚歌（1）");
        	}
        	break; 		
	case 31:
		if ( who->get_legend(TASK_40,3) && !who->get_legend(TASK_40,4) ) 
		{
			if (TASK_LEGEND_D->check_task_item(who,"修好的小木桶",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64172",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_40,4);
			who->add_exp(200500);
			who->add_potential(2255);
			who->add_cash(200500);
			send_user(who,"%c%s",';',"四面楚歌（5） 经验 200500 潜能 2255 金钱 200500 麒麟盔图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,9,"" );
        	}
		break;
	case 32:
		if ( who->get_legend(TASK_42,5) && !who->get_legend(TASK_42,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘘，你同我来.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.33\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,6) && !who->get_legend(TASK_41,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    据说战报被聚集在天门阵的地煞门偷去了，你先去杀30个地煞门众守和30个守阵天兵，然后我好用搜魂术探听下消息，\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.34\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_41,28) && !who->get_legend(TASK_41,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    集聚怨气的天门阵中魂魄不够，无法施法.\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_41,29) && !who->get_legend(TASK_41,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好，你先等等，我进屋施法，你可不要偷看，否则我的法术反噬可就要伤人伤己了!\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.35\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_41,30) && !who->get_legend(TASK_42,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呼呼，精神消耗太大了，累的我快脱了一层皮，以后没有什么高代价的事情我还是少用为妙.我知道了，那战报被人藏在天门阵二层南部角落的一个箱子里，你去将它寻到交给赵国内政官平原君.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.36\n"ESC"Rời khỏi", me->get_name(),getoid(me)));

		break;
	case 33:
		if ( who->get_legend(TASK_42,5) && !who->get_legend(TASK_42,6) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_42,6);
			who->add_exp(95000);
			who->add_potential(1650);
			who->add_cash(85000);
			send_user(who,"%c%s",';',"询查战报 经验 95000 潜能 1650 金钱 85000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,75,"" );
			me->do_welcome(32);
        	} 
		break;
	case 34:
		if ( who->get_legend(TASK_42,6) && !who->get_legend(TASK_41,28) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_41,28);
        		who->delete_save("zgbxdsmzs");
        		who->delete_save("zgbxshouztb");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,76,"勇闯天门阵" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"勇闯天门阵");
        	}
		break;
	case 35:
		if ( who->get_legend(TASK_41,29) && !who->get_legend(TASK_41,30) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_41,30);
        		who->delete_save("zgbxdsmzs");
        		who->delete_save("zgbxshouztb");
			who->add_exp(95000);
			who->add_potential(1650);
			who->add_cash(86000);
			send_user(who,"%c%s",';',"勇闯天门阵 经验 95000 潜能 1650 金钱 86000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,76,"" );
			me->do_welcome(32);
        	} 
		break;
	case 36:
		if ( who->get_legend(TASK_41,30) && !who->get_legend(TASK_42,7) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,77,"搜寻战报" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"搜寻战报");
        	}
		break;
	case 37:
		if ( who->get_legend(TASK_42,10) && !who->get_legend(TASK_42,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿嘿，你问别人不一定知道，问我算是问对了，我碰巧得知了一点点消息，不知道有什么奖赏没有？\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.38\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,11) && !who->get_legend(TASK_42,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎呀呀，看来我又得动用那个副作用极大的搜魂术了，据我所知，这件刺杀行动与太极门有关，你去天门阵三层杀30个太极门众守和30个守阵天兵，回来告诉我，我只好勉为其难再动用一次搜魂术了，这次你可得向御史大人报告一下我的功绩，赏赐一点都不能少，要不然我可就亏大了.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.39\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,12) && !who->get_legend(TASK_42,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道上次你Hoàn thành nhiệm vụ只是侥幸?那算了，别找我了，我乐得休息休息.\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_42,13) && !who->get_legend(TASK_42,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下子规矩不用我再重复了吧？出去顺手关门，不许偷窥，不许发出异动，否则一切后果由你负责，我概不负责!\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.40\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,14) && !who->get_legend(TASK_42,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好了，外面热锅上的小子，进来吧，这伙人带头的和主要出手的唤作徐四，好像并不是太极门人，不知道从哪里钻出来的，不过你也别指望从这种人嘴里撬出东西，最好一刀杀了他就一劳永逸，前提你干得掉他而不是他干掉你的话，他如今在天门阵三层北部一带联系手下，策划行动，你去那里找他决斗吧，如果你有命回来就去告诉赵国典狱官一声.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.41\n"ESC"Rời khỏi", me->get_name(),getoid(me)));

		break;
	case 38:
		if ( who->get_legend(TASK_42,10) && !who->get_legend(TASK_42,11) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_42,11);
			who->add_exp(96000);
			who->add_potential(1750);
			who->add_cash(87000);
			send_user(who,"%c%s",';',"询查原因 经验 96000 潜能 1750 金钱 87000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,78,"" );
			me->do_welcome(37);
        	} 
		break;
	case 39:
		if ( who->get_legend(TASK_42,11) && !who->get_legend(TASK_42,12) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,12);
        		who->delete_save("zgbxtjmzs");
        		who->delete_save("zgbxshouztb1");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,79,"小试身手" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"小试身手");
        	}
		break;
	case 40:
		if ( who->get_legend(TASK_42,13) && !who->get_legend(TASK_42,14) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_42,14);
        		who->delete_save("zgbxtjmzs");
        		who->delete_save("zgbxshouztb1");
			who->add_exp(97000);
			who->add_potential(1700);
			who->add_cash(88000);
			send_user(who,"%c%s",';',"小试身手 经验 97000 潜能 1700 金钱 88000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,79,"" );
			me->do_welcome(37);
        	} 
		break;
	case 41:
		if ( who->get_legend(TASK_42,14) && !who->get_legend(TASK_42,15) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,80,"除掉刺客" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"除掉刺客");
        	}
		break;
	case 42:
		if ( who->get_legend(TASK_42,23) && !who->get_legend(TASK_42,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你真的想听我们的声音？那究竟是想听好听的呢还是真的呢?\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.43\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,24) && !who->get_legend(TASK_42,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不知道你可听说有句童谣，天九地三，难过年关.这个地三，指的便是恶官叙三，他倚仗背后靠山，自己又手握实权，冒用丁税名义强索财物私宝，甚至强抢民女，破坏屋舍，还巧立名目中饱私囊，大家都惶惶不可终日，大王的威信受了践踏，现在离心向背的人日渐增多，怨声极大，要是恶官叙三不除，恐怕大王之信，将毁矣.那个叙三如今正在天门阵三层南部做客，壮士若不除此人，其他我也不敢再说了.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.44\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,25) && !who->get_legend(TASK_42,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来官官相护，我们百姓哪有出头之日!\n"ESC"Rời khỏi", me->get_name()));
		else if ( who->get_legend(TASK_42,26) && !who->get_legend(TASK_42,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这恶官总算是被除掉了.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.45\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,27) && !who->get_legend(TASK_43,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    至于上次童谣提及的天九，我也不敢直接同你说，怕你一时冲动误事，我将近段时间的事情都写在这张诉苦书上，你交给本国内政官由他再作定夺吧.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.46\n"ESC"Rời khỏi", me->get_name(),getoid(me)));

		break;
	case 43:
		if ( who->get_legend(TASK_42,23) && !who->get_legend(TASK_42,24) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_42,24);
			who->add_exp(98000);
			who->add_potential(1800);
			who->add_cash(89000);
			send_user(who,"%c%s",';',"探访民情 经验 98000 潜能 1800 金钱 89000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,83,"" );
			me->do_welcome(42);
        	} 
		break;
	case 44:
		if ( who->get_legend(TASK_42,24) && !who->get_legend(TASK_42,25) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,25);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,84,"为民除害" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"为民除害");
        	}
		break;
	case 45:
		if ( who->get_legend(TASK_42,26) && !who->get_legend(TASK_42,27) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_42,27);
			who->add_exp(97000);
			who->add_potential(1850);
			who->add_cash(90000);
			send_user(who,"%c%s",';',"为民除害 经验 97000 潜能 1850 金钱 90000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,84,"" );
			me->do_welcome(42);
        	} 
		break;
	case 46:
		if ( who->get_legend(TASK_42,27) && !who->get_legend(TASK_43,1) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0207",1);  
        		who->set_legend(TASK_43,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,85,"陈述实情" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"陈述实情");
        	}
		break;
	case 47:
		if ( who->get_legend(TASK_43,5) && !who->get_legend(TASK_43,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，此事说来话长.最近我们周围的亲朋好友，有许多都在赵长城口一带离奇失踪，失踪的有男有女，有老有少，至于个中原委，我们也想不明白.他们之间既不相识，又不相类，到底什么原因使得他们失踪呢？\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.48\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_43,6) && !who->get_legend(TASK_43,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我想起可能有个人能够帮助你彻查此事，你早日查明真相也好让我们安心啊，我在人口主要失踪地赵长城入口处一带，有个朋友叫做李防，你将我写的拜访信给他，他兴许能够透露更多的情况.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.49\n"ESC"Rời khỏi", me->get_name(),getoid(me)));

		break;
	case 48:
		if ( who->get_legend(TASK_43,5) && !who->get_legend(TASK_43,6) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_43,6);
			who->add_exp(93000);
			who->add_potential(1750);
			who->add_cash(91000);
			send_user(who,"%c%s",';',"询察起因 经验 93000 潜能 1750 金钱 91000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,88,"" );
			me->do_welcome(47);
        	} 
		break;
	case 49:
		if ( who->get_legend(TASK_43,6) && !who->get_legend(TASK_43,7) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0209",1);  
        		who->set_legend(TASK_43,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,89,"查访知情人" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"查访知情人");
        	}
		break;
        }
}
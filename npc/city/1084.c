
// 自动生成：/make/npc/make8084

#include <npc.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5901; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tề Quốc Bá Tánh");
	set_real_name("Đường Mậu");
        set_city_name("Tề Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",75);
//        set("legend",({32*24+23}));
 	set("mpLegend",([75:({32*24+23,}),85:({32*28+29,32*29+26}),100:({32*36+20,}),]));
 	set("mpLegend2",([0:({32*30+21,32*31+12,32*39+27,}),75:({32*24+25,}),85:({32*30+4,32*29+30}),100:({32*36+22,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{ 
	int id;
	string tmp="";
	object me = this_object();

	id = getoid(me);
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( (who->get_level() >= 75 && !who->get_legend(TASK_24,23)) || (who->get_legend(TASK_24,23)&&!who->get_legend(TASK_24,25)) )
	{
		tmp += sprintf(ESC HIY "有备无患\ntalk %x# welcome.1\n",id);
	}
        if ( who->get_level() >= 85 && !who->get_legend(TASK_28,29) ) 
		tmp += sprintf(ESC HIY "询问原因\ntalk %x# welcome.4\n",id); 
        if ( who->get_level() >= 85 && !who->get_legend(TASK_29,26) ) 
		tmp += sprintf(ESC HIY "探访将军\ntalk %x# welcome.6\n",id); 
	if ( who->get_legend(TASK_30,3) && !who->get_legend(TASK_30,4) )
		tmp += sprintf(ESC HIY "民间探访\ntalk %x# welcome.6\n",id);
	if ( (who->get_legend(TASK_30,4) && !who->get_legend(TASK_29,28)) || (who->get_legend(TASK_29,28) && !who->get_legend(TASK_29,30)))
		tmp += sprintf(ESC HIY "考验自己\ntalk %x# welcome.6\n",id);
	if ( who->get_legend(TASK_29,30) && !who->get_legend(TASK_30,5) )
		tmp += sprintf(ESC HIY "失而复得\ntalk %x# welcome.6\n",id);
	if ( who->get_legend(TASK_30,20) && !who->get_legend(TASK_30,21) )
		tmp += sprintf(ESC HIY "深入民间\ntalk %x# welcome.12\n",id);
	if ( who->get_legend(TASK_30,21) && !who->get_legend(TASK_30,22) )
		tmp += sprintf(ESC HIY "商人诉苦\ntalk %x# welcome.12\n",id);
        if ( who->get_legend(TASK_31,11) && !who->get_legend(TASK_31,12) ) 
		tmp += sprintf(ESC HIY "通告百姓\ntalk %x# welcome.15\n",id); 
	if ( (who->get_level() >= 100 && !who->get_legend(TASK_36,20)) || (who->get_legend(TASK_36,20) && !who->get_legend(TASK_36,22)) )
		tmp += sprintf(ESC HIY "远征\ntalk %x# welcome.17\n",id);		
        if ( who->get_legend(TASK_39,25) && !who->get_legend(TASK_39,27) ) 
		tmp += sprintf(ESC HIY "归还锄头\ntalk %x# welcome.20\n",id); 
        if ( who->get_legend(TASK_39,27) && !who->get_legend(TASK_40,1) ) 
		tmp += sprintf(ESC HIY "修理木桶\ntalk %x# welcome.20\n",id); 

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
        object who,item, *inv,item1;     
        string *nTmp,tmp;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_24,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    生活在这样的乱世，我们平民百姓之家不准备一些应急品是不行的，所以我们齐国的百姓通常都会准备一些救急丸，但是最近灵谷洞的那些妖怪们不知道出于什么居心把我们的救急丸都偷走了。听说最近又要打仗了，没有了救急丸恐怕咱们的性命就没什么保障了，你可以帮我去灵谷洞找回我们的救急丸吗？那里的所有妖怪都有我们的救急丸，我们的救急丸一共20个。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
 		else if ( who->get_legend(TASK_24,23) && !who->get_legend(TASK_24,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    战争很快就要开始了，可以的话请尽快帮我们拿回那些救急丸吧，不然战争开始，我们的性命难保了。\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_24,24) && !who->get_legend(TASK_24,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这些救急丸，我们的性命就多了一重保障，只希望这次的战争不要持续太长时间，不然，苦的是我们平民百姓啊！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
 
        	break;
        case 2:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_24,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,23);
        		who->delete_save_2("qgbxjiujiwan");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,18,"有备无患" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"有备无患");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_24,24) && !who->get_legend(TASK_24,25) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"救急丸",20) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,25);
        		who->delete_save_2("qgbxjiujiwan");
			who->add_exp(35000);
			who->add_potential(510);
			who->add_cash(33000);
			send_user(who,"%c%s",';',"有备无患 经验 35000 潜能 510 金钱 33000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,18,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 85 && !who->get_legend(TASK_28,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    想赚钱吗，最近那个数钱数到手抽筋的玉器商整日愁眉苦脸的样子，你去找找他，说不定可以赚一笔哦，他可是钱多的发烧的人。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 5:
        	if ( who->get_level() >= 85 && !who->get_legend(TASK_28,29) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,25,"询问原因" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询问原因");
        	}
        	break;
        case 6:
        	if ( who->get_level() >= 85 && !who->get_legend(TASK_29,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前天路过我军大营，看见军营上下好一阵忙乱，想必有什么麻烦事情，你如果闲的话去问问有没有你可以帮忙的地方，说不定会有意外的收获。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,3) && !who->get_legend(TASK_30,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这可得给我点时间，让我好好想想。\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,4) && !who->get_legend(TASK_29,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘘，我告诉你啊，我听说有个宝贝被一些刀俑和枪俑藏着呢，你要是有心不妨去看看说不定能捞到什么好东西呢。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_29,28) && !who->get_legend(TASK_29,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来你得多练练武功啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_29,29) && !who->get_legend(TASK_29,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……真不简单哦！\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_29,30) && !who->get_legend(TASK_30,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，那些刀俑和枪俑都被你清除了，这下子可好了，听说他们的主人藏了威虎将军令在将军古墓四层的宝箱里，命令他们看守，幸好他们主人最近看风声紧跑了，要是你没有干掉他们我还真不敢告诉你。快点去拿吧，将军如果有奖励别忘了分我一半啊！\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 7:
        	if ( who->get_level() >= 85 && !who->get_legend(TASK_29,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,30,"探访将军" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"探访将军");
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_30,3) && !who->get_legend(TASK_30,4) )
        	{ 
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,4);
			who->add_exp(57000);
			who->add_potential(790);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"民间探访 经验 57000 潜能 790 金钱 50000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,32,"" );
			me->do_welcome(6);
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_30,4) && !who->get_legend(TASK_29,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,28);
        		who->delete_save("qgbxdaoyong");
        		who->delete_save("qgbxqianyong");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,33,"考验自己" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"考验自己");
        	}
        	break;
        case 10:
        	if ( who->get_legend(TASK_29,29) && !who->get_legend(TASK_29,30) )
        	{
        		who->delete_save("qgbxdaoyong");
        		who->delete_save("qgbxqianyong");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,30);
			who->add_exp(60000);
			who->add_potential(780);
			who->add_cash(51000);
			send_user(who,"%c%s",';',"考验自己 经验 60000 潜能 780 金钱 51000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,33,"" );
			me->do_welcome(6);
        	}
        	break;
        case 11:
        	if ( who->get_legend(TASK_29,30) && !who->get_legend(TASK_30,5) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,5);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,34,"失而复得" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"失而复得");
        	}
        	break;
	case 12:
		if ( who->get_legend(TASK_30,20) && !who->get_legend(TASK_30,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    事情嘛，朱家丢了一只鸡，陈家丢了一只鸭，司马家婆媳在吵架，司空家兄弟闹分家，倩娘半夜私奔了，二壮上山被虎抓……您想听哪件？\n"ESC"完成任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,21) && !who->get_legend(TASK_30,22) )	
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你只想要有点功绩又不棘手的啊，真是的，年轻人怎么能够怕困难呢，怕困难总难免会遇到困难的，怕是没有用的，就像那个齐国商人猗顿，整天就怕被抢，怎么着，被抢了吧，哈哈！\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
			
		break;
        case 13:
        	if ( who->get_legend(TASK_30,20) && !who->get_legend(TASK_30,21) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,21);
			who->add_exp(69000);
			who->add_potential(810);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"深入民间 经验 69000 潜能 810 金钱 50000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,40,"" );
			me->do_welcome(12);
        	}
        	break;
        case 14:
        	if ( who->get_legend(TASK_30,21) && !who->get_legend(TASK_30,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,41,"商人诉苦" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"商人诉苦");
        	}
        	break;
        case 15:
        	if ( who->get_legend(TASK_31,11) && !who->get_legend(TASK_31,12) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    可以暂时喘口气了。\n"ESC"完成任务\ntalk %x# welcome.16\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 16:
        	if ( who->get_legend(TASK_31,11) && !who->get_legend(TASK_31,12) ) 
        	{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),90,ARMOR_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);        		
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,12);
			who->add_exp(69000);
			who->add_potential(830);
			who->add_cash(57000);
			send_user(who,"%c%s",';',sprintf("通告百姓 经验 69000 潜能 830 金钱 57000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,49,"" );
        	}
        	break;
        case 17:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,20)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近秦国指责我国向他们派遣间谍，严重伤害了两国人民之间的的传统友谊，提出了严重抗议，并保留诉诸武力的权力。哎，哪个国家没有派遣过间谍，不过是他们看来准备充分、发动战争的借口而已罢了，看来一场大战又是一触即发了，小老儿一介草民，可不想掺合进去做炮灰，乘还没有国家动员令之前赶紧跑路，哎，现在市面上粮食紧张，好多东西都采购不到了，看来同我一样想法的人还不少，可是我家老婆子坚持要做番薯糕和山药糕上路，说是吃不惯其他东西的味道，也不许我乱吃其他东西说会吃坏肚子，听说九曲桥有不少番薯和山药，不过那里怪物凶恶，小老儿自度没有能力去安全采到，看这位大侠武功盖世，侠义心肠，能否为老朽跑一趟?不多不多，有8个番薯，5个山药就好了。\n"ESC"接受任务\ntalk %x# welcome.18\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_36,20) && !who->get_legend(TASK_36,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎呀呀，快打起来了，大侠你快点行不？失礼失礼，我不是谎报军情，我说的是你再不找来，我家老婆子快要同我打起来了。你就可怜可怜我这把老骨头吧！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_36,21) && !who->get_legend(TASK_36,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵，等我老婆子做好了，也送你尝尝番薯糕和山药糕的味道。（凑近耳边低声道：）我也是吃上了瘾才娶我家老婆子的呢。\n"ESC"完成任务\ntalk %x# welcome.19\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 18:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,20)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_36,20);
        		who->delete_save("qgbxfansu");
        		who->delete_save("qgbxsanyao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,56,"远征" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"远征");
        	}
        	break;
	case 19:
        	if ( who->get_legend(TASK_36,21) && !who->get_legend(TASK_36,22) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"番薯",8) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"山药",5) != 1 )
        		{
        			TASK_LEGEND_D->give_item(who,"item/98/0169",8); 
        			return;
        		}
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,22);
        		who->delete_save("qgbxfansu");
        		who->delete_save("qgbxsanyao");
			who->add_exp(84000);
			who->add_potential(1040);
			who->add_cash(73000);
			send_user(who,"%c%s",';',"远征 经验 84000 潜能 1040 金钱 73000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,56,"" );
        	}
        	break; 
        case 20:
        	if ( who->get_legend(TASK_39,25) && !who->get_legend(TASK_39,26) ) 
 			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我听说赵国百姓叫你送锄头给我，还以为他改邪归正了呢，没想到狗改不了吃屎，他还是这德行。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_39,26) && !who->get_legend(TASK_39,27) ) 
 			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    他这个人呀，我都懒得说，既然你把锄头还回来了，那么以后我和他也不会有什么瓜葛了，当然，我再也不会借东西给他了。\n"ESC"完成任务\ntalk %x# welcome.21\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_39,27) && !who->get_legend(TASK_40,1) ) 
 			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    喂，那个谁，你是赵国百姓吴姬的儿女吧，真想不到，他居然有这么大的儿女了，居然有人肯娶她，真是咄咄怪事，你将这只小木桶拿到周国的妙手公输班那里修理下吧，我不说你也应该知道了，是的，这只小木桶是赵国百姓吴姬弄坏的，这可是上好的红木做的，可上次他说拿去装什么仙人醉，唬的我一愣一愣的，他啥时候有这么大本事能弄到那么多仙人醉了，结果还来时候居然坏了，他啥都没说扔下就走了，我一闻，半点酒味都没有，又弄坏我东西又谎话连篇，他不害臊我同他交往过了都为他害臊呢。\n"ESC"接受任务\ntalk %x# welcome.22\n"ESC"离开", me->get_name(),getoid(me)));
			
		break; 
	case 21:
        	if ( who->get_legend(TASK_39,26) && !who->get_legend(TASK_39,27) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"齐国百姓的锄头",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_39,27);
			who->add_exp(37000);
			who->add_potential(640);
			who->add_cash(38000);
			send_user(who,"%c%s",';',"四面楚歌（2） 经验 37000 潜能 640 金钱 38000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,62,"" );
        		me->do_welcome(20);
        	}
        	break;		
        case 22:
        	if ( who->get_legend(TASK_39,27) && !who->get_legend(TASK_40,1) ) 
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0190",1); 
        		who->set_legend(TASK_40,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,63,"四面楚歌（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"四面楚歌（3）");
        	}
        	break;
        }
}
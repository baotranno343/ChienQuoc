
#include <npc.h>
#include <ansi.h>
#include <cmd.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

// 函数:妙手公输班
int is_maker() { return 1; }

void do_make();
void do_make_2();
void do_welcome(string arg);

// 函数:获取人物造型
int get_char_picid() { return 6801; }

// 函数:构造处理
void create()
{
        set_name("Diệu Thủ Công Thâu Ban");

        set_2( "talk", ([
                "make"    : (: do_make :),
                "make2"   : (: do_make_2 :),
                "welcome"	: (: do_welcome :),
        ]));
 	set("mpLegend",([65:({32*51+4})]));
	set("mpLegend2",([0:({32*3+14,32*3+16,32*3+18,32*28+13,32*28+16,32*40+2,32*39+30}),
		65:({32*51+6})]));
        setup();
}

// 函数:对话处理
void do_look( object who )
{
	string tmp="";
        int id = getoid( this_object() );
	if ( who->get_legend(TASK_NEWBIE_03,13) && !who->get_legend(TASK_NEWBIE_03,19) )
	{
		tmp = sprintf(ESC HIY "买椟还珠\ntalk %x# welcome.1\n",id);
	}
	if ( who->get_legend(TASK_28,12) && !who->get_legend(TASK_28,13) )
		tmp += sprintf(ESC HIY "打造钥匙\ntalk %x# welcome.9\n",id);
	if ( ( who->get_legend(TASK_28,13) && !who->get_legend(TASK_28,14) ) || ( who->get_legend(TASK_28,14) && !who->get_legend(TASK_28,16) ) )
		tmp += sprintf(ESC HIY "特殊的木块 \ntalk %x# welcome.9\n",id);
        if ( who->get_legend(TASK_40,1) && !who->get_legend(TASK_40,2) )
		tmp += sprintf(ESC HIY "修理木桶\ntalk %x# welcome.13\n",id);
        if ( (who->get_legend(TASK_40,2) && !who->get_legend(TASK_39,28)) || (who->get_legend(TASK_39,28) && !who->get_legend(TASK_39,30)))
		tmp += sprintf(ESC HIY "修理的材料\ntalk %x# welcome.13\n",id);
        if ( who->get_legend(TASK_39,30) && !who->get_legend(TASK_40,3) )
		tmp += sprintf(ESC HIY "亲力而为\ntalk %x# welcome.13\n",id);
 	if ( who->get_legend(TASK_2_00,23) && !who->get_legend(TASK_2_00,24) && who->get_save("baifang_ms_2") != 1)
		tmp += sprintf(ESC HIY "拜访\ntalk %x# welcome.18\n",id);
	if ( (who->get_level() >= 70 && !who->get_legend(TASK_2_01,4)) ||
		 (who->get_legend(TASK_2_01,4) && !who->get_legend(TASK_2_01,6)) )
		tmp += sprintf(ESC HIY "机关密图\ntalk %x# welcome.19\n",id);

        more_look_menu( who, get_name() + ":\nTa chính là đệ nhất diệu thủ Công Thâu Ban ! ngươi tìm ta có chuyện chi ?\n"
                ESC "Hợp thành tinh thạch\n" + sprintf( "talk %x# make\n", id ) +
                ESC "Tinh luyện trang bị\n" + sprintf( "talk %x# make2\n", id ) +
			//	ESC "Hợp thành Đoạn Thạch\n" + sprintf( "talk %x# welcome.70\n", id ) +
                tmp +
            //    ESC "Hợp thành cùng tinh luyện\n" + sprintf( "talk %x# welcome.50\n", id ) +
            //    ESC "Phân giải rèn thạch\n" + sprintf( "talk %x# welcome.60\n", id ) +
                ESC "Rời khỏi\nCLOSE\n" );
}

// 函数:打开界面
void do_make()
{
//	send_user( this_player(), "%c%s", '!', "合成功能尚未开放." );
        send_user( this_player(), "%c%c%d", 0x25, 2, getoid( this_object() ) );    // 打开合成界面
}

// 函数:打开界面
void do_make_2()
{
//	send_user( this_player(), "%c%s", '!', "合成功能尚未开放." );
        send_user( this_player(), "%c%c%d", 0x25, 3, getoid( this_object() ) );    // 打开合成界面
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,amount,i,size,p, id;
        object who,*inv,item;
	string *nTmp,tmp;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_NEWBIE_03,13) && !who->get_legend(TASK_NEWBIE_03,14) )
        		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看你大老远的跑来不容易, 好吧!我可以答应你, 给你做这个盒子, 但是我这里没有合适的材料, 可能你得去找点木材来给我才行!\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_NEWBIE_03,14) && !who->get_legend(TASK_NEWBIE_03,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我已经答应了你, 给你做这个盒子, 但是我这里原材料不够, 据我估算, 做这个盒子需要20块木头, 你去收集20块木头来, 听说首阳山的地痞家就有!\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_NEWBIE_03,15) && !who->get_legend(TASK_NEWBIE_03,16) )
        		me->do_welcome(4);
        	else if ( who->get_legend(TASK_NEWBIE_03,16) && !who->get_legend(TASK_NEWBIE_03,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这些木头需要用刨子刨光才能用, 可凑巧的是刨子被人偷了, 你再给我找把刨子来, 我就开始做这个木盒!据说是楚方城的那帮刀兵和剑兵偷走了我的刨子.\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_NEWBIE_03,17) && !who->get_legend(TASK_NEWBIE_03,18)  )
			me->do_welcome(7);
		else if ( who->get_legend(TASK_NEWBIE_03,18) && !who->get_legend(TASK_NEWBIE_03,19)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    可能那齐国商人猗顿正急着等你回去把盒子交给他呢, 你快去吧!\n"ESC"离开", me->get_name()));

        	break;
        case 2:
        	if ( who->get_legend(TASK_NEWBIE_03,13) && !who->get_legend(TASK_NEWBIE_03,14) )
        	{
			who->add_exp(600);
			who->add_potential(10);
			who->add_cash(1000);
			TASK_LEGEND_D->task_finish(who);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_03,14);
			send_user(who,"%c%s",';',"买椟还珠 经验 600 潜能 10 金钱 1000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,8,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3 :
        	if ( who->get_legend(TASK_NEWBIE_03,14) && !who->get_legend(TASK_NEWBIE_03,15) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_NEWBIE_03,15);
        		who->delete_save_2("gongsumutou");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"周国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,4,"买椟还珠(3)" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"买椟还珠(3)");
        	}
        	break;
         case 4 :
        	if ( who->get_legend(TASK_NEWBIE_03,15) && !who->get_legend(TASK_NEWBIE_03,16) )
        	{
        		if ( who->get_save_2("gongsumutou") < 20 )
        			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有足够的木头可做不好盒子哦……\n"ESC"离开", me->get_name()));
        		else
        			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯, 年轻人, 不错不错, 这么快的速度就收集到了20块木头, 这些木头需要用斧子劈碎才能用, 可凑巧的是刨子被人偷了, 你再给我找把刨子来, 我就开始做这个木盒!\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));

        	}
        	break;
	case 5:
		if ( !who->get_legend(TASK_NEWBIE_03,15) || who->get_legend(TASK_NEWBIE_03,16) || who->get_save_2("gongsumutou") < 20 )
			return ;
		if ( TASK_LEGEND_D->check_task_item(who,"木头",20) != 1)
			return;
		TASK_LEGEND_D->give_item(who,"/item/91/9110",3);
		who->add_exp(650);
		who->add_potential(50);
		who->add_cash(1000);
		TASK_LEGEND_D->task_finish(who);
		who->set_legend(TASK_NEWBIE_03,16);
		who->delete_save_2("gongsumutou");
		send_user(who,"%c%s",';',"买椟还珠 经验 650 潜能 50 金钱 1000 正气散 3");
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,4,"" );
		me->do_welcome(1);
		break;
	case 6:
        	if ( who->get_legend(TASK_NEWBIE_03,16) && !who->get_legend(TASK_NEWBIE_03,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_NEWBIE_03,17);
        		who->delete_save_2("gongsupaozi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"周国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,5,"买椟还珠(4)" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"买椟还珠(4)");
        	}
		break;
	case 7:
		if ( !who->get_legend(TASK_NEWBIE_03,17) || who->get_legend(TASK_NEWBIE_03,18)  )
			return ;
		if ( who->get_save_2("gongsupaozi") )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你替我找到了这个刨子, 年轻人, 其实我只是在考验你的耐心, 现在我把做好了的木盒交给你, 你可以拿去交给齐国商人猗顿了, 他一定会好好的奖赏你的!\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    光有木头没有刨子, 不能做出好的盒子呀!\n"ESC"离开", me->get_name()));
		break;
	case 8:
		if ( !who->get_legend(TASK_NEWBIE_03,17) || who->get_legend(TASK_NEWBIE_03,18) ||  !who->get_save_2("gongsupaozi") )
			return ;
		if( !objectp( item = present("刨子", who, 1, MAX_CARRY) ) || item->is_legend_item() != 1 )
		{
			send_user(who,"%c%s",'!',"你的刨子呢?");
			return;
		}
		item->remove_from_user();
		destruct(item);
		TASK_LEGEND_D->give_item(who,"/item/98/0006",1);
		who->add_exp(800);
		who->add_potential(30);
		who->add_cash(1500);
		TASK_LEGEND_D->task_finish(who);
		who->set_legend(TASK_NEWBIE_03,18);
		who->delete_save_2("gongsupaozi");
		send_user(who,"%c%s",';',"买椟还珠 经验 800 潜能 30 金钱 1500 木盒 1");
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,6,"买椟还珠(5)" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,5,"" );
		send_user( who, "%c%s", '!', "得到任务 "HIY"买椟还珠(5)");
		break;
        case 9:
        	if ( who->get_legend(TASK_28,12) && !who->get_legend(TASK_28,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我从未试过打造钥匙, 但是我想如果这木箱如此宝贵, 那么他所需要的钥匙也是与众不同的, 或许是用木头做的.\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_28,13) && !who->get_legend(TASK_28,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这个锁的难度要求太高了, 我从这个锁孔的拓印来看, 似乎需要一种非常坚韧同时又能做小幅度弯曲的钥匙, 而世间能够做到这个要求的唯有华樟木, 而这种木头一向是王室显贵的收藏之物, 鲜有愿意示之人前的, 幸好老夫有个忘年之交, 唤作熊平, 为人十分豪爽, 当初老夫也为他打造过不少东西, 他曾言老夫但有所需, 府中原料任我取用, 其中恰巧就有这种特殊的木块原料, 华樟木, 你只需带了我的手信, 向他要来一小块木块就好了, 他是会爽快的给你的.不过他这人有个怪脾气, 喜欢找人比武, 所以你要当心他如果觉得你的武艺可以同他一搏的话, 他可不管你愿不愿意, 就要同你较量的.他就在晋阳, 你去打听就很容易找到他了.\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_28,14) && !who->get_legend(TASK_28,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这把钥匙必须要木质很好的钥匙才能做, 如果你找不来这种木块, 那我也无能为力.\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_28,15) && !who->get_legend(TASK_28,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这个木块, 我需要很长的时间来做, 所以, 这把钥匙我自会派人送去给守卫的, 你可以先休息了.\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 10:
        	if ( who->get_legend(TASK_28,12) && !who->get_legend(TASK_28,13) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,13);
			who->add_exp(24000);
			who->add_potential(435);
			who->add_cash(22500);
			send_user(who,"%c%s",';',"木箱的秘密（3） 经验 24000 潜能 435 金钱 22500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,49,"" );
        		me->do_welcome(9);
        	}
        	break;
	case 11:
        	if ( who->get_legend(TASK_28,13) && !who->get_legend(TASK_28,14) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,14);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"周国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,7,"木箱的秘密（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"木箱的秘密（4）");
        	}
        	break;
        case 12:
        	if ( who->get_legend(TASK_28,15) && !who->get_legend(TASK_28,16) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),80,BOOTS_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"特殊的木块",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,16);
			who->add_exp(120000);
			who->add_potential(1500);
			who->add_cash(110000);
			send_user(who,"%c%s",';',sprintf("木箱的秘密（4） 经验 120000 潜能 1500 金钱 110000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,7,"" );
        		me->do_welcome(9);
        	}
        	break;
        case 13:
       	        if ( who->get_legend(TASK_40,1) && !who->get_legend(TASK_40,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    修理这个小木桶很简单, 关键是需要一些材料, 可能需要你帮我找来.\n"ESC"完成任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
       	        else if ( who->get_legend(TASK_40,2) && !who->get_legend(TASK_39,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唔, 这个小木桶要想恢复原状不太可能了, 现在那里找成色质地都一样的红木啊, 就算找到也太过昂贵, 看来只有用普通的代替了, 断了一根桶板, 咬合也松动了, 这样吧, 我需要1只铁箍和5块木头, 你去虚陵洞给我找来吧.\n"ESC"接受任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
       	        else if ( who->get_legend(TASK_39,28) && !who->get_legend(TASK_39,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n   没有修理的材料, 我要怎么给你修理呢？\n"ESC"离开", me->get_name()));
       	        else if ( who->get_legend(TASK_39,29) && !who->get_legend(TASK_39,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好, 有了这些材料, 我很快就能修好了, 你过会儿来找我取这只木桶吧.\n"ESC"完成任务\ntalk %x# welcome.16\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_39,30) && !who->get_legend(TASK_40,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    小木桶修好了, 可是我觉得你一味帮助他但是他却毫无悔过的意识, 这样并不能让他的人际关系得到改善, 不如你将木桶交给他, 然后由他自己归还给借他木桶的那人, 我想, 这样会好点吧.\n"ESC"接受任务\ntalk %x# welcome.17\n"ESC"离开", me->get_name(),getoid(me)));

		break;
        case 14:
        	if  ( who->get_legend(TASK_40,1) && !who->get_legend(TASK_40,2) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"小木桶",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,2);
			who->add_exp(36000);
			who->add_potential(600);
			who->add_cash(35000);
			send_user(who,"%c%s",';',"四面楚歌（3） 经验 36000 潜能 600 金钱 35000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,63,"" );
        		me->do_welcome(13);
        	}
        	break;
	case 15:
        	if ( who->get_legend(TASK_40,2) && !who->get_legend(TASK_39,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_39,28);
        		who->delete_save("gsbtieku");
        		who->delete_save("gsbmutou");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"周国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,8,"四面楚歌（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"四面楚歌（4）");
        	}
        	break;
        case 16:
        	if ( who->get_legend(TASK_39,29) && !who->get_legend(TASK_39,30) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"铁箍",1) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"修理的木头",5) != 1 )
        		{
    				TASK_LEGEND_D->give_item(who,"item/98/0191",1);
        			return;
        		}
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_39,30);
        		who->delete_save("gsbtieku");
        		who->delete_save("gsbmutou");
			who->add_exp(37000);
			who->add_potential(640);
			who->add_cash(38000);
			send_user(who,"%c%s",';',"四面楚歌（4） 经验 37000 潜能 640 金钱 38000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,8,"" );
			me->do_welcome(13);
        	}
        	break;
        case 17:
        	if ( who->get_legend(TASK_39,30) && !who->get_legend(TASK_40,3) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0193",1);
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_40,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"周国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,9,"四面楚歌（5）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"四面楚歌（5）");
        	}
        	break;
        case 18:
		if ( who->get_legend(TASK_2_00,23) && !who->get_legend(TASK_2_00,24) && who->get_save("baifang_ms_2") != 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王叫你来拜访我吗？你可以看看现在和将来在我这会有什么需要的, 呵呵.年轻人, 有朝气, 真好啊.\n", me->get_name()));
			who->set_save("baifang_ms_2",1);
			USER_TASK_D->send_task_intro(who,2,TID_ZHOUGUO,21);
		}
		if ( who->get_save("baifang_ms_1") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_3") == 1 && who->get_save("baifang_ms_4") == 1 && who->get_save("baifang_ms_5") == 1 )
		{
			who->set_legend(TASK_2_00,24);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,21,"访问周国名士(完成)" );
		}
        	break;
        case 19:
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_2_01,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    壮士, 我家传木工技艺忝教世人尊为当世之首, 也曾制木牛流马以机关使死物行动, 可我听说秦王所建陵寝中有可飞天畅舞之机关金雁, 心甚羡之.听说那些机关密图分为3部存于陵寝之中, 你能否替我去寻找一番, 事成之后, 我必有重谢.\n"ESC"接受任务\ntalk %x# welcome.20\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_2_01,4) && !who->get_legend(TASK_2_01,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    壮士可曾前去寻觅机关密图了？\n"ESC"离开", me->get_name(),));
		else if ( who->get_legend(TASK_2_01,5) && !who->get_legend(TASK_2_01,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    感谢这位壮士, 我已经看过那些密图了, 确实精巧, 但不过似乎是以讹传讹, “金银为凫雁”传为机关金雁可飞天舞地了.\n"ESC"完成任务\ntalk %x# welcome.21\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 20:
        	if ( who->get_level() >= 65 && !who->get_legend(TASK_2_01,4) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_2_01,4);
			who->delete_save("fb_gsb_jgtsb");
			who->delete_save("fb_gsb_jgtzb");
			who->delete_save("fb_gsb_jgtxb");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"周国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,103,"机关密图" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"机关密图");
		}
        	break;
        case 21:
        	if ( who->get_legend(TASK_2_01,5) && !who->get_legend(TASK_2_01,6) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"机关密图上部",1) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"机关密图中部",1) != 1 )
        		{
				TASK_LEGEND_D->give_item(who,"item/98/0241",1);
        			return;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"机关密图下部",1) != 1 )
        		{
				TASK_LEGEND_D->give_item(who,"item/98/0241",1);
				TASK_LEGEND_D->give_item(who,"item/98/0242",1);
        			return;
        		}
        		TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_2_01,6);
			who->delete_save("fb_gsb_jgtsb");
			who->delete_save("fb_gsb_jgtzb");
			who->delete_save("fb_gsb_jgtxb");
			who->add_exp(16800);
			who->add_potential(650);
			who->add_cash(16800);
			send_user(who,"%c%s",';',"机关密图 经验 16800 潜能 650 金钱 16800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,103,"" );
        	}
        	break;
        case 50:
        	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
        		sprintf("%s:\n    你希望了解些什么？\n"
        		ESC"晶石是什么？\ntalk %x# welcome.51\n"
        		ESC"如何合成晶石？\ntalk %x# welcome.52\n"
        		ESC"如何精炼装备？\ntalk %x# welcome.53\n"
        		ESC"没什么.", me->get_name(),id, id, id));
        	break;
        case 51:
        	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
        		sprintf("%s:\n    在周国天坛的神秘商人那里就能买到最初级的晶石.晶石的种类一共有10种, 不同的晶石拥有不同的属性.只要你带着晶石过来, 我便可以助你强化手中的装备或武器.\n"
        		ESC"谢谢, 我知道了.", me->get_name()));
        	break;
        case 52:
        	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
        		sprintf("%s:\n    你只要带着种类与等级都相同的晶石过来, 我便可以帮你将低级的晶石合成更高级的晶石.合成的晶石必须两个为一组进行合成, 两个1级的晶石便可以合成出一个2级的晶石, 两个2级的晶石便可以合成一个3级的晶石, 依此类推.\n    晶石合成的最高等级为10级.当然, 以老夫的本事, 只要材料和体力充足, 合成高级的晶石绝对没有任何问题.\n    不过在合成的过程中, 仅仅靠老夫一人还有所不足, 因此需要小兄弟/姑娘协助.这可是个体力活, 每合成一个晶石可要消耗5点体力的.\n"
        		ESC"谢谢, 我知道了.", me->get_name()));
        	break;
        case 53:
        	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
        		sprintf("%s:\n    只要有相对应的晶石, 无论任何装备都能进行精炼.\n    比如说一件精炼度已经“＋3”的装备, 要继续精炼的话, 就必须将该装备与一个4级的晶石进行合成, 如果成功了, 装备的精炼度便会提升到“＋4”.至于要合成那个种类的晶石并不会有什么限制, 只要那个晶石符合装备的属性便可以了.\n    当然, 随着装备精炼等级越来越高, 就算以老夫天大的本事也难以担保能百分百合精炼成功.\n"
        		ESC"谢谢, 我知道了.", me->get_name()));
        	break;
        case 60:
        	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
        		sprintf("%s:\n    Ngươi có thể dùng lệnh "HIR "(Alt+G)"NOR " đem Đoạn Thạch giao cho ta để Phân giải. Căn cứ vào cấp bật của Đoạn Thạch sẽ phân giải ra 2 Đoạn Thạch cấp thấp hơn.Đương nhiên Đoạn Thạch cấp thấp không thể tái phân giải !\n"
        		ESC"离开", me->get_name()));
        	break;
		case 70:
        	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
        		sprintf("%s:\n    Ngươi muốn Hợp Thành Đoạn Thạch phải không ???? \nTrung Cấp Đoạn Thạch : cần 2 Sơ Cấp Đoạn Thạch \nCao Cấp Đoạn Thạch : cần 2 Trung Cấp Đoạn Thạch.\n"
        		ESC"Hợp thành lên Trung Cấp Đoạn Thạch\ntalk %x# welcome.71\n"
        		ESC"Hợp thành lên Cao Cấp Đoạn Thạch\ntalk %x# welcome.72\n"
        	//	ESC"Hợp thành Cao Cấp Đoạn Thạch Kết Dính\ntalk %x# welcome.73\n"
        		ESC"Rời khỏi", me->get_name(),id, id, id));
        	break;	
		case 71:
			if ( TASK_LEGEND_D->check_task_item_amount(who,"Sơ Cấp Đoạn Thạch") < 2 )
			{
				notify( "Ngươi không có 2 Sơ Cấp Đoạn Thạch" );
				return ;	
			}
			TASK_LEGEND_D->check_task_item1(who,"Sơ Cấp Đoạn Thạch",2);
			item = new("item/sell/1032");
			p = item->move2(who);
			item->add_to_user(p);
			send_user(who,"%c%s",';',"Bạn nhận được "HIY+item->get_name());
        	break;
		case 72:
			if ( TASK_LEGEND_D->check_task_item_amount(who,"Trung Cấp Đoạn Thạch") < 2 )
			{
				notify( "Ngươi không có 2 Trung Cấp Đoạn Thạch" );
				return ;	
			}
			TASK_LEGEND_D->check_task_item1(who,"Trung Cấp Đoạn Thạch",2);
			item = new("item/sell/2032");
			p = item->move2(who);
			item->add_to_user(p);
			send_user(who,"%c%s",';',"Bạn nhận được "HIY+item->get_name());
        	break;	
        }
}

// 函数:接受物品
int accept_object( object who, object item ){ return __FILE__ ->accept_object_callout( this_object(), who, item ); }

// 函数:接受物品(在线更新)
int accept_object_callout( object me, object who, object item )
{
        int level, p;
	object item2;
        me->to_front_eachother(who);
	if (item->get_real_name()!="Đoạn Thạch") return 0;
	level = item->get_level();
	if (level<=1)
	{
        	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
        		sprintf("%s:\n    Sơ Cấp Đoạn Thạch không thể phân giải\n"
        		ESC"Rời khỏi", me->get_name()));
		return 0;
	}
	if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY )
	{
		send_user( who, "%c%c%w%s", ':', 3, who->get_char_picid(),
			who->get_name()+":\n    Hãy chừa ít nhất 1 ô trống trong Hành trang 1\n"
			ESC"Rời khỏi" );
		return 0;
	}
	level --;
	item->set_level(level);
	send_user( who, "%c%d%c", 0x31, getoid(item), 0 );
	item2 = new ("/item/sell/0032");
	item2->set_level(level);
	if( p = item2->move(who, -1) )
	{
		item2->add_to_user(p);
	}
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		sprintf(me->get_name()+":\n    Ngươi đạt được 2 cái %d cấp Đoạn Thạch.\n"
		ESC"Rời khỏi", level) );
	return -99;
}
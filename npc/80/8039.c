
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;
string *TalkTable = ({ 
        "Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
        "Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
        "Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình sảng khói, thật là một hảo hán !",
});
void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5302; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tần Quản Gia");
        set_city_name("Tần Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
//        set("level",62);
//        set("legend",({32*18+28}));
 	set("mpLegend",([60:({32*18+28}),115:({32*46+1,32*46+26}),]));
 	set("mpLegend2",([0:({32*20+20,32*37+30,}),115:({32*39+10,32*46+12,}),]));        
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, this_object() ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, this_object() ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( (who->get_level() >=60 && !who->get_legend(TASK_18,28)) || ( ( who->get_legend(TASK_18,28) && !who->get_legend(TASK_18,29) ) ) )
		tmp += sprintf(ESC HIY "贺礼\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_20,19) && !who->get_legend(TASK_20,20) )
	{
		tmp += sprintf(ESC HIY "探听虚实\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( (who->get_legend(TASK_20,20) && !who->get_legend(TASK_20,21)) || (who->get_legend(TASK_20,21) && !who->get_legend(TASK_20,23)))
	{
		tmp += sprintf(ESC HIY "宫殿图纸\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( who->get_level() >=40 && who->get_legend(TASK_37,29) && !who->get_legend(TASK_37,30) )
		tmp += sprintf(ESC HIY "交换心得\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_level() >=115 && who->get_legend(TASK_39,9) && !who->get_legend(TASK_39,10) )
		tmp += sprintf(ESC HIY "心愿\ntalk %x# welcome.8\n",getoid(me));
	if ( who->get_level() >=115 && !who->get_legend(TASK_46,1) )
		tmp += sprintf(ESC HIY "确认传说\ntalk %x# welcome.10\n",getoid(me));
        if ( who->get_legend(TASK_46,11)&&!who->get_legend(TASK_46,12) ) 
		tmp += sprintf(ESC HIY "危险解除\ntalk %x# welcome.10\n",getoid(this_object())); 
	if ( who->get_level() >=115 && !who->get_legend(TASK_46,26) )
		tmp += sprintf(ESC HIY "拜访之路\ntalk %x# welcome.13\n",getoid(me));

	send_user(who,"%c%s",':',sprintf( "%s：\n    %s\n", get_name(), TalkTable[ random(sizeof(TalkTable))] ) 
			+ tmp +
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
        int flag,p;
        object who,item,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >=60 && !who->get_legend(TASK_18,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿嘿，赵总管的老爹果然强人啊，居然老来得子，你最近去赵吗，如果顺路帮我将这份贺礼送给赵总管，赵少公子居然能在老爹80大寿光荣降生，将来必定前途不可限量啊，要不是老朽无暇分身，定会亲往祝贺访谈一番的。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_18,28) && !who->get_legend(TASK_18,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    快去吧，别在路上贪玩，尽早给我把贺礼送到！\n"ESC"离开", me->get_name()));
			
        	break;
        case 2:
        	if ( who->get_level() >=60 && !who->get_legend(TASK_18,28) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0082");
        		if ( !item )
        			return ;
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			send_user(who,"%c%s",'!', "你携带的物品太多了");	
        			destruct(item);
        			return;
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_18,28);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,9,"贺礼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"贺礼");
       		}
        	break;
        case 3:
        	if ( who->get_legend(TASK_20,19) && !who->get_legend(TASK_20,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王是打算修缮冀阙宫，（秦管家好像很生气的样子）但是这也不是什么好事，给犬戎之人住的，哼，你叫那些工匠做好准备吧，大王要你们“好好的”修！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_20,20) && !who->get_legend(TASK_20,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    冀阙宫的原始图纸遗失在了秦长城匝道附近，你前去将那宫殿图纸找到并交给Tần Quốc工匠。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_20,21) && !who->get_legend(TASK_20,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    找到宫殿图纸了吗？\n"ESC"离开", me->get_name()));

        	break;
        case 4:
        	if ( who->get_legend(TASK_20,19) && !who->get_legend(TASK_20,20) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_20,20);
			who->add_exp(11000);
			who->add_potential(320);
			who->add_cash(9000);
			send_user(who,"%c%s",';',"探听虚实 经验 11000 潜能 320 金钱 9000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,23,"" );
			me->do_welcome(3);
        	}
        	break; 
	case 5:
        	if ( who->get_legend(TASK_20,20) && !who->get_legend(TASK_20,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,24,"宫殿图纸" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"宫殿图纸");
        	}
        	break;        
	case 6:
		if ( who->get_level() >=40 && who->get_legend(TASK_37,29) && !who->get_legend(TASK_37,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    齐总管谦虚了，其实我也听闻齐总管管理有方，正想前去讨教呢，没想到他派你先来了，这样吧，我会和齐总管约个时间细谈，交换下心得，麻烦你了，这么远过来！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
			
		break;
	case 7:
		if ( who->get_level() >=40 && who->get_legend(TASK_37,29) && !who->get_legend(TASK_37,30) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_37,30);
			who->add_exp(3000);
			who->add_potential(70);
			who->add_cash(2500);
			send_user(who,"%c%s",';',"交换心得 经验 3000 潜能 70 金钱 2500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,73,"" );
        	}
        	break;
	case 8:
		if ( who->get_level() >=115 && who->get_legend(TASK_39,9) && !who->get_legend(TASK_39,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没想到还有人如此的崇拜我，我帮他完成这个心愿吧！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
			
		break;
	case 9:
		if ( who->get_level() >=115 && who->get_legend(TASK_39,9) && !who->get_legend(TASK_39,10) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_39,10);
			who->add_exp(52000);
			who->add_potential(620);
			who->add_cash(48000);
			send_user(who,"%c%s",';',"心愿 经验 52000 潜能 620 金钱 48000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,67,"" );
        	}
        	break;
        case 10:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_46,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近手下报告，诛仙阵中的刀魂竟然能够在每月十日挣脱阵法束缚在城外平阳镇大肆杀戮，每月都有不少青壮年被其杀死，每次死时表情都甚为奇怪，仿佛安详的睡去，脸上挂着诡异的笑容，如今那个镇子人人自危，迁移的人越来越多，已经成为谈平阳色变的地步，我怀疑有什么邪门歪道利用刀魂汲取生魂做一些什么邪恶之事，甚或可能有关大秦命脉，你生为大秦义士断不会任此等邪魂任意妄为，残害百姓吧，我命你速速前去探察一番，听说秦老汉居住日久，博闻广识，你向他先问问看。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,11)&&!who->get_legend(TASK_46,12) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    天佑我大秦，看来没有什么人在做威胁我们Quốc运的大事了，仅仅是个小混混弄出的意外而已，壮士你此番也辛苦了，至于一直殚精竭虑的马显先生你也代我送一件礼物给他。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 11:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_46,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_46,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,64,"刀魂传说1" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"刀魂传说1");
       		}
        	break;
        case 12:
        	if( who->get_legend(TASK_46,11)&&!who->get_legend(TASK_46,12) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/64181",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,12);
			who->add_exp(92000);
			who->add_potential(1100);
			who->add_cash(93000);
			send_user(who,"%c%s",';',"刀魂传说5 经验 92000 潜能 1100 金钱 93000 祁龙鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,68,"" );
        	}
        	break;
        case 13:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_46,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    秦药师为吾王炼制仙丹，听说遇到一些麻烦，他请求我派人给予援助，不知道壮士你可愿意前往?\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
//		else if ( who->get_legend(TASK_46,11)&&!who->get_legend(TASK_46,12) ) 
//			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这可真是件好事。\n"ESC"完成任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 14:
        	if ( who->get_level() >=115 && !who->get_legend(TASK_46,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_46,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,74,"炼药之路1" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"炼药之路1");
       		}
        	break;
        }
}
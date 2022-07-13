
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5601; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Trình Phong");
        set_city_name("Yên Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ])); 
//	set("level",47);
//	set("legend",({32*12+13}));
	set("mpLegend",([45:({32*12+13}),50:({32*15+18})]));
	set("mpLegend2",([0:({32*10+7,32*31+17,32*31+20,32*31+23,32*31+26,}),45:({32*12+15,}),50:({32*15+20})]));
        setup();
}

void do_look( object who )
{
	object me = this_object();
	string tmp="";
	
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( who->get_legend(TASK_10,6) && !who->get_legend(TASK_10,7) )
		tmp += sprintf(ESC HIY "王凯的口信\ntalk %x# welcome.1\n",getoid(me));
	if ( ( who->get_level() >= 45 && !who->get_legend(TASK_12,13) ) || ( who->get_legend(TASK_12,13) && !who->get_legend(TASK_12,15) ) )
		tmp += sprintf(ESC HIY "程风的烦恼\ntalk %x# welcome.1\n",getoid(me));
	if ( ( who->get_level() >= 50 && !who->get_legend(TASK_15,18) ) || ( who->get_legend(TASK_15,18) && !who->get_legend(TASK_15,20) ) )
		tmp += sprintf(ESC HIY "爱吃辣的客人\ntalk %x# welcome.5\n",getoid(me));
	if ( who->get_legend(TASK_31,16) && !who->get_legend(TASK_31,17) )
		tmp += sprintf(ESC HIY "无人知晓的秘密\ntalk %x# welcome.8\n",getoid(me));
	if ( (who->get_legend(TASK_31,17) && !who->get_legend(TASK_31,18)) || (who->get_legend(TASK_31,18) && !who->get_legend(TASK_31,20)) )
		tmp += sprintf(ESC HIY "妖魔鬼怪\ntalk %x# welcome.8\n",getoid(me));
	if ( (who->get_legend(TASK_31,20) && !who->get_legend(TASK_31,21)) || (who->get_legend(TASK_31,21) && !who->get_legend(TASK_31,23)) )
		tmp += sprintf(ESC HIY "骷髅妖王\ntalk %x# welcome.8\n",getoid(me));
	if ( (who->get_legend(TASK_31,23) && !who->get_legend(TASK_31,24)) || (who->get_legend(TASK_31,24) && !who->get_legend(TASK_31,26)) )
		tmp += sprintf(ESC HIY "摄魂铃铛\ntalk %x# welcome.8\n",getoid(me));
			
	send_user(who,"%c%s",':',sprintf( "%s：\n    周Quốc的京都镖局尉迟老镖头武艺高强，生性豪爽，真是一条好汉！\n", get_name(),  ) 
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
        string cmd1,*nTmp,tmp;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_10,6) && !who->get_legend(TASK_10,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原来王凯住在碣石镇，这几天可把我找惨了，我这就尽快给他送过去，这位%s，多谢，咱们后会有期。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	else if ( who->get_level() >= 45 && !who->get_legend(TASK_12,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前天，我经过郑Quốc渠的时候不小心把家传宝物玲珑玉遗失在那里，你能帮我将他寻回吗？\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_12,13) && !who->get_legend(TASK_12,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下怎么向家里人交代啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_12,14) && !who->get_legend(TASK_12,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    多谢%s！帮了我一个大忙。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        		
        	break;
        case 2:
        	if( who->get_legend(TASK_10,6) && !who->get_legend(TASK_10,7) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/61004",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_10,7);
			who->add_exp(3500);
			who->add_potential(90);
			who->add_cash(2500);
			send_user(who,"%c%s",';',"带话给程风（2） 经验 3500 潜能 90 金钱 2500 小米粥图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,10,"" );
        	}
        	break;
	case 3:
        	if( who->get_level() >=45 && !who->get_legend(TASK_12,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_12,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,5,"程风的烦恼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"程风的烦恼");
        	}
        	break;       
        case 4:
        	if ( who->get_legend(TASK_12,14) && !who->get_legend(TASK_12,15) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"玲珑玉",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_12,15);
			who->add_exp(4800);
			who->add_potential(170);
			who->add_cash(4200);
			send_user(who,"%c%s",';',"程风的烦恼 经验 4800 潜能 170 金钱 4200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,5,"" );
        	}
        	break;   
	case 5:
        	if ( who->get_level() >=50 && !who->get_legend(TASK_15,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近家里来了几位爱吃辣椒的客人，每道菜里都要放辣椒，可是我们这辣椒吃得少，所以辣椒经常不够，你去燕长城给我找找，看能不能找到20个辣椒。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_15,18) && !who->get_legend(TASK_15,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果一顿饭不给他们放辣椒，估计他们马上就走了，一个人在家很无聊，实在是不想他们这么早走啊。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_15,19) && !who->get_legend(TASK_15,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    他们很久没有来我家了，凭这点辣椒我就能把他们留下来了，嘿嘿。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 6:
        	if( who->get_level() >=50 && !who->get_legend(TASK_15,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_15,18);
        		who->delete_save_2("cflajiao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,34,"爱吃辣的客人" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"爱吃辣的客人");
        	}
        	break;       
        case 7:
        	if ( who->get_legend(TASK_15,19) && !who->get_legend(TASK_15,20) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"辣椒",20) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_15,20);
        		who->delete_save_2("cflajiao");
			who->add_exp(6300);
			who->add_potential(252);
			who->add_cash(5300);
			send_user(who,"%c%s",';',"爱吃辣的客人 经验 6300 潜能 252 金钱 5300");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,34,"" );
        	}
        	break;  
	case 8:
        	if ( who->get_legend(TASK_31,16) && !who->get_legend(TASK_31,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我知道迟早会找上我的，没办法，这是当年我们共同保守的秘密，现在出了问题，还是得我们来承担。\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,17) && !who->get_legend(TASK_31,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这个秘密我们已经保守了很久，现在纸终于包不住火了。\n    五年前，我们去长白山狩猎，无意中看到一个祭坛，有个形容猥琐，衣衫破烂，状若疯癫的道人在那里念念有词，箕、咒水、咒笔、咒墨、画苻、焚香什么一通乱七八糟，猛可间地底裂开一个深不见底的大洞，一团黑雾从中冲霄而出，渐聚渐浓，黑雾中一些奇形怪状的影子渐渐成型，股股浓烈的妖气扑面而来，我俩没有胆量去破坏祭坛，就此溜了，如今想来时时如鲠在喉，最近老是听到有妖怪出没伤人的消息，我们作为唯一知情人，当然不能坐视不理。我们知道他们的老巢，但是自己能力不够，只得请壮士施以援手，请你前往困魔阵消灭骷髅妖五个与邪灵七个，拘来他们的邪气，回来我再告诉你怎么做。\n"ESC"接受任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,18) && !who->get_legend(TASK_31,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    或许我们造下的孽只能我们来承受，如果你实在是不能杀掉他们，那么你就放弃吧。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_31,19) && !who->get_legend(TASK_31,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，这些邪气拘来只能破除这群妖怪的法力增幅，还没能解决根本问题，\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,20) && !who->get_legend(TASK_31,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这个秘密我们已经保守了很久，现在纸终于包不住火了。\n    五年前，我们去长白山，见到有人开坛作法，偷听到他把所有的妖魔鬼怪都放了出来了，并且这个世界上只有摄魂铃铛才可以制服他们，他将摄魂铃铛放在困魔阵，为了不让人拿到后对付它们，那些妖怪死死的守着这个摄魂铃铛。我们为了不惹祸上身，就保守了这个秘密。\n    最近老是听到有妖怪出没伤人的消息，我们作为唯一知情人，当然不能坐视不理，所以请你去困魔阵1层消灭骷髅妖王，然后回来我这里吧。\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,21) && !who->get_legend(TASK_31,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道竟然无法遏制他们了么，如此人间大乱，为了我们当初的懦弱，我等只有一死谢天下了。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_31,22) && !who->get_legend(TASK_31,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    能真正解决这个问题，可能只有拿到摄魂铃铛了。\n"ESC"完成任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,23) && !who->get_legend(TASK_31,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在就是重新封印这些妖怪的关键了，困魔阵中的摄魂铃铛既是这些妖怪作祟的力量之源，也是克制他们的利器，摄魂铃铛在阵中的时候就能增幅他们的力量，抑制他们身上的封印，而到阵外，就成为重新抑制他们力量，加重封印的法器，你现在去魔神殿拿来摄魂铃铛，刚才看守铃铛的怪物已经被你杀掉了。\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_31,24) && !who->get_legend(TASK_31,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果没有摄魂铃铛，我还真不知这件事该怎么解决，你找来了吗？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_31,25) && !who->get_legend(TASK_31,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    拿到了这个摄魂铃铛，我再和程林开商量一下，这件事情谢谢你了！\n"ESC"完成任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 9:
        	if ( who->get_legend(TASK_31,16) && !who->get_legend(TASK_31,17) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,17);
			who->add_exp(30000);
			who->add_potential(600);
			who->add_cash(29000);
			send_user(who,"%c%s",';',"秘密（1） 经验 30000 潜能 600 金钱 29000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,36,"" );
        		me->do_welcome(8);
        	}
        	break;
        case 10:
        	if ( who->get_legend(TASK_31,17) && !who->get_legend(TASK_31,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,18);
        		who->delete_save("cfkuly");
        		who->delete_save("cfxieling");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,39,"秘密（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"秘密（2）");
        	}
        	break;  
        case 11:
        	if ( who->get_legend(TASK_31,19) && !who->get_legend(TASK_31,20) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,20);
        		who->delete_save("cfkuly");
        		who->delete_save("cfxieling");
			who->add_exp(35000);
			who->add_potential(620);
			who->add_cash(32000);
			send_user(who,"%c%s",';',"秘密（2） 经验 35000 潜能 620 金钱 32000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,39,"" );
        		me->do_welcome(8);
        	}
        	break;  
        case 12:
        	if ( who->get_legend(TASK_31,20) && !who->get_legend(TASK_31,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,40,"秘密（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"秘密（3）");
        	}
        	break;  
        case 13:
        	if ( who->get_legend(TASK_31,22) && !who->get_legend(TASK_31,23) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/64160",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,23);
			who->add_exp(40000);
			who->add_potential(650);
			who->add_cash(37000);
			send_user(who,"%c%s",';',"秘密（3） 经验 40000 潜能 650 金钱 37000 玄云靴图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,40,"" );
        		me->do_welcome(8);
        	}
        	break;  
        case 14:
        	if ( who->get_legend(TASK_31,23) && !who->get_legend(TASK_31,24) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_31,24);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,41,"秘密（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"秘密（4）");
        	}
        	break;  
        case 15:
        	if ( who->get_legend(TASK_31,24) && !who->get_legend(TASK_31,26) )
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),90,WAIST_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"摄魂铃铛",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_31,26);
			who->add_exp(150000);
			who->add_potential(1800);
			who->add_cash(140000);
			send_user(who,"%c%s",';',sprintf("秘密（4） 经验 150000 潜能 1800 金钱 140000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,41,"" );
        	}
        	break; 
        }
}
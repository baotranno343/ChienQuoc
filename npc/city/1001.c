
// 自动生成：/make/npc/make8001

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define EMPEROR_D       "/inh/city/emperor"
#define EMPEROR_2_D     "/inh/city/emperor2"

inherit OFFICER;

void do_policy( string arg );
void do_relation( string arg );
void do_master( string arg );
void do_advice( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5101; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tề Vương");
	set_real_name("Điền Kiến");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "policy"        : (: do_policy :),
                "relation"      : (: do_relation :),
                "master"        : (: do_master :),
                "advice"        : (: do_advice :),
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",37);
//        set("legend",({32*13+16}));
 	set("mpLegend",([35:({32*13+16}),70:({32*24+7}),100:({32*36+26}),110:({32*45+7})]));
 	set("mpLegend2",([35:({32*13+18,32*13+21,}),70:({32*24+16,32*24+30,32*36+2,32*36+5,}),110:({32*45+9,32*45+12,}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 35 && !who->get_legend(TASK_13,16)) || ( who->get_legend(TASK_13,16) && !who->get_legend(TASK_13,18) ) )
	{
		tmp = sprintf(ESC HIY "Giang Tế Sơn Nhung Quốc\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_13,18) && !who->get_legend(TASK_13,19)) || ( who->get_legend(TASK_13,19) && !who->get_legend(TASK_13,21) ) )
	{
		tmp += sprintf(ESC HIY "孤竹族使节\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_legend(TASK_13,21) && !who->get_legend(TASK_10,1)) || ( who->get_legend(TASK_10,1) && !who->get_legend(TASK_10,2) ) )
	{
		tmp += sprintf(ESC HIY "带信给管仲\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >= 70 && !who->get_legend(TASK_24,7)) || (who->get_legend(TASK_24,15) && !who->get_legend(TASK_24,16)) )
	{
		tmp += sprintf(ESC HIY "Trà hoa nhài\ntalk %x# welcome.7\n",getoid(me));
	}
	if ( who->get_legend(TASK_24,29) && !who->get_legend(TASK_24,30) )
		tmp += sprintf(ESC HIY "禀告齐王\ntalk %x# welcome.10\n",getoid(me));
	if ( who->get_legend(TASK_36,1) && !who->get_legend(TASK_36,2) )
		tmp += sprintf(ESC HIY "完美宝石\ntalk %x# welcome.12\n",getoid(me));
	if ( (who->get_legend(TASK_36,2) && !who->get_legend(TASK_36,3)) || (who->get_legend(TASK_36,3) && !who->get_legend(TASK_36,5)) )
		tmp += sprintf(ESC HIY "收集晶石\ntalk %x# welcome.12\n",getoid(me));
	if ( who->get_legend(TASK_36,5) && !who->get_legend(TASK_36,6) )
		tmp += sprintf(ESC HIY "炼药\ntalk %x# welcome.12\n",getoid(me));
	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,26) )
		tmp += sprintf(ESC HIY "Đại Tề Khởi Nghĩa\ntalk %x# welcome.17\n",getoid(me));
	if ( me->get_city_name() == who->get_city_name() )
	{
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			tmp += sprintf(ESC HIY "Chế Tạo Tù Và Đế Vương\ntalk %x# welcome.19\n",getoid(me));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			tmp += sprintf(ESC HIY "王之号角的雕琢\ntalk %x# welcome.19\n",getoid(me));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16)&& gone_time(who->get_save("wangzhhj"))>=86400 )
			tmp += sprintf(ESC HIY "索取王之号角\ntalk %x# welcome.19\n",getoid(me));
	}
	if ( (who->get_level() >= 110 && !who->get_legend(TASK_45,7)) || (who->get_legend(TASK_45,7) && !who->get_legend(TASK_45,9)) )
	{
		tmp += sprintf(ESC HIY "Bắt Cướp\ntalk %x# welcome.23\n",getoid(me));
	}
	if ( (who->get_legend(TASK_45,9) && !who->get_legend(TASK_45,10)) || (who->get_legend(TASK_45,10) && !who->get_legend(TASK_45,12)) )
	{
		tmp += sprintf(ESC HIY "文竹\ntalk %x# welcome.23\n",getoid(me));
	}
	if ( who->get_legend(TASK_45,12) && !who->get_legend(TASK_45,13) )
	{
		tmp += sprintf(ESC HIY "云雾茶叶\ntalk %x# welcome.23\n",getoid(me));
	}
	if ( who->get("master.type") != 69 && sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( " %s :\n "+"/quest/word"->get_country_word(me) + "\n"ESC"Đối thoại\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"Rời khỏi");
	else
		EMPEROR_D->do_look( who, this_object() ); 
	
}
void do_policy( string arg ) { EMPEROR_D->do_policy( this_player(), this_object(), arg ); }
void do_relation( string arg ) { EMPEROR_2_D->do_relation( this_player(), this_object(), arg ); }    // ## 2 ##
void do_master( string arg ) { EMPEROR_D->do_master( this_player(), this_object(), arg ); }

void do_advice( string arg ) { EMPEROR_D->do_advice( this_player(), this_object(), arg ); }

// 接收心爱物品
int accept_object( object player, object obj ) 
{
	object who = this_object();
	return TASK_MASTER_D->accept_object( who, player, obj ); 
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
        	if (who->get_level() >= 35 && !who->get_legend(TASK_13,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    燕国派人求救，说是有一个山戎族经常侵犯他们，虽然这山戎族疆土很小，但他们的战士每次出战都抱着视死如归的心态，所以他们的军队很强大，燕使者说他们与山戎族边疆的老百姓都民不聊生，所以希望我们能派兵援助他们。\n    据我们的探子回报，有一名奸细已混入齐国，藏身于白马庄内的东边角落里，你过了马踏湖，就能看到白马庄了，去吧，杀死他回来后，我会重重有赏！\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_13,16) && !who->get_legend(TASK_13,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在消灭这个奸细是当务之急，头等大事，你为什么还在拖延时间呢？尽快，知道吗？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_13,17) && !who->get_legend(TASK_13,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这个心头大患消灭了，寡人就可以放心带兵到燕国支援他们了，你可是大功臣啊！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if (who->get_legend(TASK_13,18) && !who->get_legend(TASK_13,19))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    虽然我们已经消灭了山戎族奸细，但是并没有解除他们给燕国带来的威胁，因为山戎人去了孤竹族请求援助，而孤竹族也派出了使节来商量此事，现在，孤竹族使节已进入齐国境内，正在太公府内稍做歇息。请帮助我除掉孤竹族使节这个心头大患！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if (who->get_legend(TASK_13,19) && !who->get_legend(TASK_13,20))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    若让孤竹族的使节安全到达山戎族，那么他们就狼狈为奸、串通一气了，燕国人民又得处于水深火热之中了！所以消灭孤竹族使节的事情你得尽快办好才是！\n"ESC"离开", me->get_name()));
        	else if (who->get_legend(TASK_13,20) && !who->get_legend(TASK_13,21))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好样的！既然你已经帮助我消灭了山戎族的奸细和孤竹族的使节，那么，这些赏金都是属于你的啦！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if  ( who->get_legend(TASK_13,21) && !who->get_legend(TASK_10,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    山戎族奸细和孤竹族使节都已被你消灭，你是我国的大功臣！\n    现在我的贤相管仲还在等待我的命令，请你找到管仲，说战事已停，叫他速速回国！\n    管仲就在水榭花都的入口那，从齐国的田公府可直接到水榭花都，你快去吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_10,1) && !who->get_legend(TASK_10,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你尽快去吧！可别让我的贤相管仲等久了，他就在水榭花都的入口处！\n"ESC"离开", me->get_name()));
        	break;
	case 2:
        	if ( who->get_legend(TASK_13,21) && !who->get_legend(TASK_10,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,8,"带信给管仲（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"带信给管仲（3）");
        	}
        	break;
	case 3:
        	if (who->get_level() >= 35 && !who->get_legend(TASK_13,16) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,16);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,6,"山戎族奸细（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"山戎族奸细（1）");
        	}
        	break;
        case 4:
        	if ( who->get_legend(TASK_13,17) && !who->get_legend(TASK_13,18) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,18);
			who->add_exp(3800);
			who->add_potential(120);
			who->add_cash(3500);
			send_user(who,"%c%s",';',"山戎族奸细（1） 经验 3800 潜能 120 金钱 3500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,6,"" );        		
			me->do_welcome(1);
        	}
        	break;
	case 5:
        	if (who->get_legend(TASK_13,18) && !who->get_legend(TASK_13,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,7,"孤竹族使节（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"孤竹族使节（2）");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_13,20) && !who->get_legend(TASK_13,21) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,21);
			who->add_exp(3900);
			who->add_potential(125);
			who->add_cash(3500);
			send_user(who,"%c%s",';',"孤竹族使节（2） 经验 3900 潜能 125 金钱 3500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,7,"" ); 
			me->do_welcome(1);       		
        	}
        	break;
        case 7:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_24,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    为了称霸七国，最近本王经常食不甘味、夜不能眠。有人告诉本王，在楚国民间有一种茉莉花茶可以增进食欲，促进睡眠。但本王作为一国之君是不可以随便离开自己的国家的，所以本王想请你去楚国的民间替本王寻回这种茉莉花茶，到时候本王一定好好酬谢你的。可以先去楚国找那些楚国的百姓谈一谈。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_24,15) && !who->get_legend(TASK_24,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    恩，本王果然没有看错人，多亏了你替本王找回这种香浓扑鼻的茉莉花茶，本王现在又可以专注更多的精力于称霸七国的霸业了。本王说过一定要好好酬谢你的，你就别客气了，这些是你应得的，你就收下吧。\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
 
        	break;
        case 8:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_24,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,15,"茉莉花茶（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"茉莉花茶（1）");
        	}
        	break; 
        case 9:
        	if ( who->get_legend(TASK_24,15) && !who->get_legend(TASK_24,16) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"雪水",1) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"茉莉花茶",1) != 1 )
        		{
				item = new("item/98/0114");
				if ( !item  )
					return ;
				p = item->move(who,-1);
				if ( !p )
				{
					destruct(item);
					return;
				}
				item->add_to_user(p);
        			return;
        		}
        		TASK_LEGEND_D->give_item(who,"item/product/65075",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,16);
			who->add_exp(63000);
			who->add_potential(860);
			who->add_cash(63000);
			send_user(who,"%c%s",';',"茉莉花茶（4） 经验 63000 潜能 860 金钱 63000 幽魂项链图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,31,"" );
			me->do_welcome(9);
        	}
        	break;
        case 10:
		if ( who->get_legend(TASK_24,29) && !who->get_legend(TASK_24,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵…御史真乃本王的良臣啊！\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 11:
		if ( who->get_legend(TASK_24,29) && !who->get_legend(TASK_24,30) )
		{
//			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 2 )
//        			return ;
			if(USER_INVENTORY_D->count_empty_carry(who) < 2 )
			{
			        send_user(who,"%c%s",';',"您身上没有足够空位！");
        			return;
			}
			TASK_LEGEND_D->give_item(who,"item/91/9164",1);
			TASK_LEGEND_D->give_item(who,"item/91/9164",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,30);
			who->add_exp(71000);
			who->add_potential(850);
			who->add_cash(55000);
			send_user(who,"%c%s",';',"禀告齐王 经验 71000 潜能 850 金钱 55000 紫心丹 2");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,44,"" );
        	}
        	break;			
        case 12:
	        if ( who->get_legend(TASK_36,1) && !who->get_legend(TASK_36,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    他想要完美橙晶石？这事可有点棘手，首先本王这个秘方可是从不外泄的，如若真的要令本国仙师为他制作，首先赵王迁必须付出让本王满意的代价。\n"ESC"完成任务\ntalk %x# welcome.13\n"ESC"离开", me->get_name(),getoid(me)));
	        else if ( who->get_legend(TASK_36,2) && !who->get_legend(TASK_36,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，好，既然赵王迁同意寡人的条件，寡人也自当如其所愿，完美橙晶石配方很复杂，但是基础原料必须有三种晶石，你去九曲桥找来3颗完美朱红晶石、4颗完美白晶石、3颗完美黄晶石交给我吧。\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开", me->get_name(),getoid(me)));
	        else if ( who->get_legend(TASK_36,3) && !who->get_legend(TASK_36,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这些基础材料都找不到，那么完美橙晶石也别指望了，你可不想看到赵王迁面对你空手而归的表情吧。\n"ESC"离开", me->get_name()));
	        else if ( who->get_legend(TASK_36,4) && !who->get_legend(TASK_36,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这些基础晶石还不够，还有些特殊辅助药物需要你去寻找。\n"ESC"完成任务\ntalk %x# welcome.15\n"ESC"离开", me->get_name(),getoid(me)));
	        else if ( who->get_legend(TASK_36,5) && !who->get_legend(TASK_36,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你收集的那些晶石只占了金、水、火三位，要炼成木性补血延生的完美橙晶石需得补足土性，你去九曲桥找来5份古石灰、七颗慈石、三块雄黄，然后前往秦国找仙师的师弟秦药师，自然如你所愿。\n"ESC"接受任务\ntalk %x# welcome.16\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 13:
        	if ( who->get_legend(TASK_36,1) && !who->get_legend(TASK_36,2) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,2);
			who->add_exp(32000);
			who->add_potential(608);
			who->add_cash(30000);
			send_user(who,"%c%s",';',"完美宝石（1） 经验 32000 潜能 608 金钱 30000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,57,"" );
			me->do_welcome(12);
        	}
        	break; 
	case 14:
        	if ( who->get_legend(TASK_36,2) && !who->get_legend(TASK_36,3) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_36,3);
        		who->delete_save("qwwmzhuhjs");
        		who->delete_save("qwwmbaijs");
        		who->delete_save("qwwmhuangjs");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,51,"完美宝石（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"完美宝石（2）");
        	}
        	break;
	case 15:
        	if ( who->get_legend(TASK_36,4) && !who->get_legend(TASK_36,5) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"完美朱红晶石",3) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"完美白晶石",4) != 1 )
        		{
				TASK_LEGEND_D->give_item(who,"item/98/0162",3); 
        			return ;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"完美黄晶石",3) != 1 )
        		{
				TASK_LEGEND_D->give_item(who,"item/98/0162",3); 
				TASK_LEGEND_D->give_item(who,"item/98/0163",4); 
        			return ;
        		}
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_36,5);
        		who->delete_save("qwwmzhuhjs");
        		who->delete_save("qwwmbaijs");
        		who->delete_save("qwwmhuangjs");
			who->add_exp(39000);
			who->add_potential(650);
			who->add_cash(37000);
			send_user(who,"%c%s",';',"完美宝石（2） 经验 39000 潜能 650 金钱 37000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,51,"" );
			me->do_welcome(12);
        	}
        	break;
	case 16:
        	if ( who->get_legend(TASK_36,5) && !who->get_legend(TASK_36,6) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_36,6);
        		who->delete_save("qwgushihui");
        		who->delete_save("qwcishi");
        		who->delete_save("qwxionghuang");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,52,"完美宝石（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"完美宝石（3）");
        	}
        	break;
        case 17:
	        if ( who->get_level() >= 100 && !who->get_legend(TASK_36,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    秦国妄想征服我国真是自不量力，先不说他行军路线绵长，沿路诸侯侵扰，光是辎重粮草就够他呛，更别说军士离家路远水土不服无心迎战，我军更可以以地利之便消耗他的有生力量，我们齐国以同仇敌忾的保国正义之师打他强词夺理的疲惫之师，天时地利人和都在我方，秦王赢政此来无疑是送死，而我们更可以战胜强秦再创霸业，诸侯臣服，何其快哉！啊，身为齐国的一份子，你可愿为本王霸业尽一份力？九曲桥多年都有妖怪匪类出没，刀剑储量也是颇为丰富，你去九曲桥收集10柄剑，10把刀送到本国大将军那里。\n"ESC"接受任务\ntalk %x# welcome.18\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 18:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_36,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_36,26);
        		who->delete_save("qwlijian");
        		who->delete_save("qwkuaidao");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,58,"大齐的崛起" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"大齐的崛起");
        	}
        	break;
	case 19:
		if ( me->get_city_name() != who->get_city_name() )
			return;
		if ( who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，宫廷里的工匠可以帮助你将普通的号角加工为王之号角，你将号角交给我，我替你咨询下工匠，看还需要做哪些准备。\n"ESC"完成任务\ntalk %x# welcome.20\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠说将普通的号角雕琢成为王之号角需要花费很多珍贵的材料，他需要一些钱来购买这些材料，而单靠他一个人的力量是不可能拿出这么多钱的，我想你应该要帮助他承担一部分，他说雕琢王之号角对他来说也是一项挑战，所以他不收你一文的加工费，只需要你给他100万的材料费就够了。如果你还想雕琢王之号角的话，就将钱交给我吧，我会转交给工匠的。\n    你交钱24小时后就可以来找我索取王之号角了，我想24小时已经足够让工匠来做这件事情了。\n"ESC"接受任务\ntalk %x# welcome.21\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16) && gone_time(who->get_save("wangzhhj"))>=86400 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    工匠通宵达旦地工作，终于在你来之前将王之号角雕琢好了，你拿去看看吧。\n"ESC"完成任务\ntalk %x# welcome.22\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 20:
		if ( me->get_city_name() == who->get_city_name() && who->get_legend(TASK_40,13) && !who->get_legend(TASK_40,14) )
		{
        		if (TASK_LEGEND_D->check_task_item(who,"号角",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,14);
			who->add_exp(3000);
			who->add_potential(100);
			who->add_cash(2500);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,13,"" );
			send_user(who,"%c%s",';',"寻求大王的帮助 经验 3000 潜能 100 金钱 2500");
			me->do_welcome(19);
        	}		
		break;
	case 21:
		if ( me->get_city_name() == who->get_city_name() && who->get_legend(TASK_40,14) && !who->get_legend(TASK_40,15) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( who->get_cash() < 1000000 )
			{
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你身上的钱不足以让工匠购买雕琢王之号角的材料，请你凑齐了钱再来找我吧。\n"ESC"离开", me->get_name(),getoid(me)));
				return ;	
			}
			who->add_cash(-1000000);
			who->set_save("wangzhhj",time());
        		who->set_legend(TASK_40,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHOUGUO,"Chu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,14,"王之号角的雕琢" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"王之号角的雕琢");
        	}		
		break;
	case 22:
		if ( me->get_city_name() == who->get_city_name() && who->get_legend(TASK_40,15) && !who->get_legend(TASK_40,16) && gone_time(who->get_save("wangzhhj"))>=86400 )
		{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;        		
			TASK_LEGEND_D->give_item(who,"item/std/0095",1); 			
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,16);
			who->delete_save("wangzhhj");
			who->add_exp(3000);
			who->add_potential(100);
			who->add_cash(2500);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,14,"" );
			send_user(who,"%c%s",';',"王之号角的雕琢 经验 3000 潜能 100 金钱 2500");
		}
		break;
	case 23:
        	if (who->get_level() >= 110 && !who->get_legend(TASK_45,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你知道什么是齐国至高无上的荣耀吗，你想获得齐国至高无上的荣耀吗？到我身边来吧，我告诉你，这个，也不能太早让你知道了不是？你先去消灭诛仙阵的10只剑魂，回来我将给你答案。\n"ESC"接受任务\ntalk %x# welcome.24\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,7) && !who->get_legend(TASK_45,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呃，看来什么是至高无上的荣耀我不能告诉你啊，因为我必须告诉匹配得上这个荣耀的身份的人才行。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_45,8) && !who->get_legend(TASK_45,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，看来你还是有点能力的，这样吧，我悄悄告诉你什么是齐国至高无上的荣耀，那就是——为本王做事。\n"ESC"完成任务\ntalk %x# welcome.25\n"ESC"离开", me->get_name(),getoid(me)));
        	else if (who->get_legend(TASK_45,9) && !who->get_legend(TASK_45,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近本王爱妃患上一种怪病，非要闻到文竹的味道才能醒来，要么就沉睡不醒，为了爱妃能在宫廷之中陪寡人走动，寡人要尽量在宫廷之中多多种植文竹，看爱卿如此关心寡人，想必区区20株文竹对于爱卿来说不是难事吧。听说天门阵中许多刁民都喜爱收集文竹，想必去问他们取应该很容易办到。\n"ESC"接受任务\ntalk %x# welcome.26\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,10) && !who->get_legend(TASK_45,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    什么，难道你竟然不能从刁民手中拿来文竹么？寡人对你甚为失望，寡人的宫廷可不是毫无荣耀的人来的地方。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_45,11) && !who->get_legend(TASK_45,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来你已经慢慢体验到了寡人给你的无上荣耀了啊，不过寡人还有这种荣耀交付给你。\n"ESC"完成任务\ntalk %x# welcome.27\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,12) && !who->get_legend(TASK_45,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    楚王考烈王前段时间差人送来了100尾越晶鱼，放养在闭夜池中，母后非常喜爱，来而不往非礼也，寡人也要回赠一些礼物给他，本王有一种云雾茶，产于仙山绝壁，都是有道之士与本王论道之时赠送的，据说每年不超过10斤，相信这种礼物，对得起我们齐国大国的身份了吧。\n"ESC"接受任务\ntalk %x# welcome.28\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 24:
		if (who->get_level() >= 110 && !who->get_legend(TASK_45,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_45,7);
        		who->delete_save("qwjianhun");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,69,"无上的荣耀（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"无上的荣耀（1）");
        	}
        	break;
        case 25:
		if ( who->get_legend(TASK_45,8) && !who->get_legend(TASK_45,9) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_45,9);
        		who->delete_save("qwjianhun");
			who->add_exp(51000);
			who->add_potential(780);
			who->add_cash(51000);
			send_user(who,"%c%s",';',"无上的荣耀（1） 经验 51000 潜能 780 金钱 51000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,69,"" );
			me->do_welcome(23);
        	}
        	break;
	case 26:
		if (who->get_legend(TASK_45,9) && !who->get_legend(TASK_45,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_45,10);
        		who->delete_save("qwwenzhu");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,70,"无上的荣耀（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"无上的荣耀（2）");
        	}
        	break;
        case 27:
		if ( who->get_legend(TASK_45,11) && !who->get_legend(TASK_45,12) )
        	{
			if (TASK_LEGEND_D->check_task_item(who,"文竹",20) != 1 )
        			return;        		
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_45,12);
        		who->delete_save("qwwenzhu");
			who->add_exp(55000);
			who->add_potential(830);
			who->add_cash(53000);
			send_user(who,"%c%s",';',"无上的荣耀（2） 经验 55000 潜能 830 金钱 53000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,70,"" );
			me->do_welcome(23);
        	}
        	break;
	case 28:
		if (who->get_legend(TASK_45,12) && !who->get_legend(TASK_45,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;
			TASK_LEGEND_D->give_item(who,"item/98/0224",7); 
        		who->set_legend(TASK_45,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,71,"无上的荣耀（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"无上的荣耀（3）");
        	}
        	break;		
	case 99:
 		EMPEROR_D->do_look( who, me); 
 		break;
        }
}
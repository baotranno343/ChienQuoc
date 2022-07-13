
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 5301; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quản Gia");
        set_city_name("Triệu Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));
//	set("level",60);
//	set("legend",({32*18+1,32*18+4,32*18+13}) );
 	set("mpLegend",([60:({32*18+1,32*18+4,32*18+13}),90:({32*32+9,})]));
 	set("mpLegend2",([60:({32*18+3,32*18+6,32*18+15,}),]));
        setup();
}

// 函数：对话处理
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
	if ( (who->get_level() >=60 && !who->get_legend(TASK_18,1)) || (who->get_legend(TASK_18,1) && !who->get_legend(TASK_18,3)) )
		tmp += sprintf(ESC HIY "管家的苦恼\ntalk %x# welcome.1\n",getoid(me));
	if ( (who->get_level() >=60 && !who->get_legend(TASK_18,4)) || (who->get_legend(TASK_18,4) && !who->get_legend(TASK_18,6)) )
		tmp += sprintf(ESC HIY "叛Quốc之徒\ntalk %x# welcome.4\n",getoid(me));
	if ( (who->get_level() >=60 && !who->get_legend(TASK_18,13)) || (who->get_legend(TASK_18,13) && !who->get_legend(TASK_18,15)) )
		tmp += sprintf(ESC HIY "长城上的烟火\ntalk %x# welcome.7\n",getoid(me));
	if ( who->get_level() >=90 && !who->get_legend(TASK_32,9) )
		tmp += sprintf(ESC HIY "论语\ntalk %x# welcome.10\n",getoid(me));

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
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那些无赖们，每天没事就喜欢东逛西逛，然后伺机找别人点麻烦，想弄点零花钱，生平最瞧不起的就是这种不务正业的人，一定要想个办法来治他，不然他会越来越嚣张，你去燕长城的匝道教训他一顿吧，记得出手别太狠，让他长点记性就行了！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_18,1) && !who->get_legend(TASK_18,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这以后的日子可怎么过啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_18,2) && !who->get_legend(TASK_18,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    什么？你把他杀了？！你快点走，别给我惹出一身麻烦！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_18,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,30,"管家的苦恼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"管家的苦恼");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_18,2) && !who->get_legend(TASK_18,3) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/66027",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_18,3);
			who->add_exp(6900);
			who->add_potential(260);
			who->add_cash(6600);
			send_user(who,"%c%s",';',"管家的苦恼 经验 6900 潜能 260 金钱 6600 银钥匙图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,30,"" );
        	}
        	break;   
        case 4:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    全Quốc通缉犯——叶青，你应该知道吧？最近他潜逃到Yên Quốc附近了，得赶紧把他捉拿归案，不然伤及更多的无辜百姓就不好了。\n    听说朝廷悬赏十万两黄金来捉拿他，如果你能将他干掉，那你可就发达了，趁这个消息还没走漏，赶紧去燕长城除掉他吧！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_18,4) && !who->get_legend(TASK_18,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那叛贼要是将情报出卖给敌Quốc就不好办了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_18,5) && !who->get_legend(TASK_18,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可以安心了，谢谢你了%s！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	break;
	case 5:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_18,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,31,"叛Quốc之徒" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"叛Quốc之徒");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_18,5) && !who->get_legend(TASK_18,6) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/16/1617",5);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_18,6);
			who->add_exp(7100);
			who->add_potential(270);
			who->add_cash(6200);
			send_user(who,"%c%s",';',"叛Quốc之徒 经验 7100 潜能 270 金钱 6200 高爆炸弹 5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,31,"" );
        	}
        	break;   
        case 7:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我最近路过燕长城看见烽火台处有烟火冒出，搞得到处乱成一团，我还差点被当成奸细抓了起来，这肯定是不安分的无赖李小六在作祟，他就喜欢到处给我捣乱，这个小子是的好好教训教训了，你打的他服为止，回来告诉我。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_18,13) && !who->get_legend(TASK_18,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你也纵容这个竖子，谁人可压得他！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_18,14) && !who->get_legend(TASK_18,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这小子再敢张狂，我再管不得他母亲情面，定要将他抽筋拨皮。\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 8:
        	if ( who->get_level() >= 60 && !who->get_legend(TASK_18,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_18,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,34,"长城上的烟火" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"长城上的烟火");
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_18,14) && !who->get_legend(TASK_18,15) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/63022",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_18,15);
			who->add_exp(6800);
			who->add_potential(250);
			who->add_cash(6800);
			send_user(who,"%c%s",';',"长城上的烟火 经验 6800 潜能 250 金钱 6800 气脉丹图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,34,"" );
        	}
        	break;   
        case 10:
       		if ( who->get_level() >=90 && !who->get_legend(TASK_32,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    前段时间听说燕总管在四处寻找论语的原本，我昨天在手下贡献来的物品中居然发现了这个东西，我找来人鉴证确定是真品，作为老朋友好东西当然不敢独享，既然他这么迫切得到它，我就送给他吧，你帮我将他给燕总管送去。\n"ESC"接受任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 11:
        	if ( who->get_level() >=90 && !who->get_legend(TASK_32,9) )
        	{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->give_item(who,"item/98/0150",1);
        		who->set_legend(TASK_32,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,56,"论语" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"论语");
        	}
        	break;
        }
}

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();
void do_fortune();
void accept_task();
void task_bonus();
void do_welcome( string arg );

void do_gold_task_start();
void accept_gold_task();
void gold_task_bonus();

// 函数：获取人物造型
int get_char_picid() { return 6002; }

// 函数：构造处理
void create()
{
        set_name( "Vệ Đội Trưởng " );

        set_2( "talk", ([
                "task"          : (: do_task_start :),
                "cancel"        : (: do_task_cancel :),
                "fortune"	: (: do_fortune :),
                "accept"	: (: accept_task :),
                "bonus"		: (: task_bonus :),
                "welcome"    	: (: do_welcome :),

                "gold_start"    : (: do_gold_task_start :),
                "gold_accept"	: (: accept_gold_task :),
                "gold_bonus"	: (: gold_task_bonus :),
        ]));
//        set("level", 10);
//        set("legend", ({ 32,55 }));
//	set("mpLegend",([0:({32*41+1,32*41+13}),10:({32+23}),]));
	set("mpLegend2",([0:({32*48+20,32*48+27,32+20}),]));
        setup();
}

// 函数：对话处理
void do_look( object who ) { TASK_BANDITI_D->do_look( who, this_object() ); }

// 函数：开始任务
void do_task_start() { TASK_BANDITI_D->do_task_start( this_player(), this_object() ); }
// 函数：取消任务
void do_task_cancel() { TASK_BANDITI_D->do_task_cancel( this_player(), this_object() ); }
//使命物品
void do_fortune()
 { 
	TASK_BANDITI_D->do_fortune( this_player(), this_object() ); 
 } 
void task_bonus()
 { 
	TASK_BANDITI_D->task_bonus( this_player(), this_object() ); 
 }
 //接受任务
void accept_task()
 { 
	TASK_BANDITI_D->accept_task( this_player(), this_object()); 
 } 

// 函数：开始黄金卫队长任务
void do_gold_task_start() { TASK_BANDITI_D->do_gold_task_start( this_player(), this_object() ); }
// 函数：黄金卫队长任务奖励
void gold_task_bonus() { TASK_BANDITI_D->gold_task_bonus( this_player(), this_object() ); }
//函数：接受黄金卫队长任务
void accept_gold_task() { TASK_BANDITI_D->accept_gold_task( this_player(), this_object()); } 

// --------------------------------------------------------------- 远程调用 ----

// 函数：接受物品
int accept_object( object who, object item ){ return __FILE__ ->accept_object_callout( this_object(), who, item ); }

// 函数：接受物品(在线更新)
int accept_object_callout( object me, object who, object item ) 
{
        int level;

        me->to_front_eachother(who);

        if( !item->is_task_item() ) 
        {
                return 0;
        }
        else
        {
                item->give_bonus(who);

							 send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), 
                sprintf("%s：\n    Thật...thật tốt quá, ta....ta vẫn muốn....muốn cái này!"
                        , me->get_name() ) );
        	return 1;
        }
}
void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        object who, item;
        int p, z, x, y, flag;
	
        who = this_player();

	if (arg=="cancel")
	{
	        item = who->get_equip(HAND_TYPE);
		if (item && item->get_item_number()==10001078)
		{	
			send_user( who, "%c%c%s", 0x59, 1, sprintf("你是否使用'瞒天过海符'来消除你的任务间隔时间？\n"
	                	ESC "%c\n"ESC"use %x# banditi\n"
	                        , 1, getoid(item) ) );			
			return;
		}		
	}
        flag = to_int(arg);
        switch(flag)
        {
        case 1:                               
                if ( who->get_legend(TASK_NEWBIE_01, 19) && !who->get_legend(TASK_NEWBIE_01, 20) )
                	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    太——太——太好了，今——今天又——又——有酒喝了。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
                break;
	case 2:
		if ( !who->get_legend(TASK_NEWBIE_01, 19) || who->get_legend(TASK_NEWBIE_01, 20) )
			return ;
		if (TASK_LEGEND_D->check_task_item(who,"酒钱",1) != 1 )
        			return;
		TASK_LEGEND_D->task_finish(who);
		who->set_legend(TASK_NEWBIE_01, 20);
		who->add_exp(160);
		who->add_potential(10);
		send_user(who,"%c%s",';',"牛二报恩 经验 160 潜能 10");
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,10,"" );	
		break;
	case 3:
		if ( who->get_level()<10 )
			return ;
		if ( !who->get_legend(TASK_NEWBIE_01, 23) )
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    周——周国的神仙爷爷说有——有事找你，你——你去他那里跑——跑一趟吧，这也是——是个锻炼的机会呀！记——记得了，是——是去周国哦！如果你——不知道怎——么去的话，找——找驿站老板帮忙就——就是了。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),getoid(me)));
 		else if ( !who->get_legend(TASK_NEWBIE_01, 24) )
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    你——你还没去？可——可能他找——找你是有急——急事哦～\n"ESC"离开",me->get_name()));
		break;
	case 4:
		if ( who->get_level()<10 || who->get_legend(TASK_NEWBIE_01, 23)  )
			return;
		who->set_legend(TASK_NEWBIE_01, 23);
		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,13,"锻炼的机会" );
		break;
        case 5:
		if ( who->get_legend(TASK_48, 19) && !who->get_legend(TASK_48, 20))
//        	if ( !who->get_legend(TASK_41,1) )
//			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原本村外的小山鸡是一群多么可爱的小动物，它们在野外觅食，在我上山打猎的时候，它们都会围绕在我周围，因为它们知道我不会伤害它们，但是现在，一切都变了……\n    它们不再可爱，不再善良，它们会攻击人类，我怀疑它们被妖怪迷惑，受了妖怪控制，才变成这样，这样吧，你先去消灭掉那些小山鸡，回来告诉我它们的能力后，我再想想下一步该怎么做。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
//        	else 	if ( who->get_legend(TASK_41, 2) && !who->get_legend(TASK_41, 3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\n Lực lượng của chúng hùng hậu như vậy, ta đóan thế lực yêu quái sau lưng cũng chẳng tằm thường, xem ra ta phải bố trí bước kế tiếp, dù sao cũng rất cám ơn ngươi !\n"ESC"Hòan thành nhiệm vụ\ntalk %x# welcome.7\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
        	
        	break;
	case 6:
        	if ( !who->get_legend(TASK_41,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_41,1);
        		who->delete_save("wdzxiaosj");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,31,"妖言惑众" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"妖言惑众");
        	}
        	break;
        case 7:
		if ( who->get_legend(TASK_48, 19) && !who->get_legend(TASK_48, 20))
//        	if ( who->get_legend(TASK_41,2) && !who->get_legend(TASK_41,3) )
        	{
			item = new( "/item/91/9100" );   //行军散
			if ( !item )
				return ;
			item->set_amount(5);
	                p =item->move(who, -1);
	                if ( p == 0 )
	                {
	                	destruct(item); 
	                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
	                	return ;
	                }
	                item->add_to_user(p);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_48,20);
        		who->delete_save("new_chy");
			who->add_exp(650);
			who->add_potential(30);
			who->add_cash(1000);
			send_user(who,"%c%s",';',"Yêu Ngôn Mị Dân Kinh nghiệm 650 Tiềm năng 30 Ngân lượng 1000 Hành Quân Tán 5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,108,"" );
			me->do_welcome(11);
        	}
        	break;  
        case 8:
//        	if ( !who->get_legend(TASK_41, 13) )
		if ( who->get_legend(TASK_48, 27) && !who->get_legend(TASK_48, 28))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    别看我是个粗人，可是我还是挺讲究生活的精致的，我喜欢在家里养点花花草草的，这样房子里看起来才有生气，虽然家里种了不少的兰花、文竹、菊花之类的，但是我最喜欢的还是那百合，象征着纯洁。\n    新手村的当铺老板一直是我最敬佩的人，他家正在装修，所以我想送他一些百合花来装饰房屋，我听说巴丘的持扇草人、赤褐蚁或子母蛙都会有百合花，你去替我找些来送到他家吧。\n    做完任务后，用alt+w打开人物属性界面，再使用新手信物就可以快速回到新手村哦！\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
//        	else 	if ( who->get_legend(TASK_41, 14) && !who->get_legend(TASK_41, 15) )
//			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不错，就是这种百合花，是我最喜欢的！\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 9:
//        	if ( !who->get_legend(TASK_41,13) )
		if ( who->get_legend(TASK_48, 27) && !who->get_legend(TASK_48, 28))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_48,28);
        		who->delete_save("wdzbaihh");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,112,"Trang Trí Phòng Ốc" );
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Trang Trí Phòng Ốc");
        	}
        	break;
        case 10:
        	if ( who->get_legend(TASK_41,14) && !who->get_legend(TASK_41,15) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"百合花",3) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_41,15);
        		who->delete_save("wdzbaihh");
			who->add_exp(250);
			who->add_potential(10);
			send_user(who,"%c%s",';',"装饰房屋 经验 250 潜能 10");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,30,"" );
        	}
        	break;  
        case 11: 
		if ( who->get_legend(TASK_48, 20) && !who->get_legend(TASK_48, 21))
			send_user(who,"%c%s",':',sprintf("%s:\n    新手村的村民几乎都患上了一种病，他们全身疲软无力，成天想睡觉，没有精神去耕种，去开店做生意，严重影响了村民的正常生活，之前我已经询问过药店老板了，可惜他也不知道这是种什么病，他说他行医这么多年从未见过如此奇怪的病症，他说功德老人见多识广，应该会知道，所以想请你去趟功德老人家，询问他关于村人病症之事。\n    功德老人就在修理店的后面，你好好找找吧。找到他后注意问得详细点。\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_48, 26) && !who->get_legend(TASK_48, 27))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(" %s :\n Đúng rồi! ta sớm đã nghi ngờ có người hạ độc, nhất định ta sẽ tra cứu vụ này, đường đi vất vả cho ngươi rồi !\n"ESC"Hòan thành nhiệm vụ\ntalk %x# welcome.13\n"ESC"Rời khỏi", me->get_name(),getoid(me)));
        	break;
	case 12:
//		if ( who->get_level() >= 5 && !who->get_legend(TASK_41, 4) )
		if ( who->get_legend(TASK_48, 20) && !who->get_legend(TASK_48, 21))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_48,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,109,"疑难杂症（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"疑难杂症（1）");
        	}
        	break; 
        case 13:
		if ( who->get_legend(TASK_48, 26) && !who->get_legend(TASK_48, 27))
        	{
			if (TASK_LEGEND_D->check_task_item(who,"解药",1) != 1 )
        			return;
			item = new( "/item/88/0001" );   //草鞋
			if ( !item )
				return ;
	                p =item->move(who, -1);
	                if ( p == 0 )
	                {
	                	destruct(item); 
	                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
	                	return ;
	                }
	                item->add_to_user(p);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_48,27);
			who->add_exp(600);
			who->add_potential(25);
			who->add_cash(2000);
			send_user(who,"%c%s",';',"Chứng Chứng Bệnh Nan Y (3) Kinh nghiệm 600 Tiềm năng 25 Ngân lượng 2000, Hài Tân Thủ");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,111,"" );
			me->do_welcome(8);
        	}
        	break; 
        }
}
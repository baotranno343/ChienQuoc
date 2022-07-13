
// 自动生成：/make/npc/make0007
#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：修理师傅
int is_repairer() { return 1; }
void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5407; }

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Sửa Chữa");
        set_city_name("Tân Thủ Thôn");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level", 5);
//        set("legend", ({ 49 }));
	set("mpLegend",([5:({32*40+20,32*49+24}),]));
	set("mpLegend2",([0:({32*48+17,}),0:({32*49+26,})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int id;
	string tmp="";
	object me=this_object();
	id = getoid(me);

	"/quest/help"->send_help_tips(who, 52);
	if ( who->get_legend(TASK_48, 16) && !who->get_legend(TASK_48, 17) )
               		tmp += sprintf(ESC  +HIY+ "Thu mua búa\ntalk %x# welcome.1\n",id) ;	
	if ( who->get_legend(TASK_48, 17) && !who->get_legend(TASK_48, 18) )
               		tmp +=sprintf(ESC  +HIY+ "Yêu Ngôn Mị Dân\ntalk %x# welcome.11\n",id) ;	

//	if ( who->get_level()>=5&&(!who->get_legend(TASK_NEWBIE_01, 17)||!who->get_legend(TASK_NEWBIE_01, 18)) )
//               		tmp += sprintf(ESC "破损的铁锹\ntalk %x# welcome.3\n",id) ;	

	if ( who->get_level()>=5 && !who->get_legend(TASK_40, 20) )
		tmp +=	 sprintf(ESC +HIY+ "孤独\ntalk %x# welcome.5\n",id) ;	
	if ( (who->get_level()>=5&&!who->get_legend(TASK_49,24)) ||( who->get_legend(TASK_49,25) && !who->get_legend(TASK_49,26) ) )
		tmp +=  sprintf(ESC +HIY+ "行路难\ntalk %x# welcome.13\n",getoid(me));

	if ( sizeof(tmp) )
	{
        	send_user( who, "%c%c%w%s", ':', 3, who->get_char_picid(),
	                " " + get_name() + " :\n "+"/quest/word"->get_normal_word(this_object()) 
	                        + sprintf("\n"ESC"Tu sửa và đánh giá\ntalk %x# welcome.99\n",getoid(this_object())) 
	                        + tmp +
	                        ESC "Rời khỏi");
	}	
	else	
        	REPAIR_CMD->main( who, sprintf( "%x#", getoid( this_object() ) ) );
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p,i,b;
        object who, item, *inv;
        string result;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:	
		if ( who->get_legend(TASK_48, 16) && !who->get_legend(TASK_48, 17) )
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s :\n Chủ Tiệm Tạp Hóa thật là đáng tin cậy, phái người đến cho ta nhanh\n như thế, vất vả cho ngươi rồi, %s , làm ngươi vật vả thế,\n thù lao đây ngươi hãy cầm lấy!\n Ta vẫn có thể tu sửa đặc biệt trang bị trên người ngươi một lần nữa\n.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.2\n"ESC"Rời khỏi",me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		break;
	case 2:
		if ( who->get_legend(TASK_48, 16) && !who->get_legend(TASK_48, 17) )
		{
			if( !objectp( item = present("Búa Hàn Thiết", who, 1, MAX_CARRY) ) || item->is_tiecui() != 1 )
			{
				send_user(who,"%c%s",'!',"你的铁锤呢?");
				return;	
			}
			item->remove_from_user();
			destruct(item);		
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_48, 17);
			who->add_exp(550);
			who->add_potential(50);
			who->add_cash(2500);

			inv=who->get_all_equip();
			for( i = 0 ; i < sizeof(inv)-1; i ++ )
			{
				if (inv[i]==0) continue;
				b=inv[i]->get_max_lasting();
				inv[i]->set_lasting(b);
			}

			send_user(who,"%c%s",';'," Kinh nghiệm 550, Tiềm năng 50, Ngân lượng 2500, trang bị trên người ngươi cần đến Chủ Tiệm Sửa Chữa để tu sửa đặc biệt một lần nữa.");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,107,"" );		
			me->do_welcome(11);
		}
		break;
	case 3:
		if ( who->get_level()>=5 && !who->get_legend(TASK_NEWBIE_01, 17)) 
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    前几天，村口的牛二托人交给我这把铁锹，你看我，实在是抽不开身，你能帮我把这把铁锹转交给牛二吗？牛二就在村口。拜托你了！只要你能给我安全的送到，你一定会拿到自己想要的奖励！\n"ESC"接受\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),getoid(me)));
		else   if (!who->get_legend(TASK_NEWBIE_01, 18)) 
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    叫你送去给牛二的铁锹送到了吗？他可等着用呢，别耽误了人家的农活！\n"ESC"离开",me->get_name()));
		break;
	case 4:
		if ( who->get_level() < 5 || who->get_legend(TASK_NEWBIE_01, 17) )  
			return ;
		item = new( "/item/98/9883" );
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
		who->set_legend(TASK_NEWBIE_01, 17);
		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,9,"破损的铁锹" );
		send_user( who, "%c%s", '!', "你接受了"HIY"破损的铁锹"NOR"任务");
		break;
        case 5:
        	if ( who->get_level()>=5 && !who->get_legend(TASK_40, 20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    孤独，注定孤独。\n    我为了能让家里人过上丰衣足食的生活，从小就跟随师傅学习修理各种武器、防具，等到我终于能够独立门户了，我就来到了这个新手村，开了这家修理店。\n    生意并不是很好，我苦苦支撑了这么多年，现在我老了，还是孤身一人，儿时的伙伴都不知所终，我记得清溪的孔老头曾经是我的好朋友，现在很想见见他，可是实在脱不开身，你能替我将这封叙旧信送到清溪的孔老头那吗？\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
	       	break;
        case 6:
        	if ( who->get_level()>=5 && !who->get_legend(TASK_40, 20) )
        	{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->give_item(who,"item/98/0197",1);
        		who->set_legend(TASK_40,20);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,34,"孤独" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"孤独");
        	}
        	break;
        case 11:
		if ( who->get_legend(TASK_48, 17) && !who->get_legend(TASK_48, 18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原本幽谷的那群小动物是多么可爱，它们在野外觅食，在我上山打猎的时候，它们都会围绕在我周围，因为它们知道我不会伤害它们，但是现在，一切都变了……\n    它们不再可爱，不再善良，它们会攻击人类，我怀疑它们被妖怪迷惑，受了妖怪控制，才变成这样，这样吧，你先去消灭掉那些小蜜蜂、小蚂蚁和斑点蛙，去报告新手村的卫队长，看看他想怎么处理。\n    做完任务后，用alt+w打开人物属性界面，再使用新手信物就可以快速回到新手村哦！\n"ESC"接受任务\ntalk %x# welcome.12\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 12:
		if ( who->get_legend(TASK_48, 17) && !who->get_legend(TASK_48, 18) )
		{
	                if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
	                who->set_legend(TASK_48, 18);
	                who->delete_save("new_chy");
	                send_user( who, "%c%s", '!', "Chọn nhiệm vụ "HIY"Yêu Ngôn Mị Dân"NOR"!");
	                send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
	                send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,108,"Yêu Ngôn Mị Dân" );
		}
                break;   
        case 13:
		if( who->get_level()>=5 && !who->get_legend(TASK_49, 24) )
        		send_user(who,"%c%s",':',sprintf("%s\n    新手村北面的巴丘是去洞庭湖的必经之路，行人商旅来往频繁。最近不知道怎么了，那里活动的子母蛙和赤褐蚁开始袭击行人，我有个朋友想来探望我，结果被堵在洞庭湖没法过来。我希望你去巴丘消灭几只子母蛙、赤褐蚁和持扇草人，解决商旅过往的难题。\n"ESC"接受任务\ntalk %x# welcome.14\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_49, 25) && !who->get_legend(TASK_49, 26) )
        		send_user(who,"%c%s",':',sprintf("%s\n    这下好了，我的朋友终于可以来探望我了，多亏你帮忙。以后要是你有什么东西要修理尽管来找我，我一定帮忙。\n"ESC"完成任务\ntalk %x# welcome.15\n"ESC"离开",me->get_name(),getoid(me)));
        	break;
	case 14:
		if( who->get_level()>=5 && !who->get_legend(TASK_49, 24) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_49, 24);
			who->delete_save("xiuli_zimuwa");
			who->delete_save("xiuli_chy");
			who->delete_save("xiuli_cscr");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,48,"行路难" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"行路难");	
		}
		break;
	case 15:
		if ( who->get_legend(TASK_49, 25) && !who->get_legend(TASK_49, 26) )
		{
			TASK_LEGEND_D->task_finish(who);
			who->delete_save("xiuli_zimuwa");
			who->delete_save("xiuli_chy");
			who->delete_save("xiuli_cscr");
			who->add_exp(250);
			who->add_potential(40);
			who->add_cash(600);
			who->set_legend(TASK_49, 26);
			send_user(who,"%c%s",';',"行路难 经验250 潜能40 金钱600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,48,"" );			
		}
		break;
        case 99:
        	REPAIR_CMD->main( who, sprintf( "%x#", getoid( me ) ) );
        	break;
	}
}  	

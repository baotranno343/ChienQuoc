
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_goto( int flag );
void accept_task(string arg);

// 函数：获取人物造型
int get_char_picid() { return 4143; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Sứ Giả Môn Phái");

        set_2( "talk", ([
                "1"    : (: do_goto, 1 :),
                "2"    : (: do_goto, 2 :),
                "3"    : (: do_goto, 3 :),
                "4"    : (: do_goto, 4 :),
                "5"    : (: do_goto, 5 :),
                "6"    : (: do_goto, 6 :),
                "7"    : (: do_goto, 7 :),
                "task" : (: accept_task :),
                "welcome"        : (: do_welcome :),

        ]));
//        set("level", 10);
//	set("legend", ({33}));
	set("mpLegend",([5:({32*50+10})]));
	set("mpLegend2",([0:({32*49+10,32*49+8})]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
        int id = getoid( this_object() );
	string result="";
	object item;
//	if (who->get_level()>=10&&(!who->get_legend(TASK_NEWBIE_01, 1)||!who->get_legend(TASK_NEWBIE_01, 2)) )
//		result = ESC"老村长的委托。\n" + sprintf("talk %x# task.1\n", id); 	
//	if ( "sys/sys/count"->get_new_story() )
//		result = ESC"去武功修练场。\n" + sprintf("talk %x# welcome.10\n", id);
	if ( who->get_legend(TASK_NEWBIE_01, 21) && !who->get_legend(TASK_NEWBIE_01, 22) )	
	{
		if ( sizeof(result) )
			result += ESC"牛二的苦恼。\n" + sprintf("talk %x# task.3\n", id); 
		else
			result = ESC"牛二的苦恼。\n" + sprintf("talk %x# task.3\n", id); 	
	}
	if ( who->get_level() >= 5 && !who->get_legend(TASK_2_00,10) ) 
			result += ESC HIY "Cơ Hội Từ Vương Bộ Đầu.\n" + sprintf("talk %x# welcome.1\n", id); 
	if ( who->get_legend(TASK_49, 9) && !who->get_legend(TASK_49, 10) && objectp( item = present("丢失的手镯", who, 1, MAX_CARRY) ) && item->is_souzuo() == 1 )
	        	result += sprintf(ESC HIY "丢失的手镯\ntalk %x# welcome.3\n",id);
	if ( who->get_legend(TASK_49, 7) && !who->get_legend(TASK_49, 8))
		result +=  sprintf(ESC  +HIY+ "当铺老板的交易\ntalk %x# welcome.5\n",id);
        if( who->get_fam_name() == "" )

                send_user( who, "%c%c%w%s", ':', 3, 4153, sprintf( " %s :\n Vị " + NPC_RANK_D->get_respect(who) + " này nếu muốn đến nơi những cao nhân sống ẩn dật, ta đây không lấy phí.\n"
                        ESC "Đi đến Đào Hoa Nguyên.\n"   + sprintf( "talk %x# 1\n", id ) +
                        ESC "Đi đến Thục Sơn\n"     + sprintf( "talk %x# 2\n", id ) +
                        ESC "Đi đến Đại Chu Doanh trại quân đội.\n" + sprintf( "talk %x# 3\n", id ) +
                        ESC "Đi đến Trang Viện.\n"     + sprintf( "talk %x# 4\n", id ) +
                        ESC "Đi đến Mao Sơn.\n"     + sprintf( "talk %x# 5\n", id ) +
                        ESC "Đi đến Côn Luân Sơn.\n"   + sprintf( "talk %x# 6\n", id ) +
                        ESC "Đi đến ĐầmVân Mộng.\n"   + sprintf( "talk %x# 7\n", id ) +
			result +
                        ESC "Rời khỏi.\nCLOSE\n", get_name() ) );

        else        send_user( who, "%c%c%w%s", ':', 3, 4153, sprintf( " %s :\n Vị " + NPC_RANK_D->get_respect(who) + " này muốn trở về môn phái à?\n"
                        ESC "Quay về môn phái.\n"     + sprintf( "talk %x# 1\n", id ) +
			result +
                        ESC "Rời khỏi.\nCLOSE\n", get_name() ) );
}

// 函数：移动处理
void do_goto( int flag )
{
        object map, me, who, npc;
        int gold, z, x, y, p;

        me = this_object();  who = this_player();

/*      if( present("钱票", who, 1, MAX_CARRY) )
        {
                send_user( who, "%c%s", '!', "您不能携带钱票。" );    // 带着钱票不能使用驿站。
                return;
        }       */
        if( who->get_level()<10 )
        {
                send_user( who, "%c%s", '!', "Đẳng cấp của bạn quá thấp, không thích hợp với những con đường gồ ghề." );
                return;
        }          
        if( present("贵重物品", who, 1, MAX_CARRY) )
        {
                send_user( who, "%c%s", '!', "您不能携带贵重物品。" );    // 带着贵重物品不能使用驿站。
                return;
        }
        if( objectp( npc = who->get_quest("escort.robber#") ) && npc->is_escort_robber() )    // 寻找蒙面人
        {
                send_user( who, "%c%s", '!', "蒙面人出现，您的行动受到影响。" );
                return;
        }
        gold = 0;

        switch( who->get_fam_name() )
        {
              default : gold =  0;  break;
        case "Đào Hoa Nguyên" : flag = 1;  break;
          case "Thục Sơn" : flag = 2;  break;
        case "Cấm Vệ Quân" : flag = 3;  break;
          case "Đường Môn" : flag = 4;  break;
          case "Mao Sơn" : flag = 5;  break;
        case "Côn Luân" : flag = 6;  break;
        case "Vân Mộng Cốc" : flag = 7;  break;
        }

        if( who->get_cash() < gold )
        {
                send_user( who, "%c%s", '!', "您手上的现金不够。" );
                return;
        }

        switch( flag )
        {
      default :
       case 1 : z = 289;  p = get_jumpin(z, 20);  break;
       case 2 : z = 273;  p = get_jumpin(z, 20);  break;
       case 3 : z = 080;  p = get_jumpin(z, 20);  break;
       case 4 : z = 324;  p = get_jumpin(z, 20);  break;
       case 5 : z = 269;  p = get_jumpin(z, 20);  break;
       case 6 : z = 054;  p = get_jumpin(z, 20);  break;
       case 7 : z = 165;  p = get_jumpin(z, 20);  break;
        }

        if( p )
        {
//                who->add_cash( -gold );  who->add_gold_log("pay", gold);
                who->add_to_scene( z, p / 1000, p % 1000, get_d(who), 40971, 0, 40971, 0 );

                if( map = get_map_object(z) && gold>0 ) 
                {
                        write_user( who, ECHO "您花费 %d 金来到%s。\n", gold, map->get_name() );
                }
        }
}

void accept_task(string arg)
{
	int i;
	object who=this_player(),item;
	if ( who->get_level()<5 )
		return ;

	i = to_int(arg);
	if ( i == 1  )
	{
		if ( !who->get_legend(TASK_NEWBIE_01, 1) )
			send_user( who, "%c%c%w%s", ':', 3, 4153,sprintf("%s\n    听老村长说最近村子里不太平，可能需要你们这些江湖人士的帮助，你去看看吧，他如果能委托你做点事情，你应该会拿到非常丰厚的报酬哦！\n    老村长离我这也不远，就在我的西南方，村子的最南边。\n"ESC"接受任务\ntalk %x# task.2\n"ESC"离开",get_name(),getoid(this_object())));	
		else if ( !who->get_legend(TASK_NEWBIE_01, 2) )
			send_user( who, "%c%c%w%s", ':', 3, 4153,sprintf("%s\n    年轻人，做事得积极点，慢吞吞的，一点朝气都没有！老村长那里急着呢，你赶快去吧！\n"ESC"离开",get_name()));	}
	else if ( i == 2 && !who->get_legend(TASK_NEWBIE_01, 1))
	{
		who->set_legend(TASK_NEWBIE_01, 1);
		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,12,"老村长的委托" );
		send_user( who, "%c%s", '!', "你接受了"HIY"老村长的委托"NOR"任务");
	}
	else if ( i ==  3 && who->get_legend(TASK_NEWBIE_01, 21) && !who->get_legend(TASK_NEWBIE_01, 22))
	{
		send_user( who, "%c%c%w%s", ':',3, 4153, sprintf("%s:\n    不是我不肯帮他啊！不收成年之人这是各大门派的老传统啊！你让我怎么去介绍呢？看在棋谱的份上，我就去试一下吧！能不能成？就看他造化了。\n"ESC"完成任务\ntalk %x# task.4\n"ESC"离开",get_name(),getoid(this_object())));
		
	}
	else if ( i ==  4 && who->get_legend(TASK_NEWBIE_01, 21) && !who->get_legend(TASK_NEWBIE_01, 22))
	{
		if( !objectp( item = present("棋谱", who, 1, MAX_CARRY) ) || item->is_qipu() != 1 )
		{
			send_user(who,"%c%s",'!',"你的棋谱呢?");
			return;	
		}
		item->remove_from_user();
		destruct(item);
		who->set_legend(TASK_NEWBIE_01, 22);
		who->add_exp(100);
		who->add_potential(50);
		send_user(who,"%c%s",';',"牛二的苦恼 经验 100 潜能 50");
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,11,"" );			
	}
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
		if ( who->get_level() >= 5 && !who->get_legend(TASK_2_00,10) ) 
			send_user(who, "%c%c%w%s", ':', 3, 4153, sprintf("%s:\n    周国王捕头可不是一般人，不管是窃贼宵小还是江洋大盗，都休想逃脱他的手心。\n    不过王捕头那里最近差事太多，人手也不够，听说是因为犯人逃跑了，周王悬赏捉拿这些人，想想看，王都下命令了，那奖赏肯定不少，你去了可得机灵点，给王捕头一点小意思，道理就不用我说了吧。王捕头就在周国城内的驿站旁边，还挺近的，你好好找找吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me))); 	
		break;
        case 2:
		if ( who->get_level() >= 5 && !who->get_legend(TASK_2_00,10) ) 
        	{
//        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
//        			return ;
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
//        		TASK_LEGEND_D->give_item(who,"item/98/0177",1);	
//        		who->set_legend(TASK_49,11);
			who->set_legend(TASK_2_00,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,119,"王捕头的美差" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"王捕头的美差");
        	}
        	break;
        	
        case 3:
		if ( who->get_legend(TASK_49, 9) && !who->get_legend(TASK_49, 10) && objectp( item = present("丢失的手镯", who, 1, MAX_CARRY) ) && item->is_souzuo() == 1 )
			send_user(who, "%c%c%w%s", ':', 3, 4153, sprintf("%s:\n    先把手镯交给我吧，我好好的进行消毒，稍后我会自己交给酒店老板的。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 4:
		if ( who->get_legend(TASK_49, 9) && !who->get_legend(TASK_49, 10) && objectp( item = present("丢失的手镯", who, 1, MAX_CARRY) ) && item->is_souzuo() == 1 )
		{
			if( objectp( item = present("丢失的手镯", who, 1, MAX_CARRY) ) && item->is_souzuo() == 1 )
			{
				item->remove_from_user();
				destruct(item);
				item = new("item/87/9999");
				p = item->move(who,-1);
				item->add_to_user(p);
				who->add_potential(20);
				who->add_exp(250);
				who->delete_save_2("dssouzuo");
				who->delete_save_2("dssouzuo1");
				TASK_LEGEND_D->task_finish(who);
				who->set_legend(TASK_49,10);
				send_user(who,"%c%s",';',"丢失的手镯 经验 300 潜能 20 初学者腰带 1 ");
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,117,"" );
				me->do_welcome(1);
			}
		}
		break;
	case 5:
		if ( who->get_legend(TASK_49, 7) && !who->get_legend(TASK_49, 8))
			send_user(who,"%c%s",':',sprintf("%s\n    “没想到这当铺老板对我的事还真上心，谢谢你找来这些火焰石供我把玩。这是给你的奖励！”\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开",me->get_name(),getoid(me))); 		
		break;
	case 6:
		 if ( who->get_legend(TASK_49, 7) && !who->get_legend(TASK_49, 8))
       		 {
        		if (TASK_LEGEND_D->check_task_item(who,"火焰石",5) != 1 )
        			return;
        		who->delete_save("huoyanshi");
			item = new( "/item/91/9100" );   //行军散
			item->set_amount(10);
	                p =item->move(who, -1);
	                item->add_to_user(p);
			who->add_potential(30);
			who->add_exp(280);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_49,8);
			who->set_legend(TASK_49,9);	//取消丢失的手镯任务
			who->set_legend(TASK_49,10);
			send_user(who,"%c%s",';',"当铺老板的交易 经验 280 潜能 30 行军散 10 ");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,116,"" );
			me->do_welcome(1);
		}
		break;
	case 10:
		if ( "sys/sys/count"->get_new_story() == 0 )
			return ;
		p = get_jumpin(887, 1);
		who->add_to_scene(887,p / 1000,p % 1000);
		break;
	}
}

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5805; }

// 函数：构造处理
void create()
{
        set_name("Ngưu Nhị");

        set_2( "talk", ([
                "welcome"    : (: do_welcome :),
        ]));
//        set("level", 5);
//        set("legend", ({ 51,53 }));
	set("mpLegend",([0:({32+19,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        int id = getoid( this_object() );
	if ( who->get_legend(TASK_NEWBIE_01, 17) && !who->get_legend(TASK_NEWBIE_01, 18) )
		tmp += ESC "破损的铁锹。\n"  + sprintf( "talk %x# welcome.6\n", id );
	if ( !who->get_legend(TASK_NEWBIE_01, 19) )
			tmp += ESC +HIY+ "牛二报恩。\n"  + sprintf( "talk %x# welcome.8\n", id );
/*	if ( who->get_level() >= 5 && (!who->get_legend(TASK_NEWBIE_01, 21) || !who->get_legend(TASK_NEWBIE_01, 22)))
	{
		if ( sizeof(tmp) )
			tmp += ESC "牛二的苦恼。\n"  + sprintf( "talk %x# welcome.10\n", id );
		else
			tmp = ESC "牛二的苦恼。\n"  + sprintf( "talk %x# welcome.10\n", id );
	}*/
        more_look_menu( who, sprintf( " %s :\n " + NPC_RANK_D->get_respect(who) + " , ta có thể giúp người được gì chăng ?\n", get_name() )
        	+ tmp +
                ESC "Chọn Tân Thủ Thôn là nơi trở lại thành.\n" + sprintf( "talk %x# welcome.1\n", id ) +
                ESC "Công Đức Lão Nhân sống ở đâu?\n" + sprintf( "talk %x# welcome.2\n", id ) +
                ESC "Đốc Công của Tân Thủ Thôn ở đâu?\n" + sprintf( "talk %x# welcome.3\n", id ) +
                ESC "Sứ Giả Môn Phái đang ở đâu?\n" + sprintf( "talk %x# welcome.4\n", id ) +
                ESC "Nhà Lão Thôn Trưởng ở đâu?\n" + sprintf( "talk %x# welcome.5\n", id ) 
                );
}

// 函数：移动处理
void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        object who;
        int p, z, x, y, flag;
	object item;
	
        who = this_player();
        
        flag = to_int(arg);
        switch(flag)
        {
        case 1:                               
                if( p = get_jumpin(1, 10) )
                {        
                        who->set_latest_city(00110);    // 回城符：新手村(001 #10)
        
                        write_user( who, ECHO "您设置新手村为回城点。\n" );
                }
                break;
        case 2:
                send_user( who, "%c%s", ':', get_name() + "：\n    我刚才好像在修理店后面见过那位老人家。\n");                
                break;
        case 3:
                send_user( who, "%c%s", ':', get_name() + "：\n    工头大叔很喜欢呆在村子的酒店喝酒。\n");                
                break;
        case 4:
                send_user( who, "%c%s", ':', get_name() + "：\n    不就是村口那位吗？\n");                
                break;
        case 5:
                send_user( who, "%c%s", ':', get_name() + "：\n    老村长的家就在村子的东南最尽头处。\n");                
                break;
	case 6:
		if ( !who->get_legend(TASK_NEWBIE_01, 17) || who->get_legend(TASK_NEWBIE_01, 18))
			return ;
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    终于送过来了呀，我都送去修理好几天了，一直都没有给我送回来，可耽误了我不少农活啊！不干活就没饭吃呀！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开",me->get_name(),getoid(me)));
		break;
	case 7:
		if ( !who->get_legend(TASK_NEWBIE_01, 17) || who->get_legend(TASK_NEWBIE_01, 18))
			return ;
		if( !objectp( item = present("铁锹", who, 1, MAX_CARRY) ) || item->is_tieqiu() != 1 )
		{
			send_user(who,"%c%s",'!',"你的铁锹呢?");
			return;	
		}
		item->remove_from_user();
		destruct(item);		
		who->set_legend(TASK_NEWBIE_01, 18);
		who->add_exp(80);
		who->add_potential(5);
		send_user(who,"%c%s",';',"破损的铁锹 经验 80 潜能 5");
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,9,"" );		
		break;
	case 8 :		
		if (!who->get_legend(TASK_NEWBIE_01, 19) )
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    前段日子上山打猎，不小心碰上一群土匪。那些土匪将我身上值钱的东西全部抢走了，幸好这时卫队长巡山，将我被抢的物品全部追回来。为了答谢卫队长，我特意将自己打的猎物卖成酒钱，打算送给他。你能替我送给他吗？他就在村子的东南最尽头处，和老村长家在一起。\n"ESC"接受\ntalk %x# welcome.9\n"ESC"离开",me->get_name(),getoid(me)));			
		break;
	case 9:
		if ( who->get_legend(TASK_NEWBIE_01, 19) )
			return ;
		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
		item = new( "/item/98/9884" );
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
		who->set_legend(TASK_NEWBIE_01, 19);
		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,10,"牛二报恩" );
		send_user( who, "%c%s", '!', "你接受了"HIY"牛二报恩"NOR"任务");		
		break;
//	case 10:
//		if ( who->get_level() < 5 )
//			return ;
//		if (!who->get_legend(TASK_NEWBIE_01, 21) )
//			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    我从小打猎习武，就是为了把身体练的强壮，好等成年以后去拜师学艺。好不容易等我成年以后，去找村口的那个门派向导让他帮我介绍个师傅。结果……哎～他说我年纪太大，习武之人要从小开始打基础。说什么也不肯帮我介绍师傅。拜师学得一身武艺这可是我一生的夙愿。你愿意帮我去说说情吗？听说他喜欢下棋，这是一张棋谱你带我送给他。\n"ESC"接受\ntalk %x# welcome.11\n"ESC"离开",me->get_name(),getoid(me)));			
//		else if (!who->get_legend(TASK_NEWBIE_01, 22))
//			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    拜师学艺，这可是我一生的夙愿啊！还望%s能尽心尽力帮我完成这件事。\n"ESC"离开",me->get_name(),NPC_RANK_D->get_respect_2(who)));			
//		
//		break;
//	case 11:
//		if ( who->get_level() < 5 || who->get_legend(TASK_NEWBIE_01, 21) )
//			return ;
//		item = new( "/item/98/9885" );
//		if ( !item )
//			return ;
//                p =item->move(who, -1);
//                if ( p == 0 )
//                {
//                	destruct(item); 
//                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
//                	return ;
//                }	
//                item->add_to_user(p);
//		who->set_legend(TASK_NEWBIE_01, 21);
//		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
//		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,11,"牛二的苦恼" );
//		send_user( who, "%c%s", '!', "你接受了"HIY"牛二的苦恼"NOR"任务");			
//		break;
        }
}

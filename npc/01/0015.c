
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5403; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name( "Trí Tuệ Lão Nhân" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
        setup();
}
// 函数：对话处理
void do_look( object who )
{
        string tmp = "";
        string tmp214 = "";
        object item;

	if ( (who->get_legend(TASK_41, 4) && !who->get_legend(TASK_41, 5)) || (who->get_legend(TASK_41, 5) && !who->get_legend(TASK_41, 6)) || (who->get_legend(TASK_41, 7) && !who->get_legend(TASK_41, 8)) || (who->get_legend(TASK_41, 8) && !who->get_legend(TASK_41, 9)))
        	tmp = sprintf(ESC"疑难杂症\ntalk %x# welcome.3\n",getoid(this_object()));

	if( objectp( item = present("神秘的种子", who, 1, MAX_CARRY) ) && who->get_quest("valentine.flag") == 4)
        	tmp = sprintf(ESC"爱情之花\ntalk %x# welcome.214\n",getoid(this_object()));

	send_user(who,"%c%s",':',sprintf("%s:\n    你知道吗？\n    体魄决定玩家的最大气血值的属性。体魄越好，玩家角色的最大气血值也越高。\n    精神决定玩家的最大法力值与法术的攻击力、防御力。精神越高，玩家角色的最大法力值也越高，法术攻击力与防御力也越强。\n    耐力决定玩家的物理防御力。耐力越大，玩家角色所具有的物理防御力也越高。是物理门派重要的属性之一。\n"ESC"继续\ntalk %x# welcome.1\n" +
	tmp + tmp214 +
	ESC"离开",get_name(),getoid(this_object())));
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,p,i;
	object who,item;
	string file,cWord="";
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        	case 1:
        		if ( who->get_legend(TASK_NEWBIE_02, 10) && !who->get_legend(TASK_NEWBIE_02, 11) )
				send_user(who,"%c%s",':',sprintf("%s:\n    力量决定玩家的物理攻击力。力量越高，玩家角色所具有的物理攻击力也越高。是禁卫军玩家不可忽视的属性。\n    敏捷闪避对方的攻击，并且影响攻击的命中率。敏捷越高，玩家角色所能躲避的攻击也越多，而且更容易攻击到敌人，减少攻击落空的几率。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
			else
				send_user(who,"%c%s",':',sprintf("%s:\n    力量决定玩家的物理攻击力。力量越高，玩家角色所具有的物理攻击力也越高。是禁卫军玩家不可忽视的属性。\n    敏捷越高，闪避对方攻击的几率会越高，并且敏捷属性还影响了每次攻击的暴击率。\n"ESC"离开",me->get_name(),getoid(me)));
        		break;
        	case 2:
        		if ( who->get_legend(TASK_NEWBIE_02, 10) && !who->get_legend(TASK_NEWBIE_02, 11) )
        		{
        			who->set_legend(TASK_NEWBIE_02, 11);
				who->add_exp(280);
				who->add_cash(1500);
				send_user(who,"%c%s",';',"找智慧老人谈谈 经验 280 金钱 1500");
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,17,"" );
        		}
        		break;
	        case 3: 
			if ( who->get_legend(TASK_41, 4) && !who->get_legend(TASK_41, 5) )
				send_user(who,"%c%s",':',sprintf("%s:\n    根据你描述的情况来看，村民们根本就不是生病，而是中毒了，你待我想想解毒的方法，再来找我吧。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),getoid(me)));
			else if ( who->get_legend(TASK_41, 5) && !who->get_legend(TASK_41, 6) )
				send_user(who,"%c%s",':',sprintf("%s:\n    据我估计，村民们应该是中了一种名为软骨散的毒，而毒源就是村后的那口水井，中毒的村民都是饮用过村后那口水井里的水后，才出现此症状的。\n    解此毒必需雄黄散，并且要与其他药物配合才有疗效，这药配好后不止要给村民们服下，还得洒入水井中作解毒用。\n    你先去找来雄黄散吧，我听说这一带的小山鸡身上都带有雄黄散。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),getoid(me)));
			else if ( who->get_legend(TASK_41, 7) && !who->get_legend(TASK_41, 8) )
				send_user(who,"%c%s",':',sprintf("%s:\n    我配药还需要一定的时间，你过会儿再来找我拿药吧！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开",me->get_name(),getoid(me)));
			else if ( who->get_legend(TASK_41, 8) && !who->get_legend(TASK_41, 9) )
				send_user(who,"%c%s",':',sprintf("%s:\n    你将这包解药拿给村长，并且告诉他，千万要记得叮嘱村里人最近两天不要去村后的那口水井里打水饮用，记得要将解药拿给村民服用，还要将解药洒到水井内，这样才能治标又治本！\n    还有一件事，你千万不得声张，你告诉老村长，我疑心是有人在水井里下了毒，还想请村长查明此事，揪出下毒的狠心之人。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开",me->get_name(),getoid(me)));

	        	break;
	        case 4:
			if ( who->get_legend(TASK_41, 4) && !who->get_legend(TASK_41, 5) )
	        	{
				who->set_legend(TASK_41,5);
				who->add_exp(150);
				who->add_potential(20);
				send_user(who,"%c%s",';',"疑难杂症（1） 经验 150 潜能 20");
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,27,"" );
				me->do_welcome(3);
        		}
	        	break;
		case 5:
	        	if ( who->get_legend(TASK_41, 5) && !who->get_legend(TASK_41, 6) )
	        	{
	        		who->set_legend(TASK_41,6);
				send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,28,"疑难杂症（2）" );
				send_user( who, "%c%s", '!', "得到任务 "HIY"疑难杂症（2）");
	        	}
	        	break;
		case 6:
			if( who->get_legend(TASK_41, 7) && !who->get_legend(TASK_41, 8) )
			{
				if (TASK_LEGEND_D->check_task_item(who,"雄黄散",1) != 1 )
	        			return;
//				TASK_LEGEND_D->give_item(who,"item/91/9100",5);
				who->add_exp(300);
				who->add_potential(30);
				who->add_cash(1800);
				who->set_legend(TASK_41, 8);
				send_user(who,"%c%s",';',"疑难杂症（2） 经验 300 潜能 30 金钱 1800");			
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,28,"" );
			}
			break;		        	
		case 7:
	        	if ( who->get_legend(TASK_41, 8) && !who->get_legend(TASK_41, 9) )
	        	{
	        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
	        			return ;
				TASK_LEGEND_D->give_item(who,"item/98/0200",1);
	        		who->set_legend(TASK_41,9);
				send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,29,"疑难杂症（3）" );
				send_user( who, "%c%s", '!', "得到任务 "HIY"疑难杂症（3）");
	        	}
	        	break;
		case 214:
			if( who->get_quest("valentine.flag") == 4)
			{

			send_user(who,"%c%s",':',sprintf("%s:\n    我明白你的意思，小伙子！可是想让这神秘种子开出爱情之花可不是一件轻松的事啊，他需要你用心血来浇灌，你愿意吗？\n"ESC"愿意\ntalk %x# welcome.215\n"ESC"不愿意",me->get_name(),getoid(me)));

			}
	        	break;
		case 215:
			if( who->get_quest("valentine.flag") == 4)
			{
			if(USER_INVENTORY_D->count_empty_carry(who) < 3 )
			{
			        send_user(who,"%c%s",';',"您身上没有足够空位！建议您空出三格来放置情人节礼物。");
        			return;
			}
			if( objectp( item = present("神秘的种子", who, 1, MAX_CARRY) ) )
			{
        			item->remove_from_user();
        			destruct(item); 
			}
                        switch( random(4) )
                        {
                               case 0 : file = "/item/04/0426";  break;
                               case 1 : file = "/item/04/0427";  break;
                               case 2 : file = "/item/04/0428";  break;
                               case 3 : file = "/item/04/0429";  break;
                              default : break;
                        }
                        for (i=0;i<3;i++)
                        {
				item = new (file);    
                        	if ( item )
				{	
					p = item->move(who,-1);
					item->add_to_user(p);			
				}	
			}
        		who->set_hp(1);
			who->set_quest( "valentine.flag", 10 );
			who->add_exp(500);
			who->add_potential(10);
	        	send_user( who, "%c%s", '!', "得到"HIR"玫瑰"NOR"三枝");
	        	write_user(who,ECHO"因为你的真诚与勇气，得到了情人节礼物"+item->get_name()+"三枝，赶紧送给心爱的她吧！");
	        	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_VALENTINE,"" ); 
	        	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_VALENTINE,4,"" ); 		                        
			}
	        	break;
	}
}
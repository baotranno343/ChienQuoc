#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>
#include <task.h>

inherit OFFICER;
inherit SAVE_F;
int iStart1,iFinish1,year1,year2,mon1,mon2,day1,day2;
// 函数：获取人物造型
int get_char_picid() { return 5505; }
void do_welcome(string arg);

string get_save_file()	{ return "data/51cuanyue"SAVE_EXTENSION;}

//检查日期
void check_date(object player)
{
	mixed *mixTime;
	mixTime = localtime(time());
	if (mixTime[TIME_YDAY]!=player->get_save_2("51cuanye.day"))
	{
		player->set_save_2("51cuanye.day", mixTime[TIME_YDAY]);	
	        player->set_save_2("51cuanye.count", 0);
	}
	if (mixTime[TIME_YDAY]!=player->get_save_2("51tiandao.day"))
	{
		player->set_save_2("51tiandao.day", mixTime[TIME_YDAY]);	
	        player->set_save_2("51tiandao.count", 0);
	}		
}

// 函数：构造处理
void create()
{
	restore();
        set_name("五一活动指派员");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
	set("mpLegend",([0:({32}),]));
	if ( !iStart1 || !iFinish1 )
	{
		iStart1 = mktime(2007,5,1,0,0,0);	
		iFinish1 = mktime(2007,5,8,0,0,0);	
	}
        setup();
        if ( !clonep(this_object()) )
        	return ;
        if (MAIN_D->get_host_type()==2)		//台湾除外
        	call_out("go_there",2);
}

void do_look(object who) { __FILE__->do_look_call(this_object(),who); }
void do_look_call(object me,object who)
{
	int id = getoid(me);
	int iTime=time();
	
	if (MAIN_D->get_host_type()==2)
		return ;
	if ( iTime > iStart1 && iTime < iFinish1 )
	{
		if ( who->get_save_2("51cuanye.time") )	
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    五一七天乐，战国乐翻天！\n    五一期间我们为玩家准备了丰富的线上活动，参与活动领取“战国劳动奖章”，就有机会兑换金色装备、特殊称谓等珍贵奖品！\n    三大活动将伴您共度黄金周，活动详细信息请查询http:/""/zg.mop.com活动专区。\n"ESC"天道酬勤\ntalk %x# welcome.2\n"ESC"战国劳动奖章兑奖\ntalk %x# welcome.5",me->get_name(),id,id));
		else
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    五一七天乐，战国乐翻天！\n    五一期间我们为玩家准备了丰富的线上活动，参与活动领取“战国劳动奖章”，就有机会兑换金色装备、特殊称谓等珍贵奖品！\n    三大活动将伴您共度黄金周，活动详细信息请查询http:/""/zg.mop.com活动专区。\n"ESC"极限穿越\ntalk %x# welcome.0\n"ESC"天道酬勤\ntalk %x# welcome.2\n"ESC"战国劳动奖章兑奖\ntalk %x# welcome.5",me->get_name(),id,id,id));
	}
	else
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    五一七天乐，战国乐翻天！\n    五一期间我们为玩家准备了丰富的线上活动，参与活动领取“战国劳动奖章”，就有机会兑换金色装备、特殊称谓等珍贵奖品！\n    三大活动将伴您共度黄金周，活动详细信息请查询http:/""/zg.mop.com活动专区。\n"ESC"战国劳动奖章兑奖\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),id));
	
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag, p,i,size,id,iTime,count,amount,count1,rate;
       	object who, item,*nTeam,*inv;
        string *nTmp,tmp;
	string *nFamily = ({"Đào Hoa Nguyên","Thục Sơn","Cấm Vệ Quân","Đường Môn","Mao Sơn","Côn Luân Sơn","Vân Mộng Cốc"});
	 
	if (MAIN_D->get_host_type()==2)
		return ;
		
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 0:
        	if ( who->get_save_2("51cuanye.time") )
        		return ;
        	if ( time() < iStart1 )
        	{
        		return ;	
        	}
        	if ( time() > iFinish1 )
        	{
        		return ;	
        	}
		if ( !who->is_leader() )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你不是队长，不能接受任务！\n"ESC"离开",me->get_name(),));
			return ;
		}
		if ( who->get_level() >= 30 )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你的等级似乎不太适合来做这件事情噢～不过你可以考虑帮助低级玩家来完成这个任务！\n"ESC"离开",me->get_name(),));
			return ;
		}
		if ( who->get_save_2("51cuanye.count") == 0 )
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    30级以下的玩家注意了！这个任务可是特别为你们设计的哦～不过你们想要顺利到达传说中的东海岛可离不开高级玩家的帮助，还在犹豫什么，赶紧组上他们来接任务吧！活动详情请查询http:/""/zg.mop.com活动专区。\n    拿好这张“极限穿越证明书”，去交给东海岛东北方的极限穿越审查官，你就能拿到他给你的奖励了！\n    这个任务每天可重复领取5次哦～\n"ESC"领取任务\ntalk %x# welcome.1\n"ESC"离开",me->get_name(),id,));
		else
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    30级以下的玩家注意了！这个任务可是特别为你们设计的哦～不过你们想要顺利到达传说中的东海岛可离不开高级玩家的帮助，还在犹豫什么，赶紧组上他们来接任务吧！活动详情请查询http:/""/zg.mop.com活动专区。\n    拿好这张“极限穿越证明书”，去交给东海岛东北方的极限穿越审查官，你就能拿到他给你的奖励了！\n    这个任务你还可以做%d次哦～\n"ESC"领取任务\ntalk %x# welcome.1\n"ESC"离开",me->get_name(),5-who->get_save_2("51cuanye.count"),id,));
		
        	break;
        case 1:
        	if ( who->get_save_2("51cuanye.time") )
        		return ;
        	if ( time() < iStart1 )
        	{
        		return ;	
        	}
        	if ( time() > iFinish1 )
        	{
        		return ;	
        	}
		if ( !who->is_leader() )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你不是队长，不能接受任务！\n"ESC"离开",me->get_name(),));
			return ;
		}
		if ( who->get_level() >= 30 )
       		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你的等级似乎不太适合来做这件事情噢～不过你可以考虑帮助低级玩家来完成这个任务！\n"ESC"离开",me->get_name(),));
			return ;
		}
		nTeam = who->get_team();
		nTeam -= ({0});
		size = sizeof(nTeam);
		if ( !is_god(who) && size < 2 )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你单枪匹马就想去东海岛？别做梦了，还是多叫几个人再来找我吧！\n"ESC"离开",me->get_name(),));
			return ;
		}
		if ( USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的东西太多了，请清理一下再来接任务！\n"ESC"离开",me->get_name(),));
			return ;
		}
		for(i=0;i<size;i++)
		{
			if ( !objectp(nTeam[i]) )
				continue;
			if ( !inside_screen_2(nTeam[i],me) )
				continue;
			if ( nTeam[i]->get_save_2("51cuanye.time") )
			{
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    队伍中的"HIR+nTeam[i]->get_name()+NOR "玩家已经领取了极限穿越任务。\n"ESC"离开",me->get_name(),));
				return ;
			}
			check_date(nTeam[i]);
			if ( nTeam[i]->get_save_2("51cuanye.count") >= 5 )
			{
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    每天只可领取5次该任务，"HIR+nTeam[i]->get_name()+NOR "今天的任务数量已达到。\n"ESC"离开",me->get_name(),));
				return ;
			}
		}
		item = new("item/04/0439");
		if ( !item )
			return ;
		p = item->move(who,-1);
		item->add_to_user(p);
		iTime = time();

		for(i=0;i<size;i++)
		{
			if ( !objectp(nTeam[i]) )
				continue;
			if ( !inside_screen_2(nTeam[i],me) )
				continue;
			nTeam[i]->set_save_2("51cuanye.time",iTime);
			nTeam[i]->add_save_2("51cuanye.count",1);
	                send_user( nTeam[i], "%c%c%c%w%s", 0x51, 1, 1,TID_WUYIHUODONG,"五一活动" );     
	                send_user( nTeam[i], "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,1,"极限穿越" );                  		
	                send_user( nTeam[i], "%c%s",';',"您和您的队友已经成功领取了“极限穿越”任务，赶紧出发吧！");
		}
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你的您已经领取了极限穿越的任务，现在就和您的队友一起去寻找传说中的东海岛吧！\n    越快到达目的地，拿到的奖励会越多！\n"ESC"离开",me->get_name(),));
        	break;
        case 2:
        	if ( time() < iStart1 )
        	{
        		return ;	
        	}
        	if ( time() > iFinish1 )
        	{
        		return ;	
        	}
        	if ( !who->get_save_2("51tiandao.accept") )	//没接
       		{
			check_date(who);
			if ( who->get_save_2("51tiandao.count") == 0 )
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    一分耕耘，一分收获，只要辛苦劳动就会收获丰硕的果实，天道酬勤就是给勤劳的你专门设计的任务，完成任务就可以获得神秘的“战国劳动奖章”。\n    任务很简单，只要你拿着这块试炼石，去杀满100只高于自己等级5级之内的怪，你就可以回来找我领取奖励了。这个任务每天可重复领取5次哦～\n    活动详细信息请查询http:/""/zg.mop.com活动专区。\n"ESC"领取任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),id,));
			else
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    一分耕耘，一分收获，只要辛苦劳动就会收获丰硕的果实，天道酬勤就是给勤劳的你专门设计的任务，完成任务就可以获得神秘的“战国劳动奖章”。\n    任务很简单，只要你拿着这块试炼石，去杀满100只高于自己等级5级之内的怪，你就可以回来找我领取奖励了。这个任务你还可以做%d次哦～\n    活动详细信息请查询http:/""/zg.mop.com活动专区。\n"ESC"领取任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),5-who->get_save_2("51tiandao.count"),id,));
			return ;
		}
		else if ( who->get_save_2("51tiandao.amount") >= 100 )
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    不赖不赖！这三个战国劳动奖章归你了！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),id,));
        	else
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    现在找我可拿不到奖励哦～做完了该做的事情再回来找我吧～\n"ESC"离开",me->get_name(),));
        	break;
        case 3:
        	if ( time() < iStart1 )
        	{
        		return ;	
        	}
        	if ( time() > iFinish1 )
        	{
        		return ;	
        	}
        	if ( who->get_save_2("51tiandao.accept") )
        		return ;
		check_date(who);
		if ( who->get_save_2("51tiandao.count") >= 5 )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    每天只可领取5次该任务，您今天的任务数量已达到。\n"ESC"离开",me->get_name(),));
			return ;
		}
		if ( USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的东西太多了，请清理一下再来接任务！\n"ESC"离开",me->get_name(),));
			return ;
		}
		item = new("item/04/0441");
		p = item->move(who,-1);
		item->add_to_user(p);
		who->set_save_2("51tiandao.accept",time());
		who->add_save_2("51tiandao.count",1);
                send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_WUYIHUODONG,"五一活动" );     
                send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,2,"天道酬勤" );                  		
        	break;
        case 4:
        	if ( who->get_save_2("51tiandao.amount") < 100 )
        		return ;
		if ( !objectp(item = present("试炼石", who, 1, MAX_CARRY)) )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你的试炼石呢？\n"ESC"离开",me->get_name(),));
			return ;
		}     
		item->remove_from_user();
		destruct(item);
        	who->delete_save_2("51tiandao.amount");
        	who->delete_save_2("51tiandao.accept");
        	item = new("item/04/0438");
		item->set_amount(3);
		p = item->move(who,-1);
		item->add_to_user(p);
                send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_WUYIHUODONG,2,"" );                  		
        	break;
        case 5:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    不同数量的战国劳动奖章可以换取不同的奖品，数量越多，奖品越珍贵。\n"ESC"1枚奖章兑换奖品\ntalk %x# welcome.1001\n"ESC"5枚奖章兑换奖品\ntalk %x# welcome.1005\n"ESC"20枚奖章兑换奖品\ntalk %x# welcome.1020\n"ESC"50枚奖章兑换奖品\ntalk %x# welcome.1050\n"ESC"100枚奖章兑换奖品\ntalk %x# welcome.1100\n"ESC"300枚奖章兑换奖品\ntalk %x# welcome.1300\n"ESC"30枚奖章兑换一级称号\ntalk %x# welcome.2030\n"ESC"60枚奖章兑换二级称号\ntalk %x# welcome.2060\n"ESC"120枚奖章兑换三级称号\ntalk %x# welcome.2120\n"ESC"离开",me->get_name(),id,id,id,id,id,id,id,id,id,));
        	break;
        case 1001:
        case 1005:
        case 1020:
        case 1050:
        case 1100:
        case 1300:
		if ( USER_INVENTORY_D->count_empty_carry(who) < 2 )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的东西好像太多了，清理一下再来兑换奖品吧～\n"ESC"离开",me->get_name(),));
			return ;
		}
        	count = flag - 1000;
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你确定要用%d枚战国劳动奖章来兑换奖品吗？\n"ESC"确定\ntalk %x# welcome.%d\n"ESC"离开",me->get_name(),count,id, 2000+flag));
        	
        	break;
        case 2030:
        case 2060:
        case 2120:
        	count = flag - 2000;
        	if ( count == 30 )
        		tmp = "劳动最光荣";
        	else if ( count == 60 )
        		tmp = "勤劳的小蜜蜂";
        	else if ( count == 120 )
        		tmp = "爆强的战国劳模";
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你确定要用%d枚战国劳动奖章来兑换"HIR"“%s”"NOR "的称号吗？\n"ESC"确定\ntalk %x# welcome.%d\n"ESC"离开",me->get_name(),count,tmp,id, 2000+flag));
        	break;
        case 4030:
        case 4060:
        case 4120:
        	count = flag - 4000;
        	if ( count == 30 )
        		tmp = "A003";
        	else if ( count == 60 )
        		tmp = "A004";
        	else if ( count == 120 )
        		tmp = "A005";
		if ( who->have_title(tmp) )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你已经有这样的称号了！\n"ESC"离开",me->get_name(),));
			return ;
		} 
        	inv = all_inventory(who, 1, MAX_CARRY);
        	for(i=0,size=sizeof(inv);i<size;i++)
		{
			if ( !objectp(inv[i]) )
				continue;
			if ( inv[i]->get_name() != "战国劳动奖章" )
				continue;
			amount += inv[i]->get_amount();		
		}
		if ( amount < count )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    您身上的战国劳动奖章数量不足%d个，建议您多做几次任务后再来找我吧！\n"ESC"离开",me->get_name(),count));
			return ;	
		}
		for(i=0,size=sizeof(inv);i<size;i++)
		{
			if ( !objectp(inv[i]) )
				continue;
			if ( inv[i]->get_name() != "战国劳动奖章" )
				continue;
			amount = inv[i]->get_amount();
			if ( count >= amount )
			{
				inv[i]->remove_from_user();
				destruct(inv[i]);
				count -= amount;
			}
			else
			{
				inv[i]->add_amount(-count);
				count = 0;	
			}
			if ( count <= 0 )
				break;
		}
		who->add_title(tmp);
		who->show_title(tmp);
		break;
        case 3001:
        case 3005:
        case 3020:
        case 3050:
        case 3100:
        case 3300:
        	if ( USER_INVENTORY_D->count_empty_carry(who) < 2 )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的东西好像太多了，清理一下再来兑换奖品吧～\n"ESC"离开",me->get_name(),));
			return ;
		}
        	count = flag - 3000;
		count1 = count;
        	inv = all_inventory(who, 1, MAX_CARRY);
        	for(i=0,size=sizeof(inv);i<size;i++)
		{
			if ( !objectp(inv[i]) )
				continue;
			if ( inv[i]->get_name() != "战国劳动奖章" )
				continue;
			amount += inv[i]->get_amount();		
		}
		if ( amount < count )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    您身上的战国劳动奖章数量不足%d个，建议您多做几次任务后再来找我吧！\n"ESC"离开",me->get_name(),count));
			return ;	
		}
		for(i=0,size=sizeof(inv);i<size;i++)
		{
			if ( !objectp(inv[i]) )
				continue;
			if ( inv[i]->get_name() != "战国劳动奖章" )
				continue;
			amount = inv[i]->get_amount();
			if ( count >= amount )
			{
				inv[i]->remove_from_user();
				destruct(inv[i]);
				count -= amount;
			}
			else
			{
				inv[i]->add_amount(-count);
				count = 0;	
			}
			if ( count <= 0 )
				break;
		}
		count = count1;
		rate = random(10000);
		if ( count == 1 )
		{
			if ( rate < 3500 )
				item = new("item/91/9100");
			else if ( rate < 7000 )
				item = new("item/91/9110");
			else if ( rate < 8500 )
				item = new("item/91/9101");
			else
				item = new("item/91/9111");
			item->set_amount(5);
			p = item->move(who,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",';',sprintf("您用%d枚战国劳动奖章兑换了%s",count,item->get_name()));
		}
		else if ( count == 5 )
		{
			if ( rate < 2500 )
			{
				item = new("item/91/9100");
				item->set_amount(10);
			}
			else if ( rate < 5000 )
			{
				item = new("item/91/9110");
				item->set_amount(10);
			}
			else if ( rate < 6500 )
			{
				item = new("item/91/9101");
				item->set_amount(10);
			}
			else if ( rate < 8000 )
			{
				item = new("item/91/9111");
				item->set_amount(10);
			}
			else if ( rate < 9000 )
			{
				item = new("item/std/6003");
			}			
			else 
			{
				item = new("item/std/8000");
			}			
			p = item->move(who,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",';',sprintf("您用%d枚战国劳动奖章兑换了%s",count,item->get_name()));
		}
		else if ( count == 20 )
		{
			if ( rate < 2500 )
			{
				item = new("item/91/9101");
				item->set_amount(10);
			}
			else if ( rate < 5000 )
			{
				item = new("item/91/9111");
				item->set_amount(10);
			}
			else if ( rate < 7000 )
			{
				item = new("item/std/6003");
			}			
			else if ( rate < 9000 )
			{
				item = new("item/std/8000");
			}
			else if ( rate < 9800 )
			{
				item = new("item/44/4488");
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}
			else
			{
				nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,50,HEAD_TYPE+random(6));
	        		tmp = nTmp[random(sizeof(nTmp))];
	        		if ( !stringp(tmp) )
	        			return ;
	        		item = new(tmp);
	        		ITEM_EQUIP_D->init_equip_prop_1(item);
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}			
			p = item->move(who,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",';',sprintf("您用%d枚战国劳动奖章兑换了%s",count,item->get_name()));
		}
		else if ( count == 50 )
		{
			if ( rate < 3500 )
			{
				item = new("item/std/8000");
			}
			else if ( rate < 6500 )
			{
				item = new("item/44/4488");
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}
			else if ( rate < 9000 )
			{
				nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,50,HEAD_TYPE+random(6));
	        		tmp = nTmp[random(sizeof(nTmp))];
	        		if ( !stringp(tmp) )
	        			return ;
	        		item = new(tmp);
	        		ITEM_EQUIP_D->init_equip_prop_1(item);
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}
			else
			{
				item = new(sprintf("item/std/%d",8001+random(4)));	
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}			
			p = item->move(who,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",';',sprintf("您用%d枚战国劳动奖章兑换了%s",count,item->get_name()));
		}
		else if ( count == 100 )
		{
			if ( rate < 3500 )
			{
				item = new("item/44/4488");
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}
			else if ( rate < 6500 )
			{
				nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,50,HEAD_TYPE+random(6));
	        		tmp = nTmp[random(sizeof(nTmp))];
	        		if ( !stringp(tmp) )
	        			return ;
	        		item = new(tmp);
	        		ITEM_EQUIP_D->init_equip_prop_1(item);
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}
			else if ( rate < 8500 )
			{
				item = new(sprintf("item/std/%d",8001+random(4)));	
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}	
			else
			{
				item = new("item/91/9167");
				p = item->move(who,-1);
				item->add_to_user(p);
				item = new("item/91/9167");
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}		
			p = item->move(who,-1);
			if ( p )
				item->add_to_user(p);
			send_user(who,"%c%s",';',sprintf("您用%d枚战国劳动奖章兑换了%s",count,item->get_name()));
		}
		else if ( count == 300 )
		{
			if ( rate < 6000 )
			{
				item = new(sprintf("item/std/%d",8001+random(4)));	
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}	
			else if ( rate < 9700 )
			{
				item = new("item/91/9167");
				p = item->move(who,-1);
				item->add_to_user(p);
				item = new("item/91/9167");
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}
			else if ( rate < 9800 )
			{
				nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),who->get_level(),WEAPON_TYPE);
	        		tmp = nTmp[random(sizeof(nTmp))];
	        		if ( !stringp(tmp) )
	        			return ;
	        		item = new(tmp);
	        		ITEM_EQUIP_D->init_equip_prop_3(item);
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}
			else 
			{
				nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),who->get_level(),ARMOR_TYPE);
	        		tmp = nTmp[random(sizeof(nTmp))];
	        		if ( !stringp(tmp) )
	        			return ;
	        		item = new(tmp);
	        		ITEM_EQUIP_D->init_equip_prop_3(item);
				CHAT_D->sys_channel(0,sprintf(HIR"恭喜%s玩家获得奖品%s",who->get_name(),item->get_name()));
			}		
			p = item->move(who,-1);
			if ( p )
				item->add_to_user(p);
			send_user(who,"%c%s",';',sprintf("您用%d枚战国劳动奖章兑换了%s",count,item->get_name()));
		}
        	break;
        	
	}

}

void go_there()
{
	object me=this_object();
	
	me->add_to_scene(802,78,43,2);
}

int set_open(object who,string arg)
{
	int date1,date2;
	if ( sscanf(arg ,"%d-%d",date1,date2) != 2 )
	{
		send_user(who,"%c%s",'!',"错误的格式！");	
		return 0;
	}
	year1 = date1 /10000;
	mon1 = date1 % 10000 / 100;
	day1 = date1 % 10000 % 100;
	year2 = date2 /10000;
	mon2 = date2 % 10000 / 100;
	day2 = date2 % 10000 % 100;
	if ( !year1 || !mon1 || !day1 || !year2 || !mon2 || !day2 )
	{
		send_user(who,"%c%s",'!',"错误的时间！");	
		return 0;
	}
	iStart1 = mktime(year1,mon1,day1,0,0,0);	
	iFinish1 = mktime(year2,mon2,day2,0,0,0);		
	if ( iStart1 > iFinish1 )
	{
		send_user(who,"%c%s",'!',"错误的时间！！");	
		return 0;
	}
	tell_user(who,"活动开启：%s！",arg);	
	send_user(who,"%c%s",'!',"51活动开启！");	
	save();
	return 1;
}

int set_close(object who)
{
	iStart1 = 0;	
	iFinish1 = 0;		
	send_user(who,"%c%s",'!',"51活动关闭！");	
	save();
	return 1;	
}
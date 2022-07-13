#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>

inherit OFFICER;
mapping mpXinrenwang=([]);
mapping mpLifeskill=([]);
int iStart,iFinish,iMopTime;
int host_type;

// 函数：获取人物造型
int get_char_picid() { return 6010; }
void do_bonus();
void do_welcome(string arg);
void read_renwang();
void read_lifeskill();

// 函数：构造处理
void create()
{
        set_name("Như Ý Tiên Tử");
        set_2( "talk", ([
                 "bonus"         : (: do_bonus :),
                 "welcome"         : (: do_welcome :),
        ]) );
	mpXinrenwang = ([]);
	read_renwang();
	read_lifeskill();
	iStart = mktime(2006,10,19,18,0,0);	
	iFinish = mktime(2006,10,26,18,0,0);
	iMopTime = mktime(2007,2,10,0,0,0);
	host_type = MAIN_D->get_host_type();
        setup();
}

void do_look(object who)
{
	int id = getoid(this_object()),iTime;
	
	if ( host_type == 4 && time() > iMopTime )	//猫扑
		return ;
	if ( host_type == 2)
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    您好！我是如意仙子。欢迎您来到大话江湖的世界，为了鼓励您的事业进取心，姐姐决定送给您一份礼物。\n"ESC"领取礼物\ntalk %x# welcome.4\n"ESC"离开",id));
	else if ( host_type == 4)
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    您好！我是如意仙子。欢迎您来到大话战国的世界，为了鼓励您的事业进取心，姐姐决定送给您一份礼物。\n"ESC"领取礼物\ntalk %x# welcome.4\n"ESC"离开",id));
	else		
		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    您好！我是新手使者。欢迎您来到大话战国发展，为了鼓励您的事业进取心，姐姐决定送给您一个新手大礼包。\n"ESC"领取如意礼包\ntalk %x# bonus\n"ESC"领取新人王礼包\ntalk %x# welcome.1\n"ESC"竞选技能大师称号\ntalk %x# welcome.2\n"ESC"领取第一帮礼包\ntalk %x# welcome.3\n"ESC"离开",id,id,id,id));
}

void do_bonus()
{
	int level,i,p;
	object who = this_player(),me=this_object(),item;

	if ( host_type == 4 && time() > iMopTime )	//猫扑
		return ;
	if ( host_type == 2 || host_type == 4 )	//台湾&猫扑
		return ;
	level = who->get_level();
	i = who->get_save("4testgift");
	if ( level/10 < i +1)
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    实在抱歉，您的等级还不足%d级，姐姐还不能送您礼物喔～",(i+1)*10));
		return ;
	}
	item = new("item/04/0405");
	if ( !item )
		return;
	p = item->move(who,-1);
	if ( !p )
	{
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    您身上的物品好像太多了点，先到商店清空一下您的包包，再来姐姐这里领取礼物吧～",);
		destruct(item);
		return ;
	}
	item->add_to_user(p);
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    丰富多彩的战国生活等着您呢，尽情去体验吧！等您到了%d级之后，姐姐会再送您一个大礼包的。",(i+2)*10));
	who->add_save("4testgift",1);
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}
//给予物品
int give_item(object who, string file,int iColor)
{
	int p;
	object item;
	
	item = new(file);
	if ( !item )
		return 0;
	if ( iColor == 1 )
		ITEM_EQUIP_D->init_equip_prop_1(item);
	p = item->move(who, -1);
	if( !p ) 	
	{
		destruct(item);
		return 0;	
	}
	item->add_to_user(p);
	return 1;
}
void do_welcome2( object me, string arg )
{
	int flag, p,iTime,i;
       	object who, item;
       	string name,file,*nTmp;
	mapping mpTitle = ([610:"Z007",620:"Z004",630:"Z005",640:"Z003",650:"Z013",660:"Z006",]);
	mixed *mxTime;    
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
	if ( host_type == 2 || host_type == 4 )	//台湾&猫扑
        {
		if ( host_type == 4 && time() > iMopTime )	//猫扑
			return ;
        	switch(flag)
		{
	        case 4:
	     	        if ( who->get_level() < 10 )
	     	        {
	     	        	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你现在的等级还不到10级，礼物还暂时不能送给你。等你10级之后再来找我吧。");
				return ;
			}
			if ( who->get_save("ruyi_gift") )
	        	{
	        		if ( host_type == 2 )
	        		{
	        			if ( who->get_save("ruyi_gift15") && who->get_save("ruyi_gift35") )
     	        				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    怎么？我给您的装备不错吧～希望您能在战国世界中渡过愉快的每一天。\n"ESC"离开"));
	        		  	else if ( !who->get_save("ruyi_gift15") )
	     	        			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    怎么？晶石的效果不错吧～精炼后的武器在消灭怪物之后的效率一定会更高。当你的等级到了15级之后再来吧，我还有礼物要送给你。\n"ESC"领取\ntalk %x# welcome.6\n"ESC"离开",getoid(me)));
					else if ( !who->get_save("ruyi_gift35") )
	     	        			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    当你的等级到了35级之后再来吧，我还有礼物要送给你。\n"ESC"领取\ntalk %x# welcome.11\n"ESC"离开",getoid(me)));
	        		}
	        		else
	     	        		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    怎么？晶石的效果不错吧～精炼后的武器在消灭怪物之后的效率一定会更高。");
				return ;
			}
			send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    到十级了，对武器装备都会有不同的要求了，如意仙子我决定送你12颗可以给武器装备附加属性的晶石，如果你按照从低到高的等级顺序，依次将这3颗晶石附加在武器或者防具上，你会看到它们的功能增强不少哦～记住，这些晶石只对20级以下的装备生效。\n"ESC"领取\ntalk %x# welcome.5\n"ESC"离开",getoid(me)));
	        	break;
	        case 5:
	        	if ( who->get_level() < 10 )
	        		return ;
	        	if ( who->get_save("ruyi_gift") )
	        		return ;
			if ( TASK_LEGEND_D->can_carry_amount(who,12) != 1 )
	        			return ;
			for(i=1;i<4;i++)
			{
				item = new("item/93/9343");
				item->set_level(i);
				p = item->move(who,-1);
				item->add_to_user(p);
			}
			for(i=1;i<4;i++)
			{
				item = new("item/93/9343");
				item->set_level(i);
				p = item->move(who,-1);
				item->add_to_user(p);
			}			
			for(i=1;i<4;i++)
			{
				item = new("item/93/9345");
				item->set_level(i);
				p = item->move(who,-1);
				item->add_to_user(p);
			}
			for(i=1;i<4;i++)
			{
				item = new("item/93/9345");
				item->set_level(i);
				p = item->move(who,-1);
				item->add_to_user(p);
			}
			send_user(who,"%c%s",'!',"恭喜你得到如意仙子的礼物");
			who->set_save("ruyi_gift",1);
	        	break; 

	        }
	        if ( host_type != 2 )
	        	return ;   
	        switch(flag)
		{
	        case 6:
	        	if ( who->get_save("ruyi_gift15") )
	        	{
	        		if ( !who->get_save("ruyi_gift35") )
	     	        		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    当你的等级到了35级之后再来我这里吧，还有礼物要送给你。\n"ESC"领取\ntalk %x# welcome.11\n"ESC"离开",getoid(me)));
	     	        	else
	     	        		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    怎么？我给您的装备不错吧～希望您能在战国世界中渡过愉快的每一天。\n"ESC"离开"));
	        		return ;
	        	}
	        	if ( who->get_level() < 15 )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你的等级还没达到15级，多多磨练之后再过来吧。");
				return ;
	        	}
	        	if ( (name=who->get_fam_name()) == "" )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你没有拜师哦，不能领取礼物。");
				return ;
	        	}	
	        	if ( name == "Thục Sơn" )
	        	{
	     	        	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    你希望得到什么武器？\n"ESC"刀\ntalk %x# welcome.7\n"ESC"剑\ntalk %x# welcome.8\n"ESC"离开",getoid(me),getoid(me)));
	        		return ;	
	        	}
	        	if ( name == "Cấm Vệ Quân" )
	        	{
	     	        	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    你希望得到什么武器？\n"ESC"枪\ntalk %x# welcome.9\n"ESC"棍\ntalk %x# welcome.10\n"ESC"离开",getoid(me),getoid(me)));
	        		return ;	
	        	}
	        	if ( USER_INVENTORY_D->count_empty_carry(who) < 3 )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你身上的物品过多，无法领取礼物，请清空后再领取。");
				return ;
	        	}
	        	switch(random(4))
	        	{
	        	default:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,HEAD_TYPE);
	        		break;	
	        	case 1:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,BOOTS_TYPE);
	        		break;	
	        	case 2:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,ARMOR_TYPE);
	        		break;
	        	case 3:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,WAIST_TYPE);
	        		break;
	        	}
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,NECK_TYPE);
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,WEAPON_TYPE);
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	who->set_save("ruyi_gift15",1);
	        	send_user(who,"%c%s",'!',"恭喜您得到了如意仙子的礼物。");
	        	break;    			
		case 7:
		case 8:
		case 9:
		case 10:

			if ( who->get_save("ruyi_gift15") )
	        		return ;
	        	name = who->get_fam_name();
	        	if ( name != "Thục Sơn" && name != "Cấm Vệ Quân" )
	        		return ;
	        	if ( who->get_level() < 15 )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你的等级还没达到15级，多多磨练之后再过来吧。");
				return ;
	        	}
	        	if ( USER_INVENTORY_D->count_empty_carry(who) < 3 )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你身上的物品过多，无法领取礼物，请清空后再领取。");
				return ;
	        	}
	        	switch(random(4))
	        	{
	        	default:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,HEAD_TYPE);
	        		break;	
	        	case 1:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,BOOTS_TYPE);
	        		break;	
	        	case 2:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,ARMOR_TYPE);
	        		break;
	        	case 3:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,WAIST_TYPE);
	        		break;
	        	}
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),20,NECK_TYPE);
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	if ( name == "Thục Sơn" )
	        	{
				if ( flag==7 )
					file = "item/72/1020";
				else
					file = "item/73/0020";
			}
			else if ( name == "Cấm Vệ Quân" )
	        	{
		        	if ( flag==9 )
					file = "item/74/1020";
				else
					file = "item/75/1020";
			}	
	        	give_item(who,file,1);	
	        	who->set_save("ruyi_gift15",1);
	        	send_user(who,"%c%s",'!',"恭喜您得到了如意仙子的礼物。");
			break;	
	        case 11:
	        	if ( who->get_save("ruyi_gift35") )
	        	{
     	        		send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    怎么？我给您的装备不错吧～希望您能在战国世界中渡过愉快的每一天。\n"ESC"离开"));
	        		return ;
	        	}
	        	if ( who->get_level() < 35 )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你的等级还没达到35级，多多磨练之后再过来吧。");
				return ;
	        	}
	        	if ( (name=who->get_fam_name()) == "" )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你没有拜师哦，不能领取礼物。");
				return ;
	        	}	
	        	if ( name == "Thục Sơn" )
	        	{
	     	        	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    你希望得到什么武器？\n"ESC"刀\ntalk %x# welcome.12\n"ESC"剑\ntalk %x# welcome.13\n"ESC"离开",getoid(me),getoid(me)));
	        		return ;	
	        	}
	        	if ( name == "Cấm Vệ Quân" )
	        	{
	     	        	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("Như Ý Tiên Tử：\n    你希望得到什么武器？\n"ESC"枪\ntalk %x# welcome.14\n"ESC"棍\ntalk %x# welcome.15\n"ESC"离开",getoid(me),getoid(me)));
	        		return ;	
	        	}
	        	if ( USER_INVENTORY_D->count_empty_carry(who) < 3 )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你身上的物品过多，无法领取礼物，请清空后再领取。");
				return ;
	        	}
	        	switch(random(4))
	        	{
	        	default:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,HEAD_TYPE);
	        		break;	
	        	case 1:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,BOOTS_TYPE);
	        		break;	
	        	case 2:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,ARMOR_TYPE);
	        		break;
	        	case 3:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,WAIST_TYPE);
	        		break;
	        	}
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,NECK_TYPE);
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,WEAPON_TYPE);
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	who->set_save("ruyi_gift35",1);
			send_user(who,"%c%s",'!',"恭喜您得到了如意仙子的礼物。");
	        	break;    			
		case 12:
		case 13:
		case 14:
		case 15:

			if ( who->get_save("ruyi_gift35") )
	        		return ;
	        	name = who->get_fam_name();
	        	if ( name != "Thục Sơn" && name != "Cấm Vệ Quân" )
	        		return ;
	        	if ( who->get_level() < 35 )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你的等级还没达到35级，多多磨练之后再过来吧。");
				return ;
	        	}
	        	if ( USER_INVENTORY_D->count_empty_carry(who) < 3 )
	        	{
				send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),"Như Ý Tiên Tử：\n    你身上的物品过多，无法领取礼物，请清空后再领取。");
				return ;
	        	}
	        	switch(random(4))
	        	{
	        	default:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,HEAD_TYPE);
	        		break;	
	        	case 1:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,BOOTS_TYPE);
	        		break;	
	        	case 2:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,ARMOR_TYPE);
	        		break;
	        	case 3:
	        		nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,WAIST_TYPE);
	        		break;
	        	}
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	nTmp = WEAPON_FILE->get_family_equip(name,who->get_gender(),40,NECK_TYPE);
	        	file = nTmp[random(sizeof(nTmp))];
	        	give_item(who,file,1);
	        	if ( name == "Thục Sơn" )
	        	{
				if ( flag==12 )
					file = "item/72/1040";
				else
					file = "item/73/0040";
			}
			else if ( name == "Cấm Vệ Quân" )
	        	{
		        	if ( flag==14 )
					file = "item/74/1040";
				else
					file = "item/75/1040";
			}	
	        	give_item(who,file,1);	
	        	who->set_save("ruyi_gift35",1);
	        	send_user(who,"%c%s",'!',"恭喜您得到了如意仙子的礼物。");
		} 
        	return ;
        }
        switch(flag)
        {
        case 1:
//		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    不要着急，活动的时间是从内测开始的9月18日至9月24日截止的。届时我们会根据你的技能等级和人物等级作出一个综合实力的评比。待活动时间结束，你觉得自己能成为等级最高的新人王再来找我吧～！");
		if ( !mpXinrenwang[who->get_id()] || mpXinrenwang[who->get_id()] != who->get_number() )
			return ;
		if ( who->get_save("xinrenwang") && !who->get_save("xinrenwang1") )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    经过这段时间的考验和你自己的努力，你已经成为万人瞩目的新人王，作为对你的鼓励，这是给你的大礼包～！");
			if ( TASK_LEGEND_D->can_carry_amount(who,2) != 1 )
	        			return ;
	        	name = BOOK_FILE->get_book_file();
			TASK_LEGEND_D->give_item(who,name,1);
			TASK_LEGEND_D->give_item(who,"item/08/0002",1);
			who->add_cash(10000);
			send_user(who,"%c%s",';',sprintf("%s 1 战国号角 1 10000金",name->get_name()));
			who->set_save("xinrenwang1",time());
			return;
		}
		if ( who->get_save("xinrenwang1") )
			return;
		if ( TASK_LEGEND_D->can_carry_amount(who,4) != 1 )
        			return ;
        	name = BOOK_FILE->get_book_file();
		TASK_LEGEND_D->give_item(who,name,1);
		TASK_LEGEND_D->give_item(who,"item/std/6002",1);
		TASK_LEGEND_D->give_item(who,"item/04/0405",1);
		TASK_LEGEND_D->give_item(who,"item/08/0002",1);
		who->add_cash(10000);
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    经过这段时间的考验和你自己的努力，你已经成为万人瞩目的新人王，作为对你的鼓励，这是给你的大礼包～！");
		send_user(who,"%c%s",';',sprintf("战国新人王称号 乾坤袋 1 大礼包 1 %s 1 战国号角 1 10000金",name->get_name()));
		CHAT_D->sys_channel(0,sprintf(HIG"恭喜"HIY"%s"HIG"成为战国新人王，期待"HIY"%s"HIG"在战国世界中有更加出色的表现！",who->get_name(),who->get_name()));
		who->set_save("xinrenwang1",time());
		who->add_title("Z002");
		
        	break;
        case 2:
//		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    不用着急，技能师的评比活动时间是从内测开始的9月18日至10月4日截止的。～！等活动时间结束了，你觉得自己能成为生活技能最高的技能师再来找我吧～！");
		if ( !mapp(mpLifeskill[who->get_number()])  )
			return ;
		p = mpLifeskill[who->get_number()][who->get_id()];
		name = mpTitle[p];
		if ( !name )
			return ;
		if ( who->have_title(name) )
			return;
		if ( TASK_LEGEND_D->can_carry_amount(who,2) != 1 )
        			return ;
		if ( !stringp(who->add_title(name)) )
			return ;
		TASK_LEGEND_D->give_item(who,"item/std/6002",1);
		TASK_LEGEND_D->give_item(who,"item/04/0405",1);		
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    经过这段时间的考验和你自己的努力，你已经成为万人瞩目的技能师，作为对你的鼓励，这是给你的大礼包～！");
        	break;
        case 3:
        	if (who->have_title("Z008")&&(who->get_save("firstorg")==0))
        	{
			if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY -2 )
			{
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    您身上的物品好像太多了点，先到商店清空一下您的包包，再来本仙子这里领取礼物吧～",);
				return;
			}
        		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    经过这段时间的考验和你自己的努力，你的帮派已经成为万人瞩目的第一帮，作为对你的鼓励，这是给你的大礼包～！\n"ESC"离开\nCLOSE\n");
        		who->set_save("firstorg", 1);
			item = new("item/04/0405");
			if ( !item )
				return;
			p = item->move(who,-1);
			item->add_to_user(p);
			item = new("item/std/6002");
			if ( !item )
				return;
			p = item->move(who,-1);
			item->add_to_user(p);
			name = who->get_org_name();
			who->add_cash(500000);
			send_user(who, "%c%s", ';', "您获得大礼包一个、乾坤袋一个以及50万金。");
			USER_D->user_channel(sprintf( HIY"恭喜%s成为天下第一帮，期待%s在战国世界中有更加出色的表现！", name, name));
        		return;
        	}
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    您希望得到“天下第一帮”的称号吗？这可是一条曲折艰辛的道路……不过姐姐从您的眼神中看出了你是一个坚强的人，相信无论遇到什么艰难险阻都无法动摇你的意志……\n    在你的等级达到40级之后，去拜访周国的神仙爷爷吧。他会告诉你一个关于“王之号角”的传送和更多关于帮派的事情，爷爷他一定会为你指出一条明路的。\n    姐姐会一直祝福您，祈祷您能早日得到达成天下第一帮的心愿，得到这份无比光荣的荣耀。");
        	break;
       
        case 99:
        	if (MAIN_D->get_host_type()!=2)
        		return ;
		iTime = time();
		if ( iTime < iStart || iTime > iFinish )
        		return ;
        	mxTime = localtime(iTime);
        	if ( who->get_save("bucang1018") == mxTime[TIME_YDAY] )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    您已经领取过了！");
        		return ;	
        	}
        	p = gone_time( who->get_login_time() );
		if ( p+ who->get_game_time()<who->get_double_time())
		{
		        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n     您的双倍经验时间还剩 %d 秒，不能领取\n"
		                ESC "关闭\nCLOSE\n", me->get_name(), who->get_double_time() - p - who->get_game_time() ) );			
			return;		               
		}
        	who->set_save("bucang1018",mxTime[TIME_YDAY]);
		who->set_double_time(p+ who->get_game_time()+3600);
		who->delete("tasklist");
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),"Như Ý Tiên Tử：\n    您领取了1个小时双倍经验时间，祝您游戏愉快！");
		break;
        }

}
void read_renwang()
{
	int i,size,num,level;
	string cTmp,*line,tmp;
	
	cTmp = read_file("npc/party/xinrenwang.txt");
	if ( sizeof(cTmp) == 0 )
		return;
	line = explode( cTmp, "\n" );
	size = sizeof(line);
	mpXinrenwang = ([]);
        for( i = 0; i < size; i ++ ) 
	{
		if ( line[i][0..0] == "#" )
			continue;
		if ( sscanf(line[i],"%s %d %d",tmp,num,level) != 3 )
			continue;
		mpXinrenwang[tmp] = num;
	}
}

void renwang_mail()
{
	int i,size;
	string cTmp,*line,tmp;
	size = sizeof(mpXinrenwang);
	line = keys(mpXinrenwang);
	for( i = 0; i < size; i ++ ) 
	{
		MAILBOX->sys_mail(line[i],mpXinrenwang[line[i]],"恭喜恭喜，因为你的出色表现，已经被评选为了本服务器的战国新人王。不要犹豫，快快去如意仙子那里领取你的称号和奖励吧！");
	}	
}
void read_lifeskill()
{
	int i,size,num,level,skill;
	string cTmp,*line,tmp;
	
	cTmp = read_file("npc/party/lifeskill.txt");
	if ( sizeof(cTmp) == 0 )
		return;
	line = explode( cTmp, "\n" );
	size = sizeof(line);
	mpXinrenwang = ([]);
        for( i = 0; i < size; i ++ ) 
	{
		if ( line[i][0..0] == "#" )
			continue;
		if ( sscanf(line[i],"%s %d %d %d",tmp,num,skill,level) != 4 )
			continue;
		if ( !mapp(mpLifeskill[num]) )
			mpLifeskill[num] = ([]);
		mpLifeskill[num][tmp] = skill;
	}
}

void lifeskill_mail()
{
	int i,size,*nId;
	string cTmp,*line,tmp;
	size = sizeof(mpLifeskill);
	nId = keys(mpLifeskill);
	for( i = 0; i < size; i ++ ) 
	{
		line = keys(mpLifeskill[nId[i]]);
		MAILBOX->sys_mail(line[0],nId[i],"恭喜恭喜，经过这段时间的考验和你自己的努力，你已经成为万人瞩目的技能师。不要犹豫，快快去如意仙子那里领取你的称号和奖励吧！");
	}	
}
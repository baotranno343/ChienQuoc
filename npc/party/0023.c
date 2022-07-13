#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>
#include <task.h>

inherit OFFICER;
void read_renwang();
int iStart;
mapping mpXinrenwang =  ([]);
// 函数：获取人物造型
int get_char_picid() { return 9315; }
void do_welcome(string arg);
void give_pet(object who);

//string get_save_file()	{ return "data/dodolook"SAVE_EXTENSION;}

// 函数：构造处理
void create()
{
        set_name("新人王教头");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
        read_renwang();
        if ( !clonep(this_object()) )
        	return ;
        if (MAIN_D->get_host_type()==2)		//台湾除外
        	call_out("go_there",2);
}

void do_look(object who) { __FILE__->do_look_call(this_object(),who); }
void do_look_call(object me,object who)
{
	int id = getoid(me);
	
	if (MAIN_D->get_host_type()==2)
		return ;
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    我是新人王教头，当前战国正在举办征兵活动，凡是在活动期间新创建的角色（新人）都有参加新人王比赛的活动权力。在活动结束之时，新人中级别最高的将获得实物大奖。若想知道活动详细信息，请关注游戏公告或登陆www.zg.mop.com进行查询！\n"ESC"领取新人王奖励\ntalk %x# welcome.1\n"ESC"离开",me->get_name(),id,));
	
}

void do_welcome(string arg) { __FILE__->do_welcome_call(this_object(),arg); }

/*
void do_welcome_call( object me,string arg )
{
	int flag, p,iTime,i,size,id,level,iLev;
       	object who, item;
       	string name,*nTmp,tmp;
	mixed *mxTime;  
	
	
	if (MAIN_D->get_host_type()==2)
		return ;
		
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 1:
        	if ( iStart == 0 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    新人王活动还在进行中，等活动结束之后再来找我吧！\n"ESC"离开",me->get_name(),));
        		return ;        		
        	}
        	if ( who->get_save("xrw20070315") )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你已经领过奖了！\n"ESC"离开",me->get_name(),));
        		return ;        		
        	}
        	id = who->get_number();
		name = who->get_name();
        	if ( mpXinrenwang[name] && mpXinrenwang[name]["id"] == id )
        		level = mpXinrenwang[name]["level"];
        	if ( !level )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你不是新人王，你不能获得新人王奖励！\n"ESC"离开",me->get_name(),));
        		return ;        		
        	}
        	who->set_save("xrw20070315",time());
        	if ( level == 1 )	//一等奖
		{
			if ( USER_INVENTORY_D->count_empty_carry(who) < 7 )
			{
				send_user(who,"%c%s",'!',"请清理一下你的包包再来领取奖励吧！");
				return ;	
			}
			//金色武器
			iLev = who->get_level() / 10 * 10 + 10;
			nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),iLev,WEAPON_TYPE);
	        	tmp = nTmp[random(sizeof(nTmp))];
	        	if ( !stringp(tmp) )
	        		return ;
	        	item = new(tmp);
	        	ITEM_EQUIP_D->init_equip_prop_3(item);
	        	p = item->move(who,-1);
	        	item->add_to_user(p);	        	
			//变身卡
			for(i=0;i<5;i++)
			{
				item = new("quest/gift"->get_random_card());
				if ( !item )
					continue;
				p = item->move(who,-1);
				item->add_to_user(p);
			}
			//麻布包裹
	        	item = new("item/std/6003");
			p = item->move(who,-1);
			item->add_to_user(p);
	        }
        	else if ( level == 2 )	//二等奖
		{
			if ( USER_INVENTORY_D->count_empty_carry(who) < 5 )
			{
				send_user(who,"%c%s",'!',"请清理一下你的包包再来领取奖励吧！");
				return ;	
			}
			//金色武器
			iLev = who->get_level() / 10 * 10 + 10;
			nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),iLev,WEAPON_TYPE);
	        	tmp = nTmp[random(sizeof(nTmp))];
	        	if ( !stringp(tmp) )
	        		return ;
	        	item = new(tmp);
	        	ITEM_EQUIP_D->init_equip_prop_3(item);
	        	p = item->move(who,-1);
	        	item->add_to_user(p);	        	
			//变身卡
			for(i=0;i<3;i++)
			{
				item = new("quest/gift"->get_random_card());
				if ( !item )
					continue;
				p = item->move(who,-1);
				item->add_to_user(p);
			}
			//麻布包裹
	        	item = new("item/std/6003");
			p = item->move(who,-1);
			item->add_to_user(p);
	        }
	        else if ( level == 3 )	//三等奖
		{
			if ( USER_INVENTORY_D->count_empty_carry(who) < 2 )
			{
				send_user(who,"%c%s",'!',"请清理一下你的包包再来领取奖励吧！");
				return ;	
			}
			//技能进阶书
	        	item = new(BOOK_FILE->get_book_file());
			p = item->move(who,-1);
			item->add_to_user(p);
			//麻布包裹
	        	item = new("item/std/6003");
			p = item->move(who,-1);
			item->add_to_user(p);
	        }	
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    恭喜你成为万众瞩目的新人王！\n"ESC"离开",me->get_name(),));
        	send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIY+"%s玩家在新人王选拔活动中获得了第%d名的奖励！",who->get_name(),level) );
		log_file("zgwangzhe.txt",sprintf("%s %s(%d)领取战国王者%s第%d名奖励\n",short_time(),who->get_name(),who->get_number(),who->get_fam_name(),level));
        	break;
        }
}
*/

void go_there()
{
	object me=this_object();
	
	me->add_to_scene(802,79,45,2);
}

void read_renwang()
{
	int i,size,num,level;
	string cTmp,*line,tmp;
	mpXinrenwang = ([]);
	cTmp = read_file("data/xinrenwang315.txt");
	if ( sizeof(cTmp) == 0 )
		return;
	line = explode( cTmp, "\n" );
	size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
	{
		if ( line[i][0..0] == "#" )
			continue;
		if ( sscanf(line[i],"%s %d %d",tmp,num,level) != 3 )
			continue;
		mpXinrenwang[tmp] = (["id":num,"level":level]);
	}
	if ( sizeof(mpXinrenwang) )
		iStart = 1;
}

void set_open()
{
	iStart = 1;
	read_renwang();
}

void set_close()
{
	iStart = 0;	
}

void do_welcome_call(object who, string arg)
{
	int i, flag, type, p, total, count, amount, status, id, bonus;
	string arg2, *key, name;
	object item, me;
	int size,level,iLev;
       	string *nTmp,tmp;
	me = this_player();
	flag = to_int(arg);
	status = me->get_pay_money_buy_item();
	id = getoid(who);
	bonus = me->get_save("phpbonus");
	if (bonus>0)
	{
		me->delete_save("phpbonus");
		__FILE__->give_bonus(me, bonus);
		return;
	}
	if ( iStart == 0 )
        {
		send_user(me,"%c%c%w%s",':',3,who->get_char_picid(),sprintf("%s：\n    新人王活动还在进行中，等活动结束之后再来找我吧！\n"ESC"离开",who->get_name(),));
        	return ;        		
        }	
	if (status==0)
	{
		switch(flag)
		{
		case 1:			
			if ( me->get_beast_amount() >= me->get_beast_max_amount() )
			{
				send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					who->get_name()+":\n    你的宠物太多了，请清理一下再来找我吧～！\n"
					ESC"离开" );
	                        return ;
	                }	
			count = 7;			
	                if( sizeof_inventory(me, 1, MAX_CARRY) > MAX_CARRY - count )
	                {
				send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
					who->get_name()+":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n"
					ESC"离开" );
	                        return ;
	                }	
	                flag = 1001;      
	                arg = "1001";          
	                me->set("phpnum", flag);
			me->set_pay_money_buy_item(1);
			me->set_pay_type(4);
			me->set_buy_item_cmd_string( sprintf("%x# welcome.", getoid(who) ) );
			db_user_pay( me, sprintf( "%s:80\n"
	               		"GET http:/""/%s/getgoods.php?t=%s&u=%d&o=%d&n=%s&ip=%s&r=%d&h=%d\r\n", MAIN_D->get_php_ip(),
	               		MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), arg, get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host() ) );
log_file("php.dat", sprintf( "%s:80\n"
	               		"GET http:/""/%s/getgoods.php?t=%s&u=%d&o=%d&n=%s&ip=%s&r=%d&h=%d\r\n", MAIN_D->get_php_ip(),
	               		MAIN_D->get_php_ip(), short_time_2(), me->get_acountid(), me->get_number(), arg, get_ip_name(me), MAIN_D->get_region(), MAIN_D->get_host() ) );
			log_file("getitem.txt",sprintf("%s %s %d %s\n",short_time(),me->get_id(),me->get_number(),arg ));
			break;
		}
		return ;
	}
	if (status!=8)
	{
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
			who->get_name()+":\n    您的申请正在处理中，请稍候。\n"
			ESC"离开" );
	        return ;
	}
if (MAIN_D->get_host_type()==0 ) flag = 10011;
	switch(flag)
	{
	case 10011:
		count = 7;
		break;
	case 10012:
		count = 5;
		break;
	case 10013:
		count = 2;
		break;		
	}
	if( sizeof_inventory(me, 1, MAX_CARRY) > MAX_CARRY - count )
	{
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
			who->get_name()+":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n"
			ESC"离开" );
		me->set_save("phpbonus", flag);
	        return ;
	}
	if ( me->get_beast_amount() >= me->get_beast_max_amount() )
	{
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
			who->get_name()+":\n    你的宠物太多了，请清理一下再来找我吧～！\n"
			ESC"离开" );
		me->set_save("phpbonus", flag);
	        return ;
	}	
	me->set_pay_money_buy_item(0);
	__FILE__->give_bonus(me, flag);
}


void give_bonus(object who, int type)
{
	int i, p, total, amount, count, level, iLev;
	string result, *nTmp, tmp;
	object item;
	object me = this_object();
	switch(type)
	{
	case 10011:
		count = 7;
		break;
	case 10012:
		count = 5;
		break;
	case 10013:
		count = 2;
		break;				
	}
	if( sizeof_inventory(who, 1, MAX_CARRY) > MAX_CARRY - count )
	{
		send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),
			get_name()+":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n"
			ESC"离开" );
		who->set_save("phpbonus", type);
	        return ;
	}
	log_file("getitem.txt",sprintf("%s %s %d 领取%d成功\n",short_time(),who->get_id(),who->get_number(),type ));
	switch(type)
	{
        case 10011:		
		//金色武器
		level = 1;
		iLev = who->get_level() / 10 * 10 + 10;
		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),iLev,WEAPON_TYPE);
	        tmp = nTmp[random(sizeof(nTmp))];
	        if ( !stringp(tmp) )
	        	return ;
	        item = new(tmp);
	        ITEM_EQUIP_D->init_equip_prop_3(item);
	        p = item->move(who,-1);
	        item->add_to_user(p);	      
	        result = item->get_name();  	
		//变身卡
		for(i=0;i<5;i++)
		{
			item = new("quest/gift"->get_random_card());
			if ( !item )
				continue;
			p = item->move(who,-1);
			result += sprintf("、%s", item->get_name());
			item->add_to_user(p);			
		}
		//麻布包裹
	        item = new("item/std/6003");
	        result += sprintf("、%s", item->get_name());
		p = item->move(who,-1);
		item->add_to_user(p);		
		give_pet(who);
		result += "和一只宠物";
	        break;
	case 10012:		
		level = 2;
		//金色武器
		iLev = who->get_level() / 10 * 10 + 10;
		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),iLev,WEAPON_TYPE);
	        tmp = nTmp[random(sizeof(nTmp))];
	        if ( !stringp(tmp) )
	        	return ;
	        item = new(tmp);
	        ITEM_EQUIP_D->init_equip_prop_3(item);
	        p = item->move(who,-1);
	        item->add_to_user(p);	        
	        result = item->get_name();	
		//变身卡
		for(i=0;i<3;i++)
		{
			item = new("quest/gift"->get_random_card());
			if ( !item )
				continue;
			result += sprintf("、%s", item->get_name());
			p = item->move(who,-1);			
			item->add_to_user(p);			
		}
		//麻布包裹
	        item = new("item/std/6003");
		p = item->move(who,-1);
		result += sprintf("、%s", item->get_name());
		item->add_to_user(p);
		give_pet(who);
		result += "和一只宠物";
	        break;
	case 10013:		
		level = 3;
		//技能进阶书
	        item = new(BOOK_FILE->get_book_file());
	        result = item->get_name();
		p = item->move(who,-1);
		item->add_to_user(p);
		//麻布包裹
	        item = new("item/std/6003");
	        result += sprintf("、%s", item->get_name());
		p = item->move(who,-1);
		item->add_to_user(p);	        
        	break;
	}        
	send_user(who, "%c%s", ';', sprintf("你获得%s。", result));	
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    恭喜你成为万众瞩目的新人王！\n"ESC"离开",me->get_name(),));
        send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIY+"%s玩家在新人王选拔活动中获得了第%d名的奖励！",who->get_name(),level) );
	
}
//给予宠物
void give_pet(object who)
{
	mapping mpPet = ([
	"赵国巡逻兵" : 600,
	"绿壳蜘蛛" : 301,
	"水鬼" : 8010,
	"双刀骷髅" : 802,
	"火精" : 953,
	"守阵神将" : 4133,
	"枪魂" : 1102,
	]);
	mapping mpInfo;
	string cName;
	object pet;
	int level,i,size,*nSkill;
	
	level = who->get_level();
	if ( level < 31 )
		cName = "赵国巡逻兵";
	else if ( level < 51 )
		cName = "绿壳蜘蛛";		
	else if ( level < 71 )
		cName = "水鬼";
	else if ( level < 91 )
		cName = "双刀骷髅";
	else if ( level < 101 )
		cName = "火精";				
	else if ( level < 111 )
		cName = "守阵神将";
	else 
		cName = "枪魂";
			
	mpInfo = "quest/pet"->get_beast_info(cName);
	if ( !mpInfo )
		return 0;
	nSkill = mpInfo["skill"];
	pet = USER_BEAST_D->give_pet(who,cName,1,0,mpPet[cName],0);
	for(i=0,size=sizeof(nSkill);i<size;i++)
		pet->set_skill(nSkill[i],1);
	pet->send_info();
}

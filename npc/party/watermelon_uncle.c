
#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <equip.h>

inherit OFFICER;

int *change54 =({ 0010,0011,0050,0051,0052,0053,0100,0101,0102,0150,0151,0152,0200,0201,0202,0250,0251,0252,0300,0301,0302,0303,0304,0350,0351,0352,0400,0401,0402,0450,0500,0502,0550,0551,0552,8010,8011,});
void do_bonus(string arg);
int check_item_amount(object who,string name);
void reduce_item_amount(object who,string name,int i);
void give_trial_vip(object who);
// 函数：获取人物造型
int get_char_picid() { return 9115; } 

// 函数：构造处理
void create()
{
        set_name( "西瓜伯伯" );
        set_2( "talk", ([
                 "bonus"         : (: do_bonus :),
        ]));    
        setup();     
}

void do_look( object who )
{
	__FILE__->do_look_2(who, this_object());
}

void do_look_2( object who, object me )
{
	string cmd1="",cmd2="";
	int id;
	id = getoid(me);
	cmd1 = sprintf(ESC"交还西瓜获得报酬\ntalk %x# bonus.2\n",id);
	cmd2 = sprintf(ESC"将捉到的坏动物交给西瓜伯伯。\ntalk %x# bonus.8\n",id);
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		me->get_name()+":\n    今年风调雨顺，农作物和水果都获得了大丰收，这是一件所有人都开心的事。但是我却不怎么开心，因为我种植的西瓜实在太多了，一个人根本没办法采集完，很希望有人能帮我。如果你能帮我把西瓜采集回来的话，那么将获得很不错的报酬哦！\n    不过你要小心，时常会有一些坏动物来抢我的西瓜，如果你见到了，把它们捉起来交给我，我就可以教训它们了！\n    我再给你三个神奇的葫芦，当你抓到坏动物的时候，就可以把它们关在里面交给我。这个神奇葫芦你平时看不见，当你抓到坏动物的时候，它自己就会出来的！\n"
		+cmd1
		+cmd2
		+ESC"离开" );
}


void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_object(),arg);
}

void do_bonus_2(object me , string arg)
{
	int flag, p,iTime,i,j,size,id,x,y,z,level,rate,amount,amount01,amount02,amount03;
       	object who, item,*nTeam,member,npc,map,item_q,*inv,*inv2;
       	string name,*nTmp,tmp,result="",result2="",cTmp;
	mixed *mxTime;  
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 2:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    谢谢你帮我采集西瓜！请选择你所想要的报酬。\n"
			ESC"一个西瓜的报酬\ntalk %x# bonus.3\n"
			ESC"五个西瓜的报酬\ntalk %x# bonus.4\n"
			ESC"十个西瓜的报酬\ntalk %x# bonus.5\n"
			ESC"离开",me->get_name(),id,id,id));
        	break;
        case 3:
        	if( !objectp( item_q = present("西瓜伯伯的西瓜", who, 1, MAX_CARRY*4) ) )
        	{
        		send_user( who, "%c%s", ';', "很抱歉，你的西瓜数量不足哦，想要获得报酬可是要努力采集的！");
        		return;
        	}  
		if(USER_INVENTORY_D->count_empty_carry(who) < 3 )
		{
		        send_user(who,"%c%s",';',"你的道具栏空间不足够哦，请整理一下吧。");
	    		return;
		}
		item_q->add_amount(-1);
		result2 = sprintf(HIR"%s玩家"NOR"在国庆活动中，用西瓜兑换到了"HIR, who->get_name());

		who->add_cash(2500);
		result = result + HIR"2500金、";
		who->add_exp(100+who->get_level()*35);
		result = result + sprintf(HIR"%d经验、",100+who->get_level()*35);

		item = new ("item/91/9101");//活络丸
		item->set_amount(5);
		result = result + sprintf(HIR"%s、",item->get_name());
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		item = new ("item/91/9111");//安神丸
		item->set_amount(5);
		result = result + sprintf(HIR"%s、",item->get_name());
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		rate = random(1000);
		if (rate<450)
		{
			item=0;
		}
		else if (rate<550)
		{
			cTmp = BOOK_FILE->get_book_file();
			item = new (cTmp);//随机门派技能进阶书
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<650)
		{
			item = new ("item/44/4488");//宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<700)
		{
			item = new ("item/44/4489");//高级宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<820)//白装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<900)//蓝装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			ITEM_EQUIP_D->init_equip_prop_1(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<950)
		{
			item = new ("item/08/0003");//小血石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<1000)
		{
			item = new ("item/08/0004");//小法力石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		send_user(who,"%c%s",';',"得到 "+result);
		result += NOR"，让我们大家表示祝贺！";
//		if (result !="") send_user(USER_D->get_user(), "%c%s", 0xA3, result2+result);
//		USER_D->user_channel(result);	

        	break;
        case 4:
		if ( check_item_amount(who,"西瓜伯伯的西瓜") < 5 )
		{
			send_user(who,"%c%s",';',"很抱歉，你的西瓜数量不足哦，想要获得报酬可是要努力采集的！");
			return;	
		}
		if(USER_INVENTORY_D->count_empty_carry(who) < 3 )
		{
		        send_user(who,"%c%s",';',"你的道具栏空间不足够哦，请整理一下吧。");
	    		return;
		}
		reduce_item_amount(who,"西瓜伯伯的西瓜",5);
		who->add_cash(15000);
		result = result + HIR"15000金、";
		who->add_exp(100+who->get_level()*200);
		result = result + sprintf(HIR"%d经验、",100+who->get_level()*200);

		item = new ("item/91/9102");//造化丹
		item->set_amount(5);
		result = result + sprintf(HIR"%s、",item->get_name());
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		item = new ("item/91/9112");//补心丹
		item->set_amount(5);
		result = result + sprintf(HIR"%s、",item->get_name());
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		rate = random(1000);
		if (rate<70)
		{
			item=0;
		}
		else if (rate<170)
		{
			cTmp = BOOK_FILE->get_book_file();
			item = new (cTmp);//随机门派技能进阶书
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<270)
		{
			item = new ("item/44/4488");//宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<320)
		{
			item = new ("item/44/4489");//高级宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<440)//白装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<520)//蓝装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			ITEM_EQUIP_D->init_equip_prop_1(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<570)
		{
			item = new ("item/08/0003");//小血石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<620)
		{
			item = new ("item/08/0004");//小法力石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<650)
		{
			item = new ("/item/08/0002");//战国号角
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<700)//金装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<740)
		{
			item = new ("/item/08/0001");//战国令
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<780)
		{
			item = new ("/item/sell/0002");//大血石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<820)
		{
			item = new ("/item/sell/0004");//大法力石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<920)
		{
			item = new ("/item/std/8005");//残旧藏宝图
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<970)
		{
			item = new (sprintf("/item/54/%04d",change54[random(sizeof(change54))]));//随机变身卡
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<1000)
		{
	                item = new(STONE_FILE->get_diamond_file());//随机1级晶石
	                item->set_level(1);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		send_user(who,"%c%s",';',"得到 "+result);
		result += NOR"，让我们大家表示祝贺！";
        	break;
        case 5:
		if ( check_item_amount(who,"西瓜伯伯的西瓜") < 10 )
		{
			send_user(who,"%c%s",';',"很抱歉，你的西瓜数量不足哦，想要获得报酬可是要努力采集的！");
			return;	
		}
		if(USER_INVENTORY_D->count_empty_carry(who) < 3 )
		{
		        send_user(who,"%c%s",';',"你的道具栏空间不足够哦，请整理一下吧。");
	    		return;
		}
		reduce_item_amount(who,"西瓜伯伯的西瓜",10);
		who->add_cash(30000);
		result = result + HIR"30000金、";
		who->add_exp(100+who->get_level()*500);
		result = result + sprintf(HIR"%d经验、",100+who->get_level()*500);

		item = new ("item/91/9120");//救急丹
		item->set_amount(5);
		result = result + sprintf(HIR"%s、",item->get_name());
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		item = new ("item/91/9121");//活心丹
		item->set_amount(5);
		result = result + sprintf(HIR"%s、",item->get_name());
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		rate = random(1000);
		if (rate<100)
		{
			cTmp = BOOK_FILE->get_book_file();
			item = new (cTmp);//随机门派技能进阶书
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<200)
		{
			item = new ("item/44/4488");//宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<250)
		{
			item = new ("item/44/4489");//高级宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<370)//白装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<450)//蓝装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			ITEM_EQUIP_D->init_equip_prop_1(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<500)
		{
			item = new ("item/08/0003");//小血石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<550)
		{
			item = new ("item/08/0004");//小法力石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<580)
		{
			item = new ("/item/08/0002");//战国号角
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<630)//金装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<680)
		{
			item = new ("/item/08/0001");//战国令
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<730)
		{
			item = new ("/item/sell/0002");//大血石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<780)
		{
			item = new ("/item/sell/0004");//大法力石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<880)
		{
			item = new ("/item/std/8005");//残旧藏宝图
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<930)
		{
			item = new (sprintf("/item/54/%04d",change54[random(sizeof(change54))]));//随机变身卡
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<960)
		{
	                item = new(STONE_FILE->get_diamond_file());//随机1级晶石
	                item->set_level(1);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<980)//Vip试用包
		{
			give_trial_vip(who);
			item = 0;
			result = result + HIR"Vip试用包";
		}
		else if (rate<990)
		{
			item = new ("/item/08/0015");//干将宝石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<1000)
		{
			item = new ("item/04/0454");//淬月之环
			result = result + sprintf(HIR"%s",item->get_name());
		}

		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		send_user(who,"%c%s",';',"得到 "+result);
		result += NOR"，让我们大家表示祝贺！";
        	break;

        case 8:
		amount01=check_item_amount(who,"装着坏小猴的神奇葫芦");
		amount02=check_item_amount(who,"装着坏小猪的神奇葫芦");
		amount03=check_item_amount(who,"装着坏大熊的神奇葫芦");
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    呵呵，请把你抓到的坏动物交给我吧，你现在已经抓到了%d只坏小猴，%d只坏小猪，%d只坏大熊。作为报酬你可以有如下选择。\n"
			ESC"用3只坏小猴换取报酬\ntalk %x# bonus.9\n"
			ESC"用2只坏小猪换取报酬\ntalk %x# bonus.10\n"
			ESC"用1只坏大熊换取报酬\ntalk %x# bonus.11\n"
			ESC"离开",me->get_name(),amount01,amount02,amount03,id,id,id));
        	break;
        case 9:
		if ( check_item_amount(who,"装着坏小猴的神奇葫芦") < 3 )
		{
			send_user(who,"%c%s",';',"很抱歉，你抓的坏小猴数量不足哦，继续努力吧");
			return;	
		}
		if(USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
		        send_user(who,"%c%s",';',"你的道具栏空间不足够哦，请整理一下吧。");
	    		return;
		}
		reduce_item_amount(who,"装着坏小猴的神奇葫芦",3);

		result2 = sprintf(HIR"%s玩家"NOR"在国庆活动中，用坏小猴兑换到了"HIR, who->get_name());

		rate = random(1000);
		if (rate<300)
		{
			cTmp = BOOK_FILE->get_book_file();
			item = new (cTmp);//随机门派技能进阶书
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<600)
		{
			item = new ("item/44/4488");//宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<650)
		{
			item = new ("item/44/4489");//高级宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<850)//白装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<900)//蓝装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			ITEM_EQUIP_D->init_equip_prop_1(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<1000)//钱
		{
			item=0;
			who->add_cash(10000);
			result = result + HIR"10000金";
		}
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		send_user(who,"%c%s",';',"得到 "+result);
		result += NOR"，让我们大家表示祝贺！";
//		if (result !="") send_user(USER_D->get_user(), "%c%s", 0xA3, result2+result);
//		USER_D->user_channel(result);	

        	break;
        case 10:
		if ( check_item_amount(who,"装着坏小猪的神奇葫芦") < 2 )
		{
			send_user(who,"%c%s",';',"很抱歉，你抓的坏小猪数量不足哦，继续努力吧");
			return;	
		}
		if(USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
		        send_user(who,"%c%s",';',"你的道具栏空间不足够哦，请整理一下吧。");
	    		return;
		}
		reduce_item_amount(who,"装着坏小猪的神奇葫芦",2);

		result2 = sprintf(HIR"%s玩家"NOR"在国庆活动中，用坏小猪兑换到了"HIR, who->get_name());

		rate = random(1000);
		if (rate<200)
		{
			cTmp = BOOK_FILE->get_book_file();
			item = new (cTmp);//随机门派技能进阶书
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<400)
		{
			item = new ("item/44/4488");//宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<450)
		{
			item = new ("item/44/4489");//高级宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<650)//蓝装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			ITEM_EQUIP_D->init_equip_prop_1(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<850)//钱
		{
			item=0;
			who->add_cash(10000);
			result = result + HIR"10000金";
		}
		else if (rate<900)
		{
			item = new ("item/08/0003");//小血石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<950)
		{
			item = new ("item/08/0004");//小法力石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<1000)
		{
			item = new ("/item/08/0002");//战国号角
			result = result + sprintf(HIR"%s",item->get_name());
		}
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		send_user(who,"%c%s",';',"得到 "+result);
		result += NOR"，让我们大家表示祝贺！";
        	break;
        case 11:
        	if( !objectp( item_q = present("装着坏大熊的神奇葫芦", who, 1, MAX_CARRY*4) ) )
        	{
        		send_user( who, "%c%s", ';', "很抱歉，你抓的坏大熊数量不足哦，继续努力吧");
        		return;
        	}  
		if(USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
		        send_user(who,"%c%s",';',"你的道具栏空间不足够哦，请整理一下吧。");
	    		return;
		}
		item_q->add_amount(-1);
		result2 = sprintf(HIR"%s玩家"NOR"在国庆活动中，用坏大熊兑换到了"HIR, who->get_name());

		rate = random(1000);
		if (rate<200)
		{
			cTmp = BOOK_FILE->get_book_file();
			item = new (cTmp);//随机门派技能进阶书
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<400)
		{
			item = new ("item/44/4488");//宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<450)
		{
			item = new ("item/44/4489");//高级宠物技能丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<650)//蓝装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			ITEM_EQUIP_D->init_equip_prop_1(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<700)
		{
			item = new ("item/08/0003");//小血石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<750)
		{
			item = new ("item/08/0004");//小法力石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<800)
		{
			item = new ("/item/08/0002");//战国号角
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<850)//金装
		{
			if ((level=who->get_level()+10)>120) level=120;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),level,101+random(6));
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<900)
		{
			item = new ("/item/08/0001");//战国令
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<950)
		{
			item = new ("/item/sell/0002");//大血石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate<1000)
		{
			item = new ("/item/sell/0004");//大法力石
			result = result + sprintf(HIR"%s",item->get_name());
		}
		if ( item )
		{
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
		send_user(who,"%c%s",';',"得到 "+result);
		result += NOR"，让我们大家表示祝贺！";
//		if (result !="") send_user(USER_D->get_user(), "%c%s", 0xA3, result2+result);
//		USER_D->user_channel(result);	
	}
}


int check_item_amount(object who,string name)
{
	object *inv;
	int i,amount,size;
	inv = all_inventory(who, 1, MAX_CARRY*4);
	
	for(i=0,size=sizeof(inv);i<size;i++)
	{
		if ( !objectp(inv[i]) )
			continue;
		if ( inv[i]->get_name() != name )
			continue;
		amount += inv[i]->get_amount();		
	}
	return amount;
}

void reduce_item_amount(object who,string name,int p)
{
	object *inv2;
	int i,j,size;
	j=p;
	inv2 = all_inventory(who, 1, MAX_CARRY*4);

	for(i=0,size=sizeof(inv2);i<size;i++)
	{
		if ( !objectp(inv2[i]) )
			continue;
		if ( inv2[i]->get_name() != name )
			continue;
        	if ( inv2[i]->get_amount() <= j )
        	{
        		j -= inv2[i]->get_amount();
        		inv2[i]->remove_from_user();
        		destruct(inv2[i]);
        	}
        	else
        	{
        		inv2[i]->set_amount(inv2[i]->get_amount()-j);
        		j = 0;
        	}     
        	if ( j == 0 )
        		break;

	}
	
}

void give_trial_vip(object who)
{
	int iVip,iVipTime;
	mixed *mixTime;
	iVip = who->get_vip();
	if ( iVip != 0 && iVip != 1 )
		return 0;
	if ( iVip == 0 )
	{
		who->delete_save_2("vip_package");
		who->set_vip(1);
		iVipTime = time()+3600*24*3;
	}
	else
		iVipTime = who->get_save_2("vip_package.time")+3600*24*3;
	who->add_save_2("vip_package.doubles",20);
	who->set_save_2("vip_package.time",iVipTime);
	who->add_title("V001");
	send_user( who, "%c%w%w%c", 0x81, 7401, 999, EFFECT_GOOD );
	
	USER_ENERGY_D->count_cp(who);
	USER_ENERGY_D->count_pp(who);
	USER_ENERGY_D->count_ap(who);
	USER_ENERGY_D->count_dp(who);
	mixTime = localtime(iVipTime);
//	send_user(who,"%c%s",';',sprintf("你绑定了VIP包，VIP绑定的到期时间是%d-%02d-%02d %02d:%02d:%02d。观察VIP效果描述即可了解到期时间。你也可以去找神仙爷爷查询VIP绑定到期的时间。",mixTime[TIME_YEAR],mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN],mixTime[TIME_SEC]));
	send_user( who, "%c%w%s", 0x82, 7401, "item/sell/0061"->get_loop_desc(who));
	send_user( who, "%c%c%c", 0xA2, 4, 1);
	send_user( who, "%c%c%c", 0xA2, 3, 3-who->get_save_2("vip_package.revive.count"));
	"item/sell/0061"->send_vip_to_friend(who,1);
	send_user(who, "%c%s", '!',"恭喜您已经获得了三天的VIP包试用服务");
}
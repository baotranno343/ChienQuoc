#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <equip.h>
#include <task.h>
#include <effect.h>

inherit OFFICER;
inherit SAVE_F;

int iStart,iFinish;
int mlz;
// 函数：获取人物造型
int get_char_picid() { return 8113; }
string get_save_file()	{ return "data/milizhu"SAVE_EXTENSION;}

void do_visit( string arg );
void do_welcome(string arg);
void do_dodolook(string arg);
void do_accept(string arg);
void ask_bonus(object who,string arg);

//int accept_object(object who, object item)
// 函数：构造处理
void create()
{
	restore();
        set_name("dodolook");
        set_2( "talk", ([
		"visit"		   : (: do_visit :),
                 "welcome"         : (: do_welcome :),
		"dodolook"         : (: do_dodolook :),
                 "accept"          : (: do_accept :),
        ]) );
        setup();
	set("mpLegend",([0:({32}),]));
        if ( !clonep(this_object()) )
        	return ;
        if (MAIN_D->get_host_type()==2)		//台湾除外
        	call_out("go_there",2);
}
string get_short() 
{ 
	if ( stringp(get_real_name()) )
		return get_name() + "|" + get_real_name();
	else
		return get_name();
}
void do_look(object who) { __FILE__->do_look_call(this_object(),who); }

void do_look_call(object me,object who)
{
	int id = getoid(me);
	if (MAIN_D->get_host_type()==2)
		return ;
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    怎么办好呢……\n"
		ESC"七国令线上打宝\ntalk %x# visit.1\n"
		ESC"缘分对对碰活动\ntalk %x# visit.2\n"
		ESC"缘分对对碰领奖\ntalk %x# visit.3\n"
		ESC"离开",
		me->get_name(),id,id,id));
}

void do_visit( string arg )
{
        object me = this_object();
        __FILE__ ->do_visit2(me, arg);
}

void do_visit2( object me, string arg )
{
	object who=this_player();
	int id = getoid(me);
        int flag = to_int(arg);
	if (MAIN_D->get_host_type()==2)
		return ;
        switch(flag)
        {
	case 1:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    侠士你好，我叫dodolook，来自另一个世界！我在这个时代的时间已经太长了，如果我不返回我的时代的话，也许我就永远回不去了。我需要你的帮助！帮我收集七国令，越多越好！只要拥有足够的七国令，我就有回到原来世界的可能！当然，我也会答谢你的。我从现实世界里带了一些特别的礼物来，作为谢礼！不同的令牌数量对应不同的礼物，自然令牌越多，礼物也就越大了！\n"
			ESC"给予七国令\ntalk %x# welcome.1\n"
			ESC"七国令兑换虚拟物品\ntalk %x# welcome.2\n"
			ESC"查看已交令牌数目\ntalk %x# welcome.7\n"
			ESC"哪里可以获得七国令\ntalk %x# welcome.8\n"
			ESC"七国令规则\ntalk %x# welcome.9\n"
			ESC"离开",
			me->get_name(),id,id,id,id,id));
		break;
	case 2:
		if ( who->get_save_2("dodolook_task.finish") )
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    缘分天注定，把握在个人哦！这里有一个考验你们缘分的机会，你们愿意接受吗？想必你们都已做好准备了吧！既然如此，缘分的测试就要开始了哦！\n"ESC"领取缘分宠物\ntalk %x# welcome.101\n"ESC"注意事项\ntalk %x# welcome.102\n"ESC"完成缘分任务\ntalk %x# welcome.107\n"ESC"传送去缘分驿站\ntalk %x# welcome.108\n"ESC"离开",me->get_name(),id,id,id,id));
		else
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    缘分天注定，把握在个人哦！这里有一个考验你们缘分的机会，你们愿意接受吗？想必你们都已做好准备了吧！既然如此，缘分的测试就要开始了哦！\n"ESC"领取缘分宠物\ntalk %x# welcome.101\n"ESC"注意事项\ntalk %x# welcome.102\n"ESC"接受缘分任务\ntalk %x# welcome.103\n"ESC"传送去缘分驿站\ntalk %x# welcome.108\n"ESC"离开",me->get_name(),id,id,id,id));	
		break;
	case 3:
		ask_bonus(me,"");
		break;
        }

}

/*
void do_look_call(object me,object who)
{
	int id = getoid(me);
	if (MAIN_D->get_host_type()==2)
		return ;
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    侠士你好，我叫dodolook，来自另一个世界！我在这个时代的时间已经太长了，如果我不返回我的时代的话，也许我就永远回不去了。我需要你的帮助！帮我收集七国令，越多越好！只要拥有足够的七国令，我就有回到原来世界的可能！当然，我也会答谢你的。我从现实世界里带了一些特别的礼物来，作为谢礼！不同的令牌数量对应不同的礼物，自然令牌越多，礼物也就越大了！\n"
		ESC"给予七国令\ntalk %x# welcome.1\n"
		ESC"七国令兑换虚拟物品\ntalk %x# welcome.2\n"
		ESC"查看已交令牌数目\ntalk %x# welcome.7\n"
		ESC"哪里可以获得七国令\ntalk %x# welcome.8\n"
		ESC"七国令规则\ntalk %x# welcome.9\n"
		ESC"离开",
		me->get_name(),id,id,id,id,id));
}*/

void do_welcome(string arg) { __FILE__->do_welcome_call(this_object(),arg); }

void do_welcome_call( object me,string arg )
{
	int flag, p,iTime,i,j,size,id,x,y,z,level,rate,amount;
       	object who, item,*nTeam,member,npc,map,item_q,*inv,*inv2;
       	string name,*nTmp,tmp,result="",result2="",cTmp;
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
		if (iStart==0 || time()<iStart)
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    活动还没开始呢，详情请查看官方网站(zg.mop.com)公告。\n"ESC"离开",me->get_name(),));
		else if (iStart==1 || (time()>iStart && time()<iFinish))
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你收集到七国令了吗？呵呵～！你打算给我吗？你只需要按（Ａlt+Ｇ键）用鼠标指向我，这样就可以给我了，当我收到你的七国令，你的“已交令牌数”会随之累计增加，好了，说到这里了～谢谢你的帮助哦～！\n"ESC"离开",me->get_name(),));
		else if (iStart==2 || time()>iFinish)
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    本项活动已经结束，谢谢你的参与！\n"ESC"离开",me->get_name(),));
        	break;
        case 2:
		if (iStart==0 || time()<iStart)
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    活动还没开始呢，详情请查看官方网站(zg.mop.com)公告。\n"ESC"离开",me->get_name(),));
		else if (iStart==1 || (time()>iStart && time()<iFinish))
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    其实用七国令换些自己想要的一些的物品，其实也是个不错的选择哦～！再告诉你一个秘密：选择数量越多的兑换，所得的物品越吸引人～！不过用于兑换物品的七国令不会进算入你的“已交令牌数”～这点你可要想清楚哦～！\n"
				ESC"“一个七国令”兑换\ntalk %x# welcome.3\n"
				ESC"“两个七国令”兑换\ntalk %x# welcome.4\n"
				ESC"“五个七国令”兑换\ntalk %x# welcome.5\n"
				ESC"离开",me->get_name(),id,id,id));
		else if (iStart==2 || time()>iFinish)
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    本项活动已经结束，谢谢你的参与！\n"ESC"离开",me->get_name(),));
        	break;
        case 3:
        	if( !objectp( item_q = present("七国令", who, 1, MAX_CARRY) ) )
        	{
        		send_user( who, "%c%s", '!', "你的七国令不足以兑换相应物品！");
        		return;
        	}  
		if(USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
		        send_user(who,"%c%s",';',"请清理一下你的包包，再来兑换物品吧！");
	    		return;
		}
		item_q->add_amount(-1);
		result2 = sprintf(HIR"%s玩家"NOR"在七国游活动中，用七国令兑换到了"HIR, who->get_name());
		rate = random(1000);
		if (rate<125)
		{
			item = new ("item/std/8000");//藏宝图
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=125 && rate<250)
		{
			who->add_cash(10000);
			result = result + HIR"10000金";
		}
		else if (rate>=250 && rate<375)
		{
			who->add_exp(1000);
			result = result + HIR"1000经验";
		}
		else if (rate>=375 && rate<500)
		{
			who->add_potential(100);
			result = result + HIR"100潜能";
		}
		else if (rate>=500 && rate<625)
		{
			item = new ("item/91/9161");//周天丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=625 && rate<750)
		{
			item = new ("item/91/9162");//逍遥散
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=750 && rate<875)
		{
			item = new ("item/91/9163");//金桑散
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=875 && rate<1000)
		{
			item = new ("item/91/9164");//紫心丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		if ( item )
		{
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
                		send_user( who, "%c%s", '!', "请清理一下你的包包，再来兑换物品吧！");
                		return;
			}
			else
			{
				item->add_to_user(p);	
			}
		}
		send_user(who,"%c%s",'!',"得到 "+result);
		result += NOR"，让我们大家表示祝贺！";
//		if (result !="") send_user(USER_D->get_user(), "%c%s", 0xA3, result2+result);
//		USER_D->user_channel(result);	

        	break;
        case 4:
		inv = all_inventory(who, 1, MAX_CARRY);
		
		if( !objectp( item_q = present("七国令", who, 1, MAX_CARRY) ) )
		{
			send_user(who,"%c%s",'!',"你的七国令呢?");
			return;	
		}			
		for(i=0,size=sizeof(inv);i<size;i++)
		{
			if ( !objectp(inv[i]) )
				continue;
			if ( inv[i]->get_name() != "七国令" )
				continue;
			amount += inv[i]->get_amount();		
		}
		if ( amount < 2 )
		{
			send_user(who,"%c%s",'!',"你的七国令不足以兑换相应物品！");
			return;	
		}
		if(USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
		        send_user(who,"%c%s",';',"请清理一下你的包包，再来兑换物品吧！");
	    		return;
		}
	        j = 2;
		inv2 = all_inventory(who, 1, MAX_CARRY);
	
		for(i=0,size=sizeof(inv2);i<size;i++)
		{
			if ( !objectp(inv2[i]) )
				continue;
			if ( inv2[i]->get_name() != "七国令" )
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
		result2 = sprintf(HIR"%s玩家"NOR"在七国游活动中，用七国令兑换到了"HIR, who->get_name());
		rate = random(1000);
		if (rate<100)
		{
			who->add_cash(20000);
			result = result + HIR"20000金";
		}
		else if (rate>=100 && rate<300)
		{
			who->add_exp(5000);
			result = result + HIR"5000经验";
		}
		else if (rate>=300 && rate<425)
		{
			who->add_potential(500);
			result = result + HIR"500潜能";
		}
		else if (rate>=425 && rate<625)
		{
			item = new ("item/91/9165");//归元丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=625 && rate<750)
		{
			item = new ("item/91/9125");//再造丸
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=750 && rate<875)
		{
			item = new ("item/91/9150");//天王散
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=875 && rate<1000)
		{
			item = new ("item/91/9160");//气脉丹
			result = result + sprintf(HIR"%s",item->get_name());
		}
		if ( item )
		{
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
                		send_user( who, "%c%s", '!', "请清理一下你的包包，再来兑换物品吧！");
                		return;
			}
			else
			{
				item->add_to_user(p);	
			}
		}
		send_user(who,"%c%s",'!',"得到 "+result);
		result += NOR"，让我们大家表示祝贺！";
//		if (result !="") send_user(USER_D->get_user(), "%c%s", 0xA3, result2+result);
//		USER_D->user_channel(result);	

        	break;
        case 5:
		inv = all_inventory(who, 1, MAX_CARRY);
		
		if( !objectp( item_q = present("七国令", who, 1, MAX_CARRY) ) )
		{
			send_user(who,"%c%s",'!',"你的七国令呢?");
			return;	
		}			
		for(i=0,size=sizeof(inv);i<size;i++)
		{
			if ( !objectp(inv[i]) )
				continue;
			if ( inv[i]->get_name() != "七国令" )
				continue;
			amount += inv[i]->get_amount();		
		}
		if ( amount < 5 )
		{
			send_user(who,"%c%s",'!',"你的七国令不足以兑换相应物品！");
			return;	
		}
		if(USER_INVENTORY_D->count_empty_carry(who) < 1 )
		{
		        send_user(who,"%c%s",';',"请清理一下你的包包，再来兑换物品吧！");
	    		return;
		}
	        j = 5;
		inv2 = all_inventory(who, 1, MAX_CARRY);
	
		for(i=0,size=sizeof(inv2);i<size;i++)
		{
			if ( !objectp(inv2[i]) )
				continue;
			if ( inv2[i]->get_name() != "七国令" )
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

//		result2 = sprintf(HIR"%s玩家"NOR"在七国游活动中，用七国令兑换到了"HIR, who->get_name());
		rate = random(10000);
		if (rate<2400)
		{
			who->add_cash(30000);
			result = result + HIR"30000金";
		}
		else if (rate>=2400 && rate<4999)
		{
			who->add_exp(10000);
			result = result + HIR"10000经验";
		}
		else if (rate>=4999 && rate<7499)
		{
			who->add_potential(1000);
			result = result + HIR"1000潜能";
		}
		else if (rate>=7499 && rate<7899)
		{
			cTmp = BOOK_FILE->get_book_file_2();
			item = new (cTmp);//随机门派技能秘籍
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=7899 && rate<8899)
		{
			
			item = new (sprintf("item/std/800%d",random(4)+1));//残缺藏宝图随机一角
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=8899 && rate<9899)
		{
			cTmp = BOOK_FILE->get_book_file();
			item = new (cTmp);//随机门派技能进阶书
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate>=9899 && rate<9999)
		{
			if( random(2) ) //随机金装
				item = new( ARMOR_FILE->get_armor_file_2( who->get_level()+10) );
			else
				item = new( WEAPON_FILE->get_weapon_file_2( who->get_level()+10) );
			ITEM_EQUIP_D->init_equip_prop_3(item);
			result = result + sprintf(HIR"%s",item->get_name());
		}
		else if (rate==9999 && mlz<10)
		{
			item = new ("item/08/0811");//迷你猪
			result = result + sprintf(HIR"%s",item->get_name());
			mlz ++;
			save();
		}
		else if (rate==9999 && mlz>=10)
		{
			who->add_exp(10000);
			result = result + HIR"10000经验";
		}
		if ( item )
		{
			p = item->move(who,-1);
			if ( !p )
			{
				destruct(item);
                		send_user( who, "%c%s", '!', "请清理一下你的包包，再来兑换物品吧！");
                		return;
			}
			else
			{
				item->add_to_user(p);	
				send_user(USER_D->get_user(), "%c%s", 0xA3, sprintf(HIR"%s玩家"NOR"在七国游活动中，用七国令兑换到了"HIR"%s"NOR"，让我们大家表示祝贺！",who->get_name(),item->get_name()));
			}
		}
		send_user(who,"%c%s",'!',"得到 "+result);
//		result += NOR"，让我们大家表示祝贺！";
//		USER_D->user_channel(result);	

        	break;
        case 7:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    目前为止，你已经给我了%d个七国令了，谢谢你哦～！还望你再接再厉，继续加油哦～！\n"ESC"离开",me->get_name(),who->get_save("qgl_n")));
        	break;
        case 8:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    获得七国令的方法有很多种哦～！除了通过公测活动可以获得七国令外，你还可以去消灭与自身等级相应的怪物来获得，不过有一定的几率哦！（此外，你还须注意一点：20级以上的怪物身上才有携带七国令。并且，只有打与自身级别差在5级以内的怪物才可能获取。）我还有一个小秘密要告诉你哦～！如果把七国令交给帮派里面的七国令收集员，你除了能增加“已交令牌数”之外，还可以获得相应的帮贡，呵呵～不过前提是：你必须加入帮派才行！好了～就说到这里了～去开始你的战国冒险吧～！\n"ESC"离开",me->get_name(),));
        	break;
        case 9:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    七国令可以直接与我进行兑换，兑换一些游戏虚拟物品，如果兑换到珍稀罕见的“迷你猪”小宠物，那么你肯定可以成为服务器关注的焦点。不过进行七国令兑换的七国令，将不会累积入你的“已交七国令”数量中，只有直接给予的七国令，才能增加你的“已交七国令”数量。而全服缴纳七国令最多的玩家，将获得我从现代带来的实物大奖。具体详细信息，请查阅官网zg.mop.com活动专区中相关信息，一定可以得到更多相关信息。我还有一个小秘密要告诉你哦～！如果把七国令交给帮派里面的七国令收集员，你除了能增加“已交令牌数”之外，还可以获得相应的帮贡，呵呵～不过前提是：你必须加入帮派才行！好了～就说到这里了～去开始你的战国冒险吧～！\n"ESC"离开",me->get_name(),));
        	break;
	case 101..108:
        case 10091:
        case 10101:	
		"/npc/party/dodolook"->do_welcome_call(me,arg);
		break;
	case 101204:
	case 101205:
		ask_bonus(me,arg);
		break;
	}
}

void do_dodolook(string arg)  { "/npc/party/dodolook"->do_welcome_call(this_object(),arg); }

int accept_object(object me, object item,int amount)
{

	return __FILE__->accept_object2(me, this_object(), item,amount);
}

int accept_object2(object me, object who, object item2,int amount)
{
	if (item2->get_name()!="七国令"||iStart == 0||iStart == 2|| time()<iStart|| time()>iFinish)
		return 0;
	else
	{
		me->add_save("qgl_n",amount);
		return 1;
	}
}

void go_there()
{
	object me=this_object();
	me->add_to_scene(802,78,43,2);
}

void set_prepare()
{
	iStart = 0;
	save();
}

void set_open()
{
	iStart = 1;
	save();
}

int set_open_time(object who,string arg)
{
	int date1,date2,year1,year2,mon1,mon2,day1,day2;
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
	iStart = mktime(year1,mon1,day1,0,0,0);	
	iFinish = mktime(year2,mon2,day2,0,0,0);		
	if ( iStart > iFinish )
	{
		send_user(who,"%c%s",'!',"错误的时间！！");	
		return 0;
	}
	tell_user(who,"活动开启：%s！",arg);	
	send_user(who,"%c%s",'!',"线上打宝活动开启！");	
	save();
	return 1;
}

void set_close()
{
	iStart = 2;
	iFinish = time();
	save();
}

//领奖
void ask_bonus(object who,string arg)
{
	int i, flag, type, p, count, status, id, bonus;
	object me;
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

	if (status==0)
	{
		if ( me->get_beast_amount() >= me->get_beast_max_amount() )
		{
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
				who->get_name()+":\n    你的宠物太多了，请清理一下再来找我吧～！\n"
				ESC"离开" );
                        return ;
                }	
		count = 2;			
                if( sizeof_inventory(me, 1, MAX_CARRY) > MAX_CARRY - count )
                {
			send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
				who->get_name()+":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n"
				ESC"离开" );
                        return ;
                }	
                flag = 1013;      
                arg = "1013";          
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
		return ;
	}
	if (status!=8)
	{
		send_user( me, "%c%c%w%s", ':', 3, who->get_char_picid(),
			who->get_name()+":\n    您的申请正在处理中，请稍候。\n"
			ESC"离开" );
	        return ;
	}
	switch(flag)
	{
	case 101204:
		count = 2;
		break;
	case 101205:
		count = 1;
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
	int i, p, total, count;
	string cName, *nTmp, tmp;
	object item,pet;
	object me = this_object();
	switch(type)
	{
	case 101204:
		count = 2;
		break;
	case 101205:
		count = 1;
		break;
	default:
		return ;	
	}
	if( sizeof_inventory(who, 1, MAX_CARRY) > MAX_CARRY - count )
	{
		send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),
			get_name()+":\n    你的包袱已满，请清理一下你的包包再来找我吧～！\n"
			ESC"离开" );
		who->set_save("phpbonus", type);
	        return ;
	}
	if ( type == 101205 && who->get_beast_amount() >= who->get_beast_max_amount() )
	{
		send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),
			get_name()+":\n    你的宠物太多了，请清理一下再来找我吧～！\n"
			ESC"离开" );
		who->set_save("phpbonus", type);
	        return ;
	}
	log_file("getitem.txt",sprintf("%s %s %d 领取%d成功\n",short_time(),who->get_id(),who->get_number(),type ));
	switch(type)
	{
        case 101204:	
        	item = new("item/std/8000");
		p = item->move(who,-1);
		item->add_to_user(p);
		item = new("item/std/6003");
		p = item->move(who,-1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', "你获得藏宝图一张、麻布包裹一个" );
        	break;
        case 101205:
        	nTmp = "quest/pet"->get_level_pet(who->get_level());
        	if ( !sizeof(nTmp) )
        		return ;
        	cName = nTmp[random(sizeof(nTmp))];
        	p = "quest/pet"->get_pet_picid(cName);
        	if ( !p )
        		return ;
        	pet = USER_BEAST_D->give_pet(who,cName,1,0,p,0);
        	pet->send_info();
		item = new("item/std/6003");
		p = item->move(who,-1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', "你获得"+cName+"宝宝一只、麻布包裹一个" );
        	break;
        }
        
}
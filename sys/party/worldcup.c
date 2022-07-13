//2006世界杯活动模块

#include <ansi.h>
#include <task.h>
#include <time.h>

#define GAMELIST	"ini/worldcup_list.ini"
#define _DB(x,y)	if(find_char("971")) tell_user(find_char("971"),x,y)

inherit DBASE_F;
inherit SAVE_F;

static int init_time;		//赛程表更新时间
static mapping GameList = ([]);	//赛程表
static mapping GameDate = ([]);
//进阶书/秘籍书
static string *Books = ({"0316","0317","0319","0324","0325","0329","0348","0349","0363","0364","0368","0401","0402","0403","0408","0409","0411","0413","0414","0417","0418","0421","0422","0423","0424","0425","0429","0501","0503","0511","0513","0521","0531","0591",});
mapping mpResult = ([]);	//投票结束的信息
mapping mpVote = ([]);		//正在投票的信息
mapping mpBonus = ([]);
mapping mpChampion = ([]);
mapping winners = ([]);
void read_gamelist();

// 函数：生成二进制码
void SAVE_BINARY() { }

string get_save_file()	{ return "data/worldcup"SAVE_EXTENSION;}

void create()
{
	restore();
	call_out("check_time",3);
}

int do_look(object who,object npc,int id)
{
	int *index,i,size;
	mapping mpTmp;	
	string buf;
		
	if ( sizeof(GameList) == 0 )
		return ;
	mpTmp = mpVote[id];
//	if ( !mapp(mpTmp) )
//		return ;
	index = sort_array(keys(mpTmp),1);
	size = sizeof(index);
	buf = sprintf("%s:\n    天天竞猜，天天有奖，这可是专业球迷不可不参加的经典竞猜活动！平日里积累下来众多关于足球、世界杯的知识现在可以换取奖品了，知道的越多，竞猜中自然也就多了几分胜算，不服不行。\n",npc->get_name());
	for(i=0;i<size;i++)
	{
		if ( !mapp( GameList[index[i]] ) )
			continue;
		if ( GameList[index[i]]["score1"] == -1 )
			buf += sprintf(ESC"%s VS %s\ntalk %x# choice.%d\n",GameList[index[i]]["team1"],GameList[index[i]]["team2"],getoid(npc),index[i]);
		else
			buf += sprintf(ESC"%s VS %s %d:%d\nclose\n",GameList[index[i]]["team1"],GameList[index[i]]["team2"],GameList[index[i]]["score1"],GameList[index[i]]["score2"]);
	}
	if ( mpBonus[who->get_number()] )
		buf += sprintf(ESC"领取奖励\ntalk %x# bonus\n",getoid(npc));
	buf += ESC"离开\nclose\n";
	send_user(who,"%c%c%w%s",':',3,npc->get_char_picid(),buf);
}

void do_choice(object who , object npc , string arg, int iFlag)
{
	int id,count,oid,percent;
	string buf;
	mapping mpTmp,mpTmp1;
	
	id = to_int(arg);
	mpTmp1 = mpVote[iFlag];
	if ( !mapp(mpTmp1) || !mapp(mpTmp1[id]) )	//是否存在
		return ;	
	mpTmp = GameList[id];
	if ( !mapp(mpTmp) )
		return ;
	if ( mpTmp["type"] == 32 )
		count = 2;
	else if ( mpTmp["type"] == 16 )
		count = 5;
	else if ( mpTmp["type"] == 8 )
		count = 7;
	else if ( mpTmp["type"] == 4 || mpTmp["type"] == 3)
		count = 7;
	else if ( mpTmp["type"] == 2 )
		count = 7;
	mpTmp1 = mpTmp1[id];
	if ( mpTmp1["vote1"]+mpTmp1["vote2"] )
	{
		percent = mpTmp1["vote1"] * 100 / ( mpTmp1["vote1"]+mpTmp1["vote2"]);
		buf = sprintf("%s:\n    拿出你至少%d个球队牌，就能参加竞猜活动啦！投票给你喜欢的、你支持的队伍，就有可能获取大奖哦！\n"ESC"%s %d％\ntalk %x# bet.1.%d.1\n"ESC"%s %d％\ntalk %x# bet.1.%d.2\n"ESC"离开", 
			npc->get_name(), count, mpTmp["team1"],percent,oid=getoid(npc),id,mpTmp["team2"],100-percent,oid,id );
	}
	else
		buf = sprintf("%s:\n    拿出你至少%d个球队牌，就能参加竞猜活动啦！投票给你喜欢的、你支持的队伍，就有可能获取大奖哦！\n"ESC"%s\ntalk %x# bet.1.%d.1\n"ESC"%s\ntalk %x# bet.1.%d.2\n"ESC"离开", 
			npc->get_name(), count, mpTmp["team1"],oid=getoid(npc),id,mpTmp["team2"],oid,id );
	send_user(who,"%c%c%w%s",':',3,npc->get_char_picid(),buf);
	return ;
	
}
void do_bet(object who , object npc , string arg, int iFlag)
{
	int type,id,team,count,userid,min,max,i,j,size;
	string tmp,name;
	mapping mpTmp,mpTmp1;
	object *inv,*nTask;
	
	if ( sscanf(arg,"%d.%s",type,arg) != 2 )
		return ;
	if ( type == 1 )
	{
		if ( sscanf(arg,"%d.%d", id,team) != 2 )
			return ;
		mpTmp = mpVote[iFlag];
		if ( !mapp(mpTmp) || !mapp(mpTmp[id]) )	//是否存在
			return ;
		mpTmp = GameList[id];
		if ( !mapp(mpTmp) )
			return ;
		name = mpTmp[sprintf("team%d",team)];
		if ( !stringp(name) )
			return ;
		if ( mpTmp["type"] == 4 || mpTmp["type"] == 3)
			max = 20;
		else if ( mpTmp["type"] == 2 )
			max = 0;
		else
			max = 10;
		tmp = sprintf("请输入你为%s队投的票数\n"ESC"talk %x# bet.%d.%d.%d",name,getoid(npc),2,id,team)+".%s\n";
		send_user( who, "%c%c%d%s", '?', 1, max,tmp);
	}
	else if ( type == 2 )
	{
		if ( sscanf(arg,"%d.%d.%d", id,team,count) != 3 )
			return ;
		if ( count <= 0 )
			return ;
		mpTmp = mpVote[iFlag];
		if ( !mapp(mpTmp) || !mapp(mpTmp[id]) )	//是否存在
			return ;
		mpTmp1 = mpTmp[id];
		mpTmp = GameList[id];
		if ( !mapp(mpTmp) )
			return ;
		name = mpTmp[sprintf("team%d",team)];
		if ( !stringp(name) )
			return ;
		if ( time() > mpTmp["time"] )
		{
			send_user(who,"%c%c%w%s",':', 3,npc->get_char_picid(),npc->get_name()+":\n    很遗憾，这场比赛已经开始了，不能投票。");
			return ;
		}
		if ( mpTmp1["finish"] )
		{
			send_user(who,"%c%c%w%s",':', 3,npc->get_char_picid(),npc->get_name()+":\n    很遗憾，这场比赛已经结束了，不能投票。");
			return ;
		}
		if ( mpTmp["type"] == 32 )
		{
			min = 2;
			max = 10;
		}
		else if ( mpTmp["type"] == 16 )
		{
			min = 5;
			max = 10;
		}
		else if ( mpTmp["type"] == 8 )
		{
			min = 7;
			max = 10;
		}
		else if ( mpTmp["type"] == 4 || mpTmp["type"] == 3 )
		{
			min = 7;
			max = 20;
		}
		else if ( mpTmp["type"] == 2 )
		{
			min = 7;	
			max = 1000;
		}	
		userid = who->get_number();
		if ( !mapp(mpTmp1["user"]) )	
			mpTmp1["user"]	= ([]);	
		if ( !mapp(mpTmp1["user"][userid]) )	
			mpTmp1["user"][userid]	= ([]);	
		if (( team == 1 && mpTmp1["user"][userid][2]) || ( team == 2 && mpTmp1["user"][userid][1]) )
		{
			send_user(who,"%c%c%w%s",':', 3,npc->get_char_picid(),npc->get_name()+":\n    对不起，为公平起见，您不能在同场赛事中同时给两只队伍投票，请您继续关注您的已投票队伍。");
			return ;				
		}
		if ( mpTmp1["user"][userid][team] == 0 && count < min )
		{
			send_user(who,"%c%c%w%s",':', 3,npc->get_char_picid(),sprintf(npc->get_name()+":\n    对不起，此次竞猜的最低投票球队牌数量为%d只，你给予的球队牌数量不足，可以收集够了再来参加投票。",min));
			return;	
		}
		if ( max && mpTmp1["user"][userid][team]  >= max )
		{
			send_user(who,"%c%c%w%s",':', 3,npc->get_char_picid(),sprintf(npc->get_name()+":\n    对不起，此次竞猜的最高投票球队牌数量为%d只，你已经投够了此数量，等着结果的揭晓吧！",max));
			return;	
		}
		if ( max && count > max - mpTmp1["user"][userid][team] )
			count = max - mpTmp1["user"][userid][team];	//允许投票数
		//拿走球牌		
	        inv = all_inventory(who, 1, MAX_CARRY);
	        size = sizeof(inv);
	        j = 0;
	        nTask = ({});
	        for (i=0;i<size;i++)
	        {
	                if (inv[i]->is_worldcup())
	                {			
	                        nTask += ({inv[i]});
	                        j+=inv[i]->get_amount();
	                        if ( j >=count )
	                        	break;
	                }                                                
	        }
	        if ( j < count )
	        {
	        	send_user(who,"%c%c%w%s",':', 3,npc->get_char_picid(),npc->get_name()+":\n    你身上没有足够的球牌。");
	        	return ;		
	        }
	        j = count;
	        for(i=0,size=sizeof(nTask);i<size;i++)
	        {
	        	if ( nTask[i]->get_amount() <= j )
	        	{
	        		j -= nTask[i]->get_amount();
                		nTask[i]->remove_from_user();
                		destruct(nTask[i]);
                	}
                	else
                	{
                		nTask[i]->set_amount(nTask[i]->get_amount()-j);
                		j = 0;
                	}     
                	if ( j == 0 )
                		break;	                		    	
	        }
	        mpTmp1["user"][userid][team] += count;
	        if ( !mapp(mpTmp1["user"][userid]["level"]) )
	        {
	        	mpTmp1["user"][userid]["level"] = ([]);
	        	mpTmp1["user"][userid]["name"] = who->get_name();
	        }
	        mpTmp1["user"][userid]["level"][who->get_level()] += count;
	        
	        mpTmp1[sprintf("vote%d",team)] += count;
	        send_user(who,"%c%c%w%s",':', 3,npc->get_char_picid(),sprintf(npc->get_name()+":\n    你给%s队投了%d票。",name,count));	        
	        save();
	        log_file("worldcup.txt",sprintf("%s %d %s 投 %s %d\n",short_time(),who->get_number(),who->get_name(),mpTmp[sprintf("team%d",team)],count));	
	}
}
//读入赛程
void read_gamelist()
{
	int i,size,type,index,year,month,mday,hour,min,score1,score2,timesec,*ts;
	string *line,team1,team2;
	mixed *mixTime;
	
	if( !file_exist(GAMELIST) ) return 0;
	if ( init_time == stat(GAMELIST)[1] )
		return ;
	GameList = ([]);
	init_time = stat(GAMELIST)[1];	//赛程文件更新时间
	line = explode( read_file(GAMELIST), "\n" );
	for( i = 0, size = sizeof(line); i < size; i ++ ) 
	{
		score1=score2=-1;
		if ( sscanf(line[i],"%d %d %d/%d/%d %d:%d %s:%s %d:%d", 
			type,index,year,month,mday,hour,min,team1,team2,score1,score2) != 11 && 
			sscanf(line[i],"%d %d %d/%d/%d %d:%d %s:%s", 
			type,index,year,month,mday,hour,min,team1,team2) != 9 )		
			continue;
		timesec = mktime(year,month,mday,hour,min,0);		
		mixTime = localtime(timesec);
		if ( !arrayp(GameDate[mixTime[TIME_YDAY]]) )
			GameDate[mixTime[TIME_YDAY]] = ({ index });
		else
			GameDate[mixTime[TIME_YDAY]] += ({ index });
		GameList[index] = ([	"type" : type,
					"time" : timesec,
					"team1" : team1, "team2" : team2,
					"score1" : score1, "score2" : score2,
					]);
//		log_file("worldcup.txt",sprintf("%d %d\n",score1,score2));
	}
//	ts = sort_array(keys(GameDate),1);
//	for( i = 0, size = sizeof(ts); i < size; i ++ ) 
//	{
//		log_file("worldcup",sprintf("%d %O\n",ts[i],GameDate[ts[i]]));
//	}

	
//_DMSG("%d", init_time);
}
//生成奖励名单
void add_bonus(int idx1, int idx2)
{
	int i,size,win,*userid,type,total;
	mapping mpTmp,mpTmp1,mpTmp2;
	
	mpTmp = mpVote[idx1];
	if (!mapp(mpTmp))
		return ;
	mpTmp1 = mpTmp[idx2];
	if ( !mapp(mpTmp1))
		return ;
	if ( mpTmp1["finish"]==0)
		return;
	if ( mpTmp1["bonus"]!=0)
		return;
	mpTmp = GameList[idx2];
	type = mpTmp["type"];
	mpTmp1["bonus"] = 1;
	if ( mpTmp["score1"] == mpTmp["score2"] )
		win = 3;
	else if ( mpTmp["score1"] > mpTmp["score2"] )
		win = 1;
	else
		win = 2;
	if ( type == 2 )
	{
		total = mpTmp1[sprintf("vote%d",win)];	
	}
	mpTmp1 = mpTmp1["user"];
	if ( sizeof(mpTmp1) == 0 )
		return ;
	userid = keys(mpTmp1);
	for(i=0,size=sizeof(userid);i<size;i++)
	{
		if ( win != 3 && mpTmp1[userid[i]][win] == 0 )
			continue;

		if ( !mapp(mpBonus) )
			mpBonus = ([]);		
		if ( !mapp(mpBonus[userid[i]]) )
			mpBonus[userid[i]] = ([]);			
		mpTmp2 = mpBonus[userid[i]];
		mpTmp2[idx2] = mpTmp1[userid[i]];
		if ( type == 2 )	//冠军抽奖
		{
			if ( !mapp(mpChampion) )
				mpChampion = ([]);
			mpChampion[userid[i]] = mpTmp1[userid[i]][win];	//候选名单
			if ( random(total) < mpTmp1[userid[i]][win] )
			{
				if ( !mapp(winners) )
					winners = ([]);	
				winners[userid[i]] = mpTmp1[userid[i]]["name"]; //中奖名单
			}
		}
	}
	save();
}
//玩家获取奖励
void get_bonus(object who,object npc)
{
	int i,size,*nId,id,type,exp,pot,cash,*nLevel,level;
	mapping mpTmp,mpTmp1;
	object item,item1,item2,*inv;
	string name,unit;

	mpTmp = mpBonus[who->get_number()];
	if ( !mapp(mpTmp) )
		return;
	inv = all_inventory(who, 1, MAX_CARRY);
        size = sizeof(inv);       
	nId = sort_array(keys(mpTmp),1);
	id = nId[0];
	type = GameList[id]["type"];
	if ( type == 2 || type == 8 )
		i = 3;
	else
		i = 2;
	if ( size > MAX_CARRY -i)	//不够空位不给领奖
	{
		send_user(who,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n    请在身上留出足够的位置!");
		return ;
	}
	mpTmp1 = mpTmp[id]["level"];
	if ( !mapp(mpTmp1) )
	{
		map_delete(mpTmp,id);
		save();
		return ;
	}
	nLevel = keys(mpTmp1);
	if ( type == 32 )
	{
		for(i=0,size=sizeof(nLevel);i<size;i++)
		{
			exp += nLevel[i] * 40 * mpTmp1[nLevel[i]];
			pot += nLevel[i] * 1 * mpTmp1[nLevel[i]];
			cash += nLevel[i] * 40 * mpTmp1[nLevel[i]];
		}
		item = new("/item/32/3283");
		if ( item ) item->set_amount(20);
		item1 = new("/item/31/3151");
		if ( item1 ) item1->set_amount(20);
	}
	else if ( type == 16 )
	{
		for(i=0,size=sizeof(nLevel);i<size;i++)
		{
			exp += nLevel[i] * 60 * mpTmp1[nLevel[i]];
			pot += nLevel[i] * 2 * mpTmp1[nLevel[i]];
			cash += nLevel[i] * 50 * mpTmp1[nLevel[i]];
		}
		item = new("/item/32/3285");
		if ( item ) item->set_amount(30);
		item1 = new("/item/31/3152");
		if ( item1 ) item1->set_amount(30);
	}
	else if ( type == 8 )
	{
		for(i=0,size=sizeof(nLevel);i<size;i++)
		{
			exp += nLevel[i] * 80 * mpTmp1[nLevel[i]];
			pot += nLevel[i] * 3 * mpTmp1[nLevel[i]];
			cash += nLevel[i] * 60 * mpTmp1[nLevel[i]];			
		}	
		item = new("/item/32/3280");
		if ( item ) item->set_amount(30);
		item1 = new("/item/31/3153");
		if ( item1 ) item1->set_amount(30);
		//残缺宝石一颗或进阶书一本
		if ( random(2) )
		{
			item2 = new(sprintf("item/89/%d",8901+random(23)));
		}
		else
		{
			size = sizeof(Books);
			item2 = new (sprintf("/item/95/%s", Books[random(size)]));	
		}
	}
	else if ( type == 4 || type == 3 )
	{
		for(i=0,size=sizeof(nLevel);i<size;i++)
		{
			exp += nLevel[i] * 120 * mpTmp1[nLevel[i]];
			pot += nLevel[i] * 5 * mpTmp1[nLevel[i]];
			cash += nLevel[i] * 80 * mpTmp1[nLevel[i]];
		}	
		//物品奖励	
		//蓝色武器
		if ( random(2) )
			item = new(WEAPON_FILE->get_weapon_file_2(who->get_level()));
		else
			item = new(ARMOR_FILE->get_armor_file_2(who->get_level()));
		if ( item )
			ITEM_EQUIP_D->init_equip_prop_1(item);			
		//残缺宝石一颗或进阶书一本
		if ( random(2) )
		{
			item1 = new(sprintf("item/89/%d",8901+random(23)));
		}
		else
		{
			size = sizeof(Books);
			item1 = new (sprintf("/item/95/%s", Books[random(size)]));	
		}
			
	}
	else if ( type == 2 )
	{
		level = who->get_level();
		exp = 100 + level * level * 100;
		cash = level * 2000;
		//物品奖励	
		//金色武器
		if ( random(2) )
			item = new(WEAPON_FILE->get_weapon_file_2(who->get_level()));
		else
			item = new(ARMOR_FILE->get_armor_file_2(who->get_level()));
		if ( item )
			ITEM_EQUIP_D->init_equip_prop_3(item);	
		//完美宝石一颗或秘籍书一本
		if ( random(2) )
		{
			item1 = new(sprintf("item/89/%d",8951+random(23)));
		}
		else
		{
			size = sizeof(Books);
			item1 = new (sprintf("/item/96/%s", Books[random(size)]));	
		}
		item2 = new("/item/91/9167");
		if(item2) item2->set_amount(2);
	}			
	
	map_delete(mpTmp,id);
	if ( sizeof(mpTmp) == 0 )
		map_delete(mpBonus,who->get_number());
	save();
	
	who->add_exp(exp);
	who->add_cash(cash);
	who->add_potential(pot);
	if ( pot )
		send_user( who, "%c%s", '>',sprintf("你得到奖励: 经验 %d 金钱 %d 潜能 %d",exp,cash,pot));
	else
		send_user( who, "%c%s", '>',sprintf("你得到奖励: 经验 %d 金钱 %d",exp,cash));

	if ( item )
	{
		if( USER_INVENTORY_D->can_carry(who, item)  >=1 )
		{
			name = item->get_name();
			unit = item->get_unit();
			size = item->get_amount();
			if ( size == 0 ) size =1;
			i =item->move(who, -1);
			item->add_to_user(i);
			send_user( who, "%c%s", '>', sprintf("你得到%s",name) );
		}
		else
		{
			destruct(item);
		}		
	}					
	if ( item1 )
	{
		if( USER_INVENTORY_D->can_carry(who, item1)  >=1 )
		{
			name = item1->get_name();
			unit = item1->get_unit();
			size = item1->get_amount();
			if ( size == 0 ) size =1;
			i =item1->move(who, -1);
			item1->add_to_user(i);
			send_user( who, "%c%s", '>', sprintf("你得到%s", name) );
		}
		else
		{
			destruct(item1);
		}		
	}
	if ( item2 )
	{
		if( USER_INVENTORY_D->can_carry(who, item2)  >=1 )
		{
			name = item2->get_name();
			unit = item2->get_unit();
			size = item2->get_amount();
			if ( size == 0 ) size =1;
			i =item2->move(who, -1);
			item2->add_to_user(i);
			send_user( who, "%c%s", '>', sprintf("你得到 %s", name) );
		}
		else
		{
			destruct(item2);
		}		
	}	
	log_file("worldcup.txt",sprintf("%s %d %s 获得 e %d c %d p %d\n",short_time(),who->get_number(),who->get_name(),exp,cash,pot));
}
//生成新的投票信息
void get_new_vote(int num)
{
	int i,size,*index,*dates,j,count;
	mapping mpTmp;
	
	mpVote[num] = ([]);
	mpTmp = mpVote[num];	
	dates = sort_array(keys(GameDate),1);	

	for(i=0,size=sizeof(dates);i<size;i++)
	{
		if ( mapp(mpResult[dates[i]]) )
			continue;		
		index = GameDate[dates[i]];		
		for(j=0,count=sizeof(index);j<count;j++)
		{
			mpTmp[index[j]] = ([]);
		}
		mpResult[dates[i]] = ([]);
		save();
		break;
	}
}

void check_vote()
{
	int i,size=2,m,n,*index,dates,iSave,count;
	mapping mpTmp;
	mixed mixTime;
	
	for(i=0;i<size;i++)
	{
		count = 0;
		if ( !mapp(mpVote[i]) )	
			mpVote[i] = ([]);
		mpTmp = mpVote[i];
		//生成新的投票信息
		if ( sizeof(mpTmp) == 0 )
		{
			get_new_vote(i);
			continue;	
		}
		//检查赛果
		index = keys(mpTmp);
		for(m=0,n=sizeof(index);m<n;m++)
		{
			if ( mpTmp[index[m]]["finish"] )
			{
				count++;
				continue;
			}
			if ( GameList[index[m]]["score1"] == -1 )	//没有赛果
				continue;
			mixTime = localtime(GameList[index[m]]["time"]);
			mpTmp[index[m]]["finish"] = 1;
			mpResult[mixTime[TIME_YDAY]][index[m]] = ([ "vote1" : mpTmp[index[m]]["vote1"],"vote2" : mpTmp[index[m]]["vote2"] ]);
			iSave = 1;
			count++;
			add_bonus(i,index[m]);
		}
		//开始下一轮投票
		if( count == n )
		{
			mpVote[i] = ([]);
			get_new_vote(i);
		}
	}
	if ( iSave == 1 )
		save();
}

void check_time()
{
	remove_call_out("check_time");
	read_gamelist();
	check_vote();
	call_out("check_time",300);		
}

void drop_pai(object me, object who)
{
        object item, leader;
        string file, owner, id;
        int p, rate;
        int z, x, y;

	z = time();	
	if ( z < mktime(2006,6,5,0,0,0) || z > mktime(2006,7,9,0,0,0) )	//掉牌的时间范围
		return ;
        z = get_z(me);  x = get_x(me);  y = get_y(me);
        if ( z == 1 || z == 2 || z == 3 )
        	return ;
        id = who->get_leader();
        if (!id) owner = who->get_id();
        else
        {
        	if ( leader = find_player(id ) )
        	{
        		owner = leader->get_id();
		}      
		else
			owner = who->get_id();  		
	}


        rate = me->correct_drop_rate( me->get_level() - who->get_level() ) * 15 / 100;
	if ( random(1000) >= rate )
		return;
	file = sprintf("/item/04/040%d",random(4)+1);
        if( load_object(file) && ( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) ) )
        {
                item = new(file);
                item->set_user_id(owner);
                item->add_to_scene(z, p / 1000, p % 1000);
                item->set("winner", who);
                item->set( "time", time() );
        }
    
}


void set_score(object who,string arg)
{
	mapping mpTmp;
	int idx, score1, score2;
	
	remove_call_out("check_time");

	if ( sscanf(arg,"%d %d:%d", idx, score1,score2) != 3 )
	{
		if ( to_int(arg) == 999 )
		{
			mpResult = ([]);	//投票结束的信息
			mpVote = ([]);		//正在投票的信息
			mpBonus = ([]);
			mpChampion = ([]);
			winners = ([]);		
			GameList = ([]);
			GameDate = ([]);
			init_time = 0;
			save();
			tell_user(who,"所有赛果及奖励都消除了");
			check_time();	
			remove_call_out("check_time");
		}
		return ;	
	}
	mpTmp = GameList[idx];
	if ( !mapp(mpTmp) )
		return ;
	mpTmp["score1"] = score1;
	mpTmp["score2"] = score2;
	check_vote();
}
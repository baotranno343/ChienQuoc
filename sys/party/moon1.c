/*******************************
	**中秋活动**
*******************************/
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <public.h>
#include <time.h>
#include <action.h>
#include <skill.h>
inherit DBASE_F;
inherit SAVE_F;
#define DEBUG_STR(player,str) {tell_user(player,"str=%s",str);}

#define YUEBING	"item/04/mooncake"//这个到时候要改回去的，先注 一下。
#define YUEHUAN "item/04/0454"//月环。
//#define YUTU	"npc/party/yutu"
#define YUTU	"npc/party/0008"
int iStart,iFinish,iFinish_a,kkkk,close;
//object* nObjs= ({});//保存玩家的信息以便访问删除兔子的数量。
object change;
string *nWord = ({
	"让最圆的明月陪伴你和我，让明月传达我的心愿和祝福。祝，中秋快乐，月圆人圆事事圆。",
	"听到~想到~心到，说到~做到~得到，时间到，我的美好祝福和思念已经全让你收到。",
	"我的心在键盘上，等你来轻轻的敲击。天上的月，等有情人来寄望，中秋的夜晚我将明月和星星排成最美的祝福:中秋快乐。",
	"我楞楞的看着中秋的月亮，仿佛它是一面明镜，你我在互相注视绵绵思意和祝福。",
	"我将你的ID号码告诉了一个陌生人，他叫月老，他会在中秋月圆夜要帮我告诉你，我思念你。",
	"远方的朋友你是否无恙？在这个思念的季节里，改变的我的容颜，不变的永远的牵挂你的心！",
	"月缺时我想你，月圆时我念你，无论月圆月缺，我的心如那恒古不变的月亮默默追随着祝福你。",
	"月饼节到了！嘘！别吱声！对着屏幕乐一下！再乐一下！呵呵！我看到了！好了！愿你快乐！",
	"一缕情思一颗红豆，月圆时分我会让玉兔送去我特制的月饼！中秋快乐！",
	"看到那轮明月，就想起远方的你；沐浴月辉的温馨，就感受到你温柔的笑容。亲爱的，我想你。 ",
	"中秋佳节，远远的你吃圆圆的饼看圆圆的月想圆圆的事，不要忘了远方的我！ ",
	"天苍苍，野茫茫，有个人儿在远方。秋风吹，稻花香。中秋可否回故乡？ ",
	"明月本无价，高山皆有情。愿你的生活就像这十五的月亮一样，圆圆满满！送上香甜的月饼，连同一颗祝福的心",
	"网缘！情缘！月圆！中秋之夜寄相思，花好月圆情难圆。带去问候和思恋，心想事成愿缘圆。",
	"相思是一种浓浓的酒，总在举杯时散发出醉人的芬芳；乡愁是一份厚厚的情，总在月圆时轻唤起难言的惆怅。",
	"一个月亮一个你，二个影子我和你，三生有幸认识你，四个月来好想你，五湖四海寻找你，六神无主迷恋你，七星伴月围绕你，八月十五我等你。",
	"你是月饼我是馅，缠缠绵绵总见面；你是风筝我是线，追追逐逐把你牵；你是明月我是泉，美美满满一万年！",
	"每逢佳节倍思亲，你我感情似海深，月圆又是月明时，教我怎能不思君！",
	"流星划过天际，我错过了许愿；浪花拍上岩石，我错过了祝福；故事讲了一遍，我错过了聆听；人生只有一回，我庆幸没有错过你这个好友！今晚邀你共同赏月！ ",
	"酒越久越醇，朋友相交越久越真；水越流越清，世间沧桑越流越淡。祝朋友中秋佳节过得开心！ ",
	"去年圆月时，花灯亮如昼；月上柳梢头，人约黄昏后。今年圆月时，月与灯依旧；不见去年人，泪湿春衫袖。",
	"中秋相思，意浓浓；泪眼人儿，梦在怀；月是故乡明，人是你最好。",
	"清风送去了我的祝福，明月带来了我的问候，流星记载了往日的故事，玉兔留下了永恒的吉祥。祝你中秋佳节快乐，月圆人圆事事圆满！",
	"人隔千里、路悠悠，却待要问、终无凭，请明月代传讯，寄我片纸儿慰离情。",
	"露从今夜白，月是故乡明。今夜月正圆，正是思乡时。同望当空月，月圆梦未圆。",
	});
void get_chang();
void destruct_chang();
void generate_yutu();
void destroy_yutu();
void destroy_yuebing();
void generate_yuebing();
void yuetu_bonus(object player,object npc);
void update_record(object player);
void check_time2();
void paihangbang(object player,object npc);
void paihangbang_bonus(int vip,int potential,int cash,object player,object npc);
int check_yuebing(object who, int count,string name);
int give_yuebing(object who,string name, int count);
int exchange( object player,object npc);
int get_close();
// 函数:生成二进制码
void SAVE_BINARY() { }
string get_save_file()	{ return "data/zhongqiu"SAVE_EXTENSION;}
void create()
{	
	restore();
	iStart = mktime(2007,9,24,8,0,0);	
   	iFinish = mktime(2007,9,26,22,0,0);
	iFinish_a = mktime(2007,10,3,22,0,0);
	call_out("check_time",1);
}

void check_time()
{
	int iTime;
	mixed* mixTime;

	iTime = get_party_time();
	remove_call_out("check_time");
	
	if(iTime < iStart)
	{
		call_out("check_time",iStart - iTime);
		return;
	}
	if ( iTime > iFinish_a )
	{
		destroy_yuebing();
		destroy_yutu();	
		destruct_chang();
		return;
	}
	if(iTime > iFinish)
	{
		destroy_yuebing();
		destroy_yutu();	
		get_chang();
		call_out("destruct_chang",iFinish_a - iTime);
		return;
	}
	mixTime = localtime(iTime);
	if(mixTime[TIME_HOUR] >= 22)
	{
		destroy_yuebing();//在活动结束以后直接将玉兔和月饼从场景里面清除。
		destroy_yutu();	
		call_out("check_time",3600*24 - mixTime[TIME_HOUR]*3600 - mixTime[TIME_MIN]*60);
		return;
	}

/*	delete_save_2("record");//抓兔英雄榜的记录在第二天活动开始前都是有效的。 
	delete_save_2("player");//每次活动开始的时候，都将上次的记录给清除掉。
	save();
	YUTU->delete_2("player");//删除玩家兔子数量记录。*/

	if ( mixTime[TIME_HOUR] < 8 )
	{
		call_out("check_time",3600*8-mixTime[TIME_HOUR]*3600-mixTime[TIME_MIN]*60);
		return ;
	}
	check_time2();
}


void check_time2()
{
	int iTime;
	mixed *mixTime;
//	iTime = time();
	iTime = get_party_time();
	mixTime = localtime(iTime);
	get_chang();
	CHAT_D->sys_channel(0,"各位玩家中秋快乐！作为中华民族传统节日的中秋节已经来临，为了庆祝中秋团圆佳节，大话战国特别举办了为期三天的中秋活动来陪伴大家。大家现在赶快去"HIR "周国"NOR "寻找中秋活动员——"HIR "嫦娥"NOR "参与活动吧，她就在神仙爷爷的旁边哦。");
	log_file( "zhongqiu_log.dat", sprintf( "%d月%d日 %d :%d 当天的中秋活动开始。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
	if (mixTime[TIME_MIN]<30) 
	{
		kkkk=-1;
		generate_yutu();		
		log_file( "zhongqiu_log.dat", sprintf( "%d月%d日 %d :%d 放入玉兔。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
		call_out("check_time3",60*(30-mixTime[TIME_MIN]));
	}
	else
	{
		kkkk=1;
		generate_yuebing();
//		CHAT_D->sys_channel(0,HIR "据说七国城外到处都是月饼，不知道是不是真的，大家赶快去抢啊！");
		CHAT_D->rumor_channel( 0, CHAT+HIR "据说八国城外到处都是月饼，不知道是不是真的，大家赶快去抢啊！" );  
		log_file( "zhongqiu_log.dat", sprintf( "%d月%d日 %d :%d 放入月饼。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
		call_out("check_time3",60*(60-mixTime[TIME_MIN]));
	}
}

void check_time3()
{
	int iTime,rate,level,z,p,x,y;
	int i,*nScene,size;
	mixed *mixTime;
	object robber;
	
	remove_call_out("check_time3");
//	iTime = time();
	iTime = get_party_time();	
	mixTime = localtime(iTime);
	if (get_close()) return;
	if ( iTime > iFinish_a )
	{
		destroy_yuebing();
		destroy_yutu();	
		destruct_chang();
		return;
	}
	if ( iTime > iFinish )
	{
		destroy_yuebing();
		destroy_yutu();	
		USER_D->user_channel("各位玩家，中秋节活动开展了三天，在这段时间里，大家的踊跃参与让整个战国的气氛空前热烈，感谢大家。此次活动到此圆满结束，请排名前十的玩家赶快至嫦娥处领取排名奖励，领取时间至10月3日22:00截止。");
		log_file( "zhongqiu_log.dat", sprintf( "%d月%d日 %d :%d 中秋活动全部结束。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
		call_out("destruct_chang",iFinish_a - iTime);
		return;
	}
	if(mixTime[TIME_HOUR] >= 22)
	{
		destroy_yuebing();//在活动结束以后直接将玉兔和月饼从场景里面清除。
		destroy_yutu();	
		USER_D->user_channel("今天的中秋活动到此结束，明天的同一时间大家再来参加哦，祝大家中秋愉快。");
		call_out("check_time3",3600*24 - mixTime[TIME_HOUR]*3600 - mixTime[TIME_MIN]*60);
		log_file( "zhongqiu_log.dat", sprintf( "%d月%d日 %d :%d 当天的中秋活动结束。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
		return;
	}

	if ( mixTime[TIME_HOUR] < 8 )
	{
		call_out("check_time3",3600*8-mixTime[TIME_HOUR]*3600-mixTime[TIME_MIN]*60);
		return ;
	}
	if ( mixTime[TIME_HOUR] == 8 && mixTime[TIME_MIN] < 30 )
		CHAT_D->sys_channel(0,"各位玩家中秋快乐！作为中华民族传统节日的中秋节已经来临，为了庆祝中秋团圆佳节，大话战国特别举办了为期三天的中秋活动来陪伴大家。大家现在赶快去"HIR "周国"NOR "寻找中秋活动员——"HIR "嫦娥"NOR "参与活动吧，她就在神仙爷爷的旁边哦。");
	else
		CHAT_D->sys_channel(0,"大话战国中秋活动正在热烈进行中，想参与的话就去找中秋活动员——"HIR "嫦娥"NOR "吧，她就在"HIR "周国"NOR "等着你哦。");
	if ( kkkk == 1 )
	{
		generate_yutu();
		log_file( "zhongqiu_log.dat", sprintf( "%d月%d日 %d :%d 放入玉兔。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
	}
	if ( kkkk == -1 )
	{
		generate_yuebing();
		CHAT_D->rumor_channel( 0, CHAT+HIR "据说八国城外到处都是月饼，不知道是不是真的，大家赶快去抢啊！" );  
//		CHAT_D->sys_channel(0,HIR "据说七国城外到处都是月饼，不知道是不是真的，大家赶快去抢啊！");
		log_file( "zhongqiu_log.dat", sprintf( "%d月%d日 %d :%d 放入月饼。\n",mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN]) );
	}
	kkkk=-kkkk;
	call_out("check_time3",1800);
}

// 放入嫦娥
void get_chang()
{
	if ( !objectp(change) )
	{
		change = new("npc/party/0008");
		change->add_to_scene(80,286,178,4);
	}
}

// 移除嫦娥
void destruct_chang()
{
	if ( objectp(change) )
	{
		change->remove_from_scene();
		destruct(change);
	}
}

void generate_yutu()
{
	int i,z,p,x,y;
	object *nObj,npc;
	destroy_yutu();
	nObj = ({});	
	for(z=10;z<=80;z+=10)
	{
		for(i=0;i<50;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			npc = new("npc/party/yutu");
			if ( !objectp(npc) )
				continue;
			npc->add_to_scene(z,x,y);	
			nObj += ({ npc });	
		}
	}
	YUTU->set("npc",nObj);
}

void destroy_yutu()
{
	int i,size;
	object *nObj;
	nObj = 	YUTU->get("npc");
	for(i=0,size=sizeof(nObj);i<size;i++)
	{
		if ( !objectp(nObj[i])	)
			continue;
		nObj[i]->remove_from_scene();
		destruct(nObj[i]);
	}
	YUTU->delete("npc");
}
void generate_yuebing()
{
	int i,z,p,x,y;
	object *nObj,item;	
	destroy_yuebing();
	nObj = ({});
	for(z=10;z<=80;z+=10)
	{
		for(i=0;i<100;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new(YUEBING);
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			nObj += ({ item });
		}
	}
	YUTU->set("item",nObj);
}

void destroy_yuebing()
{
	int i,size;
	object *nObj;	
	nObj = YUTU->get("item");
	for(i=0,size=sizeof(nObj);i<size;i++)
	{
		if ( !objectp(nObj[i]) )
			continue;
		if ( get_d(nObj[i]) )
			continue;
		nObj[i]->remove_from_scene();
		destruct(nObj[i]);
	}
	YUTU->delete("item");
}
//设置中秋节活动的开启
int set_open(object who,string arg)
{
	int year,mon,day,hour,min;
	string cTmp1,cTmp2;
	if ( sscanf(arg ,"%s-%s",cTmp1,cTmp2) != 2 )
	{
		send_user(who,"%c%s",'!',"错误的格式！");	
		return 0;
	}
	year = to_int(cTmp1[0..3]);
	mon = to_int(cTmp1[4..5]);
	day = to_int(cTmp1[6..7]);
	hour = to_int(cTmp1[8..9]);
	min = to_int(cTmp1[10..11]);
	iStart = mktime(year,mon,day,hour,min,0);	//活动开始时间

	year = to_int(cTmp2[0..3]);
	mon = to_int(cTmp2[4..5]);
	day = to_int(cTmp2[6..7]);
	hour = to_int(cTmp2[8..9]);
	min = to_int(cTmp2[10..11]);
	iFinish = mktime(year,mon,day,hour,min,0);	//结束时间

	if ( !iStart || !iFinish )
	{
		send_user(who,"%c%s",'!',"错误的时间！");	
		return 0;
	}
	if ( iStart > iFinish || iFinish < time() )
	{
		send_user(who,"%c%s",'!',"错误的时间！！");	
		return 0;
	}
	tell_user(who,"中秋节活动开启:%s！",arg);	
	send_user(who,"%c%s",'!',"中秋节活动开启！");	
	save();
	call_out("check_time",3);
	return 1;
}
//设置中秋节活动的关闭
/*int set_close(object who)
{
	remove_call_out("check_time");
	iStart = 0;	
	iFinish = 0;		
	send_user(who,"%c%s",'!',"中秋节活动关闭！");	
	save();
	return 1;	
}*/
//获取中秋节活动状态。
/*int is_open()
{
	mixed* mixTime;
	int iHour,iDay,iTime;
	mixTime = localtime(get_party_time());
	iHour = mixTime[TIME_HOUR];
   	iDay = mixTime[TIME_MDAY];
   	iTime = get_party_time();
	if(!iStart || !iFinish)//设置活动开始和结束时间无效。
	{
		return 0;
	}
	if(iTime < iStart || iTime > iFinish)//还没有到时间以及已经活动过期。
	{
		return 0;
	}
	if(iDay == 24 || iDay == 25 || iDay == 26)//9月24 25 26 20:00-21:00
	{
		if(iHour == 20)
		{
			return 1;
		}
	}
	return 0;	
}*/
void do_look(object npc,object player)
{
	int index;
	string dailogue = "";
	string* choices1 = ({"交还月兔","抓兔英雄榜","月饼兑换","询问中秋活动规则","询问活动时间",});
	string* choices2 = ({"月饼兑换","交还月兔","抓兔英雄榜","领取英雄榜的奖励",});
	int iTime;
	mixed *mixTime;
	iTime = get_party_time();
	mixTime = localtime(iTime);
	if( iTime < iFinish )
//	if(is_open())
	{
		dailogue += "    中秋快乐！今天是中秋佳节，我带着玉兔从月宫专门来到战国里给大家庆祝节日，但是我刚到此地，却发现玉兔不见了！哎，可能它又不听话，装扮成月兔在战国里逍遥快活吧。你能帮我把它抓回来吗？\n";
		for(index = 0; index < 5;index++)
		{
			dailogue+=sprintf(ESC"%s\ntalk %x# welcome.%d\n",choices1[index],getoid(npc),index+2);
		}
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+dailogue+ESC"离开\n");
	}	
	else
	{
		dailogue += "    你需要我帮忙吗？\n";
		for(index = 0; index < 4; index++)
		{
			dailogue+=sprintf(ESC"%s\ntalk %x# welcome.%d\n",choices2[index],getoid(npc),index+7);
		}
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+dailogue+ESC"离开\n");	
	}	
}
void do_welcome( object npc, string arg )
{
	int flag,i,size,index,move,pos,record,index2,name_size;
	int id = getoid(npc);
       	object who,item,player,obj;  
       	string name,cTmp,id1,tmp="",cmd="",playername; 
        player = this_player();
        if ( sscanf(arg,"%d.%s",flag,id1) != 2 )//这里主要处理输入ID祝福的信息。
	{
        	flag = to_int(arg);
        }
        if(!flag)
        {
        	return;
        }
//        player->set_2("rabbit.day",localtime(get_party_time())[TIME_MDAY]);//记录与嫦娥交互的时间。	
        switch(flag)
        {
        case 1://乐意帮忙，我想知道月兔在哪里
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    在周国、齐国、韩国、赵国、魏国、秦国、楚国和燕国八个国家的附近，将会出现月兔，将它们用乾坤绳抓住之后回来交给我，即可获得奖励。我还会累计你的抓兔数量，并且将这个数量排名，如果你的名字能出现在抓兔英雄榜上，那么我将给予你一份中秋大礼哦，呵呵。\n"+ESC"确定\n");
        	break;
        case 2://交还月兔，排行
		if( get_party_time() > iFinish ) return ;
		if ( check_yuebing(player,1,"小月兔") != 1 )
		{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    很抱歉，你好像没有捕捉到月兔。\n"+ESC"确定\n");
			return ;
		}
		player->add_save("tuzi",1);
		yuetu_bonus(player,npc);//给玉兔奖励。
		update_record(player);//这里更新兔子数量记录以及排行榜。
		break;
        case 3://抓兔英雄榜,
		paihangbang(player,npc);
        	break;
        case 4://月饼兑换(前)
        	send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    中秋佳节倍思亲。在这个特别的节日里，你是否也有思念的人？你是否有很多话想对你思念的人说？那赶紧去搜集月饼吧！那赶紧去搜集月饼吧！我会帮助你实现愿望的哦！！\n"ESC"交出1个月饼兑换神秘礼物\ntalk %x# welcome.13\n"ESC"交出5个月饼向朋友发出温馨的祝福\ntalk %x# welcome.14\n"ESC"离开",npc->get_name(),id,id));  	
        	break;
        case 7://月饼兑换(后)
        	send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    中秋活动时间已经过了，不过我还是会帮你兑换奖励的！\n"ESC"交出1个月饼兑换神秘礼物\ntalk %x# welcome.13\n"ESC"离开",npc->get_name(),id,id));  	
        	break;
        case 5://询问中秋活动规则
        	send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    在活动期间，周国、齐国、韩国、赵国、魏国、秦国、楚国和燕国八个国家的附近，将会出现月兔，用"HIR "乾坤绳"NOR "将它们抓住之后回来交给我，即可获得奖励哦，我还会记录下你抓兔的数量，如果你能在"HIR "抓兔英雄榜"NOR "上获得名次，那将会获得中秋特别礼物一份，其中包含了极至神秘的新法宝——淬月之环！名列前三的玩家更会获得官方奖励VIP包一个哟。想要获得的话，就要努力抓兔哦！\n    另外在八个国家城外还会刷出月饼，只要拿着这些月饼也可以在我这里兑换一定的奖励哦！\n"ESC"确定\n",npc->get_name()));  	
        	break;	 
        case 6://询问活动时间
        	send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    活动时间是9月24日到9月26日，每天的08:00点到22:00点！\n"ESC"确定",npc->get_name()));
		break;
	case 8:
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    活动时间已经过了，交还月兔只能获得奖励，不会计入抓兔英雄榜哦！你确定要交还月兔吗？\n"+sprintf(ESC"确定\ntalk %x# welcome.12\n",getoid(npc))+ESC"离开\n");
		break;
        case 12://交还月兔，不排行
		if ( check_yuebing(player,1,"小月兔") != 1 )
		{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    很抱歉，你好像没有捕捉到月兔。\n"+ESC"确定\n");
			return ;
		}
		yuetu_bonus(player,npc);//给玉兔奖励。
		break;
        case 13://交出1个月饼兑换节日礼物
        	if(check_yuebing(player,1,"月饼") == 0   )
		{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    很抱歉哦，你的月饼好象数量不足，赶紧再去收集吧，呵呵！\n"ESC"确定",npc->get_name()));
			return ;	
		}
        	//给予月饼兑换的奖励。
        	exchange(player,npc);
        	break;
        case 14://交还5个月饼以向朋友发出温馨的祝福
        	if ( check_yuebing(player,5,"月饼") == 0 )
        	{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    很抱歉哦，你的月饼好象数量不足，赶紧再去收集吧，呵呵！\n"ESC"确定",npc->get_name()));
			return ;        			
        	}
		send_user( player, "%c%c%d%s", '?', 16, 30, "请您输入您好友的ID，我就能向您的朋友发出祝福。如果您输入0的话，就可以向所有玩家发出祝福:\n"+sprintf( ESC"talk %x# welcome.15",getoid(npc))+".%s\n");
        	break;
        case 15://处理温馨的祝福。
        	if ( !sizeof(id1) )
        		return ;
        	cTmp = nWord[random(sizeof(nWord))];
        	if ( id1 == "0" )
        		name = "大家";
		else
		{        
			i = to_int(id1);
			if ( !i )
				return ;	
        		obj = find_char(id1);
       			if ( !objectp(obj) )
			{
        			if( !( player->get_friend_id(i) ) )//玩家不在线并且不在好友列表，不发送祝福.
        			{
//					name = "大家";
					send_user(player,"%c%s",'!',"对不起，该玩家不存在");
					return ;
				}
				else
				{
					name = player->get_friend_name(i);
//					MAILBOX->send_mail(player,i,cTmp);
//					MAILBOX->sys_mail(obj->get_id(),obj->get_number(),cTmp);
				}				
			}
			else
				name = obj->get_name();
			if(name == player->get_name())
			{
				send_user(player,"%c%s",'!',"你不能跟自己发送祝福！");
				return;
			}						
		}
		if ( give_yuebing(player,"月饼",5) == 0 )
        	{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    很抱歉哦，你的月饼好象数量不足，赶紧再去收集吧，呵呵！\n"ESC"确定",npc->get_name()));
			return ;        			
        	}
        	cTmp = sprintf(HIY"%s"HIR "对"HIY"%s"HIR "说:%s",player->get_name(),name,cTmp); 		
		if (objectp(obj)) MAILBOX->sys_mail(obj->get_id(),obj->get_number(),cTmp);
        	CHAT_D->sys_channel(0,HIR+cTmp);
		send_user( CHAT_D->get_chat(), "%c%s", 0xA3, cTmp );
        	break;
	case 9://抓兔英雄榜,
		paihangbang(player,npc);
		break;
	case 10://领取排行榜的奖励
		if(get_save_2(sprintf("player.%d.bonus",player->get_number())))
		{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    你已经领取过该奖励，不能重复领取哦！\n"+ESC"确定\n");
			return;
		}
		pos = get_save_2(sprintf("player.%d.pos",player->get_number()));//在排行榜的位置。				
		if ( pos<1 || pos > 10 )
		{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    抱歉，你的名字并不在抓兔排行榜上哦！\n"+ESC"确定\n");
			return ;	
		}
//		if(player->get_2("rabbit.day")== localtime(get_party_time())[TIME_MDAY])
		{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    呵呵，你很厉害呢，这是给予你的奖励哦，请收下吧！\n"+sprintf(ESC"领取奖励。\ntalk %x# welcome.16\n",getoid(npc)),npc->get_name()));
		}
		break;
	case 16:
		if(get_save_2(sprintf("player.%d.bonus",player->get_number())))
		{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    你已经领取过该奖励，不能重复领取哦。\n"+ESC"确定\n");
			return;
		}	
		pos = get_save_2(sprintf("player.%d.pos",player->get_number()));//在排行榜的位置。
		if ( pos<1 || pos > 10 )
		{
			send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    抱歉，你的名字并不在抓兔排行榜上哦！\n"+ESC"确定\n");
			return ;	
		}
		switch(pos)
		{
		case 1:
			paihangbang_bonus(1,1000,100000,player,npc);
			break;
		case 2:
			paihangbang_bonus(1,900,90000,player,npc);
			break;
		case 3:
			paihangbang_bonus(1,800,80000,player,npc);
			break;
		case 4:
			paihangbang_bonus(0,700,70000,player,npc);
			break;
		case 5:
			paihangbang_bonus(0,600,60000,player,npc);
			break;
		case 6:
			paihangbang_bonus(0,500,50000,player,npc);
			break;
		case 7:
			paihangbang_bonus(0,400,40000,player,npc);
			break;
		case 8:
			paihangbang_bonus(0,300,30000,player,npc);
			break;
		case 9:
			paihangbang_bonus(0,200,20000,player,npc);
			break;	
		default:
			paihangbang_bonus(0,100,10000,player,npc);	
		}
		break;
        }      
}
//物品奖励
void move_to_user(object player, int amount_s, string name,object npc)
{
	int p,total,amount;
	object item;
	string name_s;
	item = new(name);
	if (item)
	{
		name_s=item->get_name();
		if( item->get_max_combined()>1 )
		{
			total = amount_s;
			amount = USER_INVENTORY_D->carry_combined_item(player, item, total);
		        if( amount > 0 && item->set_amount(amount) )
		        {
		                if( p = item->move(player, -1) )
		                {
		                        item->add_to_user(p);
		                }
		        }
		        else
		        {
		        	item->add_amount( -total );
		        }
		}
		else
		{
			if( p = item->move(player, -1) )
		        {
		                item->add_to_user(p);
		        }
		}
		USER_D->user_channel("恭喜"+player->get_name()+"在中秋节活动中获得"+HIR+name_s+"。\n");
	}
}
//给予排行榜的奖励
void paihangbang_bonus(int vip,int potential,int cash,object player,object npc)
{
	int flag = 0,iVipTime,iVip;
	int id = player->get_number();
	mixed* mixTime;

	if(sizeof_inventory(player, 1, MAX_CARRY) >= MAX_CARRY )
	{
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n	很抱歉，想要获得奖励，请清理你的道具栏空间。如果经验和潜能达到上限，也是不能领取奖励的哟。"+ESC"确定\n");
		return;
	}
	move_to_user(player,1,YUEHUAN,npc);
	if(vip)//给出VIP效果到玩家身上。
	{
		iVip = player->get_vip();
		if ( iVip != 0 && iVip != 1 )
			return 0;
		iVipTime = player->get_save_2("vip_package.time");
		if ( iVipTime == 0 )
			iVipTime = time()+3600*24*31;
		else 
			iVipTime += 3600*24*31;
		if ( iVip == 0 )
			player->delete_save_2("vip_package");
		player->delete_save_2("vip_package.trial");	//试用VIP包
		player->set_vip(1);
		player->add_save_2("vip_package.doubles",4);
		player->set_save_2("vip_package.time",iVipTime);
		player->add_title("V001");
		send_user( player, "%c%w%w%c", 0x81, 7401, 999, EFFECT_GOOD );
		USER_ENERGY_D->count_cp(player);
		USER_ENERGY_D->count_pp(player);
		USER_ENERGY_D->count_ap(player);
		USER_ENERGY_D->count_dp(player);
		mixTime = localtime(iVipTime);
		send_user(player,"%c%s",';',sprintf("你绑定了VIP包，VIP绑定的到期时间是%d-%02d-%02d %02d:%02d:%02d。观察VIP效果描述即可了解到期时间。你也可以去找神仙爷爷查询VIP绑定到期的时间。",mixTime[TIME_YEAR],mixTime[TIME_MON]+1,mixTime[TIME_MDAY],mixTime[TIME_HOUR],mixTime[TIME_MIN],mixTime[TIME_SEC]));
		send_user( player, "%c%w%s", 0x82, 7401, "item/sell/0061"->get_loop_desc(player));
		send_user( player, "%c%c%c", 0xA2, 4, 1);
		send_user( player, "%c%c%c", 0xA2, 3, 3-player->get_save_2("vip_package.revive.count"));
		"item/sell/0061"->send_vip_to_friend(player,1);
		USER_D->user_channel("恭喜"+player->get_name()+"在中秋节活动中获得"+HIR+"VIP包"+"。\n");
	}
	player->add_potential(potential);//潜能
	player->add_cash(cash);//金钱	
	set_save_2(sprintf("player.%d.bonus",id),1);
	save();
}
void paihangbang(object player,object npc)
{
	int index,pos,name_size,id;  
       	string tmp="",cmd="",playername,blank="";
       	blank = repeat_string(" ",12); 

	for(index = 1; index<=5;index++)
	{
		id = get_save_2(sprintf("record.%d",index));//找到index位置所对应的id.
		if(!id)
		{
			tmp = sprintf(" ""%2d．%12s%4s%4s",index,blank,":\t","空缺");
			tmp+="\t\t";
			tmp += sprintf(" ""%2d．%12s%4s%4s",index+5,blank,":\t","空缺");
			tmp+="\n";
		}
		else
		{
			playername = get_save_2(sprintf("player.%d.name",id));
			name_size = strlen(playername);
			if(name_size<=12)
			{
				playername+= repeat_string(" ",12-name_size);
			}
			switch(index)
			{
			case 1:
				tmp = sprintf(" ""R""%2d．%12s%4s%4d"NOR,1,playername,":\t",get_save_2(sprintf("player.%d.count",id)));
					//tmp+="      ";
				break;
			case 2:
				tmp = sprintf(" ""M""%2d．%12s%4s%4d"NOR,2,playername,":\t",get_save_2(sprintf("player.%d.count",id)));
					//tmp+="  ";
				break;
			case 3:
				tmp = sprintf(" ""B""%2d．%12s%4s%4d"NOR,3,playername,":\t",get_save_2(sprintf("player.%d.count",id)));
					//tmp+="   ";
				break;
			case 4:
				tmp = sprintf(" ""%2d．%12s%4s%4d",4,playername,":\t",get_save_2(sprintf("player.%d.count",id)));	//+BLK+BLK
					//tmp+="       ";
				break;		
			case 5:
				tmp = sprintf(" ""%2d．%12s%4s%4d",5,playername,":\t",get_save_2(sprintf("player.%d.count",id)));	//+BLK+BLK
				break;							
			}	
			tmp+="\t\t";
			id = get_save_2(sprintf("record.%d",index+5));
			if(!id)
			{
				tmp += sprintf(" ""%2d．%12s%4s%4s",index+5,blank,":\t","空缺");
			}
			else
			{
				playername = get_save_2(sprintf("player.%d.name",id));
				name_size = strlen(playername);
				if(name_size<=12)
				{
					playername+= repeat_string(" ",12-name_size);
				}
				tmp += sprintf(" ""%2d．%8s%4s%4d",index+5,playername,":\t",get_save_2(sprintf("player.%d.count",id)));
//				tmp += sprintf(" ""%2d．%8s%4s%4d",index+5,get_save_2(sprintf("player.%d.name",id)),":\t",get_save_2(sprintf("player.%d.count",id)));//+BLK+BLK
			}		
			tmp+="\n";
		}
		cmd+=tmp;
		
	}
//	log_file("zhongqiu.txt",short_time() + "\n"+cmd );
       	send_user( player, "%c%c%w%s", ':',3,npc->get_char_picid(), sprintf("抓兔英雄榜（你现在已经交了%d只月兔） \n",player->get_save("tuzi"))+cmd
		+ESC "确定\n");
}
int exchange( object player,object npc) 
{
	int rand,p,cash,exp,pot;
	if(sizeof_inventory(player, 1, MAX_CARRY) >= MAX_CARRY )
	{
		send_user(player,"%c%s",'!',"你身上的道具栏空间不够，无法领取奖励，很抱歉，下次兑换奖励时可要注意哦。");
		return;
	}
	if ( give_yuebing(player,"月饼",1) == 0 )
        {
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    很抱歉哦，你的月饼好象数量不足，赶紧再去收集吧，呵呵！\n"ESC"确定",npc->get_name()));
		return ;        			
        }
	rand = random(10000);
	if(rand < 2000)
	{
		move_to_user(player, 1, "item/91/9101",npc);//活络丸。
	}
	else if(rand < 4000)
	{
		move_to_user(player, 1, "item/91/9111",npc);//安神丸。
	}
	else if(rand < 5500)
	{
		move_to_user(player, 1, "item/91/9102",npc);//造化丹。	
	}
	else if(rand < 7000)
	{
		move_to_user(player, 1, "item/91/9112",npc);//补心丹。		
	}
	else if(rand < 8000)
	{
		move_to_user(player, 1, "item/91/9120",npc);//救急丹。	
	}
	else if(rand < 9000)
	{
		move_to_user(player, 1, "item/91/9121",npc);//活心丹。
	}
	else if(rand < 9450)
	{
		player->add_cash(20000);//20000金钱
		USER_D->user_channel("恭喜"+player->get_name()+"在中秋节活动中获得"+HIR "20000金钱"+"。\n");
	}
	else if(rand < 9850)
	{
		move_to_user(player,1,"item/44/4488",npc);//随机 宠物技能丹
	}
	else if(rand < 9990)
	{
		move_to_user(player,1,"item/std/8000",npc);//藏宝图
	}
	else
	{
		move_to_user(player,1,YUEHUAN,npc);//月环
	}
	send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n    祝你中秋快乐，节日礼物已经送给了你，请快快查看一下吧！\n",npc->get_name()));
}
//检查玩家道具栏上面是否有count个name。是的话，就返回1，否则返回0。
int check_yuebing(object who, int count,string name)
{
	int i,size,amount;
	object *inv,item;	
	inv = all_inventory(who, 1, MAX_CARRY*4);
	if(!inv)
	{
		return 0;
	}
	if( !(objectp( item = present(name, who, 1, MAX_CARRY*4) )) || (item->is_zhongqiu() != 1) )
	{		
		return 0;	
	}		
	for(i=0,size=sizeof(inv);i<size;i++)
	{
		if ( !objectp(inv[i]) )
			continue;
		if ( inv[i]->get_name() != name || inv[i]->is_zhongqiu() != 1 )
			continue;
		if ( inv[i]->is_combined() )//如果可以叠加的话，那么就增加叠加的数量。
			amount += inv[i]->get_amount();		
		else
			amount ++;
	}
	if ( amount < count )
	{
		return 0;	
	}
	return 1;
}
//如果玩家身上有足够的count个数目，那么就遍历道具栏进行扣除。
int give_yuebing(object who, string name,int count)
{
	int i,size,amount;
	object *inv,item;	
	if ( check_yuebing(who,count,name) != 1 )
		return 0;
	inv = all_inventory(who, 1, MAX_CARRY*4);
	for(i=0,size=sizeof(inv);i<size;i++)
	{
		if ( !objectp(inv[i]) )
			continue;
		if ( inv[i]->get_name() != name || inv[i]->is_zhongqiu() != 1 )//
			continue;
		amount = inv[i]->get_amount();
		if ( count >= amount )
		{
			count -= amount;//这里做个修正。如果玩家给的数量超过实际道具栏上对应物品数量的话。
			inv[i]->remove_from_user();//这里将玩家道具栏上的对应物品清光。
			destruct(inv[i]);			
		}
		else//否则减去相应数目。
		{
			inv[i]->add_amount(-count);
			count = 0;	
		}
		if ( count <= 0 )
			break;
	}
	return 1;		
	
}

//在交还月兔的时候，更新月兔的数量记录排行榜。
void update_record(object player)
{
	/*
	首先获得玩家的id信息，如果有的话，
	那么就找他的id对应的月兔数量记录，并且累加1
	如果排行榜名单个数小于10的话，那么就将这个新来的添加到排行榜上面，
	要记住这个玩家的id,玩家的position,以及这个排行榜的大小。
	如果排行榜名单个数大于10的话，那么就进行比较，找出排行榜上面月兔数量比自己少的，
	这样的话，就将那个比自己少的删除掉，并且将自己加入到排行榜上面。
	最后进行全部数据的排序。
	*/
	int size,index,pos,oldid,id1,amount,i;
	int id = player->get_number();
	string name = player->get_name();
//	amount = YUTU->get_2(sprintf("player.%d.rabbit",id));//增加该玩家的排行榜兔子数量。
	amount = player->get_save("tuzi");//获取该玩家的排行榜兔子数量。
	if(get_save_2(sprintf("player.%d",id)))
	{
		if(get_save_2(sprintf("player.%d.name",id))== name)//找到原来排行榜上已经有记录的玩家，
		{
//			add_save_2(sprintf("player.%d.count",id),1);//并且将记录增加1。
			set_save_2(sprintf("player.%d.count",id),amount);
			pos = get_save_2(sprintf("player.%d.pos",id));//获得对应玩家在排行榜上的位置。
		}
	}
	else if((size = get_save_2(sprintf("record.size"))) < 10)//判断排行榜的大小是否已经超出10。
	{
			pos = size+1;
			set_save_2("record.size",pos);//更新排行榜的大小。
			set_save_2(sprintf("record.%d",pos),id);//保存排行榜pos位置对应的id。
			set_save_2(sprintf("player.%d.name",id),name);//保存id玩家的姓名
			set_save_2(sprintf("player.%d.pos",id),pos);
			set_save_2(sprintf("player.%d.count",id),amount);//保存玩家交还月兔的数目。
	}
	else 
	{
		oldid = get_save_2(sprintf("record.%d",size));
		if(get_save_2(sprintf("player.%d.count",oldid))< amount)
		{
			pos = size;
			delete_save_2(sprintf("player.%d",oldid));//删除这个旧记录
			set_save_2(sprintf("record.%d",pos),id);//保存排行榜玩家当前排行上的id。
			set_save_2(sprintf("player.%d.name",id),name);//保存玩家的姓名
			set_save_2(sprintf("player.%d.pos",id),pos);//记录名次
			set_save_2(sprintf("player.%d.count",id),amount);//保存玩家交还月兔的数目。
			set_save_2("record.size",pos);//保存排行榜的大小。		
		}
	}
	if(pos)
	{
		for(index = pos; index > 1; index--)
		{
			id = get_save_2(sprintf("record.%d",index));
			id1 = get_save_2(sprintf("record.%d",index-1));
			if(get_save_2(sprintf("player.%d.count",id1))>= get_save_2(sprintf("player.%d.count",id)))
			{
				break;
			}
			set_save_2(sprintf("record.%d",index),id1);			
			set_save_2(sprintf("player.%d.pos",id1),index);
			set_save_2(sprintf("record.%d",index-1),id);
			set_save_2(sprintf("player.%d.pos",id),index-1);	
		}
		save();
	}
	
}

//交还月兔，获得奖励
void yuetu_bonus(object player,object npc)
{
	int rand,id,move,level;
	int *decoration = ({HEAD_TYPE,NECK_TYPE,ARMOR_TYPE,WAIST_TYPE,BOOTS_TYPE});
        string *nFamily = ({"Đào Hoa Nguyên", "Thục Sơn", "Cấm Vệ Quân", "Đường Môn", "Mao Sơn", "Côn Luân", "Vân Mộng Cốc", });
	string *nTmp;
	object item;
	rand = random(10000);
	id = player->get_number();
	if(sizeof_inventory(player, 1, MAX_CARRY) >= MAX_CARRY )
	{
		send_user(player,"%c%s",'!',"你身上的道具栏空间不够，无法领取奖励，很抱歉，下次兑换奖励时可要注意哦。");
		return;
	}
	if ( give_yuebing(player,"小月兔",1) == 0 )
        {
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),sprintf("%s:\n   很抱歉，你好像被没有捕捉到月兔。\n"ESC"确定",npc->get_name()));
		return ;        			
        }
//        YUTU->add_2(sprintf("player.%d.rabbit",id),1);//增加该玩家的排行榜兔子数量。
	if(rand < 2000)
	{
		move_to_user(player, 1, YUEBING,npc);//月饼。
	}
	else if(rand < 4000)
	{

		move_to_user(player, 1, "item/91/9102",npc);//造化丹。		
	}
	else if(rand < 6000)
	{
		move_to_user(player, 1, "item/91/9112",npc);//补心丹。		
	}
	else if(rand < 7000)
	{
		move_to_user(player, 1, "item/91/9120",npc);//救急丹。		
	}
	else if(rand < 8000)
	{
		move_to_user(player, 1, "item/91/9121",npc);//活心丹。
	}
	else if(rand < 9900)//10000金钱
	{
		player->add_cash(10000);
		USER_D->user_channel("恭喜"+player->get_name()+"在中秋节活动中获得"+HIR "10000金钱"+"。\n");
	}
	else if(rand < 9990)//随机门派的金色装备1件。
	{
		if ( (level=player->get_level()+5) >= 120 ) level=120;
		nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],random(2),level,decoration[random(sizeof(decoration))]);
		if ( sizeof(nTmp) )
		{	
			item = new(nTmp[random(sizeof(nTmp))]);
			if ( !item )
				return;
			ITEM_EQUIP_D->init_equip_prop_3(item);
		}
		move = item->move(player,-1);
		if(move)
		{
			item->add_to_user(move);
			USER_D->user_channel("恭喜"+player->get_name()+"在中秋节活动中获得"+HIR+item->get_name()+"。\n");
		}	
		else
			destruct(item);
	}
	else //随机门派的金色武器1件
	{
		if ( (level=player->get_level()+5) >= 120 ) level=120;
		nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],random(2),level,WEAPON_TYPE);
		if ( sizeof(nTmp) )
		{	
			item = new(nTmp[random(sizeof(nTmp))]);
			if ( !item )
				return;
			ITEM_EQUIP_D->init_equip_prop_3(item);
		}
		move = item->move(player,-1);
		if(move)
		{
			item->add_to_user(move);
			USER_D->user_channel("恭喜"+player->get_name()+"在中秋节活动中获得"+HIR+item->get_name()+"。\n");
		}	
		else
			destruct(item);
	}
	if( get_party_time() > iFinish ) 
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    谢谢你的帮忙，这是给你的奖励。\n"+ESC"确定\n");
	else
		send_user(player,"%c%c%w%s",':',3,npc->get_char_picid(),npc->get_name()+":\n"+"    谢谢你的帮忙，这是给你的奖励，你的抓兔数量我已经记下了，请继续努力吧。\n"+ESC"确定\n");
}

void before_destruct()
{
	if ( objectp(change) )
	{
		change->remove_from_scene();
		destruct(change);
	}
}

//交还月兔，获得金色装备或者金色武器。
/*void equipment(string*schoolname, int*gender,int*decoration,object player)
{
	int level,move;
	object present; 
	string* gold_equip = ({});
	level = player->get_level();
	level = level+random(10)+1;
	if(level > 120)
	{
		level = 120;
	}
	gold_equip = WEAPON_FILE->get_family_equip(schoolname[random(sizeof(schoolname))],gender[random(sizeof(gender))],level,decoration[random(sizeof(decoration))]);
	if(sizeof(gold_equip)> 0)
	{
		present = new(gold_equip[random(sizeof(gold_equip))]);
		if(!present)
		{
			return;
		}
		ITEM_EQUIP_D->init_equip_prop_3(present);
		if( move = present->move(player, -1) )
	        {
	                present->add_to_user(move);
	                USER_D->user_channel("恭喜"+player->get_name()+"在中秋节活动中获得"+HIR+present->get_name()+"。\n");
	        }
	        else
	        {
	        	destruct(present);
	        }
	}
}*/

//活动开关
int get_close()
{
	return close;
}

void set_close()
{
	close=1;
	destruct_chang();
	destroy_yutu();
	destroy_yuebing();
}
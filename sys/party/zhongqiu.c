/*****
洒月饼，玉兔
****/

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <public.h>
#include <time.h>
#include <action.h>
#include <skill.h>

#define YUEBING	"item/04/0408"
#define YUTU	"npc/party/0009"

int iStart,iFinish;
object change,change1;
int *nScene = ({1,10,20,30,40,50,60,70});
string *nWord = ({
	"让最圆的明月陪伴你和我，让明月传达我的心愿和祝福。祝，中秋快乐，月圆人圆事事圆。",
	"听到~想到~心到，说到~做到~得到，时间到，我的美好祝福和思念已经全让你收到。",
	"我的心在键盘上，等你来轻轻的敲击。天上的月，等有情人来寄望，中秋的夜晚我将明月和星星排成最美的祝福：中秋快乐。",
	"我楞楞的看着中秋的月亮，仿佛它是一面明镜，你我在互相注视绵绵思意和祝福。",
	"我将你的ID号码告诉了一个陌生人，他叫月老，他会在中秋月圆夜要帮我告诉你，我思念你。",
	"远方的朋友你是否无恙？在这个思念的季节里，改变的我的容颜，不变的永远的牵挂你的心！",
	"月缺时我想你，月圆时我念你，无论月圆月缺，我的心如那恒古不变的月亮默默追随着祝福你。",
	"月饼节到了！嘘！别吱声！对着屏幕乐一下！再乐一下！呵呵！我看到了！好了！愿你快乐！",
	"一缕情思一颗红豆，月圆时分我会让玉兔送去我特制的月饼！中秋快乐！",
	"海上生明月，天涯共此时。",
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

void generate_yutu();
void destroy_yutu();
void destroy_yuebing();
void generate_yuebing();
int check_yuebing(object who, int count);
int give_yuebing(object who, int count);
int exchange( object who,object me,object yuebing);
void yutu_message();
void yuebing_message();

// 函数：生成二进制码
void SAVE_BINARY() { }

void create()
{
	iStart = mktime(2006,10,10,0,0,0);	
	iFinish = mktime(2006,10,18,0,0,0);	
	call_out("check_time",1);
}

void check_time()
{
	int iHour;
	mixed *mixTime;

	remove_call_out("check_time");
	if ( "sys/main/main"->get_host_type() != 2 )
		return ;
	iHour = time();
	if ( iHour > iFinish )
		return ;
	if ( iHour < iStart )
	{
		call_out("check_time",3600*6);
		return ;
	}
	if ( !objectp(change) )
	{
		change = new("npc/party/0008");
		change->add_to_scene(80,294,191);
	}
	if ( !objectp(change1) )
	{
		change1 = new("npc/party/0008");
		change1->add_to_scene(1,205,170,4);
	}
	mixTime = localtime(time());
	iHour = mixTime[TIME_HOUR];
	
	call_out("check_time",60*(60-mixTime[TIME_MIN]));
	if ( YUTU->get("dates") != mixTime[TIME_YDAY] )
	{
		YUTU->delete("send_yutu");
		YUTU->delete("send_yb");
		YUTU->set("dates",mixTime[TIME_YDAY]);	
	}
	if ( iHour == 9 || iHour == 14 || iHour == 18 || iHour == 21 )	//预告玉兔
	{
		if ( mixTime[TIME_MIN] >= 55 )
		{
			yutu_message();
		}
		else
		{
			remove_call_out("yutu_message");
			call_out("yutu_message",60*(55-mixTime[TIME_MIN]));
		}	
	}
	if ( iHour%2 )	//预告月饼
	{
		if ( mixTime[TIME_MIN] >= 55 )
		{
			yuebing_message();
		}
		else
		{
			remove_call_out("yuebing_message");
			call_out("yuebing_message",60*(55-mixTime[TIME_MIN]));
		}		
	}
//	if ( iHour == 9 || iHour == 15 || iHour == 16 || iHour == 20 || iHour == 23 )	//预告双倍
//		CHAT_D->sys_channel(0,HIY"为答谢玩家对大话战国online的支持，特在国庆节与中秋节之际，每天向玩家赠送1个小时的双倍经验，请玩家去周天坛或新手村的嫦娥处领取。");
		
	if ( iHour == 10 || iHour == 15 || iHour == 19 || iHour == 22 )	//刷新玉兔
	{
		if ( YUTU->get("send_yutu") != iHour )
		{
			generate_yutu();
			YUTU->set("send_yutu",iHour);
		}
	}
	else if ( iHour == 12 || iHour == 17 || iHour == 21 || iHour == 0 )
	{
		destroy_yutu();
	}
	if ( !(iHour%2) && (YUTU->get("send_yb") != iHour+1) )	//刷新月饼
	{
		destroy_yuebing();
		generate_yuebing();		
		YUTU->set("send_yb",iHour+1);
	}
	
}

void generate_yutu()
{
	int i,size,z,p,x,y;
	object *nObj,npc;
	
	nObj = ({});
	for(z=10;z<=70;z+=10)
	{
		for(i=0;i<50;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			npc = new(YUTU);
			if ( !objectp(npc) )
				continue;
			npc->add_to_scene(z,x,y);	
			nObj += ({ npc });
//			log_file("zhongqiu.txt",sprintf("%s %d %d %d %d\n",short_time(),i,z,x,y));	
		}
	}
	log_file("zhongqiu.txt",short_time() + " 放兔子\n" );
	YUTU->set("npc",nObj);
	CHAT_D->sys_channel(0,HIR "嫦娥仙子的玉兔因为贪吃跑到凡间，并混入了野兔群，请各路英雄在国家城外帮忙寻回交给嫦娥仙子。");
}

void destroy_yutu()
{
	int i,size,z,p,x,y;
	object *nObj,npc;

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

void before_destruct()
{
	if ( objectp(change) )
	{
		change->remove_from_scene();
		destruct(change);
	}
	if ( objectp(change1) )
	{
		change1->remove_from_scene();
		destruct(change1);
	}
}



void generate_yuebing()
{
	int i,size,z,p,x,y,j,count;
	object *nObj,item;
	
	destroy_yuebing();
	nObj = ({});
	for(j=0,count=sizeof(nScene);j<count;j++)
	{
		z = nScene[j];
		for(i=0;i<80;i++)
		{
			if( !( p = efun::get_xy_point( z, IS_CHAR_BLOCK ) ) )
				continue;
			x = ( p % 1000000 ) / 1000;  y = p % 1000;
			item = new(YUEBING);
			if ( !objectp(item) )
				continue;
			item->add_to_scene(z,x,y);	
			nObj += ({ item });
//			log_file("zhongqiu.txt",sprintf("%s %d %d %d %d\n",short_time(),i,z,x,y));	
		}
	}
	log_file("zhongqiu.txt",short_time() + " 放月饼\n" );
	YUTU->set("item",nObj);
	CHAT_D->rumor_channel(0,HIR "嫦娥撒月饼啦，大家快去抢阿！");
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
		nObj[i]->remove_from_scene();
		destruct(nObj[i]);
	}
	YUTU->delete("item");
}

//捕抓玉兔
void get_yutu(object me, object who)
{
	int iExp;
	object item;
	
	if ( !who->is_yutu() )
	{
                send_user(me, "%c%s", '!', "不能捕抓对方。");
                return ;        	
        }
	if (distance_between(me, who)>7)
        {
                send_user(me, "%c%s", '!', "您距离目标太远。");
                return ;        	
        }
        if( !objectp( item = present("乾坤绳", me, 1, MAX_CARRY) ) )
        {
                send_user(me, "%c%s", '!', "您得有乾坤绳才能捕抓。");
                return ;
        }
	if ( me->get_save("tanciyutu") )
	{
                send_user(me, "%c%s", '!', "您已经给嫦娥找到玉兔了，为什么还来找呢？");
                return ;        	
        }
	item->add_amount(-1);     	
	if ( random(100) < 90 )
	{
                send_user(me, "%c%s", '!', "捕抓失败！");
                return ;        	
        }
        if ( random(100) < 90 )
        {
        	iExp = me->get_level() * 20 ;
        	me->add_exp(iExp);
                send_user(me, "%c%s", ';', sprintf("很可惜，您捕捉的兔子并不是嫦娥的玉兔，不过还是会得到%d经验的奖励哦！",iExp));
        }
        else
        {
                send_user(me, "%c%s", ';', "您成功帮助嫦娥寻回玉兔，赶快去周国天坛交还给嫦娥吧，说不定有大礼等着您呢！");
        	me->set_save("tanciyutu",1);
        }
	who->remove_from_scene(FALL_ACT);
	destruct(who);
}

void do_look(object me,object who)
{
	int id = getoid(me),i;
	i = time();
//	if ( i >iStart && i < iFinish )
//		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    嫦娥仙子祝你国庆与中秋快乐！心想事成！\n"ESC"交还玉兔\ntalk %x# welcome.1\n"ESC"月饼兑换\ntalk %x# welcome.3\n"ESC"领取双倍经验时间\ntalk %x# welcome.8\n"ESC"离开",me->get_name(),id,id,id));
//	else
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    嫦娥仙子祝你国庆与中秋快乐！心想事成！\n"ESC"交还玉兔\ntalk %x# welcome.1\n"ESC"月饼兑换\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),id,id,id));
		
}

void do_welcome( object me, string arg )
{
	int flag,i;
	int id = getoid(me);
       	object who,item,player;  
       	string name,cTmp,id1; 
	mixed *mixTime;
        who = this_player();
        if ( sscanf(arg,"%d.%s",flag,id1) != 2 )
        	flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_save("tanciyutu") )
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    中秋节到了，这玉兔因为贪吃凡间的月饼，竟然私自下凡，混入七国城外（除周国）的野兔群中，还真是谢谢你替我找回了玉兔，这个中秋节礼物就送给你了！\n"ESC"领取奖励\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),id));
		else
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    这兔子不知道跑哪偷月饼吃去了，你去七国城外（除周国）好好找找吧，能替我找回来，我一定送你一份大礼！\n"ESC"离开",me->get_name()));
        	break;
        case 2:
		if ( who->get_save("tanciyutu") )
		{
			i = random(100);
			if ( i < 10 )	//兔娃娃
			{
				item = new("item/final/16/1636");
				cTmp = "一只"HIR "可爱的兔娃娃";	
			}	
			else if ( i < 35 )	//Thẻ Biến Thân
			{
				item = new("item/04/0407");	
				cTmp = "一张"HIR "Thẻ Biến Thân";	
			}
			else			//中秋节大礼包
			{
				item = new("item/04/0406");	
			}
			if ( !objectp(item) )
				return ;
			i = item->move(who,-1);
			if ( !i )
			{
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    您身上不够空间放我送给您的礼物，建议您清空了再来找我哦～\n"ESC"离开",me->get_name()));
				return ;
			}
			item->add_to_user(i);
                	send_user(who, "%c%s", ';', "恭喜您！您得到了嫦娥赠送的中秋节礼物——"HIG+item->get_name());
        		if ( cTmp )
        			CHAT_D->sys_channel(0,sprintf("恭喜%s获得了%s",who->get_name(),cTmp));
			who->delete_save("tanciyutu");
		}
		break;
        case 3:
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    中秋佳节倍思亲。在这个特别的节日里，你是否也有思念的人？你是否有很多话想对你思念的人说？那赶紧去搜集月饼吧！姐姐会帮助你实现愿望的哦！\n"ESC"交出3个月饼向朋友发出温馨的祝福\ntalk %x# welcome.4\n"ESC"交出1个月饼兑换神秘礼物\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),id,id));
        	break;
        case 4:
        	if ( check_yuebing(who,3) == 0 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的月饼好像不多嘢。姐姐建议你到其他国家的城外走走，说不定有意外的惊喜呢～\n"ESC"离开",me->get_name()));
			return ;        			
        	}
		send_user( who, "%c%c%d%s", '?', 16, 30, "在框中输入您好友的ID，姐姐就能向您的朋友发出祝福。如果您输入0的话，就可以向全服务器的玩家发出祝福。\n"+sprintf( ESC"talk %x# welcome.6",getoid(me))+".%s\n");		
        	break;
        case 5:
        	if( !objectp( item = present("月饼", who, 1, MAX_CARRY) ) || item->is_zhongqiu() != 1 )
	       	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的月饼好像不多嘢。姐姐建议你到其他国家的城外走走，说不定有意外的惊喜呢～\n"ESC"离开",me->get_name()));
			return ;        			
        	}
        	exchange(who,me,item);
        	break;
        case 6:
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
        		player = find_char(id1);
			if ( !objectp(player) )
			{
        			if( !( who->get_friend_id(i) ) )
        			{
					send_user(who,"%c%s",'!',"该玩家不在线并且不在好友列表，不能发送祝福！");
					return ;
				}
				name = who->get_friend_name(i);
			}
			else
				name = player->get_name();
			MAILBOX->send_mail(who,i,cTmp);			
		}
		if ( give_yuebing(who,3) == 0 )
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的月饼好像不多嘢。姐姐建议你到其他国家的城外走走，说不定有意外的惊喜呢～\n"ESC"离开",me->get_name()));
			return ;        			
        	}
        	cTmp = sprintf("%s对%s说：%s",who->get_name(),name,cTmp); 		
        	CHAT_D->sys_channel(0,HIR+cTmp);
		send_user( CHAT_D->get_chat(), "%c%s", 0xA3, HIY+cTmp );
		if ( random(1000)>4 )
			return ;
		item = new("item/04/0405");
		i = item->move(who,-1);
		if ( !i )
		{
			destruct(item);
			return ;
		}
		item->add_to_user(i);
		send_user(who,"%c%s",'!',"恭喜你，得到了奖品礼包。");
        	break;
        case 7:
        	return ;
        	if ( time() < iStart )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    还没到领双的时间。祝你游戏愉快！\n"ESC"离开",me->get_name()));
        		return ;	
        	}
		if ( time() > iFinish )
		{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    这里的领双活动已经结束了。祝你游戏愉快！\n"ESC"离开",me->get_name()));
        		return ;	
        	}
		mixTime = localtime(time());

		if ( who->get_save("changer930") == mixTime[TIME_YDAY])
        	{
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    您今天不是已经领过一次了吗？明天再来吧。\n"ESC"离开",me->get_name()));
        		return ;	
        	}
        	i = gone_time( who->get_login_time() );
		if ( i+ who->get_game_time()<who->get_double_time())
		{
		        send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		        	sprintf("%s：\n     您的双倍经验时间还剩 %d 秒，不能领取\n"
		                ESC "关闭\nCLOSE\n", me->get_name(), who->get_double_time() - i - who->get_game_time() ) );			
			return;		               
		}
        	who->set_save("changer930",mixTime[TIME_YDAY]);
		who->set_double_time(i+ who->get_game_time()+3600);        	
		send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    您成功领取了一小时双倍经验，可要好好利用哦！\n"ESC"离开",me->get_name()));
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,0001,"游戏辅助" ); 
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "双倍时间" ); 

        	break;	 
        case 8:
        	return ;
        	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    您确定要领取双倍经验时间吗？\n"ESC"确定\ntalk %x# welcome.7\n"ESC"离开",me->get_name(),getoid(me)));
		break;
        }

        
}


int exchange( object who,object me,object yuebing) 
{
	int rate,p,cash,exp,pot;
	object item;
	string name;
	
	rate = random(10000);
	if ( rate < 3000 )
	{
		exp = 400;
	}
	else if ( rate < 6000 )
	{
		pot = 30;
	}
	else if ( rate < 6010 )		//战国令
	{
		item = new("item/08/0001");
		name = "战国令";
	}
	else if ( rate < 6035 )	//战国号角
	{
		item = new("item/08/0002");
		name = "战国号角";
	}
	else if ( rate < 6055 )	//血石
	{
		item = new("item/08/0003");
	}
	else if ( rate < 6080 )	//法力石
	{
		item = new("item/08/0004");
	}
	else if ( rate < 6105 )	//技能进阶书
	{
		item = new(BOOK_FILE->get_book_file());
		name = item->get_name();
	}
	else if ( rate < 9180 )
	{
		cash = 1000;
	}
	else if ( rate < 9185 )	//百宝囊
	{
		item = new("item/std/6001");
		name = "百宝囊";
	}
	else if ( rate < 9200 )	//复生丹
	{
		item = new("item/91/9178");
		name = "复生丹";
	}
	else if ( rate < 9500 )	//炼丹成品
	{
		p = random(6);
		switch(p)
		{
		default:	
			item = new("item/final/91/1808");
			break;
		case 1:	
			item = new("item/final/91/1809");
			break;
		case 2:	
			item = new("item/final/91/1810");
			break;
		case 3:	
			item = new("item/final/91/1811");
			break;
		case 4:	
			item = new("item/std/5211");
			item->set_amount(3);
			break;
		case 5:	
			item = new("item/91/9145");
			item->set_amount(2);
			break;										
		}
	}
	else if ( rate < 9800 )	//酒食成品
	{
		p = random(5);
		switch(p)
		{
		default:	
			item = new("item/final/33/1706");
			break;
		case 1:	
			item = new("item/final/33/1707");
			break;
		case 2:	
			item = new("item/final/33/1708");
			break;
		case 3:	
			item = new("item/final/33/1753");
			break;
		case 4:	
			item = new("item/final/33/1755");
			break;
		}
		item->set_amount(2);
	}
	else			//机关中成品
	{
		p = random(4);
		switch(p)
		{
		default:	
			item = new("item/final/16/1607");
			break;
		case 1:	
			item = new("item/final/16/1612");
			break;
		case 2:	
			item = new("item/final/16/1609");
			break;
		case 3:	
			item = new("item/final/16/1610");
			break;
		}
	}
	yuebing->add_amount(-1);
	if ( item )
	{
		p = item->move(who,-1);
		if ( !p ) 
		{
			destruct(item);
			if ( objectp(yuebing) )
				yuebing->add_amount(1);
			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    你身上的东西好像太多了，清理一下再来兑换礼物吧～\n"ESC"离开",me->get_name()));
			return 0;	
		}
		send_user(who,"%c%s",'!',"恭喜您！您得到了"+item->get_name());
		item->add_to_user(p);	
		if ( name )
        		CHAT_D->sys_channel(0,sprintf("恭喜%s用中秋月饼换得了"HIR "%s",who->get_name(),name));
	}
	else if (  cash )
	{
		who->add_cash(cash);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您得到了%d金",cash));
	}
	else if (  pot )
	{
		who->add_potential(pot);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您得到了%d点潜能",pot));
	}
	else if (  exp )
	{
		who->add_exp(exp);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您得到了%d点经验",exp));
	}
	return 1;
}

int check_yuebing(object who, int count)
{
	int i,size,amount;
	object *inv,item;	
	string name="月饼";
	inv = all_inventory(who, 1, MAX_CARRY);
	
	if( !objectp( item = present(name, who, 1, MAX_CARRY) ) || item->is_zhongqiu() != 1 )
	{
		return 0;	
	}			
	for(i=0,size=sizeof(inv);i<size;i++)
	{
		if ( !objectp(inv[i]) )
			continue;
		if ( inv[i]->get_name() != name || inv[i]->is_zhongqiu() != 1 )
			continue;
		if ( inv[i]->is_combined() )
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

int give_yuebing(object who, int count)
{
	int i,size,amount;
	object *inv,item;	
	string name="月饼";
	if ( check_yuebing(who,count) != 1 )
		return 0;
	inv = all_inventory(who, 1, MAX_CARRY);
	for(i=0,size=sizeof(inv);i<size;i++)
	{
		if ( !objectp(inv[i]) )
			continue;
		if ( inv[i]->get_name() != name || inv[i]->is_zhongqiu() != 1 )
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
	return 1;		
	
}

void yutu_message()
{
	log_file("zhongqiu.txt",short_time() + " 预告放玉兔\n" );
	CHAT_D->sys_channel(0,HIR "嫦娥的玉兔因为贪吃凡间的月饼，已经从月宫中逃跑，估计不久后便会到达凡间，请各路英雄在各国城外帮忙寻找玉兔。");
}

void yuebing_message()
{
	log_file("zhongqiu.txt",short_time() + " 预告放月饼\n" );
	CHAT_D->sys_channel(0,HIR "嫦娥姐姐5分钟后即将在战国大地撒下了又大又圆的月饼，大家快快准备寻找吧～嫦娥祝大家节日快乐。");
}
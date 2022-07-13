#include <ansi.h>
#include <task.h>
#include <time.h>
#include <equip.h>

mapping nChainNpc = ([
	"Tân Thủ Thôn" : ({"李老汉", "陈老头", "刘大叔", "黄大叔", "李大伯", "孟氏", "孟大伯", "马老汉", "孔老头", "丁大叔", }),
	"Tề Quốc" : ({"齐总管", "齐管家", "齐国百姓", "李屠", "李浪", "孙老头", "王凯", "孔小飞", "崔玉", "齐小贩", "雷霸天", "棋童小红", "棋童小黑", "罗天", "玉器商", }),
	"Hàn Quốc" : ({"韩总管", "韩管家", "马大汉", "赵木", "林为", "游子", "钱老八", "李方士", "刘方士", "韩平", "乐师", "向棋师", "沈文",}),
	"Triệu Quốc" : ({"赵总管", "赵管家", "王铁匠", "脚夫 ", "李防", "白易", "吕不韦", "赵姬", }),
	"Ngụy Quốc" : ({"魏总管", "魏管家", "程林开", "周童", "李三婶", "李大毛 ", "许氏", " 纱纤小姐", "刘德", "孟求", "孙少爷", "朱狂", "花匠", "李德", "魏老汉", "秀丽小姐", "崔大官人", "寻儿",}),
	"Tần Quốc" : ({"秦总管", "秦管家", "彭尖豪", "马显", "夏侯党", "瘾君子", "贝贝", "秦老汉", "程强", "秦药师",}),
	"Sở Quốc" : ({"楚总管", "楚管家", "刘头", "钱老九", "孙陆", "王满", "丁小丫", "茶叶商", "黎老汉", "赌徒甲", "赌徒乙", "赌徒丙", "赌徒丁", }),
	"Yên Quốc" : ({"燕总管", "燕管家", "曹清", "丁鹤年", "程风", "刘老板", "燕老汉", "燕苍天 ", "药材商", "古董商", }),
]);
string *nFamily = ({"Đào Hoa Nguyên","Thục Sơn","Cấm Vệ Quân","Đường Môn","Mao Sơn","Côn Luân","Vân Mộng Cốc"});

int get_chain_type(object who);
void give_chain_task(object who, object me, int type);
void clear_chain(object who);
void next_chain(object who, object me);
void send_task_list(object who, int type);
void send_task_intro(object who);
int last_bonus(object who);
void kill_boss(object who ,object me);
void init_boss(object npc);
int catch_animal(object who ,object me);
int give_pet(object who);
int accept_object(object me,object who,object item);
int accept_item(object who);

// 函数:生成二进制码
void SAVE_BINARY() { }
//开始新任务链
void new_chain(object who, object me)
{
	int type,iCash,level;
	mixed mixTime;
	
	if ( who->get_save_2("chain.type") )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    你还有任务链，不能重复领取!\n"ESC"离开");
		return ;
	}	
	if ( (level=who->get_level()) < 50 )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    以你目前的实力难以完成如此艰巨的任务，等你到了50级再来找我吧～!\n"ESC"离开");
		return ;
	}
	iCash = 50000 + level * level * 4;
	if ( who->get_cash() < iCash )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+sprintf(":\n    你身上的金钱不够%d，不能领取新的任务!\n"ESC"离开",iCash));
		return ;
	}
	who->add_cash(-iCash);	
	//一天只能做一次任务链
	mixTime = localtime(time());
	if ( who->get_save_2("chain.date") == mixTime[TIME_YDAY] )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    你今天已经领取过一次任务链了，明天再来找我吧～!\n"ESC"离开");
		return ;
	}
	who->delete_save_2("chain.ring");
	next_chain(who,me);
}
//给予下一个任务
void next_chain(object who, object me)
{
	int type,ring;
	
	clear_chain(who);
	type = get_chain_type(who);	
	if ( !type )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    今天的天气好像不太好，不适合领取任务链!\n"ESC"离开");
		return ;
	}
	if ( is_god(who) && who->get("chain") )
		type = who->get("chain");
	give_chain_task(who,me,type);	
	
}
//保存任务链
void save_chain(object who, object me)
{
	int i;
	if ( !who->get_save_2("chain.type") || who->get_save_2("chain.save") )
		return ;
	i = gone_time(who->get_save_2("chain.start"));
	if ( i >= 2400 )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    你的任务时间已过,不能保存!\n"ESC"离开");
		return ;
	}
	if ( who->get_bonus() < 200 )
		return ;
	who->add_bonus( -200 );
	who->set_save_2("chain.past_time",i);
	who->delete_save_2("chain.start");
	who->set_save_2("chain.save",1);
	send_task_intro(who);
	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    你已经保存了你的任务链!\n"ESC"离开");
}
//询问保存
void query_save_chain(object who, object me)
{
	int id;
	if ( gone_time(who->get_save_2("chain.start")) >= 2400 )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    你的任务时间已过,不能保存!\n"ESC"离开");
		return ;
	}
	if ( who->get_bonus() < 200 )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    你的功德点不足20点，不能保存任务链!\n"ESC"离开");
		return ;
	}
	id = getoid(me);
	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+sprintf(":\n    你想保存你的任务链吗？为此必须扣除你20点功德.\n"ESC"确定\ntalk %x# buy.84\n"ESC"离开",id));
	
}
//继续任务链
void resume_chain(object who, object me)
{
	int level,iCash,i;
	if ( !who->get_save_2("chain.type") || !who->get_save_2("chain.save") )
		return ;
	level = who->get_level();
	iCash = 50000 + level * level * 4;
	if ( who->get_cash() < iCash )
		return ;
	who->add_cash(-iCash);	
	i = who->get_save_2("chain.past_time");
	who->set_save_2("chain.start",time()-i);
	who->delete_save_2("chain.past_time");
	who->delete_save_2("chain.save");
	send_task_intro(who);
	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    你已接取了任务，你可以继续完成你的任务链了!\n"ESC"离开");
}
//询问继续任务链
void query_resume_chain(object who, object me)
{
	int level,iCash,id;
	if ( !who->get_save_2("chain.type") || !who->get_save_2("chain.save") )
		return ;
	level = who->get_level();
	iCash = 50000 + level * level * 4;
	if ( who->get_cash() < iCash )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+sprintf(":\n    你身上的金钱不够%d，不能继续上次的任务链!\n"ESC"离开",iCash));
		return ;
	}
	id = getoid(me);
	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+sprintf(":\n    你想继续上次的任务链吗？为此你必须交纳%d金的费用.\n"ESC"确定\ntalk %x# buy.85\n"ESC"离开",iCash,id));
	
}
//获取任务类型
int get_chain_type(object who)
{
	int level,ring,type,rate;
	
	level = who->get_level();
	ring = who->get_save_2("chain.ring")+1;
	
	rate = random100();
	if ( ring < 10 )
	{
		if ( rate < 20 )
			type = 1;
		else if ( rate < 50 )
			type = 2;
		else if ( rate < 70 )
			type = 3;	
		else 
			type = 4;		
	}	
	else if ( ring == 10 )
	{
		if ( rate < 40 )
			type = 3;
		else if ( rate < 80 )
			type = 4;
		else 
			type = 5;		
	}
	else if ( ring < 20 )
	{
		if ( rate < 25 )
			type = 1;
		else if ( rate < 55 )
			type = 2;
		else if ( rate < 75 )
			type = 3;	
		else 
			type = 4;		
	}			
	else if ( ring == 20 )
	{
		if ( rate < 25 )
			type = 1;
		else if ( rate < 50 )
			type = 3;
		else if ( rate < 75 )
			type = 4;	
		else 
			type = 5;		
	}
	else if ( ring < 30 )
	{
		if ( rate < 30 )
			type = 1;
		else if ( rate < 50 )
			type = 2;
		else if ( rate < 70 )
			type = 3;	
		else if ( rate < 90 )
			type = 4;	
		else 
			type = 5;		
	}
	else if ( ring == 30 )
	{
		if ( rate < 25 )
			type = 1;
		else if ( rate < 50 )
			type = 3;
		else if ( rate < 75 )
			type = 4;	
		else 
			type = 5;		
	}
	else if ( ring < 40 )
	{
		if ( rate < 30 )
			type = 1;
		else if ( rate < 40 )
			type = 2;
		else if ( rate < 65 )
			type = 3;	
		else if ( rate < 80 )
			type = 4;	
		else 
			type = 5;		
	}
	else if ( ring == 40 )
	{
		if ( rate < 35 )
			type = 1;
		else if ( rate < 55 )
			type = 3;
		else if ( rate < 80 )
			type = 4;	
		else 
			type = 5;		
	}
	else if ( ring < 50 )
	{
		if ( rate < 35 )
			type = 1;
		else if ( rate < 55 )
			type = 3;
		else if ( rate < 80 )
			type = 4;	
		else 
			type = 5;		
	}
	else if ( ring == 50 )
	{
		if ( rate < 30 )
			type = 1;
		else if ( rate < 60 )
			type = 3;
		else 
			type = 5;		
	}
	return type;
}
//分配任务链任务
void give_chain_task(object who, object me, int type)
{
	int level;
	string npcname,cTmp,*nTmp,*nTmp1,cPos;
	
	if ( who->get_save_2("chain.type") || !type )
		return ;
	nTmp1 = keys(nChainNpc);
	cPos = nTmp1[random(sizeof(nTmp1))];
	nTmp = nChainNpc[cPos];
	if ( stringp(cTmp=who->get_save_2("chain.npcname")) )
		nTmp -= ({ cTmp });
	npcname = nTmp[random(sizeof(nTmp))];
	who->set_save_2("chain.type",type);
	who->set_save_2("chain.start",time());
	who->add_save_2("chain.ring",1);
	who->set_save_2("chain.from_npc",me->get_name());
	who->set_save_2("chain.npcname",npcname);
	who->set_save_2("chain.country",cPos);
	if ( type == 1 )	//索要装备
	{
		level = who->get_level()/10*10-10;
		if ( level > 80 )
			level = 80;
		cTmp = nFamily[random(sizeof(nFamily))];
		who->set_save_2("chain.level",level);
		who->set_save_2("chain.family",cTmp);

		cTmp = sprintf("%s:\n    听说%s急需一件%d级%s门派装备，麻烦你去找一件给他.这件物品对于他来说非常重要，因为他最近他想送礼买通本国内政官帮其办一件事，而内政官就对%d级%s门派装备感兴趣，你快去寻一件给%s吧～!\n"ESC"确定",me->get_name(),npcname,level,cTmp,level,cTmp,npcname);
				
	}
	else if ( type == 2 )	//传话
	{
		cTmp = sprintf("%s:\n    我的一个朋友在他家玩了很多天，竟然到现在还不给我回个消息，如今兵荒马乱，让我很是担心.麻烦你带我传一下话给"HIR"%s"NOR"，让我那个朋友给我回个信.\n"ESC"确定",me->get_name(),npcname);
	}
	else if ( type == 3 )	//杀恶霸
	{
		who->set_save_2("chain.bossname",NPC_NAME_D->get_robber_name());
		cTmp = sprintf("%s:\n    有一个恶霸欺压良民、作恶无数，最近他又想抢取"HIR"%s"NOR"的田地，那田地乃是其生存之本.为了阻止此事发生，你前去将他除掉，除掉之后告之"HIR"%s"NOR"一声\n"ESC"确定",me->get_name(),npcname,npcname);
	}
	else if ( type == 4 )	//索要师门物品
	{
		level = who->get_level();		
		nTmp = "sys/task/quest1"->get_random_quest6(level);
		who->set_save_2("chain.itemname",nTmp[0]);
		who->set_save_2("chain.itemwhere",nTmp[1]);		
		cTmp = sprintf("%s:\n    当今天下，诸侯割据，为了避开这混乱之世，%s决定举家迁徙，动身之前，须储备好物品，以防不时之需.现正缺%s，还望尔能"HIR"找齐二十件%s交于%s"NOR"，其将不甚感激.\n"ESC"确定",me->get_name(),npcname,nTmp[0],nTmp[0],npcname);
	}
	else if ( type == 5 )	//索要宝宝
	{
		if ( catch_animal(who,me) == 1 )
			cTmp = sprintf("%s:\n    不久前，"HIR"%s"NOR"丢失了一只"HIR"%s（宝宝）"NOR"，现在妖魔横行，我担心它被捉去被训练成妖怪出来害人，为了阻止此事的发生，你快去将它寻回来交给"HIR"%s"NOR"，如果你能完成此事，定是苍生之福.\n"ESC"确定",me->get_name(),npcname,who->get_save_2("chain.pet"),npcname);
		else
		{
			clear_chain(who);	
			return ;
		}
	}
	else			
	{
		clear_chain(who);
		send_user(who,"%c%s",'!',"错误的任务类型");
		return;	
	}
	
	send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),cTmp);
	send_task_list(who,type);
}

void send_task_list(object who, int type)
{
	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,TID_CHAIN,"任务链" );
	switch(type)
	{
		case 1:
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_CHAIN,type,"寻找装备" );
			break;
		case 2:
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_CHAIN,type,"传话给"+who->get_save_2("chain.npcname") );
			break;	
		case 3:
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_CHAIN,type,"帮助"+who->get_save_2("chain.npcname")+"除掉恶霸" );
			break;
		case 4:
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_CHAIN,type,"收集"+who->get_save_2("chain.itemname"));
			break;	
		case 5:
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_CHAIN,type,sprintf("寻一只%s（宝宝）",who->get_save_2("chain.pet")) );
			break;	
	}
}

//发送任务详细描述
void send_task_intro(object who)
{
	int type,lefttime,level;
	string result,cName,cPet,cFamily;
	type = who->get_save_2("chain.type");
	switch(type)
	{
	case 1:
		level = who->get_save_2("chain.level");
		cFamily = who->get_save_2("chain.family");
		result = sprintf(BLK"任务目的:\n"BLK"    寻找一件%d级%s门派装备给%s(第%d环，"HIR"%s)\n"BLK"任务描述:\n"BLK"    听说%s%s急需一件一件%d级%s门派装备，麻烦你去找一件给他.这件物品对于他来说非常重要，因为他最近他想送礼买通本国内政官帮其办一件事，而内政官就对一件%d级%s门派装备感兴趣，你快去寻一件给%s吧～!",level,cFamily,cName=who->get_save_2("chain.npcname"),who->get_save_2("chain.ring"),who->get_save_2("chain.save")?"已保存":"还有%d分钟",who->get_save_2("chain.country"),cName,level,cFamily,level,cFamily,cName);
		break;	
	case 2:
		result = sprintf(BLK"任务目的:\n"BLK"    传话给%s(第%d环，"HIR"%s)\n"BLK"任务描述:\n"BLK"    %s的一个朋友在%s的%s家玩了很多天，竟然到现在还不给%s回个消息，如今兵荒马乱，让他很是担心.麻烦你传一下话给%s的%s，让他那个朋友回个信给%s.",who->get_save_2("chain.npcname"),who->get_save_2("chain.ring"),who->get_save_2("chain.save")?"已保存":"还有%d分钟",who->get_save_2("chain.from_npc"),who->get_save_2("chain.country"),who->get_save_2("chain.npcname"),who->get_save_2("chain.from_npc"),who->get_save_2("chain.country"),who->get_save_2("chain.npcname"),who->get_save_2("chain.from_npc"));
		break;	
	case 3:
		result = sprintf(BLK"任务目的:\n"BLK"    前去找到%s，并帮助其除掉恶霸(第%d环，"HIR"%s)\n"BLK"任务描述:\n"BLK"    恶霸%s欺压良民、作恶无数，最近他又想抢取%s的田地，那田地乃是其生存之本.为了阻止此事发生，你前去将恶霸除掉，除掉之后告之%s一声.",who->get_save_2("chain.npcname"),who->get_save_2("chain.ring"),who->get_save_2("chain.save")?"已保存":"还有%d分钟",who->get_save_2("chain.bossname"),who->get_save_2("chain.npcname"),who->get_save_2("chain.npcname"),);
		break;
	case 4:
		result = sprintf(BLK"任务目的:\n"BLK"    收集二十个%s交于%s(第%d环，"HIR"%s)\n"BLK"任务描述:\n"BLK"    当今天下，诸侯割据，为了避开这混乱之世，%s决定举家迁徙，动身之前，须储备好物品，以防不时之需.现正缺%s，还望尔能找齐二十件%s交于%s，其将不甚感激.据说在"HIR"%s"NOR,who->get_save_2("chain.itemname"),cName=who->get_save_2("chain.npcname"),who->get_save_2("chain.ring"),who->get_save_2("chain.save")?"已保存":"还有%d分钟",cName,who->get_save_2("chain.itemname"),who->get_save_2("chain.itemname"),cName,who->get_save_2("chain.itemwhere"));
		break;	
	case 5:
		result = sprintf(BLK"任务目的:\n"BLK"    寻一只%s（宝宝）给%s(第%d环，"HIR"%s)\n"BLK"任务描述:\n"BLK"    %s丢失了一只%s（宝宝），现在妖魔横行，%s担心它被捉去被训练成妖怪出来害人，为了阻止此事的发生，你快去将它寻回来交给%s，如果你能完成此事，定是苍生之福.据说"HIR"%s"NOR".",cPet=who->get_save_2("chain.pet"),cName=who->get_save_2("chain.npcname"),who->get_save_2("chain.ring"),who->get_save_2("chain.save")?"已保存":"还有%d分钟",cName,cPet,cName,cName,who->get_save_2("chain.petinfo"));
		break;
	}
	if ( stringp(result) )
	{
		if ( who->get_save_2("chain.save") )
			send_user( who, "%c%c%c%w%w%s", 0x51, 1, 3,TID_CHAIN,type,result );
		else
		{
			lefttime = 2400-gone_time(who->get_save_2("chain.start"));
			if ( lefttime>0)
				send_user( who, "%c%c%c%w%w%d%s", 0x51, 1, 4,TID_CHAIN,type,lefttime,result );
			else
				send_user( who, "%c%c%c%w%w%s", 0x51, 1, 3,TID_CHAIN,type,BLK"已无剩余时间" );
		}
	}
}

//取消任务
void task_giveup(object who)
{
	int type;
	mixed mixTime;
	
	type = who->get_save_2("chain.type");
	if ( !type )
		return ;
	clear_chain(who);
	who->delete_save_2("chain.ring");
	mixTime = localtime(time());
	who->set_save_2("chain.date",mixTime[TIME_YDAY]);
	switch(type)
	{
	case 1:
		break;
	}
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_CHAIN,type,"" );
}
//清除任务链变量
void clear_chain(object who)
{
	who->delete_save_2("chain.type");
//	who->delete_save_2("chain.npcname");
	who->delete_save_2("chain.country");
	who->delete_save_2("chain.from_npc");
	who->delete_save_2("chain.start");
	who->delete_save_2("chain.save");
	who->delete_save_2("chain.past_time");
	who->delete_save_2("chain.killnpc");
	who->delete_save_2("chain.amount");
	who->delete_save_2("chain.status");
	who->delete_save_2("chain.pet");
	who->delete_save_2("chain.petinfo");
	who->delete_save_2("chain.level");
	who->delete_save_2("chain.family");
	who->delete_save_2("chain.bossname");
	who->delete_save_2("chain.legend");
	who->delete_save_2("chain.itemname");
	who->delete_save_2("chain.itemwhere");
}

string get_chain_menu(object who,object me)
{
	int id,type;
	string cTmp;

	type = who->get_save_2("chain.type");
	if ( !type || who->get_save_2("chain.npcname")!=me->get_name() || 
		who->get_save_2("chain.save") ||
		gone_time(who->get_save_2("chain.start")) > 2400 )
		return "";
	id = getoid(me);
	switch(type)
	{
	default:
	case 1:
		cTmp = sprintf(ESC HIG"寻找一件装备\nchain %x# 11\n",id);
		break;
	case 2:
		cTmp = sprintf(ESC HIG"传话给%s\nchain %x# %d\n",me->get_name(),id,type);
		break;
	case 3:
		if ( who->get_save_2("chain.status") != 99 )
			cTmp = sprintf(ESC HIG"除掉恶霸%s\nchain %x# 31\n",who->get_save_2("chain.bossname"),id);
		else
			cTmp = sprintf(ESC HIG"除掉恶霸%s(完成任务)\nchain %x# %d\n",who->get_save_2("chain.bossname"),id,type);
		break;
	case 4:
		cTmp = sprintf(ESC HIG"找齐二十件%s\nchain %x# 4\n",who->get_save_2("chain.itemname"),id);
		break;
	case 5:
		cTmp = sprintf(ESC HIG"寻一只%s（宝宝）\nchain %x# %d\n",who->get_save_2("chain.pet"),id,type);
		break;	
	}
	return cTmp;
}

void finish_task(object who,object me,string arg)
{
	int type,ring,exp,pot,level;
	type = who->get_save_2("chain.type");
	if ( !type || who->get_save_2("chain.npcname")!=me->get_name() || gone_time(who->get_save_2("chain.start")) > 2400 )
		return ;
	if ( type == 5 && !give_pet(who) )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    我托付于你的事，你办好了没有？\n"ESC"离开");
		return ;	
	}
	else if ( type == 4 && !accept_item(who) )
	{
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(),me->get_name()+":\n    我托付于你的事，你办好了没有？\n"ESC"离开");
		return ;	
	}
	//任务链完成奖励
	ring = who->get_save_2("chain.ring");
	if ( ring == 50 && last_bonus(who)!=1 )
		return ;
	level = who->get_level();
	exp = 1000+level*ring*ring*3/10;
	pot = level-40+ring*2;
	who->add_exp(exp);
	who->add_potential(pot);
        who->add_log("&chain", exp);
        who->add_log("*chain", pot);
        "/sys/sys/count"->add_task("任务链", 1);
	send_user(who,"%c%s",';',sprintf("任务链第%d环 经验 %d 潜能 %d",ring,exp,pot));
	//任务链的相关处理
	clear_chain(who);
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2,TID_CHAIN,type,"" );
	
	//下一环
	if ( ring < 50 )
		next_chain(who,me);
}
object give_item(object who, string cName,int level)
{
	int p;
	object item;
	
	item = new(cName);
	if ( !item )
		return 0;
	p = item->move(who,-1);
	if ( !p )
		return 0;
	if ( level )
		item->set_level(level);
	item->add_to_user(p);
	return item;	
}

int last_bonus(object who)
{
	int level;
	string file,cTmp;;
	
	level = who->get_level();

	if ( USER_INVENTORY_D->count_empty_carry(who) < 4 )
	{
		send_user(who,"%c%s",'!',"把你的包包清理一下再来交任务吧!");
		return 0;	
	}
	cTmp = "你获得了";
	file = 	BOOK_FILE->get_book_file();
	give_item(who,file,0);
	cTmp += file->get_name();
	give_item(who,"item/91/9167.c",0);
	cTmp += "、紫参丹";
	if ( (level >= 70 && level < 90 && random100() < 50 ) || level >= 90 )
	{
		give_item(who,"item/44/4488.c",0);
		cTmp += "、精元丹";
	}
	if ( level >= 90 && random100() < 30 )
	{
		file = STONE_FILE->get_diamond_file();
		give_item(who,file,3);
		cTmp += "、"+file->get_name();
	}
	send_user(who,"%c%s",'!',cTmp);
	return 1;
}
//队伍进入杀BOSS的场景
void team_enter_boss_scene(object who,int z,int x,int y)
{
	int i,size;
	object *nTeam;
	
	if ( !who->is_leader() )
		return ;
	nTeam = who->get_team();
	for(i=0,size=sizeof(nTeam);i<size;i++)
	{
		if ( !nTeam[i] )
			continue;
		if ( nTeam[i] == who )
			continue;
		if ( !inside_screen_2(who,nTeam[i]) )
			continue;
		nTeam[i]->add_to_scene(z,x,y);
	}
	who->add_to_scene(z,x,y);
}
//杀boss
void kill_boss(object who ,object me)
{
	int level,ring,x,y,z,p,d;
	object npc,map;
	string cName;

	if ( who->get_save_2("chain.type") != 3 || who->get_save_2("chain.status") == 99 )
		return ;
	npc = who->get("chainnpc");
	if ( npc && (npc->get("chain") == who->get_number()) )	//进入旧的场景
	{
		z = get_z(npc);
		x = get_x(npc);
		y = get_y(npc);
		npc->set_hp(npc->get_max_hp());
		npc->set_mp(npc->get_max_mp());
		if ( who->is_leader() )
			team_enter_boss_scene(who,z,x,y);
		else
			who->add_to_scene(z,x,y);
		return ;	
	}
	if( ( z = find_map_flag(1000, 2999, 0) ) <= 0 ) return ;
	npc = new( "npc/task/8220" );
        if ( !npc ) return;
        d = 891 + random(7);
	init_virtual_map(z, d);		
        map = new( NEWBIE );
        map->set_client_id(d);
        map->set_owner(who);
        set_map_object( map, map->set_id(z) );       
        map->set_name("Luyện Võ Trường");    
        p = get_jumpin(z, 1);
	x = p/1000, y = p % 1000;
	cName = who->get_save_2("chain.bossname");
	level = who->get_level();
	ring = who->get_save_2("chain.ring");
	level = level + 5 + ring/10*5;
	NPC_ENERGY_D->init_level(npc, level);
	npc->set_max_seek(8);
	npc->set_name("Ác Bá"+cName);
	npc->set("chain",who->get_number());
	init_boss(npc);
	npc->add_to_scene(z,x,y);
	npc->set("chain_x",get_x(who));
	npc->set("chain_y",get_y(who));
	npc->set("chain_z",get_z(who));
	who->set_save_2("chain.killnpc",cName);
	who->set("chainnpc",npc);
	if( p = get_valid_xy(z, x, y, IS_CHAR_BLOCK) )
        {
                x = p/1000, y = p % 1000;
		if ( who->is_leader() )
			team_enter_boss_scene(who,z,x,y);
		else
			who->add_to_scene(z,x,y);
        }
}

void init_boss(object npc)
{
	int p,level;
	
	level = npc->get_level();
	p = random(100);
	if ( p < 20)	//低物防高敏型
	{
		npc->set_skill(348,level);
		npc->set_skill(251,level);
		npc->set_skill(241,level);
		npc->set_char_picid(8011);
                npc->set_walk_speed(4);
                npc->set_attack_speed(10);	
                npc->add_dp(-1*npc->get_dp()/4);
                npc->add_max_hp(npc->get_max_hp()*8);	
                npc->add_sp(npc->get_sp()*2);
                npc->add_ap(npc->get_ap()*4/5);
                npc->add_mp(npc->get_mp()/2);  
                npc->set("chain.type",1);              		
	}
	else if ( p < 40 )	//高物防低法防型
	{
		npc->set_skill(221,level);
		npc->set_skill(231,level);
		npc->set_char_picid(0252);
                npc->set_walk_speed(4);
                npc->set_attack_speed(10);	
                npc->add_dp(npc->get_dp()*3);
                npc->add_max_hp(npc->get_max_hp()*4); 	
                npc->add_pp(-1*npc->get_pp()*3/10);                
                npc->add_ap(npc->get_ap()*4/5);                
                npc->add_mp(npc->get_mp()/2);  
                npc->set("chain.type",2);              		
	}
	else if ( p < 60 )	//高法防低物防型
	{
		npc->set_skill(423,level);
		npc->set_skill(424,level);
		npc->set_skill(425,level);
		npc->set_char_picid(8010);
                npc->set_walk_speed(4);
                npc->set_attack_speed(10);	
                npc->add_dp(-1*npc->get_dp()/4);
                npc->add_max_hp(npc->get_max_hp()*4); 	
                npc->add_sp(npc->get_sp());  
                npc->add_pp(npc->get_pp()*3/2);                
                npc->add_cp(npc->get_cp());
		npc->add_mp(npc->get_mp()*6);
                npc->set("chain.type",3);              		
	}	
	else if ( p < 70 )	//长血型:拳脚类
	{
		npc->set_skill(211,level);
		npc->set_skill(317,level);
		npc->set_char_picid(8000);
                npc->set_walk_speed(4);
                npc->set_attack_speed(10);	
                npc->add_dp(-1*npc->get_dp()/5);        
                npc->add_max_hp(npc->get_max_hp()*20); 
                npc->add_pp(-1*npc->get_pp()/5);                
                npc->add_mp(npc->get_mp()/2);                 
                npc->add_ap(npc->get_ap()*9/10);  
                npc->set("chain.type",4);              		
	}
	else if ( p < 90 )	//长血高物防高法防型:远程暗器类
	{
		npc->set_skill(261,level);
		npc->set_char_picid(8012);
                npc->set_walk_speed(4);
                npc->set_attack_speed(10);	
		npc->add_dp(npc->get_dp()*9/20);
		npc->add_max_hp(npc->get_max_hp()*5); 
 		npc->add_sp(npc->get_sp()*3);
 		npc->add_pp(npc->get_pp()*9/5);
 		npc->add_mp(npc->get_mp());
 		npc->add_ap(npc->get_ap()/2);
                npc->set("chain.type",5);              		
	}
	else 	//强攻型加召唤
	{
		npc->set_skill(414,level);
		npc->set_char_picid(8013);
                npc->set_walk_speed(4);
                npc->set_attack_speed(8);	
                npc->add_dp(npc->get_dp()*9/20);
                npc->add_ap(npc->get_ap()); 
                npc->add_max_hp(npc->get_max_hp()*5);                 
                npc->add_sp(npc->get_sp()*3);  
                npc->add_pp(npc->get_pp()*9/20);      
                npc->add_mp(npc->get_mp()*3/2);  
                npc->set("chain.type",6);              		
	}	
}
//抓宠物宝宝
int catch_animal(object who ,object me)
{
	int level;
	string *nPet,cPet;
	
	level = who->get_level()/5*5;
	if ( level < 10 )
		level = 10;
	else if ( level > 110 )
		level = 110;
	nPet = "/sys/task/quest1"->get_random_quest5(level-5-5*random(2));
	who->set_save_2("chain.pet",nPet[0]);
	who->set_save_2("chain.petinfo",nPet[1]);
	return 1;
}
//给宠物宝宝
int give_pet(object who)
{
	int i,size;
	string cName;
	object pet,*AllBeast;
	
	if ( who->get_save_2("chain.type") != 5 )
		return 0;
	cName = who->get_save_2("chain.pet");
	if ( !stringp(cName) )
		return 0;
	AllBeast = who->get_all_beast();
	for(i=0,size=sizeof(AllBeast);i<size;i++)
	{
		if ( !objectp(pet=AllBeast[i]) )
			continue;
		if ( pet->get_name() == cName && pet->get_firstname()== cName && pet->get_blood() == 1 )
			break;
	}
	if ( i >= size )
		return 0;
	USER_BEAST_D->destruct_pet(who,pet);
	return 1;	
}
//寻找装备
int accept_object(object me,object who,object item)
{
	int level,flag,index;
	string cFam;
	
	if ( me->get_save_2("chain.type") != 1 || me->get_save_2("chain.npcname") != who->get_name() || !item->is_equip() )
		return 0;
	level = me->get_save_2("chain.level")/10;
	if ( (item->get_level() / 10) != level )
		return 0;
	cFam = me->get_save_2("chain.family");
	flag = item->get_family();
	index = item->get_equip_type();
	if (flag==8) flag = 0;
	if( flag )
	{
                switch( index )
                {
		default : switch( cFam )
                        {
                      default : if( flag != 8 ) flag = -1;  break;
			case "Đào Hoa Nguyên" : if( flag != 1 ) flag = -1;  break;
			case "Thục Sơn" : if( flag != 2 && flag!=9 ) flag = -1;  break;
	                case "Cấm Vệ Quân" : if( flag != 3 ) flag = -1;  break;
			case "Đường Môn" : if( flag != 4 ) flag = -1;  break;
			case "Mao Sơn" : if( flag != 5 && flag!=9 ) flag = -1;  break;
	                case "Côn Luân" : if( flag != 6 && flag!=9 ) flag = -1;  break;
	                case "Vân Mộng Cốc" : if( flag != 7 && flag!=9 ) flag = -1;  break;
                        }
                        break;

		case WEAPON_TYPE : switch( cFam )
                        {
			default : if( flag != 8 ) flag = -1;  break;
			case "Đào Hoa Nguyên" : if( flag != 1 ) flag = -1;  break;
			case "Thục Sơn" : if( flag != 2 && flag!=9 ) flag = -1;  break;
			case "Cấm Vệ Quân" : if( flag != 3 ) flag = -1;  break;
			case "Đường Môn" : if( flag != 4 ) flag = -1;  break;
			case "Mao Sơn" : if( flag != 5 && flag!=9 ) flag = -1;  break;
			case "Côn Luân" : if( flag != 6 && flag!=9 ) flag = -1;  break;
			case "Vân Mộng Cốc" : if( flag != 7 && flag!=9 ) flag = -1;  break;
                        }
                        break;

		case HAND_TYPE : switch( cFam )
                        {
			default : flag = -1;  break;
			case "Vân Mộng Cốc" : if( flag != 7 ) flag = -1;  break;
			case "Đường Môn" : if( flag != 4 ) flag = -1;  break;
                        }
                        break;
                }
        	if( flag < 0 )
			return 0;        
        }
        
	item->remove_from_user();
	destruct( item );
	me->set_save_2("chain.status",99);
	finish_task(me,who,"");	//完成任务
	return 1;	
}
//打传说，获得装备
void legend_item(object me, object who)
{
	int level1,level2,level,p;
	string *nTmp,cTmp;
	object item;
	
	if ( me->get_save_2("chain.type") != 1 || me->get_save_2("chain.legend") || gone_time(me->get_save_2("chain.start")) > 2400 )
		return ;
	if ( USER_INVENTORY_D->count_empty_carry(me) < 1 )
		return ;
	level1 = me->get_level();
	level2 = level1 + 5;
	level1 = level1 - 5;
	level = who->get_level();
	if ( level < level1 || level > level2 )
		return ;
	if ( random100() != 1 )
		return ;
	cTmp = me->get_save_2("chain.family");
	level = me->get_save_2("chain.level");
	nTmp = WEAPON_FILE->get_family_equip(cTmp,1+random(2),level,HEAD_TYPE+random(6));
	if ( !sizeof(nTmp) )
		return ;
	cTmp = nTmp[random(sizeof(nTmp))];
	item = new(cTmp);
	if ( !item )
		return ;
	p = item->move(me,-1);
	if ( !p )
	{
		destruct(item);
		return ;
	}
	send_user(me,"%c%s",'!',"你获得了传说中的"+HIR+item->get_name());
	item->set_bind(4);
	item->add_to_user(p); 
	me->set_save_2("chain.legend",1);	
}
//收集师门物品
int accept_item(object who)
{
	string name;
	int i,size,amount,count=20;
	object *inv,item;
	
	if ( who->get_save_2("chain.type") != 4 )
		return 0;
	name = who->get_save_2("chain.itemname");
	if ( !stringp(name) )
		return 0;

	inv = all_inventory(who, 1, MAX_CARRY);
	
	for(i=0,size=sizeof(inv);i<size;i++)
	{
		if ( !objectp(inv[i]) )
			continue;
		if ( inv[i]->get_name() != name  )
			continue;
		if ( inv[i]->is_combined() )
			amount += inv[i]->get_amount();		
		else
			amount ++;
	}
	if ( amount < count )
		return 0;	
	amount = count;
	for(i=0,size=sizeof(inv);i<size;i++)
	{
		if ( !objectp(inv[i]) )
			continue;
		if ( inv[i]->get_name() != name )
			continue;
		if ( !inv[i]->is_combined() )
		{
			inv[i]->remove_from_user();
			destruct(inv[i]);
			amount--;
			if ( amount <= 0 )
				break;
			continue;
		}
		if ( inv[i]->get_amount() <= amount )
		{
			amount -= inv[i]->get_amount();
			inv[i]->remove_from_user();
			destruct(inv[i]);
		}
		else
		{
			inv[i]->set_amount(inv[i]->get_amount()-amount);
			amount = 0 ;			
		}
		if ( amount <= 0 )
			break;
	}	
	return 1;
}
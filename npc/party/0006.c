#include <npc.h>
#include <city.h>
#include <ansi.h>
inherit SAVE_F;
inherit OFFICER;

void do_bonus();
void do_info();
void do_input();
void get_bonus(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5302; }
static int flag;
static mapping mpTab = 
([
	0 : "T", 1 : "F", 2 : "K", 3 : "E", 4 : "L", 
	5 : "X", 6 : "R", 7 : "J", 8 : "P", 9 : "C", 	
]);
static mapping mpTab1 = 
([
	
]);
static string *nXuliehao = ({});
mapping mpBonus = ([]);

void read_xuliehao();
string get_save_file()	{ return "data/xueliehao74"SAVE_EXTENSION;}
// 函数：构造处理
void create()
{
	int i,size,*nTmp;
        set_name("内测使者");

        set_2( "talk", ([
//                 "bonus"         : (: do_bonus :),
//                 "info"         : (: do_info :),
                 "inputx"         : (: do_input :),
                 "get_bonus"         : (: get_bonus :),
        ]) );

        setup();
        restore();
        if ( !mapp(mpBonus) )
        	mpBonus = ([]);
	flag = mktime(2006,9,1,0,0,0);
	nTmp = keys(mpTab);
	for(i=0,size=sizeof(nTmp);i<size;i++)
	{
		mpTab1[mpTab[nTmp[i]]] = nTmp[i];
	}
	read_xuliehao();
}

void do_look( object who )
{
	int id;
	id = getoid(this_object());
	send_user( who, "%c%c%w%s", ':', 3, get_char_picid(),
		get_name()+":\n    如果您是曾经参与过《大话战国》封闭测试的玩家，而且得到了领奖码，那么便可以在我这里通过领奖码得到丰富的奖励回报。\n    感谢您对我们游戏的支持，希望您游戏愉快。\n"
		+ sprintf(ESC"输入领奖码获取奖励\ntalk %x# inputx\n"ESC"离开",id,id) );
		
}

void do_bonus()
{
	__FILE__->do_bonus_2(this_player(),this_object());	
}

void do_bonus_2(object who , object me)
{
	int i,j,k,m,n,level,total,num1,num2,num3;
	string res1,res2,res3,res4,res,tmp;
	
	if ( stringp(who->get_save("xuliehao74")) )
	{
		send_user(who,"%c%s",'!',"你已经领取过领奖码了");
		return ;	
	}
	level = who->get_level();

	if ( level < 40  )
	{
		send_user(who,"%c%s",'!',"你的等级不够40级");
		return ;	
	}

	res1 = "";
	res2 = "";
	res3 = "";
	res4 = "";

	n = who->get_number();
	k = n;
	while(k)
	{
		m = k % 10;
		k = k / 10;
		tmp = mpTab[m];
		res1 = tmp + res1;
	}
	
	k = level*3;
	while(k)
	{
		m = k % 10;
		k = k / 10;
		tmp = mpTab[m];
		res2 = tmp + res2;
	}
	
	i = time()-flag;
	k = i;
	while(k)
	{
		m = k % 10;
		k = k / 10;
		tmp = mpTab[m];
		res3 = tmp + res3;
	}
	//2X+Y*Y+Z
	total = 2 * n + level*level + i ;
	k = total;
	while(k)
	{
		m = k % 10;
		k = k / 10;
		tmp = mpTab[m];
		res4 = tmp + res4;
	}
	res = sprintf("%d%s%d%s%d%s%d%s",random(100),res1,random(100),res2,random(1000),res3,random(100),res4);
	who->set_save("xuliehao74",res);
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		me->get_name()+":\n    你的领奖码是："+ res+"\n    凭此码可以在内测服务器中，达到20级以后，领取不同的大礼包。请牢记。");
	log_file("xuliehao.txt",sprintf("%s %d %s %d\n",short_time(),who->get_number(),res,who->get_level() ));
}

void do_info()
{
	__FILE__->do_info_2(this_player(),this_object());	
}
void do_info_2(object who , object me)
{
	string tmp;
	if ( !stringp(tmp=who->get_save("xuliehao74")) )
	{
		send_user(who,"%c%s",'!',"你还没有领取过序列号");
		return ;	
	}
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		me->get_name()+":\n    你的领奖序列号是："+ tmp+"\n    凭此码可以在内测服务器中，达到20级以后，领取不同的大礼包。请牢记。");
}

void do_input()
{
	__FILE__->do_input_2(this_player(),this_object());	
}
void do_input_2(object who , object me)
{
	send_user( who, "%c%c%d%s", '?', 16, 30, "请输入序列号：\n"+sprintf( ESC"talk %x# get_bonus",getoid(me))+".%s\n");		

}
//领取奖励 要取原先发出的号码对比才行。
void get_bonus(string arg)
{
	__FILE__->get_bonus_2(this_player(),this_object(),arg);
}

void get_bonus_2(object who,object me,string arg)
{
	int i,size,k,num1,num2,num3,num4,total;
	int num,level,times,sum;
	string tmp,res1,res2,res3,res4;

	if ( (i=me->get("times")) && gone_time(i) <= 3 )
	{
		send_user(who,"%c%s",'!',"请重新输入号码");
		return ;	
	}
	if ( stringp(who->get_save("xuliehao74")) )
	{
		send_user(who,"%c%s",'!',"你已经领取奖励了");
		return ;	
	}
	arg = strupr(arg);
	if ( sscanf(arg,"%d%s%d%s%d%s%d%s",num1,res1,num2,res2,num3,res3,num4,res4) != 8 )
		return ;
	if ( mpBonus[arg] )
	{
		send_user(who,"%c%s",'!',"这个号码已经领取过奖励了");
		return ;	
	}
	if ( member_array(arg,nXuliehao) == -1 )
	{
		send_user(who,"%c%s",'!',"做人要厚道");
		me->set("times",time());
		return ;	
	}
	if ( who->get_level() < 20 )
	{
		send_user(who,"%c%s",'!',"你的等级不够20级");
		return ;	
	}	
//	for(num=0,i=0,size=sizeof(res1);i<size;i++)
//	{
//		num = num*10;
//		num += to_int(mpTab1[res1[i..i]]);	
//	}
	for(level=0,i=0,size=sizeof(res2);i<size;i++)
	{
		level = level*10;
		level += to_int(mpTab1[res2[i..i]]);	
	}
	level /= 3;
//	for(times=0,i=0,size=sizeof(res3);i<size;i++)
//	{
//		times = times*10;
//		times += to_int(mpTab1[res3[i..i]]);	
//	}	
//	for(sum=0,i=0,size=sizeof(res4);i<size;i++)
//	{
//		sum = sum*10;
//		sum += to_int(mpTab1[res4[i..i]]);	
//	}
//	total = 2 * num + level * level + times;
//	if ( sum != total )	//这个校验不足够，要取原先的号码对比。
//	{
//		send_user(who,"%c%s",'!',"做人要厚道");
//		me->set("times",time());
//		return ;	
//	}	
	if ( level >= 40 && level < 50 )
	{
		if ( TASK_LEGEND_D->can_carry_amount(who,4) != 1 )
			return ;  		
		TASK_LEGEND_D->give_item(who,"item/std/6000",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0002",3); 
		TASK_LEGEND_D->give_item(who,"item/08/0003",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0004",1); 
		send_user(who,"%c%s",';',"得到奖励 包裹 1 战国号角 3 法力石 1 血力石 1");
	}
	else if ( level < 60 )
	{
		if ( TASK_LEGEND_D->can_carry_amount(who,4) != 1 )
			return ;  		
		TASK_LEGEND_D->give_item(who,"item/std/6000",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0001",3); 
		TASK_LEGEND_D->give_item(who,"item/08/0003",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0004",1); 
		send_user(who,"%c%s",';',"得到奖励 包裹 1 战国令牌 3 法力石 1 血力石 1");
	}
	else if ( level < 70 )
	{
		if ( TASK_LEGEND_D->can_carry_amount(who,4) != 1 )
			return ;  		
		TASK_LEGEND_D->give_item(who,"item/std/6001",1); 
		TASK_LEGEND_D->give_item(who,"item/std/6000",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0003",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0004",1); 
		send_user(who,"%c%s",';',"得到奖励 百宝囊 1 包裹 1 法力石 1 血力石 1");
	}
	else if ( level < 80 )
	{
		if ( TASK_LEGEND_D->can_carry_amount(who,4) != 1 )
			return ;  		
		TASK_LEGEND_D->give_item(who,"item/std/6001",1); 
		TASK_LEGEND_D->give_item(who,"item/std/6001",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0003",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0004",1); 
		send_user(who,"%c%s",';',"得到奖励 百宝囊 2 法力石 1 血力石 1");
	}
	else if ( level < 90 )
	{
		if ( TASK_LEGEND_D->can_carry_amount(who,4) != 1 )
			return ;  		
		TASK_LEGEND_D->give_item(who,"item/std/6001",1); 
		TASK_LEGEND_D->give_item(who,"item/std/6002",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0003",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0004",1); 
		send_user(who,"%c%s",';',"得到奖励 百宝囊 1 乾坤袋 1 法力石 1 血力石 1");
	}
	else if ( level >= 90 )
	{
		if ( TASK_LEGEND_D->can_carry_amount(who,4) != 1 )
			return ;  		
		TASK_LEGEND_D->give_item(who,"item/std/6002",1); 
		TASK_LEGEND_D->give_item(who,"item/std/6002",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0003",1); 
		TASK_LEGEND_D->give_item(who,"item/08/0004",1); 
		send_user(who,"%c%s",';',"得到奖励 乾坤袋 2 法力石 1 血力石 1");
	}
	who->set_save("xuliehao74",arg);	
	mpBonus[arg] = 1;
	save();
}

void read_xuliehao()
{
	int i,size;
	string cTmp,*line,tmp1,tmp2,xlh;
	
	cTmp = read_file("npc/party/xuliehao.txt");
	if ( sizeof(cTmp) == 0 )
		return;
	line = explode( cTmp, "\n" );
	size = sizeof(line);
	nXuliehao = ({});
        for( i = 0; i < size; i ++ ) 
	{
		if ( sscanf(line[i],"%s %s %s %s %s",tmp1,tmp1,tmp1,xlh,tmp2) != 5 )
			continue;
		nXuliehao += ({ xlh });
	}
//	size = sizeof(nXuliehao);
//	for( i = 0; i < size; i ++ ) 
//	{
//		log_file("xxx.txt",nXuliehao[i]+"\n");
//	}
}
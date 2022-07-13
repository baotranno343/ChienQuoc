#include <npc.h>
#include <city.h>
#include <ansi.h>
inherit SAVE_F;
inherit OFFICER;

void do_bonus(string arg);
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
        set_name("内测使者");	//台湾

        set_2( "talk", ([
                 "bonus"         : (: do_bonus :),
                 "info"         : (: do_info :),
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
		get_name()+":\n    如果您是曾经参与过前瞻测试的玩家，而且得到了领奖码，那么便可以在我这里通过领奖码得到丰富的奖励回报。\n    感谢您对我们游戏的支持，希望您游戏愉快。\n"
		+ sprintf(ESC"输入领奖码获取奖励\ntalk %x# inputx\n"ESC"离开",id,id) );
//		+ sprintf(ESC"领取25级领奖码\ntalk %x# bonus.1\n"ESC"领取40级领奖码\ntalk %x# bonus.2\n"ESC"查询领奖码\ntalk %x# info\n"ESC"离开",id,id,id) );
		
}


void do_bonus(string arg)
{
	__FILE__->do_bonus_2(this_player(),this_object(),arg);	
}

void do_bonus_2(object who , object me, string arg)
{
	int i,j,k,m,n,level,total,num1,num2,num3,grade;
	string res1,res2,res3,res4,res,tmp;
	string cFlag;
	
	i = to_int(arg);
	if ( i == 1 )
	{
		cFlag = "xuliehao25";
		grade = 25;
	}
	else if ( i == 2 )
	{
		cFlag = "xuliehao40";
		grade = 40;
	}
	else 
		return;
	if ( stringp(who->get_save(cFlag)) )
	{
		send_user(who,"%c%s",'!',"你已经领取过该级别领奖码了");
		return ;	
	}
	level = who->get_level();

	if ( level < grade  )
	{
		send_user(who,"%c%s",'!',"你的等级不够");
		return ;	
	}
	level = grade;
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
	who->set_save(cFlag,res);
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		me->get_name()+":\n    你的领奖码是："+ res+"\n    凭此码可以在内测服务器中，达到20级以后，领取不同的大礼包。请牢记。");
	log_file("xuliehao.txt",sprintf("%s %s %d %s %d\n",short_time(),who->get_id(),who->get_number(),res,level ));
}

void do_info()
{
	__FILE__->do_info_2(this_player(),this_object());	
}
void do_info_2(object who , object me)
{
	string tmp1,tmp2,tmp;

	tmp1=who->get_save("xuliehao25");
	tmp2=who->get_save("xuliehao40");

	if ( stringp(tmp1) && stringp(tmp2) )
		tmp = tmp1+"\n    " +tmp2;
	else if ( stringp(tmp1) )
		tmp = tmp1;
	else if ( stringp(tmp2) )
		tmp = tmp2;
	else
	{
		send_user(who,"%c%s",'!',"你还没有领取过序列号");
		return ;	
	}	
	send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
		me->get_name()+":\n    你的领奖序列号是：\n    "+ tmp+"\n    凭此码可以在内测服务器中，达到20级以后，领取不同的大礼包。请牢记。");
}

void do_input()
{
	__FILE__->do_input_2(this_player(),this_object());	
}
void do_input_2(object who , object me)
{
	send_user( who, "%c%c%d%s", '?', 16, 40, "请输入领奖码：\n"+sprintf( ESC"talk %x# get_bonus",getoid(me))+".%s\n");		

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
	string tmp,res1,res2,res3,res4,cFlag;

	if ( (i=me->get("times")) && gone_time(i) <= 3 )
	{
		send_user(who,"%c%s",'!',"请重新输入号码");
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
	for(level=0,i=0,size=sizeof(res2);i<size;i++)
	{
		level = level*10;
		level += to_int(mpTab1[res2[i..i]]);	
	}
	level /= 3;
	if ( level == 25 )
		cFlag = "xuliehao25";
	else if ( level == 40 )
		cFlag = "xuliehao40";
	
	if ( stringp(who->get_save(cFlag)) )
	{
		send_user(who,"%c%s",'!',"你已经领取奖励了");
		return ;	
	}	
	
	if ( level == 25 )
	{
		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
			return ;
		who->add_cash(20000);	
		if ( random(2) )
		{
			send_user(who,"%c%s",';',"得到奖励 金 20000 血力石 1");
			TASK_LEGEND_D->give_item(who,"item/08/0003",1); 
		}
		else
		{
			send_user(who,"%c%s",';',"得到奖励 金 20000 法力石 1");
			TASK_LEGEND_D->give_item(who,"item/08/0004",1); 
		}
	}
	else if ( level == 40 )
	{
		if ( TASK_LEGEND_D->can_carry_amount(who,3) != 1 )
			return ;
		who->add_cash(20000);	
		if ( random(2) )
		{
			res1 = "血力石";
			TASK_LEGEND_D->give_item(who,"item/08/0003",1); 
		}
		else
		{
			res1 = "法力石";
			TASK_LEGEND_D->give_item(who,"item/08/0004",1); 
		}
		TASK_LEGEND_D->give_item(who,"item/08/0001",1); 
		res2 = BOOK_FILE->get_book_file();
		TASK_LEGEND_D->give_item(who,res2,1); 
		send_user(who,"%c%s",';',sprintf("得到奖励 金 20000 %s 1 战国令 1 %s 1",res1,res2->get_name()));
		
	}
	
	who->set_save(cFlag,arg);	
	mpBonus[arg] = 1;
	save();
}

void read_xuliehao()
{
	int i,size;
	string cTmp,*line,tmp1,tmp2,xlh;
	
	cTmp = read_file("npc/party/xuliehaotw.txt");
	if ( sizeof(cTmp) == 0 )
		return;
	line = explode( cTmp, "\n" );
	size = sizeof(line);
	nXuliehao = ({});
        for( i = 0; i < size; i ++ ) 
	{
		if ( sscanf(line[i],"%s %s %s %s %s %s",tmp1,tmp1,tmp1,tmp1,xlh,tmp2) != 6 )
			continue;
		nXuliehao += ({ xlh });
	}
//	size = sizeof(nXuliehao);
//	for( i = 0; i < size; i ++ ) 
//	{
//		log_file("xxx.txt",nXuliehao[i]+"\n");
//	}
}
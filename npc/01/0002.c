
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;
mixed nQue = ({
		({"如果你想很轻松的去周国，应该要找谁？","驿站老板","门派向导","酒店老板","牛二"}),
		({"存钱应该在哪个NPC处？","当铺老板","酒店老板","工头","神仙爷爷"}),
		({"捡到使命物品后需要交给谁才能拿到奖励？","卫队长","老村长","李大伯","牛二"}),
		({"卫队长处可接什么任务？","剿匪任务","运镖任务","失窃任务","师爷任务"}),
		({"装备的耐久不够，应该找谁恢复？","修理店老板","防具店老板","武器店老板","当铺老板"}),
		({"打怪收集的掉落物品可以卖给哪个NPC？","杂货店老板","当铺老板","牛二","驿站老板"}),
		({"使命物品哪里不能获得？","周国","新手村","幽谷","清溪"}),
		({"药店老板处可以买到","活络丸","细麻衣","木刀","符纸"}),
		({"王捕头处可接","失窃任务","剿匪任务","运镖任务","师爷任务"}),
		({"想快速回到自己的门派找","门派向导","驿站老板","牛二","门派传送人"}),
		({"酒店老板处可以","购买酒食的材料","喝茶","吃饭","存钱"}),
		({"使命人物有什么用？","与他战斗","与他交朋友","找他接任务","找他领奖"}),

		});
// 函数：获取人物造型
int get_char_picid() { return 0700; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("AYASHIZI");
        set_city_name("新手村");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level", 0);
//        set("legend", ({ 20 }));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	
	if ( who->get_level() < 15 )
		send_user(who,"%c%s",':',sprintf("%s\n    年轻人，你是在向我挑战吗？\n"ESC"石狮的问题\ntalk %x# welcome.1\n"ESC"离开",get_name(),getoid(this_object())));
	else
		send_user(who,"%c%s",':',sprintf("%s\n    比我丑的没我笨，比我笨的没我丑，你敢挑战我么，我就是大名鼎鼎的AYASHIZI\n"ESC"离开",get_name()));	
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void give_question(object who, object me)
{
	int ord,ord1,*nOrd,size,i,j;
	string cWord,*cMain=({"第一题：","第二题：","第三题：","第四题："}),*res=({}),*tmp=({});
	
	nOrd = who->get("stonelionQ1");
	size=sizeof(nOrd);
	if ( !size )
		return ;
	ord = who->get("stonelionQ2");
	if ( ord >= size )
		return ;
	ord1 = ord;
	ord = nOrd[ord];
	cWord = me->get_name() + ":\n    " + cMain[ord1] + nQue[ord][0] + "\n";
	size = sizeof(nQue[ord]);
	for(i=2;i<size;i++)
		res += ({ nQue[ord][i]});
	j = random(size-1);
	who->set("stonelionQ3",90+j);
	who->set("stonelionQ4",nQue[ord][1]);
	size = sizeof(res);
	while(size)
	{
		if ( sizeof(tmp) == j )
		{
			tmp += ({ nQue[ord][1] });	//正确答案
		}
		i = random(size);
		tmp += ({ res[i] });
		res -= ({ res[i] });
		size--;
	}
	if ( sizeof(tmp) == j )
	{
		tmp += ({ nQue[ord][1] });	//正确答案
	}
	size = sizeof(tmp);
	for(i=0;i<size;i++)
	{
		cWord += sprintf(ESC"%s\ntalk %x# welcome.%d\n",tmp[i],getoid(me),90+i);	
	}
	send_user(who,"%c%s",':',cWord);
}
void do_welcome2( object me, string arg )
{
	int flag,i,j,k,size,*tmp=({}),*res=({}),p;
	object who,item,item1;
	
        who = this_player();
   	if ( who->get_level() >= 15 )
		return;
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
		send_user(who,"%c%s",':',sprintf("%s\n    古时传说有一种怪兽,会说人语,具有相当高的智慧,喜欢在荒野、沙漠的要道中,对著过往的旅人问谜语,若是能够回答出来的,就让其安全通过,若是答不出来的,就将其吃掉。当然，我不是那个怪兽，但是我也请你回答几个问题，如果你能回答正确，我就给你奖励！\n"ESC"继续\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
		break;
	case 2:
		who->delete("stonelionQ1");
		who->delete("stonelionQ2");
		who->delete("stonelionQ3");
		who->delete("stonelionQ4");
		size = sizeof(nQue);
		for(i=0;i<size;i++)
			tmp += ({i});
		for(i=0;i<4;i++)
		{
			j = random(size);
			k = tmp[size-1];
			tmp[size-1] = tmp[j];
			tmp[j] = k;
			res += ({tmp[size-1]});
			size--;
		}
		who->set("stonelionQ1",res);
		__FILE__->give_question(who,me);
		break;
	case 90..100:
		if ( !who->get("stonelionQ3") )
			return ;
		if (  who->get("stonelionQ3") != flag )
		{
			if ( stringp(who->get("stonelionQ4")) )
				send_user(who,"%c%s",':',sprintf("%s\n    很遗憾，你的了解度还不够，熟悉熟悉再来吧！\n    正确答案是"HIR"%d.%s",me->get_name(),who->get("stonelionQ3")-89,who->get("stonelionQ4")));
			who->delete("stonelionQ1");
			who->delete("stonelionQ2");
			who->delete("stonelionQ3");
			who->delete("stonelionQ4");
			return ;
		}
		i = who->add("stonelionQ2",1);
		if ( i == 1 )
			send_user(who,"%c%s",':',sprintf("%s\n    呃……难不倒你……继续第二题吧！\n"ESC"继续\ntalk %x# welcome.10\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( i == 2 )
			send_user(who,"%c%s",':',sprintf("%s\n    又答对了？还要继续吗？\n"ESC"继续\ntalk %x# welcome.10\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( i == 3 )
			send_user(who,"%c%s",':',sprintf("%s\n    你真聪明！我只剩最后一题了！\n"ESC"继续\ntalk %x# welcome.10\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( i == 4 )
		{
			if ( !who->get_legend(TASK_NEWBIE_00, 20) )
				send_user(who,"%c%s",':',sprintf("%s\n    实在是太佩服你了！你居然都知道！你应该改个名字叫“百事通”！我的奖励是聪明人才能拿到的，你拿着吧！\n"ESC"完成\ntalk %x# welcome.11\n",me->get_name(),getoid(me)));
			else
				send_user(who,"%c%s",':',sprintf("%s\n    实在是太佩服你了！你居然都知道！你应该改个名字叫“百事通”！\n"ESC"离开\n",me->get_name()));
		}
		break;
	case 10:
		if ( who->get("stonelionQ2") )
			__FILE__->give_question(who,me);	
		break;
	case 11:
		if ( who->get("stonelionQ2") != 4 )
			return;
		if ( who->get_legend(TASK_NEWBIE_00, 20) )	//奖励一次
			return ;
		item = new( "/item/91/9100" );
		if ( !item )
			return ;
		item1 = new( "/item/91/9110" );
		if ( !item1 )
		{
			destruct(item1);
			return ;
		}
		item->set_amount(5);
		item1->set_amount(3);
                p =item->move(who, -1);
                if ( p == 0 )
                {
                	destruct(item); 
                	destruct(item1); 
                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
                	return ;
                }
                else	
                	item->add_to_user(p);
                p =item1->move(who, -1);
                if ( p )
                {
               		item1->add_to_user(p);
		}
               	else 
               	{
               		item->remove_from_user();
                	destruct(item); 
                	destruct(item1); 
                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
                	return ;
                }
		who->set_legend(TASK_NEWBIE_00, 20);
		who->add_exp(250);
		who->add_cash(2000);
		send_user(who,"%c%s",';',"石狮的问题 经验 250 金钱 2000 行军散 5 正气散 3");
		break;
	}
		
}
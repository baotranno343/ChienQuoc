#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <city.h>

inherit OFFICER;
inherit SAVE_F;

string get_save_file()	{ return "data/org_buchang"SAVE_EXTENSION;}

mapping mpOrg = ([]);

// 函数：获取人物造型
int get_char_picid() { return 5502; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("帮派补偿员");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );
        setup();
        
        restore();
        if ( !mapp(mpOrg) ) mpOrg= ([]);
}

void do_look(object who)
{
	object me=this_object();
	string name;
	int id = getoid(me),iHost;
	int Gold,iFavour,iStable,iStore;
	object orgnpc;
	if (MAIN_D->get_host_type()!=2)
		return ;
	iHost = MAIN_D->get_host();
//	if ( iHost == 1 || iHost == 4501 )	//天下,松花江除外
//		return ;
	name = who->get_org_name();
	if (name=="") return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
	switch(orgnpc->get_grade())
	{
		default:
			break ;
		case 2:
			Gold=5000000; iFavour=1000;iStable=1000;iStore=450;
			break;
		case 3:
			Gold=10000000; iFavour=2000;iStable=2000;iStore=700;
			break;
		case 4:
			Gold=20000000; iFavour=3000;iStable=3000;iStore=1100;
			break;
		case 5:
			Gold=40000000; iFavour=4000;iStable=4000;iStore=1500;
			break;									
	}
	send_user(who,"%c%c%w%s",':',3,this_object()->get_char_picid(),sprintf("%s：\n    本次合并服务器对大家造成的不便我们深感抱歉。为了补偿贵方的损失，只要你是帮派的帮主便可以来我这里领取一个名为‘帮派信物’的赔偿物品。当在合并服务器之后，只要你加入或者创建一个帮派，直接使用信物后其内包含的‘帮派资金’、‘人气’、‘安定’与‘储备’便会转移到新的帮派中。\n    随着本帮派规模等级越高，领取的补偿便会越多，但是1级的帮派我是不会给予任何补偿的。\n    当前帮派可以领取"HIR"%d帮派资金"NOR" 、"HIR"%d帮派人气"NOR"、"HIR"%d帮派安定"NOR"与"HIR"%d帮派储备"NOR"，你确定要现在领取补偿吗？\n"ESC"是的，我要现在领取。\ntalk %x# welcome.1\n"ESC"还是下次吧。",me->get_name(),Gold,iFavour,iStable,iStore,id));
	
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag, p,iTime,iGrade,iHost;
       	object who, orgnpc,item;
	int Gold,iFavour,iStable,iStore;
       	string name;
	mixed *mxTime;    

	if (MAIN_D->get_host_type()!=2)
		return ;
	iHost = MAIN_D->get_host();
//	if ( iHost == 1 || iHost == 4501 )	//天下,松花江除外
//		return ;
        who = this_player();
	name = who->get_org_name();
	if (name=="") return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
	switch((iGrade=orgnpc->get_grade()))
	{
		default:
			break ;
		case 2:
			Gold=5000000; iFavour=1000;iStable=1000;iStore=450;
			break;
		case 3:
			Gold=10000000; iFavour=2000;iStable=2000;iStore=700;
			break;
		case 4:
			Gold=20000000; iFavour=3000;iStable=3000;iStore=1100;
			break;
		case 5:
			Gold=40000000; iFavour=4000;iStable=4000;iStore=1500;
			break;									
	}		 
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_org_position() != ORG_MASTER )        	
		{
			send_user(who,"%c%s",'!',"你不是帮主，无法领取赔偿。");
			return ;	
		}
		if ( iGrade < 2 )        	
		{
			send_user(who,"%c%s",'!',"你的帮派规模不足2级，无法领取赔偿。");
			return ;	
		}
		if ( mpOrg[name] )
		{
			send_user(who,"%c%s",'!',"你的帮派已经领取过了赔偿，无法再次领取。");
			return ;	
		}
		if ( TASK_LEGEND_D->can_carry_amount(who,2) != 1 )
				return ;
		TASK_LEGEND_D->give_item(who,"item/std/0095",1); 
		item = new("item/04/0418");	
		if ( !item )
			return ;
		item->set("special",sprintf("%d|%d|%d|%d",Gold,iFavour,iStable,iStore));
		p = item->move(who,-1);
		if ( !p )
		{
			destruct(item);
			send_user(who,"%c%s",'!',"你的包裹已满，不能得到赔偿，请清空后再来。");
			return;	
		}
		item->add_to_user(p);
		mpOrg[name] = 1 ;
		save();
		send_user(who,"%c%s",'!',"你领取了帮派信物和王之号角。");
		log_file("org_buchang.txt",sprintf("%s %s %d\n",short_time(),who->get_name(),who->get_number()));
        	break;
        }

}

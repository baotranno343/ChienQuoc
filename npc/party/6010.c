
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 6010; }

void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("战国补偿使者");

        set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
        int id = getoid( this_object() );
	string result="";
	object item;

	if (MAIN_D->get_host()!=1001
	&& MAIN_D->get_host()!=8001
	&& MAIN_D->get_host()!=7001)
	{
		send_user(who,"%c%s",':',get_name() + "：\n    非常感谢您对大话战国的支持，我们将会齐心协力将大话战国做好！！！\n");
		return;
	}

	send_user( who, "%c%c%w%s", ':', 3, 6010, get_name() + "：\n    非常感谢您对大话战国的支持，我们将会齐心协力将大话战国做好！！！\n"
	+ESC"领取补偿\n"+ sprintf( "talk %x# welcome.1\n", id )
	+ESC"离开。\nCLOSE\n" );
}


void do_welcome(string arg)
{
        __FILE__ ->do_welcome2(this_object(),arg );
}

void do_welcome2( object me ,string arg)
{
	object item,player=this_player();
	string result,*items=({"/item/bind/sell/0032","/item/bind/08/0001","/item/bind/08/0001","/item/bind/08/0002","/item/bind/08/0002",});
	int flag,level,exp,pot,limit_exp,limit_pot,i,size,p;
	
	if (!arg) return;
	flag=to_int(arg);
	switch (flag)
	{
	case 1:
	
		if (MAIN_D->get_host()!=1001
		&& MAIN_D->get_host()!=8001
		&& MAIN_D->get_host()!=7001)
		{
			send_user(player,"%c%s",':',get_name() + "：\n    非常感谢您对大话战国的支持，我们将会齐心协力将大话战国做好！！！\n");
			return;
		}


		if ( (level=player->get_level() )<30 )
		{
			send_user(player,"%c%s",':',"你不满足领取补偿条件（领取补偿的玩家等级须≥30级）。");
			return;
		}
		if (player->get_save("kjh_repair") )
		{
			send_user(player,"%c%s",':',"你已经领取过补偿。");
			return;
		}
		exp=100000+level*level*500;
		pot=5000+level*level*5;
		limit_exp=USER_EXP_D->get_upgrade_exp_limit(player);
		limit_pot=player->get_max_potential();
	
		if (exp+player->get_upgrade_exp()>limit_exp)
		{
			send_user(player,"%c%s",':',sprintf("你将获得%d点经验补偿，但是你现在拥有的经验太多了，请清理部分经验后再来领取补偿。",exp) );
			return;
		}
		if (pot+player->get_potential()>limit_pot)
		{
			send_user(player,"%c%s",':',sprintf("你将获得%d点潜能补偿，但是你现在拥有的潜能太多了，请清理部分潜能后再来领取补偿。",pot) );
			return;
		}
		result="";
		if ( MAIN_D->get_host()==7001 )
		{
			if (USER_INVENTORY_D->get_free_count(player) < 5)
			{
				send_user(player,"%c%s",':',"你道具栏的空位少于5个，请清理道具栏后再来领取补偿。" );
				return;
			}
			result+="你获得了物品：";
			for(i=0,size=sizeof(items);i<size;i++)
			{
				item=new(items[i]);
				if (!objectp(item) ) continue;
				if (p=item->move2(player) )
				{
					item->add_to_user(p);
					result+=HIR+item->get_name()+NOR " ";
				}
			}
			send_user(player,"%c%s",';',result);
		}
		result+="\n"+sprintf("你获得了%d点的经验补偿，%d点的潜能补偿。",exp,pot);
		player->add_potential(pot);
		player->add_exp(exp);
		player->set_save("kjh_repair",1);
		send_user(player,"%c%s",';',result);
		return;

	default:return;
	}

}               
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
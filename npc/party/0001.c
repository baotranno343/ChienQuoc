#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <public.h>

inherit OFFICER;

int iTimes;

int * gift = ({ 0271, 0413, 0414, 0417, 0418, 0211, 0212, 0316, 0317, 0319, 0221, 0222, 0231, 0325, 0329, 0241, 0242, 0251, 0348, 0349, 0261, 0363, 0364, 0365, 0368, 0421, 0422, 0423, 0424, 0425, 0281, 0501, 0511, 0531, 0591, });

// 函数：获取人物造型
int get_char_picid() { return 6800; }
void do_bonus(string arg);
void do_setup(string arg);

// 函数：构造处理
void create()
{
        set_name("大神Ten");
        set_2( "talk", ([
                 "bonus"         : (: do_bonus :),
                 "setit"	 : (: do_setup :),
        ]) );

        setup();
}

void do_look( object who ) { __FILE__->do_look_call(who,this_object());}

void do_look_call(object who, object npc)
{
	if( is_player(who)  ) 
        {
        	if ( iTimes == 0 )
        		return ;
        	if ( who->get_save_2("wzx_bonus6") != iTimes ) 
			send_user(who,"%c%c%w%s", ':', 3 ,npc->get_char_picid(),sprintf("%s:\n    你是来领奖的吗?\n"ESC"接受奖励\ntalk %x# bonus.1\n"ESC"离开",npc->get_name(),getoid(npc)));
        }
        else
		send_user(who,"%c%c%w%s", ':', 3 ,npc->get_char_picid(),sprintf("%s:\n    你是来领奖的吗?\n"ESC"接受奖励\ntalk %x# bonus.1\n"ESC"设置\ntalk %x# setit.1\n"ESC"离开",npc->get_name(),getoid(npc),getoid(npc)));
}

void do_bonus(string arg) { __FILE__->do_bonus_call(this_player(),this_object(),arg);}

void do_bonus_call(object who,object npc,string arg)
{
	int i,r, rate;
	string file;
	object item;
	
	i = to_int(arg);
	if ( i == 1 )
	{
		if ( iTimes == 0 )
		{
			notify( "活动尚未开始呢。" );
			return ;
		}
		if ( who->get_save_2("wzx_bonus6") == iTimes )
		{
			notify( "您已经拿过第"+iTimes+"次的奖励了。" );
			return ;
		}
		if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY )
		{
			notify( "您携带的东西太多了。" );
			return;
		}	
		rate = random(100);
		if (rate<30)
		{
			who->add_cash(10000);
			who->set_save_2("wzx_bonus6",iTimes);
			send_user(who,"%c%s",';', "你得到1万金的奖励");
			log_file("wzx_bonus.txt",sprintf("%s,%d %s b %d\n",short_time(),who->get_number(),who->get_name(),iTimes));
			return;			
		}
		if (rate<55)
			file = sprintf("item/95/%d",gift[random(sizeof(gift))]);
		else		
		if (rate<80)
			file = "item/std/8000";
		else
		if (rate<85)
			file = "item/08/0001";		
		else
		if (rate<90)
			file = "item/08/0004";	
		else
		if (rate<95)
			file = "item/08/0003";	
		else
			file = "item/08/0002";										
		item = new(file);	
		if ( !item ) return 0;
		if( USER_INVENTORY_D->can_carry(who, item)  >=1 )
		{
			send_user(who,"%c%s",';',sprintf("你得到%s的奖励", item->get_name()));
			r =item->move(who, -1);
			item->add_to_user(r);
			who->set_save_2("wzx_bonus6",iTimes);
			log_file("wzx_bonus.txt",sprintf("%s,%d %s b %d\n",short_time(),who->get_number(),who->get_name(),iTimes));
			return ;
		}
		else
		{
			notify( "您携带的东西太多了。" );
			destruct(item);			
		}		
	}	
}

void do_setup(string arg) { __FILE__->do_setup_call(this_player(),this_object(),arg);}

void do_setup_call(object who, object npc,string arg)
{
	int i,j;
	if ( is_player(who) )
		return ;
	if ( sscanf(arg,"%d.%d",i,j)!=2 )
		i = to_int(arg);
	if ( i == 1 )
		send_user( who, "%c%c%d%s", '?', 1, 30,sprintf("请输入活动的次数\n"ESC"talk %x# setit.2.",getoid(npc))+"%s");
	else
	{
		iTimes = j;
		send_user(who,"%c%s",';',sprintf("活动次数设置为%d",iTimes) );
	}
	
}
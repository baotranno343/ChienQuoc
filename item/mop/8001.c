#include <ansi.h>
#include <equip.h>
inherit ITEM;
inherit COMBINED;

int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name("战国金色礼包");
        set_picid_1(8503);
        set_picid_2(8503);
        set_amount(1);
        set_value(100);
}

int is_usable() {return 1;}

// 函数：获取描述
string get_desc() 
{ 
        return "装有周王奖励物品的礼包，右击即可打开。"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash,level,exp;
	object item;
       	string *nTmp,tmp,cTmp;
	string *nFamily = ({"桃花源","蜀山","禁卫军","唐门","茅山","昆仑山","云梦泽"});
	int *bian=({1267,1238,1225,1201,1200});
	if(USER_INVENTORY_D->get_free_count(who) < 1 )
	{
	        send_user(who,"%c%s",';',"你的道具栏空间不足够哦，请整理一下吧。");
    		return 0;
	}
	rate = random(100);
	if (rate<9) 
		item = new ("/item/91/9167"); //紫参丹
	else if (rate<12)
		item = new ("/item/bind/08/0003");//小血
	else if (rate<14)
		item = new ("/item/08/0004");//小法
	else if (rate<16)
		item = new ("/item/bind/08/0002");//号角
	else if (rate<17)
		item = new ("/item/bind/08/0001");//令
	else if (rate<27) 
		exp=who->get_level()*2500;
	else if (rate<37) 
		exp=who->get_level()*2000;
	else if (rate<47) 
		exp=who->get_level()*1000;
	else if (rate<57)
		item = new ("/item/sell/0043");//开门芝麻
	else if (rate<70)
		item = new ("/item/sell/0012");//友情呼唤
	else if (rate<100) 
		cash = 10000;
	if ( item )
	{
		CHAT_D->sys_channel(0,sprintf(HIY"%s"HIG"玩家由于积极提供战场物资，特获得周王"HIY"%s"HIG"的奖励！具体信息请前去新手村（137，144），周国（278，155）战国征集兵处查询。",who->get_name(),item->get_name()));
		p = item->move2(who);
		item->add_to_user(p);	
	}
	else if ( cash )
	{
		who->add_cash(cash);
		send_user(who,"%c%s",'!',sprintf("获得金钱 %d",cash));
	}		
	else if ( exp )
	{
		who->add_exp(exp);
		send_user(who,"%c%s",'!',sprintf("获得经验%d",exp));
//		CHAT_D->sys_channel(0,sprintf(HIY"%s"HIR"玩家由于积极提供战场物资，特获得周王"HIY"经验%d"HIR"的奖励！具体信息请前去新手村（137，144），周国（278，155）战国征集兵处查询。",who->get_name(),exp));
	}
	gift->add_amount(-1);
	"sys/sys/magic_card"->change_shape(who,bian[random(sizeof(bian))],3600);
	return 0;
}


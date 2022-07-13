#include <ansi.h>
inherit ITEM;
// 函数：构造处理
void create()
{
        set_name("Tiểu Bảo Rương");
        set_picid_1(0080);
        set_picid_2(0080);
        set_value(10);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "不知道是谁丢失的小宝箱，打开看看有什么惊喜……"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash,exp,pot;
	object item;
	
	rate = random(100);

	if ( rate < 20 )
	{
		exp = 100;	
	}
	else if ( rate < 30 )
	{
		pot = 20;	
	}
	else if ( rate < 40 )	//桔子5个
	{
		item = new("item/32/3282");
		item->set_amount(5);
	}
	else if ( rate < 50 )	//米酒5坛
	{
		item = new("item/31/3150");
		item->set_amount(5);
	}
	else if ( rate < 60 )
	{
		cash = 100;	
	}
	else if ( rate < 70 )	//一口肉5
	{
		item = new("item/final/33/1700");
		item->set_amount(5);
	}
	else if ( rate < 80 )	//烤地瓜5
	{
		item = new("item/final/33/1701");
		item->set_amount(5);
	}
	else if ( rate < 90 )	//绿豆汤5
	{
		item = new("item/final/33/1750");
		item->set_amount(5);
	}
	else			//玉米汤5
	{
		item = new("item/final/33/1751");
		item->set_amount(5);
	}

	gift->remove_from_user();
	destruct(gift);
	if ( item )
	{
		send_user(who,"%c%s",'!',"恭喜您！您打开小宝箱得到了"+item->get_name());
		p = item->move(who,-1);
		item->add_to_user(p);	
	}
	else if (  cash )
	{
		who->add_cash(cash);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您打开小宝箱得到了%d金",cash));
	}
	else if (  exp )
	{
		who->add_exp(exp);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您打开小宝箱得到了%d点经验",exp));
	}
	else if (  pot )
	{
		who->add_potential(pot);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您打开小宝箱得到了%d点潜能",pot));
	}
	return 0;
}


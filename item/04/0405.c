#include <ansi.h>
inherit ITEM;

int get_item_value() {return 225 ;}
int get_item_value_2() {return 200 ;}
int get_item_number() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("大礼包");
        set_picid_1(4981);
        set_picid_2(4981);
        set_value(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "装有礼品的包裹。"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash;
	object item;
	
	rate = random(100);
	
	if ( rate < 8 )		//战国令
	{
		item = new("item/08/0001");
		if ( !item )
			return 0;
	}
	else if ( rate < 16 )	//战国号角
	{
		item = new("item/08/0002");
		if ( !item )
			return 0;
	}
	else if ( rate < 26 )	//血石
	{
		item = new("item/08/0003");
		if ( !item )
			return 0;
	}
	else if ( rate < 36 )	//法力石
	{
		item = new("item/08/0004");
		if ( !item )
			return 0;
	}
	else if ( rate < 50 )	//行军散
	{
		item = new("item/91/9100");
		if ( !item )
			return 0;
		item->set_amount(20);
	}
	else if ( rate < 64 )	//正气散
	{
		item = new("item/91/9110");
		if ( !item )
			return 0;
		item->set_amount(20);
	}
	else if ( rate < 74 )	//藏宝图
	{
		item = new("item/std/8000");
		if ( !item )
			return 0;
	}
	else if ( rate < 94 )
	{
		cash = 10000;
	}
	else if ( rate < 98 )	//百宝囊
	{
		item = new("item/std/6001");
		if ( !item )
			return 0;
	}
	else 			//乾坤袋
	{
		item = new("item/std/6002");
		if ( !item )
			return 0;
	}
	gift->remove_from_user();
	destruct(gift);
	if ( item )
	{
		send_user(who,"%c%s",'!',"恭喜您！您打开大礼包得到了"+item->get_name());
		p = item->move2(who);
		item->add_to_user(p);	
	}
	else if (  cash )
	{
		who->add_cash(cash);
		who->add_gold_log("item0405", cash);
		"/sys/sys/count"->add_income("item0405", cash);
		send_user(who,"%c%s",'!',"恭喜您！您打开大礼包得到了10000金");
	}
	return 0;
}


#include <ansi.h>
inherit ITEM;
// 函数：构造处理
void create()
{
        set_name("中秋节大礼包");
        set_picid_1(4981);
        set_picid_2(4981);
        set_value(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return ""; 
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
	
	if ( rate < 12 )		//战国令
	{
		item = new("item/08/0001");
		if ( !item )
			return 0;
	}
	else if ( rate < 24 )	//战国号角
	{
		item = new("item/08/0002");
		if ( !item )
			return 0;
	}
	else if ( rate < 44 )	//血石
	{
		item = new("item/08/0003");
		if ( !item )
			return 0;
	}
	else if ( rate < 64 )	//法力石
	{
		item = new("item/08/0004");
		if ( !item )
			return 0;
	}
	else if ( rate < 87 )
	{
		cash = 10000;
	}
	else if ( rate < 97 )
	{
		cash = 50000;
	}
	else if ( rate < 99 )	//百宝囊
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
		send_user(who,"%c%s",'!',"恭喜您！您打开中秋大礼包得到了"+item->get_name());
		p = item->move2(who);
		item->add_to_user(p);	
	}
	else if (  cash )
	{
		who->add_cash(cash);
		send_user(who,"%c%s",'!',sprintf("恭喜您！您打开中秋大礼包得到了%d金",cash));
	}
	return 0;
}


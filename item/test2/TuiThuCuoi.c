#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() {return 50 ;}
int get_item_value_2() {return 50 ;}
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Túi Thú Cưỡi");
        set_picid_1(9993);
        set_picid_2(9993);
        set_value(1);
		set_amount(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Túi quà Thú Cưỡi chứa đựng rất nhiều thú cưỡi quý giá"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash;
	object item;
	
	if(USER_INVENTORY_D->get_free_count(who) < 1 )
		{
				notify( "Hành trang không đủ 1 chỗ trống" );
		return 0;
		}
	rate = random(10000);
	
	if ( rate < 2000 )	//百宝囊
	{
		item = new("item/ride/BOX4/006");
		if ( !item )
			return 0;
	}
	else if ( rate < 3500 )	//百宝囊
	{
		item = new("item/ride/BOX4/004");
		if ( !item )
			return 0;
	}
	else if ( rate < 4500 )	//百宝囊
	{
		item = new("item/ride/BOX4/007");
		if ( !item )
			return 0;
	}
	else if ( rate < 5500 )	//百宝囊
	{
		item = new("item/ride/BOX4/001");
		if ( !item )
			return 0;
	}
	else if ( rate < 6500 )	//百宝囊
	{
		item = new("item/ride/BOX4/003");
		if ( !item )
			return 0;
	}
	else if ( rate < 8000 )	//百宝囊
	{
		item = new("item/ride/BOX4/005");
		if ( !item )
			return 0;
	}
	else 			//乾坤袋
	{
		item = new("item/ride/BOX4/002");
		if ( !item )
			return 0;
	}
	gift->add_amount(-1);
	if ( item )
	{
		send_user(who,"%c%s",'!',"Bạn nhận được "+item->get_name());
		p = item->move2(who);
		item->add_to_user(p);
		USER_D->user_channel(sprintf("Bằng hữu %s mở Túi Thú Cưỡi nhận được %s ", who->get_name(),item->get_name() ));	
	}
	return 0;
}


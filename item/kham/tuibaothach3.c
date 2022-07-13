#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Túi Bảo thạch Cấp 3");
        set_picid_1(7124);
        set_picid_2(7124);
        set_value(1);
		set_amount(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Mở ra sẽ có cơ hội nhận được các loại Bảo thạch cấp 3 quý hiếm."; 
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
	
	if ( rate < 2000 )		//战国令
	{
		item = new("item/kham/khamhp3");
		if ( !item )
			return 0;
	}
	else if ( rate < 4000 )	//战国号角
	{
		item = new("item/kham/khamap3");
		if ( !item )
			return 0;
	}
	else if ( rate < 6000 )	//战国号角
	{
		item = new("item/kham/khamcp3");
		if ( !item )
			return 0;
	}
	else if ( rate < 8000 )	//战国号角
	{
		item = new("item/kham/khamdp3");
		if ( !item )
			return 0;
	}
	else 			//乾坤袋
	{
		item = new("item/kham/khampp3");
		if ( !item )
			return 0;
	}
	gift->add_amount(-1);
	if ( item )
	{
		send_user(who,"%c%s",'!',"Bạn nhận được "+item->get_name());
		p = item->move2(who);
		item->add_to_user(p);	
		USER_D->user_channel(sprintf("Bằng hữu "HIR"%s"NOR" mở Túi bảo thạch và nhận được "HIY"%s"NOR".", who->get_name(),item->get_name() ));
	}
	return 0;
}


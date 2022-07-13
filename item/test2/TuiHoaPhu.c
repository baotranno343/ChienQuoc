#include <ansi.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }
int get_item_value() {return 5000 ;}
int get_item_value_2() {return 5000 ;}

// 函数：构造处理
void create()
{
        set_name( "Túi Hoả Phù" );
        set_picid_1(7107);
        set_picid_2(7107);
        set_value(5000);
		set_save("knb",5000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Tùi thần kỳ, có thể mở ra 50 cái Hoả Phù dùng cho sự kiện Thuê vật phẩm. ";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int p;
	object item;

	if(USER_INVENTORY_D->get_free_count(who) < 1 )
	{
	        send_user(who,"%c%s",'!',"Hành trang không đủ 1 chỗ trống.");
    		return 0;
	}
	item = new("item/ppvacanh/HoaPhu");
	item->set_amount(50);
	gift->remove_from_user();
	destruct(gift);
	send_user(who,"%c%s",';',"Bạn nhận được 50 cái "HIY"Hoả Phù");
	p = item->move2(who,-1);
	item->add_to_user(p);
	return 0;
}
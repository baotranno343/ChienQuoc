#include <ansi.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

// 函数：构造处理
void create()
{
        set_name( "Chén Bạc (5)" );
        set_picid_1(7126);
        set_picid_2(7126);
        set_value(500);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Mở Túi nhận được 5 Chén Bạc.";
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
	        send_user(who,"%c%s",'!',"Hành trang không đủ chỗ.");
    		return 0;
	}

	item = new("item/test/chenbac");
	item->set_amount(5);
	gift->remove_from_user();
	destruct(gift);
	send_user(who,"%c%s",';',"Bạn nhận được "HIY"5 Chén Bạc");
	p = item->move2(who,-1);
	item->add_to_user(p);
	return 0;
}
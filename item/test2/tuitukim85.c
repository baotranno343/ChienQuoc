#include <ansi.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Túi Tử Kim cấp 85");
        set_picid_1(7125);
        set_picid_2(7125);
        set_value(10000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sử dụng nhận được Trang bị Tử Kim cấp 85";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who, object gift ) 
{
	int p;
	object item;

	if (who->get_fam_name() == "")
	{
	send_user(who,"%c%s",'!',"Gia Nhập Phái đi Bạn.");
    		return 0;
	}
	if(USER_INVENTORY_D->get_free_count(who) < 1 )
		{
				notify( "Hành trang không đủ 1 chỗ trống" );
		return 0;
		}
	gift->remove_from_user();
	destruct(gift);
	item = new(sprintf("item/%d/%d085",55+random(5),who->get_fam_type()));
	item->set_hide(0);
	p = item->move2(who,-1);
	item->add_to_user(p);
	return 0;
}
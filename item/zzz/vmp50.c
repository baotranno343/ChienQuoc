#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }
int get_item_value() {return 100 ;}
int get_item_value_2() {return 100 ;}

// 函数：构造处理
void create()
{
        set_name("Túi Hoàng Kim Vô Môn Phái cấp 50");
        set_picid_1(3102);
        set_picid_2(3102);
        set_value(100);
}

// 函数：获取描述
string get_desc( object me ) 
{ 
        return "Sau khi sử dụng có thể nhận được một bộ trang bị Hoàng Kim Vô Môn Phái cấp 50 tương ứng giới tính.";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who, object gift ) 
{
	int p,level,gender,gender1;
	object item;
	string *nTmp,cFile;
	
	if ( who->get_gender()==1 ) {
	gender = 60;
	gender1 = 65;
	}
	else if ( who->get_gender()==2 ) {
	gender = 61;
	gender1 = 66;
	}
	if(USER_INVENTORY_D->get_free_count(who) < 5 )
	{
	        send_user(who,"%c%s",'!',"Hành trang không đủ chỗ.");
    		return 0;
	}

	gift->remove_from_user();
	destruct(gift);
		item = new(sprintf("item/%d/0050",gender));
		item->set_hide(0);
		ITEM_EQUIP_D->init_equip_prop_3(item);
		p = item->move2(who,-1);
		item->add_to_user(p);
		
		item = new(sprintf("item/%d/0050",gender1));
		item->set_hide(0);
		ITEM_EQUIP_D->init_equip_prop_3(item);
		p = item->move2(who,-1);
		item->add_to_user(p);
		
		item = new("item/86/0050");
		item->set_hide(0);
		ITEM_EQUIP_D->init_equip_prop_3(item);
		p = item->move2(who,-1);
		item->add_to_user(p);
		
		item = new("item/87/0050");
		item->set_hide(0);
		ITEM_EQUIP_D->init_equip_prop_3(item);
		p = item->move2(who,-1);
		item->add_to_user(p);
		
		item = new("item/88/0050");
		item->set_hide(0);
		ITEM_EQUIP_D->init_equip_prop_3(item);
		p = item->move2(who,-1);
		item->add_to_user(p);
	return 0;
}
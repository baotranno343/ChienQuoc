#include <ansi.h>
#include <equip.h>
inherit USABLE;
inherit ITEM;

int is_box() {return 1;}
int get_item_value() {return 300 ;}
int get_item_value_2() {return 300 ;}
int get_item_color() {return 2 ;}

// 函数：构造处理
void create()
{
        set_name("Hộp May Mắn");
        set_picid_1(6706);
        set_picid_2(6706);
        set_level(5);
        set_value(50);
		set_no_give(1);		
        set_no_sell(1);
		set_no_drop(1);
}

// 函数：获取描述
string get_desc()
{
        return "Một chiếc hộp dùng cho sự kiện Quay Số May Mắn ( có thể dùng "HIY "Chìa Khoá May Mắn "NOR " mở ra) \nChìa khoá May Mắn có thể mua với giá 100 triệu ngân lượng \nhoặc đánh Siêu Boss -- Song Nhi......................................\n(Khi quay ra trang bị Hoàng Kim hãy tới gặp NPC Lương Phan Tiên tái tạo để có chỉ số đúng của trang bị)";
}

int get_use_effect( object me ) 
{
	return "/item/01/0204"->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	int p;
	object item1;
	if(USER_INVENTORY_D->get_free_count(who) < 1 )
		{
		write_user(who, ECHO"Hành trang không đủ 1 chỗ trống");
		return 0;
		}	
	if (who->get_2("openbox.item")) return 0;
	if (who->get_online_rate()<100)
	{
		send_user(who, "%c%s", ';', "bla bla bla");
		return 0;
	}	
	send_user( who, "%c%c%c%d", 0x91, 1, 3, getoid(item) );
	return 0;
}
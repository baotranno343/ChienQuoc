#include <ansi.h>
#include <equip.h>
inherit USABLE;
inherit ITEM;

int is_box() {return 1;}
int get_item_value() {return 300 ;}
int get_item_value_2() {return 300 ;}

// 函数：构造处理
void create()
{
        set_name("Hồng Mộc Bảo Hộp");
        set_picid_1(6702);
        set_picid_2(6702);
        set_level(1);
        set_value(50);
}

// 函数：获取描述
string get_desc()
{
        return "Kho tàng của Chu Vương cất giấu, được làm từ những vật liệu tốt nhất ( có thể dùng "HIR "Chìa Khoá Hồng Mộc "NOR " mở ra).";
}

int get_use_effect( object me ) 
{
	return "/item/01/0200"->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	if (who->get_2("openbox.item")) return 0;
	if (who->get_online_rate()<100)
	{
		send_user(who, "%c%s", ';', "bla bla bla");
		return 0;
	}	
	send_user( who, "%c%c%c%d", 0x91, 1, item->get_level(), getoid(item) );
	return 0;
}
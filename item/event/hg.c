#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   
int get_item_color() {return 2 ;}
// 函数：构造处理
void create()
{
        set_name("Hạt Giống Cây Xanh");
        set_picid_1(3234);
        set_picid_2(3234);
        set_unit("只");
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{
	return "Sử dụng sẽ trồng ra 1 Cây xanh";
}

int get_use_effect(object who) { return __FILE__->get_use_effect_callout(who,this_object()); }

int get_use_effect_callout(object who,object item)
{
	int x,y,z,x0,y0,p;
	object obj,*nObj;
	
   if ( who->get_save("solantrong") == 1 ) {
    if ( who->get_save("trongcay") < 1 ) {
		write_user(who, ECHO"Bạn phải khiến cây lớn biến mất mới trồng tiếp được");
		return 0;
	}
	}
	z = get_z(who);  x0 = get_x(who);  y0 = get_y(who);
	p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK);
        if( !p )
        	return 0;
	x = p / 1000;  y = p % 1000;
	obj = new("npc/event/CayNho");
	if ( !obj )
		return 0;
	obj->set("birth",time());
	obj->set_save("tuoinuoc",who->get_number());
	obj->add_to_scene( z, x, y);
	who->set_save("trongcay",0);
	who->set_save("solantrong",1);
	send_user(who,"%c%s",';',"Bạn đã trồng Cây !");
	return 1;
}
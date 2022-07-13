#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;
inherit COMBINED;

int get_item_color() { return 2; }
int get_item_value() {return 5 ;}
int get_item_value_2() {return 5 ;}

// 函数：构造处理
void create()
{
        set_name("Thiên Lý Truyền Âm");
		set_picid_1(0095);
        set_picid_2(0095);
        set_value(5000);
	//	set_save("knb2",5);
		set_amount(1);
}

// 函数：获取描述
string get_desc( object me ) 
{
		return "Thiên Lý Truyền Âm, khi sử dụng có thể nói chuyện với mọi người trên khắp thế giới.";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object me,object gift ) 
{
	string arg;
					if ( gone_time(me->get("tlta" )) < 60 )
					{
					send_user(me,"%c%s",'!', sprintf("Tái sử dụng sau %d giây !", 60-gone_time(me->get("tlta" )) ));
					return 0;	
					}	
					send_user( me, "%c%c%d%s", '?', 16, 100, "Xin nhập nội dung bạn muốn gửi (giới hạn 100 chữ):\n" ESC "tlta @ %s\n" );
				
	
	return 0;
}
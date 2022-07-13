
#include <cmd.h>
#include <ansi.h>
#include <npc.h>
inherit ITEM;
inherit USABLE;
int get_item_color() { return 2; }
int get_item_value() {return 40 ;}
int get_item_value_2() {return 40 ;}
// 函数：构造处理
void create()
{
        set_name("Ân Xá Phù");
        set_picid_1(0401);
        set_picid_2(0401);
        set_value(1000);
	//	set_save("knb2",3000);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sau khi sử dụng sẽ giảm 100 điểm Ác Danh PK";
}
// 函数：使用效果
int get_use_effect( object me ) 
{
	send_user( me, "%c%c%w%s", ':', 3, 0,sprintf("Sử dụng Phù này có thể giúp bạn giảm 100 điểm Ác Danh PK, bạn chắc chắn muốn sử dụng không ?\n"ESC"Xác nhận\nuse ! %x#\n"ESC"Hủy bỏ",getoid(this_object())));
	return 0;
}
// 函数：使用效果
int confirm_use( object me ) 
{ 
	if ( me->get_pk() <= 0 )
	return 0;
	me->add_pk(-100);
	return 1;
}

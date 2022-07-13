#include <ansi.h>
//inherit USABLE;
inherit ITEM;

int get_item_value() {return 10 ;}
int get_item_value_2() {return 10 ;}
int get_item_number() {return 10001030 ;}
int get_item_color() {return 1 ;}

int is_jishihulu() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Tế Thế Bảo Ngọc");
        set_picid_1(9811);
        set_picid_2(9811);
        set_value(40);
	//	set_save("knb",10);
}

// 函数：获取描述
string get_desc()
{
        return "Tương truyền đây là loại ngọc quí mà Thái Thượng Lão Quân dùng.
 Mỗi lần sử dụng có thể tăng giới hạn của Tế Thế Hồ Lô thêm 5 vạn điểm Kinh nghiệm.";
}

// 函数：使用效果
//int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	return "npc/std/0003"->do_agend(who);
}

//int get_use_effect( object me ) 
//{
//	return __FILE__->get_use_effect_callout(me,this_object());	
//}

int get_use_effect_callout( object who,object item) 
{
	if ( !who->get_save_2("jishihulu.id") )
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("Muốn sử dụng Tế Thế Hồ Lô không\n"ESC"Chấp nhận\nuse ! %x#\n"ESC"Hủy bỏ",getoid(item))); 
	else
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("Sử dụng Tế Thế Hồ Lô trực tiếp gia tăng "HIR "Kinh Nghiệm Lưu Trữ"NOR " cao nhất 5 vạn điểm，ngươi muốn sử dụng không ？（"HIR "Lưu trữ kinh nghiệp cao nhất là 3 triệu"NOR "）\n"ESC"Xác nhận\nuse ! %x#\n"ESC"Huỷ bỏ",getoid(item))); 
	return 0;
}
#include <item.h>
#include <ansi.h>
#include <city.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Tế Thế Hồ Lô");
        set_picid_1(4271);
        set_picid_2(4271);
        set_value(1);
        set_no_give(1);
        set_no_drop(1);
        set_no_sell(1);  
}
//领取的葫芦
int is_agent() { return 1; }

// 函数：获取描述
string get_desc()
{
	int limit;
	
	limit = get("jishihulu.limit");
	if ( !limit )
	        return "Tế Thế Hồ Lô Phổ Độ, trước khi giá trị tích lũy Kinh nghiệm của nó đạt đến mức cao nhất, có thể tăng thêm 10％ Kinh nghiệm tiêu diệt yêu quái của bạn";
	return sprintf("Tế Thế Hồ Lô Phổ Độ, trước khi giá trị tích lũy Kinh nghiệm của nó đạt đến mức cao nhất, có thể tăng thêm 10％ Kinh nghiệm tiêu diệt yêu quái của bạn Kinh nghiệm tích lũy %d / %d \n"
			HIY"Nhắp chuột phải có thể trả lại Hồ Lô Tế Thế",get("jishihulu.exp"),get("jishihulu.limit")
			);
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("Phải chăng bạn muốn trả lại Tế Thế Hồ Lô\n"ESC"Trả lại Tế Thế Hồ Lô\nhulu 7\n"ESC"Hủy bỏ",)); 
	return 0;
}
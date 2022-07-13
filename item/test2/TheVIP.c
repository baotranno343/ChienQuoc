#include <ansi.h>
inherit ITEM;
//inherit COMBINED;

int get_item_value() {return 500 ;}
int get_item_value_2() {return 500 ;}
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Thẻ VIP");
        set_picid_1(3812);
        set_picid_2(3812);
        set_value(1000);
		//set_amount(1);
		set_no_give(1);		
        set_no_sell(1);
		set_no_drop(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Thẻ dành cho Hội viên VIP. \nCó thẻ này có thể sử dụng \nđược các chức năng ưu đãi VIP."; 
}
string get_tail_desc()
{
	object item = this_object();
	string desc;

	if (item->get_lock_time() == 0)
	{
		desc = HIG "(Thẻ Hội viên VIP)" NOR "[Hạn sử dụng 31 ngày]\n ";
	}

	return desc;
}
int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object me,object gift) 
{	
	string arg;
	if (gift->get_lock_time()==0) 
	{
	send_user( me, "%c%c%c", 0xA2, 4, 1);
	me->set_save("thevip",1);
	me->add_save("theviptime", 3600);
	gift->set_lock_time(time()+31*24*60*60);
	send_user( me, "%c%d%c", 0x31, getoid(gift), 0 );
	}
	if (gift->get_lock_time()<time())
	{
		send_user(me, "%c%s", '!', "Thẻ VIP đã Hết hạn sử dụng");
		return 0;		
	}
	"cmd/user/thevip"->main(me,arg);
	return 0;
}
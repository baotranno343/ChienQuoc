#include <ansi.h>
inherit ITEM;
// 函数：构造处理
void create()
{
        set_name("变身卡");
        set_picid_1(3810);
        set_picid_2(3810);
        set_value(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "使用后能改变外型，持续时间两小时。"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	if ( "sys/sys/magic_card"->change_shape(who,11,7200) == 0 )
		return ;
	item->remove_from_user();
	destruct(item);
}


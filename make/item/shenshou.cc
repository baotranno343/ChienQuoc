// make/item/make_ss_item生成

#include <item.h>
#include <ansi.h>
inherit ITEM;
inherit USABLE;   
int get_item_color() { return 2;};
// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set("picid",%d);
        set_value(%d);
}

// 函数：获取描述
string get_desc() 
{
	return "%s";
}
// 函数：使用效果
int get_use_effect( object me )
{
	send_user( me, "%s", ':', 3, 0,sprintf("使用后将会获得神兽，是否使用？\n"ESC"确定\nuse ! %s\n"ESC"取消",getoid(this_object()))); 
	return 0;
}
// 函数：使用效果
int confirm_use( object me ) 
{ 
	return "sys/user/beast"->use_shenshou_item(me,this_object());
}

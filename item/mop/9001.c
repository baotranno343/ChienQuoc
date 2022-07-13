#include <ansi.h>
inherit ITEM;
// 函数：构造处理
void create()
{
        set_name("Chìa Khóa Tử Kim, Chìa Khóa Thanh Đồng, Chìa Khóa Hồng Mộc");
        set_picid_1(4981);
        set_picid_2(4981);
        set_value(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "装有紫金钥匙、青铜钥匙、红木钥匙的包裹，右键使用打开。"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash;
	object item;
	string result;
        if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY-2 )
        {
                send_user(who,"%c%s",'!', "您需要三个物品空间。" );
                return ;
        }		
	gift->remove_from_user();
	destruct(gift);
	item = new ("/item/mop/0202");
	if ( item )
	{		
		p = item->move(who,-1);
		item->add_to_user(p);	
	}
	item = new ("/item/mop/0201");
	if ( item )
	{		
		p = item->move(who,-1);
		item->add_to_user(p);	
	}
	item = new ("/item/mop/0200");
	if ( item )
	{		
		p = item->move(who,-1);
		item->add_to_user(p);	
	}
	send_user(who,"%c%s",'!',"您获得紫金钥匙、青铜钥匙、红木钥匙！");	
	return 0;
}


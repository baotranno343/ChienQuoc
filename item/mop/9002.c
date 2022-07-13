#include <ansi.h>
inherit ITEM;
// 函数：构造处理
void create()
{
        set_name("五个金灵石");
        set_picid_1(4981);
        set_picid_2(4981);
        set_value(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "装有五个金灵石的包裹，右键使用打开。"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash,index;
	object item;
	string result;
        if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY-4 )
        {
                send_user(who,"%c%s",'!', "您需要五个物品空间。" );
                return ;
        }		
	gift->remove_from_user();
	destruct(gift);
	for (index=0;index<5;index++)
	{
		item = new ("/item/sell/9304");
		if ( item )
		{		
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
	}
	send_user(who,"%c%s",'!',"您获得五个金灵石！");	
	return 0;
}

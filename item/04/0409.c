#include <ansi.h>
inherit ITEM;
// 函数：构造处理
void create()
{
        set_name("乱世星人大礼包");
        set_picid_1(4981);
        set_picid_2(4981);
        set_value(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "装有礼品的包裹。"; 
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
        if( USER_INVENTORY_D->get_free_count(who) < 1 )
        {
                send_user(who,"%c%s",'!', "您还需要一个物品空间。" );
                return ;
        }		
	gift->remove_from_user();
	destruct(gift);
	item = new ("/item/std/8000");
	if ( item )
	{		
		p = item->move2(who);
		item->add_to_user(p);	
	}
	item = new ("/quest/book"->get_book_file());
	if ( item )
	{		
		p = item->move2(who);
		item->add_to_user(p);	
	}	
	who->add_cash(10000);
	send_user(who,"%c%s",'!',"您获得藏宝图，技能书和一万金！");	
	return 0;
}


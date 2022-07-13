#include <ansi.h>
#include <skill.h>
#include <effect.h>
inherit ITEM;

int * magic = ({ 4176, 3292, 2571, 37201, 2618, 23131, 2416, 24161, 22152, 23141, 2316, 3643, 4147, 4173, });
int * pet = ({ 1616, 1619, 1624, 1625, 1632, 1634, });

int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("帮派虚宝包");
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
	int rate,p,cash, i, pf;
	object item, item2;	
	string result;	
        
        if( USER_INVENTORY_D->get_free_count(who) < 8 )
        {
                send_user(who,"%c%s",'!', "您需要八个物品空间。" );
                return ;
        }	
	gift->remove_from_user();
	destruct(gift);
	result = sprintf(HIR"%s打开帮派虚宝包，得到", who->get_name());
	item = new ("/item/sell/0026");
	if ( item )
	{	
		item->set_amount(2);
		result = result + item->get_name();
		write_user( who, ECHO "您获得两枚"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	item = new ("/item/sell/0027");
	if ( item )
	{	
		item->set_amount(2);
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得两个"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	item = new ("/item/sell/0012");
	if ( item )
	{	
		item->set_amount(10);
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得10个"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	item = new ("/item/sell/0029");
	if ( item )
	{	
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}
	item = new ("/item/sell/0029");
	if ( item )
	{	
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	item = new ("/item/93/9303");
	if ( item )
	{	
		item->set_level(4);
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	item = new ("/item/93/9305");
	if ( item )
	{	
		item->set_level(4);
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	item = new ("/item/std/6002");
	if ( item )
	{	
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	result += "。";
	USER_D->user_channel(result);	
	pf = magic[random(sizeof(magic))];
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), pf, 1, OVER_BODY, PF_ONCE );
	return 0;
}


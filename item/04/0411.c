#include <ansi.h>
#include <skill.h>
#include <effect.h>
inherit ITEM;

int * magic = ({ 4176, 3292, 2571, 37201, 2618, 23131, 2416, 24161, 22152, 23141, 2316, 3643, 4147, 4173, });
int * pet = ({ 1616, 1619, 1624, 1625, 1632, 1634, });

// 函数：构造处理
void create()
{
        set_name("全家礼包");
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
	if (who->get_level()<10)
        {
                send_user(who,"%c%s",'!', "您的等级不足10级。" );
                return ;
        }	
        if( USER_INVENTORY_D->get_free_count(who) < 9 )
        {
                send_user(who,"%c%s",'!', "您需要九个物品空间。" );
                return ;
        }	
	gift->remove_from_user();
	destruct(gift);
	result = sprintf(HIR "%s打开乱世英雄礼包，得到", who->get_name());
	item = new (sprintf("/item/final/16/%d", pet[random(sizeof(pet))]));
	if ( item )
	{	
		result = result + item->get_name();
		write_user( who, ECHO "您获得"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	item = new ("/item/08/0003");
	if ( item )
	{	
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	item = new ("/item/08/0004");
	if ( item )
	{	
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}	
	item = new ("/item/08/0001");
	if ( item )
	{	
		result += "、";
		result = result + item->get_name();
		write_user( who, ECHO "您获得"+item->get_name()+"。" );	
		p = item->move2(who);
		item->add_to_user(p);			
	}
	if (random100()<60)
	{
		item = new ("/item/91/9160");
		if ( item )
		{	
			result += "、";
			item->set_amount(5);
			result = result + item->get_name();
			write_user( who, ECHO "您获得"+item->get_name()+"。" );	
			p = item->move2(who);
			item->add_to_user(p);			
		}		
	}	
	if (random100()<60)
	{
		item = new ("/item/91/9162");
		if ( item )
		{	
			result += "、";
			item->set_amount(5);
			result = result + item->get_name();
			write_user( who, ECHO "您获得"+item->get_name()+"。" );	
			p = item->move2(who);
			item->add_to_user(p);			
		}		
	}	
	if (random100()<60)
	{
		item = new ("/item/91/9164");
		if ( item )
		{	
			result += "、";
			item->set_amount(5);
			result = result + item->get_name();
			write_user( who, ECHO "您获得"+item->get_name()+"。" );	
			p = item->move2(who);
			item->add_to_user(p);			
		}		
	}	
	if (random100()<20)
	{
		item = new ("/item/91/9167");
		if ( item )
		{	
			result += "、";
			item->set_amount(3);
			result = result + item->get_name();
			write_user( who, ECHO "您获得"+item->get_name()+"。" );	
			p = item->move2(who);
			item->add_to_user(p);			
		}		
	}	
	if (random100()<5)
	{
		item = new ("/item/std/9501");
		if ( item )
		{	
			result += "、";
			result = result + item->get_name();
			write_user( who, ECHO "您获得"+item->get_name()+"。" );	
			p = item->move2(who);
			item->add_to_user(p);			
		}		
	}	
	
	result += "。";
	USER_D->user_channel(result);	
	pf = magic[random(sizeof(magic))];
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), pf, 1, OVER_BODY, PF_ONCE );
	return 0;
}


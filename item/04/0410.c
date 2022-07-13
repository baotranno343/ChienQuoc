#include <ansi.h>
#include <skill.h>
#include <effect.h>
inherit ITEM;

int * magic = ({ 4176, 3292, 2571, 37201, 2618, 23131, 2416, 24161, 22152, 23141, 2316, 3643, 4147, 4173, });

// 函数：构造处理
void create()
{
        set_name("乱世英雄大礼包");
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
        if( USER_INVENTORY_D->get_free_count(who) < 3 )
        {
                send_user(who,"%c%s",'!', "您需要三个物品空间。" );
                return ;
        }	
	gift->remove_from_user();
	destruct(gift);
	result = sprintf(HIR"%s打开乱世英雄礼包，得到", who->get_name());
	for (i = 0;i<2;i++)
	{
		item = 0;
		item2 = 0;
		switch(random(8))
		{
		case 0:
			item = new (sprintf("/item/std/%d", 8001+random(4)));
			break;
		case 1:
			item = new ("/item/08/0003");
			item2 = new ("/item/08/0004");
			break;
		case 2:
			item = new ("/item/08/0001");
			break;
		case 3:
			item = new ("/item/08/0002");
			break;
		case 4:
			item = new ("/quest/book"->get_book_file());
			break;
		case 5:
			if (random(2)==0)
				item = new ("/quest/armor"->get_armor_file_2(who->get_level()));
			else
				item = new ("/quest/weapon"->get_weapon_file_2(who->get_level()));
			if (item) "/sys/item/equip"->init_equip_prop_1(item);
			break;
		case 6:
			item = new ("/quest/product2"->get_random_product2(who->get_level()));
			break;
		case 7:
			item = new ("/item/std/0089");
			if (item) item->set_potential(8000);
			break;
		}
		if ( item )
		{	
			if (i==0)
				result = result + item->get_name();
			else
				result = result + "、"+ item->get_name();
			write_user( who, ECHO "您获得"+item->get_name()+"。" );	
			p = item->move2(who);
			item->add_to_user(p);			
		}	
		if ( item2 )
		{	
			result = result + "、"+ item2->get_name();
			write_user( who, ECHO "您获得"+item2->get_name()+"。" );	
			p = item2->move2(who);
			item2->add_to_user(p);			
		}			
	}
	result += "。";
	USER_D->user_channel(result);	
	pf = magic[random(sizeof(magic))];
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), pf, 1, OVER_BODY, PF_ONCE );
	return 0;
}


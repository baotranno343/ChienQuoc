#include <ansi.h>
inherit ITEM;
// 函数：构造处理
void create()
{
        set_name("龙卷风礼包");
        set_picid_1(4981);
        set_picid_2(4981);
        set_value(1);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "战国令1个、战国号角1个、尚方咸鱼1个、小血石1个、济世宝玉1个。"; 
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
	string *item_g=({"/item/08/0001","/item/08/0002","/item/sell/0028","/item/08/0003","/item/sell/0044",});
        if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY-4 )
        {
                send_user(who,"%c%s",'!', "您需要5个物品空间，请先整理一下再打开礼包吧！" );
                return ;
        }		
	gift->remove_from_user();
	destruct(gift);

	for (index=0;index<5;index++)
	{
		item = new (item_g[index]);
		if ( item )
		{		
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
	}
	send_user(who,"%c%s",';',"您获得了战国令1个、战国号角1个、尚方咸鱼1个、小血石1个、济世宝玉1个！");
	return 0;
}

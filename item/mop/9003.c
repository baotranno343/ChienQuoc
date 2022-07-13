#include <ansi.h>
inherit ITEM;

int get_item_value() {return 5000000 ;}
int get_item_value_2() {return 5000000 ;}
//int get_item_number() {return 10001099 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("国庆大礼包");
        set_picid_1(3025);
        set_picid_2(3025);
        set_value(198);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "大话战国国庆大礼包，内含多种战国珍稀物品，售价390元宝。"; 
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
	string *item_g=({"/item/08/0015","/item/54/8100","/item/sell/0033","/item/mop/0202","/item/sell/0045","/item/sell/0034","/item/08/0001","/item/sell/0043","/item/sell/0044","/item/sell/0029","/item/sell/0060","/item/sell/0041","/item/sell/0030"});
        if( sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY-12 )
        {
                send_user(who,"%c%s",'!', "您需要13个物品空间，请先整理一下再打开礼包吧！" );
                return ;
        }		
	gift->remove_from_user();
	destruct(gift);

	for (index=0;index<13;index++)
	{
		item = new (item_g[index]);
		if ( item )
		{		
			p = item->move(who,-1);
			item->add_to_user(p);	
		}
	}
	send_user(who,"%c%s",';',"您获得了干将宝石、年兽卡、鲁班宝石、紫金钥匙、瞒天过海符、保底符、战国令、开门芝麻、济世宝玉、尚方宝剑、人参王、锦囊、魔力锤！");
	return 0;
}

